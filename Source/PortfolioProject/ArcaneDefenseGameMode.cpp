// Fill out your copyright notice in the Description page of Project Settings.


#include "ArcaneDefenseGameMode.h"
#include "PlayerWizardController.h"
#include "EngineUtils.h"
#include "EnemyAIController.h"
#include "PlayerDefensePoint.h"
#include "Kismet/GameplayStatics.h"

void AArcaneDefenseGameMode::BeginPlay()
{
	Super::BeginPlay();

	GetWorldTimerManager().SetTimer(GameTimer, this, &AArcaneDefenseGameMode::TimeUp, GameLength);
}

void AArcaneDefenseGameMode::PawnKilled(APawn* PawnKilled)
{
	Super::PawnKilled(PawnKilled);

	APlayerWizardController* PlayerController = Cast<APlayerWizardController>(PawnKilled->GetController());
	if (PlayerController)
	{
		EndGame(false);
		UE_LOG(LogTemp, Warning, TEXT("EndGame: Lose"));
	}
}

void AArcaneDefenseGameMode::DefensePointDestroyed(AActor* ActorDestroyed)
{
	Super::DefensePointDestroyed(ActorDestroyed);
	UE_LOG(LogTemp, Warning, TEXT("EndGame: Lose"));

	EndGame(false);
}

float AArcaneDefenseGameMode::GetRemainingTime()
{
	return GetWorldTimerManager().GetTimerRemaining(GameTimer);
}

void AArcaneDefenseGameMode::TimeUp()
{
	UE_LOG(LogTemp, Warning, TEXT("EndGame: Win"));
	EndGame(true);
}

void AArcaneDefenseGameMode::EndGame(bool bIsPlayerWinner)
{
	for (AController* Controller : TActorRange<AController>(GetWorld()))
	{
		bool bIsWinner = Controller->IsPlayerController() == bIsPlayerWinner;
		Controller->GameHasEnded(Controller->GetPawn(), bIsWinner);
	}
}