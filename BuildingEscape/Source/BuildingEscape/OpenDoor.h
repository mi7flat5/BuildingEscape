// Copyright Shane Harmon 2016

#pragma once

#include "Components/ActorComponent.h"
#include "OpenDoor.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BUILDINGESCAPE_API UOpenDoor : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UOpenDoor();

	// Called when the game starts
	virtual void BeginPlay() override;

	void OpenDoor();
	void CloseDoor();
	// Called every frame
	virtual void TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction ) override;
private: 

	UPROPERTY(EditAnywhere)
	float openAngle = -90.0f;

	UPROPERTY(EditAnywhere)
	float doorCloseDelay = 1.0f;
	
	float lastDoorOpenTime;


	UPROPERTY(EditAnywhere)
	ATriggerVolume* pressurePlate;

	UPROPERTY(VisibleAnywhere)
	AActor* actorThatOpens;

	AActor* owner;
	
};
