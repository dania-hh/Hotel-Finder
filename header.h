#ifndef FUNCTION_H
#define FUNCTION_H

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

using namespace std;

class HotelNode{
private:
	string hotelName,cityName,stars,price,countryName,address;
	HotelNode* next;
public:
	HotelNode(HotelNode* n=NULL);
	HotelNode(string h,string cN,string s,string p, string countN, string adrs,HotelNode* n=NULL);
	string gethtlName();
	string getcityName();
	string printoutfile();
	void print();
	friend class LinkedList; 
};

bool alphabeticComp(HotelNode a, HotelNode b);

string whitespace(string input);

class LinkedList{ 
private:
	HotelNode* head;
	int citycount;
	int size;
public:
	LinkedList();
	~LinkedList();
	void removeFront();
	bool empty();
	int getcitycount();
	bool NodeExists(string htl,string city);
	void AddNode(HotelNode* hotel);
	void FindNode(string searchName,string city);
	void FindCity(string searchName);
	void RemoveNode(string searchName,string city);
	void RemoveNode2(string searchName,string city);
	friend class HotelMap;
};

class HotelMap{ 
private:
	LinkedList** Hotellist;
	int size;					
	int capacity;
public:
	HotelMap(int capacity);
	~HotelMap();
	int getcapacity();
	long hashCode(const string key);
	void insert(HotelNode* hot);
	void insert2(HotelNode* hot);
	void find(string htlname,string city);
	void findcity(string city);
	void remove(string htlname,string city);
	void remove2(string htlname,string city);
	void sizeofmap();

};

#endif