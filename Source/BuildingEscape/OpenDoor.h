// Copyright by Spartanranger

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Engine/TriggerVolume.h"
#include "OpenDoor.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BUILDINGESCAPE_API UOpenDoor : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UOpenDoor();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	void OpenDoor(float DeltaTime);
	void CloseDoor(float DeltaTime);
	float TotalMassOfActors() const;
	void SetupAudioComponent();

private:

	float TargetYaw;
	float InitialYaw;
	float CurrentYaw;

	float DoorOpenedAt = 0.f;
	float DoorCloseDelay = 0.75f;

	bool OpenDoorSound = false;
	bool CloseDoorSound = true;

	float Abc = 25.f;

	UPROPERTY()
		UAudioComponent* AudioComponent = nullptr;
	UPROPERTY(EditAnywhere)
		float Speed;
	UPROPERTY(EditAnywhere)
		ATriggerVolume* PressurePlate = nullptr;
	UPROPERTY(EditAnywhere)
		AActor* ActorThatOpens = nullptr;
	UPROPERTY(EditAnywhere)
		float TargetMass = 50.f;
};
