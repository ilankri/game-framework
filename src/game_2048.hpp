#ifndef GAME_2048_HPP
#define GAME_2048_HPP

#include "game.hpp"
#include "square_2048.hpp"
#include <utility>

class Game_2048 : public Game<Square_2048> {
public:
	Game_2048(int height);

protected:
	virtual Square_2048 random_square() const;

	virtual unsigned long long random_value() const;

private:
	bool board_change;

	vector<pair<int, int> > empty_squares;

	virtual void init();

	virtual void move(Direction dir);

	virtual bool is_over() const;

	void transpose_board();

	void pop_up_new_square();

	void slide_line(int i, Direction dir);

	void merge_line(int i, Direction dir);

	void add_empty_square(int i, int j);

	template<class It>
	int slide_line_template(It begin, It end);

	void slide_board(Direction dir, bool transpose);

	template<class It>
	void merge_line_template(It begin, It end);

	virtual bool is_mergeable(const Square_2048& sq1,
				  const Square_2048& sq2) const;

	virtual Square_2048 merge(const Square_2048& sq1,
				  const Square_2048& sq2) const;
};

#endif /* not GAME_2048_HPP */
