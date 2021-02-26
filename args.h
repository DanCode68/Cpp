#ifndef ARGS_H
#define ARGS_H

#include <string>
#include <vector>
#include <map>
#include <regex>

std::vector<std::string> ReadArgs(int argc, char* argv[], bool inclusive = false)
{
	std::vector<std::string> args;
	if (inclusive)
	{
		args.push_back(argv[0]);
	}
	for (int i = 1; i < argc; ++i)
	{
		args.push_back(argv[i]);
	}
	return args;
}

std::map<std::string, std::string> ReadParams(std::vector<std::string> args)
{
	std::map<std::string, std::string> params;
	std::string key, value;
	int start, end;
	std::regex r("(-)(.*)(=)(.*)");
	for (int i = 0; i < args.size(); ++i)
	{
		if (regex_match(args[i], r))
		{
			start = args[i].find("-") + 1;
			end = args[i].find_last_of("=");
			#ifdef CASE_H
				key = ToLower(args[i].substr(start, end - start));
				value = ToLower(args[i].substr(args[i].find_last_of("=") + 1));
			#else
				key = args[i].substr(start, end - start);
				value = args[i].substr(args[i].find_last_of("=") + 1);
			#endif
			params[key] = value;
		}
	}
	return params;
}

std::map<std::string, std::string> ReadParams(int argc, char* argv[])
{
	return ReadParams(ReadArgs(argc, argv, false));
}

class Args
{
	public:
		Args(int argc, char* argv[], bool inclusive = false)
		{
			args = ReadArgs(argc, argv, inclusive);
			params = ReadParams(args);
			FixParams();
		}

		bool HasArg(std::string s)
		{
			#ifdef CASE_H
				for (std::string arg : args)
				{
					if (ToLower(arg) == ToLower(s))
					{
						return true;
					}
				}
				return false;
			#else
				for (std::string arg : args)
				{
					if (arg == s)
					{
						return true;
					}
				}
				return false;
			#endif
		}

		std::string GetArg(unsigned int index)
		{
			if (index < args.size())
			{
				return args[index];
			}
			return "";
		}

		std::vector<std::string> GetArgs()
		{
			return args;
		}

		std::string GetArgsString(bool newLines = true)
		{
			std::string result = "";
			for (std::string& s : args)
			{
				result += s;
				if (newLines)
				{
					result += "\n";
				}
				else
				{
					result += " ";
				}
			}
			return result;
		}

		bool HasParam(std::string key)
		{
			#ifdef CASE_H
				return ToLower(params[key]) != "";
			#else
				return params[key] != "";
			#endif
		}

		std::string GetParam(std::string key)
		{
			#ifdef CASE_H
				return ToLower(params[key]);
			#else
				return params[key];
			#endif
		}

		std::map<std::string, std::string> GetParams()
		{
			return params;
		}

		std::string GetParamsString(bool newLines = true)
		{
			std::string result = "";
			for (std::map<std::string, std::string>::const_iterator it = params.begin(); it != params.end(); ++it)
			{
				result += it->first + " = " + GetParam(it->first);
				if (newLines)
				{
					result += "\n";
				}
				else
				{
					result += " ";
				}
			}
			return result;
		}
	
	private:
		std::vector<std::string> args;
		std::map<std::string, std::string> params;

		void FixParams()
		{
			for (std::map<std::string, std::string>::const_iterator it = params.begin(); it != params.end(); ++it)
			{
				if (it->second == "")
				{
					params[it->first] = "0";
				}
			}
		}
};

#endif