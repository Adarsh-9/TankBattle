// Copyright : Adarsh.S 2020

#include "Components/SceneComponent.h"
#include "Engine/World.h"
#include "Barrel.h"
#include "Turret.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/PlayerController.h"
#include "../Public/TankAimingComponent.h"

// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	// ...
}


// Called when the game starts
void UTankAimingComponent::BeginPlay()
{
	Super::BeginPlay();
	// ...
	
}


// Called every frame
void UTankAimingComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	// ...
}


void UTankAimingComponent::AimAt(FVector AimLocation,float LaunchSpeed)
{
	auto StartLocation = Barrel->GetSocketLocation(FName("Muzzle"));
	FVector LaunchVelocity;
	bool bHaveAimSolution = UGameplayStatics::SuggestProjectileVelocity
		(
			this,
			LaunchVelocity,
			StartLocation,
			AimLocation,
			LaunchSpeed,
			false,
			0.f,
			0.f,
			ESuggestProjVelocityTraceOption::DoNotTrace,
			FCollisionResponseParams::DefaultResponseParam,
			TArray<AActor*>(),
			false);
	FVector LaunchDirection = LaunchVelocity.GetSafeNormal();
	if (bHaveAimSolution)
	{
		MoveBarrelTowards(LaunchDirection);
		MoveTurretTowards(LaunchDirection);
	}

	return;
}

void UTankAimingComponent::SetBarrel(UBarrel* BarrelToSet)
{
	Barrel = BarrelToSet;
	return;
}

void UTankAimingComponent::SetTurret(UTurret* TurretToSet)
{
	Turret = TurretToSet;
}

void UTankAimingComponent::MoveBarrelTowards(FVector AimDirection)
{
	auto BarrelRotation = Barrel->GetForwardVector().Rotation();
	auto AimRotation = AimDirection.Rotation();
	auto DeltaRotation = AimRotation - BarrelRotation;
	if (Barrel)
	{
		Barrel->Elevate(DeltaRotation.Pitch);
	}
	else
		return;
}

void UTankAimingComponent::MoveTurretTowards(FVector AimDirection)
{
	FRotator TurretRotation = Barrel->GetForwardVector().Rotation();
	FRotator AimRotation = AimDirection.Rotation();
	FRotator DeltaRotation = AimRotation - TurretRotation;
	if (Turret)
	{
		Turret->RotateTurret(DeltaRotation.Yaw);
	}
	else
		return;
}


