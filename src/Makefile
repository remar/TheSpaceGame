GTK_CXXFLAGS := `pkg-config --cflags gtk+-3.0`
GTK_LIBS := `pkg-config --libs gtk+-3.0`
SDL2CONFIG := sdl2-config
CATSDIR := ../../cats/cats-cpp/src
CPPFILES := $(wildcard *.cpp)
DEPFILES := $(patsubst %.cpp,%.d,$(CPPFILES))
CXXFLAGS += -I${CATSDIR} ${GTK_CXXFLAGS} `$(SDL2CONFIG) --cflags` -std=c++11
OFILES := $(CPPFILES:.cpp=.o)


TheSpaceGame: ${OFILES}
	$(CXX) -o $@ $^ -L${CATSDIR} -lcats ${GTK_LIBS} `$(SDL2CONFIG) --libs` -lSDL2_image

-include $(DEPFILES)

%.o: %.cpp Makefile
	$(CXX) $(CXXFLAGS) -MMD -MP -c $< -o $@

clean:
	@rm -f *.o TheSpaceGame *.d
