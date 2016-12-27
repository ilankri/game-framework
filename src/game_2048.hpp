#ifndef GAME_2048_HPP
#define GAME_2048_HPP

#include "game.hpp"
#include "square_2048.hpp"

class Game_2048 : public Game<Square_2048> {
public:
	Game_2048(int height, int width);

private:
	int first_empty_old_index;

	int first_empty_new_index;

	bool board_change;

	virtual int random_value();

	virtual Square_2048 random_square();

	virtual void init();

	virtual void move(Direction dir);

	virtual bool is_over() const;

	void transpose_board();

	void slide_line(int i, Direction dir);

	void merge_line(int i, Direction dir);

	virtual bool fill_first_empty_square();

	template<class It>
	void slide_line_aux(It begin, It end);
	void slide_board(Direction dir, bool need_transpose);

	template<class It>
void merge_line_aux(It begin, It end);

};

#endif /* not GAME_2048_HPP */
