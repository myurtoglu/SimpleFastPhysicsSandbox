uname_S := $(shell sh -c 'uname -s 2>/dev/null || echo not')

CXX = clang++
CXXFLAGS =  -std=c++11 -Wall -Wextra -pedantic -O3

SFGUI = -lsfgui
BOX2D = -lBox2D

ifeq ($(uname_S), Darwin)
	SF_SYSTEM = -framework sfml-system
	SF_WINDOW = -framework sfml-window
	SF_GRAPHICS = -framework sfml-graphics
	SF_AUDIO = -framework sfml-audio
	SF_NETWORK = -framework sfml-network
	FOUNDATION = -framework Foundation
	LDFLAGS = $(SF_SYSTEM) $(SF_WINDOW) $(SF_GRAPHICS) $(SF_AUDIO) \
		  	  $(SF_NETWORK) $(FOUNDATION) $(SFGUI) $(BOX2D)
endif

ifeq ($(uname_S), Linux)
	CXX = g++
	LDFLAGS = -lsfml-system -lsfml-window -lsfml-graphics -lsfml-audio \
			  -lsfml-network -lobjc -lgnustep-base \
			  $(SFGUI) $(BOX2D)
	INCLUDE = -I/usr/include/GNUstep
endif

VPATH    = src src/*
BUILDDIR = build
CPP_SRC  = $(wildcard src/*.cpp src/**/*.cpp)
MM_SRC   = $(wildcard src/*.mm src/**/*.mm)
HEADER	 = $(wildcard src/*.h src/*.hpp src/**/*.h src/**/*.hpp)
OBJ      =  $(patsubst src/%.cpp, $(BUILDDIR)/%.o, $(CPP_SRC))
OBJ      += $(patsubst src/%.mm,  $(BUILDDIR)/%.o, $(MM_SRC))
OBJDIR   = $(dir $(OBJ))

.PHONY: all clean clobber directories

$(BUILDDIR)/%.o: %.cpp $(HEADER)
	$(CXX) $(CXXFLAGS) $(INCLUDE) -c $< -o $@

$(BUILDDIR)/%.o: %.mm $(HEADER)
	$(CXX) $(CXXFLAGS) $(INCLUDE) -c $< -o $@

all: directories main.exe

main.exe: $(OBJ)
	$(CXX) -o $@ $(OBJ) $(LDFLAGS)

directories:
	@mkdir -p $(OBJDIR)

clean:
	rm -rf $(BUILDDIR)

clobber: clean
	rm -rf *.exe

