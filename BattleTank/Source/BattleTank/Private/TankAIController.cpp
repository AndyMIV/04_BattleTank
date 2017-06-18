// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankAimingComponent.h"
#include "TankAIController.h"
// depends on movement component via pathfinding system

void ATankAIController::BeginPlay() {
	Super::BeginPlay();

	auto * ControlledTank = GetPawn();
	auto * PlayerTank = (GetWorld()->GetFirstPlayerController()->GetPawn());

	// we are looking through the tank to the aiming component (component based architecture)
	AimingComponent = ControlledTank->FindComponentByClass<UTankAimingComponent>();

	UE_LOG(LogTemp, Warning, TEXT("AI Controller Begin Play"));
	auto PosessedAITank = ControlledTank;
	if (!ensure (PosessedAITank)) {
		UE_LOG(LogTemp, Warning, TEXT("AI Tank Not Detected!!!"));
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("AI Tank Detected: %s"), *PosessedAITank->GetName());
	}


	PlayerTank = PlayerTank;
	if (!ensure (PlayerTank)) {
		UE_LOG(LogTemp, Warning, TEXT("AI not detecting player"));
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("AI Tank detecting player: %s"), *PlayerTank->GetName());
	}
}

void ATankAIController::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);
	PrimaryActorTick.bCanEverTick = true;

	auto ControlledTank = GetPawn();
	auto PlayerTank = GetWorld()->GetFirstPlayerController()->GetPawn();
	if (!ensure (ControlledTank && PlayerTank)) { return; }

	// Move towards player
	MoveToActor(PlayerTank, AcceptanceRadius); // TODO check if radius is in centimeters


	AimingComponent->AimAt(PlayerTank->GetActorLocation());

	//Fire if ready
	AimingComponent->Fire();
}



