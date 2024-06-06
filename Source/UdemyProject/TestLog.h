// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Materials/MaterialInstanceDynamic.h"
#include "TestLog.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnColorChanged, FLinearColor, Color, const FString&, Name);

UCLASS()
class UDEMYPROJECT_API ATestLog : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATestLog();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	UStaticMeshComponent* Mesh;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float ColorChangeInterval = 5.0f;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int32 MaxColorChanging = 5;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	UMaterialInterface* Material;

	UPROPERTY(BlueprintAssignable)
	FOnColorChanged OnColorChanged;

private:
	FTimerHandle timerHandle;

	int currColorChanging = 0;

	void SetRandomMaterilBaseColor();
};
