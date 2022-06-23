// A child of the Spell class, and the parent to all projectile type classes (SimpleProjectile and AoEProjectile)


#include "Projectile.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "Camera/CameraShakeBase.h"
#include "TimerManager.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AProjectile::AProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	ProjectileMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Projectile Mesh"));
	RootComponent = ProjectileMesh;

	TrailParticles = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Particle Trail"));
	TrailParticles->SetupAttachment(RootComponent);

	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Projectile Movement"));
}

// Called when the game starts or when spawned
void AProjectile::BeginPlay()
{
	Super::BeginPlay();

	// Check sounds and particles are valid before spawning
	if (CastSound)
	{
		UGameplayStatics::SpawnSoundAtLocation(this, CastSound, GetActorLocation(), GetActorRotation());
	}

	if (CastParticles)
	{
		UGameplayStatics::SpawnEmitterAtLocation(this, CastParticles, GetActorLocation(), GetActorRotation());
	}

	if (MotionSound)
	{
		UGameplayStatics::SpawnSoundAttached(MotionSound, RootComponent, TEXT("NAME_None"), ((FVector3d)(ForceInit)), FRotator::ZeroRotator, EAttachLocation::KeepRelativeOffset, true);
	}

	// Allows a projectile that will only be destroyed on impact.
	if (ProjectileLifeSpan != 0)
	{
		GetWorldTimerManager().SetTimer(ExplodeTimer, this, &AProjectile::Explode, ProjectileLifeSpan);
	}
}

// Called every frame
void AProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called upon impact, or when the Explode Timer has elapsed.
void AProjectile::Explode()
{
	if (ImpactParticles)
	{
		UGameplayStatics::SpawnEmitterAtLocation(this, ImpactParticles, GetActorLocation(), GetActorRotation());
	}

	if (ImpactSound)
	{
		UGameplayStatics::SpawnSoundAtLocation(this, ImpactSound, GetActorLocation(), GetActorRotation());
	}

	Destroy();
}