// Fill out your copyright notice in the Description page of Project Settings.


#include "TestLog.h"
#include "TimerManager.h"

// Sets default values
ATestLog::ATestLog()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	SetRootComponent(Mesh);
}

// Called when the game starts or when spawned
void ATestLog::BeginPlay()
{
	Super::BeginPlay();

	if (Mesh)
	{
		Mesh->SetMaterial(0, Material);
	}

	GetWorldTimerManager().SetTimer(timerHandle, this, &ATestLog::SetRandomMaterilBaseColor, ColorChangeInterval, true);
}

// Called every frame
void ATestLog::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ATestLog::SetRandomMaterilBaseColor()
{
	if (MaxColorChanging < 0 || currColorChanging < MaxColorChanging)
	{
		UMaterialInstanceDynamic* dynMaterial = Mesh->CreateAndSetMaterialInstanceDynamic(0);
		if (dynMaterial)
		{
			//FLinearColor color = FLinearColor::MakeRandomColor();
			FLinearColor color;
			float rnd = FMath::FRand() * 100;
			if (rnd < 33)
				color = FLinearColor::Red;
			else if (rnd < 67)
				color = FLinearColor::Green;
			else
				color = FLinearColor::Blue;
			dynMaterial->SetVectorParameterValue("Base Color", color);
			OnColorChanged.Broadcast(color, GetName());
		}
	}
	else
	{
		GetWorldTimerManager().ClearTimer(timerHandle);
	}
}