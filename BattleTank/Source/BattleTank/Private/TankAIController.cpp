// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankAimingComponent.h"
#include "Tank.h"					// so we can implement on death
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

// we only want to do this when the SetPawn() gets called
void ATankAIController::SetPawn(APawn* InPawn) {
	Super::SetPawn(InPawn);
	if (InPawn) {
		auto PosessedTank = Cast<ATank>(InPawn);
		if (!ensure(PosessedTank)) { return; }

		// subscribe our local method to the deaths tank event
		PosessedTank->OnDeath.AddUniqueDynamic(this, &ATankAIController::OnPossesedTankDeath);
	}
}

void ATankAIController::OnPossesedTankDeath() {
	// UE_LOG(LogTemp, Warning, TEXT("Received"));
	if (!ensure(GetPawn())) { return; }
	GetPawn()->DetachFromControllerPendingDestroy();
}

void ATankAIController::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);
	PrimaryActorTick.bCanEverTick = true;

	auto ControlledTank = GetPawn();
	auto PlayerTank = GetWorld()->GetFirstPlayerController()->GetPawn();
	if (!ensure (ControlledTank && PlayerTank)) { return; } // TODO think about if this ensure is necesarry

	// Move towards player
	MoveToActor(PlayerTank, AcceptanceRadius); // TODO check if radius is in centimeters


	AimingComponent->AimAt(PlayerTank->GetActorLocation());

	//Fire if ready if aiming or locked
	if (AimingComponent->GetFiringStatus() == EFiringStatus::Locked) {
		// AimingComponent->Fire();
	}
	AimingComponent->Fire();
}



