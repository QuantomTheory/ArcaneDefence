// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EnemySpawner.generated.h"

UCLASS()
class PORTFOLIOPROJECT_API AEnemySpawner : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AEnemySpawner();


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;


private:

// ACTOR COMPONENTS
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Mechanics", meta = (AllowPrivateAccess = "true"))
		UStaticMeshComponent* SpawnerMesh;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Mechanics", meta = (AllowPrivateAccess = "true"))
		USceneComponent* SpawnPoint;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Visuals", meta = (AllowPrivateAccess = "true"))
		class UParticleSystem* SpawnEffect;


// MELEE ENEMY SPAWNING
	void SpawnMeleeEnemy();

	// The Class of the melee character to be spawned
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Mechanics", meta = (AllowPrivateAccess = "true"))
		TSubclassOf<class AEnemyCharacter> SpawningMeleeCharacter;

	// The Max and Min Spawn rates, used to calculate the random spawn rate
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Spawning", meta = (AllowPrivateAccess = "true"))
		float MaxSpawnMeleeRate;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Spawning", meta = (AllowPrivateAccess = "true"))
		float MinSpawnMeleeRate;

	FTimerHandle SpawnMeleeTimer;


// RANGED ENEMY SPAWNING
	void SpawnRangedEnemy();

	// The Class of the ranged character to be spawned
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Mechanics", meta = (AllowPrivateAccess = "true"))
		TSubclassOf<class AEnemyCharacter> SpawningRangedCharacter;

	// The Max and Min Spawn rates, used to calculate the random spawn rate
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Spawning", meta = (AllowPrivateAccess = "true"))
		float MaxSpawnRangedRate;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Spawning", meta = (AllowPrivateAccess = "true"))
		float MinSpawnRangedRate;

	FTimerHandle SpawnRangedTimer;

};
