// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "IDamagable.h"
#include "GameFramework/Pawn.h"
#include "BaseCore.generated.h"

UCLASS()
class TABENGINEER_API ABaseCore : public APawn, public IDamagable
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess="true"))
	class UStaticMeshComponent* CoreMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Health", meta=(AllowPrivateAccess="true"))
	class UHealthComponent* HealthComponent;

public:
	// Sets default values for this pawn's properties
	ABaseCore();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual void Damage(const float Amount) override;
	virtual void Death() override;

	virtual bool IsDead() const override;
	
};
