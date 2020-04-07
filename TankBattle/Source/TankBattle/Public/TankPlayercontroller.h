//Copyright : Adarsh.S 2020

#pragma once

#include "CoreMinimal.h"
#include "TankPlayercontroller.generated.h"

//Forward Declarations
class ATank;
class UTankAimingComponent;
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

protected:
	UFUNCTION(BlueprintCallable)
	ATank* GetControlledTank() const;
	UFUNCTION(BlueprintImplementableEvent, Category = "Setup")
	void FoundAimingcomponent(UTankAimingComponent* AimingComponent);
public:
	void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
};
