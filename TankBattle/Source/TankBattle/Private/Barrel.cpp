// Copyright : Adarsh.S 2020
#include "Barrel.h"
#include "Engine/World.h"

void UBarrel::Elevate(float RelativeSpeed)
{
	RelativeSpeed = FMath::Clamp<float>(RelativeSpeed,-1,1);
	auto ElevationChange = RelativeSpeed * MaxElevationSpeed * GetWorld()->DeltaTimeSeconds;
	auto NewElevation = RelativeRotation.Pitch + ElevationChange;
	NewElevation = FMath::Clamp<float>(NewElevation, MinElevationAngle,MaxElevationAngle);
	SetRelativeRotation(FRotator(NewElevation,0,0));
}
