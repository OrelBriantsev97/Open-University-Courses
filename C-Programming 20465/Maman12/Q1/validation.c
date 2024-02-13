/*containes all the functions that are checking user input according maman's requirment*/

#include "magic.h"

/*sending the matrix and the magic square sum to sumRowCol and sumDiagonal:
only if both of the method return true then return true*/
bool checkSum(int matrix[N][N])
{
    int magicSquareSum=(N*(pow(N,2)+1))/2;
    if(sumRowCol(matrix,magicSquareSum) && sumDiagonal(matrix,magicSquareSum))
        return true;
    else
       return false;
}
/*check if the sum of each row and column in the matrix are equale to Magic Square sum.
magic square formula is (N((N*N)+1))/2 */
bool sumRowCol (int matrix[N][N], int sum)
{
    bool sameSum = false;
   /*comparing the sum of each row with the magic square sum */
    int i,j;
    for (i=0;i<N;i++)
    {
        int sumR=0;
        for (j=0;j<N;j++)
        {
            sumR+= matrix[i][j];
        }
        if(sum  == sumR)
            sameSum=true;
        else if(sum  != sumR)
            return sameSum=false;
    }
    /*comparing the sum of each row with the magic square sum*/
    for(i=0;i<N;i++)
    {
        int sumC=0;
        for(j=0;j<N;j++)
            {
                sumC+=matrix[i][j];
            }
        if(sum == sumC)
            sameSum=true;
        else if(sum  != sumC)
            return sameSum=false;
    }
    return sameSum;
}
/*check if the sum of diagonal and anti diagonal are equale to Magic Square sum.
magic square formula is (N((N*N)+1))/2 */
bool sumDiagonal(int matrix[N][N],int sum)
{
    /*checking the diagonal sum*/
    int sumD=0,sumAD=0;
    bool sameSum=false;
    int i,j;
    for(i=0; i<N; i++)
    {
        for(j=0;j<N;j++)
        {
            if(i==j)
            {
                sumD+=matrix[i][j];
            }
        }
    }
    if (sum == sumD)
        sameSum=true;
    else if(sum != sumD)
        return sameSum=false;
    /*checking the anti diagonal sum*/
    
    for (i = 0; i < N; i++)
    {
        for ( j = 0; j < N; j++)
        {
            if(i + j == N-1)
                sumAD+=matrix[i][j];
        }
        
    }
    if (sum == sumAD)
        sameSum=true;
    else if(sum != sumAD)
        return sameSum=false;

    return sameSum;
}

/* 
checks if m[i][j] value is bigger then N*N or smaller then 1. if so - return false.
*/
bool isValid(int matrix[N][N],int counter)
{
    int row,column;
    bool valid=false;
    for(row = 0; row < N; row++)
    {
        for(column = 0; column < N; column++)
        {
            if(matrix[row][column] >=1 && matrix[row][column]<= N*N)
                valid=true;
        }
    }
    return valid;
            
}
