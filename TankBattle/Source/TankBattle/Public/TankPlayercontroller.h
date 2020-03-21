// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Tank.h"
#include "Engine/World.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/PlayerController.h"
#include "TankPlayercontroller.generated.h"

/**
 * 
 */
UCLASS()
class TANKBATTLE_API ATankPlayercontroller : public APlayerController
{
	GENERATED_BODY()
private:
	void AimAtReticle();
	bool GetLookDirection(FVector& TraceWorldDirection);
	FHitResult TraceHitResult;
	FVector TraceWorldDirection;

	UPROPERTY(EditAnywhere)
	float HitRange = 100000.f;

public:
	ATank* GetControlledTank() const;
	void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
};
