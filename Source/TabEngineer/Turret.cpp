// Fill out your copyright notice in the Description page of Project Settings.


#include "Turret.h"
#include "WeaponComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SphereComponent.h"

// Sets default values
ATurret::ATurret()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	AttackRange = 600.f;
	
	TurretMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("TurretMesh"));
	SetRootComponent(TurretMesh);

	WeaponComponent = CreateDefaultSubobject<UWeaponComponent>(TEXT("Gun"));
	WeaponComponent->SetupAttachment(RootComponent);

	SphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("TargetingSphere"));
	SphereComponent->SetupAttachment(RootComponent);
	SphereComponent->SetSphereRadius(AttackRange);
}

// Called when the game starts or when spawned
void ATurret::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATurret::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ATurret::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ATurret::Target()
{
	TArray<AActor*> Result;
	SphereComponent->GetOverlappingActors(Result, AEnemy::StaticClass());
	if (Result.Num() > 0)
	{
		AActor* FirstHit = *(Result.GetData());
		AEnemy* FirstEnemy = Cast<AEnemy>(FirstHit);
		CurrentTarget = FirstEnemy;
	}
}

void ATurret::ClearTarget()
{
	CurrentTarget.Reset();
	StopAttack();
}

void ATurret::StopAttack()
{
	IsShooting = false;
	GetWorldTimerManager().ClearTimer(AutoAttackTimerHandle);
}

void ATurret::Attack()
{
	if (CurrentTarget != nullptr)
	{

		if (GetDistanceTo(CurrentTarget.Get()) > AttackRange)
		{
			StopAttack();
			ClearTarget();
		}
		else
		{
			WeaponComponent->Shoot(CurrentTarget.Get());	
		}
	}
}

void ATurret::StartAttack()
{
	if (CurrentTarget != nullptr)
	{
		GetWorldTimerManager().SetTimer(AutoAttackTimerHandle, this, &ATurret::Attack, 1.0f, true, 1.0f);
		IsShooting = true;
	}
}
