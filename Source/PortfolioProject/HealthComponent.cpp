// Fill out your copyright notice in the Description page of Project Settings.


#include "HealthComponent.h"
#include "Kismet/GameplayStatics.h"
#include "PortfolioProjectGameModeBase.h"

// Sets default values for this component's properties
UHealthComponent::UHealthComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UHealthComponent::BeginPlay()
{
	Super::BeginPlay();

	Health = MaxHealth;

	AActor* Owner = GetOwner();
	if (Owner != nullptr)
	{
		Owner->OnTakeAnyDamage.AddDynamic(this, &UHealthComponent::DamageTaken);
	}
}


float UHealthComponent::GetHealthPercent() const
{
	return Health/MaxHealth;
}

// Called every frame
void UHealthComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UHealthComponent::DamageTaken(AActor* DamagedActor, float Damage, const UDamageType* DamageType, class AController* Instigator, AActor* DamageCauser)
{
	AActor* DamagedOwner = DamagedActor->GetOwner();
	AActor* DamageOwner = DamageCauser->GetOwner();
	// Prevents the Player from damaging themselves or the Defense Point
	if (DamagedOwner != nullptr && DamageOwner != nullptr && DamagedOwner == DamageOwner)
	{
		UE_LOG(LogTemp, Warning, TEXT("Ignore Damage"));
		return;
	}

	if (Damage <= 0.f) return;
	if (Health > 0.f)
	{
		Health -= Damage;
	}

	UE_LOG(LogTemp, Warning, TEXT("Health: %f"), Health);
}

bool UHealthComponent::IsDead() const
{
	return Health <= 0;
}