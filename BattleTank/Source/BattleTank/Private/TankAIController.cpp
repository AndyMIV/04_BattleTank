// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "Tank.h"
#include "TankAIController.h"
// depends on movement component via pathfinding system

void ATankAIController::BeginPlay() {
	Super::BeginPlay();

	ATank * ControlledTank = Cast<ATank>(GetPawn());
	ATank * PlayerTank = Cast<ATank>(GetWorld()->GetFirstPlayerController()->GetPawn());

	UE_LOG(LogTemp, Warning, TEXT("AI Controller Begin Play"));

	auto PosessedAITank = ControlledTank;
	if (!PosessedAITank) {
		UE_LOG(LogTemp, Warning, TEXT("AI Tank Not Detected!!!"));
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("AI Tank Detected: %s"), *PosessedAITank->GetName());
	}


	PlayerTank = PlayerTank;
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

	ATank * ControlledTank = Cast<ATank>(GetPawn());
	ATank * PlayerTank = Cast<ATank>(GetWorld()->GetFirstPlayerController()->GetPawn());
	if (!ensure (ControlledTank && PlayerTank)) { return; }

	// Move towards player
	MoveToActor(PlayerTank, AcceptanceRadius); // TODO check if radius is in centimeters


	ControlledTank->AimAt(PlayerTank->GetActorLocation());

	//Fire if ready
	ControlledTank->Fire();
}



