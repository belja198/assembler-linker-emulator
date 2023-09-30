#include "../inc/assembler.h"
#include <iostream>
#include <stdio.h>
#include <string.h>
#include <vector>
using namespace std;

ASM_data asm_data;

void DEBUG_PRINT() {
  
}

int ASM_addSymbol(int val, SymType symType, bool isGlobal, int sctnNdx,string symbol_name) {
  //printf("ASM_addSymbol entry\n");
  //check if there is a sym with the same name
  for (int i = 0; i < asm_data.symtab.size(); i++) {
    if (asm_data.symtab[i].name == symbol_name) {//symbol is already in the symtab
       //if (sctnNdx == 0) { //this is just a usage of the symb
       // return 0;
      //}
      if (asm_data.symtab[i].section_index == 0) {//define the symb if it was just declared
        asm_data.symtab[i].value = val;
        asm_data.symtab[i].type = symType;
        asm_data.symtab[i].is_global = isGlobal;
        asm_data.symtab[i].section_index = sctnNdx; //now it is defined
        return 0;
      }
      cout << "ASM ERROR: Symbol: " << symbol_name << " is already defined" << endl;
      return -1;
    }
  }
  // if there isn't a symbol with the same name, add a new one :d
  SymTabEntry sym = {val, symType, isGlobal, sctnNdx, 0, symbol_name};

  asm_data.symtab.push_back(sym);

  return 0;

}


int ASM_declareSymbols(vector<string> sym_name_list) {
  //printf("ASM_declareSymbols entry\n");
  for (int i = 0; i < sym_name_list.size(); i++) {
    if (ASM_addSymbol(0, SYM_TYPE_NOTYP, true, 0, sym_name_list[i]) == -1) {
      return -1;
    }
  }

  return 0;
}




int ASM_makeSymbolsGlobal(vector<string> sym_name_list) {
  //printf("ASM_makeSymbolsGlobal entry\n");
  
  bool undf_sym_err;

  for (int i = 0; i < sym_name_list.size(); i++) {
    undf_sym_err = true;

    for (int j = 0; j < asm_data.symtab.size(); j++) {  //search all symbols
      if (sym_name_list[i] == asm_data.symtab[j].name) {
        asm_data.symtab[j].is_global = true;
        undf_sym_err = false;
        break;  //symbol found and updated, move on to the next
      }
    }

    if (undf_sym_err) {
      return -1; //undefined symbol error, add message later
    }
    
  }

  return 0;
}

int ASM_getCurrSectionVectorIndexInternal() {
  int sctn_index = 0;

  //printf("ASM_getCurrSectionVectorIndexInternal, asm_data.curr_section_symbol_index: %d\n", asm_data.curr_section_symbol_index);
  for (int i = 0; i < asm_data.sections.size(); i++) {
    //printf("ASM_getCurrSectionVectorIndexInternal, asm_data.sections[i].section_index: %d, i: %d\n", asm_data.sections[i].section_index, i);
    if (asm_data.curr_section_symbol_index == asm_data.sections[i].section_index) {
      sctn_index = i;
      break;
    }
  }
  //printf("ASM_getCurrSectionVectorIndexInternal, return_val: %d\n", sctn_index);
  
  return sctn_index;
}

//sym is already there, just change some stuff
//
int ASM_addSection(std::string section_name) {//FIRST
  //add the last section in symtab and fill the sym_lit_table, cant be done for
  // the 0th section
  printf("ASM_addSection: entry\n");
  if (asm_data.curr_section_symbol_index != 0) {  // 
    //fill the locations in the lit pool table

    //printf("ASM_addSection: if (asm_data.curr_section_symbol_index != 0)\n");
    int sctn_index = ASM_getCurrSectionVectorIndexInternal();
    int location_t = asm_data.location_cnt;
    //printf("ASM_addSection: if (asm_data.curr_section_symbol_index != 0), asm_data.sections[sctn_index].literal_pool_table.size():%ld\n", asm_data.sections[sctn_index].literal_pool_table.size());
    for (int i = 0; i < asm_data.sections[sctn_index].literal_pool_table.size(); i++) {
      asm_data.sections[sctn_index].literal_pool_table[i].location = location_t;
      //printf("ASM_addSection: lit_pool:asm_data.location_cnt:%#x)\n", asm_data.location_cnt);
      location_t += 4;
    }

    //fill the locations in the sym pool table
    /*
    printf("ASM_addSection: before sym_pool: asm_data.location_cnt:%#x)\n", asm_data.location_cnt);
    for (int i = 0; i < asm_data.sections[sctn_index].symbol_pool_table.size(); i++) {

      printf("ASM_addSection: sym_pool:asm_data.location_cnt:%#x)\n", asm_data.location_cnt);
      asm_data.sections[sctn_index].symbol_pool_table[i].location = asm_data.location_cnt;
      asm_data.location_cnt += 4;
    }*/
    // SYM POOL ONLY IN SECOND PASS

  // THIS SIZE IS WITHOUT ANY POOLS, THAT WILL BE ADDED IN SECOND PASS ONLY
    asm_data.symtab[asm_data.curr_section_symbol_index].size = asm_data.location_cnt;
    printf("add section\n");
    printf("section_size %d\n", asm_data.symtab[asm_data.curr_section_symbol_index].size);
  }

  //reset the counter, set the new curr_section_symbol_index
  asm_data.location_cnt = 0;
  asm_data.curr_section_symbol_index = asm_data.symtab.size() - 0;

  //add section to the symtab
  //SymTabEntry section_sym = {0, SYM_TYPE_SCTN, false, asm_data.curr_section_symbol_index, 0, section_name};
  //asm_data.symtab.push_back(section_sym);
  ASM_addSymbol(0, SYM_TYPE_SCTN, false, asm_data.curr_section_symbol_index, section_name);
  

  //FIRST PASS: create section content
  SctnContentASM sct;
  sct.section_index = asm_data.curr_section_symbol_index;
  asm_data.sections.push_back(sct);
  

  return 0;
}

int ASM_firstPassFinalize() {
  //printf("ASM_firstPassFinalize\n");
  asm_data.is_first_pass = false;

  int sctn_index = ASM_getCurrSectionVectorIndexInternal();
  int location_t = asm_data.location_cnt;
  for (int i = 0; i < asm_data.sections[sctn_index].literal_pool_table.size(); i++) {
    //printf("ASM_addSection:asm_data.location_cnt:%#x)\n", asm_data.location_cnt);
    asm_data.sections[sctn_index].literal_pool_table[i].location = location_t;
    location_t += 4;
  }
/*
  //fill the locations in the sym pool table
  for (int i = 0; i < asm_data.sections[sctn_index].symbol_pool_table.size(); i++) {
    asm_data.sections[sctn_index].symbol_pool_table[i].location = asm_data.location_cnt;
    asm_data.location_cnt += 4;
  }*/
  // SYM POOL ONLY IN SECOND PASS

  // THIS SIZE IS WITHOUT ANY POOLS, THAT WILL BE ADDED IN SECOND PASS ONLY
  asm_data.symtab[asm_data.curr_section_symbol_index].size = asm_data.location_cnt;
  printf("first pass finalize\n");
  printf("section_size %d\n", asm_data.symtab[asm_data.curr_section_symbol_index].size);

  asm_data.location_cnt = 0;
  asm_data.curr_section_symbol_index = 0;

  return 0;
}

int ASM_secondPassFinalize() {
  //printf("ASM_secondPassFinalize\n");
  int sctn_index = ASM_getCurrSectionVectorIndexInternal();
  for (uint i = 0; i < asm_data.sections[sctn_index].literal_pool_table.size(); i++) {
    //add value from location to bytes??
    int sym_lit_value = asm_data.sections[sctn_index].literal_pool_table[i].value;
    ASM_addByteToCurrSection((uint8_t) (sym_lit_value >> 0)  );
    ASM_addByteToCurrSection((uint8_t) (sym_lit_value >> 8)  );
    ASM_addByteToCurrSection((uint8_t) (sym_lit_value >> 16) );
    ASM_addByteToCurrSection((uint8_t) (sym_lit_value >> 24) );
    asm_data.location_cnt += 4;
  }
  for (uint i = 0; i < asm_data.sections[sctn_index].symbol_pool_table.size(); i++) {
      int sym_index = asm_data.sections[sctn_index].symbol_pool_table[i].symbol_index;
      ASM_addByteToCurrSection((uint8_t) (sym_index >> 0)  );
      ASM_addByteToCurrSection((uint8_t) (sym_index >> 8)  );
      ASM_addByteToCurrSection((uint8_t) (sym_index >> 16) );
      ASM_addByteToCurrSection((uint8_t) (sym_index >> 24) );
      asm_data.location_cnt += 4;
  }

  asm_data.symtab[asm_data.curr_section_symbol_index].size = asm_data.location_cnt;
  printf("second pass finalize\n");
  printf("section_size %d\n", asm_data.symtab[asm_data.curr_section_symbol_index].size);
  return 0;
}


int ASM_changeSection(string section_name) {
  
  //printf("ASM_changeSection\n");
  // create literal pool here in bytes vector for the section before section_name
  if (asm_data.curr_section_symbol_index != 0) {
    int sctn_index = ASM_getCurrSectionVectorIndexInternal();
    //fill the locations in the lit pool table
    for (uint i = 0; i < asm_data.sections[sctn_index].literal_pool_table.size(); i++) {
      //add value from location to bytes??
      int lit_pool_value = asm_data.sections[sctn_index].literal_pool_table[i].value;
      ASM_addByteToCurrSection((uint8_t) (lit_pool_value >> 0)  );
      ASM_addByteToCurrSection((uint8_t) (lit_pool_value >> 8)  );
      ASM_addByteToCurrSection((uint8_t) (lit_pool_value >> 16) );
      ASM_addByteToCurrSection((uint8_t) (lit_pool_value >> 24) );
      asm_data.location_cnt += 4;
    }

    //fill the locations in the sym pool table with zeroes, linker will patch this
    // for testing purposes fill it with sym indices/*
    
    for (uint i = 0; i < asm_data.sections[sctn_index].symbol_pool_table.size(); i++) {
      int sym_index = asm_data.sections[sctn_index].symbol_pool_table[i].symbol_index;
      ASM_addByteToCurrSection((uint8_t) (sym_index >> 0)  );
      ASM_addByteToCurrSection((uint8_t) (sym_index >> 8)  );
      ASM_addByteToCurrSection((uint8_t) (sym_index >> 16) );
      ASM_addByteToCurrSection((uint8_t) (sym_index >> 24) );
      asm_data.location_cnt += 4;
    }
    asm_data.symtab[asm_data.curr_section_symbol_index].size = asm_data.location_cnt;
    printf("change section\n");
    printf("section_size %d\n", asm_data.symtab[asm_data.curr_section_symbol_index].size);
    
  }

  //find the new section in symtab
  for (uint i = asm_data.curr_section_symbol_index; i < asm_data.symtab.size(); i++) {
    if (asm_data.symtab[i].type == SYM_TYPE_SCTN 
        && asm_data.symtab[i].name == section_name) {
      asm_data.curr_section_symbol_index = i;
      break;
    }
  }
  
  asm_data.location_cnt = 0;
  return 0;
}

int ASM_literalAddValueToPool(int literal_value) { //FIRST PASS
  //just add the value to the pool list

  //printf("ASM_literalAddValueToPool\n");
  //get curr section index with curr_section_symbol_index
  int sctn_index = ASM_getCurrSectionVectorIndexInternal();

  for (int i = 0; i < asm_data.sections[sctn_index].literal_pool_table.size(); i++) {
    if (asm_data.sections[sctn_index].literal_pool_table[i].value == literal_value)
      return 0;
  }
  LiteralPoolEntry sle = { literal_value, 0 };
  asm_data.sections[sctn_index].literal_pool_table.push_back(sle);
  return 0;
}

int ASM_literalGetLocationFromPool(int literal_value) { //get location from pool, SECOND

  //printf("ASM_literalGetLocationFromPool\n");
  int sctn_index = ASM_getCurrSectionVectorIndexInternal();

  for (int i = 0; i < asm_data.sections[sctn_index].literal_pool_table.size(); i++) {
    if (asm_data.sections[sctn_index].literal_pool_table[i].value == literal_value)
      return asm_data.sections[sctn_index].literal_pool_table[i].location - asm_data.location_cnt - 4;
  }

  return 0;
}

// SYMBOL POOL NEEDS TO BE ALL IN THE SECOND PASS
// this will never be called, move its functionality at the begging of ASM_symbolGetLocationFromPool
// also add ?????
int ASM_symbolAddValueToPool(string symbol_name) {//FRISTPASS

  //SymTabEntry symbol_temp;
  printf("ASM_symbolAddValueToPool symbol_name: %s\n", symbol_name.c_str());
  int symbol_num = 0;
  for (uint i = 0; i < asm_data.symtab.size(); i++) {
    printf("ASM_symbolAddValueToPool symtab[%d].name: %s\n", i, asm_data.symtab[i].name.c_str());
    if (symbol_name == asm_data.symtab[i].name) {
      //symbol_temp = asm_data.symtab[i];
      symbol_num = i;
      break;
    }
  }
  printf("ASM_symbolAddValueToPool symbol_num: %d\n", symbol_num);
  /*if (symbol_num == 0) {
    printf("\nASSEMBLER ERROR: symbol %s not defined\n", symbol_name.c_str());
    exit(1);
  }*/

  int sctn_index = ASM_getCurrSectionVectorIndexInternal();
/*
  for (int i = 0; i < asm_data.sections[sctn_index].symbol_pool_table.size(); i++) {
    if (asm_data.sections[sctn_index].symbol_pool_table[i].symbol_index == symbol_num) {

      printf("ASM_symbolAddValueToPool i: %d\n", i);
      return 0;
    }
  }*/

  

  SymbolPoolEntry sym_pool_entry = { symbol_num, 0 };
  asm_data.sections[sctn_index].symbol_pool_table.push_back(sym_pool_entry);
  return 0;

}

int ASM_symbolGetLocationFromPool(string symbol_name) {//SECONDPASS
  printf("\n****************\n");
  //get symbol and its index
  SymTabEntry symbol_t;
  int symbol_index_t = 0;
  for (uint i = 0; i < asm_data.symtab.size(); i++) {
    if (symbol_name == asm_data.symtab[i].name) {
      symbol_t = asm_data.symtab[i];
      symbol_index_t = i;
      break;
    }
  }
  if (symbol_index_t == 0) {
    printf("\nASSEMBLER ERROR: symbol %s not defined\n", symbol_name.c_str());
    //exit(1);
  }
  printf("symbol_index_t %d \n", symbol_index_t);

  //get the location in the pool
  int sctn_index = ASM_getCurrSectionVectorIndexInternal();

  printf("sctn_index %d \n", sctn_index);
  // Search the symbol_pool_table, maybe the sym is already in
  int location_t;
  int sym_pool_tab_ndx = 0;
  for (int i = 0; i < asm_data.sections[sctn_index].symbol_pool_table.size(); i++) {
    if (asm_data.sections[sctn_index].symbol_pool_table[i].symbol_index == symbol_index_t) {
      printf("Symbol found in sym_pool_table\n");
      location_t = asm_data.sections[sctn_index].symbol_pool_table[i].location;
      printf("location_t %d\n", location_t);
      return location_t - asm_data.location_cnt - 4;
      // maybe return here
    }
  }
  //printf("ASM_symbolGetLocationFromPool: location_t:%#x, %s)\n", location_t, symbol_name.c_str());

  // if you are here, symbol was not in the sym pool, so add it there
  //calculate location_t somehow
  printf("section_size %d\n", asm_data.symtab[asm_data.curr_section_symbol_index].size);
  printf("literal_pool_table.size %ld\n", asm_data.sections[sctn_index].literal_pool_table.size() * 4);
  printf("symbol_pool_table.size %ld\n", asm_data.sections[sctn_index].symbol_pool_table.size() * 4);

  location_t = asm_data.symtab[asm_data.curr_section_symbol_index].size
          + asm_data.sections[sctn_index].literal_pool_table.size() * 4
          + asm_data.sections[sctn_index].symbol_pool_table.size() * 4;

  printf("location_t %d\n", location_t);

  SymbolPoolEntry sym_pool_entry = { symbol_index_t, location_t };
  asm_data.sections[sctn_index].symbol_pool_table.push_back(sym_pool_entry);

  //make a rela entry
  RelaEntry rela_entry = { //tell the linker value in the pool
              location_t, //
              symbol_t.is_global ? symbol_index_t : symbol_t.section_index,
              symbol_t.is_global ? 0 : symbol_t.value,
              R_X86_64_32 
            };

  //add rela_entry to rela_table
  asm_data.sections[sctn_index].rela_table.push_back(rela_entry);

  return location_t - asm_data.location_cnt - 4;
}

int ASM_literalPoolCreate() {


  return 0;
}

int ASM_createOutputFileText(char output_file_name[]) {
  FILE *fp = fopen(output_file_name, "w");

  //shdr
  
  //symtab
  fprintf(fp, "#.symtab\n");
  fprintf(fp, "Num Val      Size Type  Bind Ndx Name\n");
  for (int i = 0; i < asm_data.symtab.size(); i++) {
    fprintf(fp, "%2d: ", i); 
    fprintf(fp, "%08x ", asm_data.symtab[i].value); 
    fprintf(fp, "%4d ", asm_data.symtab[i].size);

    if (asm_data.symtab[i].type == SYM_TYPE_SCTN)
      fprintf(fp, "%5s ", "SCTN");
    else
      fprintf(fp, "%5s ", "NOTYP");

    if (asm_data.symtab[i].is_global)
      fprintf(fp, "%4s ", "GLOB");
    else
      fprintf(fp, "%4s ", "LOC");

    fprintf(fp, "%3d ", asm_data.symtab[i].section_index); 
    fprintf(fp, "%-10s", asm_data.symtab[i].name.c_str());

    fprintf(fp, "\n");
  }

  //fprintf(fp, "\n");

  //sections
  for (int i = 0; i < asm_data.sections.size(); i++) {
    int section_sym_index = asm_data.sections[i].section_index;

    fprintf(fp, "\n");
    fprintf(fp, "#%s", asm_data.symtab[section_sym_index].name.c_str());
    //print bytes
    for (int j = 0; j < asm_data.sections[i].bytes.size(); j++) {
      if (j % 8 == 0)
        fprintf(fp, "\n%08x: ", j);
      fprintf(fp, "%02x ", asm_data.sections[i].bytes[j]);
      if (j % 8 == 3)
        fprintf(fp, " ");
      //if (j % 8 == 7)
        //fprintf(fp, "\n");
    }
    fprintf(fp, "\n");
  }

  //fprintf(fp, "\n");
  //rela tables
  for (int i = 0; i < asm_data.sections.size(); i++) {
    int section_sym_index = asm_data.sections[i].section_index;

    if (asm_data.sections[i].rela_table.size() == 0)
      continue;

    fprintf(fp, "\n");
    fprintf(fp, "#rela.%s\n", asm_data.symtab[section_sym_index].name.c_str());
    fprintf(fp, "Offset   Type        Symbol Addend\n");
    //print rela table
    for (int j = 0; j < asm_data.sections[i].rela_table.size(); j++) {
      fprintf(fp, "%08x ", asm_data.sections[i].rela_table[j].offset);
      if (asm_data.sections[i].rela_table[j].rela_type == R_X86_64_32)
        fprintf(fp, "%11s ", "R_X86_64_32");
      fprintf(fp, "%6d ", asm_data.sections[i].rela_table[j].symbol_index);
      fprintf(fp, "%6d ", asm_data.sections[i].rela_table[j].addend);

      fprintf(fp, "\n");
    }

  }

  fclose(fp);

  return 0;

}


int ASM_addByteToCurrSection(char byte) {
  int sctn_index = ASM_getCurrSectionVectorIndexInternal();

  asm_data.sections[sctn_index].bytes.push_back(byte);
  return 0;
}


int ASM_symbolAddToCurrRelaForAllocation(string symbol_name) {
  //find the symbol
  SymTabEntry symbol_temp;
  int symbol_num;
  for (uint i = 0; i < asm_data.symtab.size(); i++) {
    if (symbol_name == asm_data.symtab[i].name) {
      symbol_temp = asm_data.symtab[i];
      symbol_num = i;
      break;
    }
  }

  //make a rela entry
  //must decide on the addend, several cases
  //1. local -> addend = sym_val
  //2. global | extern -> 0;

  RelaEntry rela_entry = { 
              asm_data.location_cnt,
              symbol_temp.is_global ? symbol_num : symbol_temp.section_index,
              symbol_temp.is_global ? 0 : symbol_temp.value,
              R_X86_64_32 
            };

  //get current section content index
  int sctn_index = ASM_getCurrSectionVectorIndexInternal();

  //add rela_entry to rela_table
  asm_data.sections[sctn_index].rela_table.push_back(rela_entry);

  return 0;
}