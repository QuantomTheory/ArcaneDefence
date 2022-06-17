// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/CapsuleComponent.h"
#include "PortfolioProjectGameModeBase.h"
#include "TimerManager.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ABaseCharacter::ABaseCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ABaseCharacter::BeginPlay()
{
	Super::BeginPlay();
	MoveSpeed = GetCharacterMovement()->GetMaxSpeed();
	GetCharacterMovement()->AirControl = AirControlSpeed;

	HealthComponent = Cast<UHealthComponent>(GetComponentByClass(UHealthComponent::StaticClass()));
	if (HealthComponent == nullptr)
	{
		return;
	}
}

// Called every frame
void ABaseCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	IsDead();
}

// Called to bind functionality to input
void ABaseCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis(TEXT("MoveForward"), this, &ABaseCharacter::MoveForward);
	PlayerInputComponent->BindAxis(TEXT("MoveRight"), this, &ABaseCharacter::MoveRight);
	PlayerInputComponent->BindAxis(TEXT("TiltUp"), this, &ABaseCharacter::TiltUp);
	PlayerInputComponent->BindAxis(TEXT("TurnRight"), this, &ABaseCharacter::TurnRight);

	PlayerInputComponent->BindAction(TEXT("Jump"), EInputEvent::IE_Pressed, this, &ABaseCharacter::Jump);
	PlayerInputComponent->BindAction(TEXT("Crouch"), EInputEvent::IE_Pressed, this, &ABaseCharacter::StartCrouch);
	PlayerInputComponent->BindAction(TEXT("Crouch"), EInputEvent::IE_Released, this, &ABaseCharacter::EndCrouch);
	PlayerInputComponent->BindAction(TEXT("Sprint"), EInputEvent::IE_Pressed, this, &ABaseCharacter::StartSprint);
	PlayerInputComponent->BindAction(TEXT("Sprint"), EInputEvent::IE_Released, this, &ABaseCharacter::EndSprint);
}

void ABaseCharacter::TiltUp(float AxisValue)
{
	APawn::AddControllerPitchInput(AxisValue);
}

void ABaseCharacter::TurnRight(float AxisValue)
{
	APawn::AddControllerYawInput(AxisValue);
}

void ABaseCharacter::Jump()
{
	ACharacter::Jump();
}

void ABaseCharacter::StartCrouch()
{
	GetCharacterMovement()->Crouch();
	UE_LOG(LogTemp, Warning, TEXT("Crouch"));
}

void ABaseCharacter::EndCrouch()
{
	GetCharacterMovement()->UnCrouch();
	UE_LOG(LogTemp, Warning, TEXT("UnCrouch"));
}

void ABaseCharacter::StartSprint()
{
	GetCharacterMovement()->MaxWalkSpeed = (MoveSpeed * SprintMultiplier);
}

void ABaseCharacter::EndSprint()
{
	GetCharacterMovement()->MaxWalkSpeed = MoveSpeed;
}

void ABaseCharacter::MoveForward(float AxisValue)
{
	AddMovementInput(GetActorForwardVector() * AxisValue);
}

void ABaseCharacter::MoveRight(float AxisValue)
{
	AddMovementInput(GetActorRightVector() * AxisValue);
}

void ABaseCharacter::IsDead()
{
	if (HealthComponent->IsDead())
	{
		GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);


		APortfolioProjectGameModeBase* GameMode = GetWorld()->GetAuthGameMode<APortfolioProjectGameModeBase>();
		if (GameMode)
		{
			GameMode->PawnKilled(this);
		}
		DetachFromControllerPendingDestroy();

		UGameplayStatics::SpawnSoundAtLocation(this, DeathSound, GetActorLocation(), GetActorRotation());
		UGameplayStatics::SpawnEmitterAtLocation(this, DeathEffect, GetActorLocation(), GetActorRotation());

		Destroy();
	}
}

void ABaseCharacter::DestroyActor()
{
	Destroy();
}