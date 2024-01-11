#include <stdio.h>
#include "MacUILib.h"

// PPA2 GOAL: 
//       Construct the game backbone where the player can control an object 
//       to move freely in the game board area with border wraparound behaviour.

// Watch Briefing Video and Read Lab Manual before starting on the activity!

// PREPROCESSOR CONSTANTS DEFINITION HERE
/////////////////////////////////////////

#define Height 10
#define Width 20
#define FirstLevel 100000
#define SecondLevel 50000
#define ThirdLevel 25000
#define FourthLevel 10000
#define FifthLevel 5000

// GLOBAL VARIABLE DEFINITION HERE
/////////////////////////////////////////

int exitFlag;

// For storing the user input - from PPA1
char cmd;

// [TODO] : Define objPos structure here as described in the lab document
struct objPos
{
    int x; 
    int y; 
    char symbol; 
    int speed;
};

struct objPos player;
// [TODO] : Define the Direction enumeration here as described in the lab document
//          This will be the key ingredient to construct a simple Finite State Machine
//          For our console game backbone.

enum FSMMode {StartPos, UP, DOWN, LEFT, RIGHT};
enum FSMMode myFSMMode;
enum GameSpeed {One, Two, Three, Four, Five};
enum GameSpeed myGameSpeed;

// FUNCTION PROTOTYPING DEFINITION HERE
/////////////////////////////////////////

void Initialize(void);
void GetInput(void);
void RunLogic(void);
void DrawScreen(void);
void LoopDelay(void);
void CleanUp(void);

// You may insert additional helper function prototypes below.
// As a good practice, always insert prototype before main() and implementation after main()
// For ease of code management.

// MAIN PROGRAM LOOP
/////////////////////////////////////////
// This part should be intuitive by now.
// DO NOT TOUCH

int main(void)
{

    Initialize();

    while(!exitFlag)  
    {
        GetInput();

        RunLogic();

        DrawScreen();

        LoopDelay();
    }

    CleanUp();

}

// INITIALIZATION ROUTINE
/////////////////////////////////////////
void Initialize(void)
{
    MacUILib_init();
    MacUILib_clearScreen();

    cmd = 0; 
    exitFlag = 0;
   
    // [TODO] : Initialize more variables here as seen needed.
    //          PARTICULARLY for the structs!!

    myFSMMode = StartPos;
    myGameSpeed = One;
    player.x = 5;
    player.y = 10; 
    player.symbol = '@'; 
    player.speed = FirstLevel;

}

// INPUT PROCESSING ROUTINE
/////////////////////////////////////////
void GetInput(void)
{
    // [TODO] : Implement Asynchronous Input - non blocking character read-in    
    //          (Same as PPA1)
    if (MacUILib_hasChar())
    {
        cmd = MacUILib_getChar();
    }
}

// PROGRAM LOGIC ROUTINE
/////////////////////////////////////////
void RunLogic(void)
{
    // [TODO] : First, process the input by mapping
    //          WASD to the corresponding change in player object movement direction

    switch(myFSMMode)
    {
        case StartPos:
        default:
            player.x = Width / 2;
            player.y = Height / 2;
            
            if(cmd == 'w')
            {
                myFSMMode = UP;
            }
            
            if(cmd == 's')
            {
                myFSMMode = DOWN;
            }
            
            if(cmd == 'a')
            {
                myFSMMode = LEFT;
            }
            
            if(cmd == 'd')
            {
                myFSMMode = RIGHT;
            }  

            break;

        case LEFT:
            player.x--;
            
            if(cmd == 'w')
            {
                myFSMMode = UP;
            }

            if(cmd == 's')
            {
                myFSMMode = DOWN;
            }  
            
            break;

        case RIGHT:
            player.x++;

            if(cmd == 'w')
            {
                myFSMMode = UP;
            }

            if(cmd == 's')
            {
                myFSMMode = DOWN;
            } 

            break;

        case UP:
            player.y--;

            if(cmd == 'a')
            {
                myFSMMode = LEFT;
            }

            if(cmd == 'd')
            {
                myFSMMode = RIGHT;
            }  

            break;

        case DOWN:

            player.y++;

            if(cmd == 'a')
            {
                myFSMMode = LEFT;
            }

            if(cmd == 'd')
            {
                myFSMMode = RIGHT;
            }

            break;
    }   

    switch(myGameSpeed)
    {
        case One:
        default:

            player.speed = FirstLevel;
            
            if(cmd == '2')
            {
                myGameSpeed = Two;
            }

            if(cmd == '3')
            {
                myGameSpeed = Three;
            }
            
            if(cmd == '4')
            {
                myGameSpeed = Four;
            }
            
            if(cmd == '5')
            {
                myGameSpeed = Five;
            }
            
            break;

        case Two:

            player.speed = SecondLevel;
            
            if(cmd == '1')
            {
                myGameSpeed = One;
            }
            
            if(cmd == '3')
            {
                myGameSpeed = Three;
            }
            
            if(cmd == '4')
            {
                myGameSpeed = Four;
            }
            
            if(cmd == '5')
            {
                myGameSpeed = Five;
            }
            
            break;
        
        case Three:
            
            player.speed = ThirdLevel;
            
            if(cmd == '1')
            {
                myGameSpeed = One;
            }
            
            if(cmd == '2')
            {
                myGameSpeed = Two;
            }
            
            if(cmd == '4')
            {
                myGameSpeed = Four;
            }
           
            if(cmd == '5')
            {
                myGameSpeed = Five;
            }
            
            break;
        
        case Four:

            player.speed = FourthLevel;

            if(cmd == '1')
            {
                myGameSpeed = One;
            }

            if(cmd == '2')
            {
                myGameSpeed = Two;
            }

            if(cmd == '3')
            {
                myGameSpeed = Three;
            }

            if(cmd == '5')
            {
                myGameSpeed = Five;
            }
            
            break;

        case Five:

            player.speed = FifthLevel;

            if(cmd == '1')
            {
                myGameSpeed = One;
            }

            if(cmd == '2')
            {
                myGameSpeed = Two;
            }    

            if(cmd == '3')
            {
                myGameSpeed = Three;
            }

            if(cmd == '4')
            {
                myGameSpeed = Four;
            }

            break;

    }
   
    if (cmd != 0)
    {

        switch(cmd)
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
    // [TODO] : Next, you need to update the player location by 1 unit 
    //          in the direction stored in the program

    // [TODO] : Heed the border wraparound!!!
    
    if (player.x < 1)
    {
        player.x = Width-2;
    }

    if (player.x >= Width - 1)
    {
        player.x = 1;
    }

    if (player.y < 1)
    {
        player.y = Height-2;
    }

    if (player.y >= Height - 1)
    {
        player.y = 1;
    }
    
}

// SCREEN DRAWING ROUTINE
/////////////////////////////////////////
void DrawScreen(void)
{
    // [TODO] : Implement the latest drawing logic as described in the lab manual
    //
    //  1. clear the current screen contents
    MacUILib_clearScreen();
    //  2. Iterate through each character location on the game board
    //     using the nested for-loop row-scanning setup.

    //  3. For every visited character location on the game board
    //          If on border on the game board, print a special character
    //          If at the player object position, print the player symbol
    //          Otherwise, print the space character
    //     Think about how you can format the screen contents to achieve the
    //     same layout as presented in the lab manual

    //  4. Print any debugging messages as seen needed below the game board.
    //     As discussed in class, leave these debugging messages in the program
    //     throughout your dev process, and only remove them when you are ready to release
    //     your code. 

   for (int i = 0; i < Height; i++) 
   {   
        for (int n = 0; n < Width; n++)
        {
            if (i == 0 || i == Height - 1)
            {
                printf("#");
            } 

            else if (n == 0 || n == Width - 1)
            {
                printf("#");
            }

            else if (i == player.y && n == player.x)
            {
                printf("%c", player.symbol);
            } 

            else
            {
                printf(" ");
            }
        }
        printf("\n");
    }
    printf("\nSpeed: %d - (Press any number from 1 - 5 to change the game speed!)", player.speed);

}

// PROGRAM LOOOP DELAYER ROUTINE
/////////////////////////////////////////
void LoopDelay(void)
{
    MacUILib_Delay(player.speed);    
}

// PROGRAM CLEANUP ROUTINE
/////////////////////////////////////////
// Recall from PPA1 - this is run only once at the end of the program
// for garbage collection and exit messages.
void CleanUp(void)
{
    MacUILib_uninit();
}