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

	// Build out the Components for this Actor
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

	// Get the PlayerPawn...
	APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
	if (PlayerPawn == nullptr) return;
	// ... and set it as this actors Owner
	SetOwner(PlayerPawn);

	// Check the HEalth Component is not null, the activate it.
	if (HealthComponent == nullptr) return;
	HealthComponent->Activate();

	// Sawn the Sound Emitter for the Ambiant Sound
	if (AmbiantSound)
	{
		UGameplayStatics::SpawnSoundAttached(AmbiantSound, RootComponent, TEXT("NAME_None"), ((FVector3d)(ForceInit)), FRotator::ZeroRotator, EAttachLocation::KeepRelativeOffset, true);
	}
}

// Called every frame
void APlayerDefensePoint::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// Continuosly check if IsDestroyed.
	IsDestroyed();
}

// Checks the attached Health Component for if Health has reached zero
void APlayerDefensePoint::IsDestroyed()
{
	if (HealthComponent->IsDead())
	{
		// If Health has reached zero, spawn destruction effects, and hide the actor
		UGameplayStatics::SpawnEmitterAtLocation(this, DestructionEffect, Mesh->GetComponentLocation(), Mesh->GetComponentRotation());

		if (DestructionSound)
		{
			UGameplayStatics::SpawnSoundAtLocation(this, DestructionSound, Mesh->GetComponentLocation(), Mesh->GetComponentRotation());
		}
		Mesh->SetVisibility(false);
		AmbiantEffect->SetVisibility(false);

		// Trigger the DefensePointDestroyed function of the GameMode
		AArcaneDefenseGameMode* GameMode = Cast< AArcaneDefenseGameMode>(UGameplayStatics::GetGameMode(GetWorld()));
		if (GameMode)
		{
			GameMode->DefensePointDestroyed(this);
		}

		// Destroy the Actor
		Destroy();
	}
}