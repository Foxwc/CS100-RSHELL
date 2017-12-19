#ifndef _COMPONENT_H_
#define _COMPONENT_H_
#include <string>
class CommandComponent{
protected:
	//std::string command;
public:
    int hasChild;
    CommandComponent* child1;
    CommandComponent* child2;
	std::string command;
    CommandComponent() {}
    virtual CommandComponent* buildTree(int &x) = 0;
    CommandComponent(std::string in_command,int childflag);
	~CommandComponent();
	virtual void execute(int& flag, int& test) = 0;
    virtual void execute(int& flag, int& test, int ptype, int cmdpipe[2]){return;}
};

class SingleCommand:public CommandComponent{
public:
    	CommandComponent* buildTree(int &x);
	SingleCommand(std::string in_command,int childflag):CommandComponent(in_command,childflag){}
	void execute(int& flag, int& test);
};
class PipeCommand:public CommandComponent{
public:
    CommandComponent* buildTree(int &x);
    PipeCommand(std::string in_command,int childflag):CommandComponent(in_command,childflag){}
    void execute(int& flag, int& test);
    void execute(int& flag, int& test, int ptype, int cmdpipe[2]);
};
class CommandComposite:public CommandComponent{
public:
    CommandComposite(std::string in_command,int childflag):CommandComponent(in_command,childflag){}
	CommandComponent* buildTree(int &x);
};

class OriginalClass:public CommandComposite{
public:
    OriginalClass(std::string in_command,int childflag):CommandComposite(in_command,childflag){}
    std::string getCmd();
    void execute(int& flag, int& test);
};
#endif
