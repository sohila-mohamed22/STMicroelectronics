#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#define PATH /home/vboxuser/Desktop/


 
extern char *token ;
extern int append_flag ;
extern int overwrite_flag ;
// Function to trim newline characters
char * trim_newline(char *str)
{
    int len = strlen(str);

    if (len > 0 && str[len - 1] == '\n') 
    {
        str[len - 1] = '\0';
    }
    return str ;
}
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
	   token = strtok(NULL," ");
	   while(token != NULL)
	   {
		   token = trim_newline(token);
		   printf("%s ",token);
		   token = strtok(NULL," ");
	   }
	   printf("\n");
}

void copy_files()
{
	struct stat path_stat;
	char buff[100] ;
	int size = 0 ;
        int fd[2] ;
	const char*file1 ;
	token = strtok(NULL," ");        
	if(token!=NULL && strcmp(token,"\n")!=0 && strcmp(token," ")!=0)
	{
		file1 = token ;
		fd[0] = open(token, O_RDONLY);
		if(fd[0] != -1)
		{ 
			token = strtok(NULL," ");
			token = trim_newline(token);
			if(token != NULL && strcmp(token,"\n")!=0 && strcmp(token," ")!=0)
		        {
				if(append_flag==1)
				{
					fd[1] = open(token,  O_WRONLY | O_APPEND | O_CREAT, S_IRUSR | S_IWUSR );
				}
				else
				{
					fd[1] = open(token,  O_WRONLY | O_TRUNC | O_CREAT , S_IRUSR | S_IWUSR );
				}
				if(fd[1] != -1)
                                {
				    if(strcmp(file1,token)==0)
				    {
					   printf("cp: '%s' and '%s' are the same file\n",file1,file1);
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
			            perror("Error");
				    close(fd[0]);
				}
				return ;
		        }
			else
			{

				printf("cp: missing destination file operand\n");
			}
		
		}
		else
		{
			printf("cp: cannot stat '%s': No such file or directory\n",token);
			close(fd[0]);
			return ;
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
	struct stat path_stat;
        char buff[100] ;
        int size = 0 ;
        int fd[2] ;
        const char*file1 ;
        token = strtok(NULL," ");
        if(token!=NULL && strcmp(token,"\n")!=0 && strcmp(token," ")!=0)
        {

        	 file1 = token ;
                fd[0] = open(token, O_RDONLY);
                if(fd[0] != -1)
                {
                        token = strtok(NULL," ");
                        token = trim_newline(token);
                        if(token != NULL && strcmp(token,"\n")!=0 && strcmp(token," ")!=0)
                        {
                                fd[1] = open(token,  O_WRONLY | O_TRUNC  , S_IRUSR | S_IWUSR );
                                if(fd[1] != -1)
                                {
		              	    if(strcmp(file1,token)==0)
                                    {
                                           printf("cp: '%s' and '%s' are the same file\n",file1,file1);
                                    }
                                    else if(overwrite_flag==1)
				    {
					    overwrite_flag = 0 ;
			                   do
                                           {
                                                size = read(fd[0],buff,100);
                                                write(fd[1],buff,size);
                                           }while(size ==100);
                                           close(fd[0]);
                                           close(fd[1]);
                                           unlink(file1);
				    }
				    else
                                    {
					    printf("Warning: The file already exists.\nUsage: [-f] option if you want to overwrite \n");
                                    }

                                    close(fd[0]);
                                    close(fd[1]);
                                }
                                else
                                { 
					fd[1] = open(token,  O_WRONLY | O_TRUNC | O_CREAT , S_IRUSR | S_IWUSR );
					 do
                                           {
                                                size = read(fd[0],buff,100);
                                                write(fd[1],buff,size);
                                           }while(size ==100);
					 close(fd[0]);
                                        close(fd[1]);
                                      unlink(file1);

                                }
                                return ;
                        }
                        else
                        {
                                printf("cp: missing destination file operand\n");
                        }

                }
                else
                {
                        printf("cp: cannot stat '%s': No such file or directory\n",token);
                        close(fd[0]);
                        return ;
                }
        }

        else
        {
                fflush(stdout);
                printf("Enter the source and destination files\n");

        }

}
