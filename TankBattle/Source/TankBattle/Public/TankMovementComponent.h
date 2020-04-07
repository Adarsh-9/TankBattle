// Copyright : Adarsh.S 2020

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/NavMovementComponent.h"
#include "TankMovementComponent.generated.h"

class UTankTrack;
/**
 * 
 */
UCLASS(ClassGroup = (Custom),meta = (BlueprintSpawnableComponent))
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
    UFUNCTION(BlueprintCallable, Category = "SetUp")
    void Initialise(UTankTrack* LefTrackToSet,UTankTrack* RightTrackToSet);
private:
    UTankTrack* LeftTrack = nullptr;
    UTankTrack* RightTrack = nullptr;
    void RequestDirectMove(const FVector& MoveVelocity, bool bForceMaxSpeed) override;
};
