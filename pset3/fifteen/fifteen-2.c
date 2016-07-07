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

//location of empty tile
int empty_tile_x;
int empty_tile_y;

//location of normal tile
int tile_x;
int tile_y;

// prototypes
void clear(void);
void greet(void);
void init(void);
void draw(void);
bool move(int tile);
bool won(void);

bool isEven(int n);
void swap(int x1, int y1, int x2, int y2);
bool search(int tile);
bool isAdjacent(int tile);

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
    FILE* file = fopen("log-2.txt", "w");
    if (file == NULL)
    {
        return 3;
    }

    // greet user with instructions
    greet();

    // initialize the board
    init();
    
    // debug
    /*
    int test = 2;
    if(isAdjacent(test)){
        printf("location of %d is [%d, %d]\n", test, tile_x, tile_y);
        printf("%d is adjacent to empty tile\n", test);
    }
    else{
        printf("location of %d is [%d, %d]\n", test, tile_x, tile_y);
        printf("%d is not adjacent to empty tile\n", test);
    }
    */
    
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
    
    empty_tile_x = d-1;
    empty_tile_y = d-1;
    
    //if odd number of tiles(even number dimension)
    if(isEven(d)){
        //swap "1" and "2"
        swap(d-1,d-2,d-1,d-3);
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
            if(board[i][j] == EMPTY_TILE){
                //printf("%2c ", board[i][j]);
                printf("%2c ", EMPTY_TILE);
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
    /**
     * A legal move is any tile that is adjacent to the empty tile
    */
    int temp1 = 0;
    int temp2 = 0;
    if(isAdjacent(tile)){
        // allow moving
        // 1. swap the empty tile and tile
        swap(empty_tile_x,empty_tile_y, tile_x,tile_y);
        // 2. update the location of empty tile and normal tile
        temp1 = empty_tile_x;
        temp2 = empty_tile_y;
        empty_tile_x = tile_x;
        empty_tile_y = tile_y;
        tile_x = temp1;
        tile_y = temp2;
        
        return true;
    }
    return false;
}

/**
 * Returns true if game is won (i.e., board is in winning configuration), 
 * else false.
 */
bool won(void)
{
    // TODO
    int i;
    int j;
    //int number_in_place = 1;
    ///* this is used when the EMPTY_TILE is set as '_'(or ASCII 95)
    for(i = 0; i< d; i++){
        for(j = 0; j<d-1; j++){
            if(board[i][j] > board[i][j+1]||
            board[j][i] > board[j+1][i]){
                return false;        
            }
        }
    }
    if(empty_tile_x == d-1 && empty_tile_y == d-1){
         return true;
    }
    
    return false;
}

/**
 * return true if the number is even,
   false otherwise.
**/
bool isEven(int n)
{
    return (n % 2 == 0);
}

/** 
 * this function swaps the two numbers in 2-D array
 * with corrdinate (x1, y1) and (x2,y2)
**/
void swap(int x1, int y1, int x2, int y2)
{
    int temp = board[x1][y1];
    board[x1][y1] = board[x2][y2];
    board[x2][y2] = temp;
}
/**
 * search for a tile, explicitly return true if found
 * it, false otherwise. Implicitly return the location
 * of the tile by passing the indices to tile_x and tile_y
**/
bool search(int tile)
{
    int i = 0;
    int j = 0;
    
    for(i = 0; i<d; i++){
        for(j = 0; j<d; j++){
            if(board[i][j] == tile){
                tile_x = i;
                tile_y = j;
                return true;
            }
        }
    }
    return false;
}

/**
 * check whether a tile is adjacent to empty tile
 * return true if it is, false otherwise.
**/
bool isAdjacent(int tile)
{
    // not found the prescribed tile
    if(!search(tile)){
        return false;    
    }
    else{
        //compare the location of tile and location of empty tile
        if((abs(tile_x - empty_tile_x) == 1 && tile_y == empty_tile_y)||
           (abs(tile_y - empty_tile_y) == 1 && tile_x == empty_tile_x)){
            // adjacent
            return true;
        }
    }
    return false;
}