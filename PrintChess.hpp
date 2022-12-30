#include <vector>
#include <iostream>
#include <windows.h>

#ifndef _PRINTCHESS_
#define _PRINTCHESS_

class printChess {
public:
	void print(std::vector<std::vector<Figure*>*>& c) {
		int blackp0 = 0;
		int greenp1 = 10;
		int redp2 = 12;
		int brightwhite = 15;
		HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleTextAttribute(hConsole, brightwhite);

		std::cout << "===============================================\n";
		std::cout << "||-|  A |  B |  C |  D |  E |  F |  G |  H |-||\n";
		std::cout << "||=|=======================================|=||\n";
		for (int i = 0; i < 8; i++) {
			std::cout << "||" << 8 - i << "| ";
			for (int j = 0; j < 8; j++) {
				if ((*(*c[i])[j]).get_player() == 1) {
					SetConsoleTextAttribute(hConsole, greenp1);
				}
				else if ((*(*c[i])[j]).get_player() == 2) {
					SetConsoleTextAttribute(hConsole, redp2);
				}
				else {
					SetConsoleTextAttribute(hConsole, blackp0);
				}
				std::cout << (*(*c[i])[j]).get_2print();
				SetConsoleTextAttribute(hConsole, brightwhite);
				if (j < 7) {
					std::cout << " | ";
				}
				else {
					std::cout << " |";
				}
			}
			std::cout << 8 - i << "||\n";

			if (i < 7) {
				std::cout << "||-|----+----+----+----+----+----+----+----|-||\n";
			}
		}
		std::cout << "||=|=======================================|=||\n";
		std::cout << "||-|  A |  B |  C |  D |  E |  F |  G |  H |-||\n";
		std::cout << "===============================================\n";
	}
};

#endif _PRINTCHESS_