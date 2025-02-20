#include "Gameplay.h"
#include <iostream>

Gameplay::Gameplay()
{
}

Gameplay::~Gameplay()
{
}



bool Gameplay::IsMoveCommandValid(String moveCommand)
{
	//example command: move d2 d4 
	if (moveCommand.getLenght() != MAX_MOVE_COMMAND_LENGHT) {
		std::cout << "Invalid move format!" << std::endl;
		return false;
	}
	else if (moveCommand[0] != 'm' || moveCommand[1] != 'o' || moveCommand[2] != 'v' || moveCommand[3] != 'e' || moveCommand[4] != ' ' || moveCommand[7] != ' ') {
		std::cout << "Invalid move format!" << std::endl;
		return false;
	}
	else if (moveCommand[5] < 'a' || moveCommand[5] > 'h' || moveCommand[6] < '1' || moveCommand[6] > '8' || moveCommand[8] < 'a' || moveCommand[8] > 'h' || moveCommand[9] < '1' || moveCommand[9] > '8') {
		std::cout << "Invalid move format!" << std::endl;
		return false;
	}
	return true;
}

int Gameplay::GetCoordinate(String moveCommand, int index)
{
	if (index == 5 || index == 8)
		return GetLetterCoordinate(moveCommand, index);
	else
		return GetNumberCoordinate(moveCommand, index);
}

int Gameplay::GetLetterCoordinate(String moveCommand, int index)
{
	if (moveCommand[index] == 'a')
		return 0;
	else if (moveCommand[index] == 'b')
		return 1;
	else if (moveCommand[index] == 'c')
		return 2;
	else if (moveCommand[index] == 'd')
		return 3;
	else if (moveCommand[index] == 'e')
		return 4;
	else if (moveCommand[index] == 'f')
		return 5;
	else if (moveCommand[index] == 'g')
		return 6;
	else
		return 7;
}

int Gameplay::GetNumberCoordinate(String moveCommand, int index)
{
	if (moveCommand[index] == '1')
		return 0;
	else if (moveCommand[index] == '2')
		return 1;
	else if (moveCommand[index] == '3')
		return 2;
	else if (moveCommand[index] == '4')
		return 3;
	else if (moveCommand[index] == '5')
		return 4;
	else if (moveCommand[index] == '6')
		return 5;
	else if (moveCommand[index] == '7')
		return 6;
	else
		return 7;
}

bool Gameplay::IsStartPositionEmpty(Square board[BOARD_SIZE][BOARD_SIZE], int row, int col)
{
	if (board[row][col].piece == nullptr) {
		std::cout << "There's no piece at that location." << std::endl << std::endl;
		return true;
	}
	else {
		return false;
	}
}

bool Gameplay::IsPieceBelongsToCurrentPlayer(Square board[BOARD_SIZE][BOARD_SIZE], int row, int col, int currentPlayer)
{
	if (board[row][col].piece->getPlayer() != currentPlayer) {
		std::cout << "That's not your piece!" << std::endl << std::endl;
		return false;
	}
	else {
		return true;
	}
}

bool Gameplay::IsEndPositionOccupiedByCurrentPlayerPiece(Square board[BOARD_SIZE][BOARD_SIZE], int row, int col, int currentPlayer)
{
	if (board[row][col].piece != nullptr && board[row][col].piece->getPlayer() == currentPlayer) {
		std::cout << "You already have a piece there." << std::endl << std::endl;
		return true;
	}
	else {
		return false;
	}
}

bool Gameplay::IsPawn(Square board[BOARD_SIZE][BOARD_SIZE], int row, int col)
{
	if (board[row][col].piece->getName() == "Pawn") {
		return true;
	}
	else {
		return false;
	}
}

bool Gameplay::IsPawnMoveValid(Square board[BOARD_SIZE][BOARD_SIZE], int startPositionNumber, int startPositionLetter, int endPositionNumber, int endPositionLetter, int currentPlayer, int rowDifference, int columnDifference)
{
	if (((currentPlayer == BLACK_PLAYER && startPositionNumber != 1) ||
		(currentPlayer == WHITE_PLAYER && startPositionNumber != 6)) && 
		rowDifference <= -2) {
		std::cout << "Pawns can move 2 squares forward only in their first move" << std::endl;
		return false;
	}
	else if (((currentPlayer == BLACK_PLAYER && startPositionNumber != 1) ||
		(currentPlayer == WHITE_PLAYER && startPositionNumber != 6))
		&& rowDifference < -2) {
		std::cout << "Pawns can't move more than 2 squares forward their first move." << std::endl;
		return false;
	}
	else if (rowDifference >= 0) {
		std::cout << "Pawns can only move forward" << std::endl;
		return false;
	}
	else if (abs(columnDifference) > 1) {

		std::cout << "Pawns can't move more than one column forward" << std::endl;
		return false;
	}
	else if (abs(columnDifference) == 1 && rowDifference == -1 && board[endPositionNumber][endPositionLetter].piece == nullptr) {

		std::cout << "There must be an enemy piece on that position for you to move there." << std::endl;;
		return false;
	}
	else if (rowDifference == -1 && columnDifference == 0 && board[endPositionNumber][endPositionLetter].piece != nullptr && board[endPositionNumber][endPositionLetter].piece->getPlayer() == 1) {
		std::cout << "An enemy piece is blocking your move!" << std::endl;
		return false;
	}
	else 
		return true;
}

void Gameplay::MakeMove(Square board[BOARD_SIZE][BOARD_SIZE], int startPositionNumber, int startPositionLetter, int endPositionNumber, int endPositionLetter, int currentPlayer, int rowDifference, int columnDifference)
{
	if (rowDifference == -1 && abs(columnDifference) == 1 && board[endPositionNumber][endPositionLetter].piece->getPlayer() == 1) {
		std::cout << "You have taken the enemy's " << board[endPositionNumber][endPositionLetter].piece->getName() << "!" << std::endl;
		if (board[endPositionNumber][endPositionLetter].piece->getName() == "King") {
			isKingDead = true;
		}
		board[endPositionNumber][endPositionLetter].piece = board[startPositionNumber][startPositionLetter].piece;
		board[startPositionNumber][startPositionLetter].piece = nullptr;
	}
	else {
		std::cout << "Move successful!" << std::endl;
		board[endPositionNumber][endPositionLetter].piece = board[startPositionNumber][startPositionLetter].piece;
		board[startPositionNumber][startPositionLetter].piece = nullptr;
	}
}

bool Gameplay::IsKing(Square board[BOARD_SIZE][BOARD_SIZE], int row, int col)
{
	if (board[row][col].piece->getName() == "King") {
		return true;
	}
	else {
		return false;
	}
}

bool Gameplay::IsKingMoveValid(Square board[BOARD_SIZE][BOARD_SIZE], int startPositionNumber, int startPositionLetter, int endPositionNumber, int endPositionLetter, int currentPlayer, int rowDifference, int columnDifference)
{
	if (abs(rowDifference) > 1 || abs(columnDifference) > 1) {
		std::cout << "Kings may only move one square" << std::endl;
		return false;
	}
	else 
		return true;
}

bool Gameplay::IsQueen(Square board[BOARD_SIZE][BOARD_SIZE], int row, int col)
{
	if (board[row][col].piece->getName() == "Queen") {
		return true;
	}
	else {
		return false;
	}
}

bool Gameplay::IsQueenMoveValid(Square board[BOARD_SIZE][BOARD_SIZE], int startPositionNumber, int startPositionLetter, int endPositionNumber, int endPositionLetter, int currentPlayer, int rowDifference, int columnDifference)
{
	if (abs(rowDifference) != abs(columnDifference) && rowDifference != 0 && columnDifference != 0) {
		std::cout << "Queens can move like rooks and bishops only" << std::endl;
		return false;
	}
	if (rowDifference > 0 && columnDifference > 0) {
		for (int i = startPositionNumber - 1; i > endPositionNumber; i--) {
			int a = startPositionLetter;
			for (a; a > endPositionLetter; a--) {
				a--;
				if (board[i][a].piece != nullptr) {
					std::cout << "There's a piece blocking your move!" << std::endl;
					return false;
				}
				break;
			}
		}
	}
	else if (rowDifference < 0 && columnDifference < 0) {
		int a = startPositionLetter;
		for (int i = startPositionNumber + 1; i < endPositionNumber; i++) {
			for (a; a < endPositionLetter; a++) {
				a++;
				if (board[i][a].piece != nullptr) {
					std::cout << "There's a piece blocking your move!" << std::endl;
					return false;
				}
				break;
			}
		}
	}
	else if (rowDifference > 0 && columnDifference < 0) {
		int a = startPositionLetter;
		for (int i = startPositionNumber - 1; i > endPositionNumber; i--) {
			a++;
			for (a; a < endPositionLetter; a++) {
				if (board[i][a].piece != nullptr) {
					std::cout << "There's a piece blocking your move!" << std::endl;
					return false;
				}
				break;
			}
		}
	}
	else if (rowDifference < 0 && columnDifference > 0) {
		int a = startPositionNumber;
		for (int i = startPositionNumber + 1; i < endPositionNumber; i++) {
			for (a; a > endPositionLetter; a--) {
				a--;
				if (board[i][a].piece != nullptr) {
					std::cout << "There's a piece blocking your move!" << std::endl;
					return false;
				}
			}
		}
	}
	else if (rowDifference == 0 && columnDifference > 0) {
		for (int i = startPositionLetter - 1; i >= endPositionLetter; i--) {
			if (board[startPositionNumber][i].piece != nullptr) {
				std::cout << "There's a piece blocking your move!" << std::endl;
				return false;
			}
		}
	}
	else if (rowDifference == 0 && columnDifference < 0) {
		for (int i = startPositionLetter + 1; i < endPositionLetter; i++) {
			if (board[startPositionNumber][i].piece != nullptr) {
				std::cout << "There's a piece blocking your move!" << std::endl;
				return false;
			}
		}
	}
	else if (rowDifference > 0 && columnDifference == 0) {
		for (int i = startPositionNumber - 1; i > endPositionNumber; i--) {
			if (board[i][startPositionLetter].piece != nullptr) {
				std::cout << "There's a piece blocking your move!" << std::endl;
				return false;
			}
		}
	}
	else if (rowDifference < 0 && columnDifference == 0) {
		for (int i = startPositionNumber + 1; i < endPositionNumber; i++) {
			if (board[i][startPositionLetter].piece != nullptr) {
				std::cout << "There's a piece blocking your move!" << std::endl;
				return false;
			}
		}
	}
}

bool Gameplay::IsKnight(Square board[BOARD_SIZE][BOARD_SIZE], int row, int col)
{
	if (board[row][col].piece->getName() == "Knight") {
		return true;
	}
	else {
		return false;
	}
}

bool Gameplay::IsKnightMoveValid(Square board[BOARD_SIZE][BOARD_SIZE], int startPositionNumber, int startPositionLetter, int endPositionNumber, int endPositionLetter, int currentPlayer, int rowDifference, int columnDifference)
{
	if (abs(rowDifference) * abs(columnDifference) != 2) {
		std::cout << "Knights can move only L-shape" << std::endl;
		return false;
	}
	else
		return true;
}

bool Gameplay::IsBishop(Square board[BOARD_SIZE][BOARD_SIZE], int row, int col)
{
	if (board[row][col].piece->getName() == "Bishop") {
		return true;
	}
	else {
		return false;
	}
}

bool Gameplay::IsBishopMoveValid(Square board[BOARD_SIZE][BOARD_SIZE], int startPositionNumber, int startPositionLetter, int endPositionNumber, int endPositionLetter, int currentPlayer, int rowDifference, int columnDifference)
{
	if (abs(rowDifference) != abs(columnDifference)) {
		std::cout << "Bishops can move only diagonally" << std::endl;
		return false;
	}
	if (rowDifference > 0 && columnDifference > 0) {
		int a = startPositionLetter;
		for (int i = startPositionNumber - 1; i > endPositionNumber; i--) {
			for (a; a > endPositionLetter; a--) {
				a--;
				if (board[i][a].piece != nullptr) {
					std::cout << "There's a piece blocking your move!" << std::endl;
					return false;
				}
				break;
			}
		}
	}
	else if (rowDifference < 0 && columnDifference < 0) {
		int a = startPositionLetter;
		for (int i = startPositionNumber + 1; i < endPositionNumber; i++) {
			for (a; a < endPositionLetter; a++) {
				a++;
				if (board[i][a].piece != nullptr) {
					std::cout << "There's a piece blocking your move!" << std::endl;
					return false;
				}
				break;
			}
		}
	}
	else if (rowDifference > 0 && columnDifference < 0) {
		int a = startPositionLetter;
		for (int i = startPositionNumber - 1; i > endPositionNumber; i--) {
			for (a; a < endPositionLetter; a++) {
				a++;
				if (board[i][a].piece != nullptr) {
					std::cout << "There's a piece blocking your move!" << std::endl;
					return false;
				}
				break;
			}
		}
	}
	else if (rowDifference < 0 && columnDifference > 0) {
		int a = startPositionLetter;
		for (int i = startPositionNumber + 1; i < endPositionNumber; i++) {
			for (a; a > endPositionLetter; a--) {
				a--;
				if (board[i][a].piece != nullptr) {
					std::cout << "There's a piece blocking your move!" << std::endl;
					return false;
				}
				break;
			}
		}
	}
	else
		return true;
}

bool Gameplay::IsRook(Square board[BOARD_SIZE][BOARD_SIZE], int row, int col)
{
	if (board[row][col].piece->getName() == "Rook") {
		return true;
	}
	else {
		return false;
	}
}

bool Gameplay::IsRookMoveValid(Square board[BOARD_SIZE][BOARD_SIZE], int startPositionNumber, int startPositionLetter, int endPositionNumber, int endPositionLetter, int currentPlayer, int rowDifference, int columnDifference)
{
	if (rowDifference != 0 && columnDifference != 0) {
		std::cout << "Rooks can move only horizontal or vertical" << std::endl;
		return false;
	}
	if (rowDifference == 0 && columnDifference > 0) {
		for (int i = startPositionLetter - 1; i > endPositionLetter; i--) {
			if (board[startPositionNumber][i].piece != nullptr) {
				std::cout << "There's a piece blocking your move!" << std::endl;
				return false;
			}
		}
	}
	else if (rowDifference == 0 && columnDifference < 0) {
		for (int i = startPositionLetter + 1; i < endPositionLetter; i++) {
			if (board[startPositionNumber][i].piece != nullptr) {
				std::cout << "There's a piece blocking your move!" << std::endl;
				return false;
			}
		}
	}
	else if (rowDifference > 0 && columnDifference == 0) {
		for (int i = startPositionNumber - 1; i > endPositionNumber; i--) {
			if (board[i][startPositionLetter].piece != nullptr) {
				std::cout << "There's a piece blocking your move!" << std::endl;
				return false;
			}
		}
	}
	else if (rowDifference < 0 && columnDifference == 0) {
		for (int i = startPositionNumber + 1; i < endPositionNumber; i++) {
			if (board[i][startPositionLetter].piece != nullptr) {
				std::cout << "There's a piece blocking your move!" << std::endl;
				return false;
			}
		}
	}
	else
		return true;
}




bool Gameplay::IsMovePossible(String moveCommand, Square board[BOARD_SIZE][BOARD_SIZE], int currentPlayer) {

	int startPositionLetter = GetCoordinate(moveCommand, START_LETTER_INDEX_IN_COMMAND);
	int startPositionNumber = GetCoordinate(moveCommand, START_NUMBER_INDEX_IN_COMMAND);
	int endPositionLetter = GetCoordinate(moveCommand, END_LETTER_INDEX_IN_COMMAND);
	int endPositionNumber = GetCoordinate(moveCommand, END_NUMBER_INDEX_IN_COMMAND);

	if(IsStartPositionEmpty(board, startPositionNumber, startPositionLetter)) return false;
	if(!IsPieceBelongsToCurrentPlayer(board, startPositionNumber, startPositionLetter, currentPlayer)) return false;
	if(IsEndPositionOccupiedByCurrentPlayerPiece(board, endPositionNumber, endPositionLetter, currentPlayer)) return false;
		
	int rowDifference = startPositionNumber - endPositionNumber;
	int columnDifference = startPositionLetter - endPositionLetter;

	if (IsPawn(board, startPositionNumber, startPositionLetter))
	{
		if(!IsPawnMoveValid(board, startPositionNumber, startPositionLetter, endPositionNumber, endPositionLetter, currentPlayer, rowDifference, columnDifference)) 
			return false;
		else
		{
			MakeMove(board, startPositionNumber, startPositionLetter, endPositionNumber, endPositionLetter, currentPlayer, rowDifference, columnDifference);
			return true;
		}
	}
	else if (IsKing(board, startPositionNumber, startPositionLetter))
	{
		if (!IsKingMoveValid(board, startPositionNumber, startPositionLetter, endPositionNumber, endPositionLetter, currentPlayer, rowDifference, columnDifference))
			return false;
		else
		{
			MakeMove(board, startPositionNumber, startPositionLetter, endPositionNumber, endPositionLetter, currentPlayer, rowDifference, columnDifference);
			return true;
		}
	}
	else if (IsQueen(board, startPositionNumber, startPositionLetter))
	{
		if (!IsQueenMoveValid(board, startPositionNumber, startPositionLetter, endPositionNumber, endPositionLetter, currentPlayer, rowDifference, columnDifference))
			return false;
		else
		{
			MakeMove(board, startPositionNumber, startPositionLetter, endPositionNumber, endPositionLetter, currentPlayer, rowDifference, columnDifference);
			return true;
		}
	}
	else if (IsKnight(board, startPositionNumber, startPositionLetter))
	{
		if (!IsKnightMoveValid(board, startPositionNumber, startPositionLetter, endPositionNumber, endPositionLetter, currentPlayer, rowDifference, columnDifference))
			return false;
		else
		{
			MakeMove(board, startPositionNumber, startPositionLetter, endPositionNumber, endPositionLetter, currentPlayer, rowDifference, columnDifference);
			return true;
		}
	}
	else if (IsBishop(board, startPositionNumber, startPositionLetter))
	{
		if (!IsBishopMoveValid(board, startPositionNumber, startPositionLetter, endPositionNumber, endPositionLetter, currentPlayer, rowDifference, columnDifference))
			return false;
		else
		{
			MakeMove(board, startPositionNumber, startPositionLetter, endPositionNumber, endPositionLetter, currentPlayer, rowDifference, columnDifference);
			return true;
		}
	}
	else if (IsRook(board, startPositionNumber, startPositionLetter))
	{
		if (!IsRookMoveValid(board, startPositionNumber, startPositionLetter, endPositionNumber, endPositionLetter, currentPlayer, rowDifference, columnDifference))
			return false;
		else
		{
			MakeMove(board, startPositionNumber, startPositionLetter, endPositionNumber, endPositionLetter, currentPlayer, rowDifference, columnDifference);
			return true;
		}
	}
	else 
	{
		return false;
	}
}
/*
void Gameplay::undo(String move,Board board[8][8]) {
	
}
*/

void Gameplay::FillBoard()
{ 
	for (int i = 0; i < 28; i++){
		for (int j = 0; j < 65; j++){
			gameVisualization[i][j] = ' ';
		}
	}
}
void Gameplay::PaintBoard()
{
	for (int i = 3; i < 27; i++){
		for (int j = 7; j < 63; j++){
			if ((((i > 2 && i < 6) || (i > 8 && i < 12) || (i > 14 && i < 18) || (i > 20 && i < 24))
				&& ((j > 6 && j < 14) || (j > 20 && j < 28) || (j > 34 && j < 42) || (j > 48 && j < 56))) ||
				(((i > 5 && i < 9) || (i > 11 && i < 15) || (i > 17 && i < 21) || (i > 23 && i < 27))
					&& ((j > 13 && j < 21) || (j > 27 && j < 35) || (j > 41 && j < 49) || (j > 55 && j < 63))))
				gameVisualization[i][j] = 219;
		}
	}
}
void Gameplay::PrintBorders() {
	for (int i = 3; i < 27; i++){
		gameVisualization[i][5] = 186;
		gameVisualization[i][64] = 186;
	}
	gameVisualization[2][5] = 201;
	gameVisualization[2][64] = 187;
	gameVisualization[27][64] = 188;
	gameVisualization[27][5] = 200;
	for (int j = 6; j < 64; j++){
		gameVisualization[2][j] = 205;
		gameVisualization[27][j] = 205;
	}
}
void Gameplay::PrintNumbering()
{
	int k = 0;

	//column nameing
	for (int j = 10; j < 63; j += 7){
		gameVisualization[1][j] = 65 + k;
		k++;

	}
	//line numbering
	for (int i = 4; i < 27; i += 3){{
			gameVisualization[i][3] = 41 + k;
			k++;
		}
	}
}
void Gameplay::FigureSpaceCleaning()
{
	//freeing space for figures
	for (int i = 4; i < 27; i += 3){
		for (int j = 10; j < 63; j += 7){
			gameVisualization[i][j - 1] = '  ';
			gameVisualization[i][j] = '  ';
			gameVisualization[i][j + 1] = '  ';
		}
	}
}

int Gameplay::GetRowCoordinateForVisualization(int row)
{
	if (row == 0) {
		return ROW_1_COORDINATE_VISUALIZATION;
	}
	else if (row == 1) {
		return ROW_2_COORDINATE_VISUALIZATION;
	}
	else if (row == 2) {
		return ROW_3_COORDINATE_VISUALIZATION;
	}
	else if (row == 3) {
		return ROW_4_COORDINATE_VISUALIZATION;
	}
	else if (row == 4) {
		return ROW_5_COORDINATE_VISUALIZATION;
	}
	else if (row == 5) {
		return ROW_6_COORDINATE_VISUALIZATION;
	}
	else if (row == 6) {
		return ROW_7_COORDINATE_VISUALIZATION;
	}
	else if (row == 7) {
		return ROW_8_COORDINATE_VISUALIZATION;
	}
}

int Gameplay::GetColCoordinateForVisualization(int col)
{
	if (col == 0) {
		return COL_1_COORDINATE_VISUALIZATION;
	}
	else if (col == 1) {
		return COL_2_COORDINATE_VISUALIZATION;
	}
	else if (col == 2) {
		return COL_3_COORDINATE_VISUALIZATION;
	}
	else if (col == 3) {
		return COL_4_COORDINATE_VISUALIZATION;
	}
	else if (col == 4) {
		return COL_5_COORDINATE_VISUALIZATION;
	}
	else if (col == 5) {
		return COL_6_COORDINATE_VISUALIZATION;
	}
	else if (col == 6) {
		return COL_7_COORDINATE_VISUALIZATION;
	}
	else if (col == 7) {
		return COL_8_COORDINATE_VISUALIZATION;
	}
}


void Gameplay::VisualizePiece(Square board[BOARD_SIZE][BOARD_SIZE], int row, int col, int rowCoordinate, int colCoordinate)
{
	if (board[row][col].piece == nullptr) {
		gameVisualization[rowCoordinate][colCoordinate] = ' ';
	}
	else if (board[row][col].piece->getName() == "Pawn" && board[row][col].piece->getPlayer() == 1) {
		gameVisualization[rowCoordinate][colCoordinate] = 'P';
	}
	else if (board[row][col].piece->getName() == "King" && board[row][col].piece->getPlayer() == 1) {
		gameVisualization[rowCoordinate][colCoordinate] = 'K';
	}
	else if (board[row][col].piece->getName() == "Queen" && board[row][col].piece->getPlayer() == 1) {
		gameVisualization[rowCoordinate][colCoordinate] = 'Q';
	}
	else if (board[row][col].piece->getName() == "Rook" && board[row][col].piece->getPlayer() == 1) {
		gameVisualization[rowCoordinate][colCoordinate] = 'R';
	}
	else if (board[row][col].piece->getName() == "Knight" && board[row][col].piece->getPlayer() == 1) {
		gameVisualization[rowCoordinate][colCoordinate] = 'N';
	}
	else if (board[row][col].piece->getName() == "Bishop" && board[row][col].piece->getPlayer() == 1) {
		gameVisualization[rowCoordinate][colCoordinate] = 'B';
	}
	else if (board[row][col].piece->getName() == "Pawn" && board[row][col].piece->getPlayer() == 2) {
		gameVisualization[rowCoordinate][colCoordinate] = 'p';
	}
	else if (board[row][col].piece->getName() == "King" && board[row][col].piece->getPlayer() == 2) {
		gameVisualization[rowCoordinate][colCoordinate] = 'k';
	}
	else if (board[row][col].piece->getName() == "Queen" && board[row][col].piece->getPlayer() == 2) {
		gameVisualization[rowCoordinate][colCoordinate] = 'q';
	}
	else if (board[row][col].piece->getName() == "Rook" && board[row][col].piece->getPlayer() == 2) {
		gameVisualization[rowCoordinate][colCoordinate] = 'r';
	}
	else if (board[row][col].piece->getName() == "Knight" && board[row][col].piece->getPlayer() == 2) {
		gameVisualization[rowCoordinate][colCoordinate] = 'n';
	}
	else if (board[row][col].piece->getName() == "Bishop" && board[row][col].piece->getPlayer() == 2) {
		gameVisualization[rowCoordinate][colCoordinate] = 'b';
	}
}

void Gameplay::PlacePieces(Square board[8][8])
{
	int rowCoordinate, colCoordinate;

	for (int i = 0; i < 8; i++){
		rowCoordinate = GetRowCoordinateForVisualization(i);
		for (int j = 0; j < 8; j++){
			colCoordinate = GetColCoordinateForVisualization(j);
			VisualizePiece(board, i, j, rowCoordinate, colCoordinate);
		}
	}
	//printing the board
	for (int i = 0; i < 28; i++){
		for (int j = 0; j < 65; j++){
			std::cout << gameVisualization[i][j];
		}
		std::cout << std::endl;
	}
}
void Gameplay::PrintBoard(Square board[8][8])
{
	FillBoard();
	PrintNumbering();
	PaintBoard();
	FigureSpaceCleaning();
	PrintBorders();
	PlacePieces(board);
}

void Gameplay::PrintStartTurnMessage(int currentPlayer)
{
	std::cout << std::endl;
	std::cout << "It is Player " << currentPlayer << " turn. Please enter your command:" << std::endl;
}

void Gameplay::ExecutePlayerCommand(int currentPlayer)
{
	String command;
	std::cin >> command;

	if (command == HELP) {
		std::cout << "-----------------Help menu-----------------" << std::endl;
		std::cout << "Possible commands: " << std::endl;
		std::cout << "undo -> returns the game to the state before the last move." << std::endl;
		std::cout << "exit -> exits the game." << std::endl;
		std::cout << "move x1y1 x2y2 -> if possible, move the figure from position (x1, y1) to position (x2, y2)" << std::endl;
		std::cout << "example move command ---> move d2 d4" << std::endl;
		if (currentPlayer == WHITE_PLAYER) {
			currentPlayer = BLACK_PLAYER;
		}
		else {
			currentPlayer = WHITE_PLAYER;
		}
	}
	else if (command == UNDO) {

	}
	else {
		while (!(IsMoveCommandValid(command)))
		{
			std::cin >> command;
		}
		while (!(IsMovePossible(command, board, currentPlayer)) || (!(IsMoveCommandValid(command))))
		{
			std::cout << "Please enter your move again!" << std::endl;
			std::cin >> command;
		}
	}
	if (isKingDead) {
		std::cout << "Player " << currentPlayer << " wins!" << std::endl;
	}
}

void Gameplay::PlayGame()
{
	Pawn whitePawn1("Pawn", 1);
	Pawn whitePawn2("Pawn", 1);
	Pawn whitePawn3("Pawn", 1);
	Pawn whitePawn4("Pawn", 1);
	Pawn whitePawn5("Pawn", 1);
	Pawn whitePawn6("Pawn", 1);
	Pawn whitePawn7("Pawn", 1);
	Pawn whitePawn8("Pawn", 1);
	Rook whiteRook1("Rook", 1);
	Rook whiteRook2("Rook", 1);
	Knight whiteKnight1("Knight", 1);
	Knight whiteKnight2("Knight", 1);
	Bishop whiteBishop1("Bishop", 1);
	Bishop whiteBishop2("Bishop", 1);
	Queen whiteQueen("Queen", 1);
	King whiteKing("King", 1);

	Pawn blackPawn1("Pawn", 2);
	Pawn blackPawn2("Pawn", 2);
	Pawn blackPawn3("Pawn", 2);
	Pawn blackPawn4("Pawn", 2);
	Pawn blackPawn5("Pawn", 2);
	Pawn blackPawn6("Pawn", 2);
	Pawn blackPawn7("Pawn", 2);
	Pawn blackPawn8("Pawn", 2);
	Rook blackRook1("Rook", 2);
	Rook blackRook2("Rook", 2);
	Knight blackKnight1("Knight", 2);
	Knight blackKnight2("Knight", 2);
	Bishop blackBishop1("Bishop", 2);
	Bishop blackBishop2("Bishop", 2);
	Queen blackQueen("Queen", 2);
	King blackKing("King", 2);

	board[7][0].piece = &whiteRook1;
	board[7][1].piece = &whiteKnight1;
	board[7][2].piece = &whiteBishop1;
	board[7][3].piece = &whiteQueen;
	board[7][4].piece = &whiteKing;
	board[7][5].piece = &whiteBishop2;
	board[7][6].piece = &whiteKnight2;
	board[7][7].piece = &whiteRook2;

	board[6][0].piece = &whitePawn1;
	board[6][1].piece = &whitePawn2;
	board[6][2].piece = &whitePawn3;
	board[6][3].piece = &whitePawn4;
	board[6][4].piece = &whitePawn5;
	board[6][5].piece = &whitePawn6;
	board[6][6].piece = &whitePawn7;
	board[6][7].piece = &whitePawn8;

	board[0][0].piece = &blackRook1;
	board[0][1].piece = &blackKnight1;
	board[0][2].piece = &blackBishop1;
	board[0][3].piece = &blackQueen;
	board[0][4].piece = &blackKing;
	board[0][5].piece = &blackBishop2;
	board[0][6].piece = &blackKnight2;
	board[0][7].piece = &blackRook2;

	board[1][0].piece = &blackPawn1;
	board[1][1].piece = &blackPawn2;
	board[1][2].piece = &blackPawn3;
	board[1][3].piece = &blackPawn4;
	board[1][4].piece = &blackPawn5;
	board[1][5].piece = &blackPawn6;
	board[1][6].piece = &blackPawn7;
	board[1][7].piece = &blackPawn8;

	int currentPlayer = BLACK_PLAYER; // since we change the current player in the while loop we declare it as 2 so it can become 1
	String command;

	while (!isKingDead)
	{
		//after every valid move we will change Current player
		if (currentPlayer == WHITE_PLAYER) {
			currentPlayer = BLACK_PLAYER;
			//std::cout << "from 1 to 2";
		}
		else {
			currentPlayer = WHITE_PLAYER;
			//std::cout << "from 2 to 1";
		}

		PrintBoard(board);
		PrintStartTurnMessage(currentPlayer);

		std::cin >> command;
		if (command == EXIT) break;
		else
		{
			ExecutePlayerCommand(currentPlayer);
		}
	}
}