#include "../inc/emulator.h"
#include <stdint.h>
#include <string.h>
#include <limits.h>

int main(int argc, char **argv) {

  printf("line 8\n");
  char file_name_in[64];
  strcpy(file_name_in, argv[1]);
  printf("line 11: file_name_in: %s\n", file_name_in);
  EMU_Data emu_data;
  FILE *input_file_handle = fopen(file_name_in, "r");
  if (input_file_handle == NULL) {
    printf("Error opening file\n");
    return 1; // Return an error code
}
  printf("line 14\n");
  EMU_readAndProcessHexFile(&emu_data, input_file_handle);
  printf("line 16\n");
  EMU_executeProgram(&emu_data);

  EMU_printResults(&emu_data);


  return 0;
}

void EMU_printResults(EMU_Data *emu_data) {
  printf("Emulated processor state:\n");
  printf(" r0=0x%08x    r1=0x%08x    r2=0x%08x    r3=0x%08x\n", emu_data->gpr[R0], emu_data->gpr[R1], emu_data->gpr[R2], emu_data->gpr[R3]);
  printf(" r4=0x%08x    r5=0x%08x    r6=0x%08x    r7=0x%08x\n", emu_data->gpr[R4], emu_data->gpr[R5], emu_data->gpr[R6], emu_data->gpr[R7]);
  printf(" r8=0x%08x    r9=0x%08x   r10=0x%08x   r11=0x%08x\n", emu_data->gpr[R8], emu_data->gpr[R9], emu_data->gpr[R10], emu_data->gpr[R11]);
  printf("r12=0x%08x   r13=0x%08x   r14=0x%08x   r15=0x%08x\n", emu_data->gpr[R12], emu_data->gpr[R13], emu_data->gpr[SP], emu_data->gpr[PC]);

}

void EMU_pushInternal(EMU_Data *emu_data, uint value) {

  if (emu_data->gpr[SP] >= 4) {
    emu_data->gpr[SP] -= 4;
    emu_data->address_data_map[emu_data->gpr[SP] + 0] = (uint8_t)(value >> 0 );
    emu_data->address_data_map[emu_data->gpr[SP] + 1] = (uint8_t)(value >> 8 );
    emu_data->address_data_map[emu_data->gpr[SP] + 2] = (uint8_t)(value >> 16);
    emu_data->address_data_map[emu_data->gpr[SP] + 3] = (uint8_t)(value >> 24);
  } else {
    // Handle stack overflow
  }

}

uint EMU_popInternal(EMU_Data *emu_data) {
  uint result = 0;

  if (emu_data->gpr[SP] <= (UINT_MAX - 4)) {    
    result |= (uint)emu_data->address_data_map[emu_data->gpr[SP] + 0] << 0 ;
    result |= (uint)emu_data->address_data_map[emu_data->gpr[SP] + 1] << 8 ;
    result |= (uint)emu_data->address_data_map[emu_data->gpr[SP] + 2] << 16;
    result |= (uint)emu_data->address_data_map[emu_data->gpr[SP] + 3] << 24;
    emu_data->gpr[SP] += 4;
  } else {
    // Handle stack underflow
  }

  return result;
}

// 4 bytes little endian
uint EMU_readMemory(EMU_Data *emu_data, uint gprA, uint gprB, uint gprC, int disp) {
  uint result = 0;

  printf("\nEMU_readMemory gprA: %08x, gprB: %08x, gprC: %08x, disp(hex): %08x,\n", gprA, gprB, gprC, disp);
  printf("\nEMU_readMemory result_addr %08x\n", gprA + gprB + gprC + disp + 0);

  if (disp >= 0) {
    result |= (uint)emu_data->address_data_map[gprA + gprB + gprC + disp + 0] << 0 ;

  printf("\nEMU_readMemory result: %08x\n", result);
    result |= (uint)emu_data->address_data_map[gprA + gprB + gprC + disp + 1] << 8 ;

  printf("\nEMU_readMemory result: %08x\n", result);
    result |= (uint)emu_data->address_data_map[gprA + gprB + gprC + disp + 2] << 16;

  printf("\nEMU_readMemory result: %08x\n", result);
    result |= (uint)emu_data->address_data_map[gprA + gprB + gprC + disp + 3] << 24;

  printf("\nEMU_readMemory result: %08x\n", result);
  } else {
    disp = -disp;
    result |= (uint)emu_data->address_data_map[gprA + gprB + gprC - disp + 0] << 0 ;
    result |= (uint)emu_data->address_data_map[gprA + gprB + gprC - disp + 1] << 8 ;
    result |= (uint)emu_data->address_data_map[gprA + gprB + gprC - disp + 2] << 16;
    result |= (uint)emu_data->address_data_map[gprA + gprB + gprC - disp + 3] << 24;
  }

  printf("\nEMU_readMemory result: %08x\n", result);

  return result;
}

void EMU_writeMemory(EMU_Data *emu_data, uint gprA, uint gprB, uint gprC, int disp) {

  if (disp >= 0) {
    emu_data->address_data_map[gprA + gprB + disp + 0] = (uint8_t)(gprC >> 0 );
    emu_data->address_data_map[gprA + gprB + disp + 1] = (uint8_t)(gprC >> 8 );
    emu_data->address_data_map[gprA + gprB + disp + 2] = (uint8_t)(gprC >> 16);
    emu_data->address_data_map[gprA + gprB + disp + 3] = (uint8_t)(gprC >> 24);
  } else {
    disp = -disp;
    emu_data->address_data_map[gprA + gprB - disp + 0] = (uint8_t)(gprC >> 0 );
    emu_data->address_data_map[gprA + gprB - disp + 1] = (uint8_t)(gprC >> 8 );
    emu_data->address_data_map[gprA + gprB - disp + 2] = (uint8_t)(gprC >> 16);
    emu_data->address_data_map[gprA + gprB - disp + 3] = (uint8_t)(gprC >> 24);    
  }

}


void EMU_executeProgram(EMU_Data *emu_data) {
  // initialize data
  for (uint i = 0; i < 16; i++) {
    emu_data->gpr[i] = 0;
  }
  emu_data->gpr[PC] = 0x40000000; //PC

  for (uint i = 0; i < 3; i++) {
    emu_data->csr[i] = 0;
  }

  // check if is there something at pc starting address

  if (emu_data->address_data_map.count(0x40000000) != 1) {
    //ERROR
    printf("EMU ERROR: no instruction found at 0x40000000 (PC starting address)\n");
  }

  bool is_program_halted = false;


  while (!is_program_halted) {
    uint8_t instruction[4];
    printf("\n----------------------------------------------------------------\n");
    EMU_printResults(emu_data);

    // OC MOD
    instruction[0] = emu_data->address_data_map[emu_data->gpr[PC]++];
    uint8_t OC =  instruction[0] >> 4;
    uint8_t MOD = instruction[0] & 0x0F;
    printf("OC:MOD: %02x ", instruction[0]);
    // regA regB
    instruction[1] = emu_data->address_data_map[emu_data->gpr[PC]++];
    uint8_t rA = instruction[1] >> 4;
    uint8_t rB = instruction[1] & 0x0F;

    printf(", rA:rB: %02x ", instruction[1]);
    // regC disp
    instruction[2] = emu_data->address_data_map[emu_data->gpr[PC]++];
    uint8_t rC =  instruction[2] >> 4;

    printf(", rC: %02x ", rC);
   // uint8_t MOD = instruction[2] & 0x0F;
    // disp disp
    instruction[3] = emu_data->address_data_map[emu_data->gpr[PC]++];

    uint disp_value = (instruction[2] & 0x0F) << 8 | instruction[3];

    int disp = disp_value;
    if (disp & 0x800) {
      disp |= 0xFFFFF000; // Sign extend the lower 12 bits
    }
    printf(" , disp hexa: %x ", disp);
    printf(" , disp: %d\n", disp);

    uint temp;


    switch (instruction[0])
    {
    case 0x00:  //halt
      is_program_halted = true;
      printf("\n----------------------------------------------------------------\n");
      printf("\nEmulated processor executed halt instruction\n");
      break;

    case 0x10:  //int
      //push status;
      EMU_pushInternal(emu_data, emu_data->csr[STATUS]);
      //push pc;
      EMU_pushInternal(emu_data, emu_data->gpr[PC]);
      //cause<=4; 
      emu_data->csr[CAUSE] = 4;
      //status<=status&(~0x1);
      emu_data->csr[STATUS] &= ~0x1;
      //pc<=handle;
      emu_data->gpr[PC] = emu_data->csr[HANDLER];
      break;

    case 0x21:  //call
      // push pc;
      EMU_pushInternal(emu_data, emu_data->gpr[PC]);
      // pc<=mem32[gpr[A]+gpr[B]+D];
      //emu_data->gpr[PC] = emu_data->address_data_map[emu_data->gpr[rA] + emu_data->gpr[rB] + disp];
      emu_data->gpr[PC] = EMU_readMemory(emu_data, emu_data->gpr[rA], emu_data->gpr[rB], 0, disp);
      break;

    case 0x38:  //jmp
      // pc<=mem32[gpr[A]+D];
      //emu_data->gpr[PC] = emu_data->address_data_map[emu_data->gpr[rA] + disp];
      emu_data->gpr[PC] = EMU_readMemory(emu_data, emu_data->gpr[rA], 0, 0, disp);
      break;

    case 0x39:  //beq
      // if (gpr[B] == gpr[C]) pc<=mem32[gpr[A]+D];
      if (emu_data->gpr[rB] == emu_data->gpr[rC])
        emu_data->gpr[PC] = EMU_readMemory(emu_data, emu_data->gpr[rA], 0, 0, disp);
      break;

    case 0x3A:  //bne
      // if (gpr[B] != gpr[C]) pc<=mem32[gpr[A]+D]; 
      if (emu_data->gpr[rB] != emu_data->gpr[rC])
        emu_data->gpr[PC] = EMU_readMemory(emu_data, emu_data->gpr[rA], 0, 0, disp);
      break;

    case 0x3B:  //bgt
      if ((int)emu_data->gpr[rB] > (int)emu_data->gpr[rC])
        emu_data->gpr[PC] = EMU_readMemory(emu_data, emu_data->gpr[rA], 0, 0, disp);
      break;
    
    case 0x40:  //xchg
      // temp<=gpr[B]; 
      temp = emu_data->gpr[rB];
      // gpr[B]<=gpr[C];
      emu_data->gpr[rB] = emu_data->gpr[rC];
      // gpr[C]<=temp;
      emu_data->gpr[rC] = temp;
      break;

    case 0x50:  //add
      // gpr[A]<=gpr[B] + gpr[C]; 
      emu_data->gpr[rA] = emu_data->gpr[rB] + emu_data->gpr[rC]; 
      break;

    case 0x51:  //sub
      // gpr[A]<=gpr[B] - gpr[C];
      emu_data->gpr[rA] = emu_data->gpr[rB] - emu_data->gpr[rC]; 
      break;

    case 0x52:  //mul
      // gpr[A]<=gpr[B] * gpr[C];
      emu_data->gpr[rA] = emu_data->gpr[rB] * emu_data->gpr[rC]; 
      break;

    case 0x53:  //div
      // gpr[A]<=gpr[B] / gpr[C];
      emu_data->gpr[rA] = emu_data->gpr[rB] / emu_data->gpr[rC]; 
      break;

    case 0x60:  //not
      // gpr[A]<=~gpr[B];  
      emu_data->gpr[rA] = ~ emu_data->gpr[rB]; 
      break;    

    case 0x61:  //and
      // gpr[A]<=gpr[B] & gpr[C];
      emu_data->gpr[rA] = emu_data->gpr[rB] & emu_data->gpr[rC]; 
      break;  

    case 0x62:  //or
      // gpr[A]<=gpr[B] | gpr[C];
      emu_data->gpr[rA] = emu_data->gpr[rB] | emu_data->gpr[rC]; 
      break;

    case 0x63:  //xor
      // gpr[A]<=gpr[B] ^ gpr[C];
      emu_data->gpr[rA] = emu_data->gpr[rB] ^ emu_data->gpr[rC]; 
      break;

    case 0x70:  //shl
      // gpr[A]<=gpr[B] << gpr[C];
      emu_data->gpr[rA] = emu_data->gpr[rB] << emu_data->gpr[rC]; 
      break;

    case 0x71:  //shr
      // gpr[A]<=gpr[B] >> gpr[C];
      emu_data->gpr[rA] = emu_data->gpr[rB] >> emu_data->gpr[rC]; 
      break;

    case 0x80:  //st direct   //
      // mem32[gpr[A]+gpr[B]+D]<=gpr[C];
      //emu_data->address_data_map[emu_data->gpr[rA] + emu_data->gpr[rB] + disp] = emu_data->gpr[rC];
      EMU_writeMemory(emu_data, emu_data->gpr[rA], emu_data->gpr[rB], emu_data->gpr[rC], disp);
      break;

    case 0x82:  //st indirect
      // mem32[mem32[gpr[A]+gpr[B]+D]]<=gpr[C]; 
      temp = EMU_readMemory(emu_data, emu_data->gpr[rA], emu_data->gpr[rB], 0, disp);
      EMU_writeMemory(emu_data, temp, 0, emu_data->gpr[rC], 0);
      break;

    case 0x91:  //ld reg 
      // gpr[A]<=gpr[B]+D; 
      emu_data->gpr[rA] = emu_data->gpr[rB] + disp;
      break;

    case 0x92:  //ld mem  //
      // gpr[A]<=mem32[gpr[B]+gpr[C]+D]; 
      //emu_data->gpr[rA] = emu_data->address_data_map[emu_data->gpr[rB] + emu_data->gpr[rC] + disp];
      emu_data->gpr[rA] = EMU_readMemory(emu_data, 0, emu_data->gpr[rB], emu_data->gpr[rC], disp);
      break;

    case 0x90:  //csrrd
      // gpr[A]<=csr[B]; 
      emu_data->gpr[rA] = emu_data->csr[rB];
      break;

    case 0x94:  //csrrd
      // csr[A]<=gpr[B];
      emu_data->csr[rA] = emu_data->gpr[rB];
      break;

    case 0x81:  //push
      // gpr[A]<=gpr[A]+D;
      if (disp >= 0) {
        printf("push disp >= 0 : %d\n", disp);
        emu_data->gpr[rA] = emu_data->gpr[rA] + disp;
      } else {
        printf("push disp < 0 : %d\n", disp);
        disp = -disp;
        emu_data->gpr[rA] = emu_data->gpr[rA] - disp;
        printf("push disp < 0 emu_data->gpr[rA] : %08x\n", emu_data->gpr[rA] );
      }
      // mem32[gpr[A]]<=gpr[C];
      EMU_writeMemory(emu_data, emu_data->gpr[rA], 0, emu_data->gpr[rC], 0);
      break;

    case 0x93:  //pop & ret & iret second part
      // gpr[A]<=mem32[gpr[B]];
      emu_data->gpr[rA] = EMU_readMemory(emu_data, 0, emu_data->gpr[rB], 0, 0);
      // gpr[B]<=gpr[B]+D;
      if (disp >= 0) {
        emu_data->gpr[rB] = emu_data->gpr[rB] + disp;
      } else {
        disp = -disp;
        emu_data->gpr[rB] = emu_data->gpr[rB] - disp;
      }
      break;

    case 0x96:  //iret first part
      // csr[A]<=mem32[gpr[B]+gpr[C]+D];
      emu_data->csr[rA] = EMU_readMemory(emu_data, 0, emu_data->gpr[rB], emu_data->gpr[rC], 0);
      break;

    default:
      //maybe some error
      break;
    }

  }

}


void EMU_readAndProcessHexFile(EMU_Data *emu_data, FILE *input_file_handle) {
  char line[64];

  uint address;
  uint8_t bytes[8];
  fgets(line, sizeof(line), input_file_handle);
  while(fgets(line, sizeof(line), input_file_handle)) {


    int num_conversions = sscanf(line, "%x: %hhx %hhx %hhx %hhx  %hhx %hhx %hhx %hhx",
                 &address, &bytes[0], &bytes[1], &bytes[2], &bytes[3], &bytes[4], &bytes[5], &bytes[6], &bytes[7]);

    printf("num_conversions %d\n", num_conversions);
    printf("%#08x: %02x %02x %02x %02x %02x %02x %02x %02x\n", 
                address, bytes[0], bytes[1], bytes[2], bytes[3], bytes[4], bytes[5], bytes[6], bytes[7]);

    for (uint i = 0; i < num_conversions - 1; i++) {
      emu_data->address_data_map[address++] = bytes[i];
    }


  }

int count = 0;
for (const auto& entry : emu_data->address_data_map) {
    printf("Address: %#08x, Data: %#02x  ", entry.first, entry.second);
    count++;
    if (count == 4) {
        printf("\n");
        count = 0;
    }
}
}