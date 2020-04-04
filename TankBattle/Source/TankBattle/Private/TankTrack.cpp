// Fill out your copyright notice in the Description page of Project Settings.


#include "TankTrack.h"

void UTankTrack::SetThrottle(float ThrottleValue)
{
	
	FVector ForceApplied = GetForwardVector() * MaxThrottleForce * ThrottleValue;
	auto TankRoot = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());
	auto ForceLocation = GetComponentLocation();
	TankRoot->AddForceAtLocation(ForceApplied,ForceLocation,NAME_None);
}