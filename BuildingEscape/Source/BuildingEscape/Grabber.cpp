// Copyright Shane Harmon 2016
#define OUT
#include "BuildingEscape.h"
#include "Grabber.h"


// Sets default values for this component's properties
UGrabber::UGrabber()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UGrabber::BeginPlay()
{
	Super::BeginPlay();
	setupComponents();
}
void UGrabber::Grab() 
{
	FHitResult hit = GetLineHit();
	
	if (hit.GetActor())
	
	
	if (hit.GetActor()) 
	{
		auto ComponenToGrab = hit.GetComponent();
		if (!physicsHandle)
			return;
		physicsHandle->GrabComponent(ComponenToGrab, NAME_None, ComponenToGrab->GetOwner()->GetActorLocation(), true);
	}
}
void UGrabber::Release()
{
	if (!physicsHandle)
		return;
	physicsHandle->ReleaseComponent();
}
FHitResult UGrabber::GetLineHit()
{
	FVector position;
	FRotator rotation;

	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(
		OUT position,
		OUT rotation);
	
	FHitResult hitResult;
	
	FCollisionQueryParams traceparams = FCollisionQueryParams(FName(TEXT("")), false, GetOwner());
	
	GetWorld()->LineTraceSingleByObjectType(OUT hitResult,
		position, GetLineTraceEnd(), 
		FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody), 
		traceparams
		);
	return hitResult;
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

void UGrabber::TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction )
{
	Super::TickComponent( DeltaTime, TickType, ThisTickFunction );
	if (!physicsHandle) 
		return;

	if(physicsHandle->GrabbedComponent)
	{
		physicsHandle->SetTargetLocation(GetLineTraceEnd());
	}
}

void UGrabber::setupComponents()
{
	physicsHandle = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
		
	if (!physicsHandle)
		UE_LOG(LogTemp, Error, TEXT("Physics compnent of %s not found"), *GetOwner()->GetName())
		
	Controls = GetOwner()->FindComponentByClass<UInputComponent>();

	if (Controls)
	{
		Controls->BindAction("Grab", IE_Pressed, this, &UGrabber::Grab);
		Controls->BindAction("Grab", IE_Released, this, &UGrabber::Release);
	}
	else UE_LOG(LogTemp, Error, TEXT("Input component of %s not found"), *GetOwner()->GetName())

}

