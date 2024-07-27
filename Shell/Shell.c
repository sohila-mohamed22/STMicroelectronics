#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include "command.h"

#define STDIN  0
#define STDOUT 1
#define STDERR 2 
#define MAX_ARGS 15 
char *token ;
int append_flag = 0 ;
int main(int argc,char **argv)
{
	char *args[MAX_ARGS];
	int argc_new ;
        char **argv_new;
	char *cmd ;
	int opt ;
	char command[100];
	ssize_t readsize = 0 ;
	int i = 0 ;
	const char *shellmsg = "Enter the required commnand:";
	while(1)
	{
		write(STDOUT,shellmsg,strlen(shellmsg));
                readsize = read(STDIN,command,100);
                /* get the first token*/
                command[readsize] = '\0'; // Ensure the buffer is null-termination
		
		//put the command in another token 
		cmd = strtok(command," ");
                while (cmd != NULL && i < MAX_ARGS - 1) {
                    args[i++] = cmd;
                  cmd = strtok(NULL, " ");
                 }
                 args[i] = NULL; // Null-terminate the args array
 
                 // Simulate setting up argc and argv
                 argc_new = i;
                 argv_new = args;
	
                token = strtok(command," ");
                /* walk through other tokens */
                while(token != NULL)
                {
                        token = trim_newline(token);
                        if(strcmp(token,"pwd")==0)
                        {
                                print_working_directory();
                        }
                        else if(strcmp(token,"echo")==0)
                        {
                                print_user_input();
                        }
                        else if(strcmp(token,"exit")==0)
                        {
			       printf("Good Bye\n");
                               exit(1);
                        }
			else if(strcmp(token,"cp")==0)
		        {
 				if ((opt = getopt(argc_new, argv_new, "a")) != -1)
                                {
                                      switch (opt)
				      {
                                      case 'a':
					      append_flag = 1 ;
					      copy_files();
                                              break;
                                      default:
                                             fprintf(stderr, "Usage: %s [-a] <elf-file>\n", argv[0]);
				             break ;
				      }
				}
				else
				{
					copy_files();
				}
			}
			else
	                {
				printf("Unknown command: %s\n",token);
			}
			token = strtok(NULL," ");
                 }

	}
	return 0 ;
}

