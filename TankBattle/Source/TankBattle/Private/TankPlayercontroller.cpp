// Copyright : Adarsh.S 2020

#include "Engine/World.h"
#include "DrawDebugHelpers.h"
#include "TankAimingComponent.h"
#include "GameFramework/PlayerController.h"
#include "..\Public\TankPlayercontroller.h"


void ATankPlayercontroller::BeginPlay()
{
	Super::BeginPlay();
	if (!ensure(GetControlledTank()))
	{
		UE_LOG(LogTemp, Error, TEXT("No tank is possessed by the controller"))
	}
	AimingComponent = GetControlledTank()->FindComponentByClass<UTankAimingComponent>();
	if (ensure(AimingComponent))
	{
		FoundAimingcomponent(AimingComponent);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("No Aiming Component is found in tank"))
	}
}

void ATankPlayercontroller::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	AimAtReticle();
}

APawn* ATankPlayercontroller::GetControlledTank() const
{
	return GetPawn();
}


void ATankPlayercontroller::AimAtReticle()
{

	if (GetLookDirection(TraceWorldDirection) && ensure(AimingComponent))
	{
		FVector TraceHitLocation;
		if (GetLineTraceHitLocation(TraceHitLocation))
		{
			AimingComponent->AimAt(TraceHitLocation);
		}
		else
		{
			TraceHitLocation = FVector(0);
			AimingComponent->AimAt(TraceHitLocation);
		}
	}
}
bool ATankPlayercontroller::GetLookDirection(FVector& WorldDirection)
{
	int32 ViewPortX, ViewPortY;
	GetViewportSize(ViewPortX, ViewPortY);
	//Calculating Reticle Position on screen
	FVector2D ReticleScreenLocation = FVector2D(
		ViewPortX * CrosshairXLocation,
		ViewPortY * CrosshairYLocation);

	FVector CameraWorldLocation;
	return DeprojectScreenPositionToWorld(
		ReticleScreenLocation.X,
		ReticleScreenLocation.Y,
		CameraWorldLocation,
		WorldDirection);

}

bool ATankPlayercontroller::GetLineTraceHitLocation(FVector& TraceHitLocation)
{
	FVector LineTraceStart = PlayerCameraManager->GetCameraLocation();
	FVector LineTraceEnd = LineTraceStart + TraceWorldDirection * HitRange;
	GetWorld()->LineTraceSingleByChannel(
		TraceHitResult,
		LineTraceStart,
		LineTraceEnd,
		ECollisionChannel::ECC_Visibility
	);
	TraceHitLocation = TraceHitResult.Location;
	//DrawDebugLine(GetWorld(), LineTraceStart + TraceWorldDirection * 100, TraceHitLocation, FColor(255, 0, 0), false, 0.f, 0.f, 2.f);
	return TraceHitResult.IsValidBlockingHit();
}



