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

void UTankMovementComponent::RequestDirectMove(const FVector& MoveVelocity, bool bForceMaxSpeed)
{
	auto MoveDirection = MoveVelocity.GetSafeNormal();
	auto TankDirection = GetOwner()->GetActorForwardVector().GetSafeNormal();

	float MovementAxisValue = FVector::DotProduct(MoveDirection,TankDirection);
	HandleForwardMovement(MovementAxisValue);

	auto TurnAxisValue = FVector::CrossProduct(TankDirection,MoveDirection).Z;
	HandleTurnRight(TurnAxisValue);
}
