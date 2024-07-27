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
int overwrite_flag = 0;
int main(int argc,char **argv)
{
	char *args[MAX_ARGS];
	char cmd[100];
	char *token_for_opt ;
	int argc_new ;
        char **argv_new;
	int opt ;
	char command[100];
	ssize_t readsize = 0 ;
	int i = 0 ;
	const char *shellmsg = "Enter the required commnand:";
	while(1)
	{
		// Clear the buffer
                command[0] = '\0';
		write(STDOUT,shellmsg,strlen(shellmsg));
                readsize = read(STDIN,command,100);
                /* get the first token*/
                command[readsize] = '\0'; // Ensure the buffer is null-termination
		
		//put the command in another token 
		strcpy(cmd, command);
		token_for_opt = strtok(cmd," ");
                while (token_for_opt != NULL && i < MAX_ARGS - 1) {
                    args[i++] = token_for_opt;
                  token_for_opt = strtok(NULL, " ");
                 }
                 args[i] = NULL; // Null-terminate the args array
 
                 // Simulate setting up argc and argv
                 argc_new = i;
                 argv_new = args;
                fflush(stdout);	
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
					      token = strtok(NULL," ");
					      copy_files();
                                              break;
                                      default:
                                             fprintf(stderr, "Usage: %s [-a] <source> <dest>\n", argv_new[0]);
				             break ;
				      }
				}
				else
				{
					copy_files();
				}
				break ; // To leave while loop if their is error in file
			}
			else if(strcmp(token,"")==0)
			{
			}
			else if(strcmp(token,"mv")==0)
			{
				if ((opt = getopt(argc_new, argv_new, "f")) != -1)
                                {
                                      switch (opt)
                                      {
                                      case 'f':
                                              overwrite_flag = 1 ;
                                              token = strtok(NULL," ");
                                              move_files();
                                              break;
                                      default:
                                             fprintf(stderr, "Usage: %s [-f] <source> <dest>\n", argv_new[0]);
                                             break ;
                                      }
                                }
                                else
                                {
                                        move_files();
                                }
                                break ; // To leave while loop if their is error in file

			}
			else if(strcmp(token,"help")==0)
			{
                             printf("pwd:   Print the name of the current working directory.\n");
			     printf("echo:  Write arguments to the standard output.\n");
			     printf("cp:    copy a file to another file \n options : \n -a   append the source content to the end of target file\n");
			     printf("mv:  move a file to another place \n options : \n -f  to force overwriting the target file if exits\n");  
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

