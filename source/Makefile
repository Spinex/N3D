CXX=g++
CFLAGS_DEBUG=-std=c++11 -Wall -Wextra -Werror -Wno-unused-parameter -Wno-unknown-pragmas -g
LDFLAGS_DEBUG=-lIrrlicht
CFLAGS_RELEASE=-std=c++11 -Wall -Wextra -Werror -Wno-unused-parameter -Wno-unknown-pragmas -O2 -DNDEBUG
LDFLAGS_RELEASE=-lIrrlicht
#PRECOMP=precomp.hpp.gch
#jeżeli chcesz użyć prekompilowanych nagłówków
#PRECOMP=
#w przeciwnym razie
PRECOMP=precomp.hpp.gch
INCLUDES=$(PRECOMP) incl.hpp Hero.hpp InputOutputHandler.hpp SideCollisionDetector.hpp ConsoleManager.hpp Level.hpp Entity.hpp
SOURCES=Level.cpp SideCollisionDetector.cpp Hero.cpp main.cpp InputOutputHandler.cpp zmienne_globalne.cpp ConsoleManager.cpp
OBJECTS_RELEASE=$(SOURCES:.cpp=.o)
OBJECTS_DEBUG=$(OBJECTS_RELEASE:.o=d.o)

debug: $(OBJECTS_DEBUG)
	$(CXX) $(OBJECTS_DEBUG) $(LDFLAGS_DEBUG) -o ../bin/ProjektGry.exe

release: $(OBJECTS_RELEASE)
	$(CXX) $(OBJECTS_RELEASE) $(LDFLAGS_RELEASE) -o ../bin/ProjektGry.exe

whole_program: $(INCLUDES) $(SOURCES)
	$(CXX) $(SOURCES) $(CFLAGS_RELEASE) -flto $(LDFLAGS_RELEASE) -fwhole-program -o ../bin/ProjektGry.exe

precomp.hpp.gch: precomp.hpp
	$(CXX) $(CFLAGS_RELEASE) precomp.hpp

%d.o: %.cpp $(INCLUDES)
	$(CXX) $(CFLAGS_DEBUG) -c $(@:d.o=.cpp) -o $@

%.o: %.cpp $(INCLUDES)
	$(CXX) $(CFLAGS_RELEASE) -c $(@:.o=.cpp) -o $@

clean:
	rm -f *.o
	rm -f *.gch

.PHONY: release debug clean create_dirs