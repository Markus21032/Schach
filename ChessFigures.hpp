#include <string>
#include <vector>
#include <memory>

#ifndef _FIGURE_
#define _FIGURE_
//Player 0: neutral 
//Player 1: top
//Player 2: bottom

class Figure {
protected: std::shared_ptr<char> sign = std::make_shared<char>();
protected: std::shared_ptr<int> playerNumber = std::make_shared<int>();
public: char get_Name() { return (*sign); };
public: int get_player() { return (*playerNumber); };
public: virtual std::string get_2print() = 0;
public: void assign_to_player(int x) { *playerNumber = x; };
protected: void init_figure() { };
public: virtual bool moveFigure(int player, int c1, int l1, int c2, int l2, std::vector<std::shared_ptr<std::vector<std::shared_ptr<Figure> > > >chessBoard) { return false; };
};

class NoneFigure :public Figure {
public: void assign_to_player() { *playerNumber = 0; };
public: virtual std::string get_2print() override {return "l";}
public: void init_figure() { *sign = '0'; assign_to_player(); };
public: bool moveFigure (int player, int c1, int l1, int c2, int l2, std::vector<std::shared_ptr<std::vector<std::shared_ptr<Figure> > > >chessBoard) override { return false; };
};
class PawnFigure :public Figure {
public: void init_figure() { *sign = 'B'; };
std::string get_2print() override {
	if(*playerNumber == 1){
		//return u8"\u2659";
		return "k";
	}
	else {
		//return u8"\u265F";
		return "K";
	}
}
public: bool moveFigure(int player, int c1, int l1, int c2, int l2, std::vector<std::shared_ptr<std::vector<std::shared_ptr<Figure> > > >chessBoard) override {
	if(c2 > 7 || c2 < 0 || l2 < 0 || l2 > 7) {return false;} //if figure would move out of the board
	if (player == 1) {
		if (l1 == 1 && (l1 + 2) == l2) {
			if (c1 == c2) {
				int l11 = l1 + 1;
				int playerJump = (*chessBoard[l11])[c2]->get_player();
				if (playerJump == 0) {
					int playerT = (*chessBoard[l2])[c2]->get_player();
					if (playerT == 0) { return true; }
				}
			}
		}
		else if ((l1 + 1) == l2) {
			if (c1 == c2) {
				int playerT = (*chessBoard[l2])[c2]->get_player();
				if (playerT == 0) { return true; }
			}
			else if ((c1 + 1) == c2) {
				int playerT = (*chessBoard[l2])[c2]->get_player();
				char signT = (*chessBoard[l2])[c2]->get_Name();
				if (playerT != player && 0 != playerT && signT != 'K') { return true; }
			}
			else if ((c1 - 1) == c2) {
				int playerT = (*chessBoard[l2])[c2]->get_player();
				char signT = (*chessBoard[l2])[c2]->get_Name();
				if (playerT != player && 0 != playerT && signT != 'K') { return true; }
			}
		}
	}
	else {
		if (l1 == 6 && (l1 - 2) == l2) {
			if (c1 == c2) {
				int playerT = (*chessBoard[l2])[c2]->get_player();
				if (playerT == 0) { return true; }
			}
		}
		else if ((l1 - 1) == l2) {
			if (c1 == c2) {
				int playerT = (*chessBoard[l2])[c2]->get_player();
				if (playerT == 0) { return true; }
			}
			else if ((c1 + 1) == c2) {
				int playerT = (*chessBoard[l2])[c2]->get_player();
				char signT = (*chessBoard[l2])[c2]->get_Name();
				if (playerT != player && 0 != playerT && signT != 'K') { return true; }
			}
			else if ((c1 - 1) == c2) {
				int playerT = (*chessBoard[l2])[c2]->get_player();
				char signT = (*chessBoard[l2])[c2]->get_Name();
				if (playerT != player && 0 != playerT && signT != 'K') { return true; }
			}
		}
	}
	return false;
};
};
class KingFigure :public Figure {
public: void init_figure() { *sign = 'K'; };
std::string get_2print() override {
	if(*playerNumber == 1){
		return u8"\u2654";
	}
	else if(*playerNumber == 2){
		return u8"\u265A";
	}
	return "";
}
public: bool moveFigure(int player, int c1, int l1, int c2, int l2, std::vector<std::shared_ptr<std::vector<std::shared_ptr<Figure> > > >chessBoard) override{
	if(c2 > 7 || c2 < 0 || l2 < 0 || l2 > 7) {return false;} //if figure would move out of the board
	if ((l1 - 1) == l2) {
		if (c1 == c2) {
			int playerT = (*chessBoard[l2])[c2]->get_player();
			char signT = (*chessBoard[l2])[c2]->get_Name();
			if (playerT != player && signT != 'K') { return true; }
		}
		else if ((c1 + 1) == c2) {
			int playerT = (*chessBoard[l2])[c2]->get_player();
			char signT = (*chessBoard[l2])[c2]->get_Name();
			if (playerT != player && signT != 'K') { return true; }
		}
		else if ((c1 - 1) == c2) {
			int playerT = (*chessBoard[l2])[c2]->get_player();
			char signT = (*chessBoard[l2])[c2]->get_Name();
			if (playerT != player && signT != 'K') { return true; }
		}
	}
	else if ((l1 + 1) == l2) {
		if (c1 == c2) {
			int playerT = (*chessBoard[l2])[c2]->get_player();
			char signT = (*chessBoard[l2])[c2]->get_Name();
			if (playerT != player && signT != 'K') { return true; }
		}
		else if ((c1 + 1) == c2) {
			int playerT = (*chessBoard[l2])[c2]->get_player();
			char signT = (*chessBoard[l2])[c2]->get_Name();
			if (playerT != player && signT != 'K') { return true; }
		}
		else if ((c1 - 1) == c2) {
			int playerT = (*chessBoard[l2])[c2]->get_player();
			char signT = (*chessBoard[l2])[c2]->get_Name();
			if (playerT != player && signT != 'K') { return true; }
		}
	}
	else if (l1 == l2) {
		if ((c1 + 1) == c2) {
			int playerT = (*chessBoard[l2])[c2]->get_player();
			char signT = (*chessBoard[l2])[c2]->get_Name();
			if (playerT != player && signT != 'K') { return true; }
		}
		else if ((c1 - 1) == c2) {
			int playerT = (*chessBoard[l2])[c2]->get_player();
			char signT = (*chessBoard[l2])[c2]->get_Name();
			if (playerT != player && signT != 'K') { return true; }
		}
	}
	return false;
}
};
class QueenFigure :public Figure {
public: void init_figure() { *sign = 'Q'; };
std::string get_2print() override {
	if(*playerNumber == 1){
		return u8"\u2655";
	}
	else if(*playerNumber == 2){
		return u8"\u265B";
	}
	return "";
}
public: bool moveFigure(int player, int c1, int l1, int c2, int l2, std::vector<std::shared_ptr<std::vector<std::shared_ptr<Figure> > > >chessBoard) override {
	if(c2 > 7 || c2 < 0 || l2 < 0 || l2 > 7) {return false;} //if figure would move out of the board
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
			if (playerT != player && signT != 'K') { return true; }
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
			if (playerT != player && signT != 'K') { return true; }
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
			if (playerT != player && signT != 'K') { return true; }
		}
	}
	return false;
}
};
class TowerFigure :public Figure {
public: void init_figure() { *sign = 'T'; };
std::string get_2print() override {
	if(*playerNumber == 1){
		return u8"\u2656";
	}
	else if(*playerNumber == 2){
		return u8"\u265C";
	}
	return "";
}
public: bool moveFigure(int player, int c1, int l1, int c2, int l2, std::vector<std::shared_ptr<std::vector<std::shared_ptr<Figure> > > >chessBoard) override{
	if(c2 > 7 || c2 < 0 || l2 < 0 || l2 > 7) {return false;} //if figure would move out of the board
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
			if (playerT != player && signT != 'K') { return true; }
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
			if (playerT != player && signT != 'K') { return true; }
		}
	}
	return true;
}
};
class RunnerFigure :public Figure {
public: void init_figure() { *sign = 'L'; };
std::string get_2print() override {
	if(*playerNumber == 1){
		return u8"\u2657";
	}
	else if(*playerNumber == 2){
		return u8"\u265D";
	}
	return "";
}
public: bool moveFigure(int player, int c1, int l1, int c2, int l2, std::vector<std::shared_ptr<std::vector<std::shared_ptr<Figure> > > >chessBoard) override {
	if(c2 > 7 || c2 < 0 || l2 < 0 || l2 > 7) {return false;} //if figure would move out of the board
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
			if (playerT != player && signT != 'K') { return true; }
		}
	}
	return false;
}
};
class JumperFigure :public Figure {
public: void init_figure() { *sign = 'S'; };
std::string get_2print() override {
	if(*playerNumber == 1){
		return u8"\u2658";
	}
	else if(*playerNumber == 2){
		return u8"\u265E";
	}
	return "";
}
public: bool moveFigure(int player, int c1, int l1, int c2, int l2, std::vector<std::shared_ptr<std::vector<std::shared_ptr<Figure> > > >chessBoard) override {
	if(c2 > 7 || c2 < 0 || l2 < 0 || l2 > 7) {return false;} //if figure would move out of the board
	if ((l1 + 2) == l2 || (l1 - 2) == l2) {
		if ((c1 + 1) == c2 || (c1 - 1) == c2) {
			int playerT = (*chessBoard[l2])[c2]->get_player();
			char signT = (*chessBoard[l2])[c2]->get_Name();
			if (playerT != player && signT != 'K') { return true; }
		}
	}
	else if ((c1 + 2) == c2 || (c1 - 2) == c2) {
		if ((l1 + 1) == l2 || (l1 - 1) == l2) {
			int playerT = (*chessBoard[l2])[c2]->get_player();
			char signT = (*chessBoard[l2])[c2]->get_Name();
			if (playerT != player && signT != 'K') { return true; }
		}
	}
	return false;
}
};

#endif //_FIGURE_