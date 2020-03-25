// Fill out your copyright notice in the Description page of Project Settings.

#include "Engine/World.h"
#include "Barrel.h"

void UBarrel::Elevate(float RelativeSpeed)
{
	RelativeSpeed = FMath::Clamp<float>(RelativeSpeed,-1,1);
	auto ElevationChange = RelativeSpeed * MaxElevationSpeed * GetWorld()->DeltaTimeSeconds;
	auto NewElevation = RelativeRotation.Pitch + ElevationChange;
	NewElevation = FMath::Clamp<float>(NewElevation, MinElevationAngle,MaxElevationAngle);
	SetRelativeRotation(FRotator(NewElevation,0,0));
	float Time = GetWorld()->GetTimeSeconds();
}
