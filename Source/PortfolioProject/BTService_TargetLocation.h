// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Services/BTService_BlackboardBase.h"
#include "BTService_TargetLocation.generated.h"

/**
 * 
 */
UCLASS()
class PORTFOLIOPROJECT_API UBTService_TargetLocation : public UBTService_BlackboardBase
{
	GENERATED_BODY()

public:
	UBTService_TargetLocation();

protected:
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds);
	
};
