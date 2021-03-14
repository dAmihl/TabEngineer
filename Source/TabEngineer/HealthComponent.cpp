// Fill out your copyright notice in the Description page of Project Settings.


#include "HealthComponent.h"



// Sets default values for this component's properties
UHealthComponent::UHealthComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	MaxHealth = 100.f;
	bIsDead = false;
	
	// ...
}

bool UHealthComponent::IsDead() const
{
	return bIsDead;
}

void UHealthComponent::GiveDamage(const float Amount)
{
	// Only give positive amount of damage
	check(Amount >= 0.f);
	CurrentHealth = FMath::Max(0.f, CurrentHealth - Amount);
	CheckDeath();
}

void UHealthComponent::GiveHealth(const float Amount)
{
	check(Amount >= 0.f);
	CurrentHealth = FMath::Min(MaxHealth, CurrentHealth + Amount);
}

// Called when the game starts
void UHealthComponent::BeginPlay()
{
	Super::BeginPlay();

	CurrentHealth = MaxHealth;
}

void UHealthComponent::CheckDeath()
{
	if (!bIsDead)
	{
		bIsDead = CurrentHealth <= 0.f;
	}
}