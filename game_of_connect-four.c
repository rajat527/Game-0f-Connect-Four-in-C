#include <stdio.h>

#define ROWS    6
#define COLS    7
#define FOUR    4

char scores[ROWS][COLS];
char header[] = "  1   2   3   4   5   6   7  ";
char horbar[] = "|---|---|---|---|---|---|---|";
int bin = 0;
char disc = 'r';

void init_scores();
void test_scores();
void board();
void choose();
void fill_bin();
int check(char disc);

/* main function start */

main()
{
    init_scores();
    test_scores();
    board();
    
    while (1)
    {   if(disc=='r'){
        printf("player 1, ");
    }
    else{
        printf("player 2, ");
    }
        choose();
        printf("\n\n");
        board();
        if (check('r'))
        {
            printf("\n\nPlayer 1 wins! \n\n");
            break;  
        }
        if (check('y'))
        {
            printf("\n\nPlayer 2 wins!\n\n");
            break;  
        }   
    }
    
    return 0; 
}

/* helper functions      */

void init_scores()
{
    // fill the scores with the empty character:
    int i, j;
    
    for (i = 0; i < ROWS; i++)
    {
        for (j = 0; j < COLS; j++)
        {
            scores[i][j] = ' ';
        }
    }
}

void test_scores()
{
    // print the initialized scores, no board is printed yet:
    int i, j;
    
    for (i = 0; i < ROWS; i++)
    {
        for (j = 0; j < COLS; j++)
        {
            printf("%c ", scores[i][j]);
        }
        printf("\n");
    }
}

void board()
{
    // print the board and the scores according to current game:
    printf("%s\n", header);
    printf("%s\n", horbar);
    
    int i, j;
    
    for (i = 0; i < ROWS; i++)
    {
        for (j = 0; j < COLS; j++)
        {
            printf("| %c ", scores[i][j]);
        }
        printf("|\n");
        printf("%s\n", horbar);
    }
}

void choose()
{
    // choose 1 2 3 4 5 6 7:
    char c;
    
    while (1)
    {
        printf("\nWhat column do you want to put your piece(1-7)? ");
        scanf(" %c", &c);
        switch(c)
        {
            case '1':
                bin = 0;
                break;
            case '2':
                bin = 1;
                break;
            case '3':
                bin = 2;
                break;
            case '4':
                bin = 3;
                break;
            case '5':
                bin = 4;
                break;
            case '6':
                bin = 5;
                break;
            case '7':
                bin = 6;
                break;
            default:
                bin = 666;
                printf("\nWrong letter! Try again.\n\n");
                board();
        }
        // break out of while loop if the right letter was chosen:
        if ((bin >= 0 && bin <= 6) && (scores[0][bin] == ' '))
        {
            fill_bin();
            disc = (disc == 'r') ? 'y' : 'r';
            break;
        }
    }
}

void fill_bin()
{
    // fills the bin according to what's already in there:
    int level ;     /* lowest level or bottom of the board */

    for (level = ROWS-1; level >= 0; level--)
    {
        if (scores[level][bin] == ' ')
        {
            scores[level][bin] = disc;
            break;
        }   
    }               
}

int check(char disc)
{
    // checks for a 4-disc row, column or diagonal:
    
    
    /* check for 4-disc rows
    each row has 4 different ways to connect 4
    
    | r | r | r | r |   |   |   |
    |   | r | r | r | r |   |   |
    |   |   | r | r | r | r |   |
    |   |   |   | r | r | r | r |
    
     */
     
    int i, j, k;
    int count;
    int ways = 4;
    
    for (i = 0; i < ROWS; ++i)
    {
        for (j = 0; j < ways; ++j)
        {
            count = 0;
            for (k = 0; k < FOUR; ++k)
            {
                if (scores[i][j + k] == disc) count++;
            }
            if (count == FOUR) return 1;
        }
    }
    
    
    /* check for 4-disc columns 
    each column has 3 different ways to connect 4 
    
    | r |   |   |
    | r | r |   |
    | r | r | r |
    | r | r | r |
    |   | r | r |
    |   |   | r |
    
    */
    
    ways = 3;
    
    for (j = 0; j < COLS; ++j)
    {
        for (i = 0; i < ways; ++i)
        {
            count = 0;
            for (k = 0; k < FOUR; ++k)
            {
                if (scores[i + k][j] == disc) count++;
            }
            if (count == FOUR) return 1;
        }
    }
    
    /* check for 4-disc diagonals 
    
      1 2 3 4 5 6 7
    0| | | | | | | |
    1| |\|\|\|\|\| |
    2| |\|\|\|\|\| |
    3| |\|\|\|\|\| |
    4| |\|\|\|\|\| |
    5| | | | | | | |
    
    */
    
    int ii, jj;
    for (i = 1; i < ROWS-1; i++)
    {
        for (j = 1; j < COLS-1; j++)
        {
            
            /* left-tilted diagonals */
            count = 0;
            // left-upwards:
            for (ii = i, jj = j; (ii >= 0) || (jj >= 0); ii--, jj--)
            {
                if (scores[ii][jj] == disc)
                {
                    count++;
                    if (count == FOUR) return 1;    
                }
                else
                    break;
            }
            // right-downwards:
            for (ii = i+1, jj = j+1; (ii <= ROWS-1) || (jj <= COLS-1); ii++, jj++)
            {
                if (scores[ii][jj] == disc)
                {
                    count++;
                    if (count == FOUR) return 1;
                }
                else
                    break;
            }
            
            /* right-tilted diagonals */
            count = 0;
            // left-downwards:
            for (ii = i, jj = j; (ii <= ROWS-1) || (jj >= 0); ii++, jj--)
            {
                if (scores[ii][jj] == disc)
                {
                    count++;
                    if (count == FOUR) return 1;    
                }
                else
                    break;
            }
            // right-upwards:
            for (ii = i-1, jj = j+1; (ii >= 0) || (jj <= COLS-1); ii--, j++)
            {
                if (scores[ii][jj] == disc)
                {
                    count++;
                    if (count == FOUR) return 1;
                }
                else
                    break;
            }
            
        }
    }

    return 0;       
}
