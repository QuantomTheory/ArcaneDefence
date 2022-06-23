// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyAIController.h"
#include "EnemyCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "ArcaneDefenseGameMode.h"

// Setup the Behavior Tree and Blackboard values for the Enemy AI Behavior Tree
void AEnemyAIController::BeginPlay()
{
	Super::BeginPlay();

	if (AIBehavior)
	{
		RunBehaviorTree(AIBehavior);

		TargetActor = UGameplayStatics::GetActorOfClass(GetWorld(), TargetClass);
		
		if (TargetActor)
		{
			GetBlackboardComponent()->SetValueAsObject(TEXT("Target"), TargetActor);
			GetBlackboardComponent()->SetValueAsVector(TEXT("TargetLocation"), TargetActor->GetActorLocation());
		}		
	}
}

void AEnemyAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime); 
	
	// Constantly Updates the Target Actors Location.
	if (TargetActor)
	{
		GetBlackboardComponent()->SetValueAsVector(TEXT("TargetLocation"), TargetActor->GetActorLocation());
	}

}

// Return the Target Actor Pointer
AActor* AEnemyAIController::GetTargetActor() const
{
	return TargetActor;
}

