// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/ActorComponent.h"
#include "TankAimingComponent.generated.h"

// Enumeration for aiming state
UENUM()
enum class EFiringStatus : uint8 {
	Reloading,
	Aiming,
	Locked
};

// forward declaration, similar to:  class BATTLETANK_API UTankAimingComponent : public UActorComponent
// makes dependancies explicit, without creating a chain of dependancies
class UTankBarrel;
class UTankTurret;

// holds barrels properties and elevate method
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BATTLETANK_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UTankAimingComponent();

	UFUNCTION(BlueprintCallable, Category = "Setup")
	void Initialize(UTankBarrel* BarrelToSet, UTankTurret* TurretToSet);

	void AimAt(FVector HitLocation) const;

private:
	void MoveBarrelTowards(FVector AimDirection) const;

	UPROPERTY(EditDefaultsOnly, Category = "Firing")
		float LaunchSpeed = 4000;

protected: // we are asking to access the property from the subclass: tankaimingcomponent blueprint (remember c++ is the parent)
	UPROPERTY(BlueprintReadOnly, Category = "State")
	EFiringStatus FiringStatus = EFiringStatus::Locked;

	UTankBarrel* Barrel = nullptr;
	UTankTurret* Turret = nullptr;
};
