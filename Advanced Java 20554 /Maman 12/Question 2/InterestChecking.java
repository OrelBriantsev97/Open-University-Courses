
//represent an account with interest
public class InterestChecking extends NoServiceChargeChecking 
{
	public static final double INTEREST_RATE = 0.2;
	private double interestRate;

	public InterestChecking(String accountNum,String accountOwn,String id , double balance)
	{
		super(accountNum,accountOwn,id,balance);
		interestRate = INTEREST_RATE;
	}
	
	public InterestChecking(String accountNum,String accountOwn,String id , double balance,double interest)
	{
		super(accountNum,accountOwn,id,balance);
		interestRate = interest;
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
		return super.toString() + "Account Interest Rate  : " + interestRate + "\n";
	}
}
