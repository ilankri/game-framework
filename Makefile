SHELL = /bin/sh
RM = rm -f
CXX = g++
CPPFLAGS = -MMD -MP # To generate automatically dependencies for make.
DEBUGFLAG = -g3
CXXFLAGS = $(DEBUGFLAG) -Wall -Wextra -Wpedantic -std=c++11
LDFLAGS = $(DEBUGFLAG)

EXEC_2048 = game-2048 game-2048-num game-2048-num2 game-2048-neg	\
	game-2048-mult game-2048-dest game-2048-mix

EXEC_TAQUIN = taquin-int taquin-cap-char taquin-low-char

EXEC = $(EXEC_2048) $(EXEC_TAQUIN) sokoban

SRC_COMMON = printable.cpp game.cpp

SRC_2048_COMMON = action_2048.cpp square_2048.cpp game_2048.cpp
SRC_2048 = game_2048_main.cpp
SRC_2048_NUM = game_2048_num.cpp game_2048_num_main.cpp
SRC_2048_NUM2 = game_2048_num2.cpp game_2048_num2_main.cpp
SRC_2048_NEG = game_2048_neg.cpp game_2048_neg_main.cpp
SRC_2048_MULT = game_2048_mult.cpp game_2048_mult_main.cpp
SRC_2048_DEST = game_2048_dest.cpp game_2048_dest_main.cpp
SRC_2048_MIX = game_2048_num2.cpp game_2048_neg.cpp game_2048_mult.cpp	\
	game_2048_dest.cpp game_2048_mix.cpp game_2048_mix_main.cpp

SRC_TAQUIN_COMMON = square_taquin.cpp taquin.cpp
SRC_TAQUIN_INT = taquin_int_main.cpp
SRC_TAQUIN_CAP_CHAR = cap_char.cpp taquin_cap_char_main.cpp
SRC_TAQUIN_LOW_CHAR = low_char.cpp taquin_low_char_main.cpp

SRC_SOKOBAN = sokoban.cpp sokoban_main.cpp

OBJ_COMMON = $(SRC_COMMON:.cpp=.o)

OBJ_2048_COMMON = $(SRC_2048_COMMON:.cpp=.o)
OBJ_2048 = $(SRC_2048:.cpp=.o)
OBJ_2048_NUM = $(SRC_2048_NUM:.cpp=.o)
OBJ_2048_NUM2 = $(SRC_2048_NUM2:.cpp=.o)
OBJ_2048_NEG = $(SRC_2048_NEG:.cpp=.o)
OBJ_2048_MULT = $(SRC_2048_MULT:.cpp=.o)
OBJ_2048_DEST = $(SRC_2048_DEST:.cpp=.o)
OBJ_2048_MIX = $(SRC_2048_MIX:.cpp=.o)

OBJ_TAQUIN_COMMON = $(SRC_TAQUIN_COMMON:.cpp=.o)
OBJ_TAQUIN_INT = $(SRC_TAQUIN_INT:.cpp=.o)
OBJ_TAQUIN_CAP_CHAR = $(SRC_TAQUIN_CAP_CHAR:.cpp=.o)
OBJ_TAQUIN_LOW_CHAR = $(SRC_TAQUIN_LOW_CHAR:.cpp=.o)

OBJ_SOKOBAN = $(SRC_SOKOBAN:.cpp=.o)

OBJ = $(OBJ_COMMON) $(OBJ_2048_COMMON) $(OBJ_2048) $(OBJ_2048_NUM)	\
	$(OBJ_2048_NUM2) $(OBJ_2048_NEG) $(OBJ_2048_MULT)		\
	$(OBJ_2048_DEST) $(OBJ_2048_MIX) $(OBJ_TAQUIN_COMMON)		\
	$(OBJ_TAQUIN_INT) $(OBJ_TAQUIN_CAP_CHAR) $(OBJ_TAQUIN_LOW_CHAR)	\
	$(OBJ_SOKOBAN)

DEP = $(OBJ:.o=.d)

srcdir = src
compile = $(CXX) -c $(CPPFLAGS) $(CXXFLAGS)
link = $(CXX) $(LDFLAGS)

.SUFFIXES:
.SUFFIXES: .o .cpp
.PHONY: all game-2048-all taquin-all clean mrproper

all: game-2048-all taquin-all sokoban

game-2048-all: $(EXEC_2048)

$(EXEC_2048): $(OBJ_2048_COMMON)

game-2048: $(OBJ_2048)

game-2048-num: $(OBJ_2048_NUM)

game-2048-num2: $(OBJ_2048_NUM2)

game-2048-neg: $(OBJ_2048_NEG)

game-2048-mult: $(OBJ_2048_MULT)

game-2048-dest: $(OBJ_2048_DEST)

game-2048-mix: $(OBJ_2048_MIX)

taquin-all: $(EXEC_TAQUIN)

$(EXEC_TAQUIN): $(OBJ_TAQUIN_COMMON)

taquin-int: $(OBJ_TAQUIN_INT)

taquin-cap-char: $(OBJ_TAQUIN_CAP_CHAR)

taquin-low-char: $(OBJ_TAQUIN_LOW_CHAR)

sokoban: $(OBJ_SOKOBAN)

$(EXEC): $(OBJ_COMMON)
	$(link) $^ -o $@

%.o: $(srcdir)/%.cpp
	$(compile) $<

-include $(DEP)

clean:
	$(RM) $(OBJ) $(DEP)

mrproper: clean
	$(RM) $(EXEC)
