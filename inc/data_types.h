#ifndef DATA_TYPES_H
#define DATA_TYPES_H



#include <string>
#include <vector>
using namespace std;

typedef enum {
  SYM_TYPE_SCTN = 0,
  SYM_TYPE_NOTYP
} SymType;

struct SymTabEntry {
  int     value;
  SymType type;
  bool    is_global;
  int     section_index;
  int     size; // used only for sections

  string name;
};

struct LiteralPoolEntry {  //SEPARATE
  int value;
  int location;
};

struct SymbolPoolEntry {
  int symbol_index;
  int location;
};


typedef enum {
   R_X86_64_32
} RelaTypeE;

struct RelaEntry {
  int offset;
  int symbol_index;
  int addend;
  RelaTypeE rela_type;
};

struct SctnContentASM {
  int section_index;
  int section_size;
  vector<LiteralPoolEntry> literal_pool_table;
  vector<SymbolPoolEntry> symbol_pool_table;
  vector<uint8_t> bytes;

  vector<RelaEntry>  rela_table;
};

struct SctnContentLNK {
  int section_index;    
  string section_name;

  vector<uint8_t>   bytes;
  vector<RelaEntry> rela_records;
};



#endif