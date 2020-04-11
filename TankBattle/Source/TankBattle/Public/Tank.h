// Copyright : Adarsh.S 2020

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Tank.generated.h"

//Forward Declarations

UCLASS()
class TANKBATTLE_API ATank : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ATank();
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	//called by engine when there is damage to apply
	UFUNCTION()
	virtual float TakeDamage
	(
		float DamageAmount,
		struct FDamageEvent const& DamageEvent,
		class AController* EventInstigator,
		AActor* DamageCauser
	) override;
	UFUNCTION(BlueprintPure)
	float GetHealthPercentage() const;
private:
	UPROPERTY(EditDefaultsOnly, Category = "Health")
		int32 MaxHealth = 100;
	UPROPERTY(EditDefaultsOnly, Category = "Health")
		int32 CurrentHealth;
};
