// Copyright by Spartanranger
#include "Components/AudioComponent.h"
#include "Components/PrimitiveComponent.h"
#include "OpenDoor.h"

#define OUT

// Sets default values for this component's properties
UOpenDoor::UOpenDoor()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}


// Called when the game starts
void UOpenDoor::BeginPlay()
{
	Super::BeginPlay();

	ActorThatOpens = GetWorld()->GetFirstPlayerController()->GetPawn();

	InitialYaw = GetOwner()->GetActorRotation().Yaw;
	CurrentYaw = InitialYaw;
	TargetYaw = InitialYaw + 90.f;
	UE_LOG(LogTemp,Warning,TEXT("ABC is: %f"),Abc);

	if(!PressurePlate)
	{
		UE_LOG(LogTemp, Error, TEXT("%s has null pointer!"),*GetOwner()->GetName());
	}

	SetupAudioComponent();
}


// Called every frame
void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if(TotalMassOfActors() > TargetMass)
	{
		OpenDoor(DeltaTime);
		DoorOpenedAt = GetWorld()->GetTimeSeconds();
	}
	else
	{	
		if(GetWorld()->GetTimeSeconds() - DoorOpenedAt > DoorCloseDelay)
		{
			CloseDoor(DeltaTime);
		}	
	}

	// UE_LOG(LogTemp, Warning, TEXT("%s"),*GetOwner()->GetActorRotation().ToString());
	// UE_LOG(LogTemp, Warning, TEXT("Yaw is: %f"),GetOwner()->GetActorRotation().Yaw);

	// float CurrentYaw = GetOwner()->GetActorRotation().Yaw;
	// FRotator OpenDoor(0.f,TargetYaw,0.f);
	// OpenDoor.Yaw = FMath::Lerp(CurrentYaw,TargetYaw,0.01f);
	// GetOwner()->SetActorRotation(OpenDoor);

	
}
void UOpenDoor::OpenDoor(float DeltaTime)
{

	CurrentYaw = FMath::Lerp(CurrentYaw, TargetYaw, DeltaTime * Speed);

	FRotator DoorRotation = GetOwner()->GetActorRotation();
	DoorRotation.Yaw = CurrentYaw;
	GetOwner()->SetActorRotation(DoorRotation);

	CloseDoorSound = false;
	if(!OpenDoorSound)
	{
		AudioComponent->Play();
		OpenDoorSound = true;
	}
	

}
void UOpenDoor::CloseDoor(float DeltaTime)
{

	CurrentYaw = FMath::Lerp(CurrentYaw, InitialYaw, DeltaTime * Speed);

	FRotator DoorRotation = GetOwner()->GetActorRotation();
	DoorRotation.Yaw = CurrentYaw;
	GetOwner()->SetActorRotation(DoorRotation);

	OpenDoorSound = false;
	if(!CloseDoorSound)
	{
		AudioComponent->Play();
		CloseDoorSound = true;
	}
}

float UOpenDoor::TotalMassOfActors() const
{
	float TotalMass = 0.f;

	TArray<AActor*> OverlappingActors;
	PressurePlate->GetOverlappingActors(OUT OverlappingActors);

	for(AActor* Actor : OverlappingActors)
	{
		TotalMass += Actor->FindComponentByClass<UPrimitiveComponent>()->GetMass();
	}

	return TotalMass;
}

void UOpenDoor::SetupAudioComponent()
{
	AudioComponent = GetOwner()->FindComponentByClass<UAudioComponent>();
	if(!AudioComponent)
	{
		return;
	}
	
}

