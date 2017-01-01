SHELL = /bin/sh
RM = rm -f
CXX = g++
CPPFLAGS = -MMD -MP # To generate automatically dependencies for make.
DEBUGFLAG = -g3
CXXFLAGS = $(DEBUGFLAG) -Wall -Wextra -Wpedantic -std=c++11
LDFLAGS = $(DEBUGFLAG)

# 2048 executables
EXEC_2048 = game-2048 game-2048-num game-2048-num2 game-2048-neg	\
		game-2048-mult game-2048-dest game-2048-mix

# Taquin executables
EXEC_TAQUIN = taquin

# All executables
EXEC = $(EXEC_2048) $(EXEC_TAQUIN) sokoban

# Common sources
SRC_COMMON = printable.cpp game.cpp

# 2048 sources
SRC_2048_COMMON = action_2048.cpp square_2048.cpp game_2048.cpp
SRC_2048 = game_2048_main.cpp
SRC_2048_NUM = game_2048_num.cpp game_2048_num_main.cpp
SRC_2048_NUM2 = game_2048_num2.cpp game_2048_num2_main.cpp
SRC_2048_NEG = game_2048_neg.cpp game_2048_neg_main.cpp
SRC_2048_MULT = game_2048_mult.cpp game_2048_mult_main.cpp
SRC_2048_DEST = game_2048_dest.cpp game_2048_dest_main.cpp
SRC_2048_MIX = game_2048_num2.cpp game_2048_neg.cpp game_2048_mult.cpp	\
		game_2048_dest.cpp game_2048_mix.cpp			\
		game_2048_mix_main.cpp

# Taquin sources
SRC_TAQUIN = cap_char.cpp low_char.cpp square_taquin.cpp taquin.cpp	\
		taquin_main.cpp

# Sokoban sources
SRC_SOKOBAN = sokoban.cpp sokoban_main.cpp

# Common objects
OBJ_COMMON = $(SRC_COMMON:.cpp=.o)

# 2048 objects
OBJ_2048_COMMON = $(SRC_2048_COMMON:.cpp=.o)
OBJ_2048 = $(SRC_2048:.cpp=.o)
OBJ_2048_NUM = $(SRC_2048_NUM:.cpp=.o)
OBJ_2048_NUM2 = $(SRC_2048_NUM2:.cpp=.o)
OBJ_2048_NEG = $(SRC_2048_NEG:.cpp=.o)
OBJ_2048_MULT = $(SRC_2048_MULT:.cpp=.o)
OBJ_2048_DEST = $(SRC_2048_DEST:.cpp=.o)
OBJ_2048_MIX = $(SRC_2048_MIX:.cpp=.o)

# Taquin objects
OBJ_TAQUIN = $(SRC_TAQUIN:.cpp=.o)

# Sokoban objects
OBJ_SOKOBAN = $(SRC_SOKOBAN:.cpp=.o)

# All objects
OBJ = $(OBJ_COMMON) $(OBJ_2048_COMMON) $(OBJ_2048) $(OBJ_2048_NUM)	\
	$(OBJ_2048_NUM2) $(OBJ_2048_NEG) $(OBJ_2048_MULT)		\
	$(OBJ_2048_DEST) $(OBJ_2048_MIX) $(OBJ_TAQUIN) $(OBJ_SOKOBAN)

DEP = $(OBJ:.o=.d)

srcdir = src
compile = $(CXX) -c $(CPPFLAGS) $(CXXFLAGS)
link = $(CXX) $(LDFLAGS)

.SUFFIXES:
.SUFFIXES: .o .cpp
.PHONY: all game-2048-all taquin clean mrproper

all: game-2048-all taquin sokoban

# 2048 rules
game-2048-all: $(EXEC_2048)

$(EXEC_2048): $(OBJ_2048_COMMON)

game-2048: $(OBJ_2048)

game-2048-num: $(OBJ_2048_NUM)

game-2048-num2: $(OBJ_2048_NUM2)

game-2048-neg: $(OBJ_2048_NEG)

game-2048-mult: $(OBJ_2048_MULT)

game-2048-dest: $(OBJ_2048_DEST)

game-2048-mix: $(OBJ_2048_MIX)

# Taquin rules
taquin: $(OBJ_TAQUIN)

# Sokoban rule
sokoban: $(OBJ_SOKOBAN)

# Generic rules
$(EXEC): $(OBJ_COMMON)
	$(link) $^ -o $@

%.o: $(srcdir)/%.cpp
	$(compile) $<

-include $(DEP)

# Cleaning rules
clean:
	$(RM) $(OBJ) $(DEP)

mrproper: clean
	$(RM) $(EXEC)
