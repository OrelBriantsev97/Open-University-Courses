

//represents a saving account with higher interest rate
public class HighInterestSavings extends SavingsAccount
{

	public static final double HIGH_INTEREST_RATE = 0.2;
	public static final double HIGH_MIN_BALANCE = 1000;
	
	private double interestRate;
	private double minBalance;

	public HighInterestSavings(String accountNum,String accountOwn,String id , double balance)
	{
		super(accountNum,accountOwn,id,balance);
		interestRate = INTEREST_RATE;
		minBalance = HIGH_MIN_BALANCE;
	}
	
	public HighInterestSavings(String accountNum,String accountOwn,String id , double balance,double interest,double min)
	{
		super(accountNum,accountOwn,id,balance);
		interestRate = interest;
		minBalance = min;
	}
	
	//return minimum balance
	public double getInterest()
	{
		return this.interestRate;
	}
	
	//set new minimum balance
	public void setInterest(double newRate)
	{
		this.interestRate = newRate;
	}
	
	// return minimum balance
	public double getMin()
	{
		return this.minBalance;
	}
	
	//set new minimum balance
	public void setMin(double newMin)
	{
		this.minBalance = newMin;
	}
	
	//in charge to deposit the interest to the account (monthly)
	public void monthlyMng() 
	{
		this.deposit(this.calcInterest());
	}
	
	public double calcInterest()
	{
		return this.getAccountBalance() * interestRate;
	}
		
	public String toString()
	{
		return super.toString() + "Account Saving Interest Rate(Higher)  : " + interestRate + "\n" 
				+ "Account Saving Minimum Balance :" + minBalance + "\n";
	}
}
