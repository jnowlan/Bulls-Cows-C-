#pragma once
#include "FBullCowGame.h"
#include <map>
#define TMap std::map

using int32 = int;

void FBullCowGame::Reset()
{
	const FString HIDDEN_WORD = "love"; //this word must be an isogram 
	MyHiddenWord = HIDDEN_WORD;

	MyCurrentTry = 1;
	bGameIsWon = false; 
	return;
}

FBullCowGame::FBullCowGame()
{
	Reset();
}

int32 FBullCowGame::GetMaxTries() const
{
	TMap<int32, int32> WordLengthtoMaxTries{ {3, 10}, {4, 10}, {5, 10}, {6, 16}, {7, 20}};
	return WordLengthtoMaxTries[MyHiddenWord.length()];
}

int32 FBullCowGame::GetCurrentTry() const
{
	return MyCurrentTry;
}

int32 FBullCowGame::GetHiddenWordLength() const
{
	return MyHiddenWord.length();
}

bool FBullCowGame::IsGameWon() const
{
	return bGameIsWon;
}

EGuessStatus FBullCowGame::CheckGuessValidity(FString Guess) const
{
	if (!IsIsogram(Guess))
	{
		return EGuessStatus::NOT_ISOGRAMM;
	}

	else if (!IsLowerCase(Guess))
	{
		return EGuessStatus::NOT_LOWERCASE;
	} 

	else if (Guess.length() != GetHiddenWordLength() )
	{
		return EGuessStatus::WRONG_LENGTH;
	}

	else
	{
		return EGuessStatus::OK;
	}
	
}

// recieves a valid guess, increments turn and returns count
FBullCowCount FBullCowGame::SubmitValidGuess(FString Guess)
{
	//increment the turn number
	MyCurrentTry++;

	//setup a return variable
	FBullCowCount BullCowCount;

	//loop through all letters in the guess
	int32 WordLength = MyHiddenWord.length();

	for (int32 MHWChar = 0; MHWChar < WordLength; MHWChar++)
	{
		for (int32 GChar = 0; GChar < WordLength; GChar++)
		{
			if (Guess[GChar] == MyHiddenWord[MHWChar])
			{
				if (MHWChar == GChar)
				{
					BullCowCount.Bulls++; //increment bulls
				}

				else
				{
					BullCowCount.Cows++; //increment cows
				}
			}
		}
	}

	if (BullCowCount.Bulls == WordLength)
	{
		bGameIsWon = true;

	}
	else 
	{
		bGameIsWon = false;
	}
		//compare letters against the hidden word
	return BullCowCount;
}

bool FBullCowGame::IsIsogram(FString Word) const
{
	//treat 0 and 1 letter strings as isograms
	if (Word.length() <= 1)
	{
		return true;
	}
	
	TMap<char, bool> LetterSeen;

	for (auto Letter : Word) //for all letters of the word
	{
		Letter = tolower(Letter); //handle mixed casee
		if (LetterSeen[Letter]) // if the letter is in the map
		{
			return false; //we don't NOT have an isogram
		}

		else
		{
			LetterSeen[Letter] = true; // add the letter to the map as seen
		}
	}
	

	return true; 
}

bool FBullCowGame::IsLowerCase(FString Word) const
{
	for (auto Letter : Word) 
	{
		if (!islower(Letter))//if not a lowercase letter
		{
			return false;
		}
		
	}
	return true;
}
