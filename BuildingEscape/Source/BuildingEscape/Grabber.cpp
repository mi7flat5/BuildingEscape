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
	setupComponents();

	
}
void UGrabber::Grab() 
{
	UE_LOG(LogTemp, Error, TEXT("Grabber pressed"))
	FVector position;
	FRotator rotation;

	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(
		OUT position,
		OUT rotation);



	

	FCollisionQueryParams traceparams = FCollisionQueryParams(FName(TEXT("")), false, GetOwner());

	DrawDebugLine(GetWorld(), position, GetLineTraceEnd(), FColor(255, 0, 0), false, 0.0f, 0.0f, 12.0f);
	FHitResult hit;
	GetWorld()->LineTraceSingleByObjectType(OUT hit, position, GetLineTraceEnd(), FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody), traceparams);
	if (hit.GetActor())
		UE_LOG(LogTemp, Warning, TEXT("Hitting %s"), *hit.GetActor()->GetName())
		if (hit.GetActor()) {
			auto ComponenToGrab = hit.GetComponent();
			physicsHandle->GrabComponent(ComponenToGrab, NAME_None, ComponenToGrab->GetOwner()->GetActorLocation(), true);
			
		}
}
void UGrabber::Release() 
{	
	
		physicsHandle->ReleaseComponent();
		UE_LOG(LogTemp, Error, TEXT("Grabber released"))
	
}
FVector UGrabber::GetLineTraceEnd()
{
	FVector position;
	FRotator rotation;

	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(
		OUT position,
		OUT rotation);
	
	return position + (rotation.Vector() *reach);

}
// Called every frame
void UGrabber::TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction )
{
	Super::TickComponent( DeltaTime, TickType, ThisTickFunction );

	

	if(physicsHandle->GrabbedComponent)
	{
		
		physicsHandle->SetTargetLocation(GetLineTraceEnd());
	}
}

void UGrabber::setupComponents()
{
	physicsHandle = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
	// ...
	
	if (physicsHandle)
	{

	}
	else UE_LOG(LogTemp, Error, TEXT("Physics compnent of %s not found"), *GetOwner()->GetName())

		Controls = GetOwner()->FindComponentByClass<UInputComponent>();
	if (Controls)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s's input component found"), *GetOwner()->GetName())
			//Bind input actions
			Controls->BindAction("Grab", IE_Pressed, this, &UGrabber::Grab);
		Controls->BindAction("Grab", IE_Released, this, &UGrabber::Release);
	}
	else UE_LOG(LogTemp, Error, TEXT("Input component of %s not found"), *GetOwner()->GetName())

}

