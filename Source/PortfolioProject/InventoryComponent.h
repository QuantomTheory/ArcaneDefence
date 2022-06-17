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

	TSubclassOf<ASpell> GetActiveSpellClass() const;


	UFUNCTION(BlueprintPure)
		int32 GetActiveSpellNum() const;

	void SetActiveSpell(int32 ChosenSpell);



	void SetActiveSpellCooldown();

private:
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Spell List", meta = (AllowPrivateAccess = "true"))
	TArray<TSubclassOf<ASpell>> SpellList;

	int32 ActiveSpell = 0;

	FTimerHandle CooldownTimer;

	UPROPERTY(EditDefaultsOnly)
		float CastCooldown = 0.f;


	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Spell List", meta = (AllowPrivateAccess = "true"))
		TSubclassOf<ASpell> DefaultSpellClass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Spell List", meta = (AllowPrivateAccess = "true"))
		TSubclassOf<ASpell> SpellOneClass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Spell List", meta = (AllowPrivateAccess = "true"))
		float SpellOneCooldown = 0.f;

	FTimerHandle SpellOneCooldownTimer;

	bool IsSpellOneReady = true;


	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Spell List", meta = (AllowPrivateAccess = "true"))
		TSubclassOf<ASpell> SpellTwoClass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Spell List", meta = (AllowPrivateAccess = "true"))
		float SpellTwoCooldown = 0.f;

	FTimerHandle SpellTwoCooldownTimer;

	bool IsSpellTwoReady = true;


	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Spell List", meta = (AllowPrivateAccess = "true"))
		TSubclassOf<ASpell> SpellThreeClass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Spell List", meta = (AllowPrivateAccess = "true"))
		float SpellThreeCooldown = 0.f;

	FTimerHandle SpellThreeCooldownTimer;

	bool IsSpellThreeReady = true;


	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Spell List", meta = (AllowPrivateAccess = "true"))
		TSubclassOf<ASpell> SpellFourClass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Spell List", meta = (AllowPrivateAccess = "true"))
		float SpellFourCooldown = 0.f;

	FTimerHandle SpellFourCooldownTimer;

	bool IsSpellFourReady = true;


	UFUNCTION(BlueprintPure)
		bool IsSpellReady(int32 ChosenSpell) const;

	UFUNCTION(BlueprintPure)
		float GetCooldownPercent(int32 ChosenSpell) const;


	void ResetSpellOneCooldown();
	void ResetSpellTwoCooldown();
	void ResetSpellThreeCooldown();
	void ResetSpellFourCooldown();
		
};
