all: bin/wbclex bin/wbcparse

clean:
	$(MAKE) clean -C src/wbclex
	$(MAKE) clean -C src/wbcparse
	rm -f bin/*
	rm -f src/wbcparse/wbcparse
	rm -f src/wbclex/wbclex

src/wbclex/wbclex: src/wbclex/*.cpp src/wbclex/*.h
	$(MAKE) -C src/wbclex

bin/wbclex: src/wbclex/wbclex
	cp src/wbclex/wbclex bin

src/wbcparse/wbcparse: src/wbclex/*.cpp src/wbclex/*.h
	$(MAKE) -C src/wbcparse

bin/wbcparse: src/wbcparse/wbcparse
	cp src/wbcparse/wbcparse bin

clean_tables:
	$(MAKE) clean_tables -C src/wbclex
	$(MAKE) clean_tables -C src/wbcparse
