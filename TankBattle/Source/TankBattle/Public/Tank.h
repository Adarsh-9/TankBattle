// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Tank.generated.h"

//Forward Declarations
class UTankAimingComponent;
class UBarrel;
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
	void SetBarrel(UBarrel* BarrelToSet);
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	//variables and methods defined by me
	void AimAt(FVector HitLocation);
	UTankAimingComponent* AimingComponent;
private:
	UPROPERTY(EditAnywhere, Category = "Firing")
	float LaunchSpeed = 5000.f; //50 m/s
};
