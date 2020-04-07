// Copyright : Adarsh.S 2020

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "Turret.generated.h"

/**
 * 
 */
UCLASS(ClassGroup = (Custom),meta = (BlueprintSpawnableComponent))
class TANKBATTLE_API UTurret : public UStaticMeshComponent
{
	GENERATED_BODY()
public:
    void RotateTurret(float RelativeSpeed);
private:
    UPROPERTY(EditAnywhere, Category = "Setup")
    float MaxRotationRate = 20.f;
};
