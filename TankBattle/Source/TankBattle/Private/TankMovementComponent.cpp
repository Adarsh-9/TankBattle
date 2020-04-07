// Copyright : Adarsh.S 2020

#include "TankTrack.h"
#include "TankMovementComponent.h"

void UTankMovementComponent::HandleForwardMovement(float AxisValue)
{
	if (!ensure(LeftTrack && RightTrack)){return;}
	LeftTrack->SetThrottle(AxisValue);
	RightTrack->SetThrottle(AxisValue);
}

void UTankMovementComponent::HandleTurnRight(float AxisValue)
{
	if (!ensure(LeftTrack && RightTrack)) { return; }
	LeftTrack->SetThrottle(AxisValue);
	RightTrack->SetThrottle(-AxisValue);
}

void UTankMovementComponent::HandleTurnLeft(float AxisValue)
{
	if (!ensure(LeftTrack && RightTrack)) { return; }
	LeftTrack->SetThrottle(-AxisValue);
	RightTrack->SetThrottle(AxisValue);
}

void UTankMovementComponent::Initialise(UTankTrack* LeftTrackToSet, UTankTrack* RightTrackToSet)
{
	if (!ensure(LeftTrackToSet && RightTrackToSet)) { return; }
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
