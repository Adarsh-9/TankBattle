// Copyright : Adarsh.S 2020

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "AutoTurret.generated.h"

UCLASS()
class TANKBATTLE_API AAutoTurret : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AAutoTurret();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	UFUNCTION()
	virtual float TakeDamage(
		float DamageAmount,
		struct FDamageEvent const& DamageEvent,
		class AController* EventInstigator,
		AActor* DamageCauser
	) override;
	void DestroyTurret();
	UFUNCTION(BlueprintPure)
		float GetHealthPercentage() const;
protected:
	UFUNCTION(BlueprintImplementableEvent, Category = "Setup")
		void OnTurretDestroyedEvent();
private:
	UPROPERTY(EditDefaultsOnly, Category = "Health")
		int32 MaxHealth = 50;
	UPROPERTY(EditDefaultsOnly, Category = "Destruction")
		float DestroyDelay = 1.f;
	UPROPERTY(VisibleAnywhere, Category = "Health")
		int32 CurrentHealth;

};
