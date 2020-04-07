// Copyright : Adarsh.S 2020
#include "../Public/Tank.h"
#include "../Public/TankAimingComponent.h"
#include "Components/InputComponent.h"
#include "Projectile.h"
#include "Barrel.h"
// Sets default values
ATank::ATank()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ATank::BeginPlay()
{
	Super::BeginPlay();
	AimingComponent = FindComponentByClass<UTankAimingComponent>();
}



// Called every frame
void ATank::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void ATank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ATank::AimAt(FVector HitLocation)
{
	if (!ensure(AimingComponent))
	{
		return;
	}
	AimingComponent->AimAt(HitLocation,LaunchSpeed);
}

void ATank::FireProjectile()
{
	CurrentFireTime = GetWorld()->GetTimeSeconds();
	if (CurrentFireTime - PreviousFireTime >= ReloadTime && ensure(BarrelReference))
	{
		PreviousFireTime = GetWorld()->GetTimeSeconds();
		FTransform ProjectileTransform = BarrelReference->GetSocketTransform(FName("Muzzle"));
		auto ProjectileSpawned = GetWorld()->SpawnActor(ProjectileClass, &ProjectileTransform, FActorSpawnParameters());
		Cast<AProjectile>(ProjectileSpawned)->LaunchProjectile(LaunchSpeed);
	}
}
void ATank::InitialiseComponentData(UBarrel* BarrelToSet)
{
	if ( !ensure(BarrelToSet))
	{
		return;
	}
	BarrelReference = BarrelToSet;
}




