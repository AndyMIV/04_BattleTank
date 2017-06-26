// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "Projectile.h"



// Sets default values
AProjectile::AProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(FName("Projectile Movement Component"));
	ProjectileMovementComponent->bAutoActivate = false;

	CollisionMesh = CreateDefaultSubobject<UStaticMeshComponent>(FName("Collision Mesh"));
	SetRootComponent(CollisionMesh);
	CollisionMesh->SetNotifyRigidBodyCollision(true);		// when you make a BP based on C++ projectile, this checkbox will be checked by default (simulation generates hit events)
	CollisionMesh->SetVisibility(false);					//  we dont want to see the balls, only the smoke, so defailt to false

	LaunchBlast = CreateDefaultSubobject<UParticleSystemComponent>(FName("Launch Blast"));
	LaunchBlast->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);

	ImpactBlast = CreateDefaultSubobject<UParticleSystemComponent>(FName("Impact Blast"));
	ImpactBlast->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
	ImpactBlast->bAutoActivate = false;

	ExplosionForce = CreateDefaultSubobject<URadialForceComponent>(FName("Explosion Force"));
	ExplosionForce->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
}

// Called when the game starts or when spawned
void AProjectile::BeginPlay()
{
	Super::BeginPlay();
	
	CollisionMesh->OnComponentHit.AddDynamic(this, &AProjectile::OnHit);
	
}

void AProjectile::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit) {
	UE_LOG(LogTemp, Warning, TEXT("OnHit activated"));
	LaunchBlast->Deactivate();
	ImpactBlast->SetWorldLocation(CollisionMesh->GetComponentLocation());
	ImpactBlast->Activate();

	ExplosionForce->FireImpulse();

	SetRootComponent(ImpactBlast);
	CollisionMesh->DestroyComponent();

	FTimerHandle TimerHandle;
	GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &AProjectile::DestroyIt, DestroyDelay);

	UGameplayStatics::ApplyRadialDamage(
		this,  // this projectile
		ProjectileDamage,
		GetActorLocation(),
		ExplosionForce->Radius, // for consistency
		UDamageType::StaticClass(),
		TArray<AActor*>() // empty array, damage all actors
		);
}

void AProjectile::DestroyIt() {
	Destroy();
}

void AProjectile::LaunchProjectile(float Speed) {
	ProjectileMovementComponent->SetVelocityInLocalSpace(FVector::ForwardVector * Speed); // the forward vector is the unit vector. Reemeber that when projectile is spawned, it is spawned with a location and a rotation
	ProjectileMovementComponent->Activate();   // the deactivation we did at the start is now undone
}