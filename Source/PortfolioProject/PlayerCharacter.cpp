// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Spell.h"
#include "SimpleProjectile.h"
#include "AoEProjectile.h"
#include "Beam.h"	
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "InventoryComponent.h"
#include "GameFramework/SpringArmComponent.h"

// Sets default values
APlayerCharacter::APlayerCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	UltimateSpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Ultimate Spring Arm"));
	UltimateSpringArm->SetupAttachment(RootComponent);;

	UltimateSpawnPoint = CreateDefaultSubobject<USceneComponent>(TEXT("Ultimate Spawn Point"));
	UltimateSpawnPoint->SetupAttachment(UltimateSpringArm);;

}

// Called when the game starts or when spawned
void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();

	InventoryComponent = Cast<UInventoryComponent>(GetComponentByClass(UInventoryComponent::StaticClass()));
	if (InventoryComponent == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("InventoryComponent cast failed"));
		return;
	}

	CurrentSpellNum = InventoryComponent->GetActiveSpellNum();
	CurrentSpellClass = InventoryComponent->GetActiveSpellClass();
	if (CurrentSpellClass == nullptr) return;

	CurrentSpell = CurrentSpellClass.GetDefaultObject();
	if (CurrentSpell == nullptr) return;


	UE_LOG(LogTemp, Warning, TEXT("Current Spell Num: %i"), CurrentSpellNum);
}

// Called every frame
void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (IsCasting == true)
	{
		switch (CurrentSpellNum)
		{
		default:
			CurrentSpellInterval += DeltaTime;
			if (CurrentSpellInterval >= DefaultSpellRate)
			{
				ArcaneBlastSpell();
				CurrentSpellInterval = 0;
			}
			return;
		case 1:
			ArcaneBombSpell();
			return;
		case 2:
			UltimateSpell();
			return;
		}
	}
}

// Called to bind functionality to input
void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAction(TEXT("Shoot"), EInputEvent::IE_Pressed, this, &APlayerCharacter::StartCastingSpell);
	PlayerInputComponent->BindAction(TEXT("Shoot"), EInputEvent::IE_Released, this, &APlayerCharacter::StopCastingSpell);

	PlayerInputComponent->BindAction(TEXT("Spell1"), EInputEvent::IE_Pressed, this, &APlayerCharacter::SetSpellOne);
	PlayerInputComponent->BindAction(TEXT("Spell2"), EInputEvent::IE_Pressed, this, &APlayerCharacter::SetSpellTwo);
	//PlayerInputComponent->BindAction(TEXT("Spell3"), EInputEvent::IE_Pressed, this, &APlayerCharacter::SetSpellThree);
	//PlayerInputComponent->BindAction(TEXT("Spell4"), EInputEvent::IE_Pressed, this, &APlayerCharacter::SetSpellFour);
}

void APlayerCharacter::StartCastingSpell()
{

	if (CurrentSpell == nullptr) return;
	float CastDelay = CurrentSpell->GetCastDelay();
	GetWorldTimerManager().SetTimer(CastTimer, this, &APlayerCharacter::BeginSpell, CastDelay);

}

void APlayerCharacter::StopCastingSpell()
{
	if (IsCasting == false)
	{
		GetWorldTimerManager().ClearTimer(CastTimer);
	}
	SetIsCasting(false);
}

void APlayerCharacter::BeginSpell()
{
	SetIsCasting(true);
}

void APlayerCharacter::ArcaneBlastSpell()
{
	FVector ProjectileSpawnPointLocation = Cast<USceneComponent>(GetDefaultSubobjectByName(TEXT("Projectile Spawn Point")))->GetComponentLocation();
	FVector ProjectileTargetLocation = Cast<USceneComponent>(GetDefaultSubobjectByName(TEXT("TargetPoint")))->GetComponentLocation();

	FRotator ProjectileSpawnPointRotation =	UKismetMathLibrary::FindLookAtRotation(ProjectileSpawnPointLocation, ProjectileTargetLocation);

	ASpell* SpellActor = GetWorld()->SpawnActor<ASpell>(CurrentSpellClass, ProjectileSpawnPointLocation, ProjectileSpawnPointRotation);
	SpellActor->SetOwner(this);
}

void APlayerCharacter::ArcaneBombSpell()
{
	FVector ProjectileSpawnPointLocation = Cast<USceneComponent>(GetDefaultSubobjectByName(TEXT("Projectile Spawn Point")))->GetComponentLocation();
	FVector ProjectileTargetLocation = Cast<USceneComponent>(GetDefaultSubobjectByName(TEXT("TargetPoint")))->GetComponentLocation();

	FRotator ProjectileSpawnPointRotation = UKismetMathLibrary::FindLookAtRotation(ProjectileSpawnPointLocation, ProjectileTargetLocation);

	ASpell* SpellActor = GetWorld()->SpawnActor<ASpell>(CurrentSpellClass, ProjectileSpawnPointLocation, ProjectileSpawnPointRotation);
	if (SpellActor == nullptr) return;
	SpellActor->SetOwner(this);

	InventoryComponent->SetActiveSpellCooldown();

	SetSpellDefault();
}

void APlayerCharacter::UltimateSpell()
{
	SetIsUltimateCasting(true);
	
	FVector UltimateSpawnPointLocation = UltimateSpawnPoint->GetComponentLocation();
	FRotator UltimateSpawnPointRotation = UltimateSpawnPoint->GetComponentRotation();

	UltimateActor = GetWorld()->SpawnActor<ABeam>(CurrentSpellClass, UltimateSpawnPointLocation, UltimateSpawnPointRotation);
	if (UltimateActor == nullptr) return;
	UltimateActor->SetOwner(this);

	UltimateActor->AttachBeamToCaster(UltimateSpawnPoint);

	GetCharacterMovement()->DisableMovement();
	GetWorldTimerManager().SetTimer(CastTimer, this, &APlayerCharacter::EndUltimate, UltimateActor->GetBeamLifeSpan());

	InventoryComponent->SetActiveSpellCooldown();

	SetSpellDefault();
}

void APlayerCharacter::EndUltimate()
{
	GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_Walking);
	SetIsCasting(false);
	SetIsUltimateCasting(false);

	UltimateActor->EndBeam();
	UltimateActor = nullptr;
}

bool APlayerCharacter::GetIsCasting()
{
	return IsCasting;
}

void APlayerCharacter::SetIsCasting(bool NewCastingBool)
{
	IsCasting = NewCastingBool;
}

bool APlayerCharacter::GetIsUltimateCasting()
{
	return IsUltimateCasting;
}

void APlayerCharacter::SetIsUltimateCasting(bool NewCastingBool)
{
	IsUltimateCasting = NewCastingBool;
}

void APlayerCharacter::SetSpellDefault()
{
	InventoryComponent->SetActiveSpell(0);

	CurrentSpellNum = InventoryComponent->GetActiveSpellNum();
	CurrentSpellClass = InventoryComponent->GetActiveSpellClass();
	if (CurrentSpellClass == nullptr) return;

	CurrentSpell = CurrentSpellClass.GetDefaultObject();
	if (CurrentSpell == nullptr) return;
}

void APlayerCharacter::SetSpellOne()
{
	InventoryComponent->SetActiveSpell(1);

	CurrentSpellNum = InventoryComponent->GetActiveSpellNum();
	CurrentSpellClass = InventoryComponent->GetActiveSpellClass();
	if (CurrentSpellClass == nullptr) return;

	CurrentSpell = CurrentSpellClass.GetDefaultObject();
	if (CurrentSpell == nullptr) return;
}

void APlayerCharacter::SetSpellTwo()
{
	InventoryComponent->SetActiveSpell(2);

	CurrentSpellNum = InventoryComponent->GetActiveSpellNum();
	CurrentSpellClass = InventoryComponent->GetActiveSpellClass();
	if (CurrentSpellClass == nullptr) return;

	CurrentSpell = CurrentSpellClass.GetDefaultObject();
	if (CurrentSpell == nullptr) return;
}

void APlayerCharacter::SetSpellThree()
{
	InventoryComponent->SetActiveSpell(3);
}

void APlayerCharacter::SetSpellFour()
{
	InventoryComponent->SetActiveSpell(4);
}

