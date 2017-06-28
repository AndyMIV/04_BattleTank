// Fill out your copyright notice in the Description page of Project Settings.


#include "BattleTank.h"
#include "TankAimingComponent.h"
#include "Tank.h"
#include "TankPlayerController.h"

void ATankPlayerController::BeginPlay() {
	Super::BeginPlay(); // call default behavior

	// we are looking through the tank to the aiming component (component based architecture)
	AimingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();
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

void ATankPlayerController::SetPawn(APawn* InPawn) {
	Super::SetPawn(InPawn);
	if (InPawn) {
		auto PosessedTank = Cast<ATank>(InPawn);
		if (!ensure(PosessedTank)) { return; }

		// subscribe our local method to the deaths tank event
		PosessedTank->OnDeath.AddUniqueDynamic(this, &ATankPlayerController::OnPossesedTankDeath);
	}
}

void ATankPlayerController::OnPossesedTankDeath() {
	UE_LOG(LogTemp, Warning, TEXT("Received"));
	StartSpectatingOnly();
}

void ATankPlayerController::AimTowardsCrosshair() {
	if (!GetPawn()) { return; }		// e.g. if not posessing, this can happen during death so no ensure needed. And this stops crashing when opening its BP

	FVector HitLocation; // out parameter
	bool bGetSightRayHitLocation = GetSightRayHitLocation(HitLocation);
	// UE_LOG(LogTemp, Warning, TEXT("%i"), bGetSightRayHitLocation);
	if (bGetSightRayHitLocation) {
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
