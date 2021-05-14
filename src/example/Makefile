example: lexigen_table.cpp main.cpp LALRGenParserTable.cpp
	c++ -g --std=c++17 lexigen_table.cpp main.cpp LALRGenParserTable.cpp -o example

lexigen_table.cpp: calculator.wbclex
	../../bin/wbclex calculator.wbclex

LALRGenParserTable.cpp: calculator.wbcparse
	../../bin/wbcparse calculator.wbcparse

clean:
	rm -f example

clean_tables:
	rm -f lexigen_table.cpp LALRGenParserTable.cpp lexigen_table.h LALRGenParserTable.h lexigen.h LALRGenParser.h
	rm -f example
