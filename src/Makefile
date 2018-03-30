CATSDIR := ../../cats/cats-cpp/src
CXXFLAGS += -I${CATSDIR} `sdl2-config --cflags` -std=c++11


RymdSpelet: Main.o ${CATSDIR}/libcats.a ${CATSDIR}/Cats.h
	g++ -o $@ $^ -L${CATSDIR} -lcats `sdl2-config --libs` -lSDL2_image

clean:
	@rm -f *.o RymdSpelet
