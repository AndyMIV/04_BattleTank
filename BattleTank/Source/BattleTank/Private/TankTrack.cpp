// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankTrack.h"




void UTankTrack::SetThrottle(float Throttle) {
	auto Name = GetName();
	UE_LOG(LogTemp, Warning, TEXT("%s: throttle : %f"), *Name, Throttle);

	// TODO clamp actual throttle value so player cannot change values
	auto ForceApplied = GetForwardVector() * Throttle * TrackMaxDrivingForce;
	auto ForceLocation = GetComponentLocation(); // returns the location of the tracks
	auto TankRoot = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent()); // we want to use the simplest thing possible, so we need to cast down the heirarchy
	TankRoot->AddForceAtLocation(ForceApplied, ForceLocation);
	// to get here, we went up the class heirarchy to the owner (Tank_BP), down to the root component, and then cased the static mesh to the 
	// primitive component
 }