// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Tank.h"
#include "Engine/World.h"
#include "GameFramework/PlayerController.h"
#include "AIController.h"
#include "TankAIController.generated.h"

/**
 * 
 */
UCLASS()
class TANKBATTLE_API ATankAIController : public AAIController
{
	GENERATED_BODY()
protected:
    virtual void BeginPlay() override;
public:
    virtual void Tick(float DeltaTime) override;
private:
    ATank* GetControlledTank();
    ATank* GetPlayerTank();
    float AcceptanceRadius = 3000.f;
};
