// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Tank.h"
#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h" // must be the last include

class ATank;

/**
 * 
 */
UCLASS()
class BATTLETANK_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()

// has to be protected for blueprintcallable to work
protected:
	UFUNCTION(BlueprintCallable, Category = "Setup")
	ATank * GetControlledTank() const;


private:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	// starter the tank moving the barrel so that a shot would hit where the crosshair intersects
	void AimTowardsCrosshair();
	bool GetSightRayHitLocation(FVector &OutHitLocation) const;
	bool GetLookDirection(FVector2D ScreenLocation, FVector &LookDirection) const;
	bool GetLookVectorHitLocation(
		FVector &HitLocation, 
		FVector LookDirection) const;

	UPROPERTY(EditDefaultsOnly)
	float CrossHairXLocation = 0.5;
	UPROPERTY(EditDefaultsOnly)
	float CrossHairYLocation = 0.33333;
	UPROPERTY(EditDefaultsOnly)
	float LineTraceRange = 1000000; // km to cm
};
