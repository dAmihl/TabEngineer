// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "HealthComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TABENGINEER_API UHealthComponent : public UActorComponent
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, Category="Health")
	float MaxHealth;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Health", meta=(AllowPrivateAccess="true"))
	float CurrentHealth;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Health", meta=(AllowPrivateAccess="true"))
	bool bIsDead;
	
	void CheckDeath();
	
public:	
	// Sets default values for this component's properties
	UHealthComponent();

	bool IsDead() const;

	void GiveDamage(const float Amount);
	void GiveHealth(const float Amount);
	
protected:
	// Called when the game starts
	virtual void BeginPlay() override;

		
};
