// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankAimingComponent.h"


// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

void UTankAimingComponent::SetBarrelReference(UStaticMeshComponent* BarrelToSet) {
	Barrel = BarrelToSet;
}


void UTankAimingComponent::AimAt(FVector HitLocation, float LaunchSpeed) const {
	// auto OurTankName = GetOwner()->GetName();
	// auto BarrelLocation = Barrel->GetComponentLocation();
	// UE_LOG(LogTemp, Warning, TEXT("%s aiming at %s from %s"), *OurTankName, *HitLocation.ToString(), *BarrelLocation.ToString())

	if (!Barrel) { return; }  // protect

	FVector OutLaunchVelocity;
	FVector StartLocation = Barrel->GetSocketLocation(FName("Projectile"));

	// calculate the out launch velocity
	if (UGameplayStatics::SuggestProjectileVelocity(
		Barrel, // or use "this"
		OutLaunchVelocity,
		StartLocation,
		HitLocation,
		LaunchSpeed,
		false,
		0.0f,
		0.0f,
		ESuggestProjVelocityTraceOption::DoNotTrace, // you do not need to include params after this point
		FCollisionResponseParams::DefaultResponseParam,
		TArray<AActor*>(),
		true
		)) {
			auto TankName = GetOwner()->GetName();
			auto AimDirection = OutLaunchVelocity.GetSafeNormal();
			UE_LOG(LogTemp, Warning, TEXT("%s Aiming at %s"), *TankName, *AimDirection.ToString());
			MoveBarrelTowards(AimDirection);
		}

	// if nothings found, do nothing
}

void UTankAimingComponent::MoveBarrelTowards(FVector AimDirection) const {
	// work-out difference between current barrel rotation, and AimDirection

	// turning forward vector into rotation
	auto BarrelRotation = Barrel->GetForwardVector().Rotation();

	// move barrel the right ammount this frame
	// given a max elevation speed, and the frame time. (scaling)
}
