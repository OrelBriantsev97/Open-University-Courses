
//represent an account that can writhe checks
public abstract class CheckingAccount extends BankAccount
{
	public CheckingAccount(String accountNum,String accountOwn,String id , double balance)
	{
		super(accountNum,accountOwn,id,balance);
	}
	
	public void writeCheck(double amount)
	{
		try
		{
			if(amount > this.getAccountBalance())
				throw new IllegalBalance();
			System.out.println("Write check  request approved , check  amount: " + amount);
			
		}
		catch (IllegalBalance e)
		 {
			 System.out.println("Requested check sum is higher than account's balance");
		 }
	}
	

}
