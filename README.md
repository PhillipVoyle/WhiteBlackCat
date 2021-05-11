# WBC Compiler Tools
Some compiler tools written in C++, which generate type safe compiler parts in C++

## What is this?
WBC is a pair of tools that will emit a type safe parser and lexical analyser for your domain specific language. This project was initially written as an experiment to see if it would work, but is now functioning software

The software is in two parts, wbcparse, which generates a LALR parser, and wbclex which will generate a lexical
analyser for use with parsers generated using wbcparse

## Building

### POSIX
The project has recently been migrated to C++17 and so you will need a recent C++ compiler, and Make.

```
make
```

Once you have a working build of wbcparse and wbclex, it will also be possible to generate the parser and lexical
analyser tables using the `wbcparse` and `wbclex` executables.

### Windows

You're kind of on your own, but if you add all of the source files in each of the wbclex and wbcparse directories you should be able to get a reasonable result. Some assembly required

