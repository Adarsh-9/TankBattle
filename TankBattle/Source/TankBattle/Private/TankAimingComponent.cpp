// Copyright : Adarsh.S 2020

//#include "Components/SceneComponent.h"
#include "Engine/World.h"
#include "Barrel.h"
#include "Turret.h"
#include "Projectile.h"
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
	CurrentFireTime = GetWorld()->GetTimeSeconds();
	bIsReloaded = ((CurrentFireTime - PreviousFireTime) >= ReloadTime);
	if (! bIsReloaded)
	{
		AimingStatus = EAimingStatus::Reloading;
	}
	else if (IsBarrelMoving())
	{
		AimingStatus = EAimingStatus::Aiming;
	}
	else
	{
		AimingStatus = EAimingStatus::Locked;
	}
}

void UTankAimingComponent::AimAt(FVector AimLocation)
{
	if (!ensure(Barrel))
	{
		return;
	}
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
	LaunchDirection = LaunchVelocity.GetSafeNormal();
	if (bHaveAimSolution)
	{
		MoveBarrelTowards(LaunchDirection);
		MoveTurretTowards(LaunchDirection);
	}

	return;
}

void UTankAimingComponent::Initialise(UBarrel* BarrelToSet, UTurret* TurretToSet)
{
	if (!ensure(BarrelToSet && TurretToSet))
	{
		return;
	}
	Barrel = BarrelToSet;
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

bool UTankAimingComponent::IsBarrelMoving()
{
	if (!ensure(Barrel)) { return false; }
	auto BarrelDirection = Barrel->GetForwardVector();
	return !BarrelDirection.Equals(LaunchDirection,0.01);
}

void UTankAimingComponent::FireProjectile()
{
	if (bIsReloaded && ensure(Barrel))
	{
		PreviousFireTime = GetWorld()->GetTimeSeconds();
		FTransform ProjectileTransform = Barrel->GetSocketTransform(FName("Muzzle"));
		auto ProjectileSpawned = GetWorld()->SpawnActor(ProjectileClass, &ProjectileTransform, FActorSpawnParameters());
		Cast<AProjectile>(ProjectileSpawned)->LaunchProjectile(LaunchSpeed);
	}
}


