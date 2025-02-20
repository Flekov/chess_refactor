#pragma once
#include "Square.h"
#include "Pawn.h"
#include "Rook.h"
#include "Knight.h"
#include "Bishop.h"
#include "Queen.h"
#include "King.h"

class Gameplay {
private: 
	const int MAX_MOVE_COMMAND_LENGHT = 10;
	const int WHITE_PLAYER = 1;
	const int BLACK_PLAYER = 2;

	const String HELP = "help";
	const String EXIT = "exit";
	const String MOVE = "move";
	const String UNDO = "undo";

	static const int BOARD_SIZE = 8;
	const int START_LETTER_INDEX_IN_COMMAND = 5;
	const int START_NUMBER_INDEX_IN_COMMAND = 6;
	const int END_LETTER_INDEX_IN_COMMAND = 8;
	const int END_NUMBER_INDEX_IN_COMMAND = 9;

	int GetCoordinate(String move, int index);
	int GetLetterCoordinate(String move, int index);
	int GetNumberCoordinate(String move, int index);
	bool IsStartPositionEmpty(Square board[BOARD_SIZE][BOARD_SIZE], int row, int col);
	bool IsPieceBelongsToCurrentPlayer(Square board[BOARD_SIZE][BOARD_SIZE], int row, int col, int currentPlayer);
	bool IsEndPositionOccupiedByCurrentPlayerPiece(Square board[BOARD_SIZE][BOARD_SIZE], int row, int col, int currentPlayer);

	bool IsFirstDiagonalBlockedByPiece(Square board[BOARD_SIZE][BOARD_SIZE], int startRow, int startCol, int endRow, int endCol);
	bool IsSecondDiagonalBlockedByPiece(Square board[BOARD_SIZE][BOARD_SIZE], int startRow, int startCol, int endRow, int endCol);
	bool IsThirdDiagonalBlockedByPiece(Square board[BOARD_SIZE][BOARD_SIZE], int startRow, int startCol, int endRow, int endCol);
	bool IsForthDiagonalBlockedByPiece(Square board[BOARD_SIZE][BOARD_SIZE], int startRow, int startCol, int endRow, int endCol);
	bool IsLeftRowBlockedByPiece(Square board[BOARD_SIZE][BOARD_SIZE], int startRow, int startCol, int endRow, int endCol);
	bool IsRightRowBlockedByPiece(Square board[BOARD_SIZE][BOARD_SIZE], int startRow, int startCol, int endRow, int endCol);
	bool IsUpColBlockedByPiece(Square board[BOARD_SIZE][BOARD_SIZE], int startRow, int startCol, int endRow, int endCol);
	bool IsDownColBlockedByPiece(Square board[BOARD_SIZE][BOARD_SIZE], int startRow, int startCol, int endRow, int endCol);

	void MakeMove(Square board[BOARD_SIZE][BOARD_SIZE], int startRow, int startCol, int endRow, int endCol, int currentPlayer, int rowDifference, int colDifference);

	bool IsPawn(Square board[BOARD_SIZE][BOARD_SIZE], int row, int col);
	bool IsPawnMoveValid(Square board[BOARD_SIZE][BOARD_SIZE], int startRow, int startCol, int endRow, int endCol, int currentPlayer, int rowDifference, int colDifference);

	bool IsKing(Square board[BOARD_SIZE][BOARD_SIZE], int row, int col);
	bool IsKingMoveValid(Square board[BOARD_SIZE][BOARD_SIZE], int startRow, int startCol, int endRow, int endCol, int currentPlayer, int rowDifference, int colDifference);

	bool IsQueen(Square board[BOARD_SIZE][BOARD_SIZE], int row, int col);
	bool IsQueenMoveValid(Square board[BOARD_SIZE][BOARD_SIZE], int startRow, int startCol, int endRow, int endCol, int currentPlayer, int rowDifference, int colDifference);

	bool IsKnight(Square board[BOARD_SIZE][BOARD_SIZE], int row, int col);
	bool IsKnightMoveValid(Square board[BOARD_SIZE][BOARD_SIZE], int startRow, int startCol, int endRow, int endCol, int currentPlayer, int rowDifference, int colDifference);

	bool IsBishop(Square board[BOARD_SIZE][BOARD_SIZE], int row, int col);
	bool IsBishopMoveValid(Square board[BOARD_SIZE][BOARD_SIZE], int startRow, int startCol, int endRow, int endCol, int currentPlayer, int rowDifference, int colDifference);

	bool IsRook(Square board[BOARD_SIZE][BOARD_SIZE], int row, int col);
	bool IsRookMoveValid(Square board[BOARD_SIZE][BOARD_SIZE], int startRow, int startCol, int endRow, int endCol, int currentPlayer, int rowDifference, int colDifference);

	const int ROW_1_COORDINATE_VISUALIZATION = 4; 				const int COL_1_COORDINATE_VISUALIZATION = 10;
	const int ROW_2_COORDINATE_VISUALIZATION = 7;				const int COL_2_COORDINATE_VISUALIZATION = 17;
	const int ROW_3_COORDINATE_VISUALIZATION = 10;				const int COL_3_COORDINATE_VISUALIZATION = 24;
	const int ROW_4_COORDINATE_VISUALIZATION = 13;				const int COL_4_COORDINATE_VISUALIZATION = 31;
	const int ROW_5_COORDINATE_VISUALIZATION = 16;				const int COL_5_COORDINATE_VISUALIZATION = 38;
	const int ROW_6_COORDINATE_VISUALIZATION = 19;				const int COL_6_COORDINATE_VISUALIZATION = 45;
	const int ROW_7_COORDINATE_VISUALIZATION = 22;				const int COL_7_COORDINATE_VISUALIZATION = 52;
	const int ROW_8_COORDINATE_VISUALIZATION = 25;				const int COL_8_COORDINATE_VISUALIZATION = 59;
	int GetRowCoordinateForVisualization(int row);
	int GetColCoordinateForVisualization(int col);
	void VisualizePiece(Square board[BOARD_SIZE][BOARD_SIZE], int row, int col, int rowCoordinate, int colCoordinate);

	void PrintStartTurnMessage(int currentPlayer);
	void ExecutePlayerCommand(int currentPlayer);

public:
	Square board[BOARD_SIZE][BOARD_SIZE];
	char gameVisualization[28][65];
	bool isKingDead = false;
	Gameplay();
	~Gameplay();
	void PlayGame();
	bool IsMoveCommandValid(String move);
	bool IsMovePossible(String move, Square board[8][8], int currentPlayer);
	void FillBoard();
	void PaintBoard();
	void PrintBorders();
	void PrintNumbering();
	void FigureSpaceCleaning();
	void PlacePieces(Square board[8][8]);
	void PrintBoard(Square board[8][8]);
	//void undo(String move, Board board[8][8]);

};


