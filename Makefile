SHELL = /bin/sh
RM = rm -f
CXX = g++
CPPFLAGS = -MMD -MP # To generate automatically dependencies for make.
DEBUGFLAG = -g3
CXXFLAGS = $(DEBUGFLAG) -Wall -Wextra -Wpedantic -std=c++11
LDFLAGS = $(DEBUGFLAG)

SRC = main.cpp square.cpp game.cpp taquin.cpp sokoban.cpp game_2048.cpp
OBJ = $(SRC:.cpp=.o)
DEP = $(SRC:.cpp=.d)
EXEC = game

srcdir = src
compile = $(CXX) -c $(CPPFLAGS) $(CXXFLAGS)
link = $(CXX) $(LDFLAGS)

.SUFFIXES:
.SUFFIXES: .o .cpp
.PHONY: all clean mrproper

all: $(EXEC)

$(EXEC): $(OBJ)
	$(link) $^ -o $@

%.o: $(srcdir)/%.cpp
	$(compile) $<

-include $(DEP)

clean:
	$(RM) $(OBJ) $(DEP)

mrproper: clean
	$(RM) $(EXEC)
