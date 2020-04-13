// Copyright : Adarsh.S 2020

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TankTrack.generated.h"

/**
 * 
 */
UCLASS(ClassGroup = (Custom),meta = (BlueprintSpawnableComponent))
class TANKBATTLE_API UTankTrack : public UStaticMeshComponent
{
	GENERATED_BODY()
public:
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	UFUNCTION(BlueprintCallable,Category = "Input")
	void SetThrottle(float ThrottleValue);
	void DriveTrack(float ThrottleValue);
	UPROPERTY(EditDefaultsOnly, Category = "Throttle")
	float MaxThrottleForce = 48000000;
protected:
	virtual void BeginPlay() override;
private:
	UStaticMeshComponent* TankRoot;
	float SlippageSpeed;
	FVector CorrectionAcceleration;
	FVector CorrectionForce;
	float CurrentThrottle;
	void ApplySidewaysFriction(float DeltaTime);
	UFUNCTION()
		void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);
};
