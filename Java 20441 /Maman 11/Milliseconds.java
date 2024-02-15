import java.util.Scanner;
/**
 * This program receives number from user that represents miliseconds and converts it to days,hours,minutes,seconds.
 * Maman11 Q1
 * @author Orel Briantsev ID:318264132

 */

public class Milliseconds
{
    public static void main (String [] args)
    {
        final int SEC_IN_DAY = 86400; // there are 86400 seconds in one day
        final int SEC_IN_HOUR = 3600; //there are 3600 secinds in one hour
        final int SEC_IN_MINUTE = 60; //there are 60 seconds in one minute
        final int SEC_IN_MS=1000;//there are 1000 miliseconds in a second
        Scanner scan = new Scanner (System.in);
        System.out.println ("This program reads an integer which " +
            "represents Milliseconds and converts it to days, " +
            "hours, minutes and seconds. ");
        System.out.println ("Please enter the number of Milliseconds");
        long ms = scan.nextLong();
        long seconds=ms/SEC_IN_MS;//converting miliseconds into seconds
        long days=seconds/SEC_IN_DAY; //calculating # of days 
        seconds=seconds%SEC_IN_DAY;//subtracting the # of days (in seconds)
        long hours=seconds/SEC_IN_HOUR;//calculating # of hours
        seconds=seconds%SEC_IN_HOUR;//subtracting the # of hours (in seconds)
        long minutes=seconds/SEC_IN_MINUTE;//calculating # of minutes
        seconds=seconds%SEC_IN_MINUTE;//subtracting the # of minutes (in seconds)

        System.out.print(days +" days "+hours+":"+ minutes + ":" + seconds+" Hours");

    } // end of method main
} //end of class Milliseconds

