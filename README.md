# Hotel-Finder
**The aim of this project was to develop a time efficient program that streams hotel information from csv files (the hotel datasets) that store up to 100k hotel records.** 

Data Structures Used: 
- **Hash Tables and Lists** (Abstract Data Type) to store hotel info
- **Vectors** (Standard Template Library)

The program provides six functionalities that are to be used in the following format:

- **Find hotel,city**
- **Add hotel,city,stars,price,country,address**
- **Delete hotel,city**
- **allinCity,city** : provides all the hotels present in a specified city.
- **Dump hotel information** : dumps information from database into newly created file "Hotel_Information.txt"
- **Quit**

**Add**, **delete** and **find** functions are run in **O(1) time complexity**.  

There are 3 different sizes of **datasets** to choose from in the **inputs folder**:  
- hotels1k.csv
- hotels10k.csv
- hotels100k.csv

**To run the program**:

1. Open terminal 
2. Change the directory to where the files are stored 
3. Afterwards type: make
4. Finally: ./hotelFinder -f <one of the input files above> 

Example:

make 
./hotelFinder -f hotels1k.csv
