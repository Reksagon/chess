#include <iostream>
#include <string>
#include "chess.h"

using namespace std;





int main()
{
	setlocale(LC_ALL, "rus");
	Board b;
	string s;
	bool newgame = true;
	cout << endl << endl;
	cout << "\t _   _   _      ____      _    _   ___    ___      ____    _________           _" << endl;
	cout << "\t| | | | | |    / /\\ \\    \\ \\  / / |   \\  /   |    / /\\ \\  |___  ____| | |___  | |" << endl;
	cout << "\t| | | | | |   / /__\\ \\    \\ \\/ /  | |\\ \\/ /| |   / /__\\ \\     | |     | | \\ \\ | |" << endl;
	cout << "\t| |_| |_| |  / /____\\ \\   / /\\ \\  | | \\__/ | |  / /____\\ \\    | |     | |_/ / | |" << endl;
	cout << "\t|_________| /_/      \\_\\ /_/  \\_\\ |_|      |_| /_/      \\_\\   |_|     |____/  |_|" << endl;
	cout << endl << endl;
	cout << "\t \t \t Введите любой символ для продолжения..." << endl;
	cin >> s;



	while (newgame) {
		b.setBoard();
		
		while (b.playGame());
		cout << "Хотите начать игру заново? (y - да, n - нет) ";
		cin >> s;
		if (s != "y")
			newgame = false;
	}



	return 0;
}
