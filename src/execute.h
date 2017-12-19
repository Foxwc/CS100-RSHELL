#ifndef _EXCT_H_
#define _EXCT_H_
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
class Exct {
protected:
	std::string command;
	int flag;
public:
	Exct(std::string in_command);
	~Exct();
	virtual int execute() = 0;
    virtual int execute(int ptype, int cmdpipe[2]){return 0;}
	virtual int getFlag() = 0;
};

class shExct:public Exct {
public: 
	shExct(std::string in_command);
	int execute();
	int getFlag();
};

class PipeExct:public Exct {
public:
    PipeExct(std::string in_command);
    int execute(int ptype, int cmdpipe[2]);
    int execute(){return 0;}
    int getFlag();
};

class exitExct:public Exct {
public:
	exitExct(std::string in_command);
	int execute();
	int getFlag();
};

class testExct:public Exct {
public:
	testExct(std::string in_command);
	int execute();
	int getFlag();
};
#endif
