#include "sokoban.hpp"

const int Sokoban::min_width = 10;
const int Sokoban::min_height = 10;

ostream& operator<<(ostream& o, CaseSok const& c) {
	switch (c) {
	case CaseSok::empty:
		o << " ";
		break;
	case CaseSok::wall:
		o << "=";
		break;
	case CaseSok::pers:
		o << "*";
		break;
	case CaseSok::crate:
		o << "x";
		break;
	case CaseSok::target:
		o << "o";
		break;
	case CaseSok::crate_target:
		o << "ø";
		break;
	case CaseSok::pers_target:
		o << "@";
		break;
	}
	return o;
}

Sokoban::Sokoban(int height, int width, int nb_crates) :
	Game<CaseSok>(max(Sokoban::min_height,height),
		      max(Sokoban::min_width,width))
{
	int nb_max = sqrt(this -> width * this -> height) /2;
	
	if (nb_crates == -1)
		this -> nb_crates = nb_max;
	else {
		this -> nb_crates = max(0,nb_crates);
		this -> nb_crates = min(this -> nb_crates, nb_max);
	}

}

Sokoban::~Sokoban() {}

void Sokoban::print_board(ostream& o) const
{

	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			o << board[i][j] << " ";
		}
		o << endl;
	}

	o << endl;
	
	o << "[Legend]" << endl;
	
	o << CaseSok::wall << " : wall" << endl;
	
	o << CaseSok::pers << " : character (" << pos_h << ",";
	
	o << pos_w << ")" << endl;
	
	o << CaseSok::crate << " : crate" << endl;
	
	o << CaseSok::target << " : target" << endl;
	
	o << CaseSok::crate_target << " : crate set on a target" << endl;

	o << CaseSok::pers_target << " : character set on a target" << endl;

	o << endl;
}

void Sokoban::init()
{
	//cout << "init()" << endl;
	set_walls();
	set_targets_crates();
	set_pers();
	
}

void Sokoban::set_walls()
{
	//cout <<"placer_murs()" << endl;
	srand(time(nullptr));

	/*
	 * Les coins des murs externes ne seront pas forcément au bord
	 * du plateau, afin d'obtenir la disposition la plus aléatoire
	 * possible.
	 */
	i_top_left = rand() % (height / 3);
	j_top_left = rand() % (width / 3);

	i_top_right = rand() % (height / 3);
	j_top_right = width - 1 - rand() % (width / 3);

	i_bottom_left = height - 1 - rand() % (height / 3);
	j_bottom_left = rand() % (height / 3);

	i_bottom_right = height - 1 - rand() % (height / 3);
	j_bottom_right = width - 1 - rand() % (height / 3);

	/*
	 * Coin haut-gauche : on prolonge le mur jusqu'au bord du
	 * plateau.
	 */
	for (int i = i_top_left; i >= 0; i--) {
		board[i][j_top_left] = CaseSok::wall;
	}
	for (int j = j_top_left; j >= 0; j--) {
		board[i_top_left][j] = CaseSok::wall;
	}

	/* Coin haut-droite */
	for (int i = i_top_right; i >= 0; i--) {
		board[i][j_top_right] = CaseSok::wall;
	}
	for (int j = j_top_right; j < width; j++) {
		board[i_top_right][j] = CaseSok::wall;
	}

	/* Coin bas-gauche */
	for (int i = i_bottom_left; i < height; i++) {
		board[i][j_bottom_left] = CaseSok::wall;
	}
	for (int j = j_bottom_left; j >= 0; j--) {
		board[i_bottom_left][j] = CaseSok::wall;
	}

	/* Coin bas-droite */
	for (int i = i_bottom_right; i < height; i++) {
		board[i][j_bottom_right] = CaseSok::wall;
	}
	for (int j = j_bottom_right; j < width; j++) {
		board[i_bottom_right][j] = CaseSok::wall;
	}
	setExternalWalls();
	setInternalWalls();
}

void Sokoban::setExternalWalls()
{

	/* On termine de placer les murs externes.  */
	for (int i = i_top_left; i < i_bottom_left; i++) {
		board[i][0] = CaseSok::wall;
	}

	for (int j = j_top_left; j < j_top_right; j++) {
		board[0][j] = CaseSok::wall;
	}

	for (int j = j_bottom_left; j < j_bottom_right; j++) {
		board[height - 1][j] = CaseSok::wall;
	}

	for (int i = i_top_right; i < i_bottom_right; i++) {
		board[i][width - 1] = CaseSok::wall;
	}

}

void Sokoban::setInternalWalls()
{

	/*
	 * On décide aléatoirement si on place des murs internes ou pas.
	 */
	int j_h_mid = (j_top_left + j_top_right) / 2;
	int j_b_mid = (j_bottom_left + j_bottom_right) / 2;
	int i_mid_g = (i_top_left + i_bottom_left) / 2;
	int i_mid_d = (i_top_right + i_bottom_right) / 2;

	int lim_h_mid = 1 + rand() % (height / 4);
	int lim_b_mid = 1 + rand() % (height / 4);
	int lim_mid_g = 1 + rand() % (width / 4);
	int lim_mid_d = 1 + rand() % (width / 4);

	for (int i = 0; i < lim_h_mid; i++)
		board[i][j_h_mid] = CaseSok::wall;

	for (int i = height - 1; i > height - 1 - lim_b_mid; i--)
		board[i][j_b_mid] = CaseSok::wall;

	for (int j = 0; j < lim_mid_g; j++)
		board[i_mid_g][j] = CaseSok::wall;

	for(int j = width - 1; j > width - 1 -lim_mid_d; j--)
		board[i_mid_d][j] = CaseSok::wall;
}

void Sokoban::set_targets_crates()
{
	//cout << "placer_buts_caisses()" << endl;
	for (int k = 0; k < nb_crates; k++) {
		int l_c;
		int h_c;

		/*
		 * On place les buts aléatoirement sur le plateau, en
		 * vérifiant qu'ils ne soient jamais en dehors des murs.
		 */
		do {
			l_c = rand() % width;
			h_c = rand() % height;
		} while (board[h_c][l_c] != CaseSok::empty ||
			 outsideOfWalls(h_c, l_c));
		board[h_c][l_c] = CaseSok::target;

		/*
		 * On place autant de caisses que de buts, en vérifiant
		 * toujours qu'elles ne soient jamais en dehors des
		 * murs.  De plus, pour que la grille soit résolvable,
		 * les caisses ne doivent jamais être placées dans une
		 * zone entourée de murs.  S'il y a un mur
		 * devant/derrière et à gauche/à droite, la caisse ne
		 * pourra pas être déplacée, et donc le jeu sera bloqué.
		 */
		do {
			l_c = rand() % width;
			h_c = rand() % height;
		} while (!freeZone(h_c, l_c));
		board[h_c][l_c] = CaseSok::crate;
	}
}

bool Sokoban::freeZone(int h_c, int l_c) const
{

	if (outsideOfWalls(h_c,l_c))
		return false;
	if (board[h_c][l_c] != CaseSok::empty)
		return false;
	if (board[h_c + 1][l_c] != CaseSok::empty)
		return false;
	if (board[h_c - 1][l_c] != CaseSok::empty)
		return false;
	if (board[h_c][l_c - 1] != CaseSok::empty)
		return false;
	if (board[h_c][l_c + 1] != CaseSok::empty)
		return false;

	return true;
}

bool Sokoban::outsideOfWalls(int h_c, int l_c) const
{
	if (h_c >= height - 2 || h_c <= 1)
		return true;
	if (l_c >= width - 2 || l_c <= 1)
		return true;

	if (h_c <= i_top_left && l_c <= j_top_left)
		return true;
	if (h_c >= i_bottom_left && l_c <= j_bottom_left)
		return true;
	if (h_c <= i_top_right && l_c >= j_top_right)
		return true;
	if (h_c >= i_bottom_right && l_c >= j_bottom_right)
		return true;

	return false;
}

void Sokoban::set_pers()
{

	/* on vérifie s'il n'y a pas déjà un pesonnage sur le plateau */
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			if (board[i][j] == CaseSok::pers)
				return;
		}
	}
	//cout << "set_pers()" << endl;


	/*
	 * Pour que le personnage puisse effectuer au moins un
	 * mouvement, on le place dans une case entourée uniquement de
	 * cases vides, toujours à l'intérieur de la zone délimitée par
	 * les murs externes.
	 */

	do {
		pos_w = 1 + rand() % (width - 2);
		pos_h = 1 + rand() % (height - 2);
	}
	while (!freeZone(pos_h, pos_w));
	board[pos_h][pos_w] = CaseSok::pers;
}

void Sokoban::move(Direction s)
{

	int new_pos_h = pos_h;
	int new_pos_w = pos_w;
	int sens_h = 0;
	int sens_l = 0;

	CaseSok& source = board[pos_h][pos_w];
	switch(s) {
	case Direction::up:
		new_pos_h -= 1;
		sens_h = -1;
		break;
	case Direction::down:
		new_pos_h += 1;
		sens_h = 1;
		break;
	case Direction::left:
		new_pos_w -= 1;
		sens_l = -1;
		break;
	case Direction::right:
		new_pos_w += 1;
		sens_l = 1;
		break;
	default:
		break;
	}

	CaseSok& dest = board[new_pos_h][new_pos_w];
	CaseSok& derriere =
		board[new_pos_h + sens_h][new_pos_w + sens_l];

	/*
	 * Si la case juste au-dessus est vide, le personnage peut s'y
	 * déplacer sans condition.
	 */
	if (dest == CaseSok::empty || dest == CaseSok::target) {
		dest = (dest == CaseSok::empty) ?
			CaseSok::pers : CaseSok::pers_target;
		if (source == CaseSok::pers)
			source = CaseSok::empty;
		else if (source == CaseSok::pers_target)
			source = CaseSok::target;
		pos_h = new_pos_h;
		pos_w = new_pos_w;
		score++;
	}

	/*
	 * Si la case juste au-dessus contient une caisse, elle ne peut
	 * être poussée que si la case située derrière est vide ou
	 * contient un but.
	 */
	else if (dest == CaseSok::crate) {
		/* déplacement d'une caisse sur une case vide */
		if (derriere == CaseSok::empty) {
			derriere = CaseSok::crate;
			dest = CaseSok::pers;
			if (source == CaseSok::pers)
				source = CaseSok::empty;
			else if (source == CaseSok::pers_target)
				source = CaseSok::target;
			pos_h = new_pos_h;
			pos_w = new_pos_w;
			score++;
		} else if (derriere == CaseSok::target) {
			/* déplacement d'une caisse sur un but */
			derriere = CaseSok::crate_target;
			dest = CaseSok::pers;
			if (source == CaseSok::pers)
				source = CaseSok::empty;
			else if (source == CaseSok::pers_target)
				source = CaseSok::target;
			pos_h = new_pos_h;
			pos_w = new_pos_w;
			score++;
		}
	}

	/*
	 * Si la case du dessus contient un but occupé par une caisse,
	 * cette dernière peut être poussée s'il y a un autre but ou une
	 * case vide derrière.
	 */
	else if (dest == CaseSok::crate_target) {

		/* d'un but vers un autre */
		if (derriere == CaseSok::target) {
			derriere = CaseSok::crate_target;
			dest = CaseSok::pers_target;
			if (source == CaseSok::pers)
				source = CaseSok::empty;
			else if (source == CaseSok::pers_target)
				source = CaseSok::target;
			pos_h = new_pos_h;
			pos_w = new_pos_w;
			score++;
		}

		/* d'un but vers une case vide */
		else if (derriere == CaseSok::empty) {
			derriere = CaseSok::crate;
			dest = CaseSok::pers_target;
			if (source == CaseSok::pers)
				source = CaseSok::empty;
			else if (source == CaseSok::pers_target)
				source = CaseSok::target;
			pos_h = new_pos_h;
			pos_w = new_pos_w;
			score++;
		}
	}

}

bool Sokoban::is_over() const
{
	if (is_stuck())
		return true;
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			if (board[i][j] == CaseSok::target ||
			    board[i][j] == CaseSok::crate)
				return false;
		}
	}
	return true;
}

bool Sokoban::is_stuck() const
{
	/*
	 * Un bloquage peut survenir lorsqu'une caisse ne peut plus être
	 * déplacée, c'est à dire lorsqu'il y a un mur derrière et sur
	 * l'un des côtés (gauche/droite).
	 */
	for (int i = 1; i < height - 1; i++) {
		for (int j = 1; j < width - 1; j++) {
			if (board[i][j] == CaseSok::crate &&
			    (board[i - 1][j] == CaseSok::wall ||
			     board[i + 1][j] == CaseSok::wall) &&
			    (board[i][j - 1] == CaseSok::wall ||
			     board[i][j + 1] == CaseSok::wall)) {
				return true;
			}
		}
	}
	return false;
}
