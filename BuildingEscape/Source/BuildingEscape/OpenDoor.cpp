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
	
	if (!pressurePlate)
	{
		UE_LOG(LogTemp, Error, TEXT("TriggerVolume not assigned to %s"), *owner->GetName())
	}
	
}




// Called every frame
void UOpenDoor::TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction )
{
	Super::TickComponent( DeltaTime, TickType, ThisTickFunction );
	
	if (!pressurePlate)
		return;

	if (GetTotlMassOnPlate()>triggerMass)
	{
		onOpen.Broadcast();
		
	}
	else onClose.Broadcast();
	
	// ...
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