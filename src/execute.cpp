#include <iostream>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "execute.h"
using namespace std;
//                                                                PIPE EXCT IS AT THE BOTTOM
Exct::Exct(string in_command){
	command = in_command;
	flag = 0;
}

Exct::~Exct(){}
shExct::shExct(std::string in_command):Exct(in_command)
{
	;
}

int shExct::getFlag(){
	return flag;
}

int PipeExct::getFlag(){
    return flag;
}

int exitExct::getFlag(){
	return flag;
}

int testExct::getFlag(){
	return flag;
}

int shExct::execute(){
	char *cmd = new char[command.length()+1];
	flag = 0;
	strcpy(cmd, command.c_str());
	char *argv[100];
	int temp = 0;
	int i=0, j=0;
	int len = strlen(cmd);
	for(i=0, j=0;i<len;i++)
	{
		if(cmd[i] == ' ')
		{
			cmd[i] = '\0';
			argv[j] = cmd + temp;
			temp = i + 1;
			j++;
		}
		if(i == len-1)
		{
			argv[j] = cmd + temp;
			j++;
		}
	}
	while(j<100)
	{
		argv[j] = 0;
		j++;
	}
	pid_t child_pid;
	int child_status;
	child_pid = fork();
	if(child_pid == 0)
	{/*This is done by the child process.*/
		if (execvp(argv[0], argv) == -1){
            printf("Uknown command\n");
        }
        exit(EXIT_FAILURE);
	}
	else if(child_pid > 0){/*This is run by the parent. Wait for the child to terminate*/
		if(waitpid(child_pid, &child_status, 0) == -1){
			printf("command failure");
		}
		else{
			if (WIFEXITED(child_status) && WEXITSTATUS(child_status) != 0){
				flag = 1;
			}
		}
	}
	return 0;
}

exitExct::exitExct(std::string in_command):Exct(in_command){
    ;
}

int exitExct::execute(){
	exit(0);
	return 0;
}

testExct::testExct(std::string in_command):Exct(in_command){
    ;
}
PipeExct::PipeExct(std::string in_command):Exct(in_command){
    ;
}
int testExct::execute(){//Assuming the length of input is long enough, so it won't cause some unexpected problems at present.(e.g. "[ -e ]")
			//flag == 0 -no directory no file; flag == 1 -d; flag == 2 -f; flag == 3 -e.
            //flag should be 1 if failed and 0 if not?
			//According to binary, maybe we can utilize this.	
	char *cmd = new char[command.length()+1];
	//char *tmp_cmd = new char[command.length()+1];
	flag = 0;
	strcpy(cmd, command.c_str());
	int i = 0/*, j = 0*/;
	struct stat buf;
	int len = strlen(cmd);
	for(i=0;i<len;i++)
	{
		if(cmd[i] == ' ')
		{
			continue;
		}
		if(cmd[i] == '-')//" -..."
		{
			if(cmd+i+1 == NULL)//" -"
			{
				flag = 1;
                printf("(False)\n"); //maybe syntax error FIX ME
				return 1;
			}
            if(cmd[i+1] == ' '){  //" - "
                if (cmd+i+2 == NULL)
                {
                    flag = 0;
                    printf("(True)\n");
                    return 0;
                }
                else{      //" - ..." bash: [: -: unary operator expected
                    //syntax error        FIX ME
                }
            }
			if(cmd[i+1] == 'e')//" -e..."
			{
				if(cmd+i+2 == NULL)//" -e"
				{
					flag = 1;
                    printf("(False)\n"); //maybe syntax error FIX ME
					return 1;
				}
				if(cmd[i+2] == ' ')//" -e ..."
				{
					if(cmd+i+3 == NULL)//" -e "
					{
                        flag = 0;
                        printf("(True)\n");
                        return 0;
					}
					/*for(j=i+3;j<len;j++)
					{
						if(cmd[j] == ' ')
						{
							continue;
						}
						else
						{
							break;
						}
					}*/
					stat(cmd+i+3, &buf);
					if(S_ISDIR(buf.st_mode) || S_ISREG(buf.st_mode))
					{
                        flag = 0;
                        printf("(True)\n");
                        return 0;

					}else{
                        flag = 1;
                        printf("(False)\n");
                        return 1;
					}
					
				}else{//" -e..."         FIX ME, THIS IS MORE COMPLICATED
					stat(cmd+i, &buf);
					if(S_ISDIR(buf.st_mode) || S_ISREG(buf.st_mode))
					{
                        flag = 0;
                        printf("(True)\n");
                        return 0;
					}else{
                        flag = 1;
                        printf("(False)\n");
                        return 1;

					}
				}
			}
			else if(cmd[i+1] == 'f')//" -f..."
			{
				if(cmd+i+2 == NULL)//" -f"
				{
					flag = 1;
                    printf("(False)\n"); //maybe syntax error FIX ME
					return 1;
				}
				if(cmd[i+2] == ' ')//" -f ..."
				{
					if(cmd+i+3 == NULL)//" -f "
					{
                        flag = 0;
                        printf("(True)\n");
                        return 0;
					}
					stat(cmd+i+3, &buf);
					if(S_ISREG(buf.st_mode))
					{
                        flag = 0;
                        printf("(True)\n");
                        return 0;

					}else{
                        flag = 1;
                        printf("(False)\n");
                        return 1;
					}
				}else{//" -f..."               FIX ME, more complicated
					stat(cmd+i, &buf);
					if(S_ISDIR(buf.st_mode) || S_ISREG(buf.st_mode))
					{
                        flag = 0;
                        printf("(True)\n");
                        return 0;

					}else{
                        flag = 1;
                        printf("(False)\n");
                        return 1;
					}
				}
			}
			else if(cmd[i+1] == 'd')//" -d..."
			{
				if(cmd+i+2 == NULL)//" -d"
				{
					flag = 1;
                    printf("(False)\n"); //maybe syntax error FIX ME
					return 1;
				}
				if(cmd[i+2] == ' ')//" -d ..."
				{
					if(cmd+i+3 == NULL)//" -d "
					{
                        flag = 0;
                        printf("(True)\n");
                        return 0;
					}
					stat(cmd+i+3, &buf);
					if(S_ISDIR(buf.st_mode))
					{
                        flag = 0;
                        printf("(True)\n");
                        return 0;

					}else{
                        flag = 1;
                        printf("(False)\n");
                        return 1;
					}
				}else{//" -d..."                FIX ME, more complicated
					stat(cmd+i, &buf);
					if(S_ISDIR(buf.st_mode) || S_ISREG(buf.st_mode))
					{
                        flag = 0;
                        printf("(True)\n");
                        return 0;

					}else{
                        flag = 1;
                        printf("(False)\n");
                        return 1;
					}
				}
			}
			else{//" -..."
				if(cmd+i+2 == NULL)//" -"
				{
					flag = 1;
                    printf("(False)\n"); //maybe should be syntax error instead
					return 1;
				}
				if(cmd[i+2] == ' ')//" - ..."
				if (cmd+i+3 == NULL)
                {
					flag = 0;
                    printf("(True)\n");
					return 0;
				}
                else
                {
                                             //FIX ME syntax error
                }
                else{//" -..."               FIX ME, more complicated
					stat(cmd+i, &buf);
					if(S_ISDIR(buf.st_mode) || S_ISREG(buf.st_mode))
					{
                        flag = 0;
                        printf("(True)\n");
                        return 0;
					}
                    else{
                        flag = 1;
                        printf("(False)\n");
                        return 1;

					}
				}
			}
		}
		else//The command starts as a character which is not '-'
		{
            stat(cmd+1, &buf);
            if(S_ISDIR(buf.st_mode) || S_ISREG(buf.st_mode))
            {
                flag = 0;
                printf("(True)\n");
                return 0;
            }else{
                flag = 1;
                printf("(False)\n");
                return 1;
            }
		}
	}
	flag = 1;//"[        ]"
    printf("(False)\n");
	return 1;
}

int PipeExct::execute(int ptype, int cmdpipe[2]){
    /*if (ptype == 1){
        close(1);
        dup(cmdpipe[1]);
        close(cmdpipe[0]);
        close(cmdpipe[1]);
    }
    else if (ptype == 0){
        close(0);
        dup(cmdpipe[0]);
        close(cmdpipe[1]);
        close(cmdpipe[0]);
    }*/
    char *cmd = new char[command.length()+1];
    flag = 0;
    strcpy(cmd, command.c_str());
    char *argv[100];
    int temp = 0;
    int i=0, j=0;
    int len = strlen(cmd);
    for(i=0, j=0;i<len;i++)
    {
        if(cmd[i] == ' ')
        {
            cmd[i] = '\0';
            argv[j] = cmd + temp;
            temp = i + 1;
            j++;
        }
        if(i == len-1)
        {
            argv[j] = cmd + temp;
            j++;
        }
    }
    while(j<100)
    {
        argv[j] = 0;
        j++;
    }
    pid_t child_pid;
    int child_status;
    child_pid = fork();
    if(child_pid == 0)
    {/*This is done by the child process.*/
        if (execvp(argv[0], argv) == -1){
            printf("Uknown command\n");
        }
        exit(EXIT_FAILURE);
    }
    else if(child_pid > 0){/*This is run by the parent. Wait for the child to terminate*/
        if(waitpid(child_pid, &child_status, 0) == -1){
            printf("command failure");
        }
        else{
            if (WIFEXITED(child_status) && WEXITSTATUS(child_status) != 0){
                flag = 1;
            }
        }
    }
    return 0;
}
