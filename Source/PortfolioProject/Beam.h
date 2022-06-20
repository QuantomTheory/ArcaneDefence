// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Kismet/GameplayStatics.h"
#include "Spell.h"
#include "Beam.generated.h"

UCLASS()
class PORTFOLIOPROJECT_API ABeam : public ASpell
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABeam();

	float GetBeamLifeSpan();

	void AttachBeamToCaster(USceneComponent* UltimateSpawnPoint);

	void EndBeam();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	bool BeamTrace(TArray<FHitResult>& OutHitResultArray);


// GAMEPLAY

private:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Mechanics", meta = (AllowPrivateAccess = "true"))
		float BeamDamage;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Mechanics", meta = (AllowPrivateAccess = "true"))
		float BeamRange;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Mechanics", meta = (AllowPrivateAccess = "true"))
		float BeamRadius;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Mechanics", meta = (AllowPrivateAccess = "true"))
		float ProjectileSpeed;

	virtual void DealDamage(const FHitResult& Hit);

protected:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Mechanics", meta = (AllowPrivateAccess = "true"))
		float BeamLifeSpan = 5.f;

	FTimerHandle CastTimer;


// VISUALS

protected:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Visuals", meta = (AllowPrivateAccess = "true"))
		USceneComponent* BeamMesh;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Visuals", meta = (AllowPrivateAccess = "true"))
		UStaticMeshComponent* ImpactMesh;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Visuals", meta = (AllowPrivateAccess = "true"))
		TSubclassOf<class UCameraShakeBase> CastShakeClass;


// AUDIO

private:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Audio", meta = (AllowPrivateAccess = "true"))
		class USoundBase* BeamSound;

};
