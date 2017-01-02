SHELL = /bin/sh
RM = rm -f
CXX = g++
CPPFLAGS = -MMD -MP # To generate automatically dependencies for make.
DEBUGFLAG = -g3
CXXFLAGS = $(DEBUGFLAG) -std=c++11 -Wall -Wextra -Wpedantic	\
		-Wno-unused-parameter
LDFLAGS = $(DEBUGFLAG)

# All executables
EXEC = game-2048 taquin sokoban

# Common sources
SRC_COMMON = printable.cpp game.cpp

# 2048 sources
SRC_2048 = action_2048.cpp square_2048.cpp game_2048.cpp		\
		game_2048_num.cpp game_2048_neg.cpp game_2048_fancy.cpp	\
		game_2048_mix.cpp game_2048_main.cpp

# Taquin sources
SRC_TAQUIN = char_exception.cpp cap_char.cpp low_char.cpp	\
	square_taquin.cpp taquin.cpp taquin_main.cpp

# Sokoban sources
SRC_SOKOBAN = sokoban.cpp sokoban_main.cpp

# Common objects
OBJ_COMMON = $(SRC_COMMON:.cpp=.o)

# 2048 objects
OBJ_2048 = $(SRC_2048:.cpp=.o)

# Taquin objects
OBJ_TAQUIN = $(SRC_TAQUIN:.cpp=.o)

# Sokoban objects
OBJ_SOKOBAN = $(SRC_SOKOBAN:.cpp=.o)

# All objects
OBJ = $(OBJ_COMMON) $(OBJ_2048) $(OBJ_TAQUIN) $(OBJ_SOKOBAN)

DEP = $(OBJ:.o=.d)

srcdir = src
compile = $(CXX) -c $(CPPFLAGS) $(CXXFLAGS)
link = $(CXX) $(LDFLAGS)

.SUFFIXES:
.SUFFIXES: .o .cpp
.PHONY: all clean mrproper

all: $(EXEC)

game-2048: $(OBJ_2048)

taquin: $(OBJ_TAQUIN)

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
