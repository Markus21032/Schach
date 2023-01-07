#include <iostream>
#include <vector>
#include <csignal>
#include <string>
#include <memory>
#include <algorithm>

std::string defaultSaveFileName = "Chess_Save";
std::string saveFileName = "d";
int currentPlayer = 1;

#include "ChessFigures.hpp"
#include "ChessBoard.hpp"
#include "PrintChess.hpp"
#include "SaveAndLoadChess.hpp"
#include "Algorithm.hpp"


 
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

std::shared_ptr<std::vector<int>> checkAndGetSeletedPosition(std::string input)
{
	//check column
	std::string columnChar = input.substr(0, 1);
	int columnSelect;
	if (columnChar == "A")
	{
		columnSelect = 0;
	}
	else if (columnChar == "B")
	{
		columnSelect = 1;
	}
	else if (columnChar == "C")
	{
		columnSelect = 2;
	}
	else if (columnChar == "D")
	{
		columnSelect = 3;
	}
	else if (columnChar == "E")
	{
		columnSelect = 4;
	}
	else if (columnChar == "F")
	{
		columnSelect = 5;
	}
	else if (columnChar == "G")
	{
		columnSelect = 6;
	}
	else if (columnChar == "H")
	{
		columnSelect = 7;
	}
	else
	{
		return nullptr;
	}

	//check row 
	int lineSelect = 0;
	try
	{
		lineSelect = 8 - std::stoi(input.substr(1, 1));
	}
	catch (std::invalid_argument)
	{
		return nullptr;
	}

	if (lineSelect < 0 || lineSelect > 7)
	{
		return nullptr;
	}

	auto selectedPosition = std::make_shared<std::vector<int>>();
	(*selectedPosition).push_back(lineSelect);
	(*selectedPosition).push_back(columnSelect);
	return selectedPosition;
}

int main()
{
	std::atexit(exit_handler);

	ChessBoard chessBoard;
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
				std::cout << "To choose the figure please enter the position of it:\n";
				std::cin >> figureSelected;
				auto input = checkAndGetSeletedPosition(figureSelected);
				int lineSelect;
				int columnSelect;
				if(input != nullptr){
					lineSelect = (*input)[0];
					columnSelect = (*input)[1];
				}
				else{
					std::cout << "Wrong Input!";
					break;
				}
				if (!(chessBoard.getFigure(lineSelect,columnSelect)->get_player() == currentPlayer)) {
					std::cout << "You can only select figures of player " << currentPlayer << "\n";
					break;
				}
				//Select target position
				std::string targetPosition;				
				
				std::cout << "Please enter a target position:\n";
				std::cin >> targetPosition;

				input = checkAndGetSeletedPosition(targetPosition);
				int lineTarget;
				int columnTarget;
				if(input != nullptr){
					lineTarget = (*input)[0];
					columnTarget = (*input)[1];
				}
				else{
					std::cout << "Wrong Input!";
					break;
				}

				//Check if figure can move to target position
				if (!(chessBoard.validateMove(lineSelect,columnSelect, lineTarget, columnTarget))) {
					std::cout << "You can not move " << figureSelected << " to " << targetPosition << "\n";
					break;
				}
				else {
					//move figure on temp board
					ChessBoard tempChessBoard;
					tempChessBoard = copyBoard(chessBoard);
					tempChessBoard.moveFigure(lineSelect,columnSelect,lineTarget,columnTarget);					


					int attackedKing = inCheck(tempChessBoard.getBoard());
					if (attackedKing != 0) {
						std::cout<< std::endl;
						if (attackedKing == currentPlayer) {//illegal
							std::cout << "You can not move " << figureSelected << " to " << targetPosition << "\n";
							std::cout << "Your own kings would be attacked!\n";
							break;
						}
						else if (attackedKing == 3) {//illegal
							std::cout << "You can not move " << figureSelected << " to " << targetPosition << "\n";
							std::cout << "Both kings would be attacked!\n";
							break;
						}
						else{//legal
							std::cout << "The King of " << attackedKing << " gets attacked!\n";

							//move on chessBoard
							chessBoard.moveFigure(lineSelect,columnSelect,lineTarget,columnTarget);

							//check if mate
							//bool mate = isCheckMate(chessBoard, attackedKing);
						}
					}
					else{//move on chessBoard
						chessBoard.moveFigure(lineSelect,columnSelect,lineTarget,columnTarget);
					}		

					if (currentPlayer == 1) { currentPlayer = 2; }
					else { currentPlayer = 1; }
				}
				break;
			}
			
			saveAndLoad.quicksave(chessBoard.getBoard());
		}
		else if (choice == "2") {
			printer.print(chessBoard);
		}
		else if (choice == "S") {
			std::cout<<std::endl;
			std::cout<< "Enter save-file-name or type d for default save" <<std::endl;
			std::cin >>  saveFileName;
			if(saveFileName == "d"){
				saveAndLoad.save(chessBoard.getBoard(), defaultSaveFileName);
			}
			else{
				saveAndLoad.save(chessBoard.getBoard(), saveFileName);
				}
		}
		else if (choice == "L") {
		
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
			std::vector<std::shared_ptr<std::vector<std::shared_ptr<Figure>>>> chessBoardVector;
			currentPlayer = saveAndLoad.load(chessBoardVector, selectedGame);
			chessBoard.overrideBoard(chessBoardVector);
			if(currentPlayer != 1 && currentPlayer != 2){
				chessBoard.resetBoard();
			}
			saveAndLoad.quicksave(chessBoard.getBoard());
		}
		else if (choice == "R") {
			chessBoard.resetBoard();
			saveAndLoad.quicksave(chessBoard.getBoard());
		}
		else if (choice == "E") { play = false; }
		else { std::cout << "Wrong input, try again.\n"; }
		std::cout << "\n";
	}
	return 0;
}