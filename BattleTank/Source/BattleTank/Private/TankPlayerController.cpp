// Fill out your copyright notice in the Description page of Project Settings.


#include "BattleTank.h"
#include "TankAimingComponent.h"
#include "Tank.h"
#include "TankPlayerController.h"

void ATankPlayerController::BeginPlay() {
	Super::BeginPlay(); // call default behavior

	// we are looking through the tank to the aiming component (component based architecture)
	AimingComponent = GetControlledTank()->FindComponentByClass<UTankAimingComponent>();
	if (ensure (AimingComponent)) {
		// broadcasting blue printInplementableEvent
		FoundAimingComponent(AimingComponent);
	}

}

void ATankPlayerController::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);
	PrimaryActorTick.bCanEverTick = true;
	AimTowardsCrosshair();
}



ATank* ATankPlayerController::GetControlledTank() const {
	// returns the pawn that the player controller is currently posessing. works because it is based off of player controller.
	return Cast<ATank>(GetPawn());
}

void ATankPlayerController::AimTowardsCrosshair() {
	if (!ensure(GetControlledTank())) { return; }

	FVector HitLocation; // out parameter
	if (GetSightRayHitLocation(HitLocation)) {
		AimingComponent->AimAt(HitLocation);
	}
	// Get world location of linetrace through crosshair
	// if it hits landscape
		// tell controlled tank to aim at this point
}

bool ATankPlayerController::GetSightRayHitLocation(FVector &OutHitLocation) const {
	// find the crosshair position
	int32 ViewportSizeX, ViewportSizeY;
	GetViewportSize(ViewportSizeX, ViewportSizeY);
	auto ScreenLocation = FVector2D (ViewportSizeX * CrossHairXLocation, ViewportSizeY * CrossHairYLocation);


	auto LookDirection = FVector();
	if (GetLookDirection(ScreenLocation, LookDirection)) {
		// line-trace along that lookdirection, and see what we hit (up to max range)
		FHitResult ObjectHit;
		return GetLookVectorHitLocation(OutHitLocation, LookDirection);
			
		
	}
	// line-trace along that lookdirection, and see what we hit (up to max range)
	return false;
}

bool ATankPlayerController::GetLookVectorHitLocation(FVector &HitLocation, FVector LookDirection) const {
	FHitResult HitResult;
	auto StartLocation = PlayerCameraManager->GetCameraLocation();
	auto EndLocation = StartLocation + LookDirection * LineTraceRange;
	if (GetWorld()->LineTraceSingleByChannel(
		HitResult,
		StartLocation,
		EndLocation,
		ECollisionChannel::ECC_Visibility
	)) {
		HitLocation = HitResult.Location;
		return true;
	}
	else
		return false;
}

bool ATankPlayerController::GetLookDirection(FVector2D ScreenLocation, FVector &LookDirection) const {
	// "de-project" the screen position of the crosshair to a world direction
	auto CamWorldLocation = FVector();
	return DeprojectScreenPositionToWorld(
		ScreenLocation.X, ScreenLocation.Y,
		CamWorldLocation, LookDirection);
}
