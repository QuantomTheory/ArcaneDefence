// A Child Class of the Base Character Class


#include "EnemyCharacter.h"
#include "Spell.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "EnemyAIController.h"

// Sets default values
AEnemyCharacter::AEnemyCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AEnemyCharacter::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AEnemyCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void AEnemyCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

// Triggers the attack funtion depending on if the character is Ranged or Melee
void AEnemyCharacter::Attack()
{
	SetIsAttacking(true);

	if (IsRangedAttacker)
	{
		RangedAttack();
	}
	else
	{
		MeleeAttack();
	}
}

// Returns the IsAttacking bool
bool AEnemyCharacter::GetIsAttacking() const
{
	return IsAttacking;
}

// Updates the IsAttacking bool
void AEnemyCharacter::SetIsAttacking(bool NewValue)
{
	IsAttacking = NewValue;
}

// The function to control the Attack for Melee attack.
void AEnemyCharacter::MeleeAttack()
{
	AEnemyAIController* MyController = Cast<AEnemyAIController>(GetInstigatorController());
	if (MyController == nullptr) return;

	AActor* TargetActor = MyController->GetTargetActor();
	if (TargetActor == nullptr) return;

	UClass* DamageTypeClass = UDamageType::StaticClass();
	if (DamageTypeClass == nullptr) return;

	//Applies Damage to the TargetActor.
	UGameplayStatics::ApplyDamage(TargetActor, MeleeAttackDamage, MyController, this, DamageTypeClass);

	// Plays the AttackSound
	if (MeleeAttackSound)
	{
		UGameplayStatics::SpawnSoundAtLocation(this, MeleeAttackSound, GetActorLocation(), GetActorRotation());
	}
}

// The function to control the Attack for Ranged attack
void AEnemyCharacter::RangedAttack()
{
	AEnemyAIController* MyController = Cast<AEnemyAIController>(GetInstigatorController());
	if (MyController == nullptr) return;

	AActor* TargetActor = MyController->GetTargetActor();
	if (TargetActor == nullptr) return;

	// Gets the spawn point Location and Rotation to target the Target Actor
	FVector ProjectileSpawnPointLocation = Cast<USceneComponent>(GetDefaultSubobjectByName(TEXT("Projectile Spawn Point")))->GetComponentLocation();
	FVector ProjectileTargetLocation = TargetActor->GetActorLocation();

	FRotator ProjectileSpawnPointRotation = UKismetMathLibrary::FindLookAtRotation(ProjectileSpawnPointLocation, ProjectileTargetLocation);

	// Spawns the Spell attack that has been assigned as the Ranged Attackers SpellClass
	ASpell* SpellActor = GetWorld()->SpawnActor<ASpell>(RangedSpellClass, ProjectileSpawnPointLocation, ProjectileSpawnPointRotation);
	SpellActor->SetOwner(this);
}
