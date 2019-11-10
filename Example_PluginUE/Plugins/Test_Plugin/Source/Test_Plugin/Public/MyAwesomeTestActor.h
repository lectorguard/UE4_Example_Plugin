// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EngineUtils.h"
#include "Runtime/Engine/Classes/Engine/Engine.h"
#include "Engine/StaticMeshActor.h"
#include "MyAwesomeTestActor.generated.h"

UCLASS()
class TEST_PLUGIN_API AMyAwesomeTestActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMyAwesomeTestActor();
	UPROPERTY(EditAnywhere, Category = "Static Meshes", meta = (ClampMin = "0", ClampMax = "50", UIMin = "0", UIMax = "50"))
	int32 maxNumberOfElements = 4;

	UPROPERTY(EditAnywhere, Category = "Static Meshes")
	FName ContainsName = NAME_None;

	UFUNCTION(BlueprintCallable, Category = "Static Meshes")
	void GetAllStaticMeshesInScene();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
