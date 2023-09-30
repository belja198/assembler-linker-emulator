#ifndef EMULATOR_H
#define EMULATOR_H

#include <map>
#include <array>
using namespace std;

struct EMU_Inst {
  uint8_t bytes[4];
};

struct EMU_Data {
  map<uint32_t, uint8_t> address_data_map;
  uint gpr[16];
  uint csr[3];
  //?????? is this all
};

enum CsrIndex {
  STATUS = 0, HANDLER, CAUSE
};

enum GprIndex {
  R0 = 0, R1, R2, R3, R4, R5, R6, R7, R8, R9, R10, R11, R12, R13, SP = 14, PC = 15
};

void EMU_readAndProcessHexFile(EMU_Data *emu_data, FILE *input_file_handle);

void EMU_executeProgram(EMU_Data *emu_data);

void EMU_printResults(EMU_Data *emu_data);

#endif