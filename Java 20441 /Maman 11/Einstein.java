import java.util.Scanner;
/**
 * this program is playing the Einstein game.
 * Maman11 Q2
 * @author Orel Briantsev

 */

public class Einstein
{
    public static void main (String [] args)
    {
        final int HUNDRED=100;
        final int TEN=10;
        final int success=1089;
        Scanner scan =new Scanner (System.in);
        System.out.println("Welcome to the Einstein magic game");
        System.out.println("Please enter a 3 digit positive number whose first and last digits are different:");
        int num = scan.nextInt();
        int hundreds=num/HUNDRED; //gives us the number of hundreds
        int newNum=num%HUNDRED; //substract number of hundreds from num
        int tens=newNum/TEN; //gives the number of tens
        int units=newNum%TEN;//gives the number of units
        if(num<0 ||num<100|| num>999){
            System.out.print("The number you entered is not a 3 digit positive number\n");
            return;
        }
        if(hundreds == units)
        {
            System.out.print("The first and the last digits of the number should be different\n");
            return;
        }
        System.out.println("User number is:"+num);
        int revNum=(units * HUNDRED)+(tens * TEN) + hundreds;//recersed num.if num=123 revNum=321
        int diffNum=Math.abs(num-revNum);//absoulte value of thedifference between num and rev num.diffnum:321-123=198
        System.out.println("Difference:"+diffNum);
        int dHundreds=diffNum/HUNDRED; //same as with num
        int dNewNum=diffNum%HUNDRED; 
        int dTens=dNewNum/TEN; 
        int dUnits=dNewNum%TEN; 
        int revDiff =(dUnits * HUNDRED)+(dTens * TEN)+ dHundreds;//difference revered num.revDiff:891
        System.out.println("Reversed Difference:"+revDiff);

        if((revDiff+diffNum) == success)//891+198=1089
            System.out.println("SUCCEEDED");//if recDiff+diffNum=1089 then success
        else
            System.out.println("FAILED"); //else failed

    }
}
