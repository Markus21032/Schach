#include <string>

#ifndef _FIGURE_
#define _FIGURE_
//Player 0: neutral
//Player 1: top
//Player 2: bottom

class Figure {
protected: char* sign = new char;
protected: int* playerNumber = new int;
protected: bool* allowedToMove = new bool;
public: char get_Name() { return (*sign); };
public: char get_player() { return (*playerNumber); };
public: std::string get_2print() { return (*sign) + std::to_string((*playerNumber)); };
public: void assign_to_player(int x) { *playerNumber = x; };
protected: void init_figure() { };
public: virtual bool moveFigure(int player, int c1, int l1, int c2, int l2, std::vector<std::vector<Figure*>*>chessBoard) { (*allowedToMove) = false; return allowedToMove; };
public: void delete_figure_values() { delete(sign); delete(playerNumber); };
};

class NoneFigure :public Figure {
public: void assign_to_player() { *playerNumber = 0; };
public: void init_figure() { *sign = '0'; assign_to_player(); };
public: bool moveFigure(int player, int c1, int l1, int c2, int l2, std::vector<std::vector<Figure*>*>chessBoard) { (*allowedToMove) = false; return allowedToMove; };
};
class PawnFigure :public Figure {
public: void init_figure() { *sign = 'B'; };
public: bool moveFigure(int player, int c1, int l1, int c2, int l2, std::vector<std::vector<Figure*>*>chessBoard) {
	(*allowedToMove) = false;
	if (player == 1) {
		if (l1 == 1 && (l1 + 2) == l2) {
			if (c1 == c2) {
				int l11 = l1 + 1;
				int playerJump = (*chessBoard[l11])[c2]->get_player();
				if (playerJump == 0) {
					int playerT = (*chessBoard[l2])[c2]->get_player();
					if (playerT == 0) { (*allowedToMove) = true; }
				}
			}
		}
		else if ((l1 + 1) == l2) {
			if (c1 == c2) {
				int playerT = (*chessBoard[l2])[c2]->get_player();
				if (playerT == 0) { (*allowedToMove) = true; }
			}
			else if ((c1 + 1) == c2) {
				int playerT = (*chessBoard[l2])[c2]->get_player();
				char signT = (*chessBoard[l2])[c2]->get_Name();
				if (playerT != player && 0 != playerT && signT != 'K') { (*allowedToMove) = true; }
			}
			else if ((c1 - 1) == c2) {
				int playerT = (*chessBoard[l2])[c2]->get_player();
				char signT = (*chessBoard[l2])[c2]->get_Name();
				if (playerT != player && 0 != playerT && signT != 'K') { (*allowedToMove) = true; }
			}
		}
	}
	else {
		if (l1 == 6 && (l1 - 2) == l2) {
			if (c1 == c2) {
				int playerT = (*chessBoard[l2])[c2]->get_player();
				if (playerT == 0) { (*allowedToMove) = true; }
			}
		}
		else if ((l1 - 1) == l2) {
			if (c1 == c2) {
				int playerT = (*chessBoard[l2])[c2]->get_player();
				if (playerT == 0) { (*allowedToMove) = true; }
			}
			else if ((c1 + 1) == c2) {
				int playerT = (*chessBoard[l2])[c2]->get_player();
				char signT = (*chessBoard[l2])[c2]->get_Name();
				if (playerT != player && 0 != playerT && signT != 'K') { (*allowedToMove) = true; }
			}
			else if ((c1 - 1) == c2) {
				int playerT = (*chessBoard[l2])[c2]->get_player();
				char signT = (*chessBoard[l2])[c2]->get_Name();
				if (playerT != player && 0 != playerT && signT != 'K') { (*allowedToMove) = true; }
			}
		}
	}
	return (*allowedToMove);
};
};
class KingFigure :public Figure {
public: void init_figure() { *sign = 'K'; };
public: bool moveFigure(int player, int c1, int l1, int c2, int l2, std::vector<std::vector<Figure*>*>chessBoard) {
	(*allowedToMove) = false;
	if ((l1 - 1) == l2) {
		if (c1 == c2) {
			int playerT = (*chessBoard[l2])[c2]->get_player();
			char signT = (*chessBoard[l2])[c2]->get_Name();
			if (playerT != player && signT != 'K') { (*allowedToMove) = true; }
		}
		else if ((c1 + 1) == c2) {
			int playerT = (*chessBoard[l2])[c2]->get_player();
			char signT = (*chessBoard[l2])[c2]->get_Name();
			if (playerT != player && signT != 'K') { (*allowedToMove) = true; }
		}
		else if ((c1 - 1) == c2) {
			int playerT = (*chessBoard[l2])[c2]->get_player();
			char signT = (*chessBoard[l2])[c2]->get_Name();
			if (playerT != player && signT != 'K') { (*allowedToMove) = true; }
		}
	}
	else if ((l1 + 1) == l2) {
		if (c1 == c2) {
			int playerT = (*chessBoard[l2])[c2]->get_player();
			char signT = (*chessBoard[l2])[c2]->get_Name();
			if (playerT != player && signT != 'K') { (*allowedToMove) = true; }
		}
		else if ((c1 + 1) == c2) {
			int playerT = (*chessBoard[l2])[c2]->get_player();
			char signT = (*chessBoard[l2])[c2]->get_Name();
			if (playerT != player && signT != 'K') { (*allowedToMove) = true; }
		}
		else if ((c1 - 1) == c2) {
			int playerT = (*chessBoard[l2])[c2]->get_player();
			char signT = (*chessBoard[l2])[c2]->get_Name();
			if (playerT != player && signT != 'K') { (*allowedToMove) = true; }
		}
	}
	else if (l1 == l2) {
		if ((c1 + 1) == c2) {
			int playerT = (*chessBoard[l2])[c2]->get_player();
			char signT = (*chessBoard[l2])[c2]->get_Name();
			if (playerT != player && signT != 'K') { (*allowedToMove) = true; }
		}
		else if ((c1 - 1) == c2) {
			int playerT = (*chessBoard[l2])[c2]->get_player();
			char signT = (*chessBoard[l2])[c2]->get_Name();
			if (playerT != player && signT != 'K') { (*allowedToMove) = true; }
		}
	}
	return (*allowedToMove);
}
};
class QueenFigure :public Figure {
public: void init_figure() { *sign = 'Q'; };
public: bool moveFigure(int player, int c1, int l1, int c2, int l2, std::vector<std::vector<Figure*>*>chessBoard) {
	(*allowedToMove) = false;
	bool skipsFigure = false;
	if (l1 == l2) {
		if (c2 > c1) {
			for (int i = (c1 + 1); i < c2; i++) {
				if ((*chessBoard[l1])[i]->get_player() != 0) {
					skipsFigure = true;
				}
			}
		}
		else {
			for (int i = (c1 - 1); i > c2; i--) {
				if ((*chessBoard[l1])[i]->get_player() != 0) {
					skipsFigure = true;
				}
			}
		}

		if (skipsFigure == false) {
			int playerT = (*chessBoard[l2])[c2]->get_player();
			char signT = (*chessBoard[l2])[c2]->get_Name();
			if (playerT != player && signT != 'K') { (*allowedToMove) = true; }
		}
	}
	else if (c1 == c2) {
		if (l2 > l1) {
			for (int i = (l1 + 1); i < l2; i++) {
				if ((*chessBoard[i])[c1]->get_player() != 0) {
					skipsFigure = true;
				}
			}
		}
		else {
			for (int i = (l1 - 1); i > l2; i--) {
				if ((*chessBoard[i])[c1]->get_player() != 0) {
					skipsFigure = true;
				}
			}
		}

		if (skipsFigure == false) {
			int playerT = (*chessBoard[l2])[c2]->get_player();
			char signT = (*chessBoard[l2])[c2]->get_Name();
			if (playerT != player && signT != 'K') { (*allowedToMove) = true; }
		}
	}
	else if (abs(l1 - l2) == abs(c1 - c2)) {
		if (l1 < l2) {
			if (c1 < c2) {
				int j = c1 + 1;
				for (int i = (l1 + 1); i < l2; i++) {
					if ((*chessBoard[i])[j]->get_player() != 0) {
						skipsFigure = true;
					}
					j++;
				}
			}
			else {
				int j = c1 - 1;
				for (int i = (l1 + 1); i < l2; i++) {
					if ((*chessBoard[i])[j]->get_player() != 0) {
						skipsFigure = true;
					}
					j--;
				}
			}
		}
		else {
			if (c1 < c2) {
				int j = c1 + 1;
				for (int i = (l1 - 1); i < l2; i--) {
					if ((*chessBoard[i])[j]->get_player() != 0) {
						skipsFigure = true;
					}
					j++;
				}
			}
			else {
				int j = c1 - 1;
				for (int i = (l1 - 1); i < l2; i--) {
					if ((*chessBoard[i])[j]->get_player() != 0) {
						skipsFigure = true;
					}
					j--;
				}
			}
		}

		if (skipsFigure == false) {
			int playerT = (*chessBoard[l2])[c2]->get_player();
			char signT = (*chessBoard[l2])[c2]->get_Name();
			if (playerT != player && signT != 'K') { (*allowedToMove) = true; }
		}
	}
	return (*allowedToMove);
}
};
class TowerFigure :public Figure {
public: void init_figure() { *sign = 'T'; };
public: bool moveFigure(int player, int c1, int l1, int c2, int l2, std::vector<std::vector<Figure*>*>chessBoard) {
	(*allowedToMove) = false;
	bool skipsFigure = false;
	if (l1 == l2) {
		if (c2 > c1) {
			for (int i = (c1 + 1); i < c2; i++) {
				if ((*chessBoard[l1])[i]->get_player() != 0) {
					skipsFigure = true;
				}
			}
		}
		else {
			for (int i = (c1 - 1); i > c2; i--) {
				if ((*chessBoard[l1])[i]->get_player() != 0) {
					skipsFigure = true;
				}
			}
		}

		if (skipsFigure == false) {
			int playerT = (*chessBoard[l2])[c2]->get_player();
			char signT = (*chessBoard[l2])[c2]->get_Name();
			if (playerT != player && signT != 'K') { (*allowedToMove) = true; }
		}
	}
	else if (c1 == c2) {
		if (l2 > l1) {
			for (int i = (l1 + 1); i < l2; i++) {
				if ((*chessBoard[i])[c1]->get_player() != 0) {
					skipsFigure = true;
				}
			}
		}
		else {
			for (int i = (l1 - 1); i > l2; i--) {
				if ((*chessBoard[i])[c1]->get_player() != 0) {
					skipsFigure = true;
				}
			}
		}

		if (skipsFigure == false) {
			int playerT = (*chessBoard[l2])[c2]->get_player();
			char signT = (*chessBoard[l2])[c2]->get_Name();
			if (playerT != player && signT != 'K') { (*allowedToMove) = true; }
		}
	}
	return (*allowedToMove);
}
};
class RunnerFigure :public Figure {
public: void init_figure() { *sign = 'L'; };
public: bool moveFigure(int player, int c1, int l1, int c2, int l2, std::vector<std::vector<Figure*>*>chessBoard) {
	(*allowedToMove) = false;
	bool skipsFigure = false;
	if (abs(l1 - l2) == abs(c1 - c2)) {
		if (l1 < l2) {
			if (c1 < c2) {
				int j = c1 + 1;
				for (int i = (l1 + 1); i < l2; i++) {
					if ((*chessBoard[i])[j]->get_player() != 0) {
						skipsFigure = true;
					}
					j++;
				}
			}
			else {
				int j = c1 - 1;
				for (int i = (l1 + 1); i < l2; i++) {
					if ((*chessBoard[i])[j]->get_player() != 0) {
						skipsFigure = true;
					}
					j--;
				}
			}
		}
		else {
			if (c1 < c2) {
				int j = c1 + 1;
				for (int i = (l1 - 1); i < l2; i--) {
					if ((*chessBoard[i])[j]->get_player() != 0) {
						skipsFigure = true;
					}
					j++;
				}
			}
			else {
				int j = c1 - 1;
				for (int i = (l1 - 1); i < l2; i--) {
					if ((*chessBoard[i])[j]->get_player() != 0) {
						skipsFigure = true;
					}
					j--;
				}
			}
		}

		if (skipsFigure == false) {
			int playerT = (*chessBoard[l2])[c2]->get_player();
			char signT = (*chessBoard[l2])[c2]->get_Name();
			if (playerT != player && signT != 'K') { (*allowedToMove) = true; }
		}
	}
	return (*allowedToMove);
}
};
class JumperFigure :public Figure {
public: void init_figure() { *sign = 'S'; };
public: bool moveFigure(int player, int c1, int l1, int c2, int l2, std::vector<std::vector<Figure*>*>chessBoard) {
	(*allowedToMove) = false;
	if ((l1 + 2) == l2 || (l1 - 2) == l2) {
		if ((c1 + 1) == c2 || (c1 - 1) == c2) {
			int playerT = (*chessBoard[l2])[c2]->get_player();
			char signT = (*chessBoard[l2])[c2]->get_Name();
			if (playerT != player && signT != 'K') { (*allowedToMove) = true; }
		}
	}
	else if ((c1 + 2) == c2 || (c1 - 2) == c2) {
		if ((l1 + 1) == l2 || (l1 - 1) == l2) {
			int playerT = (*chessBoard[l2])[c2]->get_player();
			char signT = (*chessBoard[l2])[c2]->get_Name();
			if (playerT != player && signT != 'K') { (*allowedToMove) = true; }
		}
	}
	return (*allowedToMove);
}
};

#endif _FIGURE_