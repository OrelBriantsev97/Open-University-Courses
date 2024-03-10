
//represents a bank account
 public abstract class BankAccount
{
	 private String accountNumber;
	 private String accountOwner;
	 private String id;
	 private double balance;
	 
	 //empty constructor
	 public BankAccount()
	 {
		 this.accountNumber = "";
		 this.accountOwner = "";
		 this.id = "";
		 this.balance = 0.0;
	 }
	 
	 //constructor
	 public BankAccount(String accountNum,String accountOwn,String id , double balance)
	 {
		 this.accountNumber = accountNum;
		 this.accountOwner = accountOwn;
		 this.id = id;
		 this.balance = balance;
	 }

	 // return account number
	 public String getAccountNum()
	 {
		 return this.accountNumber;
	 }
	 
	 // set an account number
	 public void setAccountNum(String newAccNum)
	 {
		this.accountNumber = newAccNum;
	 }
	 
	 // return account owner
	 public String getAccountOwner()
	 {
		 return this.accountOwner;
	 }
	 
	 // set an account owner
	 public void setAccountOwner(String newAccOwner)
	 {
		this.accountOwner = newAccOwner;
	 }
	 
	 // return account id
	 public String getAccountId()
	 {
		 return this.id;
	 }
	 
	 // set an account id
	 public void setAccountId(String newId)
	 {
		this.id = newId;
	 }
	 
	 // return account balance
	 public double getAccountBalance()
	 {
		 return this.balance;
	 }
	 
	 // set an account balance
	 public void setAccountBalance(double newBalance)
	 {
		this.balance = newBalance;
	 }
	 
	 //represents a depositing request
	 public void deposit(double deposit)
	 {
		 if(deposit > 0.0)
		 {
			 this.balance +=deposit;
		 }
			 
		 else
			 System.out.println("Account : " + this.id + " Deposit amount cant be smaller than 0");
	 }
	 
	 //represents withdraw request
	 public void withdraw(double amount)
	 {
		 try
		 {
			 if(amount > balance || amount < 0.0)
				 throw new IllegalBalance();
			this.balance -= amount; 
		 }
		 catch (IllegalBalance e)
		 {
			 System.out.println("Account : " + this.id +" The required withdraw amount is bigger than account's balance");
		 }
		 
	 }
	 

	 public abstract void monthlyMng();
	 
	 //toString
	 public String toString()
	 {
		 return "Acount Information: \nAccount Number : " + accountNumber + "\nAccount Owner : " + accountOwner
				 +"\nAccount ID : " + id + "\nAccount Balance : " + balance +"\n";
		 
	 }
	 
	 public boolean equals(Object obj)
	 {
		 BankAccount acc = (BankAccount) obj;
		 if(obj instanceof BankAccount)
		 {
			 if(this.getAccountNum().equals(acc.getAccountNum()) && this.getAccountOwner().equals(acc.getAccountOwner()) &&
					 this.getAccountId().equals(acc.getAccountId()) && this.getAccountBalance() == acc.getAccountBalance())
				 return true;
			 else
				 return false;
		 }
		 else
			 return false;
	 }
	
}
