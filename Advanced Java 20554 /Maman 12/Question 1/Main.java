import java.util.ArrayList;
import java.util.List;
import java.util.Scanner;

public class Main {

    public static void main(String[] args) {
        Polynom p1 = getPol();
        Polynom p2 = getPol();
        check(p1, p2);
    }

    public static Polynom getPol() {
        Scanner sc = new Scanner(System.in);

        System.out.println("Enter the coefficients (comma-separated):");
        String coefficientsInput = sc.nextLine();
        double[] coefficients = parseList(coefficientsInput);

        System.out.println("Enter the powers (comma-separated):");
        String powersInput = sc.nextLine();
        int[] powers = parseListInt(powersInput);

        //sc.close();
        return new Polynom(coefficients, powers);
        
    }

    private static double[] parseList(String input) {
        String[] items = input.split(",");
        double[] result = new double[items.length];
        for (int i = 0; i < items.length; i++) {
            result[i] = Double.parseDouble(items[i].trim());
        }
        return result;
    }

    private static int[] parseListInt(String input) {
        String[] items = input.split(",");
        int[] result = new int[items.length];
        for (int i = 0; i < items.length; i++) {
            result[i] = Integer.parseInt(items[i].trim());
        }
        return result;
    }

    public static void check(Polynom p1, Polynom p2) {

        // Display results
        System.out.println("Polynomial 1: " + p1);
        System.out.println("Polynomial 2: " + p2);
        System.out.println("Sum: " + p1.plus(p2));
        System.out.println("p1 minus p2: " + p1.minus(p2));
        System.out.println("Derivative of Polynomial 1: " + p1.derivative());
        System.out.println("Derivative of Polynomial 2: " + p2.derivative());

        
        System.out.println("Polynomial 1 is equal to Polynomial 2: " + p1.equals(p2));
        
       
    }
}
