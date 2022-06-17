// Fill out your copyright notice in the Description page of Project Settings.


#include "SimpleProjectile.h"
#include "Kismet/GameplayStatics.h"


void ASimpleProjectile::BeginPlay()
{
	Super::BeginPlay();

	// One a Component Hit, trigger the OnHit function for this Projectile.
	ProjectileMesh->OnComponentHit.AddDynamic(this, &ASimpleProjectile::OnHit);
}

void ASimpleProjectile::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
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
		DealDamage(MyOwner, OtherActor);
		Explode();
	}
	else
	{
		Destroy();
	}
}

void ASimpleProjectile::DealDamage(AActor* MyOwner, AActor* OtherActor)
{
	// Get the projectile Controller, and DamageType and ensure they're not null pointers.
	AController* InstigatorController = MyOwner->GetInstigatorController();
	if (InstigatorController == nullptr) return;

	UClass* DamageTypeClass = UDamageType::StaticClass();
	if (DamageTypeClass == nullptr) return;

	// Apply damage to the impacted actor.
	UGameplayStatics::ApplyDamage(OtherActor, ImpactDamage, InstigatorController, this, DamageTypeClass);
}