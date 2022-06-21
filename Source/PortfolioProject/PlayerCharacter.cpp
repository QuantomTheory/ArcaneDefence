// A child of the BaseCharacter Class, for the character controlled by the Player


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

	// Sets up the extra components used to attach the Beam Spell to
	SpellSpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spell Spring Arm"));
	SpellSpringArm->SetupAttachment(RootComponent);;

	SpellSpawnPoint = CreateDefaultSubobject<USceneComponent>(TEXT("Spell Spawn Point"));
	SpellSpawnPoint->SetupAttachment(SpellSpringArm);;
}

// Called when the game starts or when spawned
void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();

	InventoryComponent = Cast<UInventoryComponent>(GetComponentByClass(UInventoryComponent::StaticClass()));
	if (InventoryComponent == nullptr) return;

	CurrentSpellNum = InventoryComponent->GetActiveSpellNum();
	CurrentSpellClass = InventoryComponent->GetActiveSpellClass();
	if (CurrentSpellClass == nullptr) return;

	CurrentSpell = CurrentSpellClass.GetDefaultObject();
	if (CurrentSpell == nullptr) return;

	// Sets the interval between spells to default
	CurrentSpellInterval = DefaultSpellRate;
}

// Called every frame
void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (IsCasting == true && IsUltimateCasting == false)
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
}

// Sets IsCasting to true.
void APlayerCharacter::StartCastingSpell()
{
	SetIsCasting(true);
}

// Sets IsCasting to false.
void APlayerCharacter::StopCastingSpell()
{
	// If Ultimate is Casting, don't change the variable yet.
	if (IsUltimateCasting == false)
	{
		SetIsCasting(false);
	}
	// Reset the interval between spells to default
	CurrentSpellInterval = DefaultSpellRate;
}

// Spawns the Arcane Blast Spell
void APlayerCharacter::ArcaneBlastSpell()
{
	// Gets the Location of the Spell Spawn Point scene component on the character actor...
	FVector ProjectileSpawnPointLocation = Cast<USceneComponent>(GetDefaultSubobjectByName(TEXT("Spell Spawn Point")))->GetComponentLocation();
	// ... and the location of the Target Point scene component, another scene component on a spring arm on the camera.
	FVector ProjectileTargetLocation = Cast<USceneComponent>(GetDefaultSubobjectByName(TEXT("TargetPoint")))->GetComponentLocation();

	// Uses these to get a direction to aim the projectile at.
	FRotator ProjectileSpawnPointRotation =	UKismetMathLibrary::FindLookAtRotation(ProjectileSpawnPointLocation, ProjectileTargetLocation);
	// This is to acomodate the 3rd Person perspective and the cross hair on the screen.

	ASpell* SpellActor = GetWorld()->SpawnActor<ASpell>(CurrentSpellClass, ProjectileSpawnPointLocation, ProjectileSpawnPointRotation);
	SpellActor->SetOwner(this);
}

// Spawns the Arcane Bomb Spell
void APlayerCharacter::ArcaneBombSpell()
{
	// Get the Projectile Spawn Location and Rotation as above
	FVector ProjectileSpawnPointLocation = Cast<USceneComponent>(GetDefaultSubobjectByName(TEXT("Spell Spawn Point")))->GetComponentLocation();
	FVector ProjectileTargetLocation = Cast<USceneComponent>(GetDefaultSubobjectByName(TEXT("TargetPoint")))->GetComponentLocation();

	FRotator ProjectileSpawnPointRotation = UKismetMathLibrary::FindLookAtRotation(ProjectileSpawnPointLocation, ProjectileTargetLocation);

	ASpell* SpellActor = GetWorld()->SpawnActor<ASpell>(CurrentSpellClass, ProjectileSpawnPointLocation, ProjectileSpawnPointRotation);
	if (SpellActor == nullptr) return;
	SpellActor->SetOwner(this);

	// Begins the Cooldown on this spell
	InventoryComponent->SetActiveSpellCooldown();

	// Sets the Default Spell as Active again.
	SetSpellDefault();
}

void APlayerCharacter::UltimateSpell()
{
	SetIsUltimateCasting(true);
	
	FVector UltimateSpawnPointLocation = SpellSpawnPoint->GetComponentLocation();
	FRotator UltimateSpawnPointRotation = SpellSpawnPoint->GetComponentRotation();

	UltimateActor = GetWorld()->SpawnActor<ABeam>(CurrentSpellClass, UltimateSpawnPointLocation, UltimateSpawnPointRotation);
	if (UltimateActor == nullptr) return;
	UltimateActor->SetOwner(this);

	// Attaches the Beam to the Caster
	UltimateActor->AttachBeamToCaster(SpellSpawnPoint);

	// Character Movement is disabled during casting of the Ultimate
	GetCharacterMovement()->DisableMovement();

	// Starts the Timer ofr the BEam Life Span
	GetWorldTimerManager().SetTimer(UltimateCastTimer, this, &APlayerCharacter::EndUltimate, UltimateActor->GetBeamLifeSpan());
}

void APlayerCharacter::EndUltimate()
{
	//Re-enable Character Movement
	GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_Walking);

	// Begins the Cooldonw on this spell
	InventoryComponent->SetActiveSpellCooldown();

	// Sets the Default Spell as Active again.
	SetSpellDefault();

	// Set the casting variable to false again
	SetIsCasting(false);
	SetIsUltimateCasting(false);

	// Ends the Ultimate Beam
	UltimateActor->EndBeam();
	UltimateActor = nullptr;
}

// Is Casting and IsUltimateCasting Getters and Setters
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

// Sets the Currently Active Spell back to the Default
void APlayerCharacter::SetSpellDefault()
{
	InventoryComponent->SetActiveSpell(0);

	CurrentSpellNum = InventoryComponent->GetActiveSpellNum();
	CurrentSpellClass = InventoryComponent->GetActiveSpellClass();
	if (CurrentSpellClass == nullptr) return;

	CurrentSpell = CurrentSpellClass.GetDefaultObject();
	if (CurrentSpell == nullptr) return;
}

// Sets the Currently Active Spell to Spell One
void APlayerCharacter::SetSpellOne()
{
	InventoryComponent->SetActiveSpell(1);

	CurrentSpellNum = InventoryComponent->GetActiveSpellNum();
	CurrentSpellClass = InventoryComponent->GetActiveSpellClass();
	if (CurrentSpellClass == nullptr) return;

	CurrentSpell = CurrentSpellClass.GetDefaultObject();
	if (CurrentSpell == nullptr) return;
}

// Sets the Currently Active Spell to Spell Two
void APlayerCharacter::SetSpellTwo()
{
	InventoryComponent->SetActiveSpell(2);

	CurrentSpellNum = InventoryComponent->GetActiveSpellNum();
	CurrentSpellClass = InventoryComponent->GetActiveSpellClass();
	if (CurrentSpellClass == nullptr) return;

	CurrentSpell = CurrentSpellClass.GetDefaultObject();
	if (CurrentSpell == nullptr) return;
}
