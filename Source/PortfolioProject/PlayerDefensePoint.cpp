// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerDefensePoint.h"
#include "Particles/ParticleSystemComponent.h"
#include "Components/BoxComponent.h"
#include "ArcaneDefenseGameMode.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
APlayerDefensePoint::APlayerDefensePoint()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BaseScene = CreateDefaultSubobject<USceneComponent>(TEXT("Base"));
	RootComponent = BaseScene;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(RootComponent);

	AmbiantEffect = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Particle Trail"));
	AmbiantEffect->SetupAttachment(Mesh);

	HealthComponent = CreateDefaultSubobject<UHealthComponent>(TEXT("Health Comp"));
	HealthComponent->SetActive(true);
}

// Called when the game starts or when spawned
void APlayerDefensePoint::BeginPlay()
{
	Super::BeginPlay();

	APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
	if (PlayerPawn == nullptr)
	{
		return;
	}
	SetOwner(PlayerPawn);
	if (HealthComponent == nullptr)
	{
		return;
	}

	HealthComponent->Activate();

	if (AmbiantSound)
	{
		UGameplayStatics::SpawnSoundAttached(AmbiantSound, RootComponent, TEXT("NAME_None"), ((FVector3d)(ForceInit)), FRotator::ZeroRotator, EAttachLocation::KeepRelativeOffset, true);
	}
}

// Called every frame
void APlayerDefensePoint::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	IsDestroyed();
}

void APlayerDefensePoint::IsDestroyed()
{
	if (HealthComponent->IsDead())
	{
		UGameplayStatics::SpawnEmitterAtLocation(this, DestructionEffect, Mesh->GetComponentLocation(), Mesh->GetComponentRotation());

		if (DestructionSound)
		{
			UGameplayStatics::SpawnSoundAtLocation(this, DestructionSound, Mesh->GetComponentLocation(), Mesh->GetComponentRotation());
		}
		Mesh->SetVisibility(false);
		AmbiantEffect->SetVisibility(false);

		AArcaneDefenseGameMode* GameMode = Cast< AArcaneDefenseGameMode>(UGameplayStatics::GetGameMode(GetWorld()));
		if (GameMode)
		{
			GameMode->DefensePointDestroyed(this);
		}

		Destroy();
	}
}