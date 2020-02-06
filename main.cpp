#include <iostream>
#include <cstring>
#include <cstdlib>
#include <fstream>
#include <codecvt>
#include <sstream>
#include <locale>
#include <assert.h>
#include <stdio.h>
#include <wchar.h>

#include "readCommonEvent.h"

using namespace std;


int main(int argc, char **argv)
{

	char* get_filename = new char[256];
	ifstream read;
	string temp_string;
	struct head = NULL;
	
	if(argc == 2){
		if(read.is_open()){
			while(getline(read,temp_string)){
				head = add_node(head,temp_string);
			}
		}
	}else{
		cout<<"error for reading file"<<endl;
		return 0;
	}
	


	return 0;
}
