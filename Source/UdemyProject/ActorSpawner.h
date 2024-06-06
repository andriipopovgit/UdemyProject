// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TestLog.h"
#include "ActorSpawner.generated.h"

UCLASS()
class UDEMYPROJECT_API AActorSpawner : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AActorSpawner();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	void OnColorChanged(FLinearColor Color, const FString& Name);

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<ATestLog> ObjectToSpawn;

	FTimerHandle tHandle;

	void DisplayColors();

	int32 r;
	int32 g;
	int32 b;
};
