
#include <stdio.h>

#include <stdlib.h>

#include <unistd.h>

#include <signal.h>

#include <sys/types.h>

#include <sys/wait.h>

#include <sys/stat.h>

#include <fcntl.h>

#include <string.h>

#include <time.h>

#define TIMEOUT 60 // timeout in seconds

int calc(int a, int op, int b) {
  int result;
  switch (op) {
  case 1:

    result = a + b;
    break;
  case 2:

    result = a - b;
    break;
  case 3:

    result = a * b;
    break;
  case 4:
      result = a / b;
      break;
    
  }
  return result;
}

void handler_alarm(){
 // Timer expired, delete file and exit program
        remove("to_srv.txt");
        printf("The server was closed because no request received for 60 seconds\n");
        exit(1);
  }

void handler() {
    alarm(TIMEOUT);
    //pid_t pid=fork();
	//if(pid==0){
	//close(1);
    int fd_to_srv = open("to_srv.txt", O_RDONLY);
    if (fd_to_srv < 0) {
      printf("ERROR_FROM_EX2\n");
      exit(1);
    }

    int client_pid;
    int a;
    int op;
    int b;
    int num_read = read(fd_to_srv, & client_pid, sizeof(int));
      // read request from client
      num_read = read(fd_to_srv, & a, sizeof(int));
      num_read = read(fd_to_srv, & op, sizeof(int));
      num_read = read(fd_to_srv, & b, sizeof(int));
      printf("end of stage f\n");
      pid_t pid2  = fork();
      if (pid2 == 0) {
       //son procces started
   	close(1);
	char * argument_list[] = {
          "rm",
          "to_srv.txt",
	   NULL
        };
	 int ex=execvp("rm",argument_list);
	if(ex<0){
	  exit(1);
	}
  }     
	int status;
	pid_t other_pid=wait(&status);
	printf("end of stage g\n");
	//if(pid>0){
      //parent process continue
 	
      int result;
      result = calc(a, op, b);
      // create filename for client response
      char filename[32];
      sprintf(filename, "to_client_%d.txt", client_pid);
	printf("end of stage h\n");
      // open file for writing
      int fd_response = open(filename, O_WRONLY | O_CREAT | O_EXCL, S_IRUSR | S_IWUSR);
      if (fd_response < 0) {
      printf("ERROR_FROM_EX2\n");
        exit(1);
      }
      // write result to client response file
      write(fd_response, & result, sizeof(int));

      // close client response file
      close(fd_response);
	
      // send signal to client
      kill(client_pid, 2);
	unlink("to_srv.txt");
	printf("end of stage i\n");
}


      int main(int argc, char * argv[]) {
        // Delete file if it exists
              remove("to_srv.txt");
              signal(1, handler);
	      signal(SIGALRM,handler_alarm);
              printf("end of stage c\n");

        while (1) {
	 // Set timer for 60 seconds
    	   alarm(TIMEOUT);
          pause();
        }

                return 0;

      }