// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BenchmarkFPS.generated.h"

UCLASS()
class ANITOSCAN_MODEL_API ABenchmarkFPS : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABenchmarkFPS();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	float warmupDuration = 5.0f;
	float benchmarkDuration = 10.0f;
	float elapsedTime = 0.0f;
	int32 frameCount = 0;

	bool warmupComplete = false;
	bool benchmarkFinished = false;

};
