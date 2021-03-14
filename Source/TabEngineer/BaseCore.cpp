// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseCore.h"
#include "HealthComponent.h"
#include "Components/StaticMeshComponent.h"

// Sets default values
ABaseCore::ABaseCore()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	HealthComponent = CreateDefaultSubobject<UHealthComponent>(TEXT("HealthComponent"));
	CoreMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("CoreMesh"));
}

// Called when the game starts or when spawned
void ABaseCore::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABaseCore::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ABaseCore::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ABaseCore::Damage(const float Amount)
{
	HealthComponent->GiveDamage(Amount);
	if (IsDead())
	{
		Death();
	}
}

void ABaseCore::Death()
{
	GetWorld()->DestroyActor(this);
}

bool ABaseCore::IsDead() const
{
	return HealthComponent->IsDead();
}

