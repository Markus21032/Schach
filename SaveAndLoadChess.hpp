#include <vector>
#include <iostream>
#include <fstream>
#include <memory>
#include <filesystem>
#include "ChessFigures.hpp"

#ifndef _SAVEANDLOADCHESS_
#define _SAVEANDLOADCHESS_

class saveAndLoadChess {
public:
	int save(std::vector<std::shared_ptr<std::vector<std::shared_ptr<Figure>>>>& chessBoard, int currentP,std::string File) {
		std::ofstream streamOut("StartedGames/"+File);
		streamOut << std::to_string(currentP) << std::endl;
		for (std::shared_ptr<std::vector<std::shared_ptr<Figure>>> vec : chessBoard) {
			for (std::shared_ptr<Figure> x : *vec) {
				streamOut << x->get_Name() << "\n" << std::to_string(x->get_player()) << std::endl;
			}
		}
		streamOut.close();
		std::remove("StartedGames/Chess_Quick_Save");
		return 0;
	}
public:
	int quicksave(std::vector<std::shared_ptr<std::vector<std::shared_ptr<Figure>>>>& chessBoard, int currentP) {
		std::ofstream streamOut("StartedGames/Chess_Quick_Save");
		streamOut << std::to_string(currentP) << std::endl;
		for (std::shared_ptr<std::vector<std::shared_ptr<Figure>>> vec : chessBoard) {
			for (std::shared_ptr<Figure> x : *vec) {
				streamOut << x->get_Name() << "\n" << std::to_string(x->get_player()) << std::endl;
			}
		}
		streamOut.close();
		return 0;
	}
public:
	int load(std::vector<std::shared_ptr<std::vector<std::shared_ptr<Figure>>>>& chessBoard, std::string gameToLoad) {
		std::ifstream streamIn;

		try{
			gameToLoad = "StartedGames/" + gameToLoad;
			streamIn.open(gameToLoad);			
		
			std::string input;
			std::string currentP;
			std::getline(streamIn, currentP);
			for (int i = 0; i < 8; i++) {
			std::shared_ptr<std::vector<std::shared_ptr<Figure>>> fig = std::make_shared<std::vector<std::shared_ptr<Figure>>>();

			for (int j = 0; j < 8; j++) {
				std::getline(streamIn, input);
				if (input == "0") {
					std::string player;
					std::getline(streamIn, player);
					std::shared_ptr<Figure> f = std::make_shared<NoneFigure>();
					f->init_figure();
					fig->push_back(f);
				}
				else if (input == "B") {
					std::string player;
					std::getline(streamIn, player);
					std::shared_ptr<Figure> f = std::make_shared<PawnFigure>();
					f->init_figure();
					f->assign_to_player(std::stoi(player));
					fig->push_back(f);
				}
				else if (input == "T") {
					std::string player;
					std::getline(streamIn, player);
					std::shared_ptr<Figure> f = std::make_shared<TowerFigure>();
					f->init_figure();
					f->assign_to_player(std::stoi(player));
					fig->push_back(f);
				}
				else if (input == "S") {
					std::string player;
					std::getline(streamIn, player);
					std::shared_ptr<Figure> f = std::make_shared<JumperFigure>();
					f->init_figure();
					f->assign_to_player(std::stoi(player));
					fig->push_back(f);
				}
				else if (input == "L") {
					std::string player;
					std::getline(streamIn, player);
					std::shared_ptr<Figure> f = std::make_shared<RunnerFigure>();
					f->init_figure();
					f->assign_to_player(std::stoi(player));
					fig->push_back(f);
				}
				else if (input == "K") {
					std::string player;
					std::getline(streamIn, player);
					std::shared_ptr<Figure> f = std::make_shared<KingFigure>();
					f->init_figure();
					f->assign_to_player(std::stoi(player));
					fig->push_back(f);
				}
				else if (input == "Q") {
					std::string player;
					std::getline(streamIn, player);
					std::shared_ptr<Figure> f = std::make_shared<QueenFigure>();
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
		catch(...){
			std::cout << "File not found or bad file" << std::endl;
			// 3 for Error
			return 3;
		}
	}
};

#endif //_SAVEANDLOADCHESS_