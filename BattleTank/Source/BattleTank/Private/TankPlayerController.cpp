// Fill out your copyright notice in the Description page of Project Settings.


#include "BattleTank.h"
#include "TankPlayerController.h"

void ATankPlayerController::BeginPlay() {
	Super::BeginPlay(); // call default behavior

	auto PosessedTank = GetControlledTank();
	if (!PosessedTank) {
		UE_LOG(LogTemp, Warning, TEXT("Player Tank Not Detected!!!"));
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("Player Tank Detected: %s"), *PosessedTank->GetName());
	}

	UE_LOG(LogTemp, Warning, TEXT("Player Controller Begin Play"));
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
	if (!GetControlledTank()) { return; }

	FVector HitLocation; // out parameter

	bool HitCheck = GetSightRayHitLocation(HitLocation);
	if (!HitCheck) {
		UE_LOG(LogTemp, Warning, TEXT("Did not hit: %s"), *HitLocation.ToString());
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("Direct Hit: %s"), *HitLocation.ToString());
	}
	// Get world location of linetrace through crosshair
	// if it hits landscape
		// tell controlled tank to aim at this point
}

bool ATankPlayerController::GetSightRayHitLocation(FVector &OutHitLocation) const {
	// if it hits a valid object, return true and change outparameter
	// if it hots an invalid object, return false 
	return false;
}
