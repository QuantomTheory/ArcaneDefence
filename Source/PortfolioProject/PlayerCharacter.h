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



// CHARACTER COMPONENTS
private:
	// The Spawn Point for spells to originate from
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Mechanics", meta = (AllowPrivateAccess = "true"))
		USceneComponent* SpellSpawnPoint;

	// The Spring Arm the Spell Spawn point is attached to
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Mechanics", meta = (AllowPrivateAccess = "true"))
		class USpringArmComponent* SpellSpringArm;

	// The attached Inventory Component
	class UInventoryComponent* InventoryComponent;



// SPELLCASTING FUNCTIONS

public:
// The following four are Blueprint Callable as they also control the Player Actors casting animations.

	// Returns the bool denoting if the player is currently casting
	UFUNCTION(BlueprintCallable)
		bool GetIsCasting();

	// Updates the bool denoting if the player is currently casting
	UFUNCTION(BlueprintCallable)
		void SetIsCasting(bool NewCastingBool);

	// Returns the bool denoting if the player is currently casting the Ultimate
	UFUNCTION(BlueprintCallable)
		bool GetIsUltimateCasting();

	// Updates the bool denoting if player is currently casting
	UFUNCTION(BlueprintCallable)
		void SetIsUltimateCasting(bool NewCastingBool);

private:
	// Functions that set the specified spell as the Current Spell
	void SetSpellDefault();
	void SetSpellOne();
	void SetSpellTwo();

	// Funtions to control the casting of spells
	void StartCastingSpell();
	void StopCastingSpell();

	// The Function to cast the Arcane Blast Spell
	void ArcaneBlastSpell();

	// The Function to cast the Arcane Bomb Spell
	void ArcaneBombSpell();

	// The Function to begin casting the Ultimate Beam Spell
	void UltimateSpell();
	// The Function to finish casting the Ultimate Beam Spell
	void EndUltimate();



// SPELLCASTING VARIABLES

	// CASTING VARIABLES
	// Bool to control if spells are being cast, also used in UE for animation activation
	bool IsCasting = false;
	bool IsUltimateCasting = false;

	// The FireRate for the Default Spell
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Mechanics", meta = (AllowPrivateAccess = "true"))
		float DefaultSpellRate;



	// CURRENT SPELL VARIABLES
	// The Class of the currently active spell
	TSubclassOf<class ASpell> CurrentSpellClass;
	
	// The Inventory Number of the Currently Active Spell
	int32 CurrentSpellNum = 0;

	// The Instance of the Currently Active Spell
	ASpell* CurrentSpell = nullptr;

	float CurrentSpellInterval = 0;



	// ULTIMATE BEAM
	// The Actor for the Beam Ultimate
	class ABeam* UltimateActor = nullptr;

	// The Timer to track the duration of the Ultimate
	FTimerHandle UltimateCastTimer;
	
};
