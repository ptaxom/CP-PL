#include <Windows.h>
#include <iostream>
#include <fstream>
#include <string>

#include "DataBase.h"


int main(int argc, char **argv) {
	try {
		DataBase dataBase(argc, argv);
		dataBase.handle();
	}
	catch (std::runtime_error &ex) {
		std::cout << ex.what()<<std::endl;
	}
}