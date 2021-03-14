// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemySpawn.h"
#include "Components/SceneComponent.h"

// Sets default values
AEnemySpawn::AEnemySpawn()
{
 	Scene = CreateDefaultSubobject<USceneComponent>(TEXT("SceneComponent"));
}

// Called when the game starts or when spawned
void AEnemySpawn::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AEnemySpawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

