// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Pawn.h"
#include "Tank.generated.h"			// put new includes above

// Forward Declarations
class UTankBarrel;
class UTankTurret;
class UTankAimingComponent;
// Currently, there is problem with tank blueprint. This is because blueprint is expecting a barrel vs staticmesh

UCLASS()
class BATTLETANK_API ATank : public APawn
{
	GENERATED_BODY()

public:
	void AimAt(FVector Hitlocation);

	UFUNCTION(BlueprintCallable, Category = Setup)
		void SetBarrelReference(UTankBarrel* BarrelToSet);

	UFUNCTION(BlueprintCallable, Category = Setup)
		void SetTurretReference(UTankTurret* TurretToSet);
	



private:
	// Sets default values for this pawn's properties
	ATank();

	UPROPERTY(EditAnywhere, Category = Firing)
		float LaunchSpeed = 4000;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected: // no need for outside access, but accessible with UPROPERTY
	// reference to a tank aiming component
	UTankAimingComponent* TankAimingComponent = nullptr;
	
};
