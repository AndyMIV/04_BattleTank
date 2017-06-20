// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankTrack.h"

UTankTrack::UTankTrack() {
	PrimaryComponentTick.bCanEverTick = true;
}

void UTankTrack::BeginPlay() {
	OnComponentHit.AddDynamic(this, &UTankTrack::OnHit);
}

void UTankTrack::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction) {
	// Super::TickComponent(DeltaTime, TickType, ThisTickFunction);		- although there isnt any, allows BP tick component to function
	auto SlippageSpeed = FVector::DotProduct(GetRightVector(), GetComponentVelocity());  // the component of speed in the tank right direction
	// We want opposite direction of slipping (How much opposite slippage speed we need in this frame in this acceleration (y unit direction vector))
	auto CorrectionAcceleration = -SlippageSpeed / DeltaTime * GetRightVector();
	// calculate and apply sideways force f=ma
	auto TankRoot = Cast<UStaticMeshComponent>(GetOwner()->GetRootComponent()); // downcasting, allows us to use static mesh to get mass, as a scene component does not allow us to get physics mass
	auto CorrectionForce = (TankRoot->GetMass()*CorrectionAcceleration) / 2;  // there are 2 tracks, so divide by 2
	TankRoot->AddForce(CorrectionForce);
}

void UTankTrack::SetThrottle(float Throttle) {
	
	// UE_LOG(LogTemp, Warning, TEXT("Intend move forward throw: %f"), Throttle);
	// TODO clamp actual throttle value so player cannot change values
	auto ForceApplied = GetForwardVector() * Throttle * TrackMaxDrivingForce;
	auto ForceLocation = GetComponentLocation(); // returns the location of the tracks
	auto TankRoot = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent()); // we want to use the simplest thing possible, so we need to cast down the heirarchy
	TankRoot->AddForceAtLocation(ForceApplied, ForceLocation);
	// to get here, we went up the class heirarchy to the owner (Tank_BP), down to the root component, and then cased the static mesh to the 
	// primitive component
 }

void UTankTrack::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit) {
	
}
