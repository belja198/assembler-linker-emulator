%{
  #include <stdio.h>
  #include <string>
  #include <iostream>
  #include "../inc/parser.h"

  extern int asm_line;

%}

%option noyywrap

digit       [0-9]
hex_digit   [0-9a-fA-F]
letter      [a-zA-Z]


%%

.global   { return GLOBAL;  }
.extern   { return EXTERN;  }
.section  { return SECTION; }
.word     { return WORD;    }
.skip     { return SKIP;    }
.end      { return END;     }

halt  { return HALT; }
int   { return INT;  }
iret  { return IRET; }
call  { return CALL; }
ret   { return RET;  }
jmp   { return JMP;  }
beq   { return BEQ;  }
bne   { return BNE;  }
bgt   { return BGT;  }
push  { return PUSH; }
pop   { return POP;  }
xchg  { return XCHG; }

add   { return ADD;  }
sub   { return SUB;  }
mul   { return MUL;  }
div   { return DIV;  }
not   { return NOT;  }
and   { return AND;  }
or    { return OR;   }
xor   { return XOR;  }
shl   { return SHL;  }
shr   { return SHR;  }
ld    { return LD;   }
st    { return ST;   }

csrrd { return CSRRD; }
csrwr { return CSRWR; }

\%r([1-9]|1[0-5])  { yylval.num = atoi(yytext + 2); return REG;} 
\%sp { yylval.num = 14; return REG; }
\%pc { yylval.num = 15; return REG; }

\%status  { return STATUS;  } 
\%handler { return HANDLER; } 
\%cause   { return CAUSE;   }

\$ { return DOLLAR;  }

\[ { return LEFTBRACKET;  }
\] { return RIGHTBRACKET; }
\+ { return PLUS;  }
\, { return COMMA; }
\: { return COLON; }

{digit}+  { yylval.num = (uint)atoi(yytext); return NUMBER; }

0x{hex_digit}{1,8} { 
  unsigned long temp = std::stoul(yytext + 2, nullptr, 16); 
  yylval.num = temp;
  //printf(" %x \n", yylval.num);
  return NUMBER; 
  }

({letter}|_)({letter}|{digit}|_)* { yylval.ident = strdup(yytext); return IDENTIFIER; }

\n    { 
        //printf("%d: EOL, lexer\n", asm_line);
        return EOL; 
      }

#.*\n { 
        //printf("%d: EOL comment, lexer\n", asm_line);
        return EOL; 
      }
[ \t \r \f] { }



%%
