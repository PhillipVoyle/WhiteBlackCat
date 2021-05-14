all: bin/wbclex bin/wbcparse bin/example

clean:
	$(MAKE) clean -C src/wbclex
	$(MAKE) clean -C src/wbcparse
	$(MAKE) clean -C src/example
	rm -f bin/*
	rm -f src/wbcparse/wbcparse
	rm -f src/wbclex/wbclex
	rm -f src/example/example


src/wbclex/wbclex: src/wbclex/*.cpp src/wbclex/*.h src/wbclex/*.wbclex src/wbclex/*.wbcparse
	$(MAKE) -C src/wbclex

bin/wbclex: src/wbclex/wbclex
	cp src/wbclex/wbclex bin

src/wbcparse/wbcparse: src/wbcparse/*.cpp src/wbcparse/*.h src/wbcparse/*.wbclex src/wbcparse/*.wbcparse
	$(MAKE) -C src/wbcparse

bin/wbcparse: src/wbcparse/wbcparse
	cp src/wbcparse/wbcparse bin

src/example/example: src/example/*.cpp src/example/*.h src/example/*.wbclex src/example/*.wbcparse
	$(MAKE) -C src/example

bin/example: src/example/example
	cp src/example/example bin

clean_tables:
	$(MAKE) clean_tables -C src/wbclex
	$(MAKE) clean_tables -C src/wbcparse
	$(MAKE) clean_tables -C src/example
