// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankTurret.h"


void UTankTurret::Azimuth(float RelativeSpeed) {
	// move barrel the right ammount this frame
	// given a max elevation speed, and the frame time. (scaling) - time dialation
	RelativeSpeed = FMath::Clamp<float>(RelativeSpeed, -1, 1); // TODO change scaling

	auto AzimuthChange = RelativeSpeed * MaxDegreesPerSecond * GetWorld()->DeltaTimeSeconds; // deltatimeseconds = this frame. this makes sure its framerate independent
	auto RawNewAzimuth = RelativeRotation.Yaw + AzimuthChange;

	SetRelativeRotation(FRotator(0, RawNewAzimuth, 0));

}

