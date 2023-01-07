#include <string>
#include <vector>
#include <memory>

#ifndef _FIGURE_
#define _FIGURE_
//Player 0: neutral 
//Player 1: top
//Player 2: bottom

class Figure {
protected: 	char sign;
			int playerNumber;
			int row;
			int column;			

public: 	char get_Name() { return sign; };
			int get_player() { return playerNumber; };
			int getRow(){return row;};
			int getColumn(){return column;};
			void setCoordinates(int row, int column){this->row = row; this->column = column;};
			virtual std::string get_2print() = 0;
			virtual void assign_to_player(int x) { playerNumber = x; };
			virtual void init_figure() = 0;
			virtual bool isValidMove(int player,  int rowTarget, int colTarget, std::vector<std::shared_ptr<std::vector<std::shared_ptr<Figure>>>>chessBoard) { return false; };
};

class NoneFigure :public Figure {
public: virtual std::string get_2print() override {return " ";}
public: void init_figure() { sign = '0'; assign_to_player(0); };
public: bool isValidMove (int player, int rowTarget, int colTarget, std::vector<std::shared_ptr<std::vector<std::shared_ptr<Figure>>>>chessBoard) override { return false; };
};

class PawnFigure :public Figure {
public: void init_figure() { sign = 'B'; };
std::string get_2print() override {
	if(playerNumber == 1){
		return u8"\u2659";
	}
	else {
		return u8"\u265F";
	}
}
public: bool isValidMove(int player, int rowTarget, int colTarget, std::vector<std::shared_ptr<std::vector<std::shared_ptr<Figure>>>>chessBoard) override{
	if(colTarget > 7 || colTarget < 0 || rowTarget < 0 || rowTarget > 7) {return false;} //if figure would move out of the board
	if (player == 1) {
		if (row == 1 && (row + 2) == rowTarget) {
			if (column == colTarget) {
				int l11 = row + 1;
				int playerJump = (*chessBoard[l11])[colTarget]->get_player();
				if (playerJump == 0) {
					int playerT = (*chessBoard[rowTarget])[colTarget]->get_player();
					if (playerT == 0) { return true; }
				}
			}
		}
		else if ((row + 1) == rowTarget) {
			if (column == colTarget) {
				int playerT = (*chessBoard[rowTarget])[colTarget]->get_player();
				if (playerT == 0) { return true; }
			}
			else if ((column + 1) == colTarget) {
				int playerT = (*chessBoard[rowTarget])[colTarget]->get_player();
				char signT = (*chessBoard[rowTarget])[colTarget]->get_Name();
				if (playerT != player && 0 != playerT && signT != 'K') { return true; }
			}
			else if ((column - 1) == colTarget) {
				int playerT = (*chessBoard[rowTarget])[colTarget]->get_player();
				char signT = (*chessBoard[rowTarget])[colTarget]->get_Name();
				if (playerT != player && 0 != playerT && signT != 'K') { return true; }
			}
		}
	}
	else {
		if (row == 6 && (row - 2) == rowTarget) {
			if (column == colTarget) {
				int playerT = (*chessBoard[rowTarget])[colTarget]->get_player();
				if (playerT == 0) { return true; }
			}
		}
		else if ((row - 1) == rowTarget) {
			if (column == colTarget) {
				int playerT = (*chessBoard[rowTarget])[colTarget]->get_player();
				if (playerT == 0) { return true; }
			}
			else if ((column + 1) == colTarget) {
				int playerT = (*chessBoard[rowTarget])[colTarget]->get_player();
				char signT = (*chessBoard[rowTarget])[colTarget]->get_Name();
				if (playerT != player && 0 != playerT && signT != 'K') { return true; }
			}
			else if ((column - 1) == colTarget) {
				int playerT = (*chessBoard[rowTarget])[colTarget]->get_player();
				char signT = (*chessBoard[rowTarget])[colTarget]->get_Name();
				if (playerT != player && 0 != playerT && signT != 'K') { return true; }
			}
		}
	}
	return false;
};
};
class KingFigure :public Figure {
public: void init_figure() { sign = 'K'; };
std::string get_2print() override {
	if(playerNumber == 1){
		return u8"\u2654";
	}
	else if(playerNumber == 2){
		return u8"\u265A";
	}
	return "";
}
public: bool isValidMove(int player, int rowTarget, int colTarget, std::vector<std::shared_ptr<std::vector<std::shared_ptr<Figure>>>>chessBoard) override{
	if(colTarget > 7 || colTarget < 0 || rowTarget < 0 || rowTarget > 7) {return false;} //if figure would move out of the board
	if ((row - 1) == rowTarget) {
		if (column == colTarget) {
			int playerT = (*chessBoard[rowTarget])[colTarget]->get_player();
			char signT = (*chessBoard[rowTarget])[colTarget]->get_Name();
			if (playerT != player && signT != 'K') { return true; }
		}
		else if ((column + 1) == colTarget) {
			int playerT = (*chessBoard[rowTarget])[colTarget]->get_player();
			char signT = (*chessBoard[rowTarget])[colTarget]->get_Name();
			if (playerT != player && signT != 'K') { return true; }
		}
		else if ((column - 1) == colTarget) {
			int playerT = (*chessBoard[rowTarget])[colTarget]->get_player();
			char signT = (*chessBoard[rowTarget])[colTarget]->get_Name();
			if (playerT != player && signT != 'K') { return true; }
		}
	}
	else if ((row + 1) == rowTarget) {
		if (column == colTarget) {
			int playerT = (*chessBoard[rowTarget])[colTarget]->get_player();
			char signT = (*chessBoard[rowTarget])[colTarget]->get_Name();
			if (playerT != player && signT != 'K') { return true; }
		}
		else if ((column + 1) == colTarget) {
			int playerT = (*chessBoard[rowTarget])[colTarget]->get_player();
			char signT = (*chessBoard[rowTarget])[colTarget]->get_Name();
			if (playerT != player && signT != 'K') { return true; }
		}
		else if ((column - 1) == colTarget) {
			int playerT = (*chessBoard[rowTarget])[colTarget]->get_player();
			char signT = (*chessBoard[rowTarget])[colTarget]->get_Name();
			if (playerT != player && signT != 'K') { return true; }
		}
	}
	else if (row == rowTarget) {
		if ((column + 1) == colTarget) {
			int playerT = (*chessBoard[rowTarget])[colTarget]->get_player();
			char signT = (*chessBoard[rowTarget])[colTarget]->get_Name();
			if (playerT != player && signT != 'K') { return true; }
		}
		else if ((column - 1) == colTarget) {
			int playerT = (*chessBoard[rowTarget])[colTarget]->get_player();
			char signT = (*chessBoard[rowTarget])[colTarget]->get_Name();
			if (playerT != player && signT != 'K') { return true; }
		}
	}
	return false;
}
};
class QueenFigure :public Figure {
public: void init_figure() { sign = 'Q'; };
std::string get_2print() override {
	if(playerNumber == 1){
		return u8"\u2655";
	}
	else if(playerNumber == 2){
		return u8"\u265B";
	}
	return "";
}
public: bool isValidMove(int player, int rowTarget, int colTarget, std::vector<std::shared_ptr<std::vector<std::shared_ptr<Figure>>>>chessBoard) override{
	if(colTarget > 7 || colTarget < 0 || rowTarget < 0 || rowTarget > 7) {return false;} //if figure would move out of the board
	bool skipsFigure = false;
	if (row == rowTarget) {
		if (colTarget >column) {
			for (int i = (column + 1); i < colTarget; i++) {
				if ((*chessBoard[row])[i]->get_player() != 0) {
					skipsFigure = true;
				}
			}
		}
		else {
			for (int i = (column - 1); i > colTarget; i--) {
				if ((*chessBoard[row])[i]->get_player() != 0) {
					skipsFigure = true;
				}
			}
		}

		if (skipsFigure == false) {
			int playerT = (*chessBoard[rowTarget])[colTarget]->get_player();
			char signT = (*chessBoard[rowTarget])[colTarget]->get_Name();
			if (playerT != player && signT != 'K') { return true; }
		}
	}
	else if (column == colTarget) {
		if (rowTarget >row ) {
			for (int i = (row + 1); i < rowTarget; i++) {
				if ((*chessBoard[i])[column]->get_player() != 0) {
					skipsFigure = true;
				}
			}
		}
		else {
			for (int i = (row - 1); i > rowTarget; i--) {
				if ((*chessBoard[i])[column]->get_player() != 0) {
					skipsFigure = true;
				}
			}
		}

		if (skipsFigure == false) {
			int playerT = (*chessBoard[rowTarget])[colTarget]->get_player();
			char signT = (*chessBoard[rowTarget])[colTarget]->get_Name();
			if (playerT != player && signT != 'K') { return true; }
		}
	}
	else if (abs(row - rowTarget) == abs(column - colTarget)) {
		if (row < rowTarget) {
			if (column < colTarget) {
				int j = column + 1;
				for (int i = (row + 1); i < rowTarget; i++) {
					if ((*chessBoard[i])[j]->get_player() != 0) {
						skipsFigure = true;
					}
					j++;
				}
			}
			else {
				int j = column - 1;
				for (int i = (row + 1); i < rowTarget; i++) {
					if ((*chessBoard[i])[j]->get_player() != 0) {
						skipsFigure = true;
					}
					j--;
				}
			}
		}
		else {
			if (column < colTarget) {
				int j = column + 1;
				for (int i = (row - 1); i < rowTarget; i--) {
					if ((*chessBoard[i])[j]->get_player() != 0) {
						skipsFigure = true;
					}
					j++;
				}
			}
			else {
				int j = column - 1;
				for (int i = (row - 1); i < rowTarget; i--) {
					if ((*chessBoard[i])[j]->get_player() != 0) {
						skipsFigure = true;
					}
					j--;
				}
			}
		}

		if (skipsFigure == false) {
			int playerT = (*chessBoard[rowTarget])[colTarget]->get_player();
			char signT = (*chessBoard[rowTarget])[colTarget]->get_Name();
			if (playerT != player && signT != 'K') { return true; }
		}
	}
	return false;
}
};
class TowerFigure :public Figure {
public: void init_figure() { sign = 'T'; };
std::string get_2print() override {
	if(playerNumber == 1){
		return u8"\u2656";
	}
	else if(playerNumber == 2){
		return u8"\u265C";
	}
	return "";
}
public: bool isValidMove(int player, int rowTarget, int colTarget, std::vector<std::shared_ptr<std::vector<std::shared_ptr<Figure>>>>chessBoard) override{
	if(colTarget > 7 || colTarget < 0 || rowTarget < 0 || rowTarget > 7) {return false;} //if figure would move out of the board
	bool skipsFigure = false;
	if (row == rowTarget) {
		if (colTarget >column) {
			for (int i = (column + 1); i < colTarget; i++) {
				if ((*chessBoard[row])[i]->get_player() != 0) {
					skipsFigure = true;
				}
			}
		}
		else {
			for (int i = (column - 1); i > colTarget; i--) {
				if ((*chessBoard[row])[i]->get_player() != 0) {
					skipsFigure = true;
				}
			}
		}

		if (skipsFigure == false) {
			int playerT = (*chessBoard[rowTarget])[colTarget]->get_player();
			char signT = (*chessBoard[rowTarget])[colTarget]->get_Name();
			if (playerT != player && signT != 'K') { return true; }
		}
	}
	else if (column == colTarget) {
		if (rowTarget >row ) {
			for (int i = (row + 1); i < rowTarget; i++) {
				if ((*chessBoard[i])[column]->get_player() != 0) {
					skipsFigure = true;
				}
			}
		}
		else {
			for (int i = (row - 1); i > rowTarget; i--) {
				if ((*chessBoard[i])[column]->get_player() != 0) {
					skipsFigure = true;
				}
			}
		}

		if (skipsFigure == false) {
			int playerT = (*chessBoard[rowTarget])[colTarget]->get_player();
			char signT = (*chessBoard[rowTarget])[colTarget]->get_Name();
			if (playerT != player && signT != 'K') { return true; }
		}
	}
	return true;
}
};
class RunnerFigure :public Figure {
public: void init_figure() { sign = 'L'; };
std::string get_2print() override {
	if(playerNumber == 1){
		return u8"\u2657";
	}
	else if(playerNumber == 2){
		return u8"\u265D";
	}
	return "";
}
public: bool isValidMove(int player, int rowTarget, int colTarget, std::vector<std::shared_ptr<std::vector<std::shared_ptr<Figure>>>>chessBoard) override{
	if(colTarget > 7 || colTarget < 0 || rowTarget < 0 || rowTarget > 7) {return false;} //if figure would move out of the board
	bool skipsFigure = false;
	if (abs(row - rowTarget) == abs(column - colTarget)) {
		if (row < rowTarget) {
			if (column < colTarget) {
				int j = column + 1;
				for (int i = (row + 1); i < rowTarget; i++) {
					if ((*chessBoard[i])[j]->get_player() != 0) {
						skipsFigure = true;
					}
					j++;
				}
			}
			else {
				int j = column - 1;
				for (int i = (row + 1); i < rowTarget; i++) {
					if ((*chessBoard[i])[j]->get_player() != 0) {
						skipsFigure = true;
					}
					j--;
				}
			}
		}
		else {
			if (column < colTarget) {
				int j = column + 1;
				for (int i = (row - 1); i < rowTarget; i--) {
					if ((*chessBoard[i])[j]->get_player() != 0) {
						skipsFigure = true;
					}
					j++;
				}
			}
			else {
				int j = column - 1;
				for (int i = (row - 1); i < rowTarget; i--) {
					if ((*chessBoard[i])[j]->get_player() != 0) {
						skipsFigure = true;
					}
					j--;
				}
			}
		}

		if (skipsFigure == false) {
			int playerT = (*chessBoard[rowTarget])[colTarget]->get_player();
			char signT = (*chessBoard[rowTarget])[colTarget]->get_Name();
			if (playerT != player && signT != 'K') { return true; }
		}
	}
	return false;
}
};
class JumperFigure :public Figure {
public: void init_figure() { sign = 'S'; };
std::string get_2print() override {
	if(playerNumber == 1){
		return u8"\u2658";
	}
	else if(playerNumber == 2){
		return u8"\u265E";
	}
	return "";
}
public: bool isValidMove(int player, int rowTarget, int colTarget, std::vector<std::shared_ptr<std::vector<std::shared_ptr<Figure>>>>chessBoard) override{
	if(colTarget > 7 || colTarget < 0 || rowTarget < 0 || rowTarget > 7) {return false;} //if figure would move out of the board
	if ((row + 2) == rowTarget || (row - 2) == rowTarget) {
		if ((column + 1) == colTarget || (column - 1) == colTarget) {
			int playerT = (*chessBoard[rowTarget])[colTarget]->get_player();
			char signT = (*chessBoard[rowTarget])[colTarget]->get_Name();
			if (playerT != player && signT != 'K') { return true; }
		}
	}
	else if ((column + 2) == colTarget || (column - 2) == colTarget) {
		if ((row + 1) == rowTarget || (row - 1) == rowTarget) {
			int playerT = (*chessBoard[rowTarget])[colTarget]->get_player();
			char signT = (*chessBoard[rowTarget])[colTarget]->get_Name();
			if (playerT != player && signT != 'K') { return true; }
		}
	}
	return false;
}
};

#endif //_FIGURE_