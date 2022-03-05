// Winston Yi
// wyi10

#include<stdio.h>
#include<fstream>
#include<iostream>
#include"Dictionary.h"


int main(int argc, char* argv[]) {
	std::ifstream in;
	std::ofstream out;
	// check command line for correct number of arguments
    if( argc != 3 ){
        std::cerr << "Usage: " << argv[0] << " <input file> <output file>" << std::endl;
        return(EXIT_FAILURE);
   	}

   	// open files for reading and writing 
   	in.open(argv[1]);
   	if( !in.is_open() ){
    	  std::cerr << "Unable to open file " << argv[1] << " for reading" << std::endl;
      	return(EXIT_FAILURE);
  	 }

   	out.open(argv[2]);
   	if( !out.is_open() ){
    	  std::cerr << "Unable to open file " << argv[2] << " for writing" << std::endl;
      	return(EXIT_FAILURE);
   	}
    Dictionary D;
    int i = 1;
    std::string s;
    std::getline(in, s);
    while (in) {
        D.setValue(s, i);
        i += 1;
        std::getline(in, s);
    }
    out << D << std::endl;
    printf("\n");
    std::string pre = D.pre_string();
    out << pre << std::endl;
}
