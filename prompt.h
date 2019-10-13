#ifndef PROMPT_H
#define PROMPT_H
#include <iostream>
#include <string>
std::string Prompt(std::string message)
{
	std::cout << message << std::endl << "> ";
	std::string result;
	std::getline(std::cin, result);
	return result;
}
#endif