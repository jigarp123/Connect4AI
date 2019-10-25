
#include <stdio.h>

void drawBoard(int board[6][7]);
//draws board to the console (0 = empty space, 1 = X, 2 = O)
void playerMove(int board[6][7]);
//update board with player's choice (player is always X)
void compMove(int board[6][7]);
//update board with computer's choice through AI (computer is always O)
int getScore(int board[6][7], int moves[2][5]);
//return score of board (2 = player won, -2 = computer won, 0 = tie, 1 otherwise) also keeps track of the winning moves to print out later
int getRow(int col, int board[6][7]);
//return the row index where the chip would fall in column col
void makeMove(int col, int temp[6][7], int board[6][7], int move);
//update temp with move in column col
char getColLet(int col);
//returns the corresponding column character from the column index

int main(void)
{
	_Bool ask = 1, playerTurn;
	char firstInput;
  int board[6][7]; //represents game board as [row][column]
  for(int r = 0; r < 6; r++)
  {
    for(int c = 0; c < 7; c++)
    {
      board[r][c] = 0; //sets the board values to 0 as default (represents blank space)
    }
  }
  drawBoard(board); //draw initial game board
	while (ask) //keep asking until valid input is entered
	{
		ask = 0;
		printf("Do you want to go first? (y/n)\n");
		scanf(" %c", &firstInput);
		if (firstInput == 'y' || firstInput == 'Y')
		{
			playerTurn = 1; //player goes first
		}
		else if (firstInput == 'n' || firstInput == 'N')
		{
			playerTurn = 0; //computer goes first
		}
		else
		{
			printf("Invalid character\n");
			ask = 1; //ask again
		}
	}
	int result = 1; //start game value
  int moves[2][5];
	while (result == 1) //keep playing game until winner or tie
	{
		if (playerTurn)
		{
			playerMove(board); //update board with player's choice
      drawBoard(board); //draw board after player moves
			result = getScore(board, moves); //check to see if player won or tied
			if (result == 2)
			{
				printf("You WON ");
        //prints the winning moves accordingly
        if(moves[0][4] == 0)
        {
          printf("diagonally ");
        }
        else if(moves[0][4] == 1)
        {
          printf("vertically ");
        }
        else
        {
          printf("horizontally ");
        }
        printf("with moves %i%c, %i%c, %i%c, %i%c\n",moves[0][0]+1, getColLet(moves[1][0]),moves[0][1]+1, getColLet(moves[1][1]),moves[0][2]+1, getColLet(moves[1][2]),moves[0][3]+1, getColLet(moves[1][3]));
    
			}
			else if (result == 0)
			{
				printf("It's a tie\n");
			}
      else //result = 1
      {
        playerTurn = 0; //game continues so computer goes next
      }
		}
		if (!playerTurn)
		{
			playerTurn = 1; //player goes next
			compMove(board); //update computer move in board
      drawBoard(board); //draw board after computer moves
			result = getScore(board, moves); //check to see if computer won or tied
			if (result == -2) //computer won so player lost
			{
				printf("You lost :(\nThe computer won ");
        //prints the winning moves accordingly
        if(moves[0][4] == 0)
        {
          printf("diagonally ");
        }
        else if(moves[0][4] == 1)
        {
          printf("vertically ");
        }
        else
        {
          printf("horizontally ");
        }
        printf("with moves %i%c, %i%c, %i%c, %i%c\n",moves[0][0]+1, getColLet(moves[1][0]),moves[0][1]+1, getColLet(moves[1][1]),moves[0][2]+1, getColLet(moves[1][2]),moves[0][3]+1, getColLet(moves[1][3]));
			}
			else if (result == 0)
			{
				printf("It's a tie\n");
			}
		}
	}
	return 0; //end of game. Player won, lost or tied
}
char getColLet(int col)
{
  if(col == 0)
  {
    return 'A';
  }
  else if (col == 1)
  {
    return 'B';
  }
  else if (col == 2)
  {
    return 'C';
  }
  else if (col == 3)
  {
    return 'D';
  }
  else if (col == 4)
  {
    return 'E';
  }
  else if (col == 5)
  {
    return 'F';
  }
  return 'G';
}
int getScore(int board[6][7], int moves[2][5]) 
{
	for (int row = 5; row >= 3; row--) //checks 4 in a row diagonally
	{
		for (int col = 0; col < 4; col++)
		{
			if (board[row][col] == 1 && board[row - 1][col + 1] == 1 && board[row - 2][col + 2] == 1 && board[row - 3][col + 3] == 1)
			{
        //records the winning moves
        moves[0][0] = row;
        moves[0][1] = row - 1;
        moves[0][2] = row - 2;
        moves[0][3] = row - 3;
        moves[1][0] = col;
        moves[1][1] = col + 1;
        moves[1][2] = col + 2;
        moves[1][3] = col + 3;
        moves[0][4] = 0;
				return 2;
			}
			else if (board[row][col] == 2 && board[row - 1][col + 1] == 2 && board[row - 2][col + 2] == 2 && board[row - 3][col + 3] == 2)
			{
        moves[0][0] = row;
        moves[0][1] = row - 1;
        moves[0][2] = row - 2;
        moves[0][3] = row - 3;
        moves[1][0] = col;
        moves[1][1] = col + 1;
        moves[1][2] = col + 2;
        moves[1][3] = col + 3;
        moves[0][4] = 0;
				return -2;
			}
		}
	}
	for (int row = 5; row >= 3; row--) //checks 4 in a row diagonally in the other direction
	{
		for (int col = 3; col < 7; col++)
		{
			if (board[row][col] == 1 && board[row - 1][col - 1] == 1 && board[row - 2][col - 2] == 1 && board[row - 3][col - 3] == 1)
			{
        moves[0][0] = row;
        moves[0][1] = row - 1;
        moves[0][2] = row - 2;
        moves[0][3] = row - 3;
        moves[1][0] = col;
        moves[1][1] = col - 1;
        moves[1][2] = col - 2;
        moves[1][3] = col - 3;
        moves[0][4] = 0;
				return 2;
			}
			else if (board[row][col] == 2 && board[row - 1][col - 1] == 2 && board[row - 2][col - 2] == 2 && board[row - 3][col - 3] == 2)
			{
        moves[0][0] = row;
        moves[0][1] = row - 1;
        moves[0][2] = row - 2;
        moves[0][3] = row - 3;
        moves[1][0] = col;
        moves[1][1] = col - 1;
        moves[1][2] = col - 2;
        moves[1][3] = col - 3;
        moves[0][4] = 0;
				return -2;
			}
		}
	}
	for (int row = 5; row >= 3; row--) //checks 4 in a row vertically
	{
		for (int col = 0; col < 7; col++)
		{
			if (board[row][col] == 1 && board[row - 1][col] == 1 && board[row - 2][col] == 1 && board[row - 3][col] == 1)
			{
        moves[0][0] = row;
        moves[0][1] = row - 1;
        moves[0][2] = row - 2;
        moves[0][3] = row - 3;
        moves[1][0] = col;
        moves[1][1] = col;
        moves[1][2] = col;
        moves[1][3] = col;
        moves[0][4] = 1;
				return 2;
			}
			else if (board[row][col] == 2 && board[row - 1][col] == 2 && board[row - 2][col] == 2 && board[row - 3][col] == 2)
			{
        moves[0][0] = row;
        moves[0][1] = row - 1;
        moves[0][2] = row - 2;
        moves[0][3] = row - 3;
        moves[1][0] = col;
        moves[1][1] = col;
        moves[1][2] = col;
        moves[1][3] = col;
        moves[0][4] = 1;
				return -2;
			}
		}
	}
	for (int row = 5; row >= 0; row--) //checks 4 in a row horizontally
	{
		for (int col = 0; col < 4; col++)
		{
			if (board[row][col] == 1 && board[row][col + 1] == 1 && board[row][col + 2] == 1 && board[row][col + 3] == 1)
			{
        moves[0][0] = row;
        moves[0][1] = row;
        moves[0][2] = row;
        moves[0][3] = row;
        moves[1][0] = col;
        moves[1][1] = col + 1;
        moves[1][2] = col + 2;
        moves[1][3] = col + 3;
        moves[0][4] = 2;
				return 2;
			}
			else if (board[row][col] == 2 && board[row][col + 1] == 2 && board[row][col + 2] == 2 && board[row][col + 3] == 2)
			{
        moves[0][0] = row;
        moves[0][1] = row;
        moves[0][2] = row;
        moves[0][3] = row;
        moves[1][0] = col;
        moves[1][1] = col + 1;
        moves[1][2] = col + 2;
        moves[1][3] = col + 3;
        moves[0][4] = 2;
				return -2;
			}
		}
	}
	for (int row = 5; row >= 0; row--) //check to see if there are any spaces left
	{
		for (int col = 0; col < 7; col++)
		{
			if (board[row][col] == 0)
			{
				return 1; //found an empty space on board so game continues
			}
		}
	}
	return 0; //defaults to tie since there are no more spaces left
}
int getRow(int col, int board[6][7])
{
	for (int i = 0; i < 6; i++)
	{
		if (board[i][col] == 0)
		{
			return i; //returns the row of an open space traversing from the bottom to the top of board
		}
	}
	return -1; //returns -1 if column is full
}
void makeMove(int col, int temp[6][7], int board[6][7], int move)
{
	for (int r = 0; r < 6; r++)
	{
		for (int c = 0; c < 7; c++)
		{
			temp[r][c] = board[r][c]; //update temp to match board
		}
	}
	temp[getRow(col, temp)][col] = move; //update temp with move
}
void compMove(int board[6][7])
{
	int scores[7]; //scores of making move at each column
	for (int i = 0; i < 7; i++)
	{
		scores[i] = 10; //defaults all values in scores to 10 (worst score for computer), score says 10 if the column is full so the computer never makes that move
	}
	int colMin = 0, min = 10; //deafults min score to 10
	int temp[6][7]; //temporary game state to get best move for computer
  int moves[2][5];
	for (int c = 0; c < 7; c++) //test every column move to find the best move for the computer
	{
		if (getRow(c, board) != -1) //open spot in column c
		{
			makeMove(c, temp, board, 2); //test offensive move
			scores[c] = getScore(temp, moves); //get score after making move
			if (scores[c] == 1) //1 is the value for the game continuing which does not favor the computer nor the player so we set the score to 0
			{
				scores[c] = 0;
			}
			makeMove(c, temp, board, 1); //test defensive move
			scores[c] = scores[c] - getScore(temp, moves); //subtract the defensive move from the offensive to determine which column gives the best overall move for the computer
			if (scores[c] == 1)
			{
				scores[c] = 0;
			}
			if (scores[c] < min) //finds minimum score (best for computer)
			{
				colMin = c;
				min = scores[c];
			}
		}
	}
	board[getRow(colMin, board)][colMin] = 2; //updates board with best move for computer
  printf("Computer's turn\n");
}
void playerMove(int board[6][7])
{
	int col = 0, row = 0;
	char input;
	_Bool ask = 1; //start asking for move
	while (ask) //keep asking until valid input is entered
	{
		ask = 0;
		printf("Make your move\n");
		scanf(" %c", &input);
    //convert letter to column index
		if (input == 'A' || input == 'a')
		{
			col = 0;
		}
		else if (input == 'B' || input == 'b')
		{
			col = 1;
		}
		else if (input == 'C' || input == 'c')
		{
			col = 2;
		}
		else if (input == 'D' || input == 'd')
		{
			col = 3;
		}
		else if (input == 'E' || input == 'e')
		{
			col = 4;
		}
		else if (input == 'F' || input == 'f')
		{
			col = 5;
		}
		else if (input == 'G' || input == 'g')
		{
			col = 6;
		}
		else //no corresponding column
		{
			printf("Invalid input\n");
			ask = 1; //ask again
		}
		row = getRow(col, board);
		if (row == -1) //column is full
		{
			printf("Cannot place here\n");
			ask = 1; //ask again
		}
	}
	board[row][col] = 1; //update board with player move
}
void drawBoard(int board[6][7])
{
	printf("   A B C D E F G\n");
	for (int c = 5; c >= 0; c--)
	{
		printf("%i  ", c + 1);
		for (int r = 0; r < 7; r++)
		{
			if (board[c][r] == 0)
			{
				printf(". "); //represents an empty space
			}
			else if (board[c][r] == 1) //represents a player move
			{
				printf("X ");
			}
			else if (board[c][r] == 2) //represents a computer move
			{
				printf("O ");
			}
		}
		printf("\n");
	}
	printf("\n");
}