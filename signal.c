
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <stdio.h>
#include <fcntl.h>

static void sighandler(int signo){
  // Catches the SIGUSR1 signal
	if (signo == SIGUSR1){
		//Print out the PID of the parent process. Do not exit
		printf("The parent process id is : %d\n", getppid());
	}
	if (signo == SIGINT){
		//Before exiting, append a message to a file noting that the program exited due to SIGINT
		printf("Exited process %d due to SIGINT (check error.txt)\n", getpid());
		int fd = open("error.txt", O_WRONLY | O_APPEND | O_CREAT, 0644);
		char message[] =  "The program ended due to SIGINT\n";
		int w = write(fd, message, sizeof(message));
		close(fd);
		exit(0);
	}
}


int main(){
	signal(SIGINT, sighandler);
	signal(SIGUSR1, sighandler);
	//Runs constantly inside a forever while loop.
	while(1){
		//Print out the process' PID inside the loop & use sleep(1) function
		printf("Hello, my process id is %d!\n", getpid());
		sleep(1);
  }
	return 0;
}
