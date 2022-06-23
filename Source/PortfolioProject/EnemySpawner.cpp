// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemySpawner.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystemComponent.h"
#include "EnemyCharacter.h"
#include "Kismet/KismetMathLibrary.h"

// Sets default values
AEnemySpawner::AEnemySpawner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Builds the Mesh and Spawn point of the Actor.
	SpawnerMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Spawner Mesh"));
	RootComponent = SpawnerMesh;

	SpawnPoint = CreateDefaultSubobject<USceneComponent>(TEXT("Spawn Point"));
	SpawnPoint->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void AEnemySpawner::BeginPlay()
{
	Super::BeginPlay();
	
	// Starts the Timers to Spawn the Melee and Ranged Enemies
	GetWorldTimerManager().SetTimer(SpawnMeleeTimer, this, &AEnemySpawner::SpawnMeleeEnemy, UKismetMathLibrary::RandomFloatInRange(MinSpawnMeleeRate, MaxSpawnMeleeRate));
	GetWorldTimerManager().SetTimer(SpawnRangedTimer, this, &AEnemySpawner::SpawnRangedEnemy, UKismetMathLibrary::RandomFloatInRange(MinSpawnRangedRate, MaxSpawnRangedRate));
	// These Spawn at a random intervals between a Maximum and Minimum Rate. This stops the flow of enemies feeling robotic.
}

// Called every frame
void AEnemySpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Spawns a Melee Enemy at the Spawn Point, and triggers a particle effect.
void AEnemySpawner::SpawnMeleeEnemy()
{
	FVector SpawnLocation = SpawnPoint->GetComponentLocation();
	FRotator SpawnRotator = SpawnPoint->GetComponentRotation();

	GetWorld()->SpawnActor<AEnemyCharacter>(SpawningMeleeCharacter, SpawnLocation, SpawnRotator);
	UGameplayStatics::SpawnEmitterAtLocation(this, SpawnEffect, SpawnLocation, SpawnRotator);

	// Starts the timer for the next melee enemy to be spawned, with a newly calculated random rate.
	GetWorldTimerManager().SetTimer(SpawnMeleeTimer, this, &AEnemySpawner::SpawnMeleeEnemy, UKismetMathLibrary::RandomFloatInRange(MinSpawnMeleeRate, MaxSpawnMeleeRate));
}

// Spawns a Melee Enemy at the Spawn Point, and triggers a particle effect.
void AEnemySpawner::SpawnRangedEnemy()
{
	FVector SpawnLocation = SpawnPoint->GetComponentLocation();
	FRotator SpawnRotator = SpawnPoint->GetComponentRotation();

	GetWorld()->SpawnActor<AEnemyCharacter>(SpawningRangedCharacter, SpawnLocation, SpawnRotator);
	UGameplayStatics::SpawnEmitterAtLocation(this, SpawnEffect, SpawnLocation, SpawnRotator);

	// Starts the timer for the next Ranged enemy to be spawned, with a newly calculated random rate.
	GetWorldTimerManager().SetTimer(SpawnRangedTimer, this, &AEnemySpawner::SpawnRangedEnemy, UKismetMathLibrary::RandomFloatInRange(MinSpawnRangedRate, MaxSpawnRangedRate));
}