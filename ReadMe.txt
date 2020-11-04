
----------------------HotelFinder----------------------
This is a HotelFinder tool to sift through a hotel dataset. 
The menu option will give 6 options:

-> Find hotel,city
-> Add hotel,city,stars,price,country,address
-> Delete hotel,city
-> Dump hotel information
-> allinCity
-> Quit

Action 4 dumps the information from the database into a newly created file "Hotel_Information.txt" within the folder. 

There are 3 differently sized datasets you can choose from:
	1.hotels1k.csv
	2.hotels10k.csv
	3.hotels100k.csv

To run the program on Mac OS:

1. Open terminal 
2. Change the directory to where the file is stored in 
3. Afterwards type: make
4. Finally: ./hotelFinder -f <one of the files above> 

Example:

make 
./hotelFinder -f hotels1k.csv


