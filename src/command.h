#ifndef COMMAND_H
#define COMMAND_H

#include "base.h"
#include <vector>
#include <string>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>

class Command : public Base {
private:
	std::vector<char*> cmd;
public:

	int execute(){

		if(strcmp(cmd[0], "exit") == 0)
		{	
			exit(2);
		}	
		else
		{
			return execvp(cmd[0], &cmd[0]);
		}
};
		 
	void setArgs(std::vector<std::string> args) 
	{

		cmd.reserve(args.size());
		for(int i = 0; i < args.size(); i++)
		{
			if(args.at(i) == "\0")
			{
				cmd.push_back(NULL);
			}
			else
			{
				cmd.push_back(const_cast<char*>(args[i].c_str()));
			}
		} 
	}


};

class TestCommand : public Base {
private:
	std::vector<char*> cmd;
public:


	int execute()
	{
		if (strcmp(cmd[0], "test") == 0) // differentiate between "test filename" call and "[ filename ] " call
		{
			if (strcmp(cmd[1], "-f") == 0) // call testFunction with -f flag
			{
				if (testFunction(cmd[2], 1))
				{
					std::cout << "(True)" << std::endl;
					return 0;
				}
				else
				{
					std::cout << "(False)" << std::endl;
					return -1;
				}
			}
			else if (strcmp(cmd[1], "-d") == 0) // call testFunction with -d flag
			{	
				if (testFunction(cmd[2], 2))
				{
					std::cout << "(True)" << std::endl;
					return 0;
				}
				else
				{	
					std::cout << "(False)" << std::endl;
					return -1;
				}
			}	
			else if (strcmp(cmd[1], "-e") == 0) // call testFunction with -e flag
			{
				if (testFunction(cmd[2], 0))
				{
					std::cout << "(True)" << std::endl;
					return 0;
				}
				else
				{
					std::cout << "(False)" << std::endl;
					return -1;
				}
			}
			else	// default call to testFunction
			{
				if (testFunction(cmd[1], 0))
				{
					std::cout << "(True)" << std::endl;
					return 0;
				}
				else
				{	
					std::cout << "(False)" << std::endl;
					return -1;
				}
			}
		}
		else
		{

			if (strcmp(cmd[cmd.size() - 2], "]") == 0) // same as above, but with the [ filename ] being called
			{
				
				if (strcmp(cmd[1], "-f") == 0)
				{
					if (testFunction(cmd[2], 1))
					{
						std::cout << "(True)" << std::endl;
						return 0;
					}	
					else
					{
						std::cout << "(False)" << std::endl;
						return -1;
					}
				}
				else if (strcmp(cmd[1], "-d") == 0)
				{	
					if (testFunction(cmd[2], 2))
					{
						std::cout << "(True)" << std::endl;
						return 0;
					}
					else 
					{
						std::cout << "(False)" << std::endl;
						return -1;
					}
				}	
				else if (strcmp(cmd[1], "-e") == 0)
				{
					if (testFunction(cmd[2], 0))
					{
						std::cout << "(True)" << std::endl;
						return 0;
					}
					else
					{
						std::cout << "(False)" << std::endl;
						return -1;
					}
				}
				else
				{
					if (testFunction(cmd[1], 0))
					{
						std::cout << "(True)" << std::endl;
						return 0;
					}
					else
					{
						std::cout << "(False)" << std::endl;
						return -1;
					}
				}
			}
			else
			{
				return -1;	
			}
		}
		return 0;	
	}

	bool testFunction(char* path, int flag)
	{
		struct stat buf;
	
		if (flag == 0) // -e flag check
		{
			return (stat(path, &buf) == 0);
		}
		else if (flag == 1) // -f flag check
		{
			if (stat(path, &buf) == 0)
			{
				return (S_ISREG(buf.st_mode));
			}
			else
			{
				return false;
			}
		}
		else if (flag == 2)// -d flag check
		{
			if (stat(path, &buf) == 0)
			{
				return (S_ISDIR(buf.st_mode));
			}
			else
			{
				return false;
			}
		}
	}

	void setArgs(std::vector<std::string> args) 
	{

		cmd.reserve(args.size());
		for(int i = 0; i < args.size(); i++)
		{
			if(args.at(i) == "\0")
			{
				cmd.push_back(NULL);
			}
			else
			{
				cmd.push_back(const_cast<char*>(args[i].c_str()));
			}
		} 
	}

};

#endif
