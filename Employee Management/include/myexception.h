#ifndef excep_flag
#define excep_flag

#include<iostream>
#include <string>

class MyException {
private:
	std::string message;

public:
	MyException(std::string str = { "Something went wrong" }) :message{ str } {	}

	virtual void what() {
		std::cout << message;
	}

	virtual ~MyException() = default;

};

class FileException :public MyException {

public:
	FileException(std::string str) :MyException{ str } {	}
};
#endif