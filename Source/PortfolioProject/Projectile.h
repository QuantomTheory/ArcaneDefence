// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Spell.h"
#include "Projectile.generated.h"

UCLASS()
class PORTFOLIOPROJECT_API AProjectile : public ASpell
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AProjectile();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	
	
// GAMEPLAY

private:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Mechanics", meta = (AllowPrivateAccess = "true"))
		class UProjectileMovementComponent* ProjectileMovement;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Mechanics", meta = (AllowPrivateAccess = "true"))
		float ProjectileSpeed;

protected:
	// The number of seconds before the spell explodes if it has not collided with anything
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Mechanics", meta = (AllowPrivateAccess = "true"))
		float ProjectileLifeSpan = 5.f;

	virtual void Explode();

	FTimerHandle ExplodeTimer;


// VISUALS

protected:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Mechanics", meta = (AllowPrivateAccess = "true"))
		UStaticMeshComponent* ProjectileMesh;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Visuals", meta = (AllowPrivateAccess = "true"))
		class UParticleSystem* ImpactParticles;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Visuals", meta = (AllowPrivateAccess = "true"))
		class UParticleSystem* CastParticles;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Visuals", meta = (AllowPrivateAccess = "true"))
		class UParticleSystemComponent* TrailParticles;


// AUDIO

private:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Audio", meta = (AllowPrivateAccess = "true"))
		class USoundBase* CastSound;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Audio", meta = (AllowPrivateAccess = "true"))
		USoundBase* MotionSound;

protected:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Audio", meta = (AllowPrivateAccess = "true"))
		USoundBase* ImpactSound;
};
