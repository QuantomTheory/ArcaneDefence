// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerWizardController.h"
#include "Blueprint/UserWidget.h"
#include "TimerManager.h"

void APlayerWizardController::BeginPlay()
{
	Super::BeginPlay();

	// SetUp and Show the Start Screen Widget
	StartScreen = CreateWidget(this, StartScreenClass);
	if (StartScreen)
	{
		StartScreen->AddToViewport();
	}

	// The Timer for how long the Start Screen is shown
	GetWorldTimerManager().SetTimer(StartPlayTimer, this, &APlayerWizardController::StartPlay, StartPlayDelay);
}

// Changes the Start Screen Widget for the HUD Widget
void APlayerWizardController::StartPlay()
{
	if (StartScreen)
	{
		StartScreen->RemoveFromViewport();
	}

	HUD = CreateWidget(this, HUDClass);
	if (HUD)
	{
		HUD->AddToViewport();
	}
}

// RUpdates the Widgets for the End Game
void APlayerWizardController::GameHasEnded(AActor* EndGameFocus, bool bIsWinner)
{
	Super::GameHasEnded(EndGameFocus, bIsWinner);

	// Removes the HUD Widget
	if (HUD)
	{
		HUD->RemoveFromViewport();
	}

	// Depending on if the Player Won or Lost
	if (bIsWinner)
	{
		// Displays the Win Screen Widget...
		UUserWidget* WinScreen = CreateWidget(this, WinScreenClass);
		if (WinScreen)
		{
			WinScreen->AddToViewport();
			PlayerWin = true;
		}
	}
	else
	{
		// ... or the Lose Screen Widget
		UUserWidget* LoseScreen = CreateWidget(this, LoseScreenClass);
		if (LoseScreen)
		{
			LoseScreen->AddToViewport();
		}
	}

	// Starts the Timer to Restart the Game
	GetWorldTimerManager().SetTimer(RestartTimer, this, &APlayerController::RestartLevel, RestartDelay);

}

// Returns the PlayerWin bool, called from UE
bool APlayerWizardController::GetPlayerWin() const
{
	return PlayerWin;
}

// Returns the remaning time on the Restart Timer for Display on the Win and Lose Screen Widgets
float APlayerWizardController::GetCurretTimer() const
{
	return GetWorldTimerManager().GetTimerRemaining(RestartTimer);
}

