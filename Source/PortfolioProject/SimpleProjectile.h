// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Projectile.h"
#include "SimpleProjectile.generated.h"

/**
 * 
 */
UCLASS()
class PORTFOLIOPROJECT_API ASimpleProjectile : public AProjectile
{
	GENERATED_BODY()

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


// GAMEPLAY

private:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Mechanics", meta = (AllowPrivateAccess = "true"))
		float ImpactDamage;

	UFUNCTION()
		void OnHit(
			UPrimitiveComponent* HitComp,
			AActor* OtherActor,
			UPrimitiveComponent* OtherComp,
			FVector NormalImpulse,
			const FHitResult& Hit
		);

	virtual void DealDamage(AActor* MyOwner, AActor* OtherActor);
	
};
