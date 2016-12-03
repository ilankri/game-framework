EXEC=Jeu
CPP=g++
OPT=-W -Wall -Wextra -std=c++11
SRC= main.cpp Jeu.cpp Jeu.hpp Taquin.cpp Taquin.hpp
OBJ= $(SRC:.cpp=.o)


all: $(EXEC)

$(EXEC) : $(OBJ)
	$(CPP) $(OPT) -o $(EXEC) $^

main.o: main.cpp
	$(CPP) $(OPT) -c $^

%.o: %.cpp %.hpp
	$(CPP) $(OPT) -c $^


clean:
	@rm *.o

mrproper: clean
	@rm -rf *.gch
