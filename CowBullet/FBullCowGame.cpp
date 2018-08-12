#pragma once
#include "stdafx.h"
#include "FBullCowGame.h"
#include <map>
//define TMap to make syntax more unreal like
#define TMap std::map
FBullCowGame::FBullCowGame(){
	reset();
}
void FBullCowGame::reset(){
	myHiddenWord = "crystal";
	myCurrentTry = 1;
	gameIsWon = false;
	return;
}
int32 FBullCowGame::getMaxTries() const{
	TMap<int32, int32> wordLenghtToMaxTries{ {1,3},{2,3},{3,4},{4,5},{5,5},{6,7},{7,7},{8,10},{9,10},{10,12}};


	return wordLenghtToMaxTries[myHiddenWord.length()];
}
int32 FBullCowGame::getCurrentTry() const{
	return myCurrentTry;
}
int32 FBullCowGame::getHiddenWordLength() const{
	return myHiddenWord.length();
}
bool FBullCowGame::gameWon()const{
	return gameIsWon;
}
eGuessStatus FBullCowGame::checkGuessValidity(FString guess)const{
	
	if (!isIsogram(guess)) {
		return eGuessStatus::Not_Isogram;
	}
	else if (!isLowerCase(guess)) {
		return eGuessStatus::Not_Lowercase;
	}
	else if (guess.length() != getHiddenWordLength()) {
		return eGuessStatus::Wrong_Length;
	}
	else {
		return eGuessStatus::OK;
	}
	
	
}
//Struct Method
FBullCowCount FBullCowGame::submitValidGuess(FString guess) {
	myCurrentTry++;
	FBullCowCount fBullCowCount;
	//do check
	int32 wordLength = myHiddenWord.length();
	for (int i = 0; i <wordLength;i++) {
		for (int32 j = 0; j < wordLength; j++) {
			if (guess[j] == myHiddenWord[i]) {
				if (i == j) {
					fBullCowCount.bulls++;
				}
				else {
					fBullCowCount.cows++;
				}
			}
		}
	}
	if (fBullCowCount.bulls == wordLength) {
		gameIsWon = true;
	}
	else {
		gameIsWon = false;
	}
	return fBullCowCount;
}
bool FBullCowGame::isIsogram(FString guess) const
{
	if (guess.length() <= 1) { return true; }
	TMap<char,bool> letterSeen;
	for (auto letter : guess) {
		letter = tolower(letter);
		if (letterSeen[letter]) {
			return false;
		} else {
			letterSeen[letter] = true;
		}
	}
	return true;
}
bool FBullCowGame::isLowerCase(FString guess) const
{
	for (auto letter : guess) {
		if (isupper(letter)) {
			return false;
		}
	}
	return true;
}
