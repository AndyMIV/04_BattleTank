// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankProjectileMovementComponent.h"

// we are using a different method (calling ProjectileMovementComponent directly), so this
// class is currently uninitiated. However, it can be substituted and will work
UTankProjectileMovementComponent::UTankProjectileMovementComponent() {
	bAutoActivate = false;

}