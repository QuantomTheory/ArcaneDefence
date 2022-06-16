// Fill out your copyright notice in the Description page of Project Settings.


#include "Beam.h"	
#include "NiagaraSystem.h"

// Sets default values
ABeam::ABeam()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BeamMesh = CreateDefaultSubobject<USceneComponent>(TEXT("Beam Root"));
	RootComponent = BeamMesh;

	ImpactMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Particle Trail"));
	ImpactMesh->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void ABeam::BeginPlay()
{
	Super::BeginPlay();

	if (BeamSound)
	{
		UGameplayStatics::SpawnSoundAttached(BeamSound, RootComponent, TEXT("NAME_None"),((FVector3d)(ForceInit)), FRotator::ZeroRotator, EAttachLocation::KeepRelativeOffset, true);
	}
}

float ABeam::GetBeamLifeSpan()
{
	return BeamLifeSpan;
}

void ABeam::AttachBeamToCaster(USceneComponent* UltimateSpawnPoint)
{
	AttachToComponent(UltimateSpawnPoint, FAttachmentTransformRules::KeepWorldTransform);
}

// Called every frame
void ABeam::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	TArray<FHitResult> HitResultArray;
	if (BeamTrace(HitResultArray))
	{
		UE_LOG(LogTemp, Warning, TEXT("Sweep Returned True"));
		for (int32 i = 0; i < HitResultArray.Num(); i++)
		{
			AActor* HitActor = HitResultArray[i].GetActor();
			if (HitActor == nullptr) return;
			AActor* OwnerActor = GetOwner();
			if (OwnerActor == nullptr) return;

			if (HitActor != OwnerActor)
			{
				DealDamage(HitResultArray[i]);
			}
		}
	}
}

bool ABeam::BeamTrace(TArray<FHitResult>& OutHitResultArray)
{
	FVector BeamLocation = GetActorLocation();
	FRotator BeamRotation = GetActorRotation();

	FVector End = BeamLocation + (BeamRotation.Vector() * BeamRange);
	FCollisionQueryParams Params;
	Params.AddIgnoredActor(this);
	Params.AddIgnoredActor(GetOwner());

	FCollisionShape Shape = FCollisionShape::MakeSphere(BeamRadius);

	FHitResult SweepResult;
	return GetWorld()->SweepMultiByChannel(OutHitResultArray, BeamLocation, End, BeamRotation.Quaternion(), ECollisionChannel::ECC_WorldDynamic, Shape);
}

void ABeam::DealDamage(const FHitResult& Hit)
{
	AActor* OtherActor = Hit.GetActor();
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

	UGameplayStatics::ApplyPointDamage(OtherActor, BeamDamage, Hit.ImpactPoint, Hit, InstigatorController, this, DamageTypeClass);
}

void ABeam::EndBeam()
{

	Destroy();
}

