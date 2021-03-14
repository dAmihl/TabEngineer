// Fill out your copyright notice in the Description page of Project Settings.


#include "WeaponComponent.h"

#include "BulletTrailSpline.h"

// Sets default values for this component's properties
UWeaponComponent::UWeaponComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	//StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("WeaponMesh"));
	//StaticMeshComponent->SetupAttachment(this);
		
}


// Called when the game starts
void UWeaponComponent::BeginPlay()
{
	Super::BeginPlay();

	
}


// Called every frame
void UWeaponComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}

void UWeaponComponent::Shoot(AEnemy* Target)
{
	Target->Damage(10);
	
	ABulletTrailSpline* trail = GetWorld()->SpawnActor<ABulletTrailSpline>(ShootTrailSpline);
	FVector SplineStart = GetComponentLocation();
	FVector TargetLocation = Target->GetActorLocation();
	FVector SplineEnd = FVector(TargetLocation.X, TargetLocation.Y, SplineStart.Z);
	// hand_rSocket
	trail->SetStartEnd( SplineStart, SplineEnd);
}

