// Copyright Epic Games, Inc. All Rights Reserved.

#include "TabEngineerGameMode.h"

#include "Kismet/GameplayStatics.h"

ATabEngineerGameMode::ATabEngineerGameMode()
{
}

void ATabEngineerGameMode::BeginPlay()
{
	Super::BeginPlay();

	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AEnemySpawn::StaticClass(), EnemySpawnPoints);

	SpawnCore();
}

void ATabEngineerGameMode::SpawnEnemy()
{
	check(EnemySpawnPoints.Num() > 0);
	AActor* SpawnActor = EnemySpawnPoints[FMath::RandRange(0, EnemySpawnPoints.Num() - 1)];
	FVector SpawnLocation = SpawnActor->GetActorLocation();
	FRotator SpawnRotator = SpawnActor->GetActorRotation();
	FActorSpawnParameters SpawnParameters;
	GetWorld()->SpawnActor(EnemyBP, &SpawnLocation, &SpawnRotator, SpawnParameters);
	
}

void ATabEngineerGameMode::StartRound()
{
	for (int i = 0; i < 2; ++i)
	{
		SpawnEnemy();
	}
}

void ATabEngineerGameMode::SpawnCore()
{
	
	FVector SpawnLocation = FVector::ZeroVector;
	FRotator SpawnRotator = FRotator::ZeroRotator;
	FActorSpawnParameters SpawnParameters;
	AActor* Core = GetWorld()->SpawnActor(CoreBP, &SpawnLocation, &SpawnRotator, SpawnParameters);
	Core->SetOwner(this);

	StartRound();
}
