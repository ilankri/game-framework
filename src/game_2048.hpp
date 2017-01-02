#ifndef GAME_2048_HPP
#define GAME_2048_HPP

#include <list>
#include <utility>

#include "game.hpp"
#include "square_2048.hpp"

class Game_2048 : public Game<Square_2048> {
public:
	/* We suppose that the board is a square.  */
	Game_2048(int height);

protected:
	/* Possible values for squares.  */
	vector<long long> values;

	/* Possible actions for squares.  */
	vector<Action_2048> actions;

	/*
	 * Test if sq1 and sq2 are mergeable even if there are not
	 * equal.  By default, mergeable(sq1, sq2) returns false: two
	 * squares can only merge by equality.  When (re)defining this
	 * function, don't care about empty squares: an empty square
	 * cannot be merged with another.
	 */
	virtual bool mergeable(const Square_2048& sq1,
			       const Square_2048& sq2) const;

private:
	/* Whether the last movement change game configuration.  */
	bool board_change;

	/* Whether the board is full.  */
	bool full;

	/*
	 * Positions of empty squares.  Useful to pop up randomly a new
	 * square after a movement.
	 */
	list<pair<int, int> > empty_squares;

	/*
	 * Return the result of merging sq1 with sq2.  This function
	 * doesn't check if sq1 and sq2 are mergeable.
	 */
	virtual Square_2048 merge(const Square_2048& sq1,
				  const Square_2048& sq2) const;

	/* Transpose the board like a square matrix.  */
	void transpose_board();

	/* Add (i, j) to empty_squares.  */
	void add_empty_square(int i, int j);

	/* Update the board by adding a new nonempty square.  */
	void pop_up_new_square();

	/*
	 * Compute all the mergings for line i of the board without
	 * sliding the line.
	 */
	void merge_line(int i, Direction dir);

	/*
	 * Slide all squares of line i of the board in the given
	 * direction (left or right).
	 */
	void slide_line(int i, Direction dir);

	/*
	 * Slide the board in the given direction (left or right).  If
	 * transpose is true, then the board is transposed before and
	 * after the sliding operation.
	 */
	void slide_board(Direction dir, bool transpose);

	/*
	 * Return true if and only if sq1 and sq2 are mergeable and both
	 * nonempty.
	 */
	bool mergeable_and_nonempty(const Square_2048& sq1,
				    const Square_2048& sq2) const;

	/*
	 * Compute all the mergings for a single line from position
	 * begin to position end.
	 */
	template<class It>
	void merge_line_template(It begin, It end);

	/*
	 * Slide the squares of a merged line and return the index of
	 * the first empty square on the current line beginning from the
	 * edge of the board.
	 */
	template<class It>
	int slide_merged_line(It begin, It end);

	virtual void init();

	virtual void move(Direction dir);

	virtual bool is_over() const;
};

#endif /* not GAME_2048_HPP */
