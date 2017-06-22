// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "Projectile.h"



// Sets default values
AProjectile::AProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(FName("Projectile Movement Component"));

	CollisionMesh = CreateDefaultSubobject<UStaticMeshComponent>(FName("Collision Mesh"));
	SetRootComponent(CollisionMesh);
	CollisionMesh->SetNotifyRigidBodyCollision(true);		// when you make a BP based on C++ projectile, this checkbox will be checked by default (simulation generates hit events)
	CollisionMesh->SetVisibility(false);					//  we dont want to see the balls, only the smoke, so defailt to false

	LaunchBlast = CreateDefaultSubobject<UParticleSystemComponent>(FName("Static Mesh Component"));
	LaunchBlast->AttachTo(RootComponent);

	ProjectileMovementComponent->bAutoActivate = false;
}

// Called when the game starts or when spawned
void AProjectile::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AProjectile::LaunchProjectile(float Speed) {
	ProjectileMovementComponent->SetVelocityInLocalSpace(FVector::ForwardVector * Speed); // the forward vector is the unit vector. Reemeber that when projectile is spawned, it is spawned with a location and a rotation
	ProjectileMovementComponent->Activate();   // the deactivation we did at the start is now undone
}