// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "EnemyAIController.generated.h"

/**
 * 
 */
UCLASS()
class PORTFOLIOPROJECT_API AEnemyAIController : public AAIController
{
	GENERATED_BODY()

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	AActor* GetTargetActor() const;

private:
	// The Behavior Tree Blueprint Class for Enemy AI Behavior
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "AI", meta = (AllowPrivateAccess = "true"))
		class UBehaviorTree* AIBehavior;

	// The TargetClass for the Enemy
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Defense Point", meta = (AllowPrivateAccess = "true"))
		TSubclassOf<AActor> TargetClass;
	
	AActor* TargetActor;
	
};
