
//represent account that have a monthly commission 
public class ServiceChargeChecking extends CheckingAccount
{
	public static final double COMMISSION = 10.0;
	private double commission;
	
	public ServiceChargeChecking(String accountNum,String accountOwn,String id , double balance)
	{
		super(accountNum,accountOwn,id,balance);
		commission = COMMISSION;
	}
	
	public ServiceChargeChecking(String accountNum,String accountOwn,String id , double balance,double comm)
	{
		super(accountNum,accountOwn,id,balance);
		commission = comm;
	}
	
	//return commission
	public double getCommission()
	{
		return this.commission;
	}
	
	//set new commission rate
	public void setCommission(double newComm)
	{
		this.commission = newComm;
	}
	
	//in charge to withdraw the commission from the account (monthly)
	public void monthlyMng()
	{
		this.withdraw(commission);
	}
	
	public String toString()
	{
		return super.toString() + "Account Montly Commission : " + commission + "\n";
	}
	
	public boolean equals(Object obj)
	{
		ServiceChargeChecking acc = (ServiceChargeChecking) obj;
		if(super.equals(acc))
		{
			if(this.getCommission() != acc.getCommission())
				return false;
			return true;
		}
		else
			return false;
	}
}
