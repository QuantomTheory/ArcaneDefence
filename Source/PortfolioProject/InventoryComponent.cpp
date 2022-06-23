// Fill out your copyright notice in the Description page of Project Settings.


#include "InventoryComponent.h"
#include "TimerManager.h"

// Sets default values for this component's properties
UInventoryComponent::UInventoryComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}


// Called when the game starts
void UInventoryComponent::BeginPlay()
{
	Super::BeginPlay();

	// Initialises the Spell List
	SpellList = { DefaultSpellClass, SpellOneClass , SpellTwoClass};

	// Starts the cooldown on the spells to prevent them being used right at the beginning
	IsSpellOneReady = false;
	GetOwner()->GetWorldTimerManager().SetTimer(SpellOneCooldownTimer, this, &UInventoryComponent::ResetSpellOneCooldown, SpellOneCooldown);
	IsSpellTwoReady = false;
	GetOwner()->GetWorldTimerManager().SetTimer(SpellTwoCooldownTimer, this, &UInventoryComponent::ResetSpellTwoCooldown, SpellTwoCooldown);
}


// Called every frame
void UInventoryComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

// Retuns the Currently Active Spell as a Spell class
TSubclassOf<ASpell> UInventoryComponent::GetActiveSpellClass() const
{
	return SpellList[ActiveSpell];
}

// Retuns the Currently Active Spell by its Spell Number
int32 UInventoryComponent::GetActiveSpellNum() const
{
	return ActiveSpell;
}

// Sets the Active Spell class based on the passed in Number
void UInventoryComponent::SetActiveSpell(int32 ChosenSpell)
{
	if (IsSpellReady(ChosenSpell))
	{
		ActiveSpell = ChosenSpell;
	}
}

// Starts the Cooldown Timer on the currently Active Spell (Triggered on Cast)
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

	}
}

// Resets the Cooldown on Spell One
void UInventoryComponent::ResetSpellOneCooldown()
{
	IsSpellOneReady = true;
}

// Resets the Cooldown on Spell Two
void UInventoryComponent::ResetSpellTwoCooldown()
{
	IsSpellTwoReady = true;
}

// Is the chosen spell ready (has it's cooldown elapsed.)
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
	}
}

// Returns the cooldown elapsed time as a percentage of the total cooldown time
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
	}
}

