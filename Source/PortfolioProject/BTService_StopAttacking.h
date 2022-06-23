// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "BTService_StopAttacking.generated.h"

/**
 * 
 */
UCLASS()
class PORTFOLIOPROJECT_API UBTService_StopAttacking : public UBTService
{
	GENERATED_BODY()

public:
	UBTService_StopAttacking();

protected:
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds);
	
};
