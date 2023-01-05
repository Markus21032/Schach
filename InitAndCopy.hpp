#include <vector>
#include <string>
#include <memory>
#include "ChessFigures.hpp"

#ifndef _INITANDCOPY_
#define _INITANDCOPY_ 

//initialisizes the chess board
void initBoard(std::vector<std::shared_ptr<std::vector<std::shared_ptr<Figure> > > >& chessBoard) {
	for (int i = 0; i < 8; i++) {
		std::shared_ptr<std::vector<std::shared_ptr<Figure>>> fig = std::make_shared<std::vector<std::shared_ptr<Figure>>>();
		if (i == 0 || i == 7) {
			int player = 1;
			if (i == 7) { player = 2; }
			std::shared_ptr<TowerFigure> t1 = std::make_shared< TowerFigure>();
			t1->init_figure();
			t1->assign_to_player(player);
			fig->push_back(t1);
			std::shared_ptr<JumperFigure> j1 = std::make_shared< JumperFigure>();
			j1->init_figure();
			j1->assign_to_player(player);
			fig->push_back(j1);
			std::shared_ptr<RunnerFigure> r1 = std::make_shared< RunnerFigure>();
			r1->init_figure();
			r1->assign_to_player(player);
			fig->push_back(r1);
			std::shared_ptr<KingFigure> k = std::make_shared< KingFigure>();
			k->init_figure();
			k->assign_to_player(player);
			fig->push_back(k);
			std::shared_ptr<QueenFigure> q = std::make_shared< QueenFigure>();
			q->init_figure();
			q->assign_to_player(player);
			fig->push_back(q);
			std::shared_ptr<RunnerFigure> r2 = std::make_shared< RunnerFigure>();
			r2->init_figure();
			r2->assign_to_player(player);
			fig->push_back(r2);
			std::shared_ptr<JumperFigure> j2 = std::make_shared< JumperFigure>();
			j2->init_figure();
			j2->assign_to_player(player);
			fig->push_back(j2);
			std::shared_ptr<TowerFigure> t2 = std::make_shared< TowerFigure>();
			t2->init_figure();
			t2->assign_to_player(player);
			fig->push_back(t2);
		}
		else if (i == 1 || i == 6) {
			int player = 1;
			if (i == 6) { player = 2; }
			for (int j = 0; j < 8; j++) {
				std::shared_ptr<PawnFigure> f = std::make_shared< PawnFigure>();
				f->init_figure();
				f->assign_to_player(player);
				fig->push_back(f);
			}
		}
		else {
			for (int j = 0; j < 8; j++) {
				std::shared_ptr<NoneFigure> f = std::make_shared< NoneFigure>();
				f->init_figure();
				fig->push_back(f);
			}
		}
		chessBoard.push_back(fig);
	}
};

//copyes the chessboard
std::vector<std::shared_ptr<std::vector<std::shared_ptr<Figure> > > > copyBoard(std::vector<std::shared_ptr<std::vector<std::shared_ptr<Figure> > > >& chessBoard){
	std::vector<std::shared_ptr<std::vector<std::shared_ptr<Figure> > > > copy;
	for (int i = 0; i < 8; i++) {
		std::shared_ptr<std::vector<std::shared_ptr<Figure>>> vec = std::make_shared<std::vector<std::shared_ptr<Figure>>>();
		for (int j = 0; j < 8; j++) {
			int player = (*chessBoard[i])[j]->get_player();

			if((*chessBoard[i])[j]->get_Name() == '0'){
				std::shared_ptr<NoneFigure> fig = std::make_shared< NoneFigure>();
				fig->init_figure();
				vec->push_back(fig);
			}
			else if((*chessBoard[i])[j]->get_Name() == 'B'){std::shared_ptr<PawnFigure> fig = std::make_shared< PawnFigure>();
				fig->init_figure();
				fig->assign_to_player(player);
				vec->push_back(fig);
			}
			else if((*chessBoard[i])[j]->get_Name() == 'K'){std::shared_ptr<KingFigure> fig = std::make_shared< KingFigure>();
				fig->init_figure();
				fig->assign_to_player(player);
				vec->push_back(fig);
			}
			else if((*chessBoard[i])[j]->get_Name() == 'Q'){std::shared_ptr<QueenFigure> fig = std::make_shared< QueenFigure>();
				fig->init_figure();
				fig->assign_to_player(player);
				vec->push_back(fig);
			}
			else if((*chessBoard[i])[j]->get_Name() == 'T'){std::shared_ptr<TowerFigure> fig = std::make_shared< TowerFigure>();
				fig->init_figure();
				fig->assign_to_player(player);
				vec->push_back(fig);
			}
			else if((*chessBoard[i])[j]->get_Name() == 'L'){std::shared_ptr<RunnerFigure> fig = std::make_shared< RunnerFigure>();
				fig->init_figure();
				fig->assign_to_player(player);
				vec->push_back(fig);
			}
			else if((*chessBoard[i])[j]->get_Name() == 'S'){std::shared_ptr<JumperFigure> fig = std::make_shared< JumperFigure>();
				fig->init_figure();
				fig->assign_to_player(player);
				vec->push_back(fig);
			}
		}
		
		copy.push_back(vec);
	}

	return copy;
};

#endif //_INITANDCOPY_