// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseCharacter.h"
#include "GameFramework/Character.h"
#include "EnemyCharacter.generated.h"

UCLASS()
class PORTFOLIOPROJECT_API AEnemyCharacter : public ABaseCharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AEnemyCharacter();

	UFUNCTION(BlueprintCallable)
		bool GetIsAttacking() const;

	UFUNCTION(BlueprintCallable)
		void SetIsAttacking(bool NewValue);

	UFUNCTION(BlueprintCallable)
		void Attack();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:

	bool IsAttacking = false;


// MELEE ATTACKER
	void MeleeAttack();

	// The damage dealt by the melee attack
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Spell List", meta = (AllowPrivateAccess = "true"))
		float MeleeAttackDamage = 5.f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Audio", meta = (AllowPrivateAccess = "true"))
		class USoundBase* MeleeAttackSound;


// RANGED ATTACKER
	void RangedAttack();

	// The SpellClass of the Ranged Attack
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Spell List", meta = (AllowPrivateAccess = "true"))
		TSubclassOf<class ASpell> RangedSpellClass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Spell List", meta = (AllowPrivateAccess = "true"))
		bool IsRangedAttacker = false;
};
