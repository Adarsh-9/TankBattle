// Copyright : Adarsh.S 2020


#include "TankTrack.h"
#include "SprungWheel.h"
#include "SpawnPoint.h"
void UTankTrack::BeginPlay()
{
	Super::BeginPlay();
}

void UTankTrack::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
}

void UTankTrack::SetThrottle(float ThrottleValue)
{
	float CurrentThrottle = FMath::Clamp<float>(ThrottleValue,-1,1);
	DriveTrack(CurrentThrottle);
}

//Apply Throttle to Tank
void UTankTrack::DriveTrack(float CurrentThrottle)
{
	auto ForceApplied = MaxThrottleForce * CurrentThrottle;
	auto Wheels = GetWheels();
	auto ForcePerWheel = ForceApplied / Wheels.Num();
	for (auto Wheel : Wheels)
	{
		Wheel->ApplyDrivingForce(ForcePerWheel);
	}
}

TArray<ASprungWheel*> UTankTrack::GetWheels() const
{
	TArray<ASprungWheel*> ResultArray;
	TArray<USceneComponent*> Children;
	GetChildrenComponents(true, Children);
	for (USceneComponent* Child : Children)
	{
		auto SpawnPoint = Cast<USpawnPoint>(Child);
		if (!SpawnPoint) continue;
		AActor* SpawnedChild = SpawnPoint->GetSpawnedActor();
		auto SprungWheel = Cast<ASprungWheel>(SpawnedChild);
		if (!SprungWheel) continue;
		ResultArray.Add(SprungWheel);
	}
	return ResultArray;
}

