// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Tank.h"
#include "GameFramework/PlayerController.h"
#include "TankPlayercontroller.generated.h"

/**
 * 
 */
UCLASS()
class TANKBATTLE_API ATankPlayercontroller : public APlayerController
{
	GENERATED_BODY()
public:
	ATank* GetControlledTank() const;
	void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
};
