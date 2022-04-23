EXT = cpp
SRCS_MONTADOR = $(patsubst %,%.$(EXT),main montador func_auxiliares)
OBJS_MONTADOR = $(patsubst %,build/%.o,$(basename $(SRCS_MONTADOR)))

CXX = g++
CCFLAGS = -Wall
CXXFLAGS = -Wall -g
CPPFLAGS = -Iinclude/

all: bin/montador

build/%.o: src/%.cpp
	@echo "- Compilando objeto \"$@\""
	@$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $< -o $@

bin/montador: $(OBJS_MONTADOR)
	@echo "+ Compilando programa \"$@\""
	@$(CXX) $(CXXFLAGS) $(OBJS_MONTADOR) -o bin/montador


clean:
	rm -f bin/* $(OBJS_MONTADOR)
