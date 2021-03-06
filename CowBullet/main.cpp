﻿// CowBullet.cpp : Defines the entry point for the console application.
//
#pragma once
#include "stdafx.h"
#include <iostream>
#include <string>
#include "FBullCowGame.h"

//"using" to get used to unreal syntax, on the programming side it makes no difference
using FText = std::string;
using int32 = int;

//prototyping since main has no header here
void printIntro();
void playGame();
FText getValidGuess();
bool playAgain();
void printGameSummary();
FBullCowGame bcGame;
int main(){
	bool bPlayAgain = false;
	//get player guess
	do {
		printIntro();
		playGame();
		bPlayAgain = playAgain();
	} while (bPlayAgain);
	return 0;
}
void playGame(){
	bcGame.reset();
	int32 maxTries = bcGame.getMaxTries();
	while(!bcGame.gameWon() && bcGame.getCurrentTry() <= maxTries) {
		FText guessValue = getValidGuess(); // TODO Check for valid guesses
		FBullCowCount bullCowCount = bcGame.submitValidGuess(guessValue);
		std::cout << "Bulls = " << bullCowCount.bulls;
		std::cout << " Cows = " << bullCowCount.cows;
		std::cout << " Your guess was : " << guessValue << std::endl << std::endl;
	}
	
	printGameSummary();
}
//Game Intro
void printIntro() {
	std::cout << std::endl<<std::endl << "Welcome to Bulls & Cows" << std::endl;
	std::cout << "Can you guess the " << bcGame.getHiddenWordLength();
	std::cout << " letter isogram I'm thinking of?" << std::endl;
	std::cout << std::endl;
}
FText getValidGuess() {
	FText guess = "";
	eGuessStatus status = eGuessStatus::Invalid_Status;
	do {
		int32 currentTry = bcGame.getCurrentTry();
		std::cout << "Try : " << currentTry << " of " << bcGame.getMaxTries();
		std::cout << " , Enter your guess : ";
		std::getline(std::cin, guess);

		status = bcGame.checkGuessValidity(guess);
		switch (status) {
		case eGuessStatus::Wrong_Length:
			std::cout << "Please enter a " << bcGame.getHiddenWordLength() << " letter Word" << std::endl << std::endl;;
			break;
		case eGuessStatus::Not_Isogram:
			std::cout << "Please enter a word without repeating letters." << std::endl << std::endl;;
			break;
		case eGuessStatus::Not_Lowercase:
			std::cout << "Please enter all lowercase letters." << std::endl << std::endl;;
			break;
		default:
			// assume the guess is valid;
			break;
		}
	} while (status != eGuessStatus::OK);
	return guess;
}
bool playAgain() {
	std::cout << "Do you want to play again? (y/n)";
	FText response = "";
	std::getline(std::cin,response);
	if (response[0] == 'y' || response[0] == 'Y') {
		return true;
	}
	else {
		return false;
	}
}
void printGameSummary()
{
	if (bcGame.gameWon()) {
		std::cout << "Well done - you win!" << std::endl;
	}else{
		std::cout << "You lost, better luck next time" << std::endl;
	}
}
