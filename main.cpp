#include <iostream>
#include <string>
#include <queue>

//Function Prototypes

bool updateCurrentString(std::string &correctWord, std::string &currentString, char theCharacter);

bool checkForWinner(std::string &currentString);



int main(){
  
  std::cout << "Lets play Hangman" << std::endl;
  std::cout << "Guess the correct word and YOU WIN!" << std::endl;
  std::cout << "Get five strikes and YOU LOSE!\n\n"<< std::endl;


  //Lets get the guessing word from the user
  std::string correctWord;
  std::cout <<"Enter the guessing word:";
  getline(std::cin, correctWord);

  int sizeOfWord = correctWord.length();


  
  
  //Create an empty current String and properly populate it with dashes
  std::string currentString;
  for(int i = 0; i< sizeOfWord; i++){
  	currentString = currentString + '-';	
  
  }
  std::cout << "\n\n\nIts Time To Play Hangman:\nTry to guess the " << sizeOfWord << " letter word.\n";

  std::cout << "Current word: " <<currentString << "\n" << std::endl;  
  //Make the use guess character by character until he wins or he loses

  int strikeCounter = 0;
  bool gameOver = false;
  bool foundCharacter;
  char ch;
  while(!gameOver){
    //Make the user enter on character
	  
	  std::cout<< "\n\nMake a character guess: ";
	  std::cin >> ch;

          foundCharacter =  updateCurrentString(correctWord, currentString, ch);

	  if(foundCharacter){
		  std::cout << "CORRECT!\nWe have updated the current string:" <<std::endl;
  		  std::cout << "Current word: " <<currentString << "\n" << std::endl; 

    		  //Check if we have a winner
		  if(checkForWinner(currentString))
		  {
		  	std::cout << "\n\nCongratulations: YOU WON\nYou have guessed the word: \"" 
				<< correctWord << "\" correctly.\nBye"<< std::endl;
			return 1;
		  } 

	  } else {
		  ++strikeCounter;
		  
		  std::cout << "STRIKE: " << strikeCounter << std::endl; 
	  }


	  if(strikeCounter == 5){
	  	std::cout << "\n\nFIVE SRTIKES:   YOU LOSE." << std::endl;
	        gameOver = true;
		std::cout << "The word was: \"" << correctWord << "\"" << std::endl;
		std::cout << "Bye.";
	  }

  }



  return 1;  



}



//Define our function prototypes
bool updateCurrentString(std::string &correctWord, std::string &currentString, char theCharacter){
       
	std::queue<int> myQueue;

	//Check if the character is found in the correctWord

	for(int m = 0 ; m < correctWord.size(); m++)
	{
		if(theCharacter == correctWord.at(m))
		{
			myQueue.push(m);
		}
	}





	if(myQueue.empty()){
		return 0;
	} else {
	  std::cout << "We found the character: " << theCharacter << ": " << myQueue.size()<<" times.\n"; 
          //Update the currentString.
	  int index;
	  while(!myQueue.empty())
	  {
		index = myQueue.front();
	        myQueue.pop();	
	  	currentString[index] = theCharacter;
	  }
	
	  return 1; 	
	}

}




bool checkForWinner(std::string &currentString){

	for(int i = 0 ; i < currentString.size(); i++){
		if('-' == currentString.at(i))
		{
			return 0;
		}
	}

	return 1;
}
