CXX = g++
#CXXFLAGS = -std=c++0x 
RM = rm -f

a.out: core.o make
	$(CXX) $(CXXFLAGS) @compile.txt

core.o:
	find src -name "*.cpp" > sources.txt
	$(CXX) $(CXXFLAGS) -c -Iinclude @sources.txt

make:
	find -name "*.o" > compile.txt

clean:
	$(RM) *.o
	$(RM) sources.txt
	$(RM) compile.txt
