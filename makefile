hotelFinder: mainhf2.o functionhf.o
	g++ mainhf2.o functionhf.o -o hotelFinder
mainhf2.o: mainhf2.cpp
	g++ -c mainhf2.cpp
functionhf.o: functionhf.cpp hotelfinder.h
	g++ -c functionhf.cpp
clean:
	rm *.o hotelFinder

