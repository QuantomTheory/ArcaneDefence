// Fill out your copyright notice in the Description page of Project Settings.


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

bool AEnemyCharacter::GetIsAttacking() const
{
	return IsAttacking;
}

void AEnemyCharacter::SetIsAttacking(bool NewValue)
{
	IsAttacking = NewValue;
}

void AEnemyCharacter::MeleeAttack()
{
	AEnemyAIController* MyController = Cast<AEnemyAIController>(GetInstigatorController());
	if (MyController == nullptr) return;

	AActor* TargetActor = MyController->GetTargetActor();
	if (TargetActor == nullptr) return;

	UClass* DamageTypeClass = UDamageType::StaticClass();
	if (DamageTypeClass == nullptr) return;

	UGameplayStatics::ApplyDamage(TargetActor, AttackDamage, MyController, this, DamageTypeClass);
	UE_LOG(LogTemp, Warning, TEXT("Pawn Attacked"));

	if (AttackSound)
	{
		UGameplayStatics::SpawnSoundAtLocation(this, AttackSound, GetActorLocation(), GetActorRotation());
	}
}

void AEnemyCharacter::RangedAttack()
{
	AEnemyAIController* MyController = Cast<AEnemyAIController>(GetInstigatorController());
	if (MyController == nullptr) return;

	AActor* TargetActor = MyController->GetTargetActor();
	if (TargetActor == nullptr) return;

	FVector ProjectileSpawnPointLocation = Cast<USceneComponent>(GetDefaultSubobjectByName(TEXT("Projectile Spawn Point")))->GetComponentLocation();
	FVector ProjectileTargetLocation = TargetActor->GetActorLocation();

	FRotator ProjectileSpawnPointRotation = UKismetMathLibrary::FindLookAtRotation(ProjectileSpawnPointLocation, ProjectileTargetLocation);

	ASpell* SpellActor = GetWorld()->SpawnActor<ASpell>(SpellClass, ProjectileSpawnPointLocation, ProjectileSpawnPointRotation);
	SpellActor->SetOwner(this);
}
