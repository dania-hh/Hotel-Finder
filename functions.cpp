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
#include<iomanip>

#include"hotelfinder.h"

using namespace std;


HotelNode::HotelNode(HotelNode* n){next=n;}
HotelNode::HotelNode(string h,string cN,string s,string p, string countN, string adrs,HotelNode* n){
	hotelName=h;
	cityName=cN;
	stars=s;
	price=p;
	countryName=countN;
	address=adrs;
	next=n;
}
string HotelNode::gethtlName() {return hotelName;}
string HotelNode::getcityName(){return cityName; }

string HotelNode::printoutfile(){
	string printstring="\n------------HOTEL INFORMATION------------\nHotel Name: "+hotelName+"\nCity Name: "+cityName+"\nStars: "+stars+"\nPrice: "+price+"\nCountry: "+countryName+"\nAddress: "+address;
	return printstring;
}

void HotelNode::print(){
	cout<<setw(42)<<left<<hotelName<<setw(20)<<cityName<<setw(10)<<stars<<setw(15)<<price<<setw(20)<<countryName<<setw(50)<<address<<endl;
}

bool alphabeticComp(HotelNode a, HotelNode b){
	return a.gethtlName()<b.gethtlName();
}

string whitespace(string input){
	if(input[0]==' ' || input[input.size()-1]==' '){ //First or last is " "
			if(input[0]==' ' ){
				input=input.substr(1,input.size()-1); //whitespace at front string
			}
			if(input[input.size()-1]==' '){
				input=input.substr(0,input.size()-1); //whitespace at tail of string
			}
		}
	return input;
}

LinkedList::LinkedList(){
	head=new HotelNode;
	size=0;
}
LinkedList::~LinkedList(){
	while(!empty()){
		removeFront();
	}
	delete head;
}
void LinkedList::removeFront(){
	HotelNode* oldhead=head;
	head=oldhead->next;
	delete oldhead;
}
bool LinkedList::empty(){
	return (head==NULL);
}
int LinkedList::getcitycount(){
	return citycount;
}
bool LinkedList::NodeExists(string htl,string city){ //function used in addnode, if hotel name and city already exist in records, dont add
	HotelNode* cursor;
	cursor=new HotelNode;
	cursor=head;
	bool exists=false;
	while(cursor!=NULL){
		if((*cursor).gethtlName()==htl && (*cursor).getcityName()==city){ 
			exists=true;
			break;
		}
		cursor=cursor->next;
	}
	return exists;
}
void LinkedList::AddNode(HotelNode* hotel){ //Adds to back of the list
	bool exists=NodeExists((*hotel).gethtlName(),(*hotel).getcityName());
	if(exists){
		cout<<"-> Hotel "<<(*hotel).gethtlName()<<" in "<<(*hotel).getcityName()<<" already exits"<<endl;
	}
	else{
		hotel->next=head;
		head=hotel;
		size++;
	}
}
void LinkedList::FindNode(string searchName,string city){
	HotelNode* cursor;
	cursor=new HotelNode;
	cursor=head;
	int traversal_count=0; //counter to keep track of number of nodes searched before finding node (# of comparisons)
	bool found=false;
	while(cursor!=NULL){
		if((*cursor).gethtlName()==searchName && (*cursor).getcityName()==city){ //if node of cursor matches hotel name being searched for, print contents
			cout<<endl<<setw(42)<<left<<"     HOTEL"<<setw(20)<<"CITY"<<setw(10)<<"STARS"<<setw(15)<<"PRICE"<<setw(20)<<" COUNTRY"<<setw(50)<<"  ADDRESS"<<endl;
			cout<<"___________________________________________________________________________________________________________________________________________"<<endl<<endl;
			(*cursor).print();
			cout<<endl<<"-> Number of comparisons before finding hotel: "<<traversal_count<<endl;
			found=true;
			break;
		}
		cursor=cursor->next; //if node not found, move to next node
		traversal_count++;
	}
	if(!found){
		cout<<endl<<"-> Hotel "<<searchName<<" in city "<<city<< " not found"<<endl;}
}

void LinkedList::FindCity(string searchName){
	HotelNode* cursor;
	cursor=new HotelNode;
	cursor=head;
	citycount=0;
	int count=0;
	bool found=false;
	while(cursor!=NULL){
		if((*cursor).getcityName()==searchName){ //if node of cursor matches hotel name being searched for, print contents
			if(count==0){
			cout<<endl<<setw(42)<<left<<"     HOTEL"<<setw(20)<<"  CITY"<<setw(10)<<"STARS"<<setw(15)<<"PRICE"<<setw(20)<<"  COUNTRY"<<setw(50)<<"  ADDRESS"<<endl;
			cout<<"___________________________________________________________________________________________________________________________________________"<<endl<<endl;
			count++;}
			(*cursor).print();
			citycount++;
			found=true;
		}
		cursor=cursor->next; //if node not found, move to next node
	}
	if(!found){
		cout<<endl<<"-> No hotels in "<<searchName<<endl;}
}
void LinkedList::RemoveNode2(string searchName,string city){
	int traversal_count=0;
	bool deleted=false;
	HotelNode* p;
	p=new HotelNode;
	HotelNode* q;
	q=new HotelNode;
	q=head;
	p=head->next;
	if((*q).gethtlName()==searchName && (*q).getcityName()==city){ //if first node
		head=p;
		q->next=NULL;
		delete q;
		deleted=true;
		size--;
	}
	else{ //if not start node
		if (p == NULL) return ;
		int counter=0;
		while(!deleted && counter<=size && p!=NULL){
			if((*p).gethtlName()==searchName && (*p).getcityName()==city){
				deleted=true;
				break;
			}
			p=p->next;
			q=q->next;
			counter++;
		}
		if (p == NULL) return ;
		q->next=p->next;
		p->next=NULL;
		delete p;
		deleted=true;
	}

	if(!deleted){cout<<endl<<"-> Hotel "<<searchName<<" in city "<<city<<" does not exist in records"<<endl;
	}
}

void LinkedList::RemoveNode(string searchName,string city){
	int traversal_count=0;
	bool deleted=false;
	HotelNode* p;
	p=new HotelNode;
	HotelNode* q;
	q=new HotelNode;
	q=head;
	p=head->next;
	if((*q).gethtlName()==searchName && (*q).getcityName()==city){ //if first node
		head=p;
		q->next=NULL;
		delete q;
		deleted=true;
		cout<<endl<<"-> Hotel "<<searchName<<" in city "<<city<<" has been deleted"<<endl;
		size--;
	}
	else{ //if not start node
		if (p == NULL) return ;
		int counter=0;
		while(!deleted && counter<=size && p!=NULL){
			if((*p).gethtlName()==searchName && (*p).getcityName()==city){
				deleted=true;
				break;
			}
			p=p->next;
			q=q->next;
			counter++;
		}
		if (p == NULL) return ;
		q->next=p->next;
		p->next=NULL;
		delete p;
		deleted=true;
		cout<<endl<<"-> Hotel "<<searchName<<" in city "<<city<<" has been deleted"<<endl;
	}

	if(!deleted){cout<<endl<<"-> Hotel "<<searchName<<" in city "<<city<<" does not exist in records"<<endl;
	}
}


HotelMap::HotelMap(int capacity)
	{
		Hotellist=new LinkedList*[capacity]; //Array oflinked lists created
		for(int i=0; i<(capacity-1);i++){
			Hotellist[i]=new LinkedList;
		}
		this->capacity = capacity;
		this->size = 0;
	} 
//ADD DESCTRUCTOR
HotelMap::~HotelMap(){
	for(int i=0; i<(capacity-1);i++){
		delete[] Hotellist[i];}
		delete Hotellist;
}

int HotelMap::getcapacity(){
	return capacity;
}
long HotelMap::hashCode(const string key) //Using ascii value hashcode
	{
		long val=0;
		for(int i=0;i<key.length();i++){
			val=val+key[i];
		} 

		return abs(val); 
	}
void HotelMap::insert(HotelNode* hot){
	int index = hashCode((*hot).gethtlName())%capacity; //Using HotelName as key
	(*Hotellist[index]).AddNode(hot); //Adds hotel to bucket using addnode function in linkedlist class
	size++;
}
void HotelMap::insert2(HotelNode* hot){ //Uses city as key 
	int index = hashCode((*hot).getcityName())%capacity; 
	(*Hotellist[index]).AddNode(hot);
	size++;
	
}
void HotelMap::sizeofmap(){
	cout<<"size of hotel/city map: "<<size<<endl;
}
void HotelMap::find(string htlname,string city){
	int index = hashCode(htlname)%capacity; //using HotelName as key 
	(*Hotellist[index]).FindNode(htlname,city); //calls findnode function from linkedlist class
}
void HotelMap::findcity(string city){
	int index = hashCode(city)%capacity; 
	(*Hotellist[index]).FindCity(city);
	cout<<endl<<"-> "<<(*Hotellist[index]).getcitycount()<<" hotels found in "<<city<<endl;
}
void HotelMap::remove(string htlname,string city){
	int index = hashCode(htlname)%capacity; //using HotelName as key 
	(*Hotellist[index]).RemoveNode(htlname,city); //calls removenode function from linkedlist class
	size--;
}
void HotelMap::remove2(string htlname,string city){
	int index = hashCode(city)%capacity; //using cityName as key 
	(*Hotellist[index]).RemoveNode2(htlname,city); //calls removenode function from linkedlist class
	size--;
}
