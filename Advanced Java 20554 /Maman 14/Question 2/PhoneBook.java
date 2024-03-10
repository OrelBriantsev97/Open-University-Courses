
import java.util.AbstractMap;
import java.util.TreeMap;

public class PhoneBook  
{
	//private static final long serialVersionUID = 1L;
	private TreeMap<String,String> phoneBook = new TreeMap<String,String>();
	
	//add new contact 
	//if phone invalid - will throw error accordingly
	public void add(String name , String phoneNum) throws InvalidPhoneNumberExc,DuplicateNameExc
	{
		if(phoneBook.containsKey(name))
		{
			throw new DuplicateNameExc("This contact already exist in phonebook , you can update number for this contact instead. ");
		}
		if(phoneNum.length()!=10 || !phoneNum.matches("\\d{10}"))
		{
			throw new InvalidPhoneNumberExc("Phone Number invalid. please enter a 10 digit phone number");
		}
		
		phoneBook.put(name,phoneNum);
		
	}
	
	//update an existing contact phone
	//if not exist/phone invalid - will throw error accordingly
	public void update (String name , String phoneNum) throws ContactNotExistExc,InvalidPhoneNumberExc
	{
		if(!phoneBook.containsKey(name))
			throw new ContactNotExistExc("This contact not exist in the phone book");
		
		if(phoneNum.length()!=10 || !phoneNum.matches("\\d{10}"))
			throw new InvalidPhoneNumberExc("Phone Number invalid. please enter a 10 digit phone number");
		
		phoneBook.put(name,phoneNum);	
		
	}
	
	//delete existing contact 
	//if not exist- will throw error accordingly
	public void delete  (String name , String phoneNum) throws ContactNotExistExc
	{
		if(!phoneBook.containsKey(name))
				throw new ContactNotExistExc("This contact not exist in the phone book");
		
		phoneBook.remove(name);
		
		
	}
	
	//search phone bt ontact name
	//if not exist- will throw error accordingly
	public TreeMap<String, String>  search(String name) throws ContactNotExistExc {
	    if (!phoneBook.containsKey(name)) {
	        throw new ContactNotExistExc("This contact does not exist in the phone book");
	    }

	    // Return the phone number directly
	    TreeMap<String, String> result = new TreeMap<>();
	    result.put(name, phoneBook.get(name));
	    return result;
	}
	
	  public TreeMap<String, String> getPhoneBook() {
	        return phoneBook;
	    }
	
}