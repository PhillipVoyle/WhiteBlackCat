#include <fstream>

#include "lexerBase.h"
#include "errorHandler.h"
 
int main(int argc, const char* argv[])
{
	CErrorHandler errorHandler;
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
			CLexer<CLexerBase> lexer;
			errorHandler.SetFilename(argv[1]);
			lexer.SetErrorHandler(&errorHandler);
			lexer.scan(fin);
			return 0;
		}
	}
	std::cerr << "usage:\n";
	std::cerr << " wbclex inputFile.wbclex\n";
	return -1;
}