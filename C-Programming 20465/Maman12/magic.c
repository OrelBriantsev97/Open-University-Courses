/*this program recives N*N values from stdio and checks if the these values create a magic square*/

#include "magic.h"

int main()
{
    int matrix[N][N]={0};/*creating a matrix and initiating with zero's*/
    printf("**************************\n");
    printf("please enter %d numbers :\n",N*N);
    printf("**************************\n");
    getMatrix(matrix);

    return 1;
}

/*gets number from stdin and puts the number in the matrix according to row & column values.
  prog send matrix ad counter to isMagicSquare only if there are exactly N*N values.
  prog send counter to stopProg in the following cases:
  if getMatrix recive EOF in the middle of the loop
  if getMatrix recives more then N*N values.*/

void getMatrix(int matrix[N][N])
{ 
    int row,column,counter=0;
    int number;
    int stProg=0;/*indication for sending to stopProg function or not.*/
    int check,temp;/*check is for checking if more then N*N numbers were entered.*/
    for (row = 0; row < N; row++)
    {
        for (column = 0; column < N; column++)
        {
                number= scanf("%d",&matrix[row][column]);
                if(number != -1)
                    counter++;
                else
                {
                    stProg=-1;
                    column = N;
                    row = N;
                }      
        }                   
    }
    check = scanf("%d",&temp);/*if scanf will get an addional number then check = 1*/
        if(check != 1 && stProg != -1)
            isMagicSquare(matrix,counter);       
        else if(check == 1)
            stopProg(matrix,++counter);
	else
	    stopProg(matrix,counter);
}

/*checking if the given matrix is a magic square by sending the matrix to checkSum and isValid functions.
more information on how this functions are working is in checkSum and isValid documention*/
void isMagicSquare(int matrix[N][N],int counter)
{
    bool isMagicSquare=false;
    if(checkSum(matrix) && isValid(matrix,counter))
        isMagicSquare=true;
    
    printMatrix(matrix,isMagicSquare);
}




