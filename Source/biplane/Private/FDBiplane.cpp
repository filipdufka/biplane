// Fill out your copyright notice in the Description page of Project Settings.


#include "FDBiplane.h"

// Sets default values
AFDBiplane::AFDBiplane() {
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
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
	
	FVector newFwd = fwd.RotateAngleAxis(0.5f * value, right);
	FQuat newRot = FRotationMatrix::MakeFromXY(newFwd, right).ToQuat();

	SetActorRotation(newRot);
}

// Called every frame
void AFDBiplane::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);
	
	float speed = 6000 * DeltaTime;
	FVector fwd = GetActorForwardVector();
	FVector pos = GetActorLocation();

	SetActorLocation(pos + speed * fwd);
}

// Called to bind functionality to input
void AFDBiplane::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAxis("Roll", this, &AFDBiplane::Roll);
	PlayerInputComponent->BindAxis("Pitch", this, &AFDBiplane::Pitch);
}

