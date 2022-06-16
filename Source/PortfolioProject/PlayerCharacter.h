// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseCharacter.h"
#include "PlayerCharacter.generated.h"

/**
 * 
 */
UCLASS()
class PORTFOLIOPROJECT_API APlayerCharacter : public ABaseCharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	APlayerCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION(BlueprintCallable)
		bool GetIsCasting();

	UFUNCTION(BlueprintCallable)
		void SetIsCasting(bool NewCastingBool);

	UFUNCTION(BlueprintCallable)
		bool GetIsUltimateCasting();

	UFUNCTION(BlueprintCallable)
		void SetIsUltimateCasting(bool NewCastingBool);

private:

	void SetSpellDefault();
	void SetSpellOne();
	void SetSpellTwo();
	void SetSpellThree();
	void SetSpellFour();

	void BeginSpell();
	void StartCastingSpell();
	void StopCastingSpell();

	void ArcaneBlastSpell();
	void ArcaneBombSpell();

	void UltimateSpell();
	void EndUltimate();


		bool IsCasting = false;
		bool IsUltimateCasting = false;

	TSubclassOf<class ASpell> CurrentSpellClass;

	int32 CurrentSpellNum = 0;

	class UInventoryComponent* InventoryComponent;

	FTimerHandle CastTimer;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Mechanics", meta = (AllowPrivateAccess = "true"))
		USceneComponent* UltimateSpawnPoint;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Mechanics", meta = (AllowPrivateAccess = "true"))
		class USpringArmComponent* UltimateSpringArm;

	class ABeam* UltimateActor = nullptr;

	ASpell* CurrentSpell = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Mechanics", meta = (AllowPrivateAccess = "true"))
		float DefaultSpellRate;

	float CurrentSpellInterval = 0;
	
};
