// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "PlayerHUD.generated.h"


class UUserWidget;
/**
 * 
 */
UCLASS()
class PORTFOLIOPROJECT_API APlayerHUD : public AHUD
{
	GENERATED_BODY()

public:
	void BeginPlay();

private:


	UPROPERTY(EditAnywhere)
		TSubclassOf<UUserWidget> HUDClass;

	UPROPERTY()
		class UUserWidget* HUD;
	
};
