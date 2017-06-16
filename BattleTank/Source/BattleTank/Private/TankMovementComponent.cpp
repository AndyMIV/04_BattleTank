// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankTrack.h"
#include "TankMovementComponent.h"

void UTankMovementComponent::Initialize(UTankTrack* LeftTrackToSet, UTankTrack* RightTrackToSet) {
	LeftTrack = LeftTrackToSet;
	RightTrack = RightTrackToSet;
}


void UTankMovementComponent::IntendMoveForward(float Throw) {
	// protect your pointers!!
	if (!LeftTrack || !RightTrack) { return; }
	LeftTrack->SetThrottle(Throw);
	RightTrack->SetThrottle(Throw);
	// TODO include both input control methods. With both, forward is doubled with both use cases
}

void UTankMovementComponent::IntendTurnRight(float Throw) {
	if (!LeftTrack || !RightTrack) { return; }
	LeftTrack->SetThrottle(Throw);
	RightTrack->SetThrottle(-Throw);
	// TODO prevent double speed due to dual control use
}

void UTankMovementComponent::RequestDirectMove(const FVector& MoveVelocity, bool bForceMaxSpeed) {
	// no need to replace super, as we are replacing the functionality

	// uses world space
	auto TankForwardDirection = GetOwner()->GetActorForwardVector().GetSafeNormal();
	auto AIForwardIntention = MoveVelocity.GetSafeNormal();
	IntendMoveForward(FVector::DotProduct(TankForwardDirection, AIForwardIntention));


	auto ZCrossed = FVector::CrossProduct(TankForwardDirection, AIForwardIntention).Z;
	IntendTurnRight(ZCrossed);
	// UE_LOG(LogTemp, Warning, TEXT("AI Tank Moving: %s at %s"), *GetOwner()->GetName(), *AIForwardIntention.toString());
}
