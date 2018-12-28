#include "parser.h"
#include "connector.h"
#include "command.h"
#include "iostream"
#include <sys/types.h>
#include <sys/wait.h>
#include <vector>
#include <string>
#include "gtest/gtest.h"

class CmdsTest : public :: testing :: Test{ //class CmsTest will hold the set up for google tests for assignment 2
protected:
        virtual void SetUp() {}

        virtual void TearDown() {}
};

TEST_F(CmdsTest, Badcmd){ //Badcmd is name of the first test 

	std::vector<std::string> command;

	command.push_back("echoo");
	command.push_back("hello");
	command.push_back("\0");

	Command *cmd = new Command();
	cmd->setArgs(command);

	EXPECT_EQ(-1, cmd->execute()); // expected result after running a bad code is -1

};

TEST_F(CmdsTest, Goodcmd){ //test what happends with a good cmd in rshell

	std::vector<std::string> command;
	command.push_back("echo");
	command.push_back("hello");
	command.push_back("\0");

	Command *cmd = new Command();
	cmd->setArgs(command);

	EXPECT_EQ(0, cmd->execute()); // expected result is 1 or true for a good cmd
};


TEST_F(CmdsTest, LScmd){//This test will check the ls 

	std::vector<std::string> command;
	command.push_back("ls");
	command.push_back("\0");

	Command *cmd = new Command();
	cmd->setArgs(command); // sets cmds args to ls

	EXPECT_EQ(0, cmd->execute()); // same as test above 
};



int main(int argc, char **argv){//main for googletest
        ::testing::InitGoogleTest(&argc, argv);
        return RUN_ALL_TESTS(); //return the status of all tests run for test_file_1.cpp
};
