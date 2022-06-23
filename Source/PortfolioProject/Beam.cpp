// Fill out your copyright notice in the Description page of Project Settings.


#include "Beam.h"	
#include "NiagaraSystem.h"
#include "BaseCharacter.h"

// Sets default values
ABeam::ABeam()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BeamMesh = CreateDefaultSubobject<USceneComponent>(TEXT("Beam Root"));
	RootComponent = BeamMesh;
}

// Called when the beam object is spawned
void ABeam::BeginPlay()
{
	Super::BeginPlay();

	// Starts the beam sound
	if (BeamSound)
	{
		UGameplayStatics::SpawnSoundAttached(BeamSound, RootComponent, TEXT("NAME_None"),((FVector3d)(ForceInit)), FRotator::ZeroRotator, EAttachLocation::KeepRelativeOffset, true);
	}
}

// Beam LifeSpan Getter
float ABeam::GetBeamLifeSpan()
{
	return BeamLifeSpan;
}

// Attaches the beam mesh to the character to allow aiming
void ABeam::AttachBeamToCaster(USceneComponent* UltimateSpawnPoint)
{
	AttachToComponent(UltimateSpawnPoint, FAttachmentTransformRules::KeepWorldTransform);
}

// Called every frame
void ABeam::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// If the Beam hit an Actor
	FHitResult HitResult;
	if (BeamTrace(HitResult))
	{
		UE_LOG(LogTemp, Warning, TEXT("Hit Actor"));
		AActor* HitActor = HitResult.GetActor();
		if (HitActor == nullptr) return;
		AActor* OwnerActor = GetOwner();
		if (OwnerActor == nullptr) return;

		if (HitActor != OwnerActor)
		{
			ABaseCharacter* HitCharacter = Cast<ABaseCharacter>(HitActor);
			if(HitCharacter)
			{
				// Deal damage to the hit Actor.
				DealDamage(HitResult);
			}
		}
	}
}

// The function to carry out the shape trace to find the actors hit by the beam.
bool ABeam::BeamTrace(FHitResult& OutHitResult)
{
	FVector BeamLocation = GetActorLocation();
	FRotator BeamRotation = GetActorRotation();

	FVector End = BeamLocation + (BeamRotation.Vector() * BeamRange);
	FCollisionQueryParams Params;
	Params.AddIgnoredActor(this);
	Params.AddIgnoredActor(GetOwner());

	FCollisionShape Shape = FCollisionShape::MakeSphere(BeamRadius);

	// Returns an FHitResult
	return GetWorld()->SweepSingleByObjectType(OutHitResult, BeamLocation, End, BeamRotation.Quaternion(), FCollisionObjectQueryParams::AllDynamicObjects, Shape, Params);
}

// Deal the Damage to Traced Actors
void ABeam::DealDamage(const FHitResult& Hit)
{
	AActor* OtherActor = Hit.GetActor();
	if (OtherActor == nullptr) return;
	AActor* MyOwner = GetOwner();
	if (MyOwner == nullptr)
	{
		Destroy();
		return;
	}

	AController* InstigatorController = MyOwner->GetInstigatorController();
	if (InstigatorController == nullptr) return;

	UClass* DamageTypeClass = UDamageType::StaticClass();
	if (DamageTypeClass == nullptr) return;

	// Apply Damage to the passed in HitActor
	UGameplayStatics::ApplyDamage(OtherActor, BeamDamage, InstigatorController, this, DamageTypeClass);
}

// Destroys the Beam once it's lifespan has elapsed.
void ABeam::EndBeam()
{
	Destroy();
}

