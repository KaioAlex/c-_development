EXT = cpp

SRCS_MONTADOR = $(patsubst %,%.$(EXT),main montador func_auxiliares)
OBJS_MONTADOR = $(patsubst %,build/montador/%.o,$(basename $(SRCS_MONTADOR)))

SRCS_LIGADOR = $(patsubst %,%.$(EXT),main ligador)
OBJS_LIGADOR = $(patsubst %,build/ligador/%.o,$(basename $(SRCS_LIGADOR)))

CXX = g++
CCFLAGS = -Wall
CXXFLAGS = -Wall -g
CPPFLAGS = -Iinclude/

all: bin/montador bin/ligador

bin/montador: $(OBJS_MONTADOR)
	@echo "+ Compilando programa \"$@\""
	@$(CXX) $(CXXFLAGS) $(OBJS_MONTADOR) -o bin/montador

bin/ligador: $(OBJS_LIGADOR)
	@echo "+ Compilando programa \"$@\""
	@$(CXX) $(CXXFLAGS) $(OBJS_LIGADOR) -o bin/ligador

build/montador/%.o: src/montador/%.cpp
	@echo "- Compilando objeto \"$@\""
	@$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $< -o $@

build/ligador/%.o: src/ligador/%.cpp
	@echo "- Compilando objeto \"$@\""
	@$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f bin/* $(OBJS_MONTADOR)
	rm -f bin/* $(OBJS_LIGADOR)
