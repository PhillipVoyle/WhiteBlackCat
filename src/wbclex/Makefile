all: wbclex

clean:
	rm wbclex

wbclex: errorHandler.cpp lexerBase.cpp lexerGenerator.cpp lexigen_table.cpp main.cpp parserBase.cpp parserTable.cpp utils.cpp
	c++ -std=c++0x errorHandler.cpp lexerBase.cpp lexerGenerator.cpp lexigen_table.cpp main.cpp parserBase.cpp	parserTable.cpp utils.cpp -o wbclex


