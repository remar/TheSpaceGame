CATSDIR := ../../cats/cats-cpp/src
CPPFILES := $(wildcard *.cpp)
DEPFILES := $(patsubst %.cpp,%.d,$(CPPFILES))
CXXFLAGS += -I${CATSDIR} `sdl2-config --cflags` -std=c++11
OFILES := $(CPPFILES:.cpp=.o)


TheSpaceGame: ${OFILES}
	g++ -o $@ $^ -L${CATSDIR} -lcats `sdl2-config --libs` -lSDL2_image

-include $(DEPFILES)

%.o: %.cpp Makefile
	@$(CXX) $(CXXFLAGS) -MMD -MP -c $< -o $@

clean:
	@rm -f *.o TheSpaceGame *.d
