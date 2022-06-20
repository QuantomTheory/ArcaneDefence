// Fill out your copyright notice in the Description page of Project Settings.


#include "HealthComponent.h"
#include "Kismet/GameplayStatics.h"
#include "PortfolioProjectGameModeBase.h"

// Sets default values for this component's properties
UHealthComponent::UHealthComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}


// Called when the game starts
void UHealthComponent::BeginPlay()
{
	Super::BeginPlay();

	Health = MaxHealth;

	AActor* Owner = GetOwner();
	if (Owner != nullptr)
	{
		// Sets the DamageTaken Function to be triggered when the Owner takes Damage
		Owner->OnTakeAnyDamage.AddDynamic(this, &UHealthComponent::DamageTaken);
	}
}

// Get the remaining Health as a percentage. (Used to update Health Bar Visuals)
float UHealthComponent::GetHealthPercent() const
{
	return Health/MaxHealth;
}

// Called every frame
void UHealthComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UHealthComponent::DamageTaken(AActor* DamagedActor, float Damage, const UDamageType* DamageType, class AController* Instigator, AActor* DamageCauser)
{
	// Gets the Owner of the Damaged Actor...
	AActor* DamagedOwner = DamagedActor->GetOwner();
	// ...and the owner of the Damage Causer.
	AActor* DamageOwner = DamageCauser->GetOwner();

	// Prevents the Player from damaging themselves or the Defense Point
	if (DamagedOwner != nullptr && DamageOwner != nullptr && DamagedOwner == DamageOwner) return;

	if (Damage <= 0.f) return;

	// If the character has health remaining, subtract the damage.
	if (Health > 0.f)
	{
		Health -= Damage;
	}
}

// Returns true if the owner health reaches zero
bool UHealthComponent::IsDead() const
{
	return Health <= 0;
}