// Fill out your copyright notice in the Description page of Project Settings.


#include "FDBiplane.h"

// Sets default values
AFDBiplane::AFDBiplane() {
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	speed = FVector(0, 0, 0);
	acc = FVector(0, 0, 0);
}

void AFDBiplane::Accelerate(float value) {
	thrust = FMath::Lerp(thrust, value, 0.02f);
}

void AFDBiplane::Roll(float value) {
	FVector fwd = GetActorForwardVector();
	FVector up = GetActorUpVector();

	FVector newUp = up.RotateAngleAxis(1.1f * value, fwd);
	FQuat newRot = FRotationMatrix::MakeFromXZ(fwd, newUp).ToQuat();

	SetActorRotation(newRot);
}

void AFDBiplane::Pitch(float value) {
	FVector fwd = GetActorForwardVector();
	FVector right = GetActorRightVector();
	
	FVector newFwd = fwd.RotateAngleAxis(1.5f * value, right);
	FQuat newRot = FRotationMatrix::MakeFromXY(newFwd, right).ToQuat();

	SetActorRotation(newRot);
}

void AFDBiplane::AccUpdate(float DeltaTime) {
	FVector fwd = GetActorForwardVector();
	float dot = 1.f - FMath::Abs(FVector::DotProduct(fwd.GetSafeNormal(), speed.GetSafeNormal()));
	acc = FVector(0, 0, 0);
	acc += FVector(0, 0, -9.8f); // gravity
	acc += fwd * 50 * thrust; // thrust
	//acc += fwd * 50;
	//acc -= speed * dot;

	thrust = FMath::Lerp(thrust, 0.f, 0.02f);
}

void AFDBiplane::SpeedUpdate(float DeltaTime) {
	FVector fwd = GetActorForwardVector();
	speed += acc * DeltaTime;
	float dot = 1.f - FMath::Abs(FVector::DotProduct(fwd.GetSafeNormal(), speed.GetSafeNormal()));	
	speed = FMath::Lerp(speed, fwd * speed.Size(), dot);
}

void AFDBiplane::LocUpdate(float DeltaTime) {
	FVector pos = GetActorLocation();
	SetActorLocation(pos + speed);
}

// Called every frame
void AFDBiplane::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);
	
	AccUpdate(DeltaTime);
	SpeedUpdate(DeltaTime);
	LocUpdate(DeltaTime);
}

// Called to bind functionality to input
void AFDBiplane::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAxis("Roll", this, &AFDBiplane::Roll);
	PlayerInputComponent->BindAxis("Pitch", this, &AFDBiplane::Pitch);
	PlayerInputComponent->BindAxis("Thrust", this, &AFDBiplane::Accelerate);
}

