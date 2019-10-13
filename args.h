#ifndef ARGS_H
#define ARGS_H
#include <string>
#include <vector>
std::vector<std::string> GetArgs(int argc, char* argv[], bool inclusive = true)
{
	std::vector<std::string> args;
	if (inclusive)
	{
		args.push_back(argv[0]);
	}
	for (int i = 1; i < argc; i++)
	{
		args.push_back(argv[i]);
	}
	return args;
}
#endif