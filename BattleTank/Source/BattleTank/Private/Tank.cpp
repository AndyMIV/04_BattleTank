// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankAimingComponent.h"
#include "TankBarrel.h"
#include "Projectile.h"
#include "Tank.h"

// Sets default values
ATank::ATank()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	UE_LOG(LogTemp, Warning, TEXT("CustomDebug: Tank.cpp Consructor"));
}

void ATank::BeginPlay(){
	Super::BeginPlay(); // neede for BP begin play to run!

	UE_LOG(LogTemp, Warning, TEXT("CustomDebug: Tank.cpp Begin Play"));

	// we do this because we need working code before refactoring
	TankAimingComponent = FindComponentByClass<UTankAimingComponent>();

	Barrel = FindComponentByClass<UTankBarrel>();
}

// Called to bind functionality to input
void ATank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ATank::Fire() {
	if (!ensure(Barrel)) { return; }
	UE_LOG(LogTemp, Warning, TEXT("Is fire working?"));
	bool isReloaded = FPlatformTime::Seconds() - LastFireTime > ReloadTimeInSeconds; // also same as getworld, getTimeSeconds
	if (isReloaded) {
		// spawn a projectile from the socket location of the turret
		auto Projectile = GetWorld()->SpawnActor<AProjectile>(
			ProjectileBlueprint,
			Barrel->GetSocketLocation(FName("Projectile")),
			Barrel->GetSocketRotation(FName("Projectile"))
			);
		Projectile->LaunchProjectile(5);    // temporary value
		LastFireTime = FPlatformTime::Seconds();
	}

	
}
