CFLAGS=-Wall -pedantic -pedantic-errors -g -ansi -Wextra -Weffc++ -std=c++14 -O3
ROOTFL=`root-config --cflags --libs`
RFLAGS:=`root-config --cflags` `root-config --libs`

spettro: spettro.c
	g++ $^ -o $@ ${RFLAGS} 

fit: fit.c
	g++ $^ -o $@ ${RFLAGS}

fit2: fit2.c
	g++ $^ -o $@ ${RFLAGS}

bragg: bragg.c
	g++ $^ -o $@ ${RFLAGS}