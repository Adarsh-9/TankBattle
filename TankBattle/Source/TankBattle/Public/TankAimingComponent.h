// Copyright : Adarsh.S 2020

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TankAimingComponent.generated.h"

//Forward declarations
class UBarrel;
class UTurret;
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
		EAimingStatus AimngStatus = EAimingStatus::Reloading;
public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	
	void AimAt(FVector AimLocation,float LaunchSpeed);
	UFUNCTION(BlueprintCallable, Category = "Setup")
	void Initialise(UBarrel* BarrelToSet, UTurret* TurretToSet);
	//void SetBarrel(UBarrel* BarrelToSet);//TODO Remove and make a better architecture
	//void SetTurret(UTurret* TurretToSet);//TODO Remove and make a better architecture
private:
	UBarrel* Barrel;
	UTurret* Turret;
	void MoveBarrelTowards(FVector AimDirection);
	void MoveTurretTowards(FVector AimDirection);
};
