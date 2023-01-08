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
bool inCheck(ChessBoard chessBoard,int playerNumber) {
	int kingpos[2];
	for (int row = 0; row < 8; row++) {
		for (int column = 0; column < 8; column++) {
			if (chessBoard.getFigure(row,column)->get_Name() == 'K' && chessBoard.getFigure(row,column)->get_player() == playerNumber) {
				kingpos[0] = row;
				kingpos[1] = column;
				break;
			}
		}
	}


	for (int row = 0; row < 8; row++) {
		for (int column = 0; column < 8; column++) {
			if(chessBoard.getFigure(row,column)->get_player() != playerNumber){
				for(auto move: chessBoard.getListOfValidMoves(row,column)){
					if(move[0]==kingpos[0] && move[1] == kingpos[1]){
						return true;
					}
				}
			}
		}
	}
	return false;			
};


bool isCheckMate(ChessBoard chessBoard, int attackedKing) {
	ChessBoard boardCopy;
	boardCopy = copyBoard(chessBoard);
	bool mate = false;
	int kingposition[2];

	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			if(boardCopy.getFigure(i, j)->get_Name() == 'K' && (boardCopy.getFigure(i, j)->get_player() == attackedKing)){
				kingposition[0] = i; //row
				kingposition[1] = j; //column
				break;
			}
		}
	}
	
	printChess printer;

	//Fall 1: König kann sich selbstständig befreien
	int possibleMovesForKing [8][2] = {{1,-1}, {1,0}, {1,1}, {0,1}, {-1,1}, {-1,0}, {-1,-1}, {0,-1}};

	for(auto pos: possibleMovesForKing){
		if(boardCopy.validateMove(kingposition[0], kingposition[1], kingposition[0]+pos[0], kingposition[1]+pos[1])){
			printer.print(boardCopy);
			std::cout << "[" << kingposition[0] << ", " << kingposition[1] << "] -> [" << kingposition[0]+pos[0] << ", " << kingposition[1]+pos[1] << "]" << std::endl;
			//if move is valid, do it and then check if king is still in check
			auto savedFigure = boardCopy.getFigure(kingposition[0]+pos[0], kingposition[1]+pos[1]);

			boardCopy.moveFigure(kingposition[0], kingposition[1], kingposition[0]+pos[0], kingposition[1]+pos[1]);
			

			for(auto x: boardCopy.getListOfValidMoves(1,4)){
				//std::cout<< x[0] << " " << x[1]<< std::endl;
			}

			if(!inCheck(boardCopy,attackedKing)){ //player is no longer in check
				printer.print(boardCopy);
				return false;
			} else{ //undo move
				boardCopy.moveFigure(kingposition[0]+pos[0], kingposition[1]+pos[1], kingposition[0], kingposition[1]);
				boardCopy.setFigure(kingposition[0]+pos[0], kingposition[1]+pos[1], savedFigure);
			}
		}
	}
	

	//Fall 2: Angreifende Figur kann geschlagen werden
	//Fall 3: Figur kann sich zwischen Angreifer und König stellen


	std::cout <<"true" <<std::endl;
	return true;
};


#endif //_Algorithm_