// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerWizardController.h"
#include "Blueprint/UserWidget.h"
#include "TimerManager.h"

void APlayerWizardController::BeginPlay()
{
	Super::BeginPlay();

	StartScreen = CreateWidget(this, StartScreenClass);
	if (StartScreen)
	{
		StartScreen->AddToViewport();
	}

	GetWorldTimerManager().SetTimer(StartPlayTimer, this, &APlayerWizardController::StartPlay, StartPlayDelay);
}

void APlayerWizardController::GameHasEnded(AActor* EndGameFocus, bool bIsWinner)
{
	Super::GameHasEnded(EndGameFocus, bIsWinner);

	if (HUD)
	{
		HUD->RemoveFromViewport();
	}

	if (bIsWinner)
	{
		UUserWidget* WinScreen = CreateWidget(this, WinScreenClass);
		if (WinScreen)
		{
			WinScreen->AddToViewport();
			PlayerWin = true;
		}
	}
	else
	{
		UUserWidget* LoseScreen = CreateWidget(this, LoseScreenClass);
		if (LoseScreen)
		{
			LoseScreen->AddToViewport();
		}
	}


	GetWorldTimerManager().SetTimer(RestartTimer, this, &APlayerController::RestartLevel, RestartDelay);

}

bool APlayerWizardController::GetPlayerWin() const
{
	return PlayerWin;
}

float APlayerWizardController::GetCurretTimer() const
{
	return GetWorldTimerManager().GetTimerRemaining(RestartTimer);
}

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

