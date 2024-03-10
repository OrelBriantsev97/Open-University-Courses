import java.util.TreeMap;
import java.util.Iterator;
import java.util.Map;

public class AssociationTable< K extends Comparable<K>,V>
{
	private TreeMap<K,V> table;
	
	//empty constructor
	public AssociationTable()
	{
		table = new TreeMap<K,V>();
	}
	
	//construct a new sorted Association table with the given keys and values
	public AssociationTable(K[] keys , V[] values) throws IllegalArgumentException 
	{
		if(keys.length != values.length)
			throw new IllegalArgumentException("keys and values arrays are diffrent length ");
	
		table = new TreeMap<K,V>();
		for(int i = 0 ;i< keys.length ; i++)
		{
			table.put(keys[i],values[i]);
		}
		
	}
	
	// adding given key and value to table , if key already exist - updates value
	public void add(K key , V value)
	{
		table.put(key, value);
		
	}
	
	//return the value of a given key , if not exist in table - return null
	public V get(K key)
	{
		if (contains(key))
			return table.get(key);
		else
			return null;
	}
	
	// return true if the table contains the key
	public boolean contains (K key)
	{
		if(table.containsKey(key)) 
			return true;
		else
			return false;
	}
	
	//removes given key and associated value from table , if table not contains the key return false
	public boolean remove(K key)
	{
		if(contains(key))
		{
			table.remove(key);
			return true;
		}
		else
			return false;
	}
	
	//return the number of pairs in table 
	public int size()
	{
		return table.size();
	}
	
	//return iterator
	public Iterator<Map.Entry<K,V>> keyIterator()
	{
		return table.entrySet().iterator();
	}
	
	

}
