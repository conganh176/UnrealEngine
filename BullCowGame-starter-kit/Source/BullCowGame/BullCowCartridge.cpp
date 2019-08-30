// Fill out your copyright notice in the Description page of Project Settings.
#include "BullCowCartridge.h"

void UBullCowCartridge::BeginPlay() // When the game starts
{
    Super::BeginPlay();
    PrintLine(TEXT("Hello World"));
}

void UBullCowCartridge::OnInput(const FString& Input) // When the player hits enter
{
    ClearScreen();
    FString HiddenWord = TEXT("shit");
    PrintLine(Input);
    if (Input == HiddenWord)
    {
        PrintLine(TEXT("Correct!!!"));
    }
    else
    {
        PrintLine(TEXT("Incorrect!!!"));
    }
}