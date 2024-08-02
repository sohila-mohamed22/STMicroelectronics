#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/wait.h>

#define STDIN  0
#define STDOUT 1
#define STDERR 2


extern char *token ;
extern int append_flag ;
extern int overwrite_flag;
void print_working_directory()
{
	char  buffer[100] ;
	char *directory ;
	directory = getcwd(buffer,100);
	if(directory != NULL)
	{
		printf("%s\n",directory);
	}
	else
	{
		perror("Error");
	}

}
void print_user_input()
{
	   int i ;
      	   token = strtok(NULL," ");
	   while(token != NULL)
	   {
		   size_t len = strlen(token);
		   char *dup = strdup(token);
		   if(token[0]=='"')
		   {
 			   for(i = 1 ; i<len ;i++)
			   {
				   if(token[i]=='"')
				   {
					   token[i] = '\0' ;
					   break ;
				   }
			   }
			   if( i==(len-1) )
			   {
			       printf("%s ",token+1);
			   }
			   else
			   {
			       dup[len-1] = '\0' ;
			       printf("%s ",strcat(token+1,dup+(i+2)));
			   }
		   }
		   else
		   {
			   printf("%s ",token);
		   }  
		   token = strtok(NULL," ");
	   }
	   printf("\n");
}

void copy_files()
{
	struct stat src_stat, dest_stat;
	char buff[100] ;
	int size  ;
        int fd[2] ;
	char *file1;
	token = strtok(NULL," ");       
	if(token!=NULL && strcmp(token," ")!=0)
	{
		fd[0] = open(token, O_RDONLY);
		if(fd[0] != -1)
		{ 
			file1 = token ;
			token = strtok(NULL," ");
			if(token != NULL && strcmp(token," ")!=0)
		        {
				     if(append_flag==1)
                                     {  
                                            fd[1] = open(token,  O_WRONLY | O_APPEND | O_CREAT, S_IRUSR | S_IWUSR );
                                     }
                                     else
                                     {
                                           fd[1] = open(token, O_WRONLY |  O_TRUNC | O_CREAT, S_IRUSR | S_IWUSR);
                                     }
                                     if(fd[1] != -1)
                                     {
					     /* check if two files are the same by comparing their inodes and device IDs
					      * first get information about the destination file and source file 
					      * and then compare inode and device IDs */
					     if(stat(token, &dest_stat)==0 && stat(file1, &src_stat)==0 && src_stat.st_ino == dest_stat.st_ino && src_stat.st_dev == dest_stat.st_dev)
                                            {
						 fflush(stdout);
                                                 printf("cp: '%s' and '%s' are the same file\n",token,token);
                                            }
                                             else
                                             {
                                                  do

                                                   {
                                                      size = read(fd[0],buff,100);
                                                      write(fd[1],buff,size);
                                                   }while(size ==100);
                                              }
                                              close(fd[0]);
                                              close(fd[1]);
                                   }
				   else 
				    {
					     fflush(stdout);
			         	     printf("cp: cannot stat '%s': No such file\n",token);
				    }
			}
	          	else
                        {
			        fflush(stdout);
                                printf("cp: missing destination file operand\n");
                                close(fd[0]); // Close the source file since the destination file is not open
                        }

		}
                else
                {
			fflush(stdout);
                        printf("cp: cannot stat '%s': No such file\n",token);
                }
	}
	else
	{
		fflush(stdout);
		printf("Enter the source and destination files\n");
		
	}
}

void move_files()
{
	struct stat src_stat, dest_stat;
        char buff[100] ;
        int size  ;
        int fd[2] ;
        char *file1;
        token = strtok(NULL," ");
        if(token!=NULL && strcmp(token," ")!=0)
        {
                fd[0] = open(token, O_RDONLY);
                if(fd[0] != -1)
                {
                        file1 = token ;
                        token = strtok(NULL," ");
                        if(token != NULL && strcmp(token," ")!=0)
                        {
                                     fd[1] = open(token, O_WRONLY);
                                     if(fd[1] != -1)
                                     {
                                             /* check if two files are the same by comparing their inodes and device IDs
                                              * first get information about the destination file and source file
                                              * and then compare inode and device IDs */
                                             if(stat(token, &dest_stat)==0 && stat(file1, &src_stat)==0 && src_stat.st_ino == dest_stat.st_ino && src_stat.st_dev == dest_stat.st_dev)
                                            {
                                                 fflush(stdout);
                                                 printf("cp: '%s' and '%s' are the same file\n",token,token);
                                            }
                                             else
                                             {
						     if(overwrite_flag==1)
						     {
							     do
							     {
 								   size = read(fd[0],buff,100);
                                                                   write(fd[1],buff,size);
							     }while(size==100);
							     unlink(file1);
						     }
						     else
						     {
							     fflush(stdout);
							     printf("mv: the file '%s' already exist\nUsage: mv [-f] if you want to overwrite\n",token);
						     }
					     }
                                              close(fd[0]);
                                              close(fd[1]);
                                   }
                                   else
                                    {
                                             fd[1] = open(token, O_WRONLY |  O_TRUNC | O_CREAT, S_IRUSR | S_IWUSR);
					     do
                                             {
                                                   size = read(fd[0],buff,100);
                                                   write(fd[1],buff,size);
                                             }while(size==100);
					     unlink(file1);
                                    }
                        }
                        else
                        {
                                fflush(stdout);
                                printf("cp: missing destination file operand\n");
                                close(fd[0]); // Close the source file since the destination file is not open
                        }

                }
                else
                {
                        fflush(stdout);
                        printf("cp: cannot stat '%s': No such file\n",token);
                }
        }
        else
        {
                fflush(stdout);
                printf("Enter the source and destination files\n");

        }

}
void change_directory()
{
	char *path ;
        char cwd[100];
	// Get the directory argument from the input
        token = strtok(NULL," ");
	if(token != NULL && strcmp(token," ")!=0)
	{
		if(access(token,F_OK)==0)
		{
		      // Get the current working directory
	              if(getcwd(cwd, sizeof(cwd)) == NULL)
	              {
		        perror("getcwd error");
	              }	       
	             else
	             {
	         	// Allocate memory for the new path
                       path = malloc(strlen(cwd) + strlen(token) + 2); // +2 for '/' and '\0'	     
		       strcpy(path, cwd);
		       strcat(path, "/");
		       strcat(path, token);
	               // Change the current directory
		       if (chdir(path) != 0)
		       {
                         perror("chdir error");
		       }
		      free(path);
	              }
		}
		else
		{
			fflush(stdout);
			printf("bash: cd: '%s': No such file or directory\n",token);
		}
	}
	else
	{
	      fprintf(stderr, "Usage: cd <directory>\n");
	}
}
void print_envir_variable()
{
	extern char** environ;
	int i =0 ;
        while(environ[i] !=NULL)
        {
                printf("%s\n", environ[i++]);
        }
}
int print_command_type()
{
	char* internal_commands[] = {"myenv","mycp","mymv","cd", "echo", "exit", "pwd", "set", "unset", "export", "alias", "unalias", NULL};
	int internal_flag=0;
	int external_flag=0;
	int i= 0 ;
	char *path_env ;
	char *path ;
	char fullpath[1024];
	token = strtok(NULL," ");
	if(token != NULL && strcmp(token," ")!=0)
	{
		for(i = 0 ; internal_commands[i]!=NULL ; i++)
		{
			if(strcmp(token,internal_commands[i])==0)
			{
			    printf("%s is a shell builtin\n",internal_commands[i]);
			    internal_flag = 1 ;
			    break ;
			}
		}
		if(internal_flag==0)
		{
			path_env = getenv("PATH");
		        path = strdup(path_env);
			path = strtok(path,":");
			while(path != NULL)
			{
				strcpy(fullpath,path);
				strcat(fullpath,"/");
				strcat(fullpath,token);
				if (access(fullpath, X_OK) == 0)
			       	{
                                     printf("%s is %s\n", token, fullpath);
                                     external_flag = 1;
                                      break;
                                }
				path = strtok(NULL,":");
			}
		}
		if(external_flag==0 && internal_flag==0)
		{
			fflush(stdout);
			printf("bash: type: %s: not found\n",token);
		}

	}
	else
	{
		printf("type: Enter the command\n");
	}
        
}
void external_command(char **args)
{
	int external_flag = 0; 
	/* check if the command is external or not*/
	char *path_env = getenv("PATH");
        // Duplicate the PATH environment variable string
	char *path = strdup(path_env);
	char fullpath[1024];
	char *path_token = strtok(path,":");
        while(path_token != NULL)
	{
              strcpy(fullpath,path_token);
	      strcat(fullpath,"/");
	      strcat(fullpath,args[0]);
              if (access(fullpath, X_OK) == 0)
              {
                   external_flag = 1;
                   break;
              }
              path_token = strtok(NULL,":");
	}
	//
	if(external_flag)
        {
		//Fork and exec the command
                pid_t pid = fork();
		if( pid>0 )
		{
			int status =0;
                        wait(&status);
		}
		else if( pid==0 )
		{
			extern char **environ; // Use the environment of the current process
			//child process
		        execve(fullpath, args , environ);
                        perror("execv");  // execv returns only on error
		        exit(1) ;
		}

	}
	else
       	{
            fprintf(stderr, "Command not found: %s\n", args[0]);
	}
	free(path);
}

void print_help()
{
	   printf("'IMPORTANT'All external commands are available.\n");
	   printf("These are all the supported internal commands.\n");
           printf("pwd:   Print the name of the current working directory.\n\n");
           printf("echo:  Write arguments to the standard output.\n\n");
	   printf("mycp:  copy a file to another file \noptions : \n    -a   append the source content to the end of target file.\n\n");
	   printf("mymv:  move a file to another place \noptions : \n   -f  to force overwriting the target file if exits.\n\n");
           printf("type:  print the type of command (builtin, external or unsupported).\n\n");
           printf("cd:    change the current working directory.\n\n");
           printf("myenv: print all the environment variable.\n\n");
           printf("'IMPORTANT'All external commands are available.\n\n");	   
}
