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
}

ATank* ATankPlayercontroller::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}

