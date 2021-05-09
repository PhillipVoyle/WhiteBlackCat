all: wbcparse

clean:
	rm -f wbcparse

wbcparse: errorHandler.cpp lalrGenerator.cpp lexerBase.cpp lexigen_table.cpp main.cpp parserBase.cpp parserTable.cpp production.cpp
	c++ -std=c++17 errorHandler.cpp lalrGenerator.cpp lexerBase.cpp lexigen_table.cpp main.cpp parserBase.cpp parserTable.cpp production.cpp -o wbcparse

lexigen_table.cpp: lexer.wbclex
	../../bin/wbclex lexer.wbclex

parserTable.cpp: parser.wbcparse
	../../bin/wbcparse parser.wbcparse

tables: lexigen_table.cpp parserTable.cpp

clean_tables:
	rm -f lexigen_table.cpp parserTable.cpp lexigen_table.h parserTable.h
	rm wbcparse
