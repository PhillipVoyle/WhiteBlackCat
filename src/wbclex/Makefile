all: wbclex

clean:
	rm -f wbclex

wbclex: errorHandler.cpp lexerBase.cpp lexerGenerator.cpp lexigen_table.cpp main.cpp parserBase.cpp parserTable.cpp utils.cpp
	c++ -std=c++17 errorHandler.cpp lexerBase.cpp lexerGenerator.cpp lexigen_table.cpp main.cpp parserBase.cpp parserTable.cpp utils.cpp -o wbclex

lexigen_table.cpp: lexigen.wbclex
	../../bin/wbclex lexigen.wbclex

parserTable.cpp: parser.wbcparse
	../../bin/wbcparse parser.wbcparse

tables: lexigen_table.cpp parserTable.cpp

clean_tables:
	rm -f lexigen_table.cpp parserTable.cpp lexigen_table.h parserTable.h
	rm wbclex

