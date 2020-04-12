// Copyright : Adarsh.S 2020


#include "AutoTurret.h"
#include "Engine/World.h"
#include "TimerManager.h"

// Sets default values
AAutoTurret::AAutoTurret()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AAutoTurret::BeginPlay()
{
	Super::BeginPlay();
	CurrentHealth = MaxHealth;
}

// Called every frame
void AAutoTurret::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AAutoTurret::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

float AAutoTurret::TakeDamage(float DamageAmount,struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser)
{
	int32 DamageValue = FPlatformMath::RoundToInt(DamageAmount);
	int32 DamageToApply = FMath::Clamp(DamageValue,0,CurrentHealth);
	CurrentHealth -= DamageValue;
	if (CurrentHealth <= 0)
	{
		OnTurretDestroyedEvent();
		FTimerHandle TimerHandle;
		GetWorld()->GetTimerManager().SetTimer(TimerHandle,this,&AAutoTurret::DestroyTurret,DestroyDelay,false);
	}
	return DamageAmount;
}
void AAutoTurret::DestroyTurret()
{
	Destroy();
}
float AAutoTurret::GetHealthPercentage() const
{
	auto HP = (float)CurrentHealth / (float)MaxHealth;
	return HP;
}

