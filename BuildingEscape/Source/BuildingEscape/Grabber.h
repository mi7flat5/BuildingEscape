// Copyright Shane Harmon 2016

#pragma once

#include "Components/ActorComponent.h"
#include "Grabber.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BUILDINGESCAPE_API UGrabber : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UGrabber();

	// Called when the game starts
	virtual void BeginPlay() override;


	// Called every frame
	virtual void TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction ) override;
private:
	 
	void setupComponents();

	UPROPERTY(EditAnywhere)
		float reach = 200.0f;
		
	UPhysicsHandleComponent* physicsHandle = nullptr;
	UInputComponent* Controls;

	//Ray cast adn grab physics objects within reach
	void Grab();
	void Release();
	FHitResult GetLineHit();
	
	FVector GetLineTraceEnd();
	
	
};
