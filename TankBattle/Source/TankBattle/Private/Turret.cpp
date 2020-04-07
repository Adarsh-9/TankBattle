// Copyright : Adarsh.S 2020


#include "Turret.h"

void UTurret::RotateTurret(float RelativeSpeed)
{
	RelativeSpeed = FMath::Clamp<float>(RelativeSpeed, -1, 1);
	auto RotationChange = RelativeSpeed * MaxRotationRate * GetWorld()->DeltaTimeSeconds;
	auto NewRotation = RelativeRotation.Yaw + RotationChange;
	SetRelativeRotation(FRotator(0,NewRotation, 0));
	float Time = GetWorld()->GetTimeSeconds();
}