#include <stdio.h>
#include <stdlib.h>
#include <time.h>


/*
* clearScreen()
*
*    Creates the illusion of a "clear screen" by creating 50 newline characters.
*    This makes the screen easier to read.
*/
void clearScreen()
{
    for(int i= 0; i < 50; i++)
    {
        printf("\n");
    }
}

/*
* printBoard()
*
*    Used to print the Tic Tac Toe playboard and fill in the taken and empty spaces.
*    Takes parameter moves, 3x3 2D array of characters containing X, O, or space as moves are taken or empty.
*/
void printBoard(char moves[3][3])
{
    //call to clearScreen to create seperation and give you a "clear screen"
    clearScreen();
    
    //print the top of the gameboard, will not be necessary to loop this.
    printf(" ___ ___ ___\n");
    
    //Loops through each row, and prints the taken moves or empty spaces as passed by moves
    for(int i = 0; i < 3; i++)
    {
        printf("| %c | %c | %c |\n|___|___|___|\n", moves[i][0], moves[i][1], moves[i][2]);
    }    
    
        
}

/*
* checkDraw()
*   
*   Checks to see if the board has any empty spaces or is full.
*   Takes moves 3x3 2D array with the current moves taken.
*   Loops through each row then loops each column in the row with nested loop.
*   Returns 0 if board is not full.
*   Returns 1 if board is full.
*   
*/

int checkDraw(char moves[3][3])
{
    //Loops through array by row, then by collumn and returns 0 immediately if space found in coordinate
    for(int i = 0; i < 3; i++)
    {
        for(int k = 0; k < 3; k++)
        {
            if(moves[i][k] == ' ')
            {
                return 0;
            }
        }                        
    }
    
    return 1;          
}

/*
* freeSpace()
*   
*   Checks to see whether the chosen space is filled or empty.
*   Takes moves 3x3 2D array, x coordinate, y coordinate.
*   Returns 1 if character at x,y position in array is space.
*   Returns 0 otherwise (if character is "filled").
*/
int freeSpace(char moves[3][3], int x, int y)
{
    if(moves[x][y] == ' ')
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

/*
* gameOver()
*   Takes moves 3x3 2D array
*   checks columns, rows and both diagnols for winning combination.
*   Returns 1 if a win is found and prints winner.
*   Returns 1 if all spaces are filled without a winner, and prints that game is a draw.
*   Returns 0 if there is no winning combination and there are empty spaces available.
*/

int gameOver(char moves[3][3])
{   
    //check the rows for no spaces and a match, print the winning digit and return
    for(int i = 0; i < 3; i++)
    {
        if(moves[i][0] != ' ' && moves[i][0] == moves[i][1] && moves[i][1] == moves[i][2])
        {
            printBoard(moves);
            printf("%c wins the game!!\n\n", moves[i][0]);
            return 1;    
        }
    }
    
    //check the columns for no spaces and a match, print the winning digit and return
    for(int i = 0; i < 3; i++)
    {
        if(moves[0][i] != ' ' && moves[0][i] == moves[1][i] && moves[1][i] == moves[2][i])
        {
            printBoard(moves);
            printf("\n%c wins the game!!\n\n", moves[0][i]);
            return 1;    
        }
    }
    //check diagonally heading west to east for no spaces and a match, print the winning digit and return
    if(moves[0][0] != ' ' && moves[0][0] == moves[1][1] && moves[1][1] == moves[2][2])
    {
        printBoard(moves);
        printf("\n%c wins the game!!\n\n", moves[0][0]);
        return 1;    
    }
    
    //check diagonally heading east to west for no spaces and a match, print the winning digit and return
    if(moves[0][2] != ' ' && moves[0][2] == moves[1][1] && moves[1][1] == moves[2][0])
    {
        printBoard(moves);
        printf("\n%c wins the game!!\n\n", moves[0][2]);
        return 1;    
    }
    
    //game could be a draw.  Use checkDraw to check and return accordingly
    int draw = checkDraw(moves);
    
    if(draw == 1)
    {
        printBoard(moves);
        printf("\nThis game is a draw!!\n\n");
        return 1;
    }   
    
    //game is not over if we reach this
    return 0;
}

/*
* printInstructions()
*
*   Used to print some simple instructions to the user when we first run the game.
*/

void printInstructions()
{
        
        printf("\n\nWelcome to Dale's moderately sweet Tic Tac Toe Game\n\n");
        printf("Here are some quick instructions.\n\n");
        printf("You will be O and the computer will be X.\n\n");
        printf("The computer will go first.\n\n");
        printf("You will then be prompted for a coordinate,\n0 0 will be the first box, 0 1 will be the second, etc...\n\nJust type in the coordinate you would like to place your x in.\n\n");
        printf("At this point there is no error checking, so please, digits 0-2 only please,\nRemember if you break it you fix it!!\n\n");
        printf("If your ready to continue, please type the letter c...\n\n");
        printf("This will clear the screen and begin your game.\n\n");
        printf("TYPE c TO CONTINUE TO GAME!!  "); 
}

int main()
{
    //moves taken, initialized to an empty board    
    char moves[3][3] = {
        {' ', ' ', ' '},
        {' ', ' ', ' '},
        {' ', ' ', ' '}        
    };
    int needInstructions = ' ';//show instructions or continue to game
    int x = 0;//first coordinate on gameboard 
    int y = 0;//second coordinate on gameboard 
    int over = gameOver(moves);//checks if game is over    
    int free = 1;//will use this to represent if the space is free with freeSpace
    time_t t;//used for seeding random
    srand((unsigned) time(&t));//seed random
    
    //provide instructions to the user for using our game
    //Requires user to input the c character to continue with the game
    do
    { 
        printInstructions();
        needInstructions = getchar();
        
        //clears the keyboard buffer, their is a newline character present in the stream after hitting enter.
        //This will be picked up on the next iteration of the loop, messing up the input.
        while (getchar() != '\n'); 
        
    }
    while(needInstructions != 'c');       
    
    //loop until the game is over
    while(!over)
    {
        //loop through random computer moves unitl a valid move is chosen
        do
        {
            x = rand() % 3;
            y = rand() % 3;
            free = freeSpace(moves, x, y);         
        }
        while(!free);
        
        //Set moves to include computers choice
        moves[x][y] = 'X';
        free = 1;//reset to a valid move, as not choices for player are made yet
        //show the current board to the player
        over = gameOver(moves);
        if(over)
        {
            break;
        }
        printBoard(moves);
        
        //loop until a free space is chosen
        do
        {          
            //free was reset to true on first pass, this will pass on subsequent passes if user makes invalid selections
            if(!free)
            {
                printBoard(moves);
                printf("You did not choose an empty space!\n");       
            }
            
            //Prompt the user for input, take users input, and check is the space is free
            printf("\n\nEnter your moves:  ");
            scanf_s("%d %d", &x, &y);
            free = freeSpace(moves, x, y);
                            
        }
        while(!free);
        
        moves[x][y] = 'O';
        
        over = gameOver(moves);           
    }    
       
}