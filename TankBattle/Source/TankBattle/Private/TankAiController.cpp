//Copyright : Adarsh.S 2020

#include "Engine/World.h"
#include "TankAimingComponent.h"
#include "GameFramework/PlayerController.h"
#include "TankAIController.h"

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();
	if (!GetPawn())
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
		auto AimingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();
		AimingComponent->AimAt(GetPlayerTank()->GetActorLocation());
		if (AimingComponent->GetAimingStatus() == EAimingStatus::Locked && AimingComponent->GetAmmoLeft() > 0)
		{
			AimingComponent->FireProjectile();
		}
	}
}

APawn* ATankAIController::GetPlayerTank()
{
	return GetWorld()->GetFirstPlayerController()->GetPawn();
}


