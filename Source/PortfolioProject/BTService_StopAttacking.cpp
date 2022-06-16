// Fill out your copyright notice in the Description page of Project Settings.


#include "BTService_StopAttacking.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/GameplayStatics.h"
#include "EnemyAIController.h"
#include "EnemyCharacter.h"

UBTService_StopAttacking::UBTService_StopAttacking()
{
	NodeName = TEXT("Stop Attacking");
}

void UBTService_StopAttacking::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	AAIController* OwnerController = OwnerComp.GetAIOwner();
	if (OwnerController == nullptr) return;

	AEnemyCharacter* EnemyPawn = Cast<AEnemyCharacter>(OwnerController->GetPawn());
	if (EnemyPawn == nullptr) return;

	EnemyPawn->SetIsAttacking(false);
}

