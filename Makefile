SHELL = /bin/sh
RM = rm -f
CXX = g++
CPPFLAGS = -MMD -MP # To generate automatically dependencies for make.
DEBUGFLAG = -g3
CXXFLAGS = $(DEBUGFLAG) -Wall -Wextra -Wpedantic -std=c++11
LDFLAGS = $(DEBUGFLAG)

SRC_COMMON = printable.cpp game.cpp
SRC_2048 = ordered_pair.cpp square_2048_action.cpp square_2048.cpp	\
	game_2048.cpp game_2048_main.cpp
SRC_TAQUIN = square_taquin.cpp taquin.cpp taquin_main.cpp

OBJ_COMMON = $(SRC_COMMON:.cpp=.o)
OBJ_2048 = $(SRC_2048:.cpp=.o)
OBJ_TAQUIN = $(SRC_TAQUIN:.cpp=.o)
OBJ = $(OBJ_COMMON) $(OBJ_2048) $(OBJ_TAQUIN)

DEP_COMMON = $(SRC_COMMON:.cpp=.d)
DEP_2048 = $(SRC_2048:.cpp=.d)
DEP_TAQUIN = $(SRC_TAQUIN:.cpp=.d)
DEP = $(DEP_COMMON) $(DEP_2048) $(DEP_TAQUIN)

srcdir = src
compile = $(CXX) -c $(CPPFLAGS) $(CXXFLAGS)
link = $(CXX) $(LDFLAGS)

.SUFFIXES:
.SUFFIXES: .o .cpp
.PHONY: all clean mrproper

all: game-2048 taquin

game-2048: $(OBJ_COMMON) $(OBJ_2048)
	$(link) $^ -o $@

taquin: $(OBJ_COMMON) $(OBJ_TAQUIN)
	$(link) $^ -o $@

%.o: $(srcdir)/%.cpp
	$(compile) $<

-include $(DEP)

clean:
	$(RM) $(OBJ) $(DEP)

mrproper: clean
	$(RM) game-2048 taquin
