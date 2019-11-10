// Fill out your copyright notice in the Description page of Project Settings.


#include "MyAwesomeTestActor.h"

// Sets default values
AMyAwesomeTestActor::AMyAwesomeTestActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

void AMyAwesomeTestActor::GetAllStaticMeshesInScene() {
	int32 copyNumberOfElements = maxNumberOfElements;
	if(GEngine)GEngine->ClearOnScreenDebugMessages();
	for (TActorIterator<AStaticMeshActor> ActorItr(GetWorld()); ActorItr; ++ActorItr)
	{
		AStaticMeshActor *Mesh = *ActorItr;
		FVector loc = Mesh->GetActorLocation();
		FString meshName = Mesh->GetFName().ToString();
		if (copyNumberOfElements > 0 && (meshName.Contains(ContainsName.ToString())||ContainsName == NAME_None)) 
		{
			copyNumberOfElements--;
			FString debugMessage = FString::Printf(TEXT("Name: %s Location: %f %f %f"), *meshName, loc.X, loc.Y, loc.Z);
			UE_LOG(LogTemp, Warning, TEXT("%s"), *debugMessage);
			if(GEngine)GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, debugMessage);
		}		
	}
	UE_LOG(LogTemp, Warning, TEXT("--------------------------------------------"));
}

// Called when the game starts or when spawned
void AMyAwesomeTestActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMyAwesomeTestActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

