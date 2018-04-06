CATSDIR := ../../cats/cats-cpp/src
CXXFLAGS += -I${CATSDIR} `sdl2-config --cflags` -std=c++11


RymdSpelet: Rymdskepp.o GameObject.o Main.o ${CATSDIR}/libcats.a ${CATSDIR}/Cats.h
	g++ -o $@ $^ -L${CATSDIR} -lcats `sdl2-config --libs` -lSDL2_image

data:
	(cd ../data/gfx && for i in *.xcf; do xcf2png $$i -o $${i%.xcf}.png; done)

clean:
	@rm -f *.o RymdSpelet ../data/gfx/*.png
