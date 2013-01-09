CXX=g++
CFLAGS_DEBUG=-std=c++11 -Wall -Wextra -Werror -Wno-unused-parameter -Wno-unknown-pragmas -g
LDFLAGS_DEBUG=-lIrrlicht
CFLAGS_RELEASE=-std=c++11 -Wall -Wextra -Werror -Wno-unused-parameter -Wno-unknown-pragmas -O2 -DNDEBUG
LDFLAGS_RELEASE=-lIrrlicht
#PRECOMP=precomp.hpp.gch
#jeżeli chcesz użyć prekompilowanych nagłówków
PRECOMP=
INCLUDES=$(PRECOMP) incl.hpp Hero.hpp IrrlichtInternals.hpp InputOutputHandler.hpp menedzerObiektow.hpp SideCollisionDetector.hpp ConsoleManager.hpp
SOURCES=SideCollisionDetector.cpp Hero.cpp IrrlichtInternals.cpp main.cpp petlaGry.cpp sterowanie.cpp zmienne_globalne.cpp ConsoleManager.cpp
OBJECTS_RELEASE=$(SOURCES:.cpp=.o)
OBJECTS_DEBUG=$(OBJECTS_RELEASE:.o=d.o)

debug: $(OBJECTS_DEBUG)
	$(CXX) $(OBJECTS_DEBUG) $(LDFLAGS_DEBUG) -o ../bin/ProjektGry.exe

release: $(OBJECTS_RELEASE)
	$(CXX) $(OBJECTS_RELEASE) $(LDFLAGS_RELEASE) -o ../bin/ProjektGry.exe

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