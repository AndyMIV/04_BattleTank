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

ATank* ATankPlayerController::GetControlledTank() const {
	// returns the pawn that the player controller is currently posessing. works because it is based off of player controller.
	return Cast<ATank>(GetPawn());
}


