// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "Barrel.generated.h"

/**
 * 
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class TANKBATTLE_API UBarrel : public UStaticMeshComponent
{
	GENERATED_BODY()
private:
    UPROPERTY(EditAnywhere, Category = "Setup")
        float MinElevationAngle = 0.f;
    UPROPERTY(EditAnywhere, Category = "Setup")
        float MaxElevationAngle = 40.f;
    UPROPERTY(EditAnywhere, Category = "Setup")
        float MaxElevationSpeed = 5.f;
public:
    void Elevate(float RelativeSpeed);
};
