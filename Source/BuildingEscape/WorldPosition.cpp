// Fill out your copyright notice in the Description page of Project Settings.


#include "WorldPosition.h"
#include "GameFramework/Actor.h"


// Sets default values for this component's properties
UWorldPosition::UWorldPosition()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UWorldPosition::BeginPlay()
{
	Super::BeginPlay();

	FString Name = GetOwner()->GetName();
	UE_LOG(LogTemp, Warning, TEXT("%s"), *Name);

	FString Position = GetOwner()->GetActorLocation().ToString();
	UE_LOG(LogTemp, Warning, TEXT("%s"), *Position);


	//FVector Position = GetOwner()->GetActorLocation();
	// FString Log = TEXT("Hello!");
	// //& means where address in memeory is 
	// FString* PtrLog = &Log;

	// Log.Len();

	// //dereferenceing is getting the reference
	// (*PtrLog).Len();

	// //use the arrow for indirect operations for pointers.
	// PtrLog->Len();


	// // UE_LOG(LogTemp, Display, TEXT("This is a Standard Log!"));
	// UE_LOG(LogTemp, Warning, TEXT("%s"), *Log);
	// //prints address because its not a string
	// UE_LOG(LogTemp, Warning, TEXT("%s"), *PtrLog);
	// //first star is saying we want to print a string second one dereferences and prints the string.
	// UE_LOG(LogTemp, Warning, TEXT("%s"), **PtrLog);
	// // UE_LOG(LogTemp, Error, TEXT("This is an Error!"));
	

	
}


// Called every frame
void UWorldPosition::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

