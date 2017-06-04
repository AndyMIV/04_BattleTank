// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "TankAimingComponent.h"
#include "GameFramework/Pawn.h"
#include "Tank.generated.h"			// put new includes above

UCLASS()
class BATTLETANK_API ATank : public APawn
{
	GENERATED_BODY()

public:
	void AimAt(FVector Hitlocation);

	UFUNCTION(BlueprintCallable, Category = Setup)
		void SetBarrelReference(UStaticMeshComponent* BarrelToSet);

private:
	// Sets default values for this pawn's properties
	ATank();

	UPROPERTY(EditAnywhere, Category = Firing)
		float LaunchSpeed = 10000; // TODO find sensible default

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected: // no need for outside access, but accessible with UPROPERTY
	// reference to a tank aiming component
	UTankAimingComponent* TankAimingComponent = nullptr;
	
};
