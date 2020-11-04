#include<iostream>
#include<string.h>
#include<cstdlib>
#include<fstream>
#include<algorithm>
#include<vector>
#include<sstream>
#include<type_traits>
#include<ctype.h>
#include<chrono>

#include"hotelfinder.h"

using namespace std;

int main(int argc, char* const argv[]){
	ifstream inFile;
	int hotel_num=0;
	int capacity=0;
	bool input_provided=false;
	bool num_price=true;
	bool num_stars=true;
	string hotel,city,stars,price,country,address,line,filename,outfile,info,action,action_num;
	vector<string> lineinfo;
	vector<string> hotel_info;
	vector<HotelNode>DumpVect;
		for(int i=0;i<argc;i++) //processing command line args
			{
				if (strcmp(argv[i], "-f") == 0){ //if -f is found
					if(argv[i+1]!=""){ //if arg after is not nothing nor blank space
						filename=argv[i+1]; 
						input_provided=true;
					}
					else{
						input_provided=false; //ater looping through all of commandline, if -f missing or arg after -f missing, no input is provided
					}
				} 
			}
		if(!input_provided){ //if input file not supplied
			cout<<endl<<"Please provide an input file else program cannot run"<<endl;
			exit(1);
		}
		inFile.open(filename); //after filename provided, open the file
		if(inFile.is_open()){ //going through number of hotels in text file to find capacity of mainmap and city map
			getline(inFile,line);//skips first line
			while(!inFile.eof()){ //Continuing until end of file 
				getline(inFile,line);
				hotel_num++; //counter to track how many hotels are in file
			}
			capacity=(hotel_num*1.4); //creating capacity of mainmap to be 40% bigger than # of elements
		}
		HotelMap MainMap(capacity);
		HotelMap CityMap(capacity);
		inFile.seekg(0, ios::beg); //go back to beginning of file
		if(inFile.is_open()){ 
		getline(inFile,line);//skip first line
		if(line=="") {}; //if line is blank, skip it
		line.erase(remove(line.begin(), line.end(), ' '), line.end()); //ignore whitespace when reading lines in input file	
		while(!inFile.eof()){ //Continuing until end of file 
			getline(inFile,line);
			stringstream ss; //declare stringstream as new variable at each line
			ss.str(string()); //reset string stream
			ss.clear();
			cout<<"line: "<<line<<endl;
			ss<<line;
			string str_line = ss.str();
			while(getline(ss, info,',')){lineinfo.push_back(info);}
			string htl=lineinfo[0];
			for(int i=0;i<htl.size();i++){ //function to save hotel and city name in lower case
				htl[i]=tolower(htl[i]);
			}
			string cty=lineinfo[1];
			for(int i=0;i<cty.size();i++){
				cty[i]=tolower(cty[i]);
			}
			lineinfo[0]=htl;
			lineinfo[1]=cty;
			HotelNode* nhot=new HotelNode(lineinfo[0],lineinfo[1],lineinfo[2],lineinfo[3],lineinfo[4],lineinfo[5]); //Loads information from line
			HotelNode* nhot2=new HotelNode(lineinfo[0],lineinfo[1],lineinfo[2],lineinfo[3],lineinfo[4],lineinfo[5]);
			MainMap.insert(nhot); //Adds Node to MainMap
			CityMap.insert2(nhot2); //Adds Node to CityMap
			DumpVect.push_back(*nhot); //Vector to Dump 
			lineinfo.clear(); //resetting vector	
		}
	}
		else{ //if infile not open, terminate program after telling user it is closed
			cout<<"Provided file is not open"<<endl<<"Program cannot execute"<<endl;
			exit(1);}

	inFile.close();


	do{ 
		cout<<endl<<"Options: "<<endl
		<<"-> Find hotel, city"<<endl
		<<"-> Add hotel,city,stars,price,country,address"<<endl
		<<"-> Delete hotel, city"<<endl
		<<"-> Dump"<<endl
		<<"-> allinCity city"<<endl
		<<"-> Quit"<<endl<<endl
		<<"-> ";

		getline(cin,action);
		for(int i=0;i<action.size();i++){ //converting all leters to lower case to comapre to action in mainmap inserted as all lowercase
				action[i]=tolower(action[i]);
			}

		if(action.find("find")!=std::string::npos){	//FINDING
			bool input=true;
			int commas=0;
			for(int i=0;i<action.size();i++){
				if(action[i]==',') commas++;
			}
			if(commas!=1) {cout<<"Please use find in the format listed above"<<endl; input=false;}
			while(input){
				int hotel_index=action.find('d');//save index of first 'd' i.e. last index in word 'find' 
				hotel=action.substr(hotel_index+1,action.find(',')-(hotel_index+1));
				city=action.substr(action.find(',')+1,action.size()-(action.find(',')));
				hotel=whitespace(hotel);
				city=whitespace(city);
				//source for auto start, auto stop, auto duration: geeksforgeeks.org/meausure-execution-time-function-cpp/
				auto start=chrono::high_resolution_clock::now(); //check source above for citation
				MainMap.find(hotel,city);
				auto stop=chrono::high_resolution_clock::now(); //check source above for citation
				auto duration=chrono::duration_cast<chrono::microseconds>(stop-start); //check source above for citation
				cout<<endl<<"-> Execution time: "<<duration.count()<<" microseconds"<<endl;
				break;
			}
		}
		else if(action.find("delete")!=std::string::npos){	//DELETING
			bool input=true;
			int commas=0;
			for(int i=0;i<action.size();i++){
				if(action[i]==',') commas++;
			}
			if(commas!=1) {cout<<"Please delete in the format listed above"<<endl; input=false;}
			if(input){
				int hotel_index=action.find('e')+4;//save index of third 'e' i.e. last index in word 'delete' 
				hotel=action.substr(hotel_index+1,action.find(',')-(hotel_index+1));
				city=action.substr(action.find(',')+1,action.size()-(action.find(',')));
				hotel=whitespace(hotel);
				city=whitespace(city);
				MainMap.remove(hotel,city);
				CityMap.remove2(hotel,city);
				//REMOVE FROM VECTOR
				for(vector<HotelNode>::iterator i=DumpVect.begin(); i!=DumpVect.end();i++){
					if((*i).gethtlName()==hotel){
						DumpVect.erase(i);
						break;}
				break;
				
				}
			} 
		}
		else if(action.find("add")!=std::string::npos){	//ADDING
			bool input=true;
			int count=0;
			int commas=0;
			for(int i=0;i<action.size();i++){
				if(action[i]==',') commas++;
			}
			if(commas!=5) {cout<<"Please add in the format listed above"<<endl; input=false;}
			while(input){
				int hotel_index=action.find('d')+1;//save index of second 'd' i.e. last index in word 'add' 
				hotel=action.substr(hotel_index+1,action.find(',')-(hotel_index+1));
				action=action.substr(action.find(',')+1,action.size());
				city=action.substr(0,action.find(','));
				action=action.substr(action.find(',')+1,action.size());
				stars=action.substr(0,action.find(','));
				for(int i=0;i<stars.size();i++){	//error checking if stars is valid form of int or float num
					if(stars[i]=='.'){count++;}
					if(!isdigit(stars[i]) && (stars[i]!='.' || count>1)){
						cout<<"Invalid format. Please eneter stars as a positive number"<<endl;
						input=false;
						break;}

					else{input=true;}	
				}
				if(input == false) break;
				action=action.substr(action.find(',')+1,action.size());
				price=action.substr(0,action.find(','));
				count=0;
				for(int i=0;i<price.size();i++){	//error checking if stars is valid form of int or float num
					if(price[i]=='.'){count++;}
						if(!isdigit(price[i]) && (price[i]!='.' || count>1)){
							cout<<"Invalid format. Please eneter price as a positive number"<<endl;
							input=false;
							break;}
						else{input=true;}
				}
				if(input == false) break;
				action=action.substr(action.find(',')+1,action.size());
				country=action.substr(0,action.find(','));
				action=action.substr(action.find(',')+1,action.size());
				address=action.substr(0,action.size());
				hotel=whitespace(hotel);
				city=whitespace(city);

				//ADDING
				HotelNode* nhot=new HotelNode(hotel,city,stars,price,country,address); //creating node with all inputed data
				HotelNode* nhot2=new HotelNode(hotel,city,stars,price,country,address); //creating node with all inputed data
				MainMap.insert(nhot); //inserted nhot into array of linked lists MainMap
				CityMap.insert2(nhot2);
				hotel_info.clear(); //resetting vector for use again
				DumpVect.push_back(*nhot);
				cout<<"Hotel "<<hotel<<" has been added"<<endl;
				break;
			}
		}
		
		else if(action.find("dump")!=std::string::npos){	//DUMPING
			ofstream outfile("Hotel_Information.txt"); //outfile created
			outfile<<"hotel info goes into outfile alphabetically"<<endl; //hotel info goes into outfile
			sort(DumpVect.begin(),DumpVect.end(),alphabeticComp);
			for(vector<HotelNode>::iterator i=DumpVect.begin(); i!=DumpVect.end();i++){
				outfile<<(*i).printoutfile()<<endl;
			}
			outfile.close(); //outfile closed
			cout<<endl<<"All hotel information has been saved in file: Hotel_Information.txt"<<endl;
		}
		else if(action.find("allincity")!=std::string::npos){ //CITY HOTELS
			int city_index=action.find('y');//save index of first 'd' i.e. last index in word 'find' 
			city=action.substr(city_index+1,action.size()-(city_index));
			city=whitespace(city);
			cout<<endl<<"Searching for hotels in "<<city<<"..."<<endl;
			CityMap.findcity(city);
		}
		else if(action.find("quit")!=std::string::npos){ //TERMINATE PROGRAM
			exit(1);
		}
		else{	//NONE OF SIX CHOICES CHOSEN
			cout<<endl<<"Invalid format"<<endl<<"Please choose a number between 1 to 6."<<endl; //error if one of options not chosen
		}

	}while(action_num!="6"); //while valid option btwn 1 to 6 being chosen
	

	return EXIT_SUCCESS;
}