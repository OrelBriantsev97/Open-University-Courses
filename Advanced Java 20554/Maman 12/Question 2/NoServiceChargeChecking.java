//represents an account without monthly commission and with no option for writing checks
public class NoServiceChargeChecking extends CheckingAccount 
{
	public static final double MIN_BALANCE = 1000.0;
	private double minBalance;
	
	public NoServiceChargeChecking(String accountNum,String accountOwn,String id , double balance)
	{
		super(accountNum,accountOwn,id,balance);
		minBalance = MIN_BALANCE;
	}
	
	public NoServiceChargeChecking(String accountNum,String accountOwn,String id , double balance,double min)
	{
		super(accountNum,accountOwn,id,balance);
		minBalance = min;
	}
	
	//return minimum balance
	public double getMinBalance()
	{
		return this.minBalance;
	}
	
	//set new minimum balance
	public void setMinBalance(double newMin)
	{
		this.minBalance = newMin;
	}
	
	public void monthlyMng() {}
		
	public String toString()
	{
		return super.toString() + "Account Minimum Balance : " + minBalance + "\n";
	}
	
	public boolean equals(Object obj)
	{
		NoServiceChargeChecking acc = (NoServiceChargeChecking) obj;
		if(super.equals(acc))
		{
			if(this.getMinBalance() != acc.getMinBalance())
				return false;
			return true;
		}
		else
			return false;
	}
}
