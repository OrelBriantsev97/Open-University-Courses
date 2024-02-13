/*containes all the functions that prints massage to user*/

#include "magic.h"


/*
stops the program fron running and printing an error massage in the following cases:
-- the numbers in the matrix is not an integer.
-- matrix containes less/more then N*N values.
*/

bool stopProg( int matrix[N][N],int counter)
{
    if(counter>N*N)/*recive more then N*N values.*/
    { 
        printf("\n****************************************\n");
        printf("ERROR: More then %d values were entered.\n",N*N);
        printf("****************************************\n");
        return true;
    }
       
    else if(counter<N*N)/*recived less then N*N values.*/
    { 
        printf("\n***************************************\n");
        printf("ERROR.less then %d values were entered\n",N*N);
        printf("***************************************\n");
        return true;

    }
    return false;
}

void printMatrix(int matrix[N][N],bool isMagicSquare)
{
    int row,column;
    for(row=0;row<N;row++)
    {
        printf("\n");
        for(column=0 ;column<N; column++)
            printf("%d\t",matrix[row][column]);
    }
    printf("\n");
    printf("***********************************\n");
    if(isMagicSquare==true)
        printf("This Square Is a Magic Square \n");
    else
        printf("This Square Is Not A Magic Square \n");
    printf("***********************************\n");
}



