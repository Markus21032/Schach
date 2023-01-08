#include <vector>
#include <string>
#include <memory>
#include "ChessFigures.hpp"

#ifndef _INITANDCOPY_
#define _INITANDCOPY_ 



//copyes the chessboard
ChessBoard copyBoard(ChessBoard& chessBoard){
	std::vector<std::shared_ptr<std::vector<std::shared_ptr<Figure> > > > copy;
	for (int i = 0; i < 8; i++) {
		std::shared_ptr<std::vector<std::shared_ptr<Figure>>> vec = std::make_shared<std::vector<std::shared_ptr<Figure>>>();
		for (int j = 0; j < 8; j++) {
			int player = chessBoard.getFigure(i,j)->get_player();

			if(chessBoard.getFigure(i,j)->get_Name() == '0'){
				std::shared_ptr<Figure> fig = std::make_shared< NoneFigure>();
				fig->init_figure();
				fig->setCoordinates(i,j);
				vec->push_back(fig);
			}
			else if(chessBoard.getFigure(i,j)->get_Name() == 'B'){std::shared_ptr<Figure> fig = std::make_shared< PawnFigure>();
				fig->init_figure();
				fig->assign_to_player(player);
				fig->setCoordinates(i,j);
				vec->push_back(fig);
			}
			else if(chessBoard.getFigure(i,j)->get_Name() == 'K'){std::shared_ptr<Figure> fig = std::make_shared< KingFigure>();
				fig->init_figure();
				fig->assign_to_player(player);
				fig->setCoordinates(i,j);
				vec->push_back(fig);
			}
			else if(chessBoard.getFigure(i,j)->get_Name() == 'Q'){std::shared_ptr<Figure> fig = std::make_shared< QueenFigure>();
				fig->init_figure();
				fig->assign_to_player(player);
				fig->setCoordinates(i,j);
				vec->push_back(fig);
			}
			else if(chessBoard.getFigure(i,j)->get_Name() == 'T'){std::shared_ptr<Figure> fig = std::make_shared< TowerFigure>();
				fig->init_figure();
				fig->assign_to_player(player);
				fig->setCoordinates(i,j);
				vec->push_back(fig);
			}
			else if(chessBoard.getFigure(i,j)->get_Name() == 'L'){std::shared_ptr<Figure> fig = std::make_shared< RunnerFigure>();
				fig->init_figure();
				fig->assign_to_player(player);
				fig->setCoordinates(i,j);
				vec->push_back(fig);
			}
			else if(chessBoard.getFigure(i,j)->get_Name() == 'S'){std::shared_ptr<Figure> fig = std::make_shared< JumperFigure>();
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
};

#endif //_INITANDCOPY_