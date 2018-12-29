#pragma once
#include <string>


using FString = std::string;
using int32 = int;

struct FBullCowCount
{
	int Bulls = 0;
	int Cows = 0;
};

enum class EGuessStatus
{
	INVALID,
	OK,
	NOT_ISOGRAMM,
	WRONG_LENGTH,
	NOT_LOWERCASE
	
};

class FBullCowGame{
public:

	FBullCowGame(); //constructor

	int32 GetMaxTries() const;
	int32 GetCurrentTry() const;
	int32 GetHiddenWordLength() const;
	bool IsGameWon() const;
	EGuessStatus CheckGuessValidity(FString) const;

	void Reset();
	

	
	FBullCowCount SubmitValidGuess(FString);

private:
	int32 MyCurrentTry; //see constructor for initiliazation
	FString MyHiddenWord;
	bool bGameIsWon;

	bool IsIsogram(FString) const;
	bool IsLowerCase(FString) const;
 };