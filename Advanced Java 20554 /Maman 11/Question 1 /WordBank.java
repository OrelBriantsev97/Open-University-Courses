package question1;

import java.util.ArrayList;
import java.util.Random;

//represents the wordbank in the game 
public class WordBank {

	
	ArrayList<String> wordBank= new ArrayList<String>();
	
	//constructor
	public WordBank()
	{
		String[] array= {"airplane","beach","vacation","airport","restaurant","holiday","suitcase","passport","shopping","dutyfree"
				,"hotel","pool","sunscreen","breakfast","pictures"};
		
		for (String word : array)
            wordBank.add(word);
		
		
	}
	
	// return a word from the wordBank array
	public String getRandomWord()
	{
		Random random = new Random();
		int ind = random.nextInt(wordBank.size());
		return wordBank.get(ind);
	}
	
	
	
}
