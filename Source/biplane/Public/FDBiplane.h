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
	void Roll(float value);
	void Pitch(float value);

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
