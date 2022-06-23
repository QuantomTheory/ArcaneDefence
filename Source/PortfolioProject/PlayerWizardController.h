// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "PlayerWizardController.generated.h"

/**
 * 
 */
UCLASS()
class PORTFOLIOPROJECT_API APlayerWizardController : public APlayerController
{
	GENERATED_BODY()

public:
	void BeginPlay();

	virtual void GameHasEnded(class AActor* EndGameFocus = nullptr, bool bIsWinner = false) override;

	// Returns the PlayerWin bool, called from UE
	UFUNCTION(BlueprintPure)
		bool GetPlayerWin() const;

	UFUNCTION(BlueprintPure)
		float GetCurretTimer() const;

private:

	void StartPlay();

	// The Length of time the Start Screen is displayed
	float StartPlayDelay = 5.f;

	FTimerHandle StartPlayTimer;

	// The Widget Classes
	UPROPERTY(EditAnywhere)
		TSubclassOf<UUserWidget> HUDClass;
	UPROPERTY(EditAnywhere)
		TSubclassOf<UUserWidget> StartScreenClass;
	UPROPERTY(EditAnywhere)
		TSubclassOf<UUserWidget> WinScreenClass;
	UPROPERTY(EditAnywhere)
		TSubclassOf<UUserWidget> LoseScreenClass;

	UPROPERTY()
		class UUserWidget* HUD;
	UPROPERTY()
		UUserWidget* StartScreen;

	UPROPERTY(EditAnywhere)
		float RestartDelay = 5.f;

	UPROPERTY()
		bool PlayerWin = false;

	FTimerHandle RestartTimer;

	
};
