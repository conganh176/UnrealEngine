// Fill out your copyright notice in the Description page of Project Settings.
#include "BullCowCartridge.h"

void UBullCowCartridge::BeginPlay() {         // When the game starts
    Super::BeginPlay();

    //Set up game
    SetupGame();

    PrintLine(TEXT("The hidden word is: %s. \nHas %i characters long"), *HiddenWord, HiddenWord.Len());
}

void UBullCowCartridge::OnInput(const FString& Input) {      // When the player hits enter
    if (bGameOver) {
        ClearScreen();
        SetupGame();
    } else {
        //Check guess
        ProcessGuess(Input);
    }
}

void UBullCowCartridge::SetupGame() {
    HiddenWord = TEXT("shit");
    Lives = HiddenWord.Len();
    bGameOver = false;
    
    //Welcome text
    PrintLine(TEXT("Welcome to Bull Cows!"));
    PrintLine(TEXT("Guess the %i letter words."), HiddenWord.Len());
    PrintLine(TEXT("You have %i live(s)."), Lives);
    PrintLine(TEXT("Type your word and press enter to continue"));


}

void UBullCowCartridge::GameOver() {
    bGameOver = true;
    PrintLine(TEXT("Game over. Press enter to play again!"));
}

void UBullCowCartridge::ProcessGuess(FString Guess) {
    if (Guess == HiddenWord) {
        PrintLine(TEXT("Correct!!!"));
        GameOver();
        return;
    }

    // if (!IsIsogram) {
    //     PrintLine(TEXT("No repeating letter. Guess again!"));
    // }

    --Lives;
    PrintLine(TEXT("Incorrect!!! Lost a live"));

    if (Lives <= 0) {
        ClearScreen();
        PrintLine(TEXT("No live left. Game over"));
        PrintLine(TEXT("The hidden word is %s"), *HiddenWord);
        GameOver();
        return;
    }

    if (Guess.Len() != HiddenWord.Len()) {
        PrintLine(TEXT("Try again. You got %i live(s)."), Lives);
        PrintLine(TEXT("The hidden word is %i letters long"), HiddenWord.Len());
        return;
    }

    PrintLine(TEXT("Guess again, you have %i live(s)."), Lives);
}