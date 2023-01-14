#include <string>
#include <vector>
#include <memory>
#include <array>
#include <map>


#include "ChessFigures.hpp"

#ifndef _CHESSBOARD_
#define _CHESSBOARD_


class ChessBoard{
private: 
	//2d vector filled with Figure Objects representing the chess board
    std::vector<std::shared_ptr<std::vector<std::shared_ptr<Figure>>>> chessBoard;

    	/*initialisizes the chess board, is only called by the contructor*/
        void initBoard() {
			chessBoard.clear();
            for (int i = 0; i < 8; i++) {
                std::shared_ptr<std::vector<std::shared_ptr<Figure>>> fig = std::make_shared<std::vector<std::shared_ptr<Figure>>>();
                if (i == 0 || i == 7) {
                    int player = 1;
                    if (i == 7) { player = 2; }
                    std::shared_ptr<Figure> t1 = std::make_shared< TowerFigure>();
                    t1->init_figure();
                    t1->assign_to_player(player);
                    t1->setCoordinates(i,0);
                    fig->push_back(t1);
                    std::shared_ptr<Figure> j1 = std::make_shared< JumperFigure>();
                    j1->init_figure();
                    j1->assign_to_player(player);
                    j1->setCoordinates(i,1);
                    fig->push_back(j1);
                    std::shared_ptr<Figure> r1 = std::make_shared< RunnerFigure>();
                    r1->init_figure();
                    r1->assign_to_player(player);
                    r1->setCoordinates(i,2);
                    fig->push_back(r1);
                    std::shared_ptr<Figure> k = std::make_shared< KingFigure>();
                    k->init_figure();
                    k->assign_to_player(player);
                    k->setCoordinates(i,3);
                    fig->push_back(k);
                    std::shared_ptr<Figure> q = std::make_shared< QueenFigure>();
                    q->init_figure();
                    q->assign_to_player(player);
                    q->setCoordinates(i,4);
                    fig->push_back(q);
                    std::shared_ptr<Figure> r2 = std::make_shared< RunnerFigure>();
                    r2->init_figure();
                    r2->assign_to_player(player);
                    r2->setCoordinates(i,5);
                    fig->push_back(r2);
                    std::shared_ptr<Figure> j2 = std::make_shared< JumperFigure>();
                    j2->init_figure();
                    j2->assign_to_player(player);
                    j2->setCoordinates(i,6);
                    fig->push_back(j2);
                    std::shared_ptr<Figure> t2 = std::make_shared< TowerFigure>();
                    t2->init_figure();
                    t2->assign_to_player(player);
                    t2->setCoordinates(i,7);
                    fig->push_back(t2);
                }
                else if (i == 1 || i == 6) {
                    int player = 1;
                    if (i == 6) { player = 2; }
                    for (int j = 0; j < 8; j++) {
                        std::shared_ptr<Figure> f = std::make_shared< PawnFigure>();
                        f->init_figure();
                        f->assign_to_player(player);
                        f->setCoordinates(i,j);
                        fig->push_back(f);
                    }
                }
                else {
                    for (int j = 0; j < 8; j++) {
                        std::shared_ptr<Figure> f = std::make_shared< NoneFigure>();
                        f->init_figure();
                        f->setCoordinates(i,j);
                        fig->push_back(f);
                    }
                }
                chessBoard.push_back(fig);
            }
        }

        
public:
	/*constructor*/
    ChessBoard(){
        initBoard();
    }

	/*returns the 2d vector representing the chess board*/
    std::vector<std::shared_ptr<std::vector<std::shared_ptr<Figure>>>> getBoard(){return chessBoard;}

	/*returns a fully coppied 2d vector of the chess board*/
    ChessBoard copyBoard(){
	std::vector<std::shared_ptr<std::vector<std::shared_ptr<Figure>>>> copy;
	for (int i = 0; i < 8; i++) {
		std::shared_ptr<std::vector<std::shared_ptr<Figure>>> vec = std::make_shared<std::vector<std::shared_ptr<Figure>>>();
		for (int j = 0; j < 8; j++) {
			int player = getFigure(i,j)->get_player();

			if(getFigure(i,j)->get_Name() == '0'){
				std::shared_ptr<Figure> fig = std::make_shared< NoneFigure>();
				fig->init_figure();
				fig->setCoordinates(i,j);
				vec->push_back(fig);
			}
			else if(getFigure(i,j)->get_Name() == 'B'){std::shared_ptr<Figure> fig = std::make_shared< PawnFigure>();
				fig->init_figure();
				fig->assign_to_player(player);
				fig->setCoordinates(i,j);
				vec->push_back(fig);
			}
			else if(getFigure(i,j)->get_Name() == 'K'){std::shared_ptr<Figure> fig = std::make_shared< KingFigure>();
				fig->init_figure();
				fig->assign_to_player(player);
				fig->setCoordinates(i,j);
				vec->push_back(fig);
			}
			else if(getFigure(i,j)->get_Name() == 'Q'){std::shared_ptr<Figure> fig = std::make_shared< QueenFigure>();
				fig->init_figure();
				fig->assign_to_player(player);
				fig->setCoordinates(i,j);
				vec->push_back(fig);
			}
			else if(getFigure(i,j)->get_Name() == 'T'){std::shared_ptr<Figure> fig = std::make_shared< TowerFigure>();
				fig->init_figure();
				fig->assign_to_player(player);
				fig->setCoordinates(i,j);
				vec->push_back(fig);
			}
			else if(getFigure(i,j)->get_Name() == 'L'){std::shared_ptr<Figure> fig = std::make_shared< RunnerFigure>();
				fig->init_figure();
				fig->assign_to_player(player);
				fig->setCoordinates(i,j);
				vec->push_back(fig);
			}
			else if(getFigure(i,j)->get_Name() == 'S'){std::shared_ptr<Figure> fig = std::make_shared< JumperFigure>();
				fig->init_figure();
				fig->assign_to_player(player);
				fig->setCoordinates(i,j);
				vec->push_back(fig);
			}
		}
		
		copy.push_back(vec);
	}

	ChessBoard copyBoard;
	copyBoard.overrideBoard(copy);
	return copyBoard;
}

	/*move a figure on a given position to a new position and replaced the old position with a NoneFigure Object, 
	check if the move is legal has to be done seperately */
    void moveFigure(int fromRow, int fromColumn, int toRow, int toColumn){
        //move on chessBoard
		(*chessBoard[toRow])[toColumn] = (*chessBoard[fromRow])[fromColumn];
		(*chessBoard[toRow])[toColumn]->setCoordinates(toRow,toColumn);
		std::shared_ptr<Figure> f = std::make_shared<NoneFigure>();
		f->init_figure();
		f->setCoordinates(fromRow,fromColumn);
		(*chessBoard[fromRow])[fromColumn] = f;
    }

	/*sets a given figure object to a given position*/
    void setFigure(int row, int column, std::shared_ptr<Figure> figure){
        (*chessBoard[row])[column] = figure;
    }

	/*returns the Figure Object on a given position*/
    std::shared_ptr<Figure> getFigure(int row, int column){
        return (*chessBoard[row])[column];
    }

	/*checks whether a move of a Figure is valid*/
    bool validateMove(int fromRow, int fromColumn, int toRow, int toColumn){
        return getFigure(fromRow,fromColumn)->isValidMove(toRow,toColumn,chessBoard);
    }

	/*overrides the current chess board 2d vector with a given one*/
    void overrideBoard(std::vector<std::shared_ptr<std::vector<std::shared_ptr<Figure>>>> newBoard){
        chessBoard = newBoard;
    }

	/*resets the board to default*/
    void resetBoard(){
		chessBoard.clear();
        initBoard();
		currentPlayer = 1;
    }

    /*Returns a list of all valid moves for a figure on a given position*/
    std::vector<std::array<int,2>> getListOfValidMoves(int row, int column){
        std::vector<std::array<int,2>> movesList;
        for(int r = 0; r < 8; r++){
            for(int c = 0; c < 8; c++){
                if(validateMove(row,column,r,c)){
                    std::array<int, 2> x = {r, c};
                    movesList.push_back(x);
                }
            }
        }
        return movesList;
    }

	/*checks if the king of the given player is in check*/
    bool inCheck(int playerNumber) {
	int kingpos[2];
	for (int row = 0; row < 8; row++) {
		for (int column = 0; column < 8; column++) {
			if (getFigure(row,column)->get_Name() == 'K' && getFigure(row,column)->get_player() == playerNumber) {
				kingpos[0] = row;
				kingpos[1] = column;
				break;
			}
		}
	}

	for (int row = 0; row < 8; row++) {
		for (int column = 0; column < 8; column++) {
			if(getFigure(row,column)->get_player() != playerNumber){
				for(auto move: getListOfValidMoves(row,column)){
					if(move[0]==kingpos[0] && move[1] == kingpos[1]){
						return true;
					}
				}
			}
		}
	}
	return false;			
}

/*checks if the chess board is in a stalemate position, this occurs if one player can't execute a legal move*/
bool isStalemate(){
    //1. Get all possible moves
    //2. Make all possible moves on a copied board and check if they are legal (inCheck())
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
			//check for player1
            if(getFigure(i, j)->get_player() == 1){
                for(auto move: getListOfValidMoves(i, j)){
                    ChessBoard boardCopy = copyBoard();
                    boardCopy.moveFigure(i, j, move[0], move[1]);
					//if any single position the player could take doesn't lead to the player being in check, he has at least one legal move left
					//and therefore is not in a stalemate position
                    if(!boardCopy.inCheck(1)){ 
                        return false;
                    }
                }
            }
			else if (getFigure(i, j)->get_player() == 2){
				for(auto move: getListOfValidMoves(i, j)){
                    ChessBoard boardCopy = copyBoard();
                    boardCopy.moveFigure(i, j, move[0], move[1]);
					//if any single position the player could take doesn't lead to the player being in check, he has at least one legal move left
					//and therefore is not in a stalemate position
                    if(!boardCopy.inCheck(2)){ 
                        return false;
                    }
                }
			}
        }
	}
    return true;
}

/*
Checks if a game is tied because there are not enough figures
*/

bool insufficientMaterial(){
	std::map<char, int> player1;
	std::map<char, int> player2;

	//fill the 2 maps with the amout of figures on the board for each player
	//format: <name of figure {B, K, L, Q, S, T}> : <amout of that bigure on board>
	for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
			if(getFigure(i, j)->get_player() == 1){
				if(player1.find(getFigure(i, j)->get_Name()) == player1.end()){
					player1.insert({getFigure(i, j)->get_Name(), 1});
				} else {
					player1[getFigure(i, j)->get_Name()] = player1[getFigure(i, j)->get_Name()]+1;
				}

				}
			else if(getFigure(i, j)->get_player() == 2){
				if(player2.find(getFigure(i, j)->get_Name()) == player2.end()){
					player2.insert({getFigure(i, j)->get_Name(), 1});
				} else {
					player2[getFigure(i, j)->get_Name()] = player2[getFigure(i, j)->get_Name()]+1;
				}
			}
		}
	}
	

	//King vs. King
	if( (player1.size() == 1 && player1.find('K') != player1.end() &&  player1['K'] == 1) && 	//player2 only has King
		(player2.size() == 1 && player2.find('K') != player2.end() &&  player2['K'] == 1)){	//player1 only has King
		return true;
	}
	//King & Bishop vs. King 
	else if ((player1.size() == 2 && player1.find('K') != player1.end() &&  player1['K'] == 1 && player1.find('L') != player1.end() &&  player1['L'] == 1) && 	//player1 only has king & bishop
			(player2.size() == 1 && player2.find('K') != player2.end() &&  player2['K'] == 1)){								//player2 only has king
		return true;
	}
	//King vs. Bishop & King
	else if ((player2.size() == 2 && player2.find('K') != player2.end() &&  player2['K'] == 1 && player2.find('L') != player2.end() &&  player2['L'] == 1) && 	//player2 only has king & bishop
			(player1.size() == 1 && player1.find('K') != player1.end() &&  player1['K'] == 1)){							//player1 only has king
		return true;
	}
	//King & Knight vs. King
	else if ((player1.size() == 2 && player1.find('K') != player1.end() &&  player1['K'] == 1 && player1.find('S') != player1.end() && player1['S'] == 1) && 	//player1 only has king & knight
			(player2.size() == 1 && player2.find('K') != player2.end() &&  player2['K'] == 1)){								//player2 only has king
		return true;
	}
	//King vs. Knight & King
	else if ((player2.size() == 2 && player2.find('K') != player2.end() && player2['K'] == 1 && player2.find('S') != player2.end() && player2['S'] == 1) && 	//player2 only has king & knight
			(player1.size() == 1 && player1.find('K') != player1.end() && player1['K'] == 1)){								//player1 only has king
		return true;
	}
	//Bishop & King vs. Bishop & King (when both bishops are on the same field color)
	else if ((player1.size() == 2 && player1.find('K') != player1.end() && player1['K'] == 1 && player1.find('L') != player1.end() && player1['L'] == 1) && 
			(player2.size() == 2 && player2.find('K') != player2.end() && player2['K'] == 1 && player2.find('L') != player2.end() && player2['L'] == 1)){

		int digitSumP1 = -1;
		int digitSumP2 = -1;

		for (int i = 0; i < 8; i++) {
        	for (int j = 0; j < 8; j++) {
				if(getFigure(i, j)->get_player() == 1 && getFigure(i,j)->get_Name() == 'L'){
					digitSumP1 = i + j;
				}
				else if (getFigure(i, j)->get_player() == 2 && getFigure(i,j)->get_Name() == 'L')
				{
					digitSumP2 = i + j;
				}

				if(digitSumP1 != -1 && digitSumP2 != -1){
					return ((digitSumP1 % 2) == (digitSumP2 % 2));
				}
			}
		}
	}
	return false;
}

/*checks whether a given player is in checkmate position and therefore lost the game*/

bool isCheckMate(int attackedKing) {
	ChessBoard boardCopy;
	boardCopy = copyBoard();
	bool mate = false;
	int kingposition[2];

	//determine kings position
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			if(boardCopy.getFigure(i, j)->get_Name() == 'K' && (boardCopy.getFigure(i, j)->get_player() == attackedKing)){
				kingposition[0] = i; //row
				kingposition[1] = j; //column
				break;
			}
		}
	}
	

	//Case 1: King can ecape the checkmate himself by simply moving to another position
	for(auto move: getListOfValidMoves(kingposition[0], kingposition[1])){
        //if move is valid, do it and then check if king is still in check
        auto savedFigure = boardCopy.getFigure(move[0], move[1]);

        boardCopy.moveFigure(kingposition[0], kingposition[1], move[0], move[1]);
        
        if(!boardCopy.inCheck(attackedKing)){ //player is no longer in check
            return false;
        } else{ //undo move
            boardCopy.moveFigure(move[0], move[1], kingposition[0], kingposition[1]);
            boardCopy.setFigure(move[0], move[1], savedFigure);
        }
    }

	//Case 2: attacking figure of the opponent can be kicked by another figure of the given player

	//search figures, attacking the King
	std::vector<std::array<int,2>> attackers;
	for(int row=0;row <8 ; row++){
		for(int column=0; column <8 ; column++){
			if(boardCopy.getFigure(row,column)->get_player() != attackedKing){
				for(auto move: boardCopy.getListOfValidMoves(row,column)){
					if(kingposition[0] == move[0] && kingposition[1] == move[1]){
						attackers.push_back({row,column});
					}
				}
			}
		}
	}

	
	if(attackers.size() == 1){
		//Search for a Figure that can kick the attacker
		for(int row=0;row <8 ; row++){
			for(int column=0; column <8 ; column++){
				if(boardCopy.getFigure(row,column)->get_player() == attackedKing){
					for(auto move: boardCopy.getListOfValidMoves(row,column)){						
						if(attackers[0][0] == move[0] && attackers[0][1] == move[1]){
							return false;							
						}
					}
				}
			}
		}
	}
	//if there is more than one opposing figure attacking the king they can't all be defended and the loss is inevitable
	else{
		return true;
	}

	//Case 3: A Figure can "sacrifice" itself by moving between it's king and the attacking figure
	//note: our check for case 3 theoretically includes the check for case 2
	
	auto attacker = attackers[0];
	if(boardCopy.getFigure(attacker[0],attacker[1])->get_Name() == 'S'){
		return true;
	}
	else{
		for(int row=0;row <8 ; row++){
			for(int column=0; column <8 ; column++){
				if(boardCopy.getFigure(row,column)->get_player() == attackedKing){
					for(auto move: boardCopy.getListOfValidMoves(row,column)){
					
					auto savedFigure = boardCopy.getFigure(move[0],move[1]);

					boardCopy.moveFigure(row, column, move[0],move[1]);

					if(boardCopy.inCheck(attackedKing)){
						boardCopy.moveFigure(move[0],move[1], row, column);
						boardCopy.setFigure(move[0],move[1], savedFigure);
					}
					else{
						return false;
						}
					}
				}
			}
		}
	}
	
	return true;
}
};

#endif //_CHESSBOARD_