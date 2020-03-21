// Fill out your copyright notice in the Description page of Project Settings.


#include "..\Public\TankPlayercontroller.h"


void ATankPlayercontroller::BeginPlay()
{
	Super::BeginPlay();
	if (GetControlledTank())
	{
		UE_LOG(LogTemp, Warning, TEXT("Inside Player Controller BeginPlay %s"), *GetControlledTank()->GetName())
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("No tank is possessed by the controller"))
	}
}

void ATankPlayercontroller::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	AimAtReticle();
}

ATank* ATankPlayercontroller::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}
void ATankPlayercontroller::AimAtReticle()
{

	if (GetLookDirection(TraceWorldDirection))
	{
		FVector LineTraceStart = PlayerCameraManager->GetCameraLocation();
		FVector LineTraceEnd = LineTraceStart + TraceWorldDirection * HitRange;
		GetWorld()->LineTraceSingleByChannel(
			TraceHitResult,
			LineTraceStart,
			LineTraceEnd,
			ECollisionChannel::ECC_Visibility
			);
		FVector TraceHitLocation;
		if (TraceHitResult.IsValidBlockingHit())
		{
			TraceHitLocation = TraceHitResult.Location;
			UE_LOG(LogTemp,Warning,TEXT("Hit Location is:%s"),*TraceHitResult.Location.ToString())
		}
		else
		{
			TraceHitLocation = FVector(0);
			UE_LOG(LogTemp, Warning, TEXT("Hit Location is:%s"), *TraceHitResult.Location.ToString())
		}
	}
	
}

bool ATankPlayercontroller::GetLookDirection(FVector& WorldDirection)
{
	int32 ViewPortX, ViewPortY;
	GetViewportSize(ViewPortX, ViewPortY);
	//Calculating Reticle Position on screen
	FVector2D ReticleScreenLocation = FVector2D(
		ViewPortX * GetControlledTank()->CrosshairXLocation,
		ViewPortY * GetControlledTank()->CrosshairYLocation);

	FVector CameraWorldLocation;
	return DeprojectScreenPositionToWorld(
		ReticleScreenLocation.X,
		ReticleScreenLocation.Y,
		CameraWorldLocation,
		WorldDirection);

}

