// Fill out your copyright notice in the Description page of Project Settings.
#include "BullCowCartridge.h"
#include "HiddenWordList.h"
//#include "Math/UnrealMathUtility.h"

void UBullCowCartridge::BeginPlay() {         // When the game starts
    Super::BeginPlay();

    //Set up game
    SetupGame();

    //PrintLine(TEXT("Numbers of possible words is %i"), GetValidWords(HiddenWords).Num());
    PrintLine(TEXT("The hidden word is: %s. \nHas %i characters long"), *HiddenWord, HiddenWord.Len());
}

void UBullCowCartridge::OnInput(const FString& PlayerInput) {      // When the player hits enter
    if (bGameOver) {
        ClearScreen();
        SetupGame();
    } else {
        //Check guess
        ProcessGuess(PlayerInput);
    }
}

void UBullCowCartridge::SetupGame() {
    HiddenWord = GetValidWords(HiddenWords)[FMath::RandRange(0, GetValidWords(HiddenWords).Num() - 1)];
    Lives = HiddenWord.Len();
    bGameOver = false;
    
    //Welcome text
    PrintLine(TEXT("Welcome to Bull Cows!"));
    PrintLine(TEXT("Guess the %i letter words."), HiddenWord.Len());
    PrintLine(TEXT("You have %i live(s)."), Lives);
    PrintLine(TEXT("Type your word and press enter to continue"));

    IsIsogram(HiddenWord);
}

void UBullCowCartridge::GameOver() {
    bGameOver = true;
    PrintLine(TEXT("Game over. Press enter to play again!"));
}

void UBullCowCartridge::ProcessGuess(const FString& Guess) {
    if (Guess == HiddenWord) {
        PrintLine(TEXT("Correct!!!"));
        GameOver();
        return;
    }

    if (Guess.Len() != HiddenWord.Len()) {
        PrintLine(TEXT("The hidden word is %i letters long"), HiddenWord.Len());
        return;
    }

    if (!IsIsogram(Guess)) {
        PrintLine(TEXT("No repeating letter. Guess again!"));
        return;
    }

    --Lives;
    PrintLine(TEXT("Incorrect!!! Lost a live"));

    if (Lives <= 0) {
        ClearScreen();
        PrintLine(TEXT("No live left. Game over"));
        PrintLine(TEXT("The hidden word is %s"), *HiddenWord);
        GameOver();
        return;
    }

    PrintLine(TEXT("Guess again, you have %i live(s)."), Lives);
}

bool UBullCowCartridge::IsIsogram(const FString& Word) const {
    for (int32 Index = 0; Index < Word.Len(); Index++) {
        for (int32 Comparision = Index + 1; Comparision < Word.Len(); Comparision++) {
            if (Word[Index] == Word[Comparision]) {
                return false;
            }
        }
    }
    return true;
}

TArray<FString> UBullCowCartridge::GetValidWords(const TArray<FString>& HiddenWords) const {
    TArray<FString> ValidWords;

    for (FString word : HiddenWords) {
        if (word.Len() >= 3 && word.Len() <= 8 && IsIsogram(word)) {
            ValidWords.Emplace(word);
        }
    }

    return ValidWords;
}