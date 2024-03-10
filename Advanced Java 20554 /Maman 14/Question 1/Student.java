
public class Student implements Comparable<Student>
{
	private String firstName;
	private String lastName;
	private String id;
	private String year;
	
	
	//constructor
	public Student(String fName , String lName, String id , String year)
	{	
		this.firstName = fName;
		this.lastName = lName;
		this.id =id;
		this.year = year;
		
	}

	//compareTo override
	public int compareTo(Student student)
	{
		return id.compareTo(student.id);
	}
	//toString override
	public String toString()
	{
		return "student name: "+ firstName + lastName + "student id: " + id + " student year of birth: " + 	year ; 
	}
}
