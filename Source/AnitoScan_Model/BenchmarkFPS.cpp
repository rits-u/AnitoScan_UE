// Fill out your copyright notice in the Description page of Project Settings.


#include "BenchmarkFPS.h"
#include "Kismet/KismetSystemLibrary.h"

// Sets default values
ABenchmarkFPS::ABenchmarkFPS()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ABenchmarkFPS::BeginPlay()
{
	Super::BeginPlay();

	if (APlayerController* PC = GetWorld()->GetFirstPlayerController())
	{
		PC->ConsoleCommand(TEXT("r.VSync 0"));
		PC->ConsoleCommand(TEXT("t.MaxFPS 0"));
		PC->ConsoleCommand(TEXT("r.DontLimitOnBattery 1"));
	}
}

// Called every frame
void ABenchmarkFPS::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (benchmarkFinished)
	{
		return;
	}

	if (!warmupComplete) {
		elapsedTime += DeltaTime;
		if (elapsedTime >= warmupDuration) {
			warmupComplete = true;
			elapsedTime = 0.0f;
			UE_LOG(LogTemp, Warning, TEXT("Warmup Complete. Benchmark Started!"));
		}
		return;
	}

	elapsedTime += DeltaTime;
	frameCount++;

	if (elapsedTime >= benchmarkDuration) {
		benchmarkFinished = true;

		float averageFPS = static_cast<float>(frameCount) / elapsedTime;
		float averageTimeMs = (elapsedTime / static_cast<float>(frameCount)) * 1000.0f;

		FString resultString = FString::Printf(TEXT("=== BENCHMARK COMPLETE === | Avg FPS: %.2f | Avg Frame Time: %.2f ms"), averageFPS, averageTimeMs);

		UE_LOG(LogTemp, Error, TEXT("%s"), *resultString);

		if (GEngine) {
			GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Green, resultString);
		}

		SetActorTickEnabled(false);
	}
}

