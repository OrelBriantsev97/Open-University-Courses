import java.util.Iterator;
import java.util.Map;

public class Main
{
	public static void main(String[] args) throws IllegalArgumentException
	{
		Student[] students= {
					 new Student ("Orel " , "Briantsev ", "12345678 ", "1997"),
					 new Student ("Justin " , "Timberlake ", "9876543 ", "2008"),
					 new Student ("Tylor " , "Swift ", "9876543 ", "1980"),
			};
			
		Integer [] grades = {90,75,55};
		AssociationTable<Student,Integer> studentTable = new AssociationTable<>(students,grades);
		
		
		//check student
		Student s4 = new Student("Chris", "Brown ", "264987", "1999");
        Integer s4_grade = 80;
        studentTable.add(s4,s4_grade);
		
        //check get 
        System.out.println("Justin average grade is : " + studentTable.get(students[1]));
        
        // check contains
        System.out.println("Is Chris added to table " + studentTable.contains(s4));
        
        
       //check remove
        System.out.println("is tylor removed from table " + studentTable.remove(s4));
        
        //print 
        Iterator<Map.Entry<Student,Integer>> iter = studentTable.keyIterator();
        while(iter.hasNext()) {
            Map.Entry<Student,Integer> next = iter.next();
            System.out.println("key - student: " + next.getKey());
            System.out.println("value - average grade: " + next.getValue() + "\n");
        
		
        }
	}
	

}
