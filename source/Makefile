CXX=g++
CFLAGS_DEBUG=-std=c++11 -Wall -Wextra -Werror -Wno-unused-parameter -Wno-unknown-pragmas -g
LDFLAGS_DEBUG=-lIrrlicht
CFLAGS_RELEASE=-std=c++11 -Wall -Wextra -Werror -Wno-unused-parameter -Wno-unknown-pragmas -O2 -DNDEBUG
LDFLAGS_RELEASE=-lIrrlicht
SOURCES=Hero.cpp GlownaKlasa.cpp main.cpp petlaGry.cpp sterowanie.cpp zmienne_globalne.cpp
#USE_PRECOMPILED_HEADERS=yes jeśli chcesz użyć prekompilowanych nagłówków
USE_PRECOMPILED_HEADERS=no
PRECOMP=$(USE_PRECOMPILED_HEADERS:yes=precomp.hpp)
INCLUDES=$(PRECOMP).gch Hero.hpp GlownaKlasa.hpp InputOutputHandler.hpp menedzerObiektow.hpp
OBJ_PREFIX=../obj/
OBJECTS_RELEASE=$(OBJ_PREFIX)Hero.o $(OBJ_PREFIX)GlownaKlasa.o $(OBJ_PREFIX)main.o $(OBJ_PREFIX)petlaGry.o $(OBJ_PREFIX)sterowanie.o $(OBJ_PREFIX)zmienne_globalne.o
OBJECTS_DEBUG=$(OBJECTS_RELEASE:.o=d.o)

release: create_dirs $(OBJECTS_RELEASE)
	$(CXX) $(OBJECTS_RELEASE) $(LDFLAGS_RELEASE) -o ../bin/ProjektGry.exe

debug: create_dirs $(OBJECTS_DEBUG)
	$(CXX) $(OBJECTS_DEBUG) $(LDFLAGS_DEBUG) -o ../bin/ProjektGry.exe

create_dirs:
	mkdir -p "../bin"
	mkdir -p "../obj"

precomp.hpp.gch: precomp.hpp
	$(CXX) $(CFLAGS_RELEASE) $(PRECOMP)

$(OBJ_PREFIX)Herod.o: Hero.cpp $(INCLUDES)
	$(CXX) $(CFLAGS_DEBUG) -c Hero.cpp -o $(OBJ_PREFIX)Herod.o

$(OBJ_PREFIX)GlownaKlasad.o: GlownaKlasa.cpp $(INCLUDES)
	$(CXX) $(CFLAGS_DEBUG) -c GlownaKlasa.cpp -o $(OBJ_PREFIX)GlownaKlasad.o

$(OBJ_PREFIX)maind.o: main.cpp $(INCLUDES)
	$(CXX) $(CFLAGS_DEBUG) -c main.cpp -o $(OBJ_PREFIX)maind.o

$(OBJ_PREFIX)petlaGryd.o: petlaGry.cpp $(INCLUDES)
	$(CXX) $(CFLAGS_DEBUG) -c petlaGry.cpp -o $(OBJ_PREFIX)petlaGryd.o

$(OBJ_PREFIX)sterowanied.o: sterowanie.cpp $(INCLUDES)
	$(CXX) $(CFLAGS_DEBUG) -c sterowanie.cpp -o $(OBJ_PREFIX)sterowanied.o

$(OBJ_PREFIX)zmienne_globalned.o: zmienne_globalne.cpp $(INCLUDES)
	$(CXX) $(CFLAGS_DEBUG) -c zmienne_globalne.cpp -o $(OBJ_PREFIX)zmienne_globalned.o

$(OBJ_PREFIX)Hero.o: Hero.cpp $(INCLUDES)
	$(CXX) $(CFLAGS_RELEASE) -c Hero.cpp -o $(OBJ_PREFIX)Hero.o

$(OBJ_PREFIX)GlownaKlasa.o: GlownaKlasa.cpp $(INCLUDES)
	$(CXX) $(CFLAGS_RELEASE) -c GlownaKlasa.cpp -o $(OBJ_PREFIX)GlownaKlasa.o

$(OBJ_PREFIX)main.o: main.cpp $(INCLUDES)
	$(CXX) $(CFLAGS_RELEASE) -c main.cpp -o $(OBJ_PREFIX)main.o

$(OBJ_PREFIX)petlaGry.o: petlaGry.cpp $(INCLUDES)
	$(CXX) $(CFLAGS_RELEASE) -c petlaGry.cpp -o $(OBJ_PREFIX)petlaGry.o

$(OBJ_PREFIX)sterowanie.o: sterowanie.cpp $(INCLUDES)
	$(CXX) $(CFLAGS_RELEASE) -c sterowanie.cpp -o $(OBJ_PREFIX)sterowanie.o

$(OBJ_PREFIX)zmienne_globalne.o: zmienne_globalne.cpp $(INCLUDES)
	$(CXX) $(CFLAGS_RELEASE) -c zmienne_globalne.cpp -o $(OBJ_PREFIX)zmienne_globalne.o

clean:
	rm -f $(OBJ_PREFIX)*.o
	rm -f *.gch

no:

no.hpp:

no.gch:

.PHONY: release debug clean create_dirs no no.hpp no.gch