#pragma once

class Abstract 
{
public:
	
	virtual ~Abstract() = 0 { }
	
	void reset() {

	}

	static Abstract* create();
};

class AbstractNode : public Abstract 
{
};

Abstract* Abstract::create() {
	return new AbstractNode();
}
