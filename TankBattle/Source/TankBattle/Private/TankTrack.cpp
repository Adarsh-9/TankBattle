// Copyright : Adarsh.S 2020


#include "TankTrack.h"
void UTankTrack::BeginPlay()
{
	Super::BeginPlay();
	// ...
	TankRoot = Cast<UStaticMeshComponent>(GetOwner()->GetRootComponent());
	OnComponentHit.AddDynamic(this,&UTankTrack::OnHit);
}
void UTankTrack::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	
}

void UTankTrack::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	//Programmatic Side ways Friction
	/*SlippageSpeed = FVector::DotProduct(GetRightVector(), GetComponentVelocity());
	CorrectionAcceleration = -SlippageSpeed / DeltaTime * GetRightVector();
	CorrectionForce = (TankRoot->GetMass() * CorrectionAcceleration)/2;
	TankRoot->AddForce(CorrectionForce);*/
}
//Apply Throttle to Tank
void UTankTrack::SetThrottle(float ThrottleValue)
{
	FVector ForceApplied = GetForwardVector() * MaxThrottleForce * ThrottleValue;
	auto ForceLocation = GetComponentLocation();
	TankRoot->AddForceAtLocation(ForceApplied,ForceLocation,NAME_None);
}