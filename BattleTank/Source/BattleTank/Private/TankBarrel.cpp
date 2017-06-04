// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankBarrel.h"


void UTankBarrel::Elevate(float DegreesPerSecond) {
	// move barrel the right ammount this frame


	// given a max elevation speed, and the frame time. (scaling)
	UE_LOG(LogTemp, Warning, TEXT("Barrel Elevate call at %f"), DegreesPerSecond);
}

