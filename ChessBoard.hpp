#include <string>
#include <vector>
#include <memory>


#include "ChessFigures.hpp"

#ifndef _CHESSBOARD_
#define _CHESSBOARD_


class ChessBoard{
private: 
    std::vector<std::shared_ptr<std::vector<std::shared_ptr<Figure>>>> chessBoard;


    //initialisizes the chess board
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
    ChessBoard(){
        initBoard();
    }

    std::vector<std::shared_ptr<std::vector<std::shared_ptr<Figure>>>> getBoard(){return chessBoard;}

    void moveFigure(int fromRow, int fromColumn, int toRow, int toColumn){
        //move on chessBoard
		(*chessBoard[toRow])[toColumn] = (*chessBoard[fromRow])[fromColumn];
		(*chessBoard[toRow])[toColumn]->setCoordinates(toRow,toColumn);
		std::shared_ptr<Figure> f = std::make_shared<NoneFigure>();
		f->init_figure();
		f->setCoordinates(fromRow,fromColumn);
		(*chessBoard[fromRow])[fromColumn] = f;
    }

    std::shared_ptr<Figure> getFigure(int row, int column){
        return (*chessBoard[row])[column];
    }

    bool validateMove(int fromRow, int fromColumn, int toRow, int toColumn){
        return getFigure(fromRow,fromColumn)->isValidMove(toRow,toColumn,chessBoard);
    }

    void overrideBoard(std::vector<std::shared_ptr<std::vector<std::shared_ptr<Figure>>>> newBoard){
        chessBoard = newBoard;
    }

    void resetBoard(){
		chessBoard.clear();
        initBoard();
		currentPlayer = 1;
    }




};

#endif //_CHESSBOARD_