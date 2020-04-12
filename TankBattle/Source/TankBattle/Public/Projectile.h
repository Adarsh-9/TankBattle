// Copyright : Adarsh.S 2020

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Projectile.generated.h"
//Forward Declarations
class UProjectileMovementComponent;
class UParticleSystemComponent;
class URadialForceComponent;
UCLASS()
class TANKBATTLE_API AProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AProjectile();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	UPROPERTY(BlueprintReadOnly, Category = "Projectile")
		UParticleSystemComponent* ImpactBlast;
	UFUNCTION(BlueprintImplementableEvent)
		void OnProjectileHitEvent();
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	void LaunchProjectile(float Speed);
private:
	UProjectileMovementComponent* ProjectileMovement = nullptr;
	UPROPERTY(VisibleAnywhere, Category = "Projectile")
		UParticleSystemComponent* LaunchBlast;
	UPROPERTY(VisibleAnywhere, Category = "Projectile")
		UStaticMeshComponent* CollisionMesh;
	UPROPERTY(VisibleAnywhere, Category = "Projectile")
		URadialForceComponent* RadialForce;
	UFUNCTION()
		void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);
	void OnTimerExpire();
	UPROPERTY(EditDefaultsOnly, Category = "Firing")
		float DestroyTimer = 5.f;
	UPROPERTY(EditDefaultsOnly, Category = "Firing")
		float DamageAmount = 10.f;
};