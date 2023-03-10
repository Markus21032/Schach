#include <vector>
#include <iostream>
#include <fstream>
#include <memory>
#include <filesystem>
#include "ChessFigures.hpp"

#ifndef _SAVEANDLOADCHESS_
#define _SAVEANDLOADCHESS_

class saveAndLoadChess {

private: bool encript = false;

public:
	/*Saves the game*/
	int save(std::vector<std::shared_ptr<std::vector<std::shared_ptr<Figure>>>> chessBoard, std::string File) {
	    int encriptionArray[] = {186, 169, 94, 229, 56, 188, 191, 179, 59, 56, 188, 188, 236, 135, 50, 11, 56, 212, 127, 39, 3, 159, 147, 67, 139, 119, 206, 168, 31, 108, 84, 71, 37, 34, 247, 220, 59, 4, 62, 28, 51, 155, 152, 62, 81, 189, 7, 184, 62, 186, 207, 96, 40, 123, 50, 250, 5, 5, 245, 221, 39, 9, 102, 193, 93, 9, 105, 215, 55, 190, 43, 29, 251, 13, 185, 21, 188, 254, 229, 190, 142, 5, 105, 244, 79, 132, 26, 183, 206, 76, 125, 188, 196, 241, 199, 175, 52, 70, 122, 117, 222, 171, 226, 111, 216, 255, 152, 190, 254, 17, 157, 163, 106, 55, 23, 216, 16, 31, 194, 159, 176, 98, 98, 132, 198, 79, 31, 152};
		int increment = 0;
		std::ofstream streamOut("StartedGames/"+File);
		//Writes the player, who is next
		streamOut << std::to_string(currentPlayer) << std::endl;
		for (std::shared_ptr<std::vector<std::shared_ptr<Figure>>> vec : chessBoard) {
			for (std::shared_ptr<Figure> x : *vec) {
				if(encript){
					//Writes the symbol of figure and next line the playernumber
					streamOut << x->get_Name() + encriptionArray[increment] << "\n" << std::to_string(x->get_player() + encriptionArray[increment]) << std::endl;
				}
				else{
					//Writes the symbol of figure and next line the playernumber
					streamOut << x->get_Name() << "\n" << std::to_string(x->get_player()) << std::endl;
				}
				increment++;
			}
		}
		streamOut.close();
		std::remove("StartedGames/Chess_Quick_Save");
		return 0;
	}
public:
	int quicksave(std::vector<std::shared_ptr<std::vector<std::shared_ptr<Figure>>>> chessBoard) {
		int encriptionArray[] = {186, 169, 94, 229, 56, 188, 191, 179, 59, 56, 188, 188, 236, 135, 50, 11, 56, 212, 127, 39, 3, 159, 147, 67, 139, 119, 206, 168, 31, 108, 84, 71, 37, 34, 247, 220, 59, 4, 62, 28, 51, 155, 152, 62, 81, 189, 7, 184, 62, 186, 207, 96, 40, 123, 50, 250, 5, 5, 245, 221, 39, 9, 102, 193, 93, 9, 105, 215, 55, 190, 43, 29, 251, 13, 185, 21, 188, 254, 229, 190, 142, 5, 105, 244, 79, 132, 26, 183, 206, 76, 125, 188, 196, 241, 199, 175, 52, 70, 122, 117, 222, 171, 226, 111, 216, 255, 152, 190, 254, 17, 157, 163, 106, 55, 23, 216, 16, 31, 194, 159, 176, 98, 98, 132, 198, 79, 31, 152};
		int increment = 0;
		std::ofstream streamOut("StartedGames/Chess_Quick_Save");
		//Writes the player, who is next
		streamOut << std::to_string(currentPlayer) << std::endl;
		for (std::shared_ptr<std::vector<std::shared_ptr<Figure>>> vec : chessBoard) {
			for (std::shared_ptr<Figure> x : *vec) {
				if(encript){
					//Writes the symbol of figure and next line the playernumber
					streamOut << x->get_Name() + encriptionArray[increment] << "\n" << std::to_string(x->get_player() + encriptionArray[increment]) << std::endl;
				}
				else{
					//Writes the symbol of figure and next line the playernumber
					streamOut << x->get_Name() << "\n" << std::to_string(x->get_player()) << std::endl;
				}
				increment++;
			}
		}
		streamOut.close();
		return 0;
	}
public:
	/*Returns the playernumber, who has to play next*/
	int load(std::vector<std::shared_ptr<std::vector<std::shared_ptr<Figure>>>>& chessBoard, std::string gameToLoad) {
		std::ifstream streamIn;

		try{
			gameToLoad = "StartedGames/" + gameToLoad;
			streamIn.open(gameToLoad);			
			int encriptionArray[] = {186, 169, 94, 229, 56, 188, 191, 179, 59, 56, 188, 188, 236, 135, 50, 11, 56, 212, 127, 39, 3, 159, 147, 67, 139, 119, 206, 168, 31, 108, 84, 71, 37, 34, 247, 220, 59, 4, 62, 28, 51, 155, 152, 62, 81, 189, 7, 184, 62, 186, 207, 96, 40, 123, 50, 250, 5, 5, 245, 221, 39, 9, 102, 193, 93, 9, 105, 215, 55, 190, 43, 29, 251, 13, 185, 21, 188, 254, 229, 190, 142, 5, 105, 244, 79, 132, 26, 183, 206, 76, 125, 188, 196, 241, 199, 175, 52, 70, 122, 117, 222, 171, 226, 111, 216, 255, 152, 190, 254, 17, 157, 163, 106, 55, 23, 216, 16, 31, 194, 159, 176, 98, 98, 132, 198, 79, 31, 152};
			int increment = 0;
			std::string inputAsString;
			std::string currentP;
			std::getline(streamIn, currentP);
			for (int i = 0; i < 8; i++) {
			std::shared_ptr<std::vector<std::shared_ptr<Figure>>> fig = std::make_shared<std::vector<std::shared_ptr<Figure>>>();
				for (int j = 0; j < 8; j++) {
					std::getline(streamIn, inputAsString);
					char input;
					if(encript){					
						char inputAsChar = stoi(inputAsString);
						input = inputAsChar - encriptionArray[increment];		
					}
					else{
						input = inputAsString[0];		
					}			
					if (input == '0') {
						std::string playerInput;
						std::getline(streamIn, playerInput);
						char inputAsChar = stoi(playerInput);			
						std::shared_ptr<Figure> f = std::make_shared<NoneFigure>();
						f->init_figure();
						f->setCoordinates(i,j);
						fig->push_back(f);
					}
					else if (input == 'B') {
						std::string playerInput;
						std::getline(streamIn, playerInput);
						char player;
						if(encript){
							char inputAsChar = stoi(playerInput);
							player = inputAsChar - encriptionArray[increment];		
						}
						else{
							player = stoi(playerInput);	
						}
						std::shared_ptr<Figure> f = std::make_shared<PawnFigure>();
						f->init_figure();
						f->assign_to_player(player);
						f->setCoordinates(i,j);
						fig->push_back(f);
					}
					else if (input == 'T') {
						std::string playerInput;
						std::getline(streamIn, playerInput);
						char player;
						if(encript){
							char inputAsChar = stoi(playerInput);
							player = inputAsChar - encriptionArray[increment];		
						}
						else{
							player = stoi(playerInput);	
						}
						std::shared_ptr<Figure> f = std::make_shared<TowerFigure>();
						f->init_figure();
						f->assign_to_player(player);
						f->setCoordinates(i,j);
						fig->push_back(f);
					}
					else if (input == 'S') {
						std::string playerInput;
						std::getline(streamIn, playerInput);
						char player;
						if(encript){
							char inputAsChar = stoi(playerInput);
							player = inputAsChar - encriptionArray[increment];		
						}
						else{
							player = stoi(playerInput);		
						}
						std::shared_ptr<Figure> f = std::make_shared<JumperFigure>();
						f->init_figure();
						f->assign_to_player(player);
						f->setCoordinates(i,j);
						fig->push_back(f);
					}
					else if (input == 'L') {
						std::string playerInput;
						std::getline(streamIn, playerInput);
						char player;
						if(encript){
							char inputAsChar = stoi(playerInput);
							player = inputAsChar - encriptionArray[increment];		
						}
						else{
							player = stoi(playerInput);	
						}
						std::shared_ptr<Figure> f = std::make_shared<RunnerFigure>();
						f->init_figure();
						f->assign_to_player(player);
						f->setCoordinates(i,j);
						fig->push_back(f);
					}
					else if (input == 'K') {
						std::string playerInput;
						std::getline(streamIn, playerInput);
						char player;
						if(encript){
							char inputAsChar = stoi(playerInput);
							player = inputAsChar - encriptionArray[increment];		
						}
						else{
							player = stoi(playerInput);		
						}
						std::shared_ptr<Figure> f = std::make_shared<KingFigure>();
						f->init_figure();
						f->assign_to_player(player);
						f->setCoordinates(i,j);
						fig->push_back(f);
					}
					else if (input == 'Q') {
						std::string playerInput;
						std::getline(streamIn, playerInput);
						char player;
						if(encript){
							char inputAsChar = stoi(playerInput);
							player = inputAsChar - encriptionArray[increment];		
						}
						else{
							player = stoi(playerInput);		
						}
						std::shared_ptr<Figure> f = std::make_shared<QueenFigure>();
						f->init_figure();
						f->assign_to_player(player);
						f->setCoordinates(i,j);
						fig->push_back(f);
					}
					increment++;
				}
			chessBoard.push_back(fig);
			}
			streamIn.close();

			if(chessBoard.size() == 8){
				for(auto vector : chessBoard){
					if(vector->size() != 8){
						throw std::exception();
					}
				}
			}
			else{
				throw std::exception();
			}

			return std::stoi(currentP);
		}
		catch(...){
			// 3 for Error
			return 3;
		}
	
	}
};

#endif //_SAVEANDLOADCHESS_