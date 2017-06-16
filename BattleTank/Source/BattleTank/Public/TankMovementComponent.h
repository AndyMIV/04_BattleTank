// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/NavMovementComponent.h"
#include "TankMovementComponent.generated.h"

class UTankTrack;

/**
 * Responsible for driving the tank tracks
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent)) // necesarry for seeing component through the "add component" button
class BATTLETANK_API UTankMovementComponent : public UNavMovementComponent
{
	GENERATED_BODY()
	
public:

	UFUNCTION(BlueprintCallable, Category = "Setup")
	void Initialize(UTankTrack* LeftTrackToSet, UTankTrack* RightTrackToSet);

	UFUNCTION(BlueprintCallable, Category = "Controls")
	void IntendMoveForward(float Throw);  // how far back controller is moved

	UFUNCTION(BlueprintCallable, Category = "Controls")
	void IntendTurnRight(float Throw);

private:
	// Intercepts the engine call and overrides it with our own version of RequestDirectMove
	// called from the pathfinding logic by the AI controllers
	void RequestDirectMove(const FVector& MoveVelocity, bool bForceMaxSpeed) override;

	UTankTrack* LeftTrack = nullptr;
	UTankTrack* RightTrack = nullptr;

	
	
};
