// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankAIController.h"

void ATankAIController::BeginPlay() {
	Super::BeginPlay();

	UE_LOG(LogTemp, Warning, TEXT("AI Controller Begin Play"));

	auto PosessedAITank = GetControlledTank();
	if (!PosessedAITank) {
		UE_LOG(LogTemp, Warning, TEXT("AI Tank Not Detected!!!"));
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("AI Tank Detected: %s"), *PosessedAITank->GetName());
	}

}


ATank* ATankAIController::GetControlledTank() const {
	return Cast<ATank>(GetPawn());
}


