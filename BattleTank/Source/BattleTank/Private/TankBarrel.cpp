// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankBarrel.h"


void UTankBarrel::Elevate(float RelativeSpeed) {
	// move barrel the right ammount this frame
	// given a max elevation speed, and the frame time. (scaling) - time dialation
	RelativeSpeed = FMath::Clamp<float>(RelativeSpeed, -1, 1);
	auto ElevationChange = RelativeSpeed * MaxDegreesPerSecond * GetWorld()->DeltaTimeSeconds; // deltatimeseconds = this frame. this makes sure its framerate independent
	auto RawNewElevation = RelativeRotation.Pitch + ElevationChange;

	RawNewElevation = FMath::Clamp<float>(RawNewElevation, MinElevation, MaxElevation);
	SetRelativeRotation(FRotator(RawNewElevation, 0, 0));
	
}

