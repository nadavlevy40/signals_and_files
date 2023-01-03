
#include <stdio.h>

#include <stdlib.h>

#include <unistd.h>

#include <signal.h>

#include <sys/types.h>

#include <sys/stat.h>

#include <fcntl.h>

#include <string.h>

#include <time.h>

#define TIMEOUT 30 // timeout in seconds


int get_random() {
  int random_number = (rand() % 5) + 1;
  return random_number;
}

void handler_alarm(){
  // Timer expired, print error message and exit program
        printf("client closed because no response\n");
        exit(1);
 }

void handler() {
    int curr_pid = getpid();
    char filename[32];
    sprintf(filename, "to_client_%d.txt", curr_pid);

    int fd_to_client = open(filename, O_RDONLY);
    if (fd_to_client < 0) {
      printf("ERROR_FROM_EX2\n");
      exit(1);
    }
    int result;
    int num_read = read(fd_to_client, & result, sizeof(int));
      // read result from server

      printf("Result: %d\n", result);
      close(fd_to_client);
       unlink("to_srv.txt"); // delete to_srv.txt
       unlink(filename); // delete to_client_[client_pid].txt
      //remove("to_srv.txt");
      //remove(filename);
	printf("end of stage j\n");
	exit(0);
}

    

  
    int main(int argc, char * argv[]) {
      if (argc != 5) {
      printf("ERROR_FROM_EX2\n");
        exit(1);
      }
     signal(SIGALRM,handler_alarm);
     signal(2, handler);      

      // get server PID and calculation parameters from command line
      int server_pid = atoi(argv[1]);
      int a = atoi(argv[2]);
      int op = atoi(argv[3]);
      int b = atoi(argv[4]);
      if(op!=1 && op!=2 &&op!=3 && op!=4){
	printf("insert valid operation number (1-4)\n");
	exit(1);
	}
	if(op==4 && b==0){
	 printf("cannot divide by zero!\n");
	 exit(1);
	}
      // create server-to file
      int i=0;
      int fd_to_srv = open("to_srv.txt", O_CREAT | O_WRONLY, S_IRUSR | S_IRWXU);
      if(fd_to_srv<0){
      for ( i; i < 10; i++) {
         fd_to_srv = open("to_srv.txt", O_CREAT | O_WRONLY, S_IRUSR | S_IRWXU);
        if (fd_to_srv < 0) {
          int random_number = get_random();
          sleep(random_number);
        } else {
          break;
        }
      }
	printf("end of stage e\n");
      if (i == 10 || i == 11) {
        printf("Cannot connect to server , bye bye");
	close(fd_to_srv);
        exit(1);
      }
     }
      // write client PID and calculation parameters to server-to file
      int curr_client_pid = getpid();
      write(fd_to_srv, & curr_client_pid, sizeof(int));
      write(fd_to_srv, & a, sizeof(int));
      write(fd_to_srv, & op, sizeof(int));
      write(fd_to_srv, & b, sizeof(int));

      // close server-to file
      close(fd_to_srv);

      // send signal to server
      printf("end of stage d\n");
      kill(server_pid, 1);
	alarm(TIMEOUT);
      pause();
	alarm(0);
	
    
     
      exit (0);
    }	