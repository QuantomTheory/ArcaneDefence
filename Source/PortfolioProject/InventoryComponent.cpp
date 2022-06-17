// Fill out your copyright notice in the Description page of Project Settings.


#include "InventoryComponent.h"
#include "TimerManager.h"

// Sets default values for this component's properties
UInventoryComponent::UInventoryComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UInventoryComponent::BeginPlay()
{
	Super::BeginPlay();

	SpellList = { DefaultSpellClass, SpellOneClass , SpellTwoClass};

	IsSpellOneReady = false;
	GetOwner()->GetWorldTimerManager().SetTimer(SpellOneCooldownTimer, this, &UInventoryComponent::ResetSpellOneCooldown, SpellOneCooldown);
	IsSpellTwoReady = false;
	GetOwner()->GetWorldTimerManager().SetTimer(SpellTwoCooldownTimer, this, &UInventoryComponent::ResetSpellTwoCooldown, SpellTwoCooldown);
	IsSpellThreeReady = false;
	GetOwner()->GetWorldTimerManager().SetTimer(SpellThreeCooldownTimer, this, &UInventoryComponent::ResetSpellThreeCooldown, SpellThreeCooldown);
	IsSpellFourReady = false;
	GetOwner()->GetWorldTimerManager().SetTimer(SpellFourCooldownTimer, this, &UInventoryComponent::ResetSpellFourCooldown, SpellFourCooldown);
}


// Called every frame
void UInventoryComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

TSubclassOf<ASpell> UInventoryComponent::GetActiveSpellClass() const
{
	return SpellList[ActiveSpell];
}

int32 UInventoryComponent::GetActiveSpellNum() const
{
	return ActiveSpell;
}

void UInventoryComponent::SetActiveSpell(int32 ChosenSpell)
{
	if (IsSpellReady(ChosenSpell))
	{
		ActiveSpell = ChosenSpell;
	}
}

void UInventoryComponent::SetActiveSpellCooldown()
{
	switch (ActiveSpell)
	{
	default:
		return;
	case 1:
		IsSpellOneReady = false;

		GetOwner()->GetWorldTimerManager().SetTimer(SpellOneCooldownTimer, this, &UInventoryComponent::ResetSpellOneCooldown, SpellOneCooldown);
		return;

	case 2:
		IsSpellTwoReady = false;

		GetOwner()->GetWorldTimerManager().SetTimer(SpellTwoCooldownTimer, this, &UInventoryComponent::ResetSpellTwoCooldown, SpellTwoCooldown);
		return;

	case 3:
		IsSpellThreeReady = false;

		GetOwner()->GetWorldTimerManager().SetTimer(SpellThreeCooldownTimer, this, &UInventoryComponent::ResetSpellThreeCooldown, SpellThreeCooldown);
		return;

	case 4:
		IsSpellFourReady = false;

		GetOwner()->GetWorldTimerManager().SetTimer(SpellFourCooldownTimer, this, &UInventoryComponent::ResetSpellFourCooldown, SpellFourCooldown);
		return;

	}
}

void UInventoryComponent::ResetSpellOneCooldown()
{
	IsSpellOneReady = true;
}

void UInventoryComponent::ResetSpellTwoCooldown()
{
	IsSpellTwoReady = true;
}

void UInventoryComponent::ResetSpellThreeCooldown()
{
	IsSpellThreeReady = true;
}

void UInventoryComponent::ResetSpellFourCooldown()
{
	IsSpellFourReady = true;
}

bool UInventoryComponent::IsSpellReady(int32 ChosenSpell) const
{
	switch (ChosenSpell)
	{
	default:
		return true;
	case 1:
		return IsSpellOneReady;
	case 2:
		return IsSpellTwoReady;
	case 3:
		return IsSpellThreeReady;
	case 4:
		return IsSpellFourReady;
	}
}

float UInventoryComponent::GetCooldownPercent(int32 ChosenSpell) const
{
	float CurrentTime;
	switch (ChosenSpell)
	{
	default:
		return 0.0f;
	case 1:
		CurrentTime = GetOwner()->GetWorldTimerManager().GetTimerRemaining(SpellOneCooldownTimer);
		return (CurrentTime / SpellOneCooldown);
	case 2:
		CurrentTime = GetOwner()->GetWorldTimerManager().GetTimerRemaining(SpellTwoCooldownTimer);
		return (CurrentTime / SpellTwoCooldown);
	case 3:
		CurrentTime = GetOwner()->GetWorldTimerManager().GetTimerRemaining(SpellThreeCooldownTimer);
		return (CurrentTime / SpellThreeCooldown);
	case 4:
		CurrentTime = GetOwner()->GetWorldTimerManager().GetTimerRemaining(SpellFourCooldownTimer);
		return (CurrentTime / SpellFourCooldown);
	}
}

