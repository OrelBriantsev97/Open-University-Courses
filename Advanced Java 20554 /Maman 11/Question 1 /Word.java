package question1;

import java.util.ArrayList;

// Word class represents the chosen word that user needs to guess
public class Word {
	
	private ArrayList<Character> alphabet = new ArrayList<Character>(); //represents the remaining alphabet array
	private StringBuilder status = new StringBuilder();
	private int wordLength = 0;
	private String word;
	
	//empty constructor
	public Word() {};
	
	//Word constructor
	public Word(String newWord)
	{
		//fill alphabet array with the ABC... 
		for(char letter = 'a'; letter <= 'z'; letter++)
			alphabet.add(letter);
		
		wordLength = newWord.length();
		word= newWord;
	}

	// delete given letter from the remaining alphabet 
	public void deleteChar(String letter)
	{
		char usedChar = letter.charAt(0);
		int index = alphabet.indexOf(usedChar);
		if(index != -1)
			alphabet.remove(index);
		
	}
	
	/* update user progress status :
	* if status is empty then add "_" according to word length 
	* else switch the '_' char with the letter that placed in the word[index] 
	*/
	public void updateStatus(int index)
	{
		if (status.length() == 0 && index == -1)
		{
			for (int i = 0 ; i < wordLength ; i++)
				status.append("_ ");
		}
		else
		{
		      status.setCharAt(index*2, word.charAt(index));
		}
	}
	
	// return user status
	public String getStatus()
	{
		return status.toString();
	}
	
	/* check if the word contains the guessed letter: if so then update status
	 * delete the char from the alphabet
	 */
	public void isMatch(String letter)
	{
	    for (int i = 0; i < wordLength; i++)
	    {
	        if (word.charAt(i) == letter.charAt(0)) 
	            updateStatus(i);
	    }
	    deleteChar(letter);
	}
	
	//return the alphabet
	public ArrayList<Character> getAlphabet() {
		    return alphabet;
	}
	
	//return the chosen word
	public String getWord()
	{
		return word;
	}
	
}

