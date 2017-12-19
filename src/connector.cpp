#include "connector.h"
#include "component.h"
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/wait.h>
#include <iostream>
void Always::execute(int& flag, int& test){
    if (flag == test) child1->execute(flag, test);
    flag = 0; //when the ; opperator is used, it doesnt matter what the value of flag is, it just must be equal to the value of test to ensure that the next command will run, I picked 0 just because it seemed like a good defualt
    
    test = 0; //these are explained in better detail in main.cpp, read more about it there if you want to
    child2->execute(flag, test);
	return;
}
void And::execute(int& flag, int& test){
    if (flag == test){
        child1->execute(flag, test);
    }
    test = 0; //test for && opperator is 0, this means the next command will only run if flag = 0 (no error)
    child2->execute(flag, test);
    return;
}
void Or::execute(int& flag, int& test){
    if (flag == test){
        child1->execute(flag, test);
    }
    test = 1; //test for || opperator is 1, this means the next command will only run if flag = 1 (error occured)
    child2->execute(flag, test);
    return;
}
void Comment::execute(int& flag, int& test){
    if (flag == test) child1->execute(flag, test); //test does not need to be set for comments because they only have a single child that will run or not run based on previous commands
	return;
}
void Parentheses::execute(int& flag, int& test){
    if (flag == test) child1->execute(flag, test); //Parentheses only has 1 child
    return;
}
void Pipe::execute(int& flag, int& test){
    std::cout << "Pipes do not work, connector.cpp line 40 probably holds the problem" << std::endl;
    /*int cmdpipe[2];
    int stdin_copy = dup(0);
    int stdout_copy = dup(1);
    if (pipe(cmdpipe) == -1){
        printf("pipe failed\n");//ERROR
        flag = 1;
        return;
    }
    close(1);
    dup2(cmdpipe[1], 1);
    close(cmdpipe[1]);
    if (flag == test){
        child1->execute(flag, test, 1, cmdpipe);//pipe
    }
    flag = 0;
    test = 0;
    close(0);
    dup2(cmdpipe[0], 0);
    close(cmdpipe[0]);
    child2->execute(flag, test, 0, cmdpipe);//pipe
    close(0);
    close(1);
    dup2(stdin_copy, 0);
    dup2(stdout_copy, 1);
    close(stdin_copy);
    close(stdout_copy);*/
    return;
}
