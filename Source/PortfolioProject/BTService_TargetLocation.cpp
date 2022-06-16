// Fill out your copyright notice in the Description page of Project Settings.


#include "BTService_TargetLocation.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/GameplayStatics.h"

UBTService_TargetLocation::UBTService_TargetLocation()
{
	NodeName = TEXT("Update Target Location");
}

void UBTService_TargetLocation::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);
}

