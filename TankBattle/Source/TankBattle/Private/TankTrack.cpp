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
	DriveTrack(CurrentThrottle);
	float Deltatime = GetWorld()->GetDeltaSeconds();
	ApplySidewaysFriction(Deltatime);
	CurrentThrottle = 0;
}

void UTankTrack::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
}

void UTankTrack::SetThrottle(float ThrottleValue)
{
	CurrentThrottle = FMath::Clamp<float>(CurrentThrottle + ThrottleValue,-1,1);
}

//Apply Throttle to Tank
void UTankTrack::DriveTrack(float ThrottleValue)
{
	FVector ForceApplied = GetForwardVector() * MaxThrottleForce * ThrottleValue;
	auto ForceLocation = GetComponentLocation();
	TankRoot->AddForceAtLocation(ForceApplied, ForceLocation, NAME_None);
}

//Programmatic Side ways Friction
void UTankTrack::ApplySidewaysFriction(float DeltaTime)
{
	SlippageSpeed = FVector::DotProduct(GetRightVector(), GetComponentVelocity());
	CorrectionAcceleration = (-SlippageSpeed / DeltaTime) * GetRightVector();
	CorrectionForce = (TankRoot->GetMass() * CorrectionAcceleration)/3;
	TankRoot->AddForce(CorrectionForce);
}
