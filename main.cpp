#include<bits/stdc++.h>
#include <iostream>
#include <cstring>
#include <cstdlib>
#include <fstream>
#include <sstream>
#include <locale>
#include <assert.h>
#include <stdio.h>
#include <wchar.h>
#include <vector>

using namespace std;


struct event {
	string SeqNumber;
	string EventSource;
	string SampleName;
	string Timestamp;
	string MediaTime;
	vector<string> raw_data; 
};


void print_info(vector<event> &events){
	for(int i=0; i<events.size(); i++){
		cout<<"seqNumber: "<<events[i].SeqNumber<<"\t";
		cout<<"Event Source: "<<events[i].EventSource<<"\t";
		cout<<"Sample Name: "<<events[i].SampleName<<"\t";
		cout<<"Time stamp: "<<events[i].Timestamp<<"\t";
		cout<<"MediaTime: "<<events[i].MediaTime<<"\t";
		cout<<"raw data: ";
		for(int j=0; j<events[i].raw_data.size(); j++){
			cout<<events[i].raw_data[j]<<" ";
		}
		cout<<endl;
	}
	cout<<endl;
}


string seqrate_word(int& i, string temp_string){
	string temp = "";

	while(i < temp_string.length() && temp_string[i] != ';'){
		temp += temp_string[i];
		i++;
	}
	return temp;
}


void load_raw_data(int& i, vector<event> &events, string temp_string, int count){
	string temp = "";
	
	while(i < temp_string.length() && temp_string[i] != ';'){
		temp = seqrate_word(i, temp_string);
		events[count].raw_data.push_back(temp);
		i++;
	}

}


void load_info(vector<event> &events, string temp_string, int count){

	string temp = "";
	int i = 0;

	vector<string> raw_data_info;

	//while(i < temp_string.length() || temp_string[i] != ';'){
		// seqNumber
		temp = seqrate_word(i, temp_string);
		events.push_back(event());
		events[count].SeqNumber = temp;
		i++;

		// event source
		temp = seqrate_word(i, temp_string);
		events[count].EventSource = temp;
		i++;

		// SampleName
		temp = seqrate_word(i, temp_string);
		events[count].SampleName = temp;
		i++;

		// Timestamp
		temp = seqrate_word(i, temp_string);
		events[count].Timestamp = temp;
		i++;

		//MediaTime
		temp = seqrate_word(i, temp_string);
		events[count].MediaTime = temp;
		i++;

		//events[count].raw_data = 
		load_raw_data(i, events, temp_string, count);
	//}
	


}




int main(int argc, char **argv)
{

	ifstream read;
	string temp_string;

	vector<event> events;
	int count;

	
	if(argc == 2){

		read.open(argv[1]);
		if(read.is_open()){

			while(getline(read,temp_string)){
				//events = 
				load_info(events,temp_string, count);
				
				count ++;
			}
		}
	}else{
		cout<<"error for reading file"<<endl;
		return 0;
	}

	read.close();

	print_info(events);
	


	return 0;
}
