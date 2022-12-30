#include <iostream>
#include <vector>
#include <csignal>
#include <memory>
#include "ChessFigures.hpp"
#include "PrintChess.hpp"
#include "SafeAndLoadChess.hpp"



void signal_handler(int signal){
	std::remove("Chess_Safe.txt");
	std::rename("Chess_Quick_Safe.txt", "Chess_Safe.txt");
}
void exit_handler(){
	std::remove("Chess_Safe.txt");
	std::rename("Chess_Quick_Safe.txt", "Chess_Safe.txt");
}

void del(std::vector<std::shared_ptr<std::vector<std::shared_ptr<Figure>>>>& chessBoard) {
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			(*(*chessBoard[i])[j]).delete_figure_values();
			//delete((*chessBoard[i])[j]);
		}
		//delete(chessBoard[i]);
	}
}
void initBoard(std::vector<std::shared_ptr<std::vector<std::shared_ptr<Figure>>>>& chessBoard) {
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
}

int isKingAttacked(std::vector<std::shared_ptr<std::vector<std::shared_ptr<Figure>>>>& chessBoard) {
	bool isAttacked = false;
	int attackePlayer = 0;
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			if ((*chessBoard[i])[j]->get_Name() == 'K') {
				int playerOfKing = (*chessBoard[i])[j]->get_player();
				//check schraeg
				int c1 = j+1;
				int c2 = j-1;
				for (int l = i+1; l < 8; l++) {// i->7
					if (c1 < 8 && c1 >= 0) {
						if ((*chessBoard[l])[c1]->get_player() != 0 && (*chessBoard[l])[c1]->get_player() == playerOfKing) {
							c1 = 8;
						}
						else if ((*chessBoard[l])[c1]->get_player() != 0 && (*chessBoard[l])[c1]->get_player() != playerOfKing) {
							if ((*chessBoard[l])[c1]->get_Name() == 'L' || (*chessBoard[l])[c1]->get_Name() == 'Q') {
								isAttacked = true;
								break;
							}
						}
					}
					if (c2 < 8 && c2 >= 0) {
						if ((*chessBoard[l])[c2]->get_player() != 0 && (*chessBoard[l])[c2]->get_player() == playerOfKing) {
							c2 = -1;
						}
						else if ((*chessBoard[l])[c2]->get_player() != 0 && (*chessBoard[l])[c2]->get_player() != playerOfKing) {
							if ((*chessBoard[l])[c2]->get_Name() == 'L' || (*chessBoard[l])[c2]->get_Name() == 'Q') {
								isAttacked = true;
								break;
							}
						}
					}
					c1++;
					c2--;
				}
				int c3 = j+1;
				int c4 = j-1;
				for (int l = i-1; l >= 0; l--) {// i->0
					if (c3 < 8 && c3 >= 0) {
						if ((*chessBoard[l])[c3]->get_player() != 0 && (*chessBoard[l])[c3]->get_player() == playerOfKing) {
							c3 = 8;
						}
						else if ((*chessBoard[l])[c3]->get_player() != 0 && (*chessBoard[l])[c3]->get_player() != playerOfKing) {
							if ((*chessBoard[l])[c3]->get_Name() == 'L' || (*chessBoard[l])[c3]->get_Name() == 'Q') {
								isAttacked = true;
								break;
							}
						}
					}
					if (c4 < 8 && c4 >= 0) {
						if ((*chessBoard[l])[c4]->get_player() != 0 && (*chessBoard[l])[c4]->get_player() == playerOfKing) {
							c4 = -1;
						}
						else if ((*chessBoard[l])[c4]->get_player() != 0 && (*chessBoard[l])[c4]->get_player() != playerOfKing) {
							if ((*chessBoard[l])[c4]->get_Name() == 'L' || (*chessBoard[l])[c4]->get_Name() == 'Q') {
								isAttacked = true;
								break;
							}
						}
					}
					c3++;
					c4--;
				}
				// check gerade
				for(int lup = i-1; lup >=0;lup--){
					if ((*chessBoard[lup])[j]->get_player() != 0 && (*chessBoard[lup])[j]->get_player() == playerOfKing) {
						lup = -1;
					}
					else if ((*chessBoard[lup])[j]->get_player() != 0 && (*chessBoard[lup])[j]->get_player() != playerOfKing) {
						if ((*chessBoard[lup])[j]->get_Name() == 'T' || (*chessBoard[lup])[j]->get_Name() == 'Q') {
							isAttacked = true;
							break;
						}
					}
				}
				for(int ldown = i+1; ldown <8; ldown++){
					if ((*chessBoard[ldown])[j]->get_player() != 0 && (*chessBoard[ldown])[j]->get_player() == playerOfKing) {
						ldown = 8;
					}
					else if ((*chessBoard[ldown])[j]->get_player() != 0 && (*chessBoard[ldown])[j]->get_player() != playerOfKing) {
						if ((*chessBoard[ldown])[j]->get_Name() == 'T' || (*chessBoard[ldown])[j]->get_Name() == 'Q') {
							isAttacked = true;
							break;
						}
					}
				}
				for(int cleft = j-1; cleft >=0;cleft--){
					if ((*chessBoard[i])[cleft]->get_player() != 0 && (*chessBoard[i])[cleft]->get_player() == playerOfKing) {
						cleft = -1;
					}
					else if ((*chessBoard[i])[cleft]->get_player() != 0 && (*chessBoard[i])[cleft]->get_player() != playerOfKing) {
						if ((*chessBoard[i])[cleft]->get_Name() == 'T' || (*chessBoard[i])[cleft]->get_Name() == 'Q') {
							isAttacked = true;
							break;
						}
					}
				}
				for(int cright = j+1; cright <8;cright++){
					if ((*chessBoard[i])[cright]->get_player() != 0 && (*chessBoard[i])[cright]->get_player() == playerOfKing) {
						cright = 8;
					}
					else if ((*chessBoard[i])[cright]->get_player() != 0 && (*chessBoard[i])[cright]->get_player() != playerOfKing) {
						if ((*chessBoard[i])[cright]->get_Name() == 'T' || (*chessBoard[i])[cright]->get_Name() == 'Q') {
							isAttacked = true;
							break;
						}
					}
				}
				// check springer
				if((i+1)<8 && (j+2)<8){
					if ((*chessBoard[i+1])[j+2]->get_Name() == 'S' && (*chessBoard[i+1])[j+2]->get_player() != playerOfKing) {
								isAttacked = true;
					}
				}
				if((i+1)<8 && (j-2)>=0){
					if ((*chessBoard[i+1])[j-2]->get_Name() == 'S' && (*chessBoard[i+1])[j-2]->get_player() != playerOfKing) {
								isAttacked = true;
					}
				}
				if((i-1)>=0 && (j+2)<8){
					if ((*chessBoard[i-1])[j+2]->get_Name() == 'S' && (*chessBoard[i-1])[j+2]->get_player() != playerOfKing) {
								isAttacked = true;
					}
				}
				if((i-1)>=0 && (j-2)>=0){
					if ((*chessBoard[i-1])[j-2]->get_Name() == 'S' && (*chessBoard[i-1])[j-2]->get_player() != playerOfKing) {
								isAttacked = true;
					}
				}

				if((i+2)<8 && (j+1)<8){
					if ((*chessBoard[i+2])[j+1]->get_Name() == 'S' && (*chessBoard[i+2])[j+1]->get_player() != playerOfKing) {
								isAttacked = true;
					}
				}
				if((i+2)<8 && (j-1)>=0){
					if ((*chessBoard[i+2])[j-1]->get_Name() == 'S' && (*chessBoard[i+2])[j-1]->get_player() != playerOfKing) {
								isAttacked = true;
					}
				}
				if((i-2)>=0 && (j+1)<8){
					if ((*chessBoard[i-2])[j+1]->get_Name() == 'S' && (*chessBoard[i-2])[j+1]->get_player() != playerOfKing) {
							isAttacked = true;
					}
				}
				if((i-2)>=0 && (j-1)>=0){
					if ((*chessBoard[i-2])[j-1]->get_Name() == 'S' && (*chessBoard[i-2])[j-1]->get_player() != playerOfKing) {
							isAttacked = true;
					}
				}

				//check Bauer
				if(playerOfKing==1){
					if((i+1)<8 && (j-1)>=0){
						if ((*chessBoard[i+1])[j-1]->get_Name() == 'B' && (*chessBoard[i+1])[j-1]->get_player() != playerOfKing) {
							isAttacked = true;
						}
					}
					if((i+1)<8 && (j+1)<8){
						if ((*chessBoard[i+1])[j+1]->get_Name() == 'B' && (*chessBoard[i+1])[j+1]->get_player() != playerOfKing) {
							isAttacked = true;
						}
					}
				}
				else{
					if((i-1)>=0 && (j-1)>=0){
						if ((*chessBoard[i-1])[j-1]->get_Name() == 'B' && (*chessBoard[i-1])[j-1]->get_player() != playerOfKing) {
							isAttacked = true;
						}
					}
					if((i-1)>=0 && (j+1)<8){
						if ((*chessBoard[i-1])[j+1]->get_Name() == 'B' && (*chessBoard[i-1])[j+1]->get_player() != playerOfKing) {
							isAttacked = true;
						}
					}
				}
				



				if (isAttacked) { attackePlayer = attackePlayer + playerOfKing; }
			}
		}
	}
	return attackePlayer;
}

int main()
{
	//std::signal(SIGINT,signal_handler);
	std::atexit(exit_handler);
	
	std::vector<std::shared_ptr<std::vector<std::shared_ptr<Figure>>>> chessBoard;
	initBoard(chessBoard);
	printChess printer;
	safeAndLoadChess safeAndLoad;
	printer.print(chessBoard);
	bool play = true;
	int currentPlayer = 1;
	while (play) {
		std::string choice;
		std::cout << "Player " << currentPlayer << " Type:\n";
		std::cout << "1 to move a figure\n"
			<< "2 to print the chessboard\n"
			<< "S to safe the game\n"
			<< "L to load game\n"
			<< "R to reset game\n"
			<< "E to end\n";
		std::cin >> choice;
		std::cout << "\n";
		if (choice == "1") {
			while (true) {
				//Select figure
				std::string colSelect;
				std::string lSelect;
				std::cout << "To choose the figure please enter coloumn char:\n";
				std::cin >> colSelect;
				int columnSelect;
				if (colSelect == "A") { columnSelect = 0; }
				else if (colSelect == "B") { columnSelect = 1; }
				else if (colSelect == "C") { columnSelect = 2; }
				else if (colSelect == "D") { columnSelect = 3; }
				else if (colSelect == "E") { columnSelect = 4; }
				else if (colSelect == "F") { columnSelect = 5; }
				else if (colSelect == "G") { columnSelect = 6; }
				else if (colSelect == "H") { columnSelect = 7; }
				else {
					std::cout << "Wrong input!\n";
					break;
				}
				std::cout << "To choose the figure please enter line number:\n";
				std::cin >> lSelect;
				int lineSelect = 8 - std::stoi(lSelect);
				if (lineSelect < 0 || lineSelect >7) {
					std::cout << "Wrong input!\n";
					break;
				}

				if (!((*(*chessBoard[lineSelect])[columnSelect]).get_player() == currentPlayer)) {
					std::cout << "You can only select figures of player " << currentPlayer << "\n";
					break;
				}
				//Select target position
				std::string colTarget;
				std::string lTarget;
				std::cout << "To choose the target position enter coloumn char:\n";
				std::cin >> colTarget;
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
					std::cout << "Wrong input!\n";
					break;
				}
				std::cout << "To choose the target position  enter line number:\n";
				std::cin >> lTarget;
				int lineTarget = 8 - std::stoi(lTarget);
				if (lineTarget < 0 || lineTarget >7) {
					std::cout << "Wrong input!\n";
					break;
				}
				//Check if figure can move to target position
				if (!(((*(*chessBoard[lineSelect])[columnSelect])).moveFigure(currentPlayer, columnSelect, lineSelect, columnTarget, lineTarget, chessBoard))) {
					std::cout << "You can not move " << colSelect << lSelect << " to " << colTarget << lTarget << "\n";
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
				if (attackedKing != 3) {
					std::cout << "The King of " << attackedKing << " gets attacked!\n";
				}
				else {
					std::cout << "Both kings are attacked!\n";
				}
			}
			
			safeAndLoad.quicksafe(chessBoard,currentPlayer);
		}
		else if (choice == "2") {
			printer.print(chessBoard);
		}
		else if (choice == "S") {
			safeAndLoad.safe(chessBoard, currentPlayer);
		}
		else if (choice == "L") {
			del(chessBoard);
			chessBoard.clear();
			currentPlayer = safeAndLoad.load(chessBoard);
		}
		else if (choice == "R") {
			del(chessBoard);
			chessBoard.clear();
			initBoard(chessBoard);
			currentPlayer = 1;
			safeAndLoad.quicksafe(chessBoard,currentPlayer);
		}
		else if (choice == "E") { 
			safeAndLoad.safe(chessBoard, currentPlayer);
			play = false; 
		}
		else { std::cout << "Wrong input, try again.\n"; }
		std::cout << "\n";
	}
	del(chessBoard);
	return 0;
}