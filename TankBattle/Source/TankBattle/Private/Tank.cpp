// Copyright : Adarsh.S 2020
#include "../Public/Tank.h"
#include "Components/InputComponent.h"
// Sets default values
ATank::ATank()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ATank::BeginPlay()
{
	Super::BeginPlay();
	CurrentHealth = MaxHealth;
}



// Called every frame
void ATank::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void ATank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

float ATank::TakeDamage(float DamageAmount,struct FDamageEvent const& DamageEvent,class AController* EventInstigator, AActor* DamageCauser)
{
	int32 DamageValue = FPlatformMath::RoundToInt(DamageAmount);
	int32 DamageToApply = FMath::Clamp<float>(DamageValue,0,CurrentHealth);
	CurrentHealth -= DamageValue;
	OnDamageTakenEvent();
	if (CurrentHealth <= 0)
	{
		TankDead.Broadcast();
	}
	return DamageToApply;
}

float ATank::GetHealthPercentage() const
{
	float HP = (float)CurrentHealth / (float)MaxHealth;
	return HP;
}





