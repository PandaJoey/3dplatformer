// Fill out your copyright notice in the Description page of Project Settings.

#include "Grabber.h"
#include "DrawDebugHelpers.h"
#include "Engine/World.h"
#include "GameFramework/PlayerController.h"
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

	UE_LOG(LogTemp, Warning, TEXT("Grabber Checking In!"));
 
	FindPhysicsHandle();
	SetUpInputComponent();
}


// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);	

	if(!PhysicsHandle) {return;}
	if(PhysicsHandle->GrabbedComponent)
	{
		PhysicsHandle->SetTargetLocation(GetReach());
	}
}


void UGrabber::	SetUpInputComponent()
{
	InputComponent = GetOwner()->FindComponentByClass<UInputComponent>();

	if(InputComponent)
	{
		UE_LOG(LogTemp, Warning, TEXT("Found Input Component on %s"), *GetOwner()->GetName());
		InputComponent->BindAction("Grab", IE_Pressed, this, &UGrabber::Grab);
		InputComponent->BindAction("Grab", IE_Released, this, &UGrabber::Release);
	}

}

void UGrabber::FindPhysicsHandle() 
{
		// Checking  for physics handle component
	PhysicsHandle = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
	
	if(!PhysicsHandle)
	{
		UE_LOG(LogTemp, Error, TEXT("No Physics handle component found on %s"), *GetOwner()->GetName());
	}
}

void UGrabber::Grab()
{
	FHitResult HitResult = GetFirstPhysicsBodyInReach();

	UPrimitiveComponent* ComponentToGrab = HitResult.GetComponent();

	AActor* ActorHit = HitResult.GetActor();

	if(ActorHit)
	{
		if(!PhysicsHandle) {return;}
		PhysicsHandle->GrabComponentAtLocation(ComponentToGrab, NAME_None, GetReach());
	}

	
}

void UGrabber::Release()
{
	if(!PhysicsHandle) {return;}
	PhysicsHandle->ReleaseComponent();
}


FHitResult UGrabber::GetFirstPhysicsBodyInReach() const
{

	//ray-cast out to a certain distance (Reach)
	FHitResult HitDetected;
	FCollisionQueryParams TraceParams(FName(TEXT("")), false, GetOwner());
	GetWorld()->LineTraceSingleByObjectType(OUT HitDetected, GetPlayerWorldPos(), GetReach(), 
		FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody), TraceParams 
	);

	return HitDetected;
}

FVector UGrabber::GetReach() const 
{
		//get player viewpoint
	FVector PlayerViewPointLocation;
	FRotator PlayerViewPointRotation;
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(
		OUT PlayerViewPointLocation, 
		OUT PlayerViewPointRotation
	);

	return PlayerViewPointLocation + PlayerViewPointRotation.Vector() * Reach; 
	
}

FVector UGrabber::GetPlayerWorldPos() const
{
	FVector PlayerViewPointLocation;
	FRotator PlayerViewPointRotation;
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(
		OUT PlayerViewPointLocation, 
		OUT PlayerViewPointRotation
	);
	return PlayerViewPointLocation;
}
