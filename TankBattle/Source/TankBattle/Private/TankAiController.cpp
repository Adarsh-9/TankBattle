//Copyright : Adarsh.S 2020

#include "Tank.h"
#include "Engine/World.h"
#include "GameFramework/PlayerController.h"
#include "TankAIController.h"

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();
	if (!GetControlledTank())
	{
		UE_LOG(LogTemp, Error, TEXT("AI controller not possessed ay Tank"));
	}
}
void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (ensure(GetPlayerTank()))
	{
		MoveToActor(GetPlayerTank(),AcceptanceRadius);
		GetControlledTank()->AimAt(GetPlayerTank()->GetActorLocation());
		GetControlledTank()->FireProjectile();
	}
}

ATank* ATankAIController::GetControlledTank()
{
	return Cast<ATank>(GetPawn());
}

ATank* ATankAIController::GetPlayerTank()
{
	return Cast<ATank>(GetWorld()->GetFirstPlayerController()->GetPawn());
}


