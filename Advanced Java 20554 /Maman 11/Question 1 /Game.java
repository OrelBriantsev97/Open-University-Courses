
package question1;

import java.util.ArrayList;

import javax.swing.JOptionPane;

// Game represents a game session from start until the user guesses the word / quits
public class Game {
    public static void main(String[] args) {
        boolean playAgain;

        do {
            playAgain = playGame();
        } while (playAgain);
    }

    // Function to play a single game
    private static boolean playGame() {
        ArrayList<Character> lettersArr;
        WordBank wBank = new WordBank();
        Word word = new Word(wBank.getRandomWord());

        int attempts = 0;
        boolean found = false;
        String userInput = "";
        word.updateStatus(-1);
        int choice;

        do {
            choice = JOptionPane.showConfirmDialog(null, "Hello!\n Do you want to play a game ? ", "Ready?",JOptionPane.YES_NO_OPTION);
            if (choice == JOptionPane.CLOSED_OPTION)
                System.exit(0);

        } while (!(choice != JOptionPane.NO_OPTION));

        do {
            lettersArr = word.getAlphabet();
            userInput = JOptionPane.showInputDialog(null,"Guess the word by entering a letter [a-z,A-Z]\n Game Status : " + word.getStatus()
                            + "\n Remaining letters :  " + lettersArr,JOptionPane.CLOSED_OPTION);
            
            if (userInput.length() == 1 && Character.isLetter(userInput.charAt(0))) // is user input is only one char
{
                word.isMatch(userInput);
                attempts++;

            } else {
                JOptionPane.showMessageDialog(null, "Please enter a single letter.");
            }
            if (word.getStatus().indexOf('_') == -1) { // if user found the word
                found = true;
            }

        } while (!found);

        int tryAgainChoice = JOptionPane.showConfirmDialog(null,
                "Congratulations! You guessed the word " + word.getWord() + " with only " + attempts + " attempts!\nDo you want to play again?",
                "Try Again", JOptionPane.YES_NO_OPTION);

        return tryAgainChoice == JOptionPane.YES_OPTION;
    }
}
