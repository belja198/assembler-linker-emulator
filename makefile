all: assembler linker emulator

src/parser.cpp: misc/parser.y
	bison -v --defines=inc/parser.h --output=$(@) $(^)

src/lexer.cpp: misc/lexer.l 
	flex --outfile=$(@) $(^)

assembler: src/parser.cpp src/assembler.cpp src/lexer.cpp
	g++ -o $(@) $(^)

linker: src/linker.cpp
	g++ -o $(@) $(^)

emulator: src/emulator.cpp
	g++ -o $(@) $(^)

clean:
	rm -f src/parser.cpp src/parser.output inc/parser.h
	rm -f src/lexer.cpp
	rm -f assembler
	rm -f linker
	rm -f emulator