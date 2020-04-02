// Fill out your copyright notice in the Description page of Project Settings.

#include "TankTrack.h"
#include "TankMovementComponent.h"

void UTankMovementComponent::HandleForwardMovement(float AxisValue)
{
	LeftTrack->SetThrottle(AxisValue);
	RightTrack->SetThrottle(AxisValue);
}

void UTankMovementComponent::HandleTurnRight(float AxisValue)
{
	LeftTrack->SetThrottle(AxisValue);
	RightTrack->SetThrottle(-AxisValue);
}

void UTankMovementComponent::HandleTurnLeft(float AxisValue)
{
	LeftTrack->SetThrottle(-AxisValue);
	RightTrack->SetThrottle(AxisValue);
}

void UTankMovementComponent::SetTracks(UTankTrack* LeftTrackToSet, UTankTrack* RightTrackToSet)
{
	LeftTrack = LeftTrackToSet;
	RightTrack = RightTrackToSet;
}
