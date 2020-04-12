// Copyright : Adarsh.S 2020

#include "TankAimingComponent.h"
#include "Engine/World.h"
#include "Barrel.h"
#include "Turret.h"
#include "Projectile.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/PlayerController.h"

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
	if (AmmoLeft <= 0)
	{
		AimingStatus = EAimingStatus::OutOfAmmo;
	}
	else if (! bIsReloaded)
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
	if (!ensure(Turret)) { return; }
	if(FMath::Abs(DeltaRotation.Yaw) < 180)
	{
		Turret->RotateTurret(DeltaRotation.Yaw);
	}
	else
	{
		Turret->RotateTurret(-DeltaRotation.Yaw);
	}		
}

bool UTankAimingComponent::IsBarrelMoving()
{
	if (!ensure(Barrel)) { return false; }
	auto BarrelDirection = Barrel->GetForwardVector();
	return !BarrelDirection.Equals(LaunchDirection,0.01);
}

bool UTankAimingComponent::FireProjectile()
{
	if (!ensure(Barrel)){return false;}
	if (bIsReloaded && AmmoLeft > 0)
	{
		PreviousFireTime = GetWorld()->GetTimeSeconds();
		FTransform ProjectileTransform = Barrel->GetSocketTransform(FName("Muzzle"));
		auto ProjectileSpawned = GetWorld()->SpawnActor(ProjectileClass, &ProjectileTransform, FActorSpawnParameters());
		Cast<AProjectile>(ProjectileSpawned)->LaunchProjectile(LaunchSpeed);
		AmmoLeft--;
		bIsFiringSuccesfull = true;
		return bIsFiringSuccesfull;
	}
	else
	{
		bIsFiringSuccesfull = false;
		return bIsFiringSuccesfull;
	}
}

int32 UTankAimingComponent::GetAmmoLeft() const
{
	return AmmoLeft;
}

EAimingStatus UTankAimingComponent::GetAimingStatus() const
{
	return AimingStatus;
}


