#include <iostream> 

using namespace std;

bool whiteColor(int character){
  if(character == 2 || character == 4){
    return true;
  }
  return false;
}

bool blackColor(int character){
  if(character == 3 || character == 5){
    return true;
  }
  return false;
}
  
bool emptyCharacter(int character){
  if(character == 1){
    return true;
  }
  return false;
}

#define EMPTY 1
#define WHITE 2
#define BLACK 3
#define WHITEKING 4
#define BLACKKING 5
#define ROWS 8
#define COLUMNS 8

void printDisplay(int board[][COLUMNS]);

void swap(int board[ROWS][COLUMNS], int initialX, int initialY, int newX, int newY);

char valueToSymbol(int initialX);

void printBoard(int board[][COLUMNS]);

int playerTurn(int board[][COLUMNS], int player, int initialX, int initialY, int newX, int newY);
 
int main()
{
	int character;
	int initialX, newX; 
	char initialY, newY; 
	int board[ROWS][COLUMNS]={
    {0,2,0,2,0,2,0,2},
    {2,0,2,0,2,0,2,0}, 
    {0,2,0,2,0,2,0,2}, 
    {1,0,1,0,1,0,1,0}, 
    {0,1,0,1,0,1,0,1}, 
    {3,0,3,0,3,0,3,0},
    {0,3,0,3,0,3,0,3},
	{3,0,3,0,3,0,3,0}};
  
  cout << "Instructions: Enter the number then the letter of the piece you would like to move" << endl << "Then enter the place you want to move the piece to." << endl << "Example: 3b to 4a." << endl;
  cout << endl << "W - White" << endl << "B - Black" << endl << "E - Empty" << endl;
  cout << endl;
    for(;;){
        printBoard(board);
        while(1){
            cout << "White's turn, From: ";
            cin >> initialX >> initialY;
    	    cout <<"to: ";
        	cin >> newX >> newY;
        	if(playerTurn(board, WHITE, initialX - 1, initialY - 'a', newX - 1, newY - 'a') == 0)
        	    break;
        	cout << "Illegal move, try again" << endl;
        }
        printBoard(board);
        while(1){
            cout << "Black's turn, From: ";
            cin >> initialX >> initialY;
    	    cout << "to: ";
        	cin >> newX >> newY;
        	if(playerTurn(board, BLACK, initialX - 1, initialY - 'a', newX - 1, newY - 'a') == 0)
        	    break;
        	cout << "Illegal move, try again" << endl;
        }
    }
 
	getchar();
	getchar();
    return 0;
}

void printBoard(int board[][COLUMNS])
{
    int rr, cc, pp;
    
    cout <<"  +---+---+---+---+---+---+---+---+" << endl;
    
    for (rr=0; rr<ROWS; rr++)
    {
        cout <<rr+1 << " |";
        for (cc=0; cc<COLUMNS; cc++)
        {
            cout <<" " <<valueToSymbol(board[rr][cc]) << " |";
        }
        cout << endl;
        cout <<"  +---+---+---+---+---+---+---+---+" << endl;
    }
    
    cout <<"    a   b   c   d   e   f   g   h" << endl;
}
 
void swap(int board[ROWS][COLUMNS], int initialX, int initialY, int newX, int newY)
{
    int temp;
    
     cout << "SWAPPING: " << initialX << "," << initialY << " TO " << newX << "," << newY << endl;
    
    temp = board[initialX][initialY];
    
    board[initialX][initialY] = board[newX][newY];
    
    board[newX][newY] = temp;
}
 
char valueToSymbol(int initialX) 
{
  if(initialX == 0){
    return ' ';
  }
  else if(initialX == 1){
    return 'E';
  }
  else if(initialX == 2){
    return 'W';
  }
  else if(initialX == 3){
    return 'B';
  }
  else{
    return 'X';
  }
}
 
int playerTurn(int board[][COLUMNS], int player, int initialX, int initialY, int newX, int newY)
{
    int jump_1;
    int jump_2;
    
    if(player == WHITE){
        cout << "WHITE MOVE FROM " << initialX << "," << initialY << " TO " << newX << "," << newY << endl;
    } else {
        cout << "BLACK MOVE FROM " << initialX << "," << initialY << " TO " << newX << "," << newY << endl;
    }

    if(initialX < 0 && ROWS <= initialX){ 
        cout << "OUT OF BOUNDS" << endl;
        return -1;
    }
    if(initialY < 0 && COLUMNS <= initialY){
        cout << "OUT OF BOUNDS" << endl;
        return -1;
    }
        
    if(newX < 0 && ROWS <= newX){
        cout << "OUT OF BOUNDS";
        return -1;
        
    }
    if(newY < 0 && COLUMNS<= newY){
        cout << "OUT OF BOUNDS" << endl;
        return -1;
    }
        
    if(player == WHITE){
        if(board[initialX][initialY] != WHITE){
            cout << "MOVE YOUR OWN PIECES." << endl;
            return -1;
        }
    } else { 
        if(board[initialX][initialY] != BLACK){
            cout << "MOVE YOUR OWN PIECES." << endl;
            return -1;
        }
    }
    
    if(board[newX][newY] != EMPTY){
        cout << "NOT EMPTY." << endl;
        return -1;
    }
    
    if(player == WHITE){
        if(initialX >= newX){
            cout << "WHITE PLAYER MOVE DOWN" << endl;
            return -1;
        }
    } else { 
        if(initialX <= newX){
            cout << "BLACK PLAYER MOVES UP" << endl;   
            return -1;
        }
    }
    if(initialX - newX == -1 || initialX - newX == 1){
        if(initialY - newY == 1 || initialY - newY == -1){
            swap(board, initialX, initialY, newX, newY);
            return 0;
        }
    }  
  
    if(initialX - newX == -2 || initialX - newX == 2){
        if(initialY - newY == -2 || initialY - newY == 2){
            if(initialX < newX){ 
                jump_1 = initialX + 1;
            } else { 
                jump_1 = initialX - 1;
            }
            if(initialY < newY){ 
                jump_2 = initialY + 1;
            } else { 
                jump_2 = initialY - 1;
            }
            
            if(player == WHITE && board[jump_1][jump_2]!=BLACK)
            {
                cout << "ENEMY IS NOT BLACK AT: " << jump_1 << ", " << jump_2;
                return -1;
            }
            if(player == BLACK && board[jump_1][jump_2] != WHITE){
                cout << "YOU CAN ONLY JUMP OVER AN ENEMY PLAYER." << endl;
                return -1;
            }
 
            board[jump_1][jump_2] = 1;
            swap(board,initialX,initialY,newX,newY);
            return 0;
        }
    }
    
    cout << "CAN ONLY MOVE DIAGONALLY." << endl;
    return -1;
}