#include "component.h"
#include "connector.h"
#include "execute.h"
#include <iostream>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <fstream>

//-------------------------------------------READ ME!!!!----------------------------------------
//all the code for the pipe objects is at the bottom of the page
// it should be pretty similar but with pipes instead

CommandComponent::CommandComponent(std::string in_command,int childflag){
	command = in_command;
	hasChild = childflag;
}

CommandComponent* SingleCommand::buildTree(int &x){
return (NULL);
}

void SingleCommand::execute(int& flag, int& test){
    if (flag != test) return;
    Exct* excommand;
    while (command.size() != 0 && command.at(0) == ' '){
        command.erase(0, 1);
    }
    while (command.size() != 0 && command.at(command.size()-1) == ' '){
        command.erase(command.size()-1, 1);
    }
    //---------------------------------input redirect?---------------------------------
    int stdin_copy = dup(0);
    bool redirect2 = 0;
    std::size_t found3 = command.find('<');
    if (found3!=std::string::npos){
        if (found3 < command.size() - 2 && command.at(found3+1) == ' ' && command.at(found3-1) == ' '){
            redirect2 = 1;
            found3--;
            command.erase(found3, 3);
            std::size_t found2 = found3;
            while (found2 != command.size() && command.at(found2) != ' '){
                found2++;
            }
            std::string filename = command.substr(found3, found2-found3);
            command.erase(found3, found2-found3);
            int file = open(filename.c_str(), O_RDONLY);
            close(0);
            dup2(file, 0);
            close(file);
        }
    }
    //---------------------------------output redirect?----------------------------------
    int stdout_copy = dup(1);
    bool redirect = 0;
    std::size_t found = command.find('>');
    if (found!=std::string::npos){
        if (found < command.size() - 2 && command.at(found+1) == ' ' && command.at(found-1) == ' '){
            redirect = 1;
            command.erase(found, 2);
            std::string filename = command.substr(found, command.size()-found);
            command.erase(found-1, command.size()-found+1);
            std::fstream files;
            files.open(filename.c_str(), std::ios::out);
            files.close();
            int file = open(filename.c_str(), O_WRONLY);
            close(1);
            dup2(file, 1);
            close(file);
        }
        else if(found < command.size() - 3 && command.at(found+1) == '>' && command.at(found-1) == ' ' &&
            command.at(found+2) == ' ') {
            redirect = 1;
            command.erase(found, 3);
            std::string filename = command.substr(found, command.size()-found);
            command.erase(found, command.size()-found);
            std::ifstream files;
            files.open(filename.c_str());
            std::string temps;
            std::string tempstr;
            while (getline(files, tempstr)){
                temps += tempstr;
            }
            files.close();
            std::fstream files2;
            files2.open(filename.c_str(), std::ios::out);
            files2.close();
            int file = open(filename.c_str(), O_WRONLY);
            close(1);
            dup2(file, 1);
            close(file);
            std::cout << temps.c_str() << std::endl;
        }
    }
    if (command.at(0) == '['){
        unsigned temp = command.find(']');
        if (temp != command.size() - 1){ // ']' is not add the end of the single command
            printf("syntax error\n");
                   return;
        }          //new testExct
        excommand = new testExct(command.substr(1, temp-2));
        excommand->execute();
        flag = excommand->getFlag();
        return;
    }
    std::string commandCheck; //creates substring out of first 4 characters and checks if it says exit
    if (command.size() > 3){
        commandCheck = command.substr(0,4);
        for (int i = 0; i < 4; i++){
            if (commandCheck.at(i) > 64 && commandCheck.at(i) < 91){
                commandCheck.at(i)+=32;
            }
        }
    }
	if(commandCheck == "exit")   //command is exit
	{
        if (command.size() == 4 || command.at(4) == ';' || command.at(4) == ' '){ //command is either "exit", "exit;" or "exit (insert anything here)", in all cases it should exit
	   
            excommand = new exitExct(command);
		excommand->execute();
	    flag = excommand->getFlag();
            return;
        }
        else {
            excommand = new shExct(command); //first 4 letters were exit but it was a larger word, for example: $ exitdude
            excommand->execute();
            flag = excommand->getFlag();
            if (redirect){
                dup2(stdout_copy, 1);
                close(stdout_copy);
            }
            if (redirect2){
                dup2(stdin_copy, 0);
                close(stdin_copy);
            }
            return;
        }
	}
    else if (commandCheck == "test" && command.size() > 4 && command.at(4) == ' '){
        //NEW testExct
        excommand = new testExct(command.substr(4, command.size() - 4));
        excommand->execute();
        flag = excommand->getFlag();
        if (redirect){
            dup2(stdout_copy, 1);
            close(stdout_copy);
        }
        if (redirect2){
            dup2(stdin_copy, 0);
            close(stdin_copy);
        }
        return;
    }
	else// if command in /bin/
	{
        excommand = new shExct(command);
        excommand->execute();
        flag = excommand->getFlag();
        if (redirect){
            dup2(stdout_copy, 1);
            close(stdout_copy);
        }
        if (redirect2){
            dup2(stdin_copy, 0);
            close(stdin_copy);
        }
        return;
	}
    if (redirect){
        dup2(stdout_copy, 1);
        close(stdout_copy);
    }
    if (redirect2){
        dup2(stdin_copy, 0);
        close(stdin_copy);
    }
    flag = excommand->getFlag();
    return;
}
std::string OriginalClass::getCmd(){ //gets command from user
    std::string str;
    std::getline(std::cin, str);
    command = str;
    return command;
}
void OriginalClass::execute(int& flag, int& test){
    child1->execute(flag, test);
    return;
}
CommandComponent* CommandComposite::buildTree(int &x){ //this builds a tree of commands by serperating the string into pieces based on opperators
    
    if (x == 0){
        
        while (command.size() != 0 && command.at(0) == ' '){ //REMOVE ANY EXTRA SPACES BEFORE COMMAND
            command.erase(0,1);
        }
        while (command.size() != 0 && command.at(command.size() - 1) == ' '){ //REMOVE ANY EXTRA SPACES BEFORE COMMAND
            command.erase(command.size()-1,1);
        }
        if (command.size() == 0){
            x = 2;
            return NULL;
        }
        
        
        //list of variables used for parsing command and what they do:
        //-----------------------------------------------------------------------------------------------------------
        bool quotes = 0;   //found a " character, this stays equal to 1 until another " is found,
        bool foundOr = 0;  //found | last pass through loop, if found again then it is an || operator
        bool foundAnd = 0; //found & last pass through loop, if found again then it is an && operator
        bool foundspace = 0; //found a space in the last character, opperators can only be found when this = 1
        int foundParentheses = 0; //counts openned parentheses
        int foundParentheses2 = 0; //counts closed parentheses
        bool parenFlag = 0; //found even parentheses, created parentheses object
        unsigned j = 0; //loop variable, used when first character is '(' to start the loop at 1 instead of 0
        CommandComponent* temp; //temporary command component, stores parentheses while loop searches for an opperator
        //-----------------------------------------------------------------------------------------------------------
        
        
        if (command.at(0) == '('){
            foundParentheses++;
            j++;
        }
        if (command.at(0) == '#'){
            std::string nocommand = " "; //NEW COMMENT OBJECT, this happens twice to allow for comments like this: $#comment
            CommandComponent* obj = new Comment(nocommand,0);
            obj->child1 = obj->buildTree(x);
            return obj;
        }
        for (unsigned i = j; i < command.size(); i++){ //checks for opperators
            if (foundParentheses > 0){
                if (command.at(i) == '#'){
                    if (i == 1 || command.at(i-1) == ' '){
                        //error uneven parentheses, a # was found before parentheses were closed, meaning they must be open
                        x = 1;
                        return NULL;
                    }
                }
                if (command.at(i) == '('){ //found openning parentheses
                    foundParentheses++;
                }
                if (command.at(i) == ')'){ //found closing parentheses
                    foundParentheses2++;
                    if (foundParentheses == foundParentheses2){ //checks if number of openned and closed parentheses are equal
                        if (i == 1){
                            foundParentheses = 0;
                            foundParentheses2 = 0;
                            //error, user inputed () with nothing inside, we may not need to add anything in here
                        }
                        else {
                            temp = new Parentheses(command.substr(1, i-1),1); // NEW PARENTHESES OBJECT
                            temp->child1 = temp->buildTree(x);
                            parenFlag = 1;
                            foundParentheses = 0;
                            foundParentheses2 = 0;
                        }
                    }
                }
                if (i == command.size() - 1 && (foundParentheses2 != foundParentheses)){ //i went through entire string, even set of parentheses not found
                    //error uneven parentheses
                    x = 1;
                }
            }
            else {
                if (foundspace){
                    foundspace = 0;
                    if (command.at(i) == '|'){
                        foundOr = 1;
                    }
                    else if (command.at(i) == '&'){
                        foundAnd = 1;
                    }
                    else if (command.at(i) == '#'){    //NEW COMMENT OBJECT
                        if (parenFlag){ //parentheses were found, using contents of parentheses as the child
                            CommandComponent* obj = new Comment("\0",0);
                            obj->child1 = temp;
                            return obj;
                        }
                        else{
                            std::string cmd = command.substr(0, i-1);
                            while ((cmd.size() > 0) && (cmd.at(0) == ' ')){ //removes any spaces before the command's first letter
                                cmd.erase(0,1);
                            }
                            CommandComponent* obj = new Comment(cmd,0);
                            obj->child1 = obj->buildTree(x);
                            return obj;
                        }
                    }
                    else if (command.at(i) == ' '){
                        foundspace = 1;
                    }
                    else if (command.at(i) == '\"'){
                        if (i != 0){
                            if (command.at(i-1) != '\\'){
                                quotes = !quotes;
                            }
                        }
                        else {
                            quotes = !quotes;
                        }
                    }
                }
                else if (foundOr){
                    if (command.at(i) == '|'){   //NEW OR OBJECT
                        if (i > command.size() - 2){
                            x = 3;
                            return NULL;
                        }
                        if (parenFlag){ //parentheses were found, using contents of parentheses as the first child
                            std::string cmd2 = command.substr(i+2, command.size() - (i+2));
                            CommandComposite* obj = new Or(cmd2,1);
                            obj->child1 = temp;
                            obj->child2 = obj->buildTree(x);
                            return obj;
                        }
                        else {
                            std::string cmd = command.substr(0, i-2);
                            while ((cmd.size() > 0) && (cmd.at(0) == ' ')){ //removes any spaces before the command's first letter
                                cmd.erase(0,1);
                            }
                            std::string cmd2 = command.substr(i+2, command.size() - (i+2));
                            CommandComposite* obj = new Or(cmd2,1);
                            obj->child1 = new SingleCommand(cmd,0);
                            obj->child2 = obj->buildTree(x);
                            return obj;
                        }
                    }
                    else if (command.at(i) == ' '){ //NEW PIPE OBJECT
                        if (parenFlag){ //parentheses were found, using contents of parentheses as the first child
                            std::string cmd2 = command.substr(i+2, command.size() - (i+2));
                            CommandComposite* obj = new Pipe(cmd2,1);
                            obj->child1 = temp;
                            obj->child2 = obj->buildTree(x);
                            return obj;
                        }
                        else {
                            std::string cmd = command.substr(0, i-2);
                            while ((cmd.size() > 0) && (cmd.at(0) == ' ')){ //removes any spaces before the command's first letter
                                cmd.erase(0,1);
                            }
                            std::string cmd2 = command.substr(i+1, command.size() - (i+1));
                            CommandComposite* obj = new Pipe(cmd2,1);
                            obj->child1 = new SingleCommand(cmd,0);
                            obj->child2 = obj->buildTree(x);
                            return obj;
                        }
                    }
                    foundOr = 0;
                }
                else if (foundAnd){
                    if (command.at(i) == '&'){        //NEW AND OBJECT
                        if (i > command.size() - 2){
                            x = 3;
                            return NULL;
                        }
                        if (parenFlag){ //parentheses were found, using contents of parentheses as the first child
                            std::string cmd2 = command.substr(i+2, command.size() - (i+2));
                            CommandComposite* obj = new And(cmd2,1);
                            obj->child1 = temp;
                            obj->child2 = obj->buildTree(x);
                            return obj;
                        }
                        else {
                            std::string cmd = command.substr(0, i-2);
                            while ((cmd.size() > 0) && (cmd.at(0) == ' ')){ //removes any spaces before the command's first letter
                                cmd.erase(0,1);
                            }
                            std::string cmd2 = command.substr(i+2, command.size() - (i+2));
                            CommandComposite* obj = new And(cmd2,1);
                            obj->child1 = new SingleCommand(cmd,0);
                            obj->child2 = obj->buildTree(x);
                            return obj;
                        }
                    }
                    foundAnd = 0;
                }
                if (!quotes){
                    if (command.at(i) == ' '){
                        foundspace = 1;
                    }
                    else if (command.at(i) == ';'){         //NEW ALWAYS OBJECT
                        if (i != command.size()-1 && i != command.size()-2){
                            if (parenFlag){ //parentheses were found, using contents of parentheses as the first child
                                std::string cmd2 = command.substr(i+2, command.size() - (i+2));
                                CommandComposite* obj = new Always(cmd2,1);
                                obj->child1 = temp;
                                obj->child2 = obj->buildTree(x);
                                return obj;
                            }
                            else{
                                std::string cmd = command.substr(0, i);
                                while ((cmd.size() > 0) && (cmd.at(0) == ' ')){ //removes any spaces before the command's first letter
                                    cmd.erase(0,1);
                                }
                                std::string cmd2 = command.substr(i+1, command.size() - (i+1));
                                CommandComposite* obj = new Always(cmd2,1);
                                obj->child1 = new SingleCommand(cmd,0);
                                obj->child2 = obj->buildTree(x);
                                return obj;
                            }
                        }
                        else {
                            if (parenFlag){ //parentheses were found, using contents of parentheses as the command
                                return temp;
                            }
                            while ((command.size() > 0) && (command.at(0) == ' ')){ //removes any spaces before the command's first letter
                                command.erase(0,1);
                                i--;
                            }
                            return new SingleCommand(command.substr(0, i),0);
                        }
                    }
                }
            }
        }
        if (parenFlag){ //parentheses were found, using contents of parentheses as the command
            if (command.at(command.size()-1) != ')'){
                while (command.at(command.size()-1) == ' '){
                    command.erase(command.at(command.size() - 1), 1);
                }
            }
            if (command.at(command.size()-1) == ')'){
                return temp;
            }
            else {
                x = 4;
                return NULL;
            }
        }
        while ((command.size() > 0) && (command.at(0) == ' ')){ //removes any spaces before the command's first letter
            command.erase(0,1);
        }
        return new SingleCommand(command,0);
    }
    return NULL;
}

//--------------PIPE COMMAND CODE (make sure to copy when the original code is changed)----------------------------------

CommandComponent* PipeCommand::buildTree(int &x){
    return (NULL);
}
void PipeCommand::execute(int& flag, int& test){
    return;
}
void PipeCommand::execute(int& flag, int& test, int ptype, int cmdpipe[2]){
    if (flag != test) return;
    Exct* excommand;
    while (command.size() != 0 && command.at(0) == ' '){
        command.erase(0, 1);
    }
    while (command.size() != 0 && command.at(command.size()-1) == ' '){
        command.erase(command.size()-1, 1);
    }
    if (command.at(0) == '['){
        unsigned temp = command.find(']');
        if (temp != command.size() - 1){ // ']' is not add the end of the single command
            int temp2 = 0;
            for (unsigned i = temp; i < command.size(); i++){ //temp2 stays 0 if the only thing after ']; is spaces
                if (command.at(i) != ' '){
                    temp2 = 1;
                }
            }
            if (temp2 == 1){ //if temp2 = 1 (something like $ [ ... ] ls, then syntax error
                printf("syntax error\n");
                return;
            }
        }          //new testExct
        excommand = new testExct(command.substr(1, temp-2));
        excommand->execute();
        flag = excommand->getFlag();
        return;
    }
    std::string commandCheck; //creates substring out of first 4 characters and checks if it says exit
    if (command.size() > 3){
        commandCheck = command.substr(0,4);
        for (int i = 0; i < 4; i++){
            if (commandCheck.at(i) > 64 && commandCheck.at(i) < 91){
                commandCheck.at(i)+=32;
            }
        }
    }
    if(commandCheck == "exit")   //command is exit
    {
        if (command.size() == 4 || command.at(4) == ';' || command.at(4) == ' '){ //command is either "exit", "exit;" or "exit (insert anything here)", in all cases it should exit
            
            excommand = new exitExct(command);
            excommand->execute();
            flag = excommand->getFlag();
            return;
        }
        else {
            excommand = new PipeExct(command); //first 4 letters were exit but it was a larger word, for example: $ exitdude
            excommand->execute();
            flag = excommand->getFlag();
            return;
        }
    }
    else if (commandCheck == "test" && command.size() > 4 && command.at(4) == ' '){
        //NEW testExct
        excommand = new testExct(command.substr(4, command.size() - 4));
        excommand->execute();
        flag = excommand->getFlag();
        return;
    }
    else// if command in /bin/
    {
        excommand = new PipeExct(command);
        excommand->execute(ptype, (&cmdpipe)[2]);
        flag = excommand->getFlag();
        return;
    }
    flag = excommand->getFlag();
    return;
}

CommandComponent* Pipe::buildTree(int &x){ //this builds a tree of commands by serperating the string into pieces based on opperators
    
    if (x == 0){
        
        while (command.size() != 0 && command.at(0) == ' '){ //REMOVE ANY EXTRA SPACES BEFORE COMMAND
            command.erase(0,1);
        }
        while (command.size() != 0 && command.at(command.size() - 1) == ' '){ //REMOVE ANY EXTRA SPACES BEFORE COMMAND
            command.erase(command.size()-1,1);
        }
        if (command.size() == 0){
            x = 2;
            return NULL;
        }
        
        
        //list of variables used for parsing command and what they do:
        //-----------------------------------------------------------------------------------------------------------
        bool quotes = 0;   //found a " character, this stays equal to 1 until another " is found,
        bool foundOr = 0;  //found | last pass through loop, if found again then it is an || operator
        bool foundAnd = 0; //found & last pass through loop, if found again then it is an && operator
        bool foundspace = 0; //found a space in the last character, opperators can only be found when this = 1
        int foundParentheses = 0; //counts openned parentheses
        int foundParentheses2 = 0; //counts closed parentheses
        bool parenFlag = 0; //found even parentheses, created parentheses object
        unsigned j = 0; //loop variable, used when first character is '(' to start the loop at 1 instead of 0
        CommandComponent* temp; //temporary command component, stores parentheses while loop searches for an opperator
        //-----------------------------------------------------------------------------------------------------------
        
        
        if (command.at(0) == '('){
            foundParentheses++;
            j++;
        }
        if (command.at(0) == '#'){
            std::string nocommand = " "; //NEW COMMENT OBJECT, this happens twice to allow for comments like this: $#comment
            CommandComponent* obj = new Comment(nocommand,0);
            obj->child1 = obj->buildTree(x);
            return obj;
        }
        for (unsigned i = j; i < command.size(); i++){ //checks for opperators
            if (foundParentheses > 0){
                if (command.at(i) == '#'){
                    if (i == 1 || command.at(i-1) == ' '){
                        //error uneven parentheses, a # was found before parentheses were closed, meaning they must be open
                        x = 1;
                        return NULL;
                    }
                }
                if (command.at(i) == '('){ //found openning parentheses
                    foundParentheses++;
                }
                if (command.at(i) == ')'){ //found closing parentheses
                    foundParentheses2++;
                    if (foundParentheses == foundParentheses2){ //checks if number of openned and closed parentheses are equal
                        if (i == 1){
                            foundParentheses = 0;
                            foundParentheses2 = 0;
                            //error, user inputed () with nothing inside, we may not need to add anything in here
                        }
                        else {
                            temp = new Parentheses(command.substr(1, i-1),1); // NEW PARENTHESES OBJECT
                            temp->child1 = temp->buildTree(x);
                            parenFlag = 1;
                            foundParentheses = 0;
                            foundParentheses2 = 0;
                        }
                    }
                }
                if (i == command.size() - 1 && (foundParentheses2 != foundParentheses)){ //i went through entire string, even set of parentheses not found
                    //error uneven parentheses
                    x = 1;
                }
            }
            else {
                if (foundspace){
                    foundspace = 0;
                    if (command.at(i) == '|'){
                        foundOr = 1;
                    }
                    else if (command.at(i) == '&'){
                        foundAnd = 1;
                    }
                    else if (command.at(i) == '#'){    //NEW COMMENT OBJECT
                        if (parenFlag){ //parentheses were found, using contents of parentheses as the child
                            CommandComponent* obj = new Comment("\0",0);
                            obj->child1 = temp;
                            return obj;
                        }
                        else{
                            std::string cmd = command.substr(0, i-1);
                            while ((cmd.size() > 0) && (cmd.at(0) == ' ')){ //removes any spaces before the command's first letter
                                cmd.erase(0,1);
                            }
                            CommandComponent* obj = new Comment(cmd,0);
                            obj->child1 = obj->buildTree(x);
                            return obj;
                        }
                    }
                    else if (command.at(i) == ' '){
                        foundspace = 1;
                    }
                    else if (command.at(i) == '\"'){
                        if (i != 0){
                            if (command.at(i-1) != '\\'){
                                quotes = !quotes;
                            }
                        }
                        else {
                            quotes = !quotes;
                        }
                    }
                }
                else if (foundOr){
                    if (command.at(i) == '|'){   //NEW OR OBJECT
                        if (i > command.size() - 2){
                            x = 3;
                            return NULL;
                        }
                        if (parenFlag){ //parentheses were found, using contents of parentheses as the first child
                            std::string cmd2 = command.substr(i+2, command.size() - (i+2));
                            CommandComposite* obj = new Or(cmd2,1);
                            obj->child1 = temp;
                            obj->child2 = obj->buildTree(x);
                            return obj;
                        }
                        else {
                            std::string cmd = command.substr(0, i-2);
                            while ((cmd.size() > 0) && (cmd.at(0) == ' ')){ //removes any spaces before the command's first letter
                                cmd.erase(0,1);
                            }
                            std::string cmd2 = command.substr(i+2, command.size() - (i+2));
                            CommandComposite* obj = new Or(cmd2,1);
                            obj->child1 = new PipeCommand(cmd,0);
                            obj->child2 = obj->buildTree(x);
                            return obj;
                        }
                    }
                    else if (command.at(i) == ' '){ //NEW PIPE OBJECT
                        if (parenFlag){ //parentheses were found, using contents of parentheses as the first child
                            std::string cmd2 = command.substr(i+2, command.size() - (i+2));
                            CommandComposite* obj = new Pipe(cmd2,1);
                            obj->child1 = temp;
                            obj->child2 = obj->buildTree(x);
                            return obj;
                        }
                        else {
                            std::string cmd = command.substr(0, i-2);
                            while ((cmd.size() > 0) && (cmd.at(0) == ' ')){ //removes any spaces before the command's first letter
                                cmd.erase(0,1);
                            }
                            std::string cmd2 = command.substr(i+1, command.size() - (i+1));
                            CommandComposite* obj = new Pipe(cmd2,1);
                            obj->child1 = new PipeCommand(cmd,0);
                            obj->child2 = obj->buildTree(x);
                            return obj;
                        }
                    }
                    foundOr = 0;
                }
                else if (foundAnd){
                    if (command.at(i) == '&'){        //NEW AND OBJECT
                        if (i > command.size() - 2){
                            x = 3;
                            return NULL;
                        }
                        if (parenFlag){ //parentheses were found, using contents of parentheses as the first child
                            std::string cmd2 = command.substr(i+2, command.size() - (i+2));
                            CommandComposite* obj = new And(cmd2,1);
                            obj->child1 = temp;
                            obj->child2 = obj->buildTree(x);
                            return obj;
                        }
                        else {
                            std::string cmd = command.substr(0, i-2);
                            while ((cmd.size() > 0) && (cmd.at(0) == ' ')){ //removes any spaces before the command's first letter
                                cmd.erase(0,1);
                            }
                            std::string cmd2 = command.substr(i+2, command.size() - (i+2));
                            CommandComposite* obj = new And(cmd2,1);
                            obj->child1 = new PipeCommand(cmd,0);
                            obj->child2 = obj->buildTree(x);
                            return obj;
                        }
                    }
                    foundAnd = 0;
                }
                if (!quotes){
                    if (command.at(i) == ' '){
                        foundspace = 1;
                    }
                    else if (command.at(i) == ';'){         //NEW ALWAYS OBJECT
                        if (i != command.size()-1 && i != command.size()-2){
                            if (parenFlag){ //parentheses were found, using contents of parentheses as the first child
                                std::string cmd2 = command.substr(i+2, command.size() - (i+2));
                                CommandComposite* obj = new Always(cmd2,1);
                                obj->child1 = temp;
                                obj->child2 = obj->buildTree(x);
                                return obj;
                            }
                            else{
                                std::string cmd = command.substr(0, i);
                                while ((cmd.size() > 0) && (cmd.at(0) == ' ')){ //removes any spaces before the command's first letter
                                    cmd.erase(0,1);
                                }
                                std::string cmd2 = command.substr(i+1, command.size() - (i+1));
                                CommandComposite* obj = new Always(cmd2,1);
                                obj->child1 = new PipeCommand(cmd,0);
                                obj->child2 = obj->buildTree(x);
                                return obj;
                            }
                        }
                        else {
                            if (parenFlag){ //parentheses were found, using contents of parentheses as the command
                                return temp;
                            }
                            while ((command.size() > 0) && (command.at(0) == ' ')){ //removes any spaces before the command's first letter
                                command.erase(0,1);
                                i--;
                            }
                            return new PipeCommand(command.substr(0, i),0);
                        }
                    }
                }
            }
        }
        if (parenFlag){ //parentheses were found, using contents of parentheses as the command
            if (command.at(command.size()-1) != ')'){
                while (command.at(command.size()-1) == ' '){
                    command.erase(command.at(command.size() - 1), 1);
                }
            }
            if (command.at(command.size()-1) == ')'){
                return temp;
            }
            else {
                x = 4;
                return NULL;
            }
        }
        while ((command.size() > 0) && (command.at(0) == ' ')){ //removes any spaces before the command's first letter
            command.erase(0,1);
        }
        return new PipeCommand(command,0);
    }
    return NULL;
}


