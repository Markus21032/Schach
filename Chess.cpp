#include <iostream>
#include <vector>
#include <csignal>
#include <string>
#include <memory>
#include <algorithm>
#include "ChessFigures.hpp"
#include "PrintChess.hpp"
#include "SaveAndLoadChess.hpp"
#include "Algorithm.hpp"


std::string defaultSaveFileName = "Chess_Save";
std::string saveFileName = "d";
int currentPlayer = 1;
 
void exit_handler(){
	std::string quicksave = "StartedGames/Chess_Quick_Save";
	std::ifstream infile(quicksave);
    try{
		if(infile.good()){//if quicksafe exists
			infile.close();
			if(saveFileName == "d"){
				std::string save ="StartedGames/"+defaultSaveFileName;

				std::remove(save.c_str());
				std::rename(quicksave.c_str(), save.c_str());
			}
			else{
				std::string save ="StartedGames/"+saveFileName;
				
				std::remove(save.c_str());
				std::rename(quicksave.c_str(), save.c_str());
			}
		}
	}
	catch(...){
		infile.close();
	}
}



int main()
{
	std::atexit(exit_handler);

	std::vector<std::shared_ptr<std::vector<std::shared_ptr<Figure>>>> chessBoard;
	initBoard(chessBoard);
	printChess printer;
	saveAndLoadChess saveAndLoad;
	printer.print(chessBoard);
	bool play = true;
	while (play) {
		std::string choice;
		std::cout << "Player " << currentPlayer << " Type:\n";
		std::cout << "1 to move a figure\n"
			<< "2 to print the chessboard\n"
			<< "S to save the game\n"
			<< "L to load game\n"
			<< "R to reset game\n"
			<< "E to end\n";
		std::cin >> choice;
		std::cout << "\n";
		if (choice == "1") {
			while (true) {
				//Select figure
				std::string figureSelected;
				std::string columnChar;
				std::cout << "To choose the figure please enter the position of it:\n";
				std::cin >> figureSelected;
				columnChar = figureSelected.substr(0, 1);
				int columnSelect;
				if (columnChar == "A") { columnSelect = 0; }
				else if (columnChar == "B") { columnSelect = 1; }
				else if (columnChar == "C") { columnSelect = 2; }
				else if (columnChar == "D") { columnSelect = 3; }
				else if (columnChar == "E") { columnSelect = 4; }
				else if (columnChar == "F") { columnSelect = 5; }
				else if (columnChar == "G") { columnSelect = 6; }
				else if (columnChar == "H") { columnSelect = 7; }
				else {
					std::cout << "Wrong column input!\n";
					break;
				}
				//std::cout << "To choose the figure please enter line number:\n";
				//std::cin >> lSelect;
				int lineSelect;
				try{
					lineSelect = 8 - std::stoi(figureSelected.substr(1, 1));
				}catch(std::invalid_argument){
					std::cout << "You entered an invalid input for the line number!\n";
				}				
				
				if (lineSelect < 0 || lineSelect >7) {
					std::cout << "Wrong input!\n";
					break;
				}

				if (!((*(*chessBoard[lineSelect])[columnSelect]).get_player() == currentPlayer)) {
					std::cout << "You can only select figures of player " << currentPlayer << "\n";
					break;
				}
				//Select target position
				std::string targetPosition;				
				
				std::cout << "Please enter a target position:\n";
				std::cin >> targetPosition;
				std::string colTarget = targetPosition.substr(0,1);
				std::string lTarget = targetPosition.substr(1,1);
				int columnTarget;
				if (colTarget == "A") { columnTarget = 0; }
				else if (colTarget == "B") { columnTarget = 1; }
				else if (colTarget == "C") { columnTarget = 2; }
				else if (colTarget == "D") { columnTarget = 3; }
				else if (colTarget == "E") { columnTarget = 4; }
				else if (colTarget == "F") { columnTarget = 5; }
				else if (colTarget == "G") { columnTarget = 6; }
				else if (colTarget == "H") { columnTarget = 7; }
				else {
					std::cout << "Wrong column input!\n";
					break;
				}
				//std::cout << "To choose the target position enter line number:\n";
				//std::cin >> lTarget;
				int lineTarget;
				try{
					lineTarget = 8 - std::stoi(lTarget);
				}catch(std::invalid_argument){
					std::cout << "You entered an invalid input for the line number!" << std::endl;
				}
				if (lineTarget < 0 || lineTarget >7) {
					std::cout << "Wrong input!\n";
					break;
				}
				//Check if figure can move to target position
				if (!(((*(*chessBoard[lineSelect])[columnSelect])).moveFigure(currentPlayer, columnSelect, lineSelect, columnTarget, lineTarget, chessBoard))) {
					std::cout << "You can not move " << figureSelected << " to " << colTarget << lTarget << "\n";
					break;
				}
				else {
					*(*chessBoard[lineTarget])[columnTarget] = *(*chessBoard[lineSelect])[columnSelect];
					
					std::shared_ptr<NoneFigure> f = std::make_shared<NoneFigure>();
					f->init_figure();
					(*chessBoard[lineSelect])[columnSelect] = f;
					if (currentPlayer == 1) { currentPlayer = 2; }
					else { currentPlayer = 1; }
				}
				break;
			}
			int attackedKing = isKingAttacked(chessBoard);
			if (attackedKing != 0) {
				std::cout<< std::endl;
				if (attackedKing == currentPlayer) {
					//illegal
				}
				else if (attackedKing == 3) {
					std::cout << "Both kings are attacked!\n";
					//todo: this move is not allowed
				}
				else{
					std::cout << "The King of " << attackedKing << " gets attacked!\n";
					bool mate = isMate(chessBoard, attackedKing);
				}
			}			
			saveAndLoad.quicksave(chessBoard,currentPlayer);
		}
		else if (choice == "2") {
			printer.print(chessBoard);
		}
		else if (choice == "S") {
			std::cout<<std::endl;
			std::cout<< "Enter save-file-name or type d for default save" <<std::endl;
			std::cin >>  saveFileName;
			if(saveFileName == "d"){
				saveAndLoad.save(chessBoard, currentPlayer,defaultSaveFileName);
			}
			else{
				saveAndLoad.save(chessBoard, currentPlayer,saveFileName);
				}
		}
		else if (choice == "L") {
			chessBoard.clear();
		
			bool gameIsSelected = false;
			std::string selectedGame = "";
			std::vector<std::string> gamesToLoad;
			std::cout << "These games can continue:\n";
			 for (const auto & entry : std::filesystem::directory_iterator("StartedGames")){
				gamesToLoad.push_back(entry.path().string().substr(13, entry.path().string().length() - 1)); //just show the raw file names (raw filename would be sth. like "StartedGames\\Chess_Save.txt" )
				std::cout << entry.path().string().substr(13, entry.path().string().length() - 1) << std::endl;
			 }
			std::cout << "Please select a game with which you want to continue:\n";	
			//waits till you selected a game which you want to continue
			while(!gameIsSelected){				
				std::cin >> selectedGame;
				if (std::find(gamesToLoad.begin(), gamesToLoad.end(), selectedGame) != gamesToLoad.end()){
						std::cout << "Game was found!" << std::endl;
						gameIsSelected = true;
						saveFileName = selectedGame;
				}else {
					std::cout << "There is no game with the entered name. Please try again.\n";
				}				
			}
			currentPlayer = saveAndLoad.load(chessBoard, selectedGame);
			if(currentPlayer == 3){
				chessBoard.clear();
				initBoard(chessBoard);
				currentPlayer = 1;
			}
			saveAndLoad.quicksave(chessBoard,currentPlayer);
		}
		else if (choice == "R") {
			chessBoard.clear();
			initBoard(chessBoard);
			currentPlayer = 1;
			saveAndLoad.quicksave(chessBoard,currentPlayer);
		}
		else if (choice == "E") { play = false; }
		else { std::cout << "Wrong input, try again.\n"; }
		std::cout << "\n";
	}
	return 0;
}