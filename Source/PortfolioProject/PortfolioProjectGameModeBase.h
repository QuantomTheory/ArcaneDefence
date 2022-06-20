// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "PortfolioProjectGameModeBase.generated.h"


// The Default Base Game Mode. Parent Class to the ArcaneDefenseGameMode
UCLASS()
class PORTFOLIOPROJECT_API APortfolioProjectGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public:

	virtual void BeginPlay() override;

	virtual void PawnKilled(APawn* PawnKilled);

	virtual void DefensePointDestroyed(AActor* ActorDestroyed);
	
};
