// Fill out your copyright notice in the Description page of Project Settings.


#include "ActorSpawner.h"

DEFINE_LOG_CATEGORY_STATIC(LogActorSpawner, All, All);

// Sets default values
AActorSpawner::AActorSpawner()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AActorSpawner::BeginPlay()
{
	Super::BeginPlay();

	GetWorldTimerManager().SetTimer(tHandle, this, &AActorSpawner::DisplayColors, 5.0f, true);

	if (GetWorld() && ObjectToSpawn)
	{
		for (int i = 0; i < 5; i++)
		{
			FTransform transform(FRotator::ZeroRotator, FVector{ 0.0f, 0.0f, 200.0f * i });
			auto obj = GetWorld()->SpawnActorDeferred<ATestLog>(ObjectToSpawn, transform);
			if (obj && obj->Mesh)
				obj->Mesh->CreateAndSetMaterialInstanceDynamic(0)->SetVectorParameterValue("Base Color", FLinearColor::MakeRandomColor());
			obj->OnColorChanged.AddDynamic(this, &AActorSpawner::OnColorChanged);
			UE_LOG(LogActorSpawner, Error, TEXT("Actor spawned: %s"), *obj->GetName());
			obj->FinishSpawning(transform);
		}
	}
}

// Called every frame
void AActorSpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AActorSpawner::OnColorChanged(FLinearColor Color, const FString& Name)
{
	UE_LOG(LogActorSpawner, Warning, TEXT("%s - %s"), *Color.ToString(), *Name);

	if (Color == FLinearColor::Red) r++;
	if (Color == FLinearColor::Green) g++;
	if (Color == FLinearColor::Blue) b++;

}

void AActorSpawner::DisplayColors()
{
	UE_LOG(LogActorSpawner, Warning, TEXT("r = %d, g = %d, b = %d"), r, g, b);
}

