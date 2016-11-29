// Copyright Shane Harmon 2016

#include "BuildingEscape.h"
#include "PositionReport.h"


// Sets default values for this component's properties
UPositionReport::UPositionReport()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UPositionReport::BeginPlay()
{
	Super::BeginPlay();
	FString ownerName = GetOwner()->GetName();
	FTransform transform = GetOwner()->GetTransform();
	FVector position = transform.GetLocation();
	FString objectPos = "X = " + FString::SanitizeFloat(position.X) + " Y = " + FString::SanitizeFloat(position.Y) + " Z = " + FString::SanitizeFloat(position.Z);
	UE_LOG(LogTemp, Warning, TEXT("Position report reporting for duty on: %s %s"), *ownerName, *objectPos)
	// ...
	
}


// Called every frame
void UPositionReport::TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction )
{
	Super::TickComponent( DeltaTime, TickType, ThisTickFunction );

	// ...
}

