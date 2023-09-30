#ifndef LINKER_H
#define LINKER_H

#include <string>
#include <vector>
#include <utility>
#include <map>
#include "../inc/data_types.h"
using namespace std;

struct LNK_SectionAddressMapping {
  uint file_num;
  uint sctn_vector_ndx;
  uint sctn_address;
};


struct LNK_Data { //first index is to reach data made from a specific file, second index is used to reach a specific section or rela entry of said file
  vector<vector<SymTabEntry>>     symtabs;
  vector<vector<SctnContentLNK>>  sections;

  vector<SymTabEntry>     combined_symtab;
  vector<SctnContentLNK>  combined_sections;

  //temporary vector used in LNK_readAndProcessObjectFile LNK_mapSectionAdresses
  vector<string>  section_names_for_mapping;
  map<string, int> global_sym_name_offset_map;

  //
  vector<pair<string, vector<LNK_SectionAddressMapping>>> section_address_mapping_vector;

};

struct LNK_PlaceCmd {
  string section_name;
  uint   adress;
};

void LNK_readAndProcessObjectFile(LNK_Data *lnk_data, FILE *input_file_handle);

void LNK_mapSectionAdresses(LNK_Data *lnk_data, vector<LNK_PlaceCmd> place_cmd_vector);

void LNK_updateSymtabs(LNK_Data *lnk_data);

void LNK_globalSymNameOffsetMapGenerate(LNK_Data *lnk_data);

void LNK_relaRecordsReslove(LNK_Data *lnk_data);


void LNK_createOutputHexFile(LNK_Data *lnk_data, FILE *output_file_handle);

#endif