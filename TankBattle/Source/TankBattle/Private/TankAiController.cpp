//Copyright : Adarsh.S 2020

#include "TankAIController.h"
#include "Engine/World.h"
#include "TankAimingComponent.h"
#include "GameFramework/PlayerController.h"
#include "Tank.h"

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();
	if (!GetPawn())
	{
		UE_LOG(LogTemp, Error, TEXT("AI controller not possessed ay Tank"));
	}
}


void ATankAIController::SetPawn(APawn* InPawn)
{
	Super::SetPawn(InPawn);
	if (InPawn)
	{
		auto PossedTank = Cast<ATank>(InPawn);
		if (!ensure(PossedTank)) { return; }
		PossedTank->TankDead.AddUniqueDynamic(this, &ATankAIController::OnPossessedTankDeath);
	}
}
void ATankAIController::OnPossessedTankDeath()
{
	GetPawn()->DetachFromControllerPendingDestroy();
	UE_LOG(LogTemp,Warning,TEXT("AI Tank Death Message Received"))
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



