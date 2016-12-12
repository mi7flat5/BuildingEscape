// Copyright Shane Harmon 2016

#include "BuildingEscape.h"
#include "OpenDoor.h"


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
	
	owner = GetOwner();
	
	
}




// Called every frame
void UOpenDoor::TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction )
{
	Super::TickComponent( DeltaTime, TickType, ThisTickFunction );
	if (!pressurePlate)
	{
		UE_LOG(LogTemp, Error, TEXT("TriggerVolume not assigned to %s"), *owner->GetName())
		return;
	}
	if (GetTotlMassOnPlate()>triggerMass)
	{
		OpenDoor();
		lastDoorOpenTime = GetWorld()->GetTimeSeconds();
	}
	
	if (GetWorld()->GetTimeSeconds() - lastDoorOpenTime > doorCloseDelay) 
	{
		CloseDoor();
	}
	// ...
}
void UOpenDoor::OpenDoor()
{
	owner->SetActorRotation(FRotator(0.0f, openAngle, 0.0f));
}
void UOpenDoor::CloseDoor()
{
	owner->SetActorRotation(FRotator(0.0f, 0, 0.0f));
}
float UOpenDoor::GetTotlMassOnPlate()
{

	float massOnPlate = 0.0f;
	
	TArray<AActor*> overLappingActors;
	pressurePlate->GetOverlappingActors(overLappingActors);

	for (const auto& actor : overLappingActors)
	{
		massOnPlate += actor->FindComponentByClass<UPrimitiveComponent>()->GetMass();
		 
	}

	return massOnPlate;
}