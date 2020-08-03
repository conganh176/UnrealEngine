// Copyright SworldsGame 2020

#include "Grabber.h"
#include "GameFramework/PlayerController.h"
#include "Engine/World.h"
//#include "DrawDebugHelpers.h"

#define OUT

// Sets default values for this component's properties
UGrabber::UGrabber()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}

// Called when the game starts
void UGrabber::BeginPlay()
{
	Super::BeginPlay();

	//Check PhysicsHandleComponent
	FindPhysicsHandle();

	//Check input component
	SetupInputComponent();
}

void UGrabber::FindPhysicsHandle() {
	PhysicsHandle = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();

	if (PhysicsHandle == nullptr) {
		UE_LOG(LogTemp, Error, TEXT("No UPhysicsHandleComponent found on %s."), *GetOwner()->GetName());
	}
}

void UGrabber::SetupInputComponent() {
	InputComponent = GetOwner()->FindComponentByClass<UInputComponent>();
	if (InputComponent == nullptr) {
		UE_LOG(LogTemp, Error, TEXT("No UInputComponent found on %s."), *GetOwner()->GetName());
	}
	else {
		InputComponent->BindAction("Grab", IE_Pressed, this, &UGrabber::Grab);
		InputComponent->BindAction("Grab", IE_Released, this, &UGrabber::Release);
	}
}

void UGrabber::Grab() {
	//UE_LOG(LogTemp, Warning, TEXT("Pressed"));

	FHitResult HitResult = GetFirstPhysicsBodyInReach();
	UPrimitiveComponent* ComponentToGrab = HitResult.GetComponent();
	AActor* ActorHit = HitResult.GetActor();

	if (ActorHit) {
		if (!PhysicsHandle) { return; }

		PhysicsHandle->GrabComponentAtLocation(
			ComponentToGrab,
			NAME_None,
			GetPlayersReach()
		);
	}
}

void UGrabber::Release() {
	//UE_LOG(LogTemp, Warning, TEXT("Release"));
	if (!PhysicsHandle) { return; }

	PhysicsHandle->ReleaseComponent();
}

// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	//if PhysicsHandle is attached
	if (!PhysicsHandle) { return; }

	if (PhysicsHandle->GrabbedComponent) {
		//Move the object that are holding
		PhysicsHandle->SetTargetLocation(GetPlayersReach());
	}
}

FHitResult UGrabber::GetFirstPhysicsBodyInReach() const {
	//UE_LOG(LogTemp, Warning, TEXT("Location: %s\nRotation: %s"), *PlayerViewPointLocation.ToString(), *PlayerViewPointRotation.ToString());

	//Draw a line from player showing the reach
	/*DrawDebugLine(
		GetWorld(),
		PlayerViewPointLocation,
		LineTraceEnd,
		FColor{0, 255, 0},
		false,
		0.f, 0, 5.f
	);*/

	//raycast out to certain distance (Reach)
	FHitResult Hit;
	FCollisionQueryParams TraceParams{ FName(TEXT("")), false, GetOwner() };

	GetWorld()->LineTraceSingleByObjectType(
		OUT Hit,
		GetPlayersWorldPos(),
		GetPlayersReach(),
		FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody),
		TraceParams
	);
	////See what hits
	//AActor* ActorHit = Hit.GetActor();

	//if (ActorHit) {
	//	UE_LOG(LogTemp, Warning, TEXT("Line trace has hit: %s"), *ActorHit->GetName());
	//}

	return Hit;
}

FVector UGrabber::GetPlayersWorldPos() const {
	//Get player viewpoint
	FVector PlayerViewPointLocation;
	FRotator PlayerViewPointRotation;

	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(OUT PlayerViewPointLocation, OUT PlayerViewPointRotation);
	
	return PlayerViewPointLocation;
}

FVector UGrabber::GetPlayersReach() const {
	FVector PlayerViewPointLocation;
	FRotator PlayerViewPointRotation;

	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(OUT PlayerViewPointLocation, OUT PlayerViewPointRotation);

	return PlayerViewPointLocation + PlayerViewPointRotation.Vector() * Reach;
}