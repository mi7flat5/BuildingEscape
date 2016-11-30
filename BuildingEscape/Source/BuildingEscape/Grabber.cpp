// Copyright Shane Harmon 2016
#define OUT
#include "BuildingEscape.h"
#include "Grabber.h"


// Sets default values for this component's properties
UGrabber::UGrabber()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UGrabber::BeginPlay()
{
	Super::BeginPlay();
	UE_LOG(LogTemp, Warning, TEXT("Grabber reporting for duty"))
	// ...
	
}


// Called every frame
void UGrabber::TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction )
{
	Super::TickComponent( DeltaTime, TickType, ThisTickFunction );
	FVector position;
	FRotator rotation;

	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(
		OUT position,
		OUT rotation);

	/*UE_LOG(LogTemp, 
		Warning,
		TEXT("Player Position %s Rotation %s"),
		*position.ToString(),
		*rotation.ToString()
		)*/
	
	FVector lineTrace = position + (rotation.Vector() *reach);

	DrawDebugLine(GetWorld(),position,lineTrace,FColor(255,0,0),false,0.0f,0.0f,12.0f);
}

