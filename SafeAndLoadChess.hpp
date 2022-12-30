#include <vector>
#include <iostream>
#include <fstream>

#ifndef _SAFEANDLOADCHESS_
#define _SAFEANDLOADCHESS_

class safeAndLoadChess {
public:
	int safe(std::vector<std::vector<Figure*>*>& chessBoard, int currentP) {
		std::ofstream streamOut("Chess_Safe.txt");
		streamOut << std::to_string(currentP) << std::endl;
		for (std::vector<Figure*>* vec : chessBoard) {
			for (Figure* x : *vec) {
				streamOut << x->get_Name() << "\n" << std::to_string(x->get_player()) << std::endl;
			}
		}
		streamOut.close();
		return 0;
	}
public:
	int load(std::vector<std::vector<Figure*>*>& chessBoard) {
		std::ifstream streamIn;
		streamIn.open("Chess_Safe.txt");
		std::string input;
		std::string currentP;
		std::getline(streamIn, currentP);
		for (int i = 0; i < 8; i++) {
			std::vector<Figure*>* fig = new std::vector<Figure*>;

			for (int j = 0; j < 8; j++) {
				std::getline(streamIn, input);
				if (input == "0") {
					std::string player;
					std::getline(streamIn, player);
					NoneFigure* f = new NoneFigure;
					f->init_figure();
					fig->push_back(f);
				}
				else if (input == "B") {
					std::string player;
					std::getline(streamIn, player);
					PawnFigure* f = new PawnFigure;
					f->init_figure();
					f->assign_to_player(std::stoi(player));
					fig->push_back(f);
				}
				else if (input == "T") {
					std::string player;
					std::getline(streamIn, player);
					TowerFigure* f = new TowerFigure;
					f->init_figure();
					f->assign_to_player(std::stoi(player));
					fig->push_back(f);
				}
				else if (input == "S") {
					std::string player;
					std::getline(streamIn, player);
					JumperFigure* f = new JumperFigure;
					f->init_figure();
					f->assign_to_player(std::stoi(player));
					fig->push_back(f);
				}
				else if (input == "L") {
					std::string player;
					std::getline(streamIn, player);
					RunnerFigure* f = new RunnerFigure;
					f->init_figure();
					f->assign_to_player(std::stoi(player));
					fig->push_back(f);
				}
				else if (input == "K") {
					std::string player;
					std::getline(streamIn, player);
					KingFigure* f = new KingFigure;
					f->init_figure();
					f->assign_to_player(std::stoi(player));
					fig->push_back(f);
				}
				else if (input == "Q") {
					std::string player;
					std::getline(streamIn, player);
					QueenFigure* f = new QueenFigure;
					f->init_figure();
					f->assign_to_player(std::stoi(player));
					fig->push_back(f);
				}
			}
			chessBoard.push_back(fig);
		}
		streamIn.close();
		return std::stoi(currentP);
	}
};

#endif _SAFEANDLOADCHESS_