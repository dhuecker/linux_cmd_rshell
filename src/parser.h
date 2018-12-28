#ifndef PARSE_H
#define PARSE_H

#include <boost/tokenizer.hpp>
#include <vector>
#include <string.h>

class Parse {
public:
	std::string str; // string to be parsed
	std::vector<std::string> args;	// vector of commands and arguements
	std::vector<int> flags;   // vector of flags for operators && = 1, // || = 2, everything else = 0

	Parse() {};
	Parse(std::string s) : str(s) {};
	
	void getInput() {
		getline(std::cin, this->str); // gets a line of input from user
	}
	
	void print() {	// for testing vectors are created correctly
		for(int i = 0; i < args.size(); i++)
		{
			std::cout << "args[" << i << "]: " << args.at(i) << std::endl;
		}
		for(int i = 0; i < flags.size(); i++)
		{
			std::cout << "flags[" << i << "]: " << flags.at(i) << std::endl;
		}
	}

	void tokenize() {	
		typedef boost::tokenizer<boost::char_separator<char> >	
			tokenizer;
		boost::char_separator<char> sep(" ",";#[]"); // remove whitespace, separates at ';'
		tokenizer tokens(this->str, sep);

		for(tokenizer::iterator it = tokens.begin(); it != tokens.end(); ++it){ 
			if(*it == "&&" || *it == "||" || *it == ";" || *it == "#") // fills args and flags vectors 
			{
				this->args.push_back("\0");
				
				if(*it == "&&")
				{
					this->flags.push_back(1);	
				}
				else if(*it == "||")
				{
					this->flags.push_back(2);
				}
				else if(*it == "#")
				{
					//this->args.push_back("\0");
					this->flags.push_back(0);
					break;
				}
				else
				{
					this->flags.push_back(0);
				}
			}
			else
			{	
				this->args.push_back(*it);
			}		
		}
		this->args.push_back("\0"); // adds null terminator to vector of args
		this->flags.push_back(0);

	};
};

#endif
