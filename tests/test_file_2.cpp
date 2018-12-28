#include "parser.h"
#include "connector.h"
#include "command.h"
#include "iostream"
#include <sys/types.h>
#include <sys/wait.h>
#include <vector>
#include <string>
#include "gtest/gtest.h"

class testCmdTest : public :: testing :: Test{ //set up for class testCmdTest which will be used for all google testing in this .cpp
protected:
	virtual void SetUp() {}

	virtual void TearDown () {}
};

TEST_F(testCmdTest, There){	//Test There will check if the file src/ is found
	std::vector<std::string> command;

	command.push_back("test");
	command.push_back("src/");
	command.push_back("\0");

	TestCommand *tcmd = new TestCommand();
	tcmd->setArgs(command);

	EXPECT_EQ(0, tcmd->execute()); //expected results is 0, which means true the file was found
};

TEST_F(testCmdTest, notThere){ //Test notThere will check what happens if the file is not found
        std::vector<std::string> command;

        command.push_back("test");
        command.push_back("src/hello"); //file will not be found
        command.push_back("\0");

        TestCommand *tcmd = new TestCommand();
        tcmd->setArgs(command);

        EXPECT_EQ(-1, tcmd->execute()); //expected return value is -1, which means false file not found
};

TEST_F(testCmdTest, bNormTest){ //This test will check what happens when [] operation is entered 
        std::vector<std::string> command;

        command.push_back("[");
        command.push_back("src/");
	command.push_back("]");
        command.push_back("\0");

        TestCommand *tcmd = new TestCommand();
        tcmd->setArgs(command);

        EXPECT_EQ(0, tcmd->execute()); //expected result is true
};

TEST_F(testCmdTest, bBadTest){//this test checks what happens when a file that is not found with the [] operation
        std::vector<std::string> command;

        command.push_back("[");
        command.push_back("src/hello");//file doesn't exist
        command.push_back("]");
        command.push_back("\0");

        TestCommand *tcmd = new TestCommand();
        tcmd->setArgs(command);

        EXPECT_EQ(-1, tcmd->execute());//expected results will be false 
};

TEST_F(testCmdTest, bFlag_d_Test){//This test will check [-d] operation with a good file
        std::vector<std::string> command;

        command.push_back("[");
        command.push_back("-d");
	command.push_back("src/");
        command.push_back("]");
        command.push_back("\0");

        TestCommand *tcmd = new TestCommand();
        tcmd->setArgs(command);

        EXPECT_EQ(0, tcmd->execute());//expected value should be true
};

TEST_F(testCmdTest, bBadFlag_d_Test){ //This test will check [-d] operation with a bad file
        std::vector<std::string> command;

        command.push_back("[");
	command.push_back("-d");
        command.push_back("src/hello");//file doesn't exist
        command.push_back("]");
        command.push_back("\0");

        TestCommand *tcmd = new TestCommand();
        tcmd->setArgs(command);

        EXPECT_EQ(-1, tcmd->execute());//expected value is false
};

TEST_F(testCmdTest, bFlag_e_Test){ //This test will check [-e] operation with a good file
        std::vector<std::string> command;

        command.push_back("[");
        command.push_back("-e");
        command.push_back("src/");
        command.push_back("]");
        command.push_back("\0");

        TestCommand *tcmd = new TestCommand();
        tcmd->setArgs(command);

        EXPECT_EQ(0, tcmd->execute());//expected results should be true
};

TEST_F(testCmdTest, bBadFlag_e_Test){//This test will check [-e] operation with a bad file
        std::vector<std::string> command;

        command.push_back("[");
        command.push_back("-e");
        command.push_back("src/hello");//file doesn't exist
        command.push_back("]");
        command.push_back("\0");

        TestCommand *tcmd = new TestCommand();
        tcmd->setArgs(command);

        EXPECT_EQ(-1, tcmd->execute());//expected results should be false
};

int main(int argc, char **argv){ //main for googletest
        ::testing::InitGoogleTest(&argc, argv);
        return RUN_ALL_TESTS();//returns the results of all tests in this .cpp
};


