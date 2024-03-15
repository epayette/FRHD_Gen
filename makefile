# Compiler and flags
CXX = g++
CXXFLAGS = --std=c++17 -Wall -Werror -pedantic -g -Wno-sign-compare -Wno-comment

# Targets and dependencies
all: Create

Create: Create.o imageC.o trackC.o
	$(CXX) $(CXXFLAGS) $^ -o $@

# Object file dependencies
Create.o: Create.cpp Image.hpp Track.hpp
	$(CXX) $(CXXFLAGS) -c Create.cpp -o Create.o

imageC.o: Image.cpp Image.hpp
	$(CXX) $(CXXFLAGS) -c Image.cpp -o imageC.o

trackC.o: Track.cpp Track.hpp Image.hpp
	$(CXX) $(CXXFLAGS) -c Track.cpp -o trackC.o

# Clean rule
clean:
	rm -f *.o Create