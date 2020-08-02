// Copyright SworldsGame 2020


#include "OpenDoor.h"
#include "GameFramework/Actor.h"

// Sets default values for this component's properties
UOpenDoor::UOpenDoor()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UOpenDoor::BeginPlay()
{
	Super::BeginPlay();
	
	
}


// Called every frame
void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	float CurrentYaw = GetOwner()->GetActorRotation().Yaw;
	FRotator OpenDoor {0.f, TargetYaw, 0.f};
	//OpenDoor.Yaw = FMath::Lerp(CurrentYaw, TargetYaw, 0.05f);
	//OpenDoor.Yaw = FMath::FInterpConstantTo(CurrentYaw, TargetYaw, DeltaTime, 45);
	OpenDoor.Yaw = FMath::FInterpTo(CurrentYaw, TargetYaw, DeltaTime, 2);
	GetOwner()->SetActorRotation(OpenDoor);
}

// FRotator CurrentRotation = GetOwner()->GetActorRotation();
	// CurrentRotation.Yaw = 90.f;
	//GetOwner()->SetActorRotation(CurrentRotation);

	// FRotator OpenDoor {0.f, 90.f, 0.f};

	// GetOwner()->SetActorRotation(OpenDoor);