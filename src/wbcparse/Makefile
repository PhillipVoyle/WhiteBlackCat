all: wbcparse

clean:
	rm wbcparse

wbcparse: errorHandler.cpp lalrGenerator.cpp lexerBase.cpp lexigen_table.cpp main.cpp parserBase.cpp parserTable.cpp production.cpp
	clang++ -std=c++0x errorHandler.cpp lalrGenerator.cpp lexerBase.cpp lexigen_table.cpp main.cpp parserBase.cpp parserTable.cpp production.cpp -o wbcparse
