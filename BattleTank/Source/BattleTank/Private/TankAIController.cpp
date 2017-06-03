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


	PlayerTank = GetPlayerTank();
	if (!PlayerTank) {
		UE_LOG(LogTemp, Warning, TEXT("AI not detecting player"));
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("AI Tank detecting player: %s"), *PlayerTank->GetName());
	}



}

void ATankAIController::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);
	PrimaryActorTick.bCanEverTick = true;
	AimTowardsPlayer();
}

void ATankAIController::AimTowardsPlayer() const{
	GetControlledTank()->AimAt(GetPlayerTank()->GetActorLocation());
}


ATank* ATankAIController::GetControlledTank() const {
	return Cast<ATank>(GetPawn());
}

ATank* ATankAIController::GetPlayerTank() const {
	return Cast<ATank>(GetWorld()->GetFirstPlayerController()->GetPawn());
}


