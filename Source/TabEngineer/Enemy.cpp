// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy.h"
#include "HealthComponent.h"
#include "Components/CapsuleComponent.h"


// Sets default values
AEnemy::AEnemy()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	HealthComponent = CreateDefaultSubobject<UHealthComponent>(TEXT("Health"));
}

// Called when the game starts or when spawned
void AEnemy::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AEnemy::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AEnemy::Damage(const float Amount)
{
	HealthComponent->GiveDamage(Amount);
	UE_LOG(LogTemp, Display, TEXT("I received %f damage"), Amount);
	if (IsDead())
	{
		UE_LOG(LogTemp, Display, TEXT("I Am Dead"));
		Death();
	}
}

bool AEnemy::IsDead() const
{
	return HealthComponent->IsDead();
}

void AEnemy::Death()
{
	GetMesh()->SetSimulatePhysics(true);
	GetMesh()->SetCollisionProfileName(FName("Ragdoll"));
	GetMesh()->WakeAllRigidBodies();
	GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}
