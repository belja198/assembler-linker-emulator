#include "../inc/linker.h"
#include <stdio.h>
#include <string.h>
#include <vector>

int main(int argc, char **argv) {// -hex -place=data@0x4000F000 -place=text@0x40000000 -o mem_content.hex ulaz1.o ulaz2.o 
    vector<LNK_PlaceCmd> place_cmd_vector;
    uint arg_cnt;
    bool is_hex_cmd_found = false;

    // While for place commands
    for (arg_cnt = 1; arg_cnt < argc - 2; arg_cnt++) {
        if (strcmp(argv[arg_cnt], "-o") == 0) {
            break;
        }

        char *arg = argv[arg_cnt];

        if (strcmp(arg, "-hex") == 0) {
            if (!is_hex_cmd_found) {
                is_hex_cmd_found = true;
                continue;
            } else {
                printf("LNK Error: There can't be two -hex arguments!");
                exit(-1);
            }
        }

        if (strncmp(arg, "-place=", 7) == 0) {  //-place=text@0x40000000

            // Find the '@' character
            const char *at_char = strchr(argv[arg_cnt], '@');
            if (at_char == NULL) {
                printf("LNK Error: Invalid arguments!");
                exit(-1);
            }
    
            // Check if the string before '@' is not empty
            if (at_char == argv[arg_cnt]) {
                printf("LNK Error: Invalid arguments!");
                exit(-1);
            }
    
            // Check if the string after '@' is not empty
            if (*(at_char + 1) == '\0') {
                printf("LNK Error: Invalid arguments!");
                exit(-1);
            }
    
            // Check if the string after '@' starts with "0x"
            if (strncmp(at_char + 1, "0x", 2) != 0) {
                printf("LNK Error: Invalid arguments!");
                exit(-1);
            }
    
            // Check if the rest of the string after "0x" contains valid hexadecimal characters
            const char *hex_part = at_char + 3;
            while (*hex_part != '\0') {
                if (!isxdigit(*hex_part)) {
                    return false;
                }
                hex_part++;
            }

            hex_part = at_char + 3;
            char *end_ptr;
            uint hex_value = strtoul(hex_part, &end_ptr, 16);
            if (*end_ptr != '\0') {
                return false;  // Conversion failed
            }

            // Extract the section name
            string section_name;
            char *section_name_ptr = argv[arg_cnt] + 7;
            size_t sectionNameLength = at_char - section_name_ptr;
            section_name.assign(section_name_ptr, sectionNameLength);


            LNK_PlaceCmd place_cmd = {section_name, hex_value};
            printf("\n %d. LNK_PlaceCmd: section_name: %s, address: %08x\n", arg_cnt, place_cmd.section_name.c_str(), place_cmd.adress);
            place_cmd_vector.push_back(place_cmd);

            continue;
        }

        printf("LNK Error: Invalid arguments! Argument at %d not recognized", arg_cnt);
        exit(-1);

    }

    if (!is_hex_cmd_found) {
        printf("LNK Error: Invalid arguments! Option -hex is compulsory");
        exit(-1);
    }

    // -o
    if (strcmp(argv[arg_cnt], "-o") != 0) {
        printf("LNK Error: Invalid arguments! -o was expected as %d. argument, followed by at least one input file", arg_cnt);
        exit(-1);
    }
    arg_cnt++;

    // Output.hex
    char output_file_name[64];
    strcpy(output_file_name, argv[arg_cnt]);
    arg_cnt++;//maybe add some check?

    //init LNK_Data;

    LNK_Data *lnk_data = new LNK_Data;

    // While for input.o
    while (arg_cnt < argc) {
        char file_name_in[64];
        strcpy(file_name_in, argv[arg_cnt]);
        FILE *input_file_handle = fopen(file_name_in, "r");
        if (input_file_handle == NULL) {
            printf("Error: File not opened\n");
            exit(1);
        }
        printf("\n%s: %d\n", file_name_in, arg_cnt);
        LNK_readAndProcessObjectFile(lnk_data, input_file_handle);
        fclose(input_file_handle);
        arg_cnt++;
    }

    // Map sections to LNK_data->section_address_mapping_vector
    LNK_mapSectionAdresses(lnk_data, place_cmd_vector);

    // Update symbol values
    LNK_updateSymtabs(lnk_data);

    LNK_globalSymNameOffsetMapGenerate(lnk_data);

    // Resolve relocation
    LNK_relaRecordsReslove(lnk_data);

    FILE *output_file_handle = fopen(output_file_name, "w");

    LNK_createOutputHexFile(lnk_data, output_file_handle);
    

    delete lnk_data;

    return 0;
}


void LNK_createOutputHexFile(LNK_Data *lnk_data, FILE *output_file_handle) {
    // Iterate through the weird structure and print damn code
    //addres: 2hex 2hex 2.....
    //section_address_mapping_vector
    for (uint i = 0; i < lnk_data->section_address_mapping_vector.size(); i++) {

        // Take first string, iterate through the vector in pair
        //string section_name = lnk_data->section_address_mapping_vector[i].first;

        // Iterate through vector<LNK_SectionAddressMapping> from section_address_mapping_vector

        for (uint j = 0; j < lnk_data->section_address_mapping_vector[i].second.size(); j++) {
            uint sctn_address = lnk_data->section_address_mapping_vector[i].second[j].sctn_address;
            uint file_num = lnk_data->section_address_mapping_vector[i].second[j].file_num;
            uint sctn_vector_ndx = lnk_data->section_address_mapping_vector[i].second[j].sctn_vector_ndx;

            for (uint k = 0; k < lnk_data->sections[file_num][sctn_vector_ndx].bytes.size(); k++) {
                
                if (k % 8 == 0) {
                    fprintf(output_file_handle, "\n%08x:", sctn_address + k);
                }
                fprintf(output_file_handle, " %02x", lnk_data->sections[file_num][sctn_vector_ndx].bytes[k]);
            }
        }

    }

}

void LNK_globalSymNameOffsetMapGenerate(LNK_Data *lnk_data) {

    for (uint file_num = 0; file_num < lnk_data->symtabs.size(); file_num++) {
        for (uint sym_ndx = 1; sym_ndx < lnk_data->symtabs[file_num].size(); sym_ndx++) {
            // Check if symbol is global and defined
            if (lnk_data->symtabs[file_num][sym_ndx].is_global && lnk_data->symtabs[file_num][sym_ndx].section_index != 0) {
                string sym_name = lnk_data->symtabs[file_num][sym_ndx].name;
                uint sym_offset = lnk_data->symtabs[file_num][sym_ndx].value;
                // check for double definitions ERROR
                if (lnk_data->global_sym_name_offset_map.count(sym_name) == 1) {
                    // ERROR
                    printf("\nLNK ERROR: double definition of symbol: %s, second definition in file_num: %d\n", sym_name.c_str(), file_num);
                    delete lnk_data;
                    exit(1);

                } else {
                    // Add to map
                    lnk_data->global_sym_name_offset_map[sym_name] = sym_offset;
                }
            }
        }
    }
    printf("\nglobal_sym_name_offset_map:\n");
    for (const auto& entry : lnk_data->global_sym_name_offset_map) {
        printf("Key: %s, Value: %#08x\n", entry.first.c_str(), entry.second);
    }

}


    // note: what to do if a symbol is extern
    // use the symbol_index to get the name, then search for the name in other files and use its value if the ndx is not 0
void LNK_relaRecordsReslove(LNK_Data *lnk_data) {
    // iterate sections , and rela_records from sections
    // update vector bytes in said section, use offset in rela_record
    // symbol_index, get the name from symtab, if there is a value there(sym was defined in the same section)
    // use that value, otherwise search for the symbol in global_sym_name_offset_map

    // iterate through files
    for (uint file_num = 0; file_num < lnk_data->sections.size(); file_num++) {

        printf("\n****************\n");
        printf("\nfile_num: %d\n", file_num);
        // iterate through sections of a file
        for (uint sctn_num = 0; sctn_num < lnk_data->sections[file_num].size(); sctn_num++) {

            printf("\n+++++++++++++++\n");
            printf("\nsctn_num: %d\n", sctn_num);
            //iterate through rela record of said section
            for (uint i = 0; i < lnk_data->sections[file_num][sctn_num].rela_records.size(); i++) {
                printf("\n________________\n");
                printf("\ncurr rela record entry: %d: ", i);
                uint offset = lnk_data->sections[file_num][sctn_num].rela_records[i].offset;
                uint addend = lnk_data->sections[file_num][sctn_num].rela_records[i].addend;
                int sym_ndx = lnk_data->sections[file_num][sctn_num].rela_records[i].symbol_index;
                

                printf(" offset: %#08x, addend: %#08x, sym_ndx %d\n", offset, addend, sym_ndx);
                uint rela_patch_value;

                //fetch from symtab[file_num][sym_ndx]
                //check if it is extern, if it is fetch from map i guess
                //
                SymTabEntry symtab_entry = lnk_data->symtabs[file_num][sym_ndx];
                printf("symtab_entry.name: %s\n", symtab_entry.name.c_str());
                printf("symtab_entry.value: %#08x\n", symtab_entry.value);
                printf("symtab_entry.section_index: %d\n", symtab_entry.section_index);

                if (symtab_entry.section_index != 0) {
                    rela_patch_value = symtab_entry.value;
                    printf("Symbol found in local file\n");
                } else {
                    // first check if it exists
                    printf("Symbol not found in local file\n");
                    if (lnk_data->global_sym_name_offset_map.count(symtab_entry.name) == 1) {
                        rela_patch_value = lnk_data->global_sym_name_offset_map[symtab_entry.name];
                    } else {
                        // ERROR i guess, undefined symbol
                        printf("\nLNK ERROR: symbol %s not defined\n", symtab_entry.name.c_str());
                    }
                }
                printf("rela_patch_value before addend: %#08x\n", rela_patch_value);
                rela_patch_value += addend;
                printf("rela_patch_value after addend: %#08x\n", rela_patch_value);
                //write to bytes
                // 4 writes, use little endian again
                lnk_data->sections[file_num][sctn_num].bytes[offset++] = (uint8_t) (rela_patch_value >> 0);
                lnk_data->sections[file_num][sctn_num].bytes[offset++] = (uint8_t) (rela_patch_value >> 8);
                lnk_data->sections[file_num][sctn_num].bytes[offset++] = (uint8_t) (rela_patch_value >> 16);
                lnk_data->sections[file_num][sctn_num].bytes[offset++] = (uint8_t) (rela_patch_value >> 24);
                
            }
        }
    }

    
}


void LNK_updateSymtabs(LNK_Data *lnk_data) {
    printf("\n");
    for (uint i = 0; i < lnk_data->symtabs.size(); i++) {
        printf("\n#symtab: %d\n", i);
        for (uint j = 0; j < lnk_data->symtabs[i].size(); j++) {
            SymTabEntry entry = lnk_data->symtabs[i][j];
            printf("%d: %08x %d %d %d %d %s \n", j, entry.value, entry.size, entry.type, entry.is_global, entry.section_index, entry.name.c_str());
        }
    }
    
    // Iterate through section_address_mapping_vector
    for (uint i = 0; i < lnk_data->section_address_mapping_vector.size(); i++) {
        // Take first string, iterate through the vector in pair
        string section_name = lnk_data->section_address_mapping_vector[i].first;

        // Iterate through vector<LNK_SectionAddressMapping> from section_address_mapping_vector

        for (uint j = 0; j < lnk_data->section_address_mapping_vector[i].second.size(); j++) {
            // Get sctn_ndx for symtab, use sctn_vector_ndx
            uint sctn_address = lnk_data->section_address_mapping_vector[i].second[j].sctn_address;
            // LNK_SectionAddressMapping use this to know what file_num symtab to update
            uint file_num = lnk_data->section_address_mapping_vector[i].second[j].file_num;
            uint sctn_vector_ndx = lnk_data->section_address_mapping_vector[i].second[j].sctn_vector_ndx;
            uint sctn_sym_ndx = lnk_data->sections[file_num][sctn_vector_ndx].section_index;

            // Iterate through a specific symtab using file_num and sctn_index(to check if it needs to be updated)
            // update by adding address from lnk_data->section_address_mapping_vector[i].second[j] to symbol value
            for (uint k = 0; k < lnk_data->symtabs[file_num].size(); k++) {
                if (lnk_data->symtabs[file_num][k].section_index == sctn_sym_ndx) {
                    lnk_data->symtabs[file_num][k].value += sctn_address;
                    // maybe add here to global_symbol_name_offset_pairs
                }
            }

        }


    }

    //DEBUG PRINT
    // prinit maybe all symtabs
    printf("\n");
    for (uint i = 0; i < lnk_data->symtabs.size(); i++) {
        printf("\n#symtab: %d\n", i);
        for (uint j = 0; j < lnk_data->symtabs[i].size(); j++) {
            SymTabEntry entry = lnk_data->symtabs[i][j];
            printf("%d: %08x %d %d %d %d %s \n", j, entry.value, entry.size, entry.type, entry.is_global, entry.section_index, entry.name.c_str());
        }
    }




}



// Map original sections to the lnk_data->section_address_mapping_vector
void LNK_mapSectionAdresses(LNK_Data *lnk_data, vector<LNK_PlaceCmd> place_cmd_vector) {
    // First iterate through place_cmd_vector

    uint next_address = 0;


    printf("\nlnk_data->section_names_for_mapping.size() = %ld\n", lnk_data->section_names_for_mapping.size());

    printf("\nnext_address %08x\n", next_address);
    //SOMEERROR 
    for (uint i = 0; i < place_cmd_vector.size(); i++) {

        //vector<pair<string, vector<LNK_SectionAddressMapping>>> section_address_mapping_vector
        pair<string, vector<LNK_SectionAddressMapping>> curr_mapping_pair;
        curr_mapping_pair.first = place_cmd_vector[i].section_name;
        next_address = place_cmd_vector[i].adress;
        printf("\nnext_address %08x\n", next_address);

        //horrible c arrays are better i still long for them
        for (uint l = 0; l < lnk_data->section_names_for_mapping.size(); l++)
            if (lnk_data->section_names_for_mapping[l] == place_cmd_vector[i].section_name) {
                lnk_data->section_names_for_mapping.erase(lnk_data->section_names_for_mapping.begin() + l);
                break;
            }

        // Iterate through all files to try and find sections with the name in the command
        for (uint j = 0; j < lnk_data->sections.size(); j++) {  // Iterate through files

            for (uint k = 0; k < lnk_data->sections[j].size(); k++) {   // Iterate through sections in file 'j'

                if (lnk_data->sections[j][k].section_name == curr_mapping_pair.first) {
                    // Do the mapping here
                    LNK_SectionAddressMapping curr_maping;
                    curr_maping.file_num = j;
                    curr_maping.sctn_vector_ndx = k;
                    curr_maping.sctn_address = next_address;
                    // Calculate the next address
                    next_address = next_address + lnk_data->sections[j][k].bytes.size();
                    printf("\nnext_address %08x\n", next_address);

                    curr_mapping_pair.second.push_back(curr_maping);

                    break;
                }

            }

        }

        // Add the pair to section_address_mapping_vector
        lnk_data->section_address_mapping_vector.push_back(curr_mapping_pair);
    }

    //RESET next_addr to 0 if the section_address_mapping_vector is still empty meaning that there were no sections of said name
    //or let it be an error


    printf("\nnext_address %08x\n", next_address);

    // Iterate again to map the rest of the sections, exclude sections that were processed using place cmd
    // next_address is either zero or after last places sections using place cmd
    printf("\nlnk_data->section_names_for_mapping.size() = %ld\n", lnk_data->section_names_for_mapping.size());
    for (uint i = 0; i < lnk_data->section_names_for_mapping.size(); i++) {

        pair<string, vector<LNK_SectionAddressMapping>> curr_mapping_pair;
        curr_mapping_pair.first = lnk_data->section_names_for_mapping[i];

        for (uint j = 0; j < lnk_data->sections.size(); j++) {

            for (uint k = 0; k < lnk_data->sections[j].size(); k++) {   // Iterate through sections in file 'j'

                if (lnk_data->sections[j][k].section_name == curr_mapping_pair.first) {
                    // Do the mapping here
                    LNK_SectionAddressMapping curr_maping;
                    curr_maping.file_num = j;
                    curr_maping.sctn_vector_ndx = k;
                    curr_maping.sctn_address = next_address;
                    // Calculate the next address
                    next_address = next_address + lnk_data->sections[j][k].bytes.size();
                    printf("\nnext_address %08x\n", next_address);

                    curr_mapping_pair.second.push_back(curr_maping);

                    break;
                }

            }

        }


        // Add the pair to section_address_mapping_vector
        lnk_data->section_address_mapping_vector.push_back(curr_mapping_pair);
    }

    // DEBUG PRINT
    printf("\nsection_address_mapping_vector\n");
    for (uint i = 0; i < lnk_data->section_address_mapping_vector.size(); i++) {
        printf("%s: ", lnk_data->section_address_mapping_vector[i].first.c_str());
        for (uint j = 0; j < lnk_data->section_address_mapping_vector[i].second.size(); j++) {
            printf("{file_num:%d, sctn_vector_ndx:%d, sctn_address:%08x} -> ", lnk_data->section_address_mapping_vector[i].second[j].file_num ,
                            lnk_data->section_address_mapping_vector[i].second[j].sctn_vector_ndx, 
                            lnk_data->section_address_mapping_vector[i].second[j].sctn_address);
        }

        printf("\n");
    }

    lnk_data->section_names_for_mapping.clear();

}



// Read a file and make struct corresponding to the ones in the file
void LNK_readAndProcessObjectFile(LNK_Data *lnk_data, FILE *input_file_handle) {
    //printf("LNK_fileRead enter f\n");


    //first is symtab, read it and make a symtab in lnk_data->symtabs[]
    char line[256];
    vector<SymTabEntry> symtab; //put this in lnk_data->symtabs using push_back
    //printf("LNK_fileRead before first fgets\n");
    fgets(line, sizeof(line), input_file_handle);   //#symtab
    //printf("LNK_fileRead before second fgets\n");
    fgets(line, sizeof(line), input_file_handle);   //Num Val      Size Type  Bind Ndx Name

    while(fgets(line, sizeof(line), input_file_handle)) {
        //printf("LNK_fileRead while %d\n", iteration);

        if (strcmp(line, "\n") == 0) {
            break;
        }

        SymTabEntry entry;
        int num;
        char is_global_str[8];
        char sym_type_str[8];
        char sym_name[32] = "";

        int parsed_fields = sscanf(line, "%d: %x %d %s %s %d %s %[^\n]",
                                  &num, &entry.value, &entry.size, sym_type_str,
                                  is_global_str, &entry.section_index, sym_name, line);

        //entry.is_global = (strcmp(is_global_str, "GLOB") == 0);

        if (strcmp(is_global_str, "GLOB") == 0)
            entry.is_global = true;
        else 
            entry.is_global = false;

        if (strcmp(sym_type_str, "SCTN") == 0)
            entry.type = SYM_TYPE_SCTN;
        else 
            entry.type = SYM_TYPE_NOTYP;

        entry.name = sym_name;

        //printf("Parsed fields: %d\n", parsed_fields);
        //printf("Line: %s\n", line);

        printf("Val: %0x, Size: %d, Type: %d, Bind: %s, Ndx: %d, Name: %s\n",
            entry.value, entry.size, entry.type, entry.is_global ? "GLOB" : "LOC", entry.section_index, entry.name.c_str());

        symtab.push_back(entry);
        
    }
    lnk_data->symtabs.push_back(symtab);

    //sections
    vector<SctnContentLNK> my_sections;
    while(fgets(line, sizeof(line), input_file_handle)) {

        if (strncmp(line, "#rela.", 6) == 0) {
        // Line starts with "rela.", so break out of the loop
            break;
        }

        char section_name[32];
        //get the section name #sctn_name
        sscanf(line, "#%s", section_name);
        uint8_t bytes[8];
        uint address;
        printf("%s", section_name);
        string section_name_s = section_name;

        int sym_ndx;
        for (sym_ndx = 0; sym_ndx < symtab.size(); sym_ndx++) {
            if (symtab[sym_ndx].name == section_name_s) {
                break;
            }
        }
        printf(" %d \n", sym_ndx);
        //find the section index by name from the symtab
        SctnContentLNK sctn_content;
        sctn_content.section_index = sym_ndx;
        sctn_content.section_name = section_name_s;

        // Add section names without repetition for easier fetching in the mapping function
        bool section_name_exists = false;
        for (uint k = 0; k < lnk_data->section_names_for_mapping.size(); k++)
            if (lnk_data->section_names_for_mapping[k] == section_name_s) {
                section_name_exists = true; break;
            }
        
        if (!section_name_exists)
            lnk_data->section_names_for_mapping.push_back(section_name_s);

        //fill the vector in the section
        while(fgets(line, sizeof(line), input_file_handle)) {

            if (strcmp(line, "\n") == 0) {
                break;
            }
            //READ 4 BY 4
            int num_conversions = sscanf(line, "%x: %hhx %hhx %hhx %hhx  %hhx %hhx %hhx %hhx",
                 &address, &bytes[0], &bytes[1], &bytes[2], &bytes[3], &bytes[4], &bytes[5], &bytes[6], &bytes[7]);

            printf("%08x(conv: %d) :", address, num_conversions);
            //make a section using the data
            for (uint j = 0; j < num_conversions - 1; j++) {
                printf("%hhx ", bytes[j]);
                sctn_content.bytes.push_back(bytes[j]);
            }
            printf("\n");

            
        }

        //add section to my_sections
        my_sections.push_back(sctn_content);
    }


    //rela records
    
    //currently in line there is #rela.sctn_name
    do {

        if (strcmp(line, "\n") == 0) {
            break;
        }

        vector<RelaEntry> my_rela_records;
        char section_name_from_rela_c[64];
        sscanf(line, "#rela.%s", section_name_from_rela_c);
        printf("#rela.%s ", section_name_from_rela_c);
        string section_name_from_rela = section_name_from_rela_c;
        int sym_ndx;
        for (sym_ndx = 0; sym_ndx < symtab.size(); sym_ndx++) {
            if (symtab[sym_ndx].name == section_name_from_rela) {
                break;
            }
        }

        printf("%d \n", sym_ndx);

        fgets(line, sizeof(line), input_file_handle); // Offset   Type        Symbol Addend

        //read all rela entries of curr rela record
        while(fgets(line, sizeof(line), input_file_handle)) {

            if (strcmp(line, "\n") == 0) {
                break;
            }

            RelaEntry rela_entry;

            char type_str_c[16];

            sscanf(line, "%08x %s %d %d", &rela_entry.offset, type_str_c, &rela_entry.symbol_index, &rela_entry.addend);

            if (strcmp(type_str_c, "R_X86_64_32") == 0)
                rela_entry.rela_type = R_X86_64_32;

            printf("%08x %d %d %d\n", rela_entry.offset, rela_entry.rela_type, rela_entry.symbol_index, rela_entry.addend);
            my_rela_records.push_back(rela_entry);
        }

        int sctn_index_in_sections = 0;
        for (int j = 0; j < my_sections.size(); j++) {
            if (my_sections[j].section_index == sym_ndx) {
                sctn_index_in_sections = j;
                break;
            }
        }
        printf("sctn ndx in sections %d \n", sctn_index_in_sections);
        // Add my_rela_records to my_sections at specific sctn index, using sym index
        my_sections[sctn_index_in_sections].rela_records = my_rela_records;
    } while(fgets(line, sizeof(line), input_file_handle));

    // Add my_sections to lnk_data vec
    lnk_data->sections.push_back(my_sections);


    //maybe something else ?
}