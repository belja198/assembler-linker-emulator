#ifndef ASSEMBLER_H
#define ASSEMBLER_H

#include <string>
#include <vector>
#include <map>
#include "../inc/data_types.h"
using namespace std;

//symbol pool, add symbols by their symbol number, everything else seems the same
//adding to symbol pool could return pc displacement and make a rela record at the same time
//maybe change literal pool, i dont know
//


struct ASM_data {
  vector<SymTabEntry>  symtab;
  vector<SctnContentASM>  sections;

  int curr_section_symbol_index;
  int location_cnt;
  
  bool is_first_pass = true;
};

int ASM_addSymbol(int val, SymType sym_type, bool is_global, int sctnNdx, string sybol_name);

//maybe be a specific func just for .extern
int ASM_declareSymbols(vector<string> sym_name_list);

int ASM_makeSymbolsGlobal(vector<string> sym_name_list);


int ASM_addSection(string section_name);

int ASM_createOutputFileText(char output_file_name[]);

int ASM_addByteToCurrSection(char byte);

int ASM_changeSection(string section_name);

int ASM_firstPassFinalize();

int ASM_literalAddValueToPool(int literal_value);

int ASM_literalGetLocationFromPool(int literal_value);

int ASM_symbolAddValueToPool(string symbol_name);//maybe change later

int ASM_symbolGetLocationFromPool(string symbol_name);//maybe change later

int ASM_secondPassFinalize();

int ASM_literalPoolCreate();

int ASM_symbolAddToCurrRelaForAllocation(string symbol_name);

extern ASM_data asm_data; 

#endif