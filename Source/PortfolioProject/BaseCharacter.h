// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "HealthComponent.h"
#include "BaseCharacter.generated.h"

UCLASS()
class PORTFOLIOPROJECT_API ABaseCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ABaseCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void IsDead();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:
	// The functions to control movement
	void MoveForward(float AxisValue);
	void MoveRight(float AxisValue);
	void TiltUp(float AxisValue);
	void TurnRight(float AxisValue);

	void Jump();
	void StartSprint();
	void EndSprint();

	// The multiplier variable to determine how fast sprinting is.
	UPROPERTY(EditDefaultsOnly, Category = "Movement")
		float SprintMultiplier = 2.f;

	float MoveSpeed;

	UPROPERTY(EditAnywhere, Category = "Movement")
		float AirControlSpeed = 100;

	UHealthComponent* HealthComponent;

	// The effects to play on character death.
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Visuals", meta = (AllowPrivateAccess = "true"))
		class UParticleSystem* DeathEffect;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Audio", meta = (AllowPrivateAccess = "true"))
		class USoundBase* DeathSound;
};
