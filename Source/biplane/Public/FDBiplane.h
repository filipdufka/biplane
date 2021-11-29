// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "FDBiplane.generated.h"

UCLASS()
class BIPLANE_API AFDBiplane : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AFDBiplane();

protected:
	void Accelerate(float value);

	void Roll(float value);
	void Pitch(float value);
	
	void AccUpdate(float DeltaTime);
	void SpeedUpdate(float DeltaTime);
	void LocUpdate(float DeltaTime);

	float thrust;
	FVector acc;
	FVector speed;


public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
