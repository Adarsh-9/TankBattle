// Fill out your copyright notice in the Description page of Project Settings.


#include "../Public/TankAiController.h"
#include "Engine/World.h"
#include "GameFramework/PlayerController.h"

ATankAiController::ATankAiController() 
{
}
void ATankAiController::BeginPlay()
{
	PlayerTank = GetWorld()->GetFirstPlayerController()->GetPawn();
	if (GetControlledTank())
	{
		UE_LOG(LogTemp,Warning,TEXT("Ai tank is possed by AI controller: %s"),*GetControlledTank()->GetName())
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Ai tank is not possed by AI controller"))
	}
	if (PlayerTank)
	{
		UE_LOG(LogTemp, Warning, TEXT("Aiming at player:%s"), *PlayerTank->GetName())
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("No player to Aim"))
	}
}
void ATankAiController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	UE_LOG(LogTemp,Warning,TEXT("Inside ai controller Tick"))
}
ATank* ATankAiController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}
