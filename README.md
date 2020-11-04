# Hotel-Finder
**The aim of this project was to develop a time efficient program that streams hotel information from csv files (the hotel datasets) that store up to 100k hotel records.** 

Data Structures Used: 
- **Hash Tables and Lists** (Abstract Data Type) to store hotel info
- **Vectors** (Standard Template Library)

The program provides six functionalities that are to be used in the following format:

- **Find hotel,city**
- **Add hotel,city,stars,price,country,address**
- **Delete hotel,city**
- **Dump hotel information**
- **allinCity,city**
- **Quit**

Add, delete and search functions are run in O(1) time complexity.  
Dump hotel information dumps the information from the database into a newly created file "Hotel_Information.txt" within the folder.  
allinCity provides all the hotels present in a specified city.  

There are 3 differently sized datasets to choose from in the **inputs folder**:
	1.hotels1k.csv
	2.hotels10k.csv
	3.hotels100k.csv

To run the program:

1. Open terminal 
2. Change the directory to where the files are stored 
3. Afterwards type: make
4. Finally: ./hotelFinder -f <one of the files above> 

Example:

make 
./hotelFinder -f hotels1k.csv
