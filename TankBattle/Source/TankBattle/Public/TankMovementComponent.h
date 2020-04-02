// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/NavMovementComponent.h"
#include "TankMovementComponent.generated.h"

class UTankTrack;
/**
 * 
 */
UCLASS()
class TANKBATTLE_API UTankMovementComponent : public UNavMovementComponent
{
	GENERATED_BODY()
public:
    UFUNCTION(BlueprintCallable,Category = "Controls")
    void HandleForwardMovement(float AxisValue);
    UFUNCTION(BlueprintCallable, Category = "Controls")
    void HandleTurnRight(float AxisValue);
    UFUNCTION(BlueprintCallable, Category = "Controls")
    void HandleTurnLeft(float AxisValue);
    void SetTracks(UTankTrack* LefTrackToSet,UTankTrack* RightTrackToSet);
private:
    UTankTrack* LeftTrack = nullptr;
    UTankTrack* RightTrack = nullptr;
};
