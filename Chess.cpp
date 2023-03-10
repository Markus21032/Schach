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

/*
Checks if given user input is legal and gives back a vector with selected row and column.
For an invalid input the function returns a nullptr
*/

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
	int rowSelect = 0;
	try
	{
		rowSelect = 8 - std::stoi(input.substr(1, 1));
	}
	catch (std::invalid_argument)
	{
		return nullptr;
	}

	if (rowSelect < 0 || rowSelect > 7)
	{
		return nullptr;
	}

	auto selectedPosition = std::make_shared<std::vector<int>>();
	(*selectedPosition).push_back(rowSelect);
	(*selectedPosition).push_back(columnSelect);
	return selectedPosition;
}

/*
is called after the game has ended (draw or checkmate) and lets the user decide whether he wants to play again
*/
void endGame(ChessBoard &chessboard, bool &play){
	while(true){
		std::cout << "Do you want to play again? (y/n)" << std::endl;
		std::string choice;
		std::cin >> choice;
		if(choice == "y"){
			chessboard.resetBoard();
			currentPlayer = 1; 
			return;
		}
		else if (choice == "n")
		{
			exit(0); //end program
		}
		else{
			std::cout << "illegal input" << std::endl;
		}
	}
}

int main()
{
	std::atexit(exit_handler);

	ChessBoard chessBoard;
	printChess printer;
	saveAndLoadChess saveAndLoad;
	printer.print(chessBoard);
	bool play = true;

	while (play) { //game loop
		std::string choice;
		std::cout << "Player " << currentPlayer << " Type:"<< std::endl;
		std::cout << "1 to move a figure"<< std::endl
			<< "2 to print the chessboard"<< std::endl
			<< "S to save the game"<< std::endl
			<< "L to load game"<< std::endl
			<< "R to reset game"<< std::endl
			<< "E to end"<< std::endl;
		std::cin >> choice;
		std::cout << std::endl;
		if (choice == "1") {
			while (true) {
				//Select figure
				std::string figureSelected;
				std::cout << "To choose the figure please enter the position of it:"<< std::endl;
				std::cin >> figureSelected;
				auto input = checkAndGetSeletedPosition(figureSelected);
				int lineSelect;
				int columnSelect;
				if(input != nullptr){ //if user input was illegal
					lineSelect = (*input)[0];
					columnSelect = (*input)[1];
				}
				else{
					std::cout << "Wrong Input!";
					break;
				}
				if (!(chessBoard.getFigure(lineSelect,columnSelect)->get_player() == currentPlayer)) { //if a figure of the other player is selected
					std::cout << "You can only select figures of player " << currentPlayer << std::endl;
					break;
				}
				//Select target position
				std::string targetPosition;				
				
				std::cout << "Please enter a target position:"<< std::endl;
				std::cin >> targetPosition;

				input = checkAndGetSeletedPosition(targetPosition);
				int lineTarget;
				int columnTarget;
				if(input != nullptr){ //if user input was illegal
					lineTarget = (*input)[0];
					columnTarget = (*input)[1];
				}
				else{
					std::cout << "Wrong Input!";
					break;
				}

				//Check if figure can move to target position
				if (!(chessBoard.validateMove(lineSelect, columnSelect, lineTarget, columnTarget))) {
					std::cout << "You can not move " << figureSelected << " to " << targetPosition << std::endl;
					break;
				}
				else {
					//move figure on copied temp board to use the inCheck() function to determine whether the move is legal without 
					//changing the play board
					ChessBoard tempChessBoard;
					tempChessBoard = chessBoard.copyBoard();
					tempChessBoard.moveFigure(lineSelect, columnSelect, lineTarget, columnTarget);					

					int inCheckKingPlayer1 = tempChessBoard.inCheck(1);
					int inCheckKingPlayer2 = tempChessBoard.inCheck(2);

					if (inCheckKingPlayer1 || inCheckKingPlayer2) { //if least one player is in check
						std::cout<< std::endl;
						if (1 == currentPlayer) {
							if(inCheckKingPlayer1 && inCheckKingPlayer2){ //illegal
								std::cout << "You can not move " << figureSelected << " to " << targetPosition << std::endl;
								std::cout << "Both kings would be attacked!" << std::endl;
								break;
							}
							else if(inCheckKingPlayer1 && !inCheckKingPlayer2){ //illegal
								std::cout << "You can not move " << figureSelected << " to " << targetPosition << std::endl;
								std::cout << "Your own kings would be attacked!"<< std::endl;
								break;
							}
							else{ //move of figure is legal and sets the opponent king in check, so do the move on the play board
								std::cout << "The King of Player " << 2 << " gets attacked!"<< std::endl;

								//move on chessBoard
								chessBoard.moveFigure(lineSelect,columnSelect,lineTarget,columnTarget);

								//check if the move leads to checkmate
								if(chessBoard.isCheckMate(2)){
									std::cout<<"Player 2 is checkmate"<<std::endl;
									endGame(chessBoard, play);
									//Player will be switched after move
									currentPlayer = 2;
								}
							}							
						}
						else{
							if(inCheckKingPlayer1 && inCheckKingPlayer2){ //illegal
								std::cout << "You can not move " << figureSelected << " to " << targetPosition << std::endl;
								std::cout << "Both kings would be attacked!"<< std::endl;
								break;
							}
							else if(!inCheckKingPlayer1 && inCheckKingPlayer2){ //illegal
								std::cout << "You can not move " << figureSelected << " to " << targetPosition << std::endl;
								std::cout << "Your own kings would be attacked!"<< std::endl;
								break;
							}
							else{ //move of figure is legal and sets the opponent king in check, so do the move on the play board

								std::cout << "The King of Player " << 1 << " gets attacked!"<< std::endl;

								//move on chessBoard
								chessBoard.moveFigure(lineSelect,columnSelect,lineTarget,columnTarget);

								//check if the move leads to checkmate
								if(chessBoard.isCheckMate(1)){
									std::cout<<"Player 1 is checkmate"<<std::endl;
									endGame(chessBoard, play);
									//Player will be switched after move
									currentPlayer = 2;
								}
							}
						}
					}
					else{ 
					/*move is legal but does not lead to check, so execute the move and check if 
					it leads to a draw through stalemate or insufficientMaterial (ref. https://www.chess.com/terms/draw-chess)*/

						chessBoard.moveFigure(lineSelect,columnSelect,lineTarget,columnTarget);

						if(chessBoard.isStalemate() || chessBoard.insufficientMaterial()){
						std::cout << std::endl << "Draw!" << std::endl;
						endGame(chessBoard, play);
						break;
						}
					}		

					//change the player after the move is completed
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
			std::cout << "These games can continue:"<< std::endl;
			 for (const auto & entry : std::filesystem::directory_iterator("StartedGames")){
				gamesToLoad.push_back(entry.path().string().substr(13, entry.path().string().length() - 1)); //just show the raw file names (raw filename would be sth. like "StartedGames\\Chess_Save.txt" )
				std::cout << entry.path().string().substr(13, entry.path().string().length() - 1) << std::endl;
			 }
			std::cout << "Please select a game with which you want to continue or enter q to quit:"<< std::endl;	
			//waits till you selected a game which you want to continue
			while(!gameIsSelected){				
				std::cin >> selectedGame;
				if (std::find(gamesToLoad.begin(), gamesToLoad.end(), selectedGame) != gamesToLoad.end()){
						gameIsSelected = true;
						saveFileName = selectedGame;
						std::cout << "File found!" << std::endl;
				}
				else if(selectedGame == "q"){
					gameIsSelected = true;
				}else {
					std::cout << "There is no game with the entered name. Please try again."<< std::endl;
				}				
			}
			if(selectedGame != "q"){
				std::vector<std::shared_ptr<std::vector<std::shared_ptr<Figure>>>> chessBoardVector;
				currentPlayer = saveAndLoad.load(chessBoardVector, selectedGame);
				chessBoard.overrideBoard(chessBoardVector);
				if(currentPlayer != 1 && currentPlayer != 2){
					std::cout << "Bad file" << std::endl;
					chessBoard.resetBoard();
				}
				printer.print(chessBoard);
				saveAndLoad.quicksave(chessBoard.getBoard());

				//check if the figure on the loaded board positions instantly lead to checkmate or draw

				if(chessBoard.inCheck(1)){
					if(chessBoard.isCheckMate(1)){
						std::cout << "Player 1 is checkmate"<< std::endl;
						endGame(chessBoard, play);
					}
				}
				else if(chessBoard.inCheck(2)){
					if(chessBoard.isCheckMate(2)){
						std::cout << "Player 2 is checkmate"<< std::endl;
						endGame(chessBoard, play);
					}
				}
				else if(chessBoard.isStalemate() || chessBoard.insufficientMaterial()){
					std::cout << "Draw!" << std::endl;
					endGame(chessBoard, play);
				}
			}
		}
		else if (choice == "R") {
			chessBoard.resetBoard();
			saveAndLoad.quicksave(chessBoard.getBoard());
		}
		else if (choice == "E") { play = false; }
		else { std::cout << "Wrong input, try again."<< std::endl; }
		std::cout<< std::endl;
	}
	return 0;
}

