matedit: matedit.cpp matrix.h
	g++ -Wall -ansi -g matedit.cpp matrix.cpp matrix.h -lcurses


clean:
	rm  *.o
