#include<iostream>
#include <sstream>
#include <iostream>
#include <fstream>
using namespace std;

struct Move
{
	int row, col;
};

char AI = 'O', player = 'X';


bool isMovesLeft(char board[3][3])
{
	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 3; j++)
			if (isdigit(board[i][j]))
				return true;
	return false;
}

//evalutate winning condition
int evaluate(char b[3][3])
{
	// Checking for Rows 
	for (int row = 0; row < 3; row++)
	{
		if (b[row][0] == b[row][1] &&
			b[row][1] == b[row][2])
		{
			if (b[row][0] == AI)
				return +10;
			else if (b[row][0] == player)
				return -10;
		}
	}

	// Checking for Columns
	for (int col = 0; col < 3; col++)
	{
		if (b[0][col] == b[1][col] &&
			b[1][col] == b[2][col])
		{
			if (b[0][col] == AI)
				return +10;

			else if (b[0][col] == player)
				return -10;
		}
	}

	// Checking for Diagonals
	if (b[0][0] == b[1][1] && b[1][1] == b[2][2])
	{
		if (b[0][0] == AI)
			return +10;
		else if (b[0][0] == player)
			return -10;
	}

	if (b[0][2] == b[1][1] && b[1][1] == b[2][0])
	{
		if (b[0][2] == AI)
			return +10;
		else if (b[0][2] == player)
			return -10;
	}

	// Else if none of them have won then return 0
	return 0;
}

// This is the minimax function. It considers all the possible ways the game can go and returns 
// the value of the board
int minimax(char board[3][3], int depth, bool isMax)
{
	int score = evaluate(board);

	// If Maximizer has won the game return his/her evaluated score
	if (score == 10)
		return score;

	// If Minimizer has won the game return his/her evaluated score
	if (score == -10)
		return score;

	// If there are no more moves and no winner then it is a tie
	if (isMovesLeft(board) == false)
		return 0;

	// If this maximizer's move
	if (isMax)
	{
		int best = -1000;

		// Traverse all cells
		for (int i = 0; i < 3; i++)
		{
			for (int j = 0; j < 3; j++)
			{
				// Check if cell is empty
				if (isdigit(board[i][j]))
				{
					// Make the move
					char digit = board[i][j];
					board[i][j] = AI;

					// Call minimax recursively and choose
					// the maximum value
					best = max(best,
						minimax(board, depth + 1, !isMax));

					// Undo the move
					board[i][j] = digit;
				}
			}
		}
		return best;
	}

	// If this minimizer's move
	else
	{
		int best = 1000;

		// Traverse all cells
		for (int i = 0; i < 3; i++)
		{
			for (int j = 0; j < 3; j++)
			{
				// Check if cell is empty
				if (isdigit(board[i][j]))
				{
					// Make the move
					char digit = board[i][j];
					board[i][j] = player;

					// Call minimax recursively and choose
					// the minimum value
					best = min(best,
						minimax(board, depth + 1, !isMax));

					// Undo the move
					board[i][j] = digit;
				}
			}
		}
		return best;
	}
}

// This will return the best possible move for the AI
Move findBestMove(char board[3][3])
{
	int bestVal = -1000;
	Move bestMove;
	bestMove.row = -1;
	bestMove.col = -1;

	// Traverse all cells, evaluate minimax function for
	// all empty cells. And return the cell with optimal
	// value.
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			// Check if cell is empty
			if (isdigit(board[i][j]))
			{
				// Make the move
				char digit = board[i][j];
				board[i][j] = AI;

				// compute evaluation function for this
				// move.
				int moveVal = minimax(board, 0, false);

				// Undo the move
				board[i][j] = digit;

				// If the value of the current move is
				// more than the best value, then update
				// best/
				if (moveVal > bestVal)
				{
					bestMove.row = i;
					bestMove.col = j;
					bestVal = moveVal;
				}
			}
		}
	}

	return bestMove;
}

void openBoard(char square[3][3]) {
	
	cout << endl;

	cout << "     |     |     " << endl;
	cout << "  " << square[0][0] << "  |  " << square[0][1] << "  |  " << square[0][2] << endl;

	cout << "_____|_____|_____" << endl;
	cout << "     |     |     " << endl;

	cout << "  " << square[1][0] << "  |  " << square[1][1] << "  |  " << square[1][2] << endl;

	cout << "_____|_____|_____" << endl;
	cout << "     |     |     " << endl;

	cout << "  " << square[2][0] << "  |  " << square[2][1] << "  |  " << square[2][2] << endl;

	cout << "     |     |     " << endl << endl;
}

char& position(char board[3][3], int pos) {
	switch (pos) {
		case 1:
			return board[0][0];
		case 2:
			return board[0][1];
		case 3:
			return board[0][2];
		case 4:
			return board[1][0];
		case 5:
			return board[1][1];
		case 6:
			return board[1][2];
		case 7:
			return board[2][0];
		case 8:
			return board[2][1];
		case 9:
			return board[2][2];

	}
}

bool validity(string input, char board[3][3]) {
	if (input.size() == 1) {
		int digit = stoi(input);
		int arr[9] = { 1,2,3,4,5,6,7,8,9 };
		for (int& i : arr) {
			if (digit == i)
				if (isdigit(position(board, digit))) {
					return true;
				}
		}
		return false;
	}
	else
		return false;
}

// Driver code
int main()
{
	char board[3][3] =
	{
		{ '1', '2', '3' },
		{ '4', '5', '6' },
		{ '7', '8', '9' }
	};

	cout << "\n\n\tTic Tac Toe\n\n";

	cout << "Player (X)  -  AI (O)" << endl << endl;
	openBoard(board);
	cout << "Please enter just the grid number you want to place in with no other symbols: ";



	bool shouldStop{ false };
	string userInput;
	while (!shouldStop)
	{
		getline(cin, userInput);
		if (validity(userInput, board)) {
			position(board, stoi(userInput)) = player;
			openBoard(board);
			if (evaluate(board) == 10) {
				shouldStop = true;
				cout << "You lost!\n";
				break;
			}

			else if (evaluate(board) == -10) {
				shouldStop = true;
				cout << "You win.\n";
				break;
			}

			else if (!isMovesLeft(board)) {
				shouldStop = true;
				cout << "Tie.\n";
				break;
			}
			Move bestMove = findBestMove(board);
			board[bestMove.row][bestMove.col] = AI;
			cout << "AI move : \n";
			openBoard(board);
			if (evaluate(board) == 10) {
				shouldStop = true;
				cout << "You lost!\n";
				break;
			}

			else if (evaluate(board) == -10) {
				shouldStop = true;
				cout << "You win.\n";
				break;
			}

			else if (!isMovesLeft(board)) {
				shouldStop = true;
				cout << "Tie.\n";
				break;
			}
			cout << "Enter the grid you want to place in: ";
		}
		else
			cout << "Please enter a valid grid: ";
	}

	cout << "Program stopped. \n";
	return 0;
}