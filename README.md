
# Clients-Server Calculator
Welcome to the Clients-Server Calculator !





## Overview
This repository contains a client program that sends a request to a math server for a mathematical calculation. The calculation type (addition, subtraction, multiplication, or division) and the two operands are passed as command line arguments to the client program, along with the server's PID.

The client program creates a file called "to_srv.txt" and writes the client's PID and the calculation parameters to this file. The client then sets up signal handlers for the SIGALRM and SIGINT signals. If the client does not receive a response from the server within 30 seconds (TIMEOUT), the SIGALRM signal will be triggered and the client will print an error message and exit. When the server has finished the calculation and written the result to a file, it will send the SIGINT signal to the client. The client will then read the result from the file, print it, delete the "to_srv.txt" and "to_client_[client_pid].txt" files, and exit the program.

If the client is unable to create the "to_srv.txt" file, it will try again up to 10 times with a random delay between each attempt. If the file still cannot be created after these attempts, the program will print an error message and exit.
## Getting Started
This program is written in C and has been tested on Linux systems
To get started with the Calculator program, follow these steps:

 1. Clone this repository to your local machine.
 2. Navigate to the repository directory.
 3. Compile the client and the Server program in home directory :
  ```
  gcc -o ex_2_srv.out ex_2_srv.c
  gcc -o ex_2_client.out ex_2_client.c
  ```
 4. To grab the server's PID just run the command:
  ```
  ex_2_srv.out &
  ```    
 5. Run the client program with the desired server PID, operands, and operation type:
 ```
 ./ex_2_client.out [server_pid] [operand1] [operation_type] [operand2]

 ```
 Replace [server_pid] with the PID of the math server, [operand1] and [operand2] with the two operands for the calculation, and [operation_type] with the desired operation (1 for addition, 2 for subtraction, 3 for multiplication, or 4 for division).

Thats all ! Have fun ! 
## Examples
```
$ ./ex_2_srv.out &
[1] 1234
$ ps
  PID TTY          TIME CMD
 1234 pts/0    00:00:00 ex_2_srv.out
 1235 pts/0    00:00:00 ps
$ ./ex_2_client.out 1234 5 1 6
Result: 11

```
```
./ex_2_client.out 1234 100 4 25
Result: 4
```
## Conclusion
This math-client program provided an opportunity to work with files and signals in C. Key concepts that were explored include:

*  Creating and writing to files using the open and write functions.
*  Setting up signal handlers using the signal function.
*  Sending signals using the kill function.
*  Practicing fork() and execvp() functions and understanding processes hierarchy.
