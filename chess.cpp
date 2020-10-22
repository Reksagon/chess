#include "chess.h"

int rookw1 = 0;
int rookw2 = 0;
int rookb1 = 0;
int rookb2 = 0;
int kingw = 0;
int kingb = 0;

Square::Square()
{
	piece = EMPTY;
	color = NONE;
}

void Square::setSpace(Square* space) 
{
	color = space->getColor();
	piece = space->getPiece();
}

void Square::setEmpty() //установка пустого места после хода
{
	color = NONE;
	piece = EMPTY;
}

Piece Square::getPiece() //узнать название фигуры на клетке
{
	return piece;
}

Color Square::getColor() //узнать цвет фигуры на клетке
{
	return color;
}

void Square::setPieceAndColor(Piece p, Color c) //установка названия фигуры и цвета
{
	piece = p;
	color = c;

}


void Board::printBoard() //вывод доски
{
	using namespace std;
	cout << "   y:  0    1     2     3     4     5     6     7 " << endl << "x:" << endl;
	for (int i = 0; i < 8; i++)
	{
		 cout << "    ------------------------------------------------" << endl;
		cout << "  " << i << " ";
		for (int j = 0; j < 8; j++)
		{
			Piece p = square[i][j].getPiece();
			Color c = square[i][j].getColor();

			

			switch (p)
			{
			case KING: (c == WHITE) ? cout << "| WK |" : cout << "| BK |";
				break;
			case QUEEN: (c == WHITE) ? cout << "| WQ |" : cout << "| BQ |";
				break;
			case BISHOP:(c == WHITE) ? cout << "| WB |" : cout << "| BB |";
				break;
			case KNIGHT:(c == WHITE) ? cout << "| WH |" : cout << "| BH |";
				break;
			case ROOK: (c == WHITE) ? cout << "| WR |" : cout << "| BR |";
				break;
			case PAWN: (c == WHITE) ? cout << "| WP |" : cout << "| BP |";
				break;
			case EMPTY: cout << "|" << "    " << "|";
				break;
			default: cout << "XXX";
				break;
			}

		}
		
cout << endl;
	}
	cout << "    ------------------------------------------------" << endl;
}

bool Board::doMove() //сделать ход
{
	using namespace std;
	string move;
	int x1, x2, y1, y2;
	bool stop = false;
	cout << "1 - Сделать ход" << endl;
	cout << "2 - Сохранить игру" << endl;
	cout << "3 - Загрузить игру" << endl;
	cout << "4 - Перезапустить игру" << endl;
	int a;
	GG:
	cin >> a;
	if (a > 4 || a < 1) { cout << "Не правильный ввол. Введите правильно!" << endl; goto GG; }


	if (a == 1) //для выбора Сделать Ход
	{
		
		while (!stop)
		{
			(turn == WHITE) ? cout << "Ход белых" << endl : cout << "Ход черных" << endl;
			cout << "Введите ваш ход в виде одной строки из четырех символов. Сначала используйте X-координаты в каждой паре." << endl;
			cin >> move;
			x1 = move[0] - 48;
			y1 = move[1] - 48;
			x2 = move[2] - 48;
			y2 = move[3] - 48;
			

			if (getSquare(x2, y2)->getPiece() == KING) //если ход на короля то мат

			{
				if (getSquare(x1, y1)->getColor() == WHITE) //если ходили белые
				{
					cout << "Белые выиграли!" << endl;
					return false;
				}
				else

				{
					cout << "Черные выиграли!" << endl; // иначе черные
					return false;
				}
			}
			
			
			if (getSquare(x1, y1)->getColor() == turn)
			{


				if (makeMove(x1, y1, x2, y2) == false)
				{
					cout << "Неверный ход, попробуйте еще раз." << endl;
				}
				else
					stop = true;
			} 
			else
				cout << "Попробуйте еще раз." << endl;
		}
		
	 
		if (turn == BLACK) //меняет цвет хода следующего
			turn = WHITE;
		else
			turn = BLACK;
		return true;

	
	}



	

	else if (a == 3) //загрузка игры
	{
		ifstream file1("SAVE.txt"); //загрузка расстановки
		file1.read(reinterpret_cast<char*>(&square), sizeof(square));
		file1.close();

		ifstream in("TURN.txt"); //загрузка хода
		string s;
		getline(in, s);
		int clr;
		clr = atoi(s.c_str());
		if (clr == 0) turn = WHITE;
		else turn = BLACK;

		ifstream inking("KINGW.txt"); //загрузка ходил ли король для рокировки
		string s1;
		getline(inking, s1);
		int kings;
		kings = atoi(s1.c_str());
		kingw = kings;

		ifstream inrookw2("ROOKW2.txt"); //загрузка ходила ли вторая ладья белых для рокировки
		string rookw2s;
		getline(inrookw2, rookw2s);
		int rookw22;
		rookw22 = atoi(rookw2s.c_str());
		rookw2 = rookw22;

		ifstream inrookw1("ROOKW1.txt"); //загрузка ходила ли первая ладья белых для рокировки
		string rookw1s;
		getline(inrookw1, rookw1s);
		int rookw11;
		rookw11 = atoi(rookw1s.c_str());
		rookw1 = rookw11;

		ifstream inrookb2("ROOKB2.txt");//загрузка ходила ли вторая ладья черных для рокировки
		string rookb2s;
		getline(inrookb2, rookb2s);
		int rookb22;
		rookb22 = atoi(rookb2s.c_str());
		rookb2 = rookb22;

		ifstream inrookb1("ROOKB1.txt");//загрузка ходила ли первая ладья черных для рокировки
		string rookb1s;
		getline(inrookb1, rookb1s);
		int rookb11;
		rookb11 = atoi(rookb1s.c_str());
		rookb1 = rookb11;


	}

	else  if (a == 2) //все тоже только сохранение
	{
		ofstream file("SAVE.txt", ios::binary);
		file.write(reinterpret_cast<char*>(&square), sizeof(square));
		file.close();
		
		ofstream out("TURN.txt");
		out << turn;
		out.close();
		
		ofstream KINGKW("KINGW.txt");
		out << kingw;
		KINGKW.close();
		
		ofstream ROOKW2("ROOKW2.txt");
		out << rookw2;
		ROOKW2.close();
		
		ofstream ROOKW1("ROOKW1.txt");
		out << rookw1;
		ROOKW1.close();

		ofstream ROOKB2("ROOKB2.txt");
		out << rookb2;
		ROOKB2.close();

		ofstream ROOKB1("ROOKB1.txt");
		out << rookb1;
		ROOKB1.close();
	}

	if (a == 4) //начать игру заново
	{
		turn = WHITE;
		return false;
		
	}
	return true;

}

void Board::setBoard() //начальная расстановка шахтат на доске
{
	square[0][0].setPieceAndColor(ROOK, WHITE);
	square[1][0].setPieceAndColor(KNIGHT, WHITE);
	square[2][0].setPieceAndColor(BISHOP, WHITE);
	square[3][0].setPieceAndColor(QUEEN, WHITE);
	square[4][0].setPieceAndColor(KING, WHITE);
	square[5][0].setPieceAndColor(BISHOP, WHITE);
	square[6][0].setPieceAndColor(KNIGHT, WHITE);
	square[7][0].setPieceAndColor(ROOK, WHITE);

	square[0][7].setPieceAndColor(ROOK, BLACK);
	square[1][7].setPieceAndColor(KNIGHT, BLACK);
	square[2][7].setPieceAndColor(BISHOP, BLACK);
	square[3][7].setPieceAndColor(QUEEN, BLACK);
	square[4][7].setPieceAndColor(KING, BLACK);
	square[5][7].setPieceAndColor(BISHOP, BLACK);
	square[6][7].setPieceAndColor(KNIGHT, BLACK);
	square[7][7].setPieceAndColor(ROOK, BLACK);

	for (int i = 0; i < 8; i++)
	{
		square[i][1].setPieceAndColor(PAWN, WHITE);
		square[i][6].setPieceAndColor(PAWN, BLACK);

	}
	for (int i = 2; i < 6; i++)
	{
		for (int j = 0; j < 8; j++)
			square[j][i].setPieceAndColor(EMPTY, NONE);

	}
	for (int i = 0; i < 8; i++)
		for (int j = 0; j < 8; j++)
		{
			square[i][j].setX(i);
			square[i][j].setY(j);
		}

}

bool Board::playGame() //играть в игру :)
{
	system("cls");
	printBoard();
	return doMove();

}

bool Board::moveKing(Square* thisKing, Square* thatSpace)  //ход королем
{
	int x = thisKing->getX();
	int y = thisKing->getY();
	
	if (thatSpace->getX() > 4) //ход для рокировки ход вверх
	{
		//бля белых
		if (square[4][0].getPiece() == KING && square[5][0].getPiece() == EMPTY && square[6][0].getPiece() == EMPTY && square[7][0].getPiece() == ROOK && kingw == 0 && rookw2 == 0)
		{
			if (abs(thatSpace->getX() - thisKing->getX()) == 2)
				if (abs(thatSpace->getY() - thisKing->getY()) == 1 || abs(thatSpace->getX() - thisKing->getX()) == 2)
				{
					thatSpace->setSpace(thisKing);
					thisKing->setEmpty();
					square[5][0].setPieceAndColor(ROOK, WHITE);
					square[7][0].setPieceAndColor(EMPTY, NONE);
					return true;
				}
		}
		//для черных
		if (square[4][7].getPiece() == KING && square[5][7].getPiece() == EMPTY && square[6][7].getPiece() == EMPTY && square[7][7].getPiece() == ROOK && kingb == 0 && rookb2 == 0)
		{
			if (abs(thatSpace->getX() - thisKing->getX()) == 2)
				if (abs(thatSpace->getY() - thisKing->getY()) == 2 || abs(thatSpace->getX() - thisKing->getX()) == 2)
				{
					thatSpace->setSpace(thisKing);
					thisKing->setEmpty();
					square[5][7].setPieceAndColor(ROOK, WHITE);
					square[7][7].setPieceAndColor(EMPTY, NONE);
					return true;
				}
		}

	}

	if (thatSpace->getX() < 4) //ход вниз для рокировки
	{
		//ход белых
		if (square[4][0].getPiece() == KING && square[3][0].getPiece() == EMPTY && square[2][0].getPiece() == EMPTY && square[1][0].getPiece() == EMPTY && square[0][0].getPiece() == ROOK && kingw == 0 && rookw1 == 0 )
		{
			if (abs(thatSpace->getX() - thisKing->getX()) == 2)
				if (abs(thatSpace->getY() - thisKing->getY()) == 1 || abs(thatSpace->getX() - thisKing->getX()) == 2)
				{
					thatSpace->setSpace(thisKing);
					thisKing->setEmpty();
					square[3][0].setPieceAndColor(ROOK, WHITE);
					square[0][0].setPieceAndColor(EMPTY, NONE);
					return true;
				}
		}
		
		//ход черных
		if (square[4][7].getPiece() == KING && square[3][7].getPiece() == EMPTY && square[2][7].getPiece() == EMPTY && square[1][7].getPiece() == EMPTY && square[0][7].getPiece() == ROOK && kingb == 0 && rookb1 == 0)
		{
			if (abs(thatSpace->getX() - thisKing->getX()) == 2)
				if (abs(thatSpace->getY() - thisKing->getY()) == 1 || abs(thatSpace->getX() - thisKing->getX()) == 2)
				{
					thatSpace->setSpace(thisKing);
					thisKing->setEmpty();
					square[3][7].setPieceAndColor(ROOK, WHITE);
					square[0][7].setPieceAndColor(EMPTY, NONE);
					return true;
				}
		}
	}

	//обычный ход
	 if (abs(thatSpace->getX() - thisKing->getX()) == 1 || abs(thatSpace->getY() - thisKing->getY()) == 1)
		if (abs(thatSpace->getY() - thisKing->getY()) == 1 || abs(thatSpace->getX() - thisKing->getX()) == 1 )
		{
			if (getSquare(x, y)->getColor() == WHITE) { kingw = 1; } //если сделан ход то рокировка невозможна
			else kingb = 1;
			
			thatSpace->setSpace(thisKing);
			thisKing->setEmpty();
			return true;
		}
		else return false;
	else return false;
}
	bool Board::moveQueen(Square* thisQueen, Square* thatSpace)  //ход ферзя
	{


	int queenX = thisQueen->getX();
	int queenY = thisQueen->getY();
	int thatX = thatSpace->getX();
	int thatY = thatSpace->getY();
	cout << "this";
	int yIncrement;
	int xIncrement;

	bool invalid = false;
	if (queenX != thatX || queenY != thatY)
	{

		if (queenX == thatX)
		{
			yIncrement = (thatY - queenY) / (abs(thatY - queenY));
			for (int i = queenY + yIncrement; i != thatY; i += yIncrement)
			{

				if (square[thatX][i].getColor() != NONE)
					return false;

			}
		}
		else
			if (queenY == thatY)
			{

				xIncrement = (thatX - queenX) / (abs(thatX - queenX));
				for (int i = queenX + xIncrement; i != thatX; i += xIncrement)
				{
					if (square[i][thatY].getColor() != NONE)
						return false;
				}
			}
			else
				if (abs(queenX - thatX) == abs(queenY - thatY))
				{
					xIncrement = (thatX - queenX) / (abs(thatX - queenX));
					yIncrement = (thatY - queenY) / (abs(thatY - queenY));

					for (int i = 1; i < abs(queenX - thatX); i++)
					{
						cout << "Вы не можете сюда походить";
						if (square[queenX + xIncrement * i][queenY + yIncrement * i].getColor() != NONE)
							return false;

					}
				}
				else
					return false;
	}



	if (invalid == false)
	{
		thatSpace->setSpace(thisQueen);
		thisQueen->setEmpty();
		return true;
	}
	else
	{
		return false;
	}
}

bool Board::moveBishop(Square* thisBishop, Square* thatSpace) //ход слона
{ 
	int bishopX = thisBishop->getX();
	int bishopY = thisBishop->getY();
	int thatX = thatSpace->getX();
	int thatY = thatSpace->getY();
	bool invalid = false;
	Square* s;
	if (abs(bishopX - thatX) == abs(bishopY - thatY))
	{
		int xIncrement = (thatX - bishopX) / (abs(thatX - bishopX));
		int yIncrement = (thatY - bishopY) / (abs(thatY - bishopY));

		for (int i = 1; i < abs(bishopX - thatX); i++)
		{
			cout << "Не можете сюда походить";
			if (square[bishopX + xIncrement * i][bishopY + yIncrement * i].getColor() != NONE)
				return false;

		}
	}
	else
		return false;

	if (invalid == false)
	{
		thatSpace->setSpace(thisBishop);
		thisBishop->setEmpty();
		return true;
	}
	else
	{
		return false;
	}
}
bool Board::moveKnight(Square* thisKnight, Square* thatSpace) //ход коня
{

	int knightX = thisKnight->getX();
	int knightY = thisKnight->getY();
	int thatX = thatSpace->getX();
	int thatY = thatSpace->getY();

	if ((abs(knightX - thatX) == 2 && abs(knightY - thatY) == 1) || (abs(knightX - thatX) == 1 && abs(knightY - thatY) == 2))
	{
		thatSpace->setSpace(thisKnight);
		thisKnight->setEmpty();
		return true;
	}
	else
	{
		return false;
	}
}

bool Board::moveRook(Square* thisRook, Square* thatSpace) //ход ладьи
{

	int rookX = thisRook->getX();
	int rookY = thisRook->getY();
	int thatX = thatSpace->getX();
	int thatY = thatSpace->getY();
	bool invalid = false;
	if (rookX != thatX || rookY != thatY)
	{
		if (rookX == 7 && rookY == 0) rookw2 = 1;
		if (rookX == 0 && rookY == 0) rookw1 = 1;
		if (rookX == 0 && rookY == 7) rookb1 = 1;
		if (rookX == 7 && rookY == 7) rookb2 = 1;

		if (rookX == thatX)
		{
			int yIncrement = (thatY - rookY) / (abs(thatY - rookY));
			for (int i = rookY + yIncrement; i != thatY; i += yIncrement)
			{

				if (square[thatX][i].getColor() != NONE)
					return false;

			}
		}
		else
			if (rookY == thatY)
			{

				int xIncrement = (thatX - rookX) / (abs(thatX - rookX));
				for (int i = rookX + xIncrement; i != thatX; i += xIncrement)
				{
					if (square[i][thatY].getColor() != NONE)
						return false;
				}
			}
			
		
			
			else
				return false;
	}
	if (invalid == false)
	{
		thatSpace->setSpace(thisRook);
		thisRook->setEmpty();
		return true;
	}
	else
	{
		cout << "Нельзя так ходить";
		return false;
	}
}

bool Board::movePawn(Square* thisPawn, Square* thatSpace) //ход пешки
{
	
	using namespace std;
	bool invalid = false;
	int pawnX = thisPawn->getX();
	int pawnY = thisPawn->getY();
	int thatX = thatSpace->getX();
	int thatY = thatSpace->getY();



	if (thisPawn->getColor() == WHITE)
	{
		
		if (thatY == 7) //если белые достигли конца поля черных и замена фигуры
		{
			
			int choice;
			cout << "1 - Заменить пешку на Ферзя" << endl;
			cout << "2 - Заменить пешку на Коня" << endl;
			cout << "3 - Заменить пешку на Ладью" << endl;
			cout << "4 - Заменить пешку на Слона" << endl;
			Again:
			cin >> choice;

			if (choice > 4 || choice < 1) {cout << "Не правильный ввод. Введите правильно!" << endl; goto Again;}
			
				switch (choice)
			{
			case 1: 
				thatSpace->setSpace(thisPawn);
				thisPawn->setEmpty();
				square[thatX][thatY].setPieceAndColor(QUEEN, WHITE); break;
			case 2:
				thatSpace->setSpace(thisPawn);
				thisPawn->setEmpty();
				square[thatX][thatY].setPieceAndColor(KNIGHT, WHITE); break;
			case 3:
				thatSpace->setSpace(thisPawn);
				thisPawn->setEmpty();
				square[thatX][thatY].setPieceAndColor(ROOK, WHITE); break;
			case 4:
				thatSpace->setSpace(thisPawn);
				thisPawn->setEmpty();
				square[thatX][thatY].setPieceAndColor(BISHOP, WHITE); break;
			}
		
		}
		
		else if (pawnY == 1) //первых ход доступно на 2 клетки
		{
			if (pawnX == thatX && (thatY == pawnY + 1 || thatY == pawnY + 2) && thatSpace->getColor() == NONE)
			{
				thatSpace->setSpace(thisPawn);
				thisPawn->setEmpty();
				
				
				return true;
			}
			else
				if ((pawnX + 1 == thatX || pawnX - 1 == thatX) && pawnY + 1 == thatY && thatSpace->getColor() == BLACK)
				{
					thatSpace->setSpace(thisPawn);
					thisPawn->setEmpty();
					
					return true;
				}
				else
					return false;
		}

		else if (pawnY != 1)
		{
			if (pawnX == thatX && thatY == pawnY + 1 && thatSpace->getColor() == NONE)
			{
				thatSpace->setSpace(thisPawn);
				thisPawn->setEmpty();
				return true;
			}
			else
				if ((pawnX + 1 == thatX || pawnX - 1 == thatX) && pawnY + 1 == thatY && thatSpace->getColor() == BLACK)
				{
					thatSpace->setSpace(thisPawn);
					thisPawn->setEmpty();
					return true;
				}
				else
					return false;

			}
		}
	
	else
		
		if (thisPawn->getColor() == BLACK)
		{
			if (thatY == 0) //если черные достигли конца поля белых и замена фигуры
			{

				int choice1;
				cout << "1 - Заменить пешку на Ферзя" << endl;
				cout << "2 - Заменить пешку на Коня" << endl;
				cout << "3 - Заменить пешку на Ладью" << endl;
				cout << "4 - Заменить пешку на Слона" << endl;
			Again2:
				cin >> choice1;

				if (choice1 > 4 || choice1 < 1) { cout << "Не правильный ввод. Введите правильно!" << endl; goto Again2; }

				switch (choice1)
				{
				case 1:
					thatSpace->setSpace(thisPawn);
					thisPawn->setEmpty();
					square[thatX][thatY].setPieceAndColor(QUEEN, BLACK); break;
				case 2:
					thatSpace->setSpace(thisPawn);
					thisPawn->setEmpty();
					square[thatX][thatY].setPieceAndColor(KNIGHT, BLACK); break;
				case 3:
					thatSpace->setSpace(thisPawn);
					thisPawn->setEmpty();
					square[thatX][thatY].setPieceAndColor(ROOK, BLACK); break;
				case 4:
					thatSpace->setSpace(thisPawn);
					thisPawn->setEmpty();
					square[thatX][thatY].setPieceAndColor(BISHOP, BLACK); break;
				}
			}
			
			else if (pawnY == 6) //первый ход доступно на две клетки
			{
				if (pawnX == thatX && (thatY == pawnY - 1 || thatY == pawnY - 2) && thatSpace->getColor() == NONE)
				{
					thatSpace->setSpace(thisPawn);
					thisPawn->setEmpty();
					return true;
				}
				else
					if ((pawnX + 1 == thatX || pawnX - 1 == thatX) && pawnY - 1 == thatY && thatSpace->getColor() == WHITE)
					{
						thatSpace->setSpace(thisPawn);
						thisPawn->setEmpty();
						return true;
					}
					else
						return false;
			}

			else if (pawnY != 6)
			{
				if (pawnX == thatX && thatY == pawnY - 1 && thatSpace->getColor() == NONE)
				{
					thatSpace->setSpace(thisPawn);
					thisPawn->setEmpty();
					return true;
				}
				else
					if ((pawnX + 1 == thatX || pawnX - 1 == thatX) && pawnY - 1 == thatY && thatSpace->getColor() == WHITE)
					{
						thatSpace->setSpace(thisPawn);
						thisPawn->setEmpty();
						return true;
					}
					else
						return false;
			}
		}
		
		else
			return false;
}
bool Board::makeMove(int x1, int y1, int x2, int y2) //провера хода
{

	using namespace std;
	if (x1 < 0 || x1>7 || y1 < 0 || y1>7 || x2 < 0 || x2>7 || y2 < 0 || y2>8)
	{
		cout << "Не правильные координаты." << endl;
		return false;
	}
	Square* src = getSquare(x1, y1);
	Square* dest = getSquare(x2, y2);

	if (src->getColor() == dest->getColor() && dest->getColor() != NONE)
	{
		cout << "Неверный ход." << endl;
		return false;
	}

	switch (src->getPiece())
	{
	case KING: return moveKing(src, dest);
		break;
	case QUEEN: return moveQueen(src, dest);
		break;
	case BISHOP: return moveBishop(src, dest);
		break;
	case KNIGHT: return moveKnight(src, dest);
		break;
	case ROOK: return moveRook(src, dest);
		break;
	case PAWN: return movePawn(src, dest);
		break;
	case EMPTY: cout << "Вы не можете сюда походить" << endl;  return false;
		break;
	default: cout << "Что-то пошло не так" << endl;
		break;
	}
	return false;
}
