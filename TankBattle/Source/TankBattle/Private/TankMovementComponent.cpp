// Copyright : Adarsh.S 2020

#include "TankMovementComponent.h"
#include "TankTrack.h"

void UTankMovementComponent::HandleForwardMovement(float AxisValue)
{
	if (!ensure(LeftTrack && RightTrack)){return;}
	LeftTrack->SetThrottle(AxisValue);
	RightTrack->SetThrottle(AxisValue);
	//GetOwner()->AddActorLocalOffset(FVector(AxisValue*18,0,0));
}

void UTankMovementComponent::HandleTurnRight(float AxisValue)
{
	if (!ensure(LeftTrack && RightTrack)) { return; }
	LeftTrack->SetThrottle(AxisValue);
	RightTrack->SetThrottle(-AxisValue);
	//GetOwner()->AddActorLocalRotation(FRotator(0,AxisValue,0));
}

void UTankMovementComponent::HandleTurnLeft(float AxisValue)
{
	if (!ensure(LeftTrack && RightTrack)) { return; }
	LeftTrack->SetThrottle(-AxisValue);
	RightTrack->SetThrottle(AxisValue);
	//GetOwner()->AddActorLocalRotation(FRotator(0,-AxisValue,0));
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

