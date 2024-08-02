#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include "command.h"

#define STDIN  0
#define STDOUT 1
#define STDERR 2 
#define MAX_ARGS 50
#define MAX_INPUT 1024
#define INITIAL_ARG_SIZE 10

char *token = NULL;
int append_flag = 0 ;
int overwrite_flag = 0;
extern char *optarg;
extern int optind, opterr, optopt;
int main(int argc,char **argv)
{
	char cmd[100];
	char *token_for_opt ;
	int opt ;
	char command[100];
	ssize_t readsize = 0 ;
	int i =0 ;
	const char *shellmsg = "Enter the required commnand:";
	while(1)
	{
		token = NULL ;
		i =0 ; 
	       // Initialize command with zeros
                memset(command, 0, sizeof(command));
		memset(cmd, 0, sizeof(cmd));
		write(STDOUT,shellmsg,strlen(shellmsg));
		readsize = read(STDIN,command,100);
                
                command[readsize-1] = '\0'; // Ensure the buffer is null-termination
		//put the command in another token 
		strcpy(cmd, command);
                  
		// Tokenize the input into arguments
                 char **args = malloc(INITIAL_ARG_SIZE * sizeof(char *));
                 int arg_size = INITIAL_ARG_SIZE;
                 int arg_count = 0;                 
                 char *token = strtok(cmd, " ");
                 while (token) 
		 {
                            if (arg_count >= arg_size - 1)
			    {
                               arg_size *= 2;  // Double the size
                               args = realloc(args, arg_size * sizeof(char *));  // Reallocate memory
                            }
                            args[arg_count++] = token;
                            token = strtok(NULL, " ");
                 }
                  args[arg_count] = NULL;  // Null-terminate the argument list

                fflush(stdout);	
                token = strtok(command," ");
                /* walk through other tokens */
                while(token != NULL)
                {
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
			else if(strcmp(token,"mycp")==0)
		        {
				append_flag = 0; // Reset flag before processing options	
				if (args[1][0]=='-')
                                   {
                                      if(strcmp(args[1],"-a")==0)
				      {
					      append_flag = 1 ;
					      token = strtok(NULL," ");
					      copy_files();
				      }
                                       else
				       {
                                             fprintf(stderr, "Usage: %s [-a] <source> <dest>\n", args[0]);
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
			else if(strcmp(token,"mymv")==0)
			{
				overwrite_flag = 0; // Reset flag before processing options
			     	if (args[1][0]=='-')
                                   {
                                       if(strcmp(args[1],"-f")==0)
                                       {
                                              overwrite_flag = 1 ;
                                              token = strtok(NULL," ");
                                              move_files();
                                        }
                                        else
					{
					      fflush(stdout);
                                              fprintf(stderr, "Usage: %s [-f] <source> <dest>\n", args[0]);
                                        }
				     }
                                else
                                {
                                        move_files();
                                }
                                break ; // To leave while loop if their is error in file

			}
			else if (strcmp(token,"cd")==0)
			{
				change_directory(args);
				break ;
			}
			else if(strcmp(token,"myenv")==0)
			{
				print_envir_variable();
				break ;
			}
			else if(strcmp(token,"type")==0)
			{
				print_command_type();
				break ;
			}
			else if(strcmp(token,"help")==0)
			{
                             print_help();
			}
			else
	                {
				external_command(args);
				//printf("Unknown command: %s\n",token);
				break;
			}
			token = strtok(NULL," ");
                 }
                 free(args);
	}
	return 0 ;
}

