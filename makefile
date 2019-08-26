CXXFLAGS = -std=c++11 -Wall -Wextra -Wpedantic -fopenmp
CXX = g++

SOURCEDIR = src
BUILDIR = build

LIBS = -lassimp -pthread

EXECUTABLE= pathtracer

CXXFLAGS += -MMD \
			-I../../../../work/common/glm-0.9.7.0 \
			-I/usr/local/include

LDFLAGS = -L/usr/lib/gcc/x86_64-linux-gnu/4.8 \
		  -L/usr/lib/x86_64-linux-gnu \
		  -L/usr/lib \
	      -L/usr/local/lib


SOURCES = $(wildcard $(SOURCEDIR)/*.cpp)
DEPENDENCIES = $(wildcard $(SOURCEDIR)/*.h)

_OBJECTS = $(SOURCES:.cpp=.o)
OBJECTS = $(patsubst $(SOURCEDIR)/%,$(BUILDIR)/%,$(_OBJECTS))

$(BUILDIR)/%.o : $(SOURCEDIR)/%.cpp $(DEPENDENCIES)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(EXECUTABLE) : $(OBJECTS)
	$(CXX) $(CXXFLAGS) $^ -o $@ $(LIBS)

.PHONY : cleanobj clean

cleanobj:
	rm $(OBJECTS)
clean:
	rm $(EXECUTABLE)