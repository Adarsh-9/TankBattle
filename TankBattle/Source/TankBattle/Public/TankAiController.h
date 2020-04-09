// Copyright : Adarsh.S 2020

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "TankAIController.generated.h"

/**
 This class is responsible for controlling AI tanks
 */
class ATank;
UCLASS()
class TANKBATTLE_API ATankAIController : public AAIController
{
	GENERATED_BODY()
protected:
    virtual void BeginPlay() override;
public:
    virtual void Tick(float DeltaTime) override;
private:
    APawn* GetPlayerTank();
    UPROPERTY(EditDefaultsOnly,Category = "Movement")
    float AcceptanceRadius = 3000.f;
};
