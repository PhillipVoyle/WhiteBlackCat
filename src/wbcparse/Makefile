all: wbcparse

clean:
	rm -f wbcparse

wbcparse: errorHandler.cpp lalrGenerator.cpp lexerBase.cpp lexigen_table.cpp main.cpp parserBase.cpp parserTable.cpp production.cpp
	c++ -std=c++0x errorHandler.cpp lalrGenerator.cpp lexerBase.cpp lexigen_table.cpp main.cpp parserBase.cpp parserTable.cpp production.cpp -o wbcparse
