#include <iostream>
#include <string>
#include <queue>
#include <unordered_map>

//Function Prototypes

bool updateCurrentString(std::string &correctWord, std::string &currentString, char theCharacter);

bool checkForWinner(std::string &currentString);



int main(){
  
  std::cout << "\n\nLets play Hangman." << std::endl;
  std::cout << "Guess the correct word and YOU WIN!" << std::endl;
  std::cout << "Get five strikes and YOU LOSE!\n\n"<< std::endl;

  std::cout << "We need two players to play this game.\n\n";

  //Lets get the guessing word from the user.
  std::string correctWord;
  int sizeOfWord;

  std::cout <<"Player one will enter the word that player two will try to guess.\n\n";

  //We need the word to have at least 3 characters

  std::cout << "PLAYER ONE: Enter the guessing word: ";
  getline(std::cin, correctWord);
  sizeOfWord = correctWord.length();

  while(sizeOfWord < 3){
 	 std::cout << "\n\nInvalid word.\nThe word should have at least three characters.\n";
 	 std::cout << "PLAYER ONE: Enter a valid guessing word: ";
  	 getline(std::cin, correctWord);
  	 sizeOfWord = correctWord.length();
  }


  //We have to hide the correct word from the 
  std::cout <<"\n\n\n\n\n\n\n\n\n\n\n\n\n\n\nHiding the word from player two.";
  std::cout <<"\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n"; 
  
  //Create an empty current String and properly populate it with dashes
  std::string currentString;
  for(int i = 0; i< sizeOfWord; i++){
  	currentString = currentString + '-';	
  
  }
  std::cout << "\n\n\nPLAYER TWO: Its Time To Play Hangman.\n";
  std::cout << "Try to guess the " << sizeOfWord << " letter word.\n";
  std::cout << "All the alphabet characters are valid guesses "
	  << "and the space character is also a valid guess.\n";

  std::cout << "Current word: " <<currentString << "\n" << std::endl;  
  
  //Make the use guess character by character until he wins or he loses

  int strikeCounter = 0;
  bool gameOver = false;
  bool foundCharacter;
  char ch = '0';

  std::unordered_map<char, int> myMap;
  int k = 0;

  while(!gameOver){


       	  //Make the user enter on character.	  
	  std::cout<< "\n\nMake a character guess: ";
	  std::string temp;
	  std::getline(std::cin, temp);
	  
	  if(!temp.empty()){
	  	//Make sure that we only get one character
	  	ch = temp.at(0);
	  }


 
	  while( myMap.find(ch) != myMap.end() || ch == '0') {
	  	
		if(ch=='0')
			std::cout<< "\nEmpty character, try again.\nMake a character guess: ";
		else
			std::cout<< "\nRepeated character, try again.\nMake a character guess: ";
		
	 

	  	
		std::string temp;
	  	std::getline(std::cin, temp);
	  	//Make sure that we only get one character
	  	if(!temp.empty()){
	  		//Make sure that we only get one character
	  		ch = temp.at(0);
		
		}
		else{
			//If we have an empty character, then we reamin in the while loop
			ch ='0';
		}
	  }


	  //We have a valid character
	  if(ch >=65 && ch <=90){
		  //We have an upper case character
	  	myMap[ch] = k;
	  	++k;
		myMap[(char(ch+32))] = k;
		++k;	
	  }
	  else if(ch >=97 && ch <=122){
		  //We have an upper case character
	  	myMap[ch] = k;
	  	++k;
		myMap[(char(ch-32))] = k;
		++k;	
	  }
	  else
	  {
	  	myMap[ch] = k;
	  	++k;
	  }
	  


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
		  
		  std::cout << "Bad guess my friend: "<< ch << " is not a character"
			 <<" in our mystery word.\n" << "STRIKE: " << strikeCounter << std::endl; 
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
      

	//We need a queue, just in case we have multiple correct guesses	
	std::queue<int> myQueue;

	//Are we dealing with an upper case character or lower case
	bool upperCaseGuessing = (theCharacter >=65 && theCharacter <=90) ? true:false;


	//Check if the character is found in the correctWord
	for(int m = 0 ; m < correctWord.size(); m++)
	{


		char currCh = correctWord.at(m);

		bool upperCaseAnswer = (currCh >=65 && currCh <=90) ? true:false;


		//My queue will store the index if we find a correct guess
		if(upperCaseGuessing && !upperCaseAnswer){
		
			if( (char)(theCharacter+32) == currCh)
				myQueue.push(m);
	
		} 
		else if(!upperCaseGuessing && upperCaseAnswer){
		
			if( (char)(currCh+32) == theCharacter)
				myQueue.push(m);
		}
		else{	

			if(theCharacter == correctWord.at(m))
				myQueue.push(m);
		}
		
	}





	if(myQueue.empty()){
		return 0;
	} else {
	  std::cout << "We found the character: " << theCharacter 
		  << ": " << myQueue.size()<<" times.\n"; 
          //Update the currentString.
	  int index;
	  while(!myQueue.empty())
	  {
		index = myQueue.front();
	        myQueue.pop();	
	  	currentString[index] = correctWord.at(index);
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
