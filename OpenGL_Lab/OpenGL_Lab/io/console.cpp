
#include "console.h"
#include <iostream>

std::map<std::string, std::string> io::Console::params_ ;

void io::Console::readArgs(int argc, char* argv[]){

	if(argc > 1){
		for(int i = 1; i < argc - 1; i+=2){
			params_[argv[i]] = argv[i+1];
		}
	}
}

std::string io::Console::getParam(const std::string param){
	return params_[param];
}