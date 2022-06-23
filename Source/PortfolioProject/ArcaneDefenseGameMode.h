// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PortfolioProjectGameModeBase.h"
#include "ArcaneDefenseGameMode.generated.h"

/**
 * 
 */
UCLASS()
class PORTFOLIOPROJECT_API AArcaneDefenseGameMode : public APortfolioProjectGameModeBase
{
	GENERATED_BODY()

public:
	virtual void BeginPlay() override;

	virtual void PawnKilled(APawn* PawnKilled) override;

	virtual void DefensePointDestroyed(AActor* ActorDestroyed) override;


	// Allow the remaining Game time to be return in UE, used to update the on screen timer.
	UFUNCTION(BlueprintCallable)
		virtual float GetRemainingTime();

private:
	void EndGame(bool bIsPlayerWinner);

	void TimeUp();

	// The length in seconds for the game to last (i.e. the length of time the player must defend the point,
	UPROPERTY(EditDefaultsOnly)
		float GameLength = 305.f;

	FTimerHandle GameTimer;

	
};
