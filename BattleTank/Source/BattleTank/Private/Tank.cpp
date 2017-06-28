// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"

#include "Tank.h"

// Sets default values
ATank::ATank()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	UE_LOG(LogTemp, Warning, TEXT("CustomDebug: Tank.cpp Consructor"));

}

void ATank::BeginPlay() {
	Super::BeginPlay();
	CurrentHealth = StartingHealth;
}

float ATank::GetHealthPercentage() const {
	// floating point division
	return (float)CurrentHealth / (float)StartingHealth;
}

float ATank::TakeDamage(float DamageAmount, struct FDamageEvent const & DamageEvent, class AController * EventInstigator, AActor * DamageCauser) {
	// you don't want to compare floats, so we are converting to points (int32). round damage to nearest integer
	int32 DamagePoints = FPlatformMath::RoundToInt(DamageAmount);
	int32 DamageToApply = FMath::Clamp(DamagePoints, 0, CurrentHealth);
	// now we can say for sure if the tank has 0 health.

	CurrentHealth -= DamageToApply;
	if (CurrentHealth <= 0) {
		UE_LOG(LogTemp, Warning, TEXT("Tank Died"));
		OnDeath.Broadcast();
	}

	// UE_LOG(LogTemp, Warning, TEXT("Damage Ammount:%f, DamageToApply:%i"), DamageAmount, DamageToApply);
	return DamageToApply;
}
