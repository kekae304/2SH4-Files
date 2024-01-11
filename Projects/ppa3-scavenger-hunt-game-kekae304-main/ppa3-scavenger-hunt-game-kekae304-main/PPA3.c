#include <stdio.h>
#include "MacUILib.h"
#include "myStringLib.h" // This is your first custom C library

// [TODO] Import the required library for rand() and srand()
#include <stdlib.h>

// [TODO] Import the required library for accessing the current time - for seeding random number generation
#include <time.h>

// PREPROCESSOR DIRECTIVE CONSTANTS
// ================================
// For program-wide constants, define them here using #define.  Add as seen needed.
const char *desiredString = "McMaster-ECE"; // declaring the constant string for "McMaster-ECE" -> a constant pointer to a string
char *mysteryString;                        // declaring the mystery string and allocating it on the heap

// [COPY AND PASTE FROM PPA2] Copy your additional preprocessor constants from PPA2 and paste them below
#define Height 10
#define Width 20

// GLOBAL VARIABLE DEFINITION HERE
/////////////////////////////////////////
int moveCount = 0; // initializing a varibale for the move counter
int exitFlag;      // initializing an exit flag
char cmd;          // declaring a variable that will store an input
const int listSize = 5; //constant integer for listSize

struct objPos // defining a structure for object position
{
    int x;       // initializing a variable for the x-coordinate
    int y;       // initializing a variable for the y-coordinate
    char symbol; // initializing a variable for the player symbol
};
struct objPos player;     // declaring a variable instance for the structure
struct objPos itemBin[5]; // declaring an array of the strucutre of size 5

enum FSMMode
{
    StartPos,
    UP,
    DOWN,
    LEFT,
    RIGHT
};                      // defining enumeration type with the set of constants within
enum FSMMode myFSMMode; // declares a variable that holds one of the values in the enumeration

// FUNCTION PROTOTYPES
// ================================
// Declare function prototypes here, so that we can organize the function implementation after the main function for code readability.
void Initialize(void);
void GetInput(void);
void RunLogic(void);
void DrawScreen(void);
void LoopDelay(void);
void CleanUp(void);

// [TODO] In PPA3, you will need to implement this function to generate random items on the game board
//        to set the stage for the Scavenger Hunter game.
// list[]       The pointer to the Item Bin
// listSize     The size of the Item Bin (5 by default)
// playerPos    The pointer to the Player Object, read only.
// xRange       The maximum range for x-coordinate generation (probably the x-dimension of the gameboard?)
// yRange       The maximum range for y-coordinate generation (probably the y-dimension of the gameboard?)
// str          The pointer to the start of the Goal String (to choose the random characters from)
void GenerateItems(struct objPos list[], const int listSize, const struct objPos *playerPos, const int xRange, const int yRange, const char *str);

// MAIN PROGRAM
// ===============================
int main(void)
{

    Initialize();

    while (!exitFlag)
    {
        GetInput();

        RunLogic();

        DrawScreen();

        LoopDelay();
    }

    CleanUp();
}

// INITIALIZATION ROUTINE
// ===============================
void Initialize(void)
{
    MacUILib_init();
    MacUILib_clearScreen();

    // [COPY AND PASTE FROM PPA2] Copy your initialization routine from PPA2 and paste them below
    cmd = 0;              // setting the input command to 0
    myFSMMode = StartPos; // assigning StartPos to myFSMMode
    player.x = 5;         // assigning a value of 5 to the x of player
    player.y = 10;        // assigning a value of 10 to the y of player
    player.symbol = '@';  // assigning a symbol of @ for the player

    // [TODO] Initialize any global variables as required.
    exitFlag = 0; // 0 - do not exit, non-zero - exit the program

    // [TODO] Allocated heap memory for on-demand variables as required.  Initialize them as required.
    mysteryString = (char *)malloc(my_strlen(desiredString) + 1); // allocating memory for the mystery string and making it the same size as our desired string

    if (mysteryString != NULL) // check to see if the allocation was succesful
    {
        int i = 0;
        for (i; i < my_strlen(desiredString); i++) // creating a for loop for that will iterate through all items in the string but the last
        {
            mysteryString[i] = '?'; // making item 'i' of list, a '?'
        }
        mysteryString[i] = '\0'; // null-terminating the mystery string
    }

    // [TODO] Seed the random integer generation function with current time.
    srand(time(NULL)); // seeding the random number generator with the current time -> ensures the randomness

    // [TODO] Generate the initial random items on the game board at the start of the game.
    GenerateItems(itemBin, listSize, &player, Width, Height, desiredString); 
}

// INPUT COLLECTION ROUTINE
// ===============================
void GetInput(void)
{

    // Asynchronous Input - non blocking character read-in

    // [COPY AND PASTE FROM PPA2] Copy your input collection routine from PPA2 and paste them below

    if (MacUILib_hasChar())
    {
        cmd = MacUILib_getChar();
    }

    // [TODO] Though optional for PPA3, you may insert any additional logic for input processing.
}

// MAIN LOGIC ROUTINE
// ===============================
void RunLogic(void)
{
    // [COPY AND PASTE FROM PPA2] Copy your main logic routine from PPA2 and paste them below
    switch (myFSMMode)
    {
    case StartPos:
    default:
        player.x = Width / 2;
        player.y = Height / 2;

        if (cmd == 'w')
        {
            myFSMMode = UP;
        }

        if (cmd == 's')
        {
            myFSMMode = DOWN;
        }

        if (cmd == 'a')
        {
            myFSMMode = LEFT;
        }

        if (cmd == 'd')
        {
            myFSMMode = RIGHT;
        }

        break;

    case LEFT:
        moveCount++;
        player.x--;

        if (cmd == 'w')
        {
            myFSMMode = UP;
        }

        if (cmd == 's')
        {
            myFSMMode = DOWN;
        }

        break;

    case RIGHT:
        moveCount++;
        player.x++;

        if (cmd == 'w')
        {
            myFSMMode = UP;
        }

        if (cmd == 's')
        {
            myFSMMode = DOWN;
        }

        break;

    case UP:
        moveCount++;
        player.y--;

        if (cmd == 'a')
        {
            myFSMMode = LEFT;
        }

        if (cmd == 'd')
        {
            myFSMMode = RIGHT;
        }

        break;

    case DOWN:
        moveCount++;
        player.y++;

        if (cmd == 'a')
        {
            myFSMMode = LEFT;
        }

        if (cmd == 'd')
        {
            myFSMMode = RIGHT;
        }

        break;
    }

    if (cmd != 0)
    {
        switch (cmd)
        {
        case 27:
            exitFlag = 1;
            break;

            // Add more key processing here
            // Add more key processing here
            // Add more key processing here

        default:
            break;
        }
        cmd = 0;
    }

    if (player.x < 1)
    {
        player.x = Width - 2;
    }

    if (player.x >= Width - 1)
    {
        player.x = 1;
    }

    if (player.y < 1)
    {
        player.y = Height - 2;
    }

    if (player.y >= Height - 1)
    {
        player.y = 1;
    }

    // [TODO]   Implement the Object Collision logic here
    //
    //      Simple Collision Algorithm
    //      1. Go through all items on board and check their (x,y) against the player object x and y.
    //      2. If a match is found, use the ASCII symbol of the collided character, and
    //         find all the occurrences of this ASCII symbol in the Goal String
    //      3. For every occurrence, reveal its ASCII character at the corresponding location in the
    //         Collected String
    //      4. Then, determine whether the game winning condition is met.

    for (int i = 0; i < listSize; i++) //creating a for loop to iterate through the items in the itemBin array
    {
        if (player.x == itemBin[i].x && player.y == itemBin[i].y) //checking if the coordinates of the player's position 
                                                                  //and the coordinates of the current item in the bin match 
        {
            for (int j = 0; j < my_strlen(desiredString); j++) //iterating through the items in the desired string
            {
                if (itemBin[i].symbol == desiredString[j]) //checking to see if they symbol matches the desired string 
                {
                    mysteryString[j] = desiredString[j]; //if so, updating the matched character
                }
            }
            GenerateItems(itemBin, listSize, &player, Width, Height, desiredString); //when an item is found, regengerating new items 
        }
    }

    // [TODO]   Implement Game Winning Check logic here
    //
    //      Game Winning Check Algorithm
    //      1. Check if the contents of the Collected String exactly matches that of the Goal String.
    //         YOU MUST USE YOUR OWN my_strcmp() function from Lab 3.
    //      2. If matched, end the game.
    //      3. Otherwise, discard the current items on the game board, and
    //         generate a new set of random items on the board.  Game continues.
    if (my_strcmp(mysteryString, desiredString) == 1) //checking if the strings are identical
    {
        exitFlag = 1; //exiting the game
    }
}
// DRAW ROUTINE
// ===============================
void DrawScreen(void)
{

    // [COPY AND PASTE FROM PPA2] Copy your draw logic routine from PPA2 and paste them below
    MacUILib_clearScreen();

    for (int i = 0; i < Height; i++) //creating a for loop to iterate through each row
    {
        for (int n = 0; n < Width; n++) //creating a for loop to iterate through each coloumn
        {
            if (i == 0 || i == Height - 1) //drawing the vertical boundaries (top and bottom)
            {
                printf("#");
            }

            else if (n == 0 || n == Width - 1) //drwaing the horizontal boundaries (left and right)
            {
                printf("#");
            }

            else if (i == player.y && n == player.x) //drawing the player sybol at the coordinates 
            {
                printf("%c", player.symbol);
            }

            else
            {
                int itemFound = 0; //initializing a variable for itemFound
                for (int j = 0; j < listSize; j++) //creating a for loop to iterate through each item in itemBin
                {
                    if (itemBin[j].x == n && itemBin[j].y == i) //checking if the item's cooridnates match the
                                                                //the current position of the loop
                    {
                        printf("%c", itemBin[j].symbol); //print the the symbol
                        itemFound = 1; //set flag to 1
                        break; //break out of loop
                    }
                }

                if (!itemFound) //cheaking if there is no item
                {
                    printf(" "); //printing an empty space 
                }
            }
        }
        printf("\n"); //moving to the next line
    }
    // [TODO]   Insert somewhere in the draw routine to draw the randomly generated items on the board.

    // [TODO]   Display the "Mystery String" contents at the bottom of the game board
    //          To help players keep track of their game progress.
    printf("Mystery String: %s\n", mysteryString); //printing the mystery string contents 
    printf("Move Count: %d\n", moveCount); //printing the move counter

    if (my_strcmp(mysteryString, desiredString) == 1) //checking if the strings are indentical
    {
        printf("You have won the game!"); //print statement declaring victory
    }
}

// DELAY ROUTINE
// ===============================
void LoopDelay(void)
{
    MacUILib_Delay(100000); // 0.1s delay
}

// TEAR-DOWN ROUTINE
// ===============================
void CleanUp(void)
{
    // [TODO]   To prevent memory leak, free() any allocated heap memory here
    //          Based on the PPA3 requirements, you need to at least deallocate one heap variable here.
    
    free(mysteryString); //freeing our mysteryString

    // Insert any additional end-game actions here.
    MacUILib_uninit();
}

// The Item Generation Routine
////////////////////////////////////
void GenerateItems(struct objPos list[], const int listSize, const struct objPos *playerPos, const int xRange, const int yRange, const char *str)
{
    // This is possibly one of the most conceptually challenging function in all PPAs
    // Once you've mastered this one, you are ready to take on the 2SH4 course project!

    // Random Non-Repeating Item Generation Algorithm
    ////////////////////////////////////////////////////

    // Use random number generator function, rand(), to generate a random x-y coordinate and a random choice of character from the Goal String as the ASCII character symbol.
    //      The x and y coordinate range should fall within the xRange and yRange limits, which should be the x- and y-dimension of the board size.
    // This will then be a candidate of the randomly generated Item to be placed on the game board.

    // In order to make sure this candidate is validated, it needs to meet both criteria below:
    //  1. Its coordinate and symbol has not been previously generated (no repeating item)
    //  2. Its coordinate does not overlap the Player's position
    // Thus, for every generated item candidate, check whether its x-y coordinate and symbol has previously generated.
    //  Also, check if it overlaps the player position
    //      If yes, discard this candidate and regenerate a new one
    //      If no, this candidate is validated.  Add it to the input list[]

    // There are many efficient ways to do this question
    //  We will take a deep dive into some methods in 2SI.

    int used[xRange][yRange]; //declaring a 2D array to keep track of the used coordinates 
    int desiredStringLength = my_strlen(desiredString); //calculating the length of the desired string

    for (int i = 0; i < listSize; ++i) //creating a for loop to iterate through each item in the list
    {
        while (1) //creating an infinite loop to allow us to generate an item
        {
            int xPotential = (rand() % (xRange - 2)) + 1; //generating a random x coordinate within our range 
            int yPotential = (rand() % (yRange - 2)) + 1; //generating a random y coordinate within our range

            if (xPotential == playerPos->x && yPotential == playerPos->y || used[xPotential][yPotential] == 1) 
            //a check to see whether the coordinate overlaps with the players' position or if its been used
            {
                continue; //if so, generate again 
            }
            int twoDesired; //initialing a variable to store random index from the desired string
            char twoDesiredCharacter; //declaring a character that will hold our symbol from the desired string

            if (i < 2) //choosing first two character from the desired string
            {
                twoDesired = rand() % desiredStringLength; //finding random index from desired string
                twoDesiredCharacter = desiredString[twoDesired]; //storing the symbol from the random index point in the desired string
                list[i].symbol = twoDesiredCharacter; //assining the random desired symbol to the current item symbol
            }
            else //after we have acquired two characters from the desired string
            {
                do //choosing the remaining three characters from the ASCII range in the PPA document (33-126)
                {
                    int randomCharacter = (rand() % (126 - 33 + 1)) + 33; //finding a random ASCII character between the values of 33 and 126
                                                   //closed range formula = b - a + 1 where b is upper bound and a is lower bound. 
                                                   //(+33 shifts the range from 0-93 to 33-126)
                    list[i].symbol = (char)randomCharacter; //assigning the random character to the current item symbol 
                } while (list[i].symbol == playerPos->symbol || list[i].symbol == ' ' || list[i].symbol == '#'); //omiting the player symbol, empty character, and border symbol
            }
            list[i].x = xPotential; //assigning random x coordiante to ith item in list
            list[i].y = yPotential; //assigning random y coordinate to ith item in list
            used[xPotential][yPotential] = 1; //marks our coordinate as used in the array
            break; //exiting the infinite loop
        }
    }
}
