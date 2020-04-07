// Copyright : Adarsh.S 2020

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Tank.generated.h"

//Forward Declarations
class UTankAimingComponent;
class UTurret;
class UBarrel;
class AProjectile;
class UTankTrack;

UCLASS()
class TANKBATTLE_API ATank : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ATank();
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable, Category = "SetUp")
	void InitialiseComponentData(UBarrel* BarrelToSet, UTurret* TurretToSet);
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;


	void AimAt(FVector HitLocation);
	UPROPERTY(BlueprintReadOnly)
	UTankAimingComponent* AimingComponent;

	UFUNCTION(BlueprintCallable,Category = "Firing")
	void FireProjectile();
private:
	UPROPERTY(EditAnywhere, Category = "Firing")
	float LaunchSpeed = 5000.f; //50 m/s
	UPROPERTY(EditAnywhere,Category = "SetUp")
	TSubclassOf<AProjectile> ProjectileClass;
	UBarrel* BarrelReference;
	UPROPERTY(EditDefaultsOnly,Category = "Firing")
	float ReloadTime = 3.f;
	float PreviousFireTime = 0.f;
	float CurrentFireTime = 0.f;
};
