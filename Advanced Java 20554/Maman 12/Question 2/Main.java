public class Main 
{
    public static void main(String[] args) 
    {
        // Create instances of different account types
        SavingsAccount sa = new SavingsAccount("123", "John Doe", "12345678", 5000.0, 0.15);
        HighInterestSavings his = new HighInterestSavings("456", "Jane Smith", "87654321", 1000.0, 0.2, 1500.0);
        ServiceChargeChecking scc = new ServiceChargeChecking("789", "Bob Johnson", "24680567", 3000.0, 12.0);
        NoServiceChargeChecking nscc = new NoServiceChargeChecking("321", "Alice Brown", "13579987", 2500.0, 1000.0);
        InterestChecking ic = new InterestChecking("654", "Charlie Williams", "23654168", 6000.0, 0.18);

        //  deposit and withdraw 
        sa.deposit(1000.0);
        sa.deposit(-1000.0); // should print an error
        his.withdraw(500.0);
        his.withdraw(1000.0); //should print an error
        
        //montlyMng
        sa.monthlyMng();
        his.monthlyMng();
        scc.monthlyMng();
        ic.monthlyMng();
        

        //  check writing
        scc.writeCheck(50.0);
        nscc.writeCheck(200.0); //should print an error ?

        // Display account information
        SavingsAccount saCopy = new SavingsAccount("123", "John Doe", "12345678", 4000.0, 0.15);
        SavingsAccount saCopy1 = new SavingsAccount("123", "John Doe", "12345678", 5000.0, 0.15);
        System.out.println("Savings Account Information:");
        System.out.println(sa);
        System.out.println("savingsAccount.equals(savingsAccount copy): " + sa.equals(saCopy)); // not equal
        System.out.println("savingsAccount.equals(savingsAccount copy1): " + sa.equals(saCopy1)); // not equal

        
        HighInterestSavings hisCopy = new HighInterestSavings("456", "Jane Smith", "12345678", 1000.0, 0.2, 1500.0);
        HighInterestSavings hisCopy1 = new HighInterestSavings("456", "Jan Smith", "87654321", 1000.0, 0.2, 1500.0);
        System.out.println("High Interest Savings Account Information:");
        System.out.println(his);
        System.out.println("highInterestSavings.equals(highInterestSavings copy): " + his.equals(hisCopy)); //false
        System.out.println("highInterestSavings.toString():\n" + hisCopy1);//false
        

        ServiceChargeChecking sccCopy = new ServiceChargeChecking("789", "Bob Johnson", "24680567", 3000.0, 12.0);
        ServiceChargeChecking sccCopy1 = new ServiceChargeChecking("789", "Bot Johnson", "24680567", 3000.0, 12.0);
        System.out.println("Service Charge Checking Account Information:");
        System.out.println(scc);
        System.out.println("serviceChargeChecking.equals(serviceChargeChecking copy): " + scc.equals(sccCopy));
        System.out.println("serviceChargeChecking.equals(serviceChargeChecking copy1): " + scc.equals(sccCopy1));

        System.out.println("No Service Charge Checking Account Information:");
        System.out.println(nscc);
        NoServiceChargeChecking nsccCopy = new NoServiceChargeChecking("321", "Alice Brown", "13579987", 2500.0, 1000.0);
        NoServiceChargeChecking nsccCopy1 = new NoServiceChargeChecking("321", "Alice Brown", "13579987", 1500.0, 1000.0);
        System.out.println("noserviceChargeChecking.equals(serviceChargeChecking copy): " + scc.equals(sccCopy));
        System.out.println("serviceChargeChecking.equals(serviceChargeChecking copy1): " + scc.equals(sccCopy1));
        
        System.out.println("Interest Checking Account Information:");
        System.out.println(ic);
    }
}
