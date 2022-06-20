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

	// Starts the Game Timer. The player must defend th point for this length of time.
	GetWorldTimerManager().SetTimer(GameTimer, this, &AArcaneDefenseGameMode::TimeUp, GameLength);
}

// Trigger by the BaseCharacter class when HP reaches 0
void AArcaneDefenseGameMode::PawnKilled(APawn* PawnKilled)
{
	Super::PawnKilled(PawnKilled);

	APlayerWizardController* PlayerController = Cast<APlayerWizardController>(PawnKilled->GetController());
	if (PlayerController)
	{
		// If the pawn destroyed was the Player, triggers the EndGame function with the Lose condition.
		EndGame(false);
		UE_LOG(LogTemp, Warning, TEXT("EndGame: Lose"));
	}
}

// Triggered by the PlayerDefencePoint class when it's HP reaches 0
void AArcaneDefenseGameMode::DefensePointDestroyed(AActor* ActorDestroyed)
{
	Super::DefensePointDestroyed(ActorDestroyed);
	UE_LOG(LogTemp, Warning, TEXT("EndGame: Lose"));

	// Triggers the EndGame function with the Lose condition.
	EndGame(false);
}

// Returns the GameTime remaining
float AArcaneDefenseGameMode::GetRemainingTime()
{
	return GetWorldTimerManager().GetTimerRemaining(GameTimer);
}

// Triggers when the GameTimer has elapsed.
void AArcaneDefenseGameMode::TimeUp()
{
	UE_LOG(LogTemp, Warning, TEXT("EndGame: Win"));

	// Triggers the EndGame function with the Win condition.
	EndGame(true);
}

// Triggered by one of the above functions.
void AArcaneDefenseGameMode::EndGame(bool bIsPlayerWinner)
{
	for (AController* Controller : TActorRange<AController>(GetWorld()))
	{
		// Checks if the current controller is the player controller, and if the Win condition passed in was true.
		bool bIsWinner = Controller->IsPlayerController() == bIsPlayerWinner;
		Controller->GameHasEnded(Controller->GetPawn(), bIsWinner);
	}
}