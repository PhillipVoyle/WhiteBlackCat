#include <fstream>
#include <iostream>

#include "lexerBase.h"
#include "errorHandler.h"
 
int main(int argc, const char* argv[])
{
	if(argc == 2)
	{
		std::ifstream fin(argv[1]);
		if(!fin)
		{
			std::cerr << "error: could not open file \"" << argv[1] << "\"" << std::endl;
			return -1;
		}
		else
		{
			CErrorHandler errorHandler;
			errorHandler.SetFilename(argv[1]);
			CLexer<CLexerBase> lexer;
			lexer.SetErrorHandler(&errorHandler);
			lexer.scan(fin);
			if(errorHandler.Ok())
			{
				return 0;
			}
			else
			{
				return -1;
			}
		}
	}
	std::cerr << "usage:\n";
	std::cerr << " wbcparse inputFile.wbcparse\n";
	return -1;
}
