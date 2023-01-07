#include <vector>
#include <iostream>
#include <memory>

#ifndef _PRINTCHESS_
#define _PRINTCHESS_  
 
class printChess {
public:
	void print(std::vector<std::shared_ptr<std::vector<std::shared_ptr<Figure>>>>& c) {
		std::cout << "=======================================\n";
		std::cout << "||-| A | B | C | D | E | F | G | H |-||\n";
		std::cout << "||=|===============================|=||\n";
		for (int i = 0; i < 8; i++) {
			std::cout << "||" << 8 - i << "| ";
			for (int j = 0; j < 8; j++) {

				std::cout << (*(*c[i])[j]).get_2print();
				
				if (j < 7) {
					std::cout << " | ";
				}
				else {
					std::cout << " |";
				}
			}
			std::cout << 8 - i << "||\n";

			if (i < 7) {
				std::cout << "||-|---+---+---+---+---+---+---+---|-||\n";
			}
		}
		std::cout << "||=|===============================|=||\n";
		std::cout << "||-| A | B | C | D | E | F | G | H |-||\n";
		std::cout << "=======================================\n";
	}
};

#endif //_PRINTCHESS_