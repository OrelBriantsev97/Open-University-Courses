
/**
 * 2021a
 * @orel briantsev 
 */
public class Ex14
{
    /**
     * this method returns the minimum diffrence between two given numbers
     * @param int[] a represent the given array
     * @param x is one of the two given numbers.
     * @param y is one of the two given numbers.
     * Time complexity O(n) - findMinDiff going through one loop only.
     * Space complexity O(1)-no array just instance variables.
     */
    public static int findMinDiff (int[] a, int x, int y)
    {
        int diff=Integer.MAX_VALUE;
        int minDiff=0;
        int preX=-1;//previus index of x
        int preY=-1;//previoues index of y
        for (int i=0;i<a.length;i++)
        {
            if(a[i]==x)
            {
                if(preY>=0)
                {
                    minDiff= i-preY;
                    diff=Math.min(diff,minDiff);
                }
                preX=i;
            }

            if(a[i]==y)
            {
                if(preX>=0)
                {
                    minDiff=i-preX;
                    diff=Math.min(diff,minDiff);
                }
                preY=i;
            }
        }
        return diff;
    }
    
       /**
     * this method returns true if the number is found in the matrix,return false if not.
     * @param int[][] mat represent the given matrix.
     * @param num the given number.
     * Time complexity O(logn) - using sort of binary search (using the given matrix attributes).
     * Space complexity O(1)-no array just instance variables.
     */
    public static boolean search (int [][] mat, int num)
    {
        int arrayLength=mat.length;
        int i=0;
        int j=0;
        int whichQuarter=-1;
        //checking if num is smaller then the smallest number in the matrix and is num is bigger then the bigest number in the matrix.
        //if so - we will return false because num is not in the matrix.

        if(num<mat[0][0]||num>mat[arrayLength-1][0])
            return false;
        while(arrayLength>1)
        {
            int max1=mat[(arrayLength/2)-1+i][j];
            int max2=mat[(arrayLength/2)-1+i][(arrayLength/2)+j];
            int max3=mat[(arrayLength-1)+i][(arrayLength/2)+j];
            int max4=mat[(arrayLength-1)+i][j];

            if(num>max1)//the num should be found in the second quarter,third or fourth quarter.
            {
                if(num>max2)
                {
                    if(num>max3)//the num should be found in the 4th quarter
                    {
                        j=0;
                        i=(arrayLength/2);
                        whichQuarter=4;
                    }
                    else //the num should be found in the 3th quarter
                    {
                        j=(arrayLength/2);
                        i=(arrayLength/2);
                        whichQuarter=3;
                    }
                } 
                else
                {
                    j=(arrayLength/2);
                    i=0;
                    whichQuarter=2;
                }
            }
            else//the num should be found in the first quarter
            {
                i=i;
                j=j;
                whichQuarter=1;
            }
            arrayLength=arrayLength/2;
        }
        arrayLength=(mat.length/2)-1;
        if(whichQuarter==1 && num == mat[i][j])
            return true;

        if(whichQuarter==2 && num == mat[arrayLength+i][arrayLength+j])
            return true;

        if(whichQuarter==3 && num == mat[arrayLength+i][arrayLength+j])

            return true;

        if(whichQuarter==4 && num == mat[i+arrayLength][j])
            return true;
        return false;
    }

      /**
     * this method returns true if 2 groups of with the same sum can be found in the given array,using every cell(arr[i])
     * this method using a private method with variables that helps count and summerize all the cells.
     * @param int[] a represent the given array
     * @param i represent the location in the array
     * @param counter1 is the counter of group number 1 - used to count number of numbers that are in the sum.
     * @param counter2 same as counter1 but for group number 2
     * @param sum1 represents total sum of group 1
     * @param sum2 represents total sum of group 2
     */
    public static boolean equalSplit (int[] arr)
    {
        return equalSplit(arr,0,0,0,0,0);
    }

    private static boolean equalSplit(int[] arr,int i,int counter1,int counter2,int sum1,int sum2)
    {
        if(i==arr.length)
            if(sum1==sum2 && counter1 == counter2 &&sum1!=0 && counter1!=0)
                return true;
            else
                return false;
        return equalSplit(arr,i+1,counter1+1,counter2,sum1+arr[i],sum2) || equalSplit(arr,i+1,counter1,counter2+1,sum1,sum2+arr[i]);
    }

       /**
     * this method returns true if the given number is a special number or not using recursion.
     * this method using private method in order to check maman's requirements.
     * @param n - the given number (to check if special)
     * @param num - using for calculating the next numbers that would be deleted.
     */
    public static boolean isSpecial (int n)
    {
        return isSpecial(n,1);
    }

    private static boolean isSpecial(int n , int num)
    {
        if(n<num+1)
            return true;//if the given number is smaller than num+1 then the number is a special number.

        if(n%(num+1)==0)//if the number is a multiplation of num+1 then it will be deleted and not a special number.
            return false;
        return isSpecial(n-(n/(num+1)),num+1); 
    }
}

