#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include "execute.h"
#include "component.h"
#include "connector.h"
using namespace std;

int main(){
    
	OriginalClass* command = new OriginalClass("command",1); //simliar to a base class but slightly different, there is a single instance of this class at all times so that we can use the interface defined by the composite structure even before the user enters the first command
    
	while(1)
	{
		cout<<"$ "; //print prompt
		command->getCmd(); //user input
        
        int errorflag = 0;
        
		command->child1 = command->buildTree(errorflag); //composite structure built based on user input
        
        if (errorflag == 0){
        
            int flag = 0; //this is the flag that gets set by the most recently run command, 1 if an error occured, 0 if not
            int test = 0; //this holds information about what the previous opperator was, new commands run if flag = test
        
/*for example: if the previous command was || and the first child of the previous command worked, flag will be 0 because
 there was not an error running the previous command, and test will be 1, because the next command should only run if an
 error occured (meaning flag = 1), in this situation the next command would not run because flag = 1 and test = 0*/
        
        
            command->execute(flag, test); //run commands that are held in composite tree
        }
        else if(errorflag == 1){
            cout << "syntax error: uneven parentheses" <<endl;
        }
        else if (errorflag == 3){
            cout << "error: expected command" << endl;
        }
        else if (errorflag == 4){
            cout << "error: unexpected command after \")\"" << endl;
        }
	}
	return 1;
}
