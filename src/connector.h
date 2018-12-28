#ifndef CONNECTOR_H
#define CONNECTOR_H

#include "base.h"

class ConnectorBase : public Base {
protected:
	Base* cmd;
	bool skipNext;

public:
	ConnectorBase() {};
	ConnectorBase(Base* c) : cmd(c) {};
	
	virtual int execute() = 0;

};

class And : public ConnectorBase {

public:
	
	And() {};
	And(Base* c) : ConnectorBase(c) {};

	int execute() {
		return cmd->execute();
	}

};

class Or : public ConnectorBase {

public:
	
	Or() {};
	Or(Base* c) : ConnectorBase(c) {};

	int execute() {
		return cmd->execute();
	}


};

#endif

