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

	void MeleeAttack();
	void RangedAttack();


	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Spell List", meta = (AllowPrivateAccess = "true"))
		TSubclassOf<class ASpell> SpellClass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Spell List", meta = (AllowPrivateAccess = "true"))
		float AttackDamage = 5.f;

	bool IsAttacking = false;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Spell List", meta = (AllowPrivateAccess = "true"))
		bool IsRangedAttacker = false;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Audio", meta = (AllowPrivateAccess = "true"))
		class USoundBase* AttackSound;
};
