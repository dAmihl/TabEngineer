// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "IDamagable.h"
#include "GameFramework/Character.h"
#include "Enemy.generated.h"

UCLASS()
class TABENGINEER_API AEnemy : public ACharacter, public IDamagable
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Health", meta=(AllowPrivateAccess="true"))
	class UHealthComponent* HealthComponent;

	

public:
	// Sets default values for this character's properties
	AEnemy();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual void Damage(const float Amount) override;

	virtual bool IsDead() const override;

	virtual void Death() override;
};
