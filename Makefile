SHELL = /bin/sh
RM = rm -f
CXX = g++
CPPFLAGS = -MMD -MP # To generate automatically dependencies for make.
DEBUGFLAG = -g3
CXXFLAGS = $(DEBUGFLAG) -Wall -Wextra -Wpedantic -std=c++11
LDFLAGS = $(DEBUGFLAG)

SRC_COMMON = printable.cpp game.cpp
SRC_2048_COMMON = action_2048.cpp square_2048.cpp game_2048.cpp
SRC_2048 = game_2048_main.cpp
SRC_2048_NUM = game_2048_num.cpp game_2048_num_main.cpp
SRC_2048_NEG = game_2048_neg.cpp game_2048_neg_main.cpp
SRC_2048_MULT = game_2048_mult.cpp game_2048_mult_main.cpp
SRC_2048_DEST = game_2048_dest.cpp game_2048_dest_main.cpp
SRC_2048_MIX = game_2048_num.cpp game_2048_neg.cpp game_2048_mult.cpp \
	game_2048_dest.cpp game_2048_mix.cpp game_2048_mix_main.cpp
SRC_TAQUIN = square_taquin.cpp taquin.cpp taquin_main.cpp
SRC_SOKOBAN = sokoban.cpp sokoban_main.cpp

OBJ_COMMON = $(SRC_COMMON:.cpp=.o)
OBJ_2048_COMMON = $(SRC_2048_COMMON:.cpp=.o)
OBJ_2048 = $(SRC_2048:.cpp=.o)
OBJ_2048_NUM = $(SRC_2048_NUM:.cpp=.o)
OBJ_2048_NEG = $(SRC_2048_NEG:.cpp=.o)
OBJ_2048_MULT = $(SRC_2048_MULT:.cpp=.o)
OBJ_2048_DEST = $(SRC_2048_DEST:.cpp=.o)
OBJ_2048_MIX = $(SRC_2048_MIX:.cpp=.o)
OBJ_TAQUIN = $(SRC_TAQUIN:.cpp=.o)
OBJ_SOKOBAN = $(SRC_SOKOBAN:.cpp=.o)
OBJ = $(OBJ_COMMON) $(OBJ_2048_COMMON) $(OBJ_2048) $(OBJ_2048_NUM) \
	$(OBJ_2048_NEG) $(OBJ_2048_MULT) $(OBJ_2048_DEST) $(OBJ_2048_MIX) \
	$(OBJ_TAQUIN) $(OBJ_SOKOBAN)

DEP_COMMON = $(SRC_COMMON:.cpp=.d)
DEP_2048_COMMON= $(SRC_2048_COMMON:.cpp=.d)
DEP_2048 = $(SRC_2048:.cpp=.d)
DEP_2048_NUM = $(SRC_2048_NUM:.cpp=.d)
DEP_2048_NEG = $(SRC_2048_NEG:.cpp=.d)
DEP_2048_MULT = $(SRC_2048_MULT:.cpp=.d)
DEP_2048_DEST = $(SRC_2048_DEST:.cpp=.d)
DEP_2048_MIX = $(SRC_2048_MIX:.cpp=.d)
DEP_TAQUIN = $(SRC_TAQUIN:.cpp=.d)
DEP_SOKOBAN = $(SRC_SOKOBAN:.cpp=.d)
DEP = $(DEP_COMMON) $(DEP_2048_COMMON) $(DEP_2048) $(DEP_2048_NUM) \
	$(DEP_2048_NEG) $(DEP_2048_MULT) $(DEP_2048_DEST) $(DEP_2048_MIX) \
	$(DEP_TAQUIN) $(DEP_SOKOBAN)

srcdir = src
compile = $(CXX) -c $(CPPFLAGS) $(CXXFLAGS)
link = $(CXX) $(LDFLAGS)

.SUFFIXES:
.SUFFIXES: .o .cpp
.PHONY: all clean mrproper

all: game-2048 game-2048-num game-2048-neg game-2048-mult game-2048-dest \
	game-2048-mix taquin sokoban

game-2048: $(OBJ_COMMON) $(OBJ_2048_COMMON) $(OBJ_2048)
	$(link) $^ -o $@

game-2048-num: $(OBJ_COMMON) $(OBJ_2048_COMMON) $(OBJ_2048_NUM)
	$(link) $^ -o $@

game-2048-neg: $(OBJ_COMMON) $(OBJ_2048_COMMON) $(OBJ_2048_NEG)
	$(link) $^ -o $@

game-2048-mult: $(OBJ_COMMON) $(OBJ_2048_COMMON) $(OBJ_2048_MULT)
	$(link) $^ -o $@

game-2048-dest: $(OBJ_COMMON) $(OBJ_2048_COMMON) $(OBJ_2048_DEST)
	$(link) $^ -o $@

game-2048-mix: $(OBJ_COMMON) $(OBJ_2048_COMMON) $(OBJ_2048_MIX)
	$(link) $^ -o $@

taquin: $(OBJ_COMMON) $(OBJ_TAQUIN)
	$(link) $^ -o $@

sokoban: $(OBJ_COMMON) $(OBJ_SOKOBAN)
	$(link) $^ -o $@

%.o: $(srcdir)/%.cpp
	$(compile) $<

-include $(DEP)

clean:
	$(RM) $(OBJ) $(DEP)

mrproper: clean
	$(RM) game-2048 game-2048-num game-2048-neg game-2048-mult \
	game-2048-dest game-2048-mix taquin sokoban
