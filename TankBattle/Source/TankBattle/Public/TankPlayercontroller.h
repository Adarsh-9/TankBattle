// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TankPlayercontroller.generated.h"

//Forward Declarations
class ATank;
/**
 * 
 */
UCLASS()
class TANKBATTLE_API ATankPlayercontroller : public APlayerController
{
	GENERATED_BODY()
private:
	FHitResult TraceHitResult;
	FVector TraceWorldDirection;

	UPROPERTY(EditAnywhere,Category = "Aiming")
	float HitRange = 50000.f;
	UPROPERTY(EditAnywhere, Category = "Aiming")
	float CrosshairXLocation = 0.5;
	UPROPERTY(EditAnywhere, Category = "Aiming")
	float CrosshairYLocation = 0.3333;
	void AimAtReticle();
	bool GetLookDirection(FVector& TraceWorldDirection);
	bool GetLineTraceHitLocation(FVector& TraceHitLocation);

public:
	ATank* GetControlledTank() const;
	void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
};
