// Copyright : Adarsh.S 2020

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TankAimingComponent.generated.h"

//Forward declarations
class UBarrel;
class UTurret;
class AProjectile;
UENUM()
enum class EAimingStatus :uint8
{
	Reloading,
	Aiming,
	Locked
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TANKBATTLE_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UTankAimingComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	UPROPERTY(BlueprintReadOnly)
		EAimingStatus AimingStatus = EAimingStatus::Reloading;
public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	
	void AimAt(FVector AimLocation);
	UFUNCTION(BlueprintCallable, Category = "Setup")
	void Initialise(UBarrel* BarrelToSet, UTurret* TurretToSet);
	UFUNCTION(BlueprintCallable, Category = "Firing")
	void FireProjectile();
private:
	void MoveBarrelTowards(FVector AimDirection);
	void MoveTurretTowards(FVector AimDirection);
	bool IsBarrelMoving();
	UBarrel* Barrel;
	UTurret* Turret;
	bool bIsReloaded = false;
	UPROPERTY(EditAnywhere, Category = "Firing")
	float LaunchSpeed = 5000.f; //50 m/s

	UPROPERTY(EditAnywhere, Category = "SetUp")
		TSubclassOf<AProjectile> ProjectileClass;

	UPROPERTY(EditDefaultsOnly, Category = "Firing")
		float ReloadTime = 3.f;

	float PreviousFireTime = 0.f;
	float CurrentFireTime = 0.f;
	FVector LaunchDirection;
};
