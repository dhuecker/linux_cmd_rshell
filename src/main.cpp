#include "parser.h"
#include "connector.h"
#include "command.h"
#include <iostream>
#include <sys/types.h>
#include <sys/wait.h>

int runCmds(std::vector<std::string>);

int main() {
	
	const int SIZE = 256; // buffer for gethostname function
	int pid; // fork pid
	int wpid; // wait pid
	int status;	// fork exiting status
	int cmdCount; // total number of commands user entered
	char hostName[SIZE];
	
	gethostname(hostName, SIZE);
	std::vector<std::vector<std::string>> commands; // vector of vector<string> to hold each command separately

	for(;;) 
	{
	
		cmdCount = 0;
		commands.clear();
		std::cout << getenv("USER") << "@" << hostName << " $ ";

		// Creates Parse object, gets line of input from user and tokenizes the input
		Parse* input = new Parse;
		input->getInput();
		input->tokenize();
		
		// Determines number of commands from user input
		for(int i = 0; i < input->args.size(); i++) 
		{
			if(input->args.at(i) == "\0")
			{
				cmdCount++;
			}
		} 

		// Set vector size based on number of commands
		commands.resize(cmdCount);

		// Pushes commands into vector of vector<string>
		int j = 0;	
		for(int i = 0; i < input->args.size(); i++)
		{
			commands.at(j).push_back(input->args.at(i));
			if(input->args.at(i) == "\0")
			{
				j++;
			}
		}	
		
		// Will fork for each command, depending on number of commands
		for(int i = 0; i < commands.size(); i++)
		{

			//creates TestCommand object , not using execvp to execute	
			if (commands.at(i).at(0) == "test" || commands.at(i).at(0) == "[")
			{
				TestCommand *tcmd = new TestCommand();
				tcmd->setArgs(commands.at(i));
				
				if (tcmd->execute() == 0)
				{
					if (input->flags.at(i) == 1)
					{
						//break;
					}
					else if (input->flags.at(i) == 2)
					{
						i++;
						//break;
					}
				}
				else
				{
					if (input->flags.at(i) == 1)
					{
						i++;
						//break;
					}
					else if (input->flags.at(i) == 2)
					{
						//break;
					}
				}
			}
			else // if not "test" or [ ] every other command
			{			
				Command *cmd = new Command();
				cmd->setArgs(commands.at(i));
			
				if ((pid = fork()) == 0) // child
				{	
					if (cmd->execute() < 0)
					{
						perror("failed exec");
						exit(1);
					}	
				}
				else if (pid > 0) // parent
				{
					for (;;) 
					{
						wpid = waitpid(-1, &status, 0);
						if (pid == wpid)
						{
							if (WEXITSTATUS(status) == 2) // If user entered "exit"
							{
								exit(0); // Exits rshell
							}
							else if (WEXITSTATUS(status) == 0) // command executed no error
							{
								if (input->flags.at(i) == 1) // && flag
								{
									break;
								}
								else if (input->flags.at(i) == 2) // || flag
								{
									i++;
									break;
								}
							}
							else if (WEXITSTATUS(status) == 1) // command failed to execute
							{
								if (input->flags.at(i) == 1)
								{
									i++;
									break;
								}
								else if (input->flags.at(i) == 2)
								{
									break;
								}
							}
							break;
						}
					}				
				}
				else // fork failed
				{
					perror("fork failed");
					exit(-1);
				}	
			}
		}	
	} // main for(;;)

	return 0;
}
