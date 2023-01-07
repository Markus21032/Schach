#include <vector>
#include <string>
#include <memory>
#include "ChessFigures.hpp"
#include "InitAndCopy.hpp"

#ifndef _Algorithm_
#define _Algorithm_ 


//returns the attacked player
//0 -> none
//1 -> player 1
//2 -> player 2
//3 -> both players (illegal move)
int isKingAttacked(std::vector<std::shared_ptr<std::vector<std::shared_ptr<Figure> > > >& chessBoard) {
	bool isAttacked = false;
	int attackedPlayer = 0;
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			if ((*chessBoard[i])[j]->get_Name() == 'K') {
				int playerOfKing = (*chessBoard[i])[j]->get_player();
				//check schraeg
				int c1 = j+1;
				int c2 = j-1;
				for (int l = i+1; l < 8; l++) {// i->7
					if (c1 < 8 && c1 >= 0) {
						if ((*chessBoard[l])[c1]->get_player() != 0 && (*chessBoard[l])[c1]->get_player() == playerOfKing) {
							c1 = 8;
						}
						else if ((*chessBoard[l])[c1]->get_player() != 0 && (*chessBoard[l])[c1]->get_player() != playerOfKing) {
							if ((*chessBoard[l])[c1]->get_Name() == 'L' || (*chessBoard[l])[c1]->get_Name() == 'Q') {
								isAttacked = true;
								break;
							}
						}
					}
					if (c2 < 8 && c2 >= 0) {
						if ((*chessBoard[l])[c2]->get_player() != 0 && (*chessBoard[l])[c2]->get_player() == playerOfKing) {
							c2 = -1;
						}
						else if ((*chessBoard[l])[c2]->get_player() != 0 && (*chessBoard[l])[c2]->get_player() != playerOfKing) {
							if ((*chessBoard[l])[c2]->get_Name() == 'L' || (*chessBoard[l])[c2]->get_Name() == 'Q') {
								isAttacked = true;
								break;
							}
						}
					}
					c1++;
					c2--;
				}
				int c3 = j+1;
				int c4 = j-1;
				for (int l = i-1; l >= 0; l--) {// i->0
					if (c3 < 8 && c3 >= 0) {
						if ((*chessBoard[l])[c3]->get_player() != 0 && (*chessBoard[l])[c3]->get_player() == playerOfKing) {
							c3 = 8;
						}
						else if ((*chessBoard[l])[c3]->get_player() != 0 && (*chessBoard[l])[c3]->get_player() != playerOfKing) {
							if ((*chessBoard[l])[c3]->get_Name() == 'L' || (*chessBoard[l])[c3]->get_Name() == 'Q') {
								isAttacked = true;
								break;
							}
						}
					}
					if (c4 < 8 && c4 >= 0) {
						if ((*chessBoard[l])[c4]->get_player() != 0 && (*chessBoard[l])[c4]->get_player() == playerOfKing) {
							c4 = -1;
						}
						else if ((*chessBoard[l])[c4]->get_player() != 0 && (*chessBoard[l])[c4]->get_player() != playerOfKing) {
							if ((*chessBoard[l])[c4]->get_Name() == 'L' || (*chessBoard[l])[c4]->get_Name() == 'Q') {
								isAttacked = true;
								break;
							}
						}
					}
					c3++;
					c4--;
				}
				// check gerade
				for(int lup = i-1; lup >=0;lup--){
					if ((*chessBoard[lup])[j]->get_player() != 0 && (*chessBoard[lup])[j]->get_player() == playerOfKing) {
						lup = -1;
					}
					else if ((*chessBoard[lup])[j]->get_player() != 0 && (*chessBoard[lup])[j]->get_player() != playerOfKing) {
						if ((*chessBoard[lup])[j]->get_Name() == 'T' || (*chessBoard[lup])[j]->get_Name() == 'Q') {
							isAttacked = true;
							break;
						}
					}
				}
				for(int ldown = i+1; ldown <8; ldown++){
					if ((*chessBoard[ldown])[j]->get_player() != 0 && (*chessBoard[ldown])[j]->get_player() == playerOfKing) {
						ldown = 8;
					}
					else if ((*chessBoard[ldown])[j]->get_player() != 0 && (*chessBoard[ldown])[j]->get_player() != playerOfKing) {
						if ((*chessBoard[ldown])[j]->get_Name() == 'T' || (*chessBoard[ldown])[j]->get_Name() == 'Q') {
							isAttacked = true;
							break;
						}
					}
				}
				for(int cleft = j-1; cleft >=0;cleft--){
					if ((*chessBoard[i])[cleft]->get_player() != 0 && (*chessBoard[i])[cleft]->get_player() == playerOfKing) {
						cleft = -1;
					}
					else if ((*chessBoard[i])[cleft]->get_player() != 0 && (*chessBoard[i])[cleft]->get_player() != playerOfKing) {
						if ((*chessBoard[i])[cleft]->get_Name() == 'T' || (*chessBoard[i])[cleft]->get_Name() == 'Q') {
							isAttacked = true;
							break;
						}
					}
				}
				for(int cright = j+1; cright <8;cright++){
					if ((*chessBoard[i])[cright]->get_player() != 0 && (*chessBoard[i])[cright]->get_player() == playerOfKing) {
						cright = 8;
					}
					else if ((*chessBoard[i])[cright]->get_player() != 0 && (*chessBoard[i])[cright]->get_player() != playerOfKing) {
						if ((*chessBoard[i])[cright]->get_Name() == 'T' || (*chessBoard[i])[cright]->get_Name() == 'Q') {
							isAttacked = true;
							break;
						}
					}
				}
				// check springer
				if((i+1)<8 && (j+2)<8){
					if ((*chessBoard[i+1])[j+2]->get_Name() == 'S' && (*chessBoard[i+1])[j+2]->get_player() != playerOfKing) {
								isAttacked = true;
					}
				}
				if((i+1)<8 && (j-2)>=0){
					if ((*chessBoard[i+1])[j-2]->get_Name() == 'S' && (*chessBoard[i+1])[j-2]->get_player() != playerOfKing) {
								isAttacked = true;
					}
				}
				if((i-1)>=0 && (j+2)<8){
					if ((*chessBoard[i-1])[j+2]->get_Name() == 'S' && (*chessBoard[i-1])[j+2]->get_player() != playerOfKing) {
								isAttacked = true;
					}
				}
				if((i-1)>=0 && (j-2)>=0){
					if ((*chessBoard[i-1])[j-2]->get_Name() == 'S' && (*chessBoard[i-1])[j-2]->get_player() != playerOfKing) {
								isAttacked = true;
					}
				}

				if((i+2)<8 && (j+1)<8){
					if ((*chessBoard[i+2])[j+1]->get_Name() == 'S' && (*chessBoard[i+2])[j+1]->get_player() != playerOfKing) {
								isAttacked = true;
					}
				}
				if((i+2)<8 && (j-1)>=0){
					if ((*chessBoard[i+2])[j-1]->get_Name() == 'S' && (*chessBoard[i+2])[j-1]->get_player() != playerOfKing) {
								isAttacked = true;
					}
				}
				if((i-2)>=0 && (j+1)<8){
					if ((*chessBoard[i-2])[j+1]->get_Name() == 'S' && (*chessBoard[i-2])[j+1]->get_player() != playerOfKing) {
							isAttacked = true;
					}
				}
				if((i-2)>=0 && (j-1)>=0){
					if ((*chessBoard[i-2])[j-1]->get_Name() == 'S' && (*chessBoard[i-2])[j-1]->get_player() != playerOfKing) {
							isAttacked = true;
					}
				}

				//check Bauer
				if(playerOfKing==1){
					if((i+1)<8 && (j-1)>=0){
						if ((*chessBoard[i+1])[j-1]->get_Name() == 'B' && (*chessBoard[i+1])[j-1]->get_player() != playerOfKing) {
							isAttacked = true;
						}
					}
					if((i+1)<8 && (j+1)<8){
						if ((*chessBoard[i+1])[j+1]->get_Name() == 'B' && (*chessBoard[i+1])[j+1]->get_player() != playerOfKing) {
							isAttacked = true;
						}
					}
				}
				else{
					if((i-1)>=0 && (j-1)>=0){
						if ((*chessBoard[i-1])[j-1]->get_Name() == 'B' && (*chessBoard[i-1])[j-1]->get_player() != playerOfKing) {
							isAttacked = true;
						}
					}
					if((i-1)>=0 && (j+1)<8){
						if ((*chessBoard[i-1])[j+1]->get_Name() == 'B' && (*chessBoard[i-1])[j+1]->get_player() != playerOfKing) {
							isAttacked = true;
						}
					}
				}
				
				
				if (isAttacked) { attackedPlayer = attackedPlayer + playerOfKing; }
			}
		}
	}
	return attackedPlayer;
};


bool isMate(std::vector<std::shared_ptr<std::vector<std::shared_ptr<Figure> > > >& chessBoard, int attackedKing) {
	std::vector<std::shared_ptr<std::vector<std::shared_ptr<Figure> > > > board = copyBoard(chessBoard);
	bool mate = false;
	int kingposition[2];

	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			if((*board[i])[j]->get_Name() == 'K' && (*board[i])[j]->get_player() == attackedKing){
				kingposition[0] = i; //row
				kingposition[1] = j; //column
			}
		}
	}

	//Fall 1: König kann sich selbstständig befreien
	if((((*(*board[kingposition[0]])[kingposition[1]])).isValidMove(currentPlayer, kingposition[0]+1, kingposition[1], board))){ //Check if King is movable to postion

		//Move Figure
		(*chessBoard[kingposition[0]])[kingposition[1]] = (*chessBoard[kingposition[0]+1])[kingposition[1]];
		std::shared_ptr<Figure> f = std::make_shared<NoneFigure>();
		f->init_figure();
		(*chessBoard[kingposition[0]])[kingposition[1]] = f;

		if(isKingAttacked(board) != attackedKing){ // Check if King is not attacked anymore after move
			return false;
		}
	}
	if((((*(*board[kingposition[0]])[kingposition[1]])).isValidMove(currentPlayer, kingposition[0]+1, kingposition[1], board)))


	//Fall 2: Angreifende Figur kann geschlagen werden
	//Fall 3: Figur kann sich zwischen Angreifer und König stellen


	
	return mate;
};


#endif //_Algorithm_