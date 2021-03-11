// Fill out your copyright notice in the Description page of Project Settings.


#include "BulletTrailSpline.h"
#include "Components/SplineMeshComponent.h"

// Sets default values
ABulletTrailSpline::ABulletTrailSpline()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	SplineComponent = CreateDefaultSubobject<USplineMeshComponent>(TEXT("BulletSpline"));
	SetRootComponent(SplineComponent);
	
	Lifetime = 1.0f;
}

// Called when the game starts or when spawned
void ABulletTrailSpline::BeginPlay()
{
	Super::BeginPlay();

	GetWorldTimerManager().SetTimer(LifetimeTimerHandle, this, &ABulletTrailSpline::SelfDestroy, Lifetime, false, Lifetime);
}

// Called every frame
void ABulletTrailSpline::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABulletTrailSpline::SetStartEnd(const FVector Start, const FVector End)
{
	SplineComponent->SetStartAndEnd(Start, Start, End, End, true);
}

void ABulletTrailSpline::SelfDestroy()
{
	GetWorldTimerManager().ClearTimer(LifetimeTimerHandle);
	Super::Destroy();
}

