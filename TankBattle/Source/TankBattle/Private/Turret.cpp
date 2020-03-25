// Fill out your copyright notice in the Description page of Project Settings.


#include "Turret.h"

void UTurret::RotateTurret(float RelativeSpeed)
{
	RelativeSpeed = FMath::Clamp<float>(RelativeSpeed, -1, 1);
	auto RotationChange = RelativeSpeed * MaxRotationRate * GetWorld()->DeltaTimeSeconds;
	auto NewRotation = RelativeRotation.Yaw + RotationChange;
	SetRelativeRotation(FRotator(0,NewRotation, 0));
	float Time = GetWorld()->GetTimeSeconds();
}