#ifndef _CONNECTOR_H_
#define _CONNECTOR_H_
#include "component.h"
class Always:public CommandComposite {
public:
    Always(std::string in_command,int childflag):CommandComposite(in_command,childflag){}
    void execute(int& flag, int& test);
};

class And:public CommandComposite {
public:
    And(std::string in_command,int childflag):CommandComposite(in_command,childflag){}
    void execute(int& flag, int& test);
};

class Or:public CommandComposite {
public:
    Or(std::string in_command,int childflag):CommandComposite(in_command,childflag){}
    void execute(int& flag, int& test);
};

class Comment:public CommandComposite {
public:
    Comment(std::string in_command,int childflag):CommandComposite(in_command,childflag){}
    void execute(int& flag, int& test);
};
class Parentheses:public CommandComposite {
public:
    Parentheses(std::string in_command,int childflag):CommandComposite(in_command,childflag){}
    void execute(int& flag, int& test);
};
class Pipe:public CommandComposite {
public:
CommandComponent* buildTree(int &x);
Pipe(std::string in_command,int childflag):CommandComposite(in_command,childflag){}
void execute(int& flag, int& test);
};
#endif
