// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Spell.h"
#include "InventoryComponent.generated.h"

class AProjectile;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PORTFOLIOPROJECT_API UInventoryComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UInventoryComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;


// GENERAL
public:
	// Retuns the Currently Active Spell as a Spell class
	TSubclassOf<ASpell> GetActiveSpellClass() const;

	// Retuns the Currently Active Spell by its Spell Number
	UFUNCTION(BlueprintPure)
		int32 GetActiveSpellNum() const;

	// Sets the Active Spell Class based on the passed in Number
	void SetActiveSpell(int32 ChosenSpell);

	// Starts the Cooldown Timer on the currently Active Spell (Triggered on Cast)
	void SetActiveSpellCooldown();

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Spell List", meta = (AllowPrivateAccess = "true"))
	TArray<TSubclassOf<ASpell>> SpellList;

	int32 ActiveSpell = 0;

	// Is the chosen spell ready (has it's cooldown elapsed.)
	UFUNCTION(BlueprintPure)
		bool IsSpellReady(int32 ChosenSpell) const;

	// Returns the cooldown elapsed time as a percentage of the total cooldown time
	UFUNCTION(BlueprintPure)
		float GetCooldownPercent(int32 ChosenSpell) const;


// DEFAULT SPELL
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Spell List", meta = (AllowPrivateAccess = "true"))
		TSubclassOf<ASpell> DefaultSpellClass;


// SPELL ONE
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Spell List", meta = (AllowPrivateAccess = "true"))
		TSubclassOf<ASpell> SpellOneClass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Spell List", meta = (AllowPrivateAccess = "true"))
		float SpellOneCooldown = 0.f;

	FTimerHandle SpellOneCooldownTimer;

	bool IsSpellOneReady = true;

	void ResetSpellOneCooldown();

// SPELL TWO
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Spell List", meta = (AllowPrivateAccess = "true"))
		TSubclassOf<ASpell> SpellTwoClass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Spell List", meta = (AllowPrivateAccess = "true"))
		float SpellTwoCooldown = 0.f;

	FTimerHandle SpellTwoCooldownTimer;

	bool IsSpellTwoReady = true;

	void ResetSpellTwoCooldown();


		
};
