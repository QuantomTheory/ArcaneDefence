// Fill out your copyright notice in the Description page of Project Settings.


#include "AoEProjectile.h"
#include "Kismet/GameplayStatics.h"

// Runs on Projectile creation
void AAoEProjectile::BeginPlay()
{
	Super::BeginPlay();

	// One a Component Hit, trigger the OnHit function for this Projectile.
	ProjectileMesh->OnComponentHit.AddDynamic(this, &AAoEProjectile::OnHit);
}

void AAoEProjectile::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	AActor* MyOwner = GetOwner();
	if (MyOwner == nullptr)
	{
		Destroy();
		return;
	}

	//Cancel the projectile life timer that was set during the parent prjectile class BeginPlay()
	GetWorldTimerManager().ClearTimer(ExplodeTimer);

	// Ensures the actor hit isn't the caster
	if (OtherActor && OtherActor != this && OtherActor != MyOwner)
	{
		DealDamage();
		Explode(Hit.ImpactPoint, Hit.ImpactNormal.Rotation());
	}
	else
	{
		Destroy();
	}
}

void AAoEProjectile::DealDamage()
{
	// Get the projectile Owner, Controller, and DamageType and ensure they're not null pointers.
	AActor* MyOwner = GetOwner();
	if (MyOwner == nullptr) return;

	AController* InstigatorController = MyOwner->GetInstigatorController();
	if (InstigatorController == nullptr) return;

	UClass* DamageTypeClass = UDamageType::StaticClass();
	if (DamageTypeClass == nullptr) return;

	// Set the projectile owner as an Ignored Actor for the Damage Function
	TArray<AActor*> IgnoredActors = {MyOwner};

	// Apply Radial Damage on Impact
	UGameplayStatics::ApplyRadialDamage(GetWorld(), ImpactDamage, GetActorLocation(), ImpactRadius, DamageTypeClass, IgnoredActors, this, InstigatorController, true);
}


// Does not use the inherited Explode function. This allows the particle location/rotation to dynamically be set based on impact details.
void AAoEProjectile::Explode(FVector ImpactLocation, FRotator ImpactRotation)
{
	if (ImpactParticles)
	{
		UGameplayStatics::SpawnEmitterAtLocation(this, ImpactParticles, ImpactLocation, ImpactRotation);
	}

	if (ImpactSound)
	{
		UGameplayStatics::SpawnSoundAtLocation(this, ImpactSound, GetActorLocation(), GetActorRotation());
	}

	Destroy();
}
