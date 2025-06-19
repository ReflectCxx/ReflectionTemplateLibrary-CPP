
#include "Singleton.h"

Singleton::Singleton()
{

}

Singleton::~Singleton()
{

}

const Singleton& Singleton::getInstance()
{
	static Singleton instance;
	return instance;
}


std::string Singleton::getHelloString() const
{
	return HELLO_STR;
}