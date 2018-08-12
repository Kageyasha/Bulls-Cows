#pragma once      //pragma once -> import once -> avoid recursion in worst case scenarios
#include <string>


using FString = std::string;
using int32 = int;

struct FBullCowCount {
	int32 bulls = 0;
	int32 cows = 0;
};
enum class eGuessStatus {
	Invalid_Status,
	OK,
	Not_Isogram,
	Wrong_Length,
	Not_Lowercase
};
class FBullCowGame {
public :
	//constuctor
	FBullCowGame();
	
	//Const -> make sure those methods cant change actuall numbers
	int32 getMaxTries()const;
	int32 getCurrentTry()const;
	int32 getHiddenWordLength()const;
	eGuessStatus checkGuessValidity(FString)const;
	bool gameWon()const;
	//
	void reset();
	FBullCowCount submitValidGuess(FString);

private :
	int32 myCurrentTry;
	FString myHiddenWord;
	bool gameIsWon;
	bool isIsogram(FString) const;
	bool isLowerCase(FString) const;
};