%{
  #include <stdio.h>
  #include <iostream>
  #include <string.h>
  #include <vector>
  #include "../inc/assembler.h"

  using namespace std;

  extern void yyrestart(FILE *input_file);

  extern int yylex();
  extern int yyparse();
  extern FILE *yyin;

  void yyerror(const char *s);

  char error_str[32];

  int asm_line = 1;

  vector<string> sym_name_list;
  int gpr_1, gpr_2;
  int csr;
  int pc_relative_disp;
  bool is_first_pass_aborted;

  uint8_t instruction[4];
  
%}
%define parse.error verbose

%union {
  unsigned int num;
  char* ident;
}

%token GLOBAL EXTERN SECTION WORD SKIP END
%token HALT INT IRET CALL RET JMP BEQ BNE BGT PUSH POP XCHG
%token ADD SUB MUL DIV NOT AND OR XOR SHL SHR LD ST
%token CSRRD CSRWR
%token REG STATUS HANDLER CAUSE
%token DOLLAR LEFTBRACKET RIGHTBRACKET PLUS COMMA COLON EOL

%token <num> NUMBER
%token <ident> IDENTIFIER

%type<num> literal;
%type<ident> symbol;

%start program

%%

program
  : line
  | program line
  ;

line
  : label operation end_of_line
  | label end_of_line
  | operation end_of_line
  | end_of_line
  ;

end_of_line 
  : EOL {
    //printf("%d: EOL, parser\n", asm_line);
    asm_line++;
    
  }
  ;

label
  : IDENTIFIER COLON {
      if (asm_data.is_first_pass)
        ASM_addSymbol(asm_data.location_cnt, SYM_TYPE_NOTYP, false,
                     asm_data.curr_section_symbol_index, $1);
      //printf("%d: LABEL: %s\n", asm_line, $1);
  }
  ;

operation
  : directive
  | instruction
  ;

directive
  : GLOBAL symbol_list {
      //SECOND PASS
      if (!asm_data.is_first_pass) {
        ASM_makeSymbolsGlobal(sym_name_list);  //only switch syms to global
        sym_name_list.clear(); //clear everytime symbol_list is used
      } else {
        ASM_declareSymbols(sym_name_list);
      }
      //printf("%d: GLOBAL\n", asm_line);
  }
  | EXTERN symbol_list {
      if (asm_data.is_first_pass) {
        ASM_declareSymbols(sym_name_list);
        sym_name_list.clear();
      }
      //printf("%d: EXTERN\n", asm_line);
  }
  | SECTION symbol {
      if (asm_data.is_first_pass)
        ASM_addSection($2);
      else
        ASM_changeSection($2);
      //printf("%d: SECTION\n", asm_line);
  }
  | WORD symbol_literal_list {
      
  }
  | SKIP literal {
      asm_data.location_cnt += $2;
      //SECOND PASS
      if (!asm_data.is_first_pass)
        for (int i = 0; i < $2; i++) 
          ASM_addByteToCurrSection(0x00);
  }
  | END {
      if (asm_data.is_first_pass)
        ASM_firstPassFinalize();
      else
        ASM_secondPassFinalize();
      YYACCEPT;
  }
  ;

instruction
  : no_op_inst
  | jmp_inst
  | one_reg_inst
  | two_reg_inst
  | two_reg_jmp_inst
  | LD ld_data_operand {
      asm_data.location_cnt += 4;
      //if (!asm_data.is_first_pass) {
        //ASM_addByteToCurrSection(instruction[0]);
        //ASM_addByteToCurrSection(instruction[1] | (uint8_t)(reg_t << 4));
        //ASM_addByteToCurrSection(instruction[2]);
        //ASM_addByteToCurrSection(instruction[3]);
      //}
      //printf("%d: LD\n", asm_line);
  }
  | ST one_reg COMMA st_data_operand {
      asm_data.location_cnt += 4;
      
      //printf("%d: ST\n", asm_line);
  }
  | CSRRD csr_reg COMMA one_reg {
      asm_data.location_cnt += 4;
      if (!asm_data.is_first_pass) {
        ASM_addByteToCurrSection(0x90);
        ASM_addByteToCurrSection(0x00 | (uint8_t)(gpr_1 << 4) | (uint8_t)csr);
        ASM_addByteToCurrSection(0x00);
        ASM_addByteToCurrSection(0x00);
      }
      
  }
  | CSRWR one_reg COMMA csr_reg {
      asm_data.location_cnt += 4;
      if (!asm_data.is_first_pass) {
        ASM_addByteToCurrSection(0x94);
        ASM_addByteToCurrSection(0x00 | (uint8_t)(gpr_1 << 0) | (uint8_t)(csr << 4));
        ASM_addByteToCurrSection(0x00);
        ASM_addByteToCurrSection(0x00);
      }
  }
  ;

csr_reg
  : STATUS {
      csr = 0;
  }
  | HANDLER {
      csr = 1;
  }
  | CAUSE {
      csr = 2;
  }
  ;

no_op_inst
  : HALT {
      asm_data.location_cnt += 4;
      if (!asm_data.is_first_pass) {
        ASM_addByteToCurrSection(0x00);
        ASM_addByteToCurrSection(0x00);
        ASM_addByteToCurrSection(0x00);
        ASM_addByteToCurrSection(0x00);
      }
  }
  | INT {
    //printf("%d: INT\n", asm_line);
    asm_data.location_cnt += 4;
    if (!asm_data.is_first_pass) {
      ASM_addByteToCurrSection(0x10);
      ASM_addByteToCurrSection(0x00);
      ASM_addByteToCurrSection(0x00);
      ASM_addByteToCurrSection(0x00);
    }
  }
  | IRET {
      if (!asm_data.is_first_pass) {
        ASM_addByteToCurrSection(0x96); //MMMM==0b0110: csr[A]<=mem32[gpr[B]+gpr[C]+D
        ASM_addByteToCurrSection(0x0E); // 0x0 == 0 == status, 0xE == 14 == SP
        ASM_addByteToCurrSection(0x00);  
        ASM_addByteToCurrSection(0x04); 

        ASM_addByteToCurrSection(0x93); //pop pc
        ASM_addByteToCurrSection(0xFE); // 0xF == 15 == PC, 0xE == 14 == SP
        ASM_addByteToCurrSection(0x00);  
        ASM_addByteToCurrSection(0x08); //move sp by 2 words because of status
      }
      asm_data.location_cnt += 4;
      asm_data.location_cnt += 4;
  }
  | RET {
      if (!asm_data.is_first_pass) {
        ASM_addByteToCurrSection(0x93); //pop pc
        ASM_addByteToCurrSection(0xFE); // 0xE == 15 == PC, 0xE == 14 == SP
        ASM_addByteToCurrSection(0x00);  
        ASM_addByteToCurrSection(0x04); 
      }
      asm_data.location_cnt += 4;
  }
  ;

jmp_inst
  : CALL adress_operand {
      asm_data.location_cnt += 4;
      if (!asm_data.is_first_pass) {
        ASM_addByteToCurrSection(0x21);
        ASM_addByteToCurrSection(0xF0); // 0xf == 15 == PC
        ASM_addByteToCurrSection(0x00 | (uint8_t)(pc_relative_disp >> 8));
        ASM_addByteToCurrSection(0x00 | (uint8_t)(pc_relative_disp & 0xFF) );
      }
  }
  | JMP adress_operand {
      asm_data.location_cnt += 4;
      // 0011 1000  0xF0  0x0+pc_relative_disp[] + pc_relative_disp[9..12] pc_relative_disp[0..8]
      if (!asm_data.is_first_pass) {
        ASM_addByteToCurrSection(0x38);
        ASM_addByteToCurrSection(0xF0); // 0xf == 15 == PC
        ASM_addByteToCurrSection(0x00 | (uint8_t)(pc_relative_disp >> 8));
        ASM_addByteToCurrSection(0x00 | (uint8_t)(pc_relative_disp & 0xFF) );
      }
      
  }
  ;

one_reg_inst
  : PUSH one_reg {  //OC==0b1000; MMMM==0b0001: gpr[A]<=gpr[A]+D; mem32[gpr[A]]<=gpr[C];
      asm_data.location_cnt += 4;
      if (!asm_data.is_first_pass) {
        ASM_addByteToCurrSection(0x81);
        ASM_addByteToCurrSection(0xE0); // 0xe == 14 == SP
        ASM_addByteToCurrSection(0x00 | (uint8_t)(gpr_1 << 4) | 0x0F);  //FFC
        ASM_addByteToCurrSection(0xFC); 
      }
  }
  | POP one_reg {
      asm_data.location_cnt += 4;
      if (!asm_data.is_first_pass) {
        ASM_addByteToCurrSection(0x93);
        ASM_addByteToCurrSection(0x00 | (uint8_t)(gpr_1 << 4) | 0x0E); // 0xe == 14 == SP
        ASM_addByteToCurrSection(0x00);  
        ASM_addByteToCurrSection(0x04); 
      }
  }
  | NOT one_reg {
      asm_data.location_cnt += 4;
      if (!asm_data.is_first_pass) {
        ASM_addByteToCurrSection(0x60);
        ASM_addByteToCurrSection(0x00 | (uint8_t)(gpr_1 << 4) | (uint8_t)gpr_1);
        ASM_addByteToCurrSection(0x00);
        ASM_addByteToCurrSection(0x00);
      }
  }
  ;

two_reg_inst
  : XCHG two_regs {
      asm_data.location_cnt += 4;
      if (!asm_data.is_first_pass) {
        ASM_addByteToCurrSection(0x40);
        ASM_addByteToCurrSection(0x00 | (uint8_t)gpr_2);
        ASM_addByteToCurrSection(0x00 | (uint8_t)(gpr_1 << 4));
        ASM_addByteToCurrSection(0x00);
      }
  }
  | ADD two_regs {
      asm_data.location_cnt += 4;
      if (!asm_data.is_first_pass) {
        ASM_addByteToCurrSection(0x50);
        ASM_addByteToCurrSection(0x00 | (uint8_t)(gpr_2 << 4) | (uint8_t)gpr_2);
        ASM_addByteToCurrSection(0x00 | (uint8_t)(gpr_1 << 4));
        ASM_addByteToCurrSection(0x00);
      }
  }
  | SUB two_regs {
      asm_data.location_cnt += 4;
      if (!asm_data.is_first_pass) {        
        ASM_addByteToCurrSection(0x51);
        ASM_addByteToCurrSection(0x00 | (uint8_t)(gpr_2 << 4) | (uint8_t)gpr_2);
        ASM_addByteToCurrSection(0x00 | (uint8_t)(gpr_1 << 4));
        ASM_addByteToCurrSection(0x00);
      }
  }
  | MUL two_regs {
      asm_data.location_cnt += 4;
      if (!asm_data.is_first_pass) {
        ASM_addByteToCurrSection(0x52);
        ASM_addByteToCurrSection(0x00 | (uint8_t)(gpr_2 << 4) | (uint8_t)gpr_2);
        ASM_addByteToCurrSection(0x00 | (uint8_t)(gpr_1 << 4));
        ASM_addByteToCurrSection(0x00);
      }
  }
  | DIV two_regs {
      asm_data.location_cnt += 4;
      if (!asm_data.is_first_pass) {
        ASM_addByteToCurrSection(0x53);
        ASM_addByteToCurrSection(0x00 | (uint8_t)(gpr_2 << 4) | (uint8_t)gpr_2);
        ASM_addByteToCurrSection(0x00 | (uint8_t)(gpr_1 << 4));
        ASM_addByteToCurrSection(0x00);
      }
  }
  | AND two_regs {
      asm_data.location_cnt += 4;
      if (!asm_data.is_first_pass) {
        ASM_addByteToCurrSection(0x61);
        ASM_addByteToCurrSection(0x00 | (uint8_t)(gpr_2 << 4) | (uint8_t)gpr_2);
        ASM_addByteToCurrSection(0x00 | (uint8_t)(gpr_1 << 4));
        ASM_addByteToCurrSection(0x00);
      }
  }
  | OR two_regs {
      asm_data.location_cnt += 4;
      if (!asm_data.is_first_pass) {
        ASM_addByteToCurrSection(0x62);
        ASM_addByteToCurrSection(0x00 | (uint8_t)(gpr_2 << 4) | (uint8_t)gpr_2);
        ASM_addByteToCurrSection(0x00 | (uint8_t)(gpr_1 << 4));
        ASM_addByteToCurrSection(0x00);
      }
  }
  | XOR two_regs {
      asm_data.location_cnt += 4;
      if (!asm_data.is_first_pass) {
        ASM_addByteToCurrSection(0x63);
        ASM_addByteToCurrSection(0x00 | (uint8_t)(gpr_2 << 4) | (uint8_t)gpr_2);
        ASM_addByteToCurrSection(0x00 | (uint8_t)(gpr_1 << 4));
        ASM_addByteToCurrSection(0x00);
      }
  }
  | SHL two_regs {
      asm_data.location_cnt += 4;
      if (!asm_data.is_first_pass) {
        ASM_addByteToCurrSection(0x70);
        ASM_addByteToCurrSection(0x00 | (uint8_t)(gpr_2 << 4) | (uint8_t)gpr_2);
        ASM_addByteToCurrSection(0x00 | (uint8_t)(gpr_1 << 4));
        ASM_addByteToCurrSection(0x00);
      }
  }
  | SHR two_regs {
      asm_data.location_cnt += 4;
      if (!asm_data.is_first_pass) {
        ASM_addByteToCurrSection(0x71);
        ASM_addByteToCurrSection(0x00 | (uint8_t)(gpr_2 << 4) | (uint8_t)gpr_2);
        ASM_addByteToCurrSection(0x00 | (uint8_t)(gpr_1 << 4));
        ASM_addByteToCurrSection(0x00);
      }
  }
  ;

one_reg
  : REG {
      gpr_1 = yylval.num;
  }
  ;


two_regs
  : one_reg COMMA REG {
      gpr_2 = yylval.num;
  }
  ;

two_reg_jmp_inst
  : BEQ two_regs COMMA adress_operand {
      asm_data.location_cnt += 4;
      if (!asm_data.is_first_pass) {
        ASM_addByteToCurrSection(0x39);
        ASM_addByteToCurrSection(0xF0 | (uint8_t)(gpr_1)); // 0xf == 15 == PC
        ASM_addByteToCurrSection(0x00 | (uint8_t)(gpr_2 << 4) | (uint8_t)(pc_relative_disp >> 8));
        ASM_addByteToCurrSection(0x00 | (uint8_t)(pc_relative_disp & 0xFF) );
      }
  }
  | BNE two_regs COMMA adress_operand {
      asm_data.location_cnt += 4;
      if (!asm_data.is_first_pass) {
        ASM_addByteToCurrSection(0x3A);
        ASM_addByteToCurrSection(0xF0 | (uint8_t)(gpr_1)); // 0xf == 15 == PC
        ASM_addByteToCurrSection(0x00 | (uint8_t)(gpr_2 << 4) | (uint8_t)(pc_relative_disp >> 8));
        ASM_addByteToCurrSection(0x00 | (uint8_t)(pc_relative_disp & 0xFF) );
      }
  }
  | BGT two_regs COMMA adress_operand {
      asm_data.location_cnt += 4;
      if (!asm_data.is_first_pass) {
        ASM_addByteToCurrSection(0x3B);
        ASM_addByteToCurrSection(0xF0 | (uint8_t)(gpr_1)); // 0xf == 15 == PC
        ASM_addByteToCurrSection(0x00 | (uint8_t)(gpr_2 << 4) | (uint8_t)(pc_relative_disp >> 8));
        ASM_addByteToCurrSection(0x00 | (uint8_t)(pc_relative_disp & 0xFF) );
      }
  }
  ;



adress_operand
  : literal {
      if (asm_data.is_first_pass) {
        ASM_literalAddValueToPool($1);
      } else {
        pc_relative_disp = ASM_literalGetLocationFromPool($1);  //
      }
  }
  | symbol {// add it to the pool, but also add rela record for that spot in the pool
      if (asm_data.is_first_pass) {
        //ASM_symbolAddValueToPool($1);
      } else {
        pc_relative_disp = ASM_symbolGetLocationFromPool($1);  //
      }
  }
  ;

ld_data_operand
  : DOLLAR literal COMMA REG {
      if (!asm_data.is_first_pass) {
        pc_relative_disp = ASM_literalGetLocationFromPool($2);
        uint gpr_t = yylval.num;
        ASM_addByteToCurrSection(0x92);
        ASM_addByteToCurrSection(0x0F | (uint8_t)(gpr_t << 4));
        ASM_addByteToCurrSection(0x00 | (uint8_t)(pc_relative_disp >> 8));
        ASM_addByteToCurrSection(0x00 | (uint8_t)(pc_relative_disp & 0xFF));
      } else {
        ASM_literalAddValueToPool($2);
      }

      //printf("%d: DOLLAR literal\n", asm_line);
  }
  | DOLLAR symbol COMMA REG {
      if (!asm_data.is_first_pass) {
        pc_relative_disp = ASM_symbolGetLocationFromPool($2);
        uint gpr_t = yylval.num;
        ASM_addByteToCurrSection(0x92);
        ASM_addByteToCurrSection(0x0F | (uint8_t)(gpr_t << 4));
        ASM_addByteToCurrSection(0x00 | (uint8_t)(pc_relative_disp >> 8));
        ASM_addByteToCurrSection(0x00 | (uint8_t)(pc_relative_disp & 0xFF));
      } else {
        //ASM_symbolAddValueToPool($2);
      }
      //printf("%d: DOLLAR symbol\n", asm_line);
  }
  | literal COMMA REG {
      if (!asm_data.is_first_pass) {
        pc_relative_disp = ASM_literalGetLocationFromPool($1);
        uint gpr_t = yylval.num;
        ASM_addByteToCurrSection(0x92);
        ASM_addByteToCurrSection(0x0F | (uint8_t)(gpr_t << 4));// f = pc
        ASM_addByteToCurrSection(0x00 | (uint8_t)(pc_relative_disp >> 8));
        ASM_addByteToCurrSection((uint8_t)(pc_relative_disp & 0xFF));

        ASM_addByteToCurrSection(0x92);
        ASM_addByteToCurrSection(0x00 | (uint8_t)(gpr_t << 4) | (uint8_t)(gpr_t << 0));
        ASM_addByteToCurrSection(0x00);
        ASM_addByteToCurrSection(0x00);
      } else {
        ASM_literalAddValueToPool($1);
      }
      asm_data.location_cnt += 4;
  }
  | symbol COMMA REG {
      if (!asm_data.is_first_pass) {
        pc_relative_disp = ASM_symbolGetLocationFromPool($1);
        uint gpr_t = yylval.num;
        ASM_addByteToCurrSection(0x92);
        ASM_addByteToCurrSection(0x0F | (uint8_t)(gpr_t << 4));// f = pc
        ASM_addByteToCurrSection(0x00 | (uint8_t)(pc_relative_disp >> 8));
        ASM_addByteToCurrSection((uint8_t)(pc_relative_disp & 0xFF));

        ASM_addByteToCurrSection(0x92);
        ASM_addByteToCurrSection(0x00 | (uint8_t)(gpr_t << 4) | (uint8_t)(gpr_t << 0));
        ASM_addByteToCurrSection(0x00);
        ASM_addByteToCurrSection(0x00);
      } else {
        //ASM_symbolAddValueToPool($1);
      }
      asm_data.location_cnt += 4;
  }
  | one_reg COMMA REG {
      if (!asm_data.is_first_pass) {
        uint gpr_t = yylval.num;  //load into this reg, gpr_1 was updated in one_reg
        ASM_addByteToCurrSection(0x91);
        ASM_addByteToCurrSection(0x00 | (uint8_t)(gpr_t << 4) | (uint8_t)(gpr_1 << 0));
        ASM_addByteToCurrSection(0x00);
        ASM_addByteToCurrSection(0x00);
      }
  }
  | LEFTBRACKET one_reg RIGHTBRACKET COMMA REG {
      if (!asm_data.is_first_pass) {
        uint gpr_t = yylval.num;
        ASM_addByteToCurrSection(0x92);
        ASM_addByteToCurrSection(0x00 | (uint8_t)(gpr_t << 4) | (uint8_t)(gpr_1 << 0));
        ASM_addByteToCurrSection(0x00);
        ASM_addByteToCurrSection(0x00);
      }
  }
  | LEFTBRACKET one_reg PLUS literal RIGHTBRACKET COMMA REG {//two machine inst
      //printf("%d: LEFTBRACKET REG PLUS literal RIGHTBRACKET\n", asm_line);
      if (!asm_data.is_first_pass) {
        pc_relative_disp = ASM_literalGetLocationFromPool($4);
        uint gpr_t = yylval.num;
        ASM_addByteToCurrSection(0x92); //load literal val from the pool to gpr_t
        ASM_addByteToCurrSection(0x0F | (uint8_t)(gpr_t << 4));// f = pc
        ASM_addByteToCurrSection(0x00 | (uint8_t)(pc_relative_disp >> 8));
        ASM_addByteToCurrSection((uint8_t)(pc_relative_disp & 0xFF));

        ASM_addByteToCurrSection(0x92); //use gpr_1 and gpr_t to load from mem to gpr_t
        ASM_addByteToCurrSection(0x00 | (uint8_t)(gpr_t << 4) | (uint8_t)(gpr_t << 0));//changed0x0F to 0x00
        ASM_addByteToCurrSection(0x00 | (uint8_t)(gpr_1 << 4));
        ASM_addByteToCurrSection(0x00);
      } else {
        int value = $4;
        if (!(value >= -2048 && value <= 2047)) {
          printf("ASM_ERROR %d: literal %#x in instruction type ld [%%gpr1 + literal], %%gpr2 must be 12 bit", asm_line, value);
          
          YYABORT;
        }
        ASM_literalAddValueToPool($4);
      }
      asm_data.location_cnt += 4;
  }
  /*| LEFTBRACKET one_reg PLUS symbol RIGHTBRACKET {
      //printf("%d: LEFTBRACKET REG PLUS literal RIGHTBRACKET\n", asm_line);
  }*/
  ; 
  
st_data_operand
  : literal {
      if (!asm_data.is_first_pass) {  //gpr_1 is the src
        pc_relative_disp = ASM_literalGetLocationFromPool($1);
        ASM_addByteToCurrSection(0x82);
        ASM_addByteToCurrSection(0x0F); // pc relative
        ASM_addByteToCurrSection(0x00 | (uint8_t)(gpr_1 << 4) | (uint8_t)(pc_relative_disp >> 8));
        ASM_addByteToCurrSection((uint8_t)(pc_relative_disp & 0xFF));
      } else {
        ASM_literalAddValueToPool($1);
      }
      //printf("%d: literal\n", asm_line);
  }
  | symbol {
      if (!asm_data.is_first_pass) {  //gpr_1 is the src
        pc_relative_disp = ASM_symbolGetLocationFromPool($1);
        ASM_addByteToCurrSection(0x82);
        ASM_addByteToCurrSection(0x0F); // pc relative
        ASM_addByteToCurrSection(0x00 | (uint8_t)(gpr_1 << 4) | (uint8_t)(pc_relative_disp >> 8));
        ASM_addByteToCurrSection((uint8_t)(pc_relative_disp & 0xFF));
      } else {
        //ASM_symbolAddValueToPool($1);//this will need to be removed
      }
      //printf("%d: literal\n", asm_line);
  }
  | LEFTBRACKET REG RIGHTBRACKET {
      if (!asm_data.is_first_pass) {
        uint gpr_t = yylval.num;
        ASM_addByteToCurrSection(0x80);
        ASM_addByteToCurrSection(0x00 | (uint8_t)(gpr_t << 4));
        ASM_addByteToCurrSection(0x00 | (uint8_t)(gpr_1 << 4));
        ASM_addByteToCurrSection(0x00);
      }
  }
  | LEFTBRACKET REG PLUS literal RIGHTBRACKET {
      if (!asm_data.is_first_pass) {
        pc_relative_disp = ASM_literalGetLocationFromPool($4);
        uint gpr_t = yylval.num;
        ASM_addByteToCurrSection(0x80);// maybe even here
        ASM_addByteToCurrSection(0x0F | (uint8_t)(gpr_t << 4)); // pc relative and gpr_t
        ASM_addByteToCurrSection(0x00 | (uint8_t)(gpr_1 << 4) | (uint8_t)(pc_relative_disp >> 8));
        ASM_addByteToCurrSection((uint8_t)(pc_relative_disp & 0xFF));
      } else {
        ASM_literalAddValueToPool($4);
      }
      //printf("%d: LEFTBRACKET REG PLUS literal RIGHTBRACKET\n", asm_line);
  }
  /*| LEFTBRACKET one_reg PLUS symbol RIGHTBRACKET {
      //printf("%d: LEFTBRACKET REG PLUS symbol RIGHTBRACKET\n", asm_line);
  }*/
  ;

literal
  : NUMBER
  ;

symbol
  : IDENTIFIER {
    if (asm_data.is_first_pass) {
      //ASM_addSymbol(0, SYM_TYPE_NOTYP, false, 0, $1);
    }
  }
  ;

symbol_list
  : symbol {
      //printf("%d: symbol: %s\n", asm_line, $1);
      sym_name_list.push_back($1);
  }
  | symbol_list COMMA symbol {
      //printf("%d: symbol_list COMMA symbol: %s\n", asm_line, $3);
      sym_name_list.push_back($3);
  }
  ;

symbol_literal_list
  : symbol {
      if (!asm_data.is_first_pass) { 
        ASM_symbolAddToCurrRelaForAllocation($1);
        ASM_addByteToCurrSection(0x00);
        ASM_addByteToCurrSection(0x00);
        ASM_addByteToCurrSection(0x00);
        ASM_addByteToCurrSection(0x00);
      }
      asm_data.location_cnt += 4;
  }
  | literal {
      if (!asm_data.is_first_pass) {
        unsigned int litValue = $1;
        ASM_addByteToCurrSection((uint8_t) (litValue >> 0 ));
        ASM_addByteToCurrSection((uint8_t) (litValue >> 8 ));
        ASM_addByteToCurrSection((uint8_t) (litValue >> 16));
        ASM_addByteToCurrSection((uint8_t) (litValue >> 24));
      }
      asm_data.location_cnt += 4;
  }
  | symbol_literal_list COMMA symbol {
      if (!asm_data.is_first_pass) { 
        ASM_symbolAddToCurrRelaForAllocation($3);
        ASM_addByteToCurrSection(0x00);
        ASM_addByteToCurrSection(0x00);
        ASM_addByteToCurrSection(0x00);
        ASM_addByteToCurrSection(0x00);
      }
      asm_data.location_cnt += 4;
  }
  | symbol_literal_list COMMA literal {
      if (!asm_data.is_first_pass) {
        unsigned int litValue = $3;
        ASM_addByteToCurrSection((uint8_t) (litValue >> 0 ));
        ASM_addByteToCurrSection((uint8_t) (litValue >> 8 ));
        ASM_addByteToCurrSection((uint8_t) (litValue >> 16));
        ASM_addByteToCurrSection((uint8_t) (litValue >> 24));
      }
      asm_data.location_cnt += 4;
  }
  ;

%%

int main(int argc, char** argv) {
  // open a file handle to a particular file:
  char file_name_in[64];
  strcpy(file_name_in, argv[3]);
  //FIRST PASS
  FILE *fp_in = fopen(file_name_in, "r");
  // make sure it's valid:
  if (!fp_in) {
    std::cout << "Can't open file!" << std::endl;
    return -1;
  }
  // Set flex to read from it instead of defaulting to STDIN:
  yyin = fp_in;
  ASM_addSymbol(0, SYM_TYPE_NOTYP, false, 0, "");
  // Parse through the input:
  do {
		yyparse();
	} while(!feof(yyin));

  //some asm functions

  fclose(fp_in);

  //SECOND PASS
  yyrestart(NULL);
  asm_line = 1;
  FILE *fp_in2 = fopen(file_name_in, "r");
  // make sure it's valid:
  if (!fp_in2) {
    printf("Can't open file!\n");
    return -1;
  }
  // Set flex to read from it instead of defaulting to STDIN:
  yyin = fp_in2;

  // Parse through the input:
  do {
		yyparse();
	} while(!feof(yyin));


  fclose(fp_in2);


  char file_name_out[64];
  strcpy(file_name_out, argv[2]);

  ASM_createOutputFileText(file_name_out);

  return 0;
}


void yyerror(const char *s) {
  std::cout << "EEK, parse error!  Message: " << s << ", at the line: " << asm_line <<std::endl;
  // might as well halt now:
  exit(-1);
}
