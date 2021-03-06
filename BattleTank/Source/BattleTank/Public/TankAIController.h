// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "AIController.h"
#include "TankAIController.generated.h"

class ATank;
class UTankAimingComponent;

/**
 * 
 */
UCLASS()
class BATTLETANK_API ATankAIController : public AAIController
{
	GENERATED_BODY()
	
private:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	virtual void SetPawn(APawn* InPawn) override; // called when pawn is posessed

	UFUNCTION()
		void OnPossesedTankDeath();

	UTankAimingComponent* AimingComponent = nullptr;


	ATank* PlayerTank = nullptr;

protected: // children can read it
	// how close can the AI tank get
	UPROPERTY(EditDefaultsOnly, Category = "Setup")
		float AcceptanceRadius = 5000;
};
