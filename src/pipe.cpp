#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <errno.h>

#define PIPE_READ 0
#define PIPE_WRITE 1

int createChild(char* cmds[]){
int aStdinPipe[2];
int aStdoutPipe[2];
int nChild;
char nChar;
int nResult;

if (pipe(aStdinPipe) < 0){
	perror("allocating pipe for input redirect");
	return -1;
}
if (pipe(aStdoutPipe) < 0){
	close(aStdinPipe[PIPE_READ]);
	close(aStdinPipe[PIPE_WRITE]);
	perror("allocating pipe for output redirect");
	return -1;
}

nChild = fork();
if (nChild == 0){
//child continues here
//
//redirect stdin
if(dup2(aStdinPipe[PIPE_READ], STDIN_FILENO) == -1) {
	exit(errno);
}

//redirect stdout
if (dup2(aStdoutPipe[PIPE_WRITE], STDOUT_FILENO) == -1){
	exit(errno);
}

//all these are for use by parent only
close(aStdinPipe[PIPE_READ]);
close(aStdinPipe[PIPE_WRITE]);
close(aStdoutPipe[PIPE_READ]);
close(aStdoutPipe[PIPE_WRITE]);

//run child process image?

//Also replace execve with exec* function need
// nResult = execve(cmds[0]);

exit(nResult);
} 

else if (nChild > 0){
//parent continoues here
//
//close unused file descriptors, there are for child only
	close(aStdinPipe[PIPE_READ]);
	close(aStdinPipe[PIPE_WRITE]);

//char by char read, can change later
	while (read(aStdout[PIPE_WRITE], &nChar, 1) == 1){
		write(STDOUT_FILENO, &nChar, 1);
}
	close(aStdinPipe[PIPE_WRITE]);
	close(aStdoutPipe[PIPE_READ]);
}

else {
//failed to create child
close(aStdinPipe[PIPE_READ]);
close(aStdinPipe[PIPE_WRITE]);
close(aStdoutPipe[PIPE_READ]);
close(aStdoutPipe[PIPE_WRITE]);
}

return nChild;

};


