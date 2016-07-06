/**
 * fifteen.c
 *
 * Computer Science 50
 * Problem Set 3
 *
 * Implements Game of Fifteen (generalized to d x d).
 *
 * Usage: fifteen d
 *
 * whereby the board's dimensions are to be d x d,
 * where d must be in [DIM_MIN,DIM_MAX]
 *
 * Note that usleep is obsolete, but it offers more granularity than
 * sleep and is simpler to use than nanosleep; `man usleep` for more.
 */
 
#define _XOPEN_SOURCE 500

#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// constants
#define DIM_MIN 3
#define DIM_MAX 9

/* ASCII value of underscore
 * Since the max dimension is 9, the largest
 number involved will be only 80, hence it is
 safe to choose 95.
**/
#define EMPTY_TILE '_'

// board
int board[DIM_MAX][DIM_MAX];

// dimensions
int d;

// prototypes
void clear(void);
void greet(void);
void init(void);
void draw(void);
bool move(int tile);
bool won(void);

/**
 * return true if the number is even,
   false otherwise.
**/
bool isEven(int n);
/** this function swaps the two numbers indexed by index 1
 * and index 2, located in the last row of a TWO_dimensional
   array.
**/
void swap(int index1, int index2);

int main(int argc, string argv[])
{
    // ensure proper usage
    if (argc != 2)
    {
        printf("Usage: fifteen d\n");
        return 1;
    }

    // ensure valid dimensions
    d = atoi(argv[1]);
    if (d < DIM_MIN || d > DIM_MAX)
    {
        printf("Board must be between %i x %i and %i x %i, inclusive.\n",
            DIM_MIN, DIM_MIN, DIM_MAX, DIM_MAX);
        return 2;
    }

    // open log
    FILE* file = fopen("log.txt", "w");
    if (file == NULL)
    {
        return 3;
    }

    // greet user with instructions
    //greet();

    // initialize the board
    init();

    // accept moves until game is won
    while (true)
    {
        // clear the screen
        clear();

        // draw the current state of the board
        draw();

        // log the current state of the board (for testing)
        for (int i = 0; i < d; i++)
        {
            for (int j = 0; j < d; j++)
            {
                fprintf(file, "%i", board[i][j]);
                if (j < d - 1)
                {
                    fprintf(file, "|");
                }
            }
            fprintf(file, "\n");
        }
        fflush(file);

        // check for win
        if (won())
        {
            printf("ftw!\n");
            break;
        }

        // prompt for move
        printf("Tile to move: ");
        int tile = GetInt();
        
        // quit if user inputs 0 (for testing)
        if (tile == 0)
        {
            break;
        }

        // log move (for testing)
        fprintf(file, "%i\n", tile);
        fflush(file);

        // move if possible, else report illegality
        if (!move(tile))
        {
            printf("\nIllegal move.\n");
            usleep(500000);
        }

        // sleep thread for animation's sake
        usleep(500000);
    }
    
    // close log
    fclose(file);

    // success
    return 0;
}

/**
 * Clears screen using ANSI escape sequences.
 */
void clear(void)
{
    printf("\033[2J");
    printf("\033[%d;%dH", 0, 0);
}

/**
 * Greets player.
 */
void greet(void)
{
    clear();
    printf("WELCOME TO GAME OF FIFTEEN\n");
    usleep(2000000);
}

/**
 * Initializes the game's board with tiles numbered 1 through d*d - 1
 * (i.e., fills 2D array with values but does not actually print them).  
 */
void init(void)
{
    //TODO
    int i;
    int j;
    int to_fill = d*d-1;
    
    for(i = 0; i<d; i++){
        for(j = 0; j<d; j++){
            board[i][j] = to_fill;
            to_fill--;
        }
    }
    //overwrite the last number with empty title character
    board[d-1][d-1] = EMPTY_TILE;
    
    //if odd number of tiles(even number dimension)
    if(isEven(d)){
        //swap "1" and "2"
        swap(d-2,d-3);
    }
    
}

/**
 * Prints the board in its current state.
 */
void draw(void)
{
    // TODO
    int i;
    int j;
    
    for(i = 0; i<d; i++){
        for(j = 0; j<d; j++){
            if(i == d-1 && j == d-1){
                printf("%2c ", board[i][j]);
            }
            else {
                printf("%2d ", board[i][j]);    
            }
        }
    printf("\n\n");
    }
}

/**
 * If tile borders empty space, moves tile and returns true, else
 * returns false. 
 */
bool move(int tile)
{
    // TODO
    return false;
}

/**
 * Returns true if game is won (i.e., board is in winning configuration), 
 * else false.
 */
bool won(void)
{
    // TODO
    return false;
}

bool isEven(int n)
{
    return (n % 2 == 0);
}

void swap(int index1, int index2)
{
    int temp = board[d-1][index1];
    board[d-1][index1] = board[d-1][index2];
    board[d-1][index2] = temp;
}