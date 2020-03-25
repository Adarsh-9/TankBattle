// Fill out your copyright notice in the Description page of Project Settings.

#include "../Public/TankAimingComponent.h"
#include "../Public/Tank.h"
#include "Components/InputComponent.h"
#include "Barrel.h"
// Sets default values
ATank::ATank()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	AimingComponent = CreateDefaultSubobject<UTankAimingComponent>(FName("Aiming Component"));
}

// Called when the game starts or when spawned
void ATank::BeginPlay()
{
	Super::BeginPlay();
	
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
	AimingComponent->AimAt(HitLocation,LaunchSpeed);
}

void ATank::FireProjectile()
{
	UE_LOG(LogTemp,Warning,TEXT("Firing projectile"))
}

void ATank::SetBarrel(UBarrel* BarrelToSet)
{
	AimingComponent->SetBarrel(BarrelToSet);
}

void ATank::SetTurret(UTurret* TurretToSet)
{
	AimingComponent->SetTurret(TurretToSet);
}


