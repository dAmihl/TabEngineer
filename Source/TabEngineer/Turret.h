// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "Enemy.h"
#include "GameFramework/Pawn.h"
#include "Turret.generated.h"

UCLASS()
class TABENGINEER_API ATurret : public APawn
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess="true"))
	class UStaticMeshComponent* TurretMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess="true"))
	class UWeaponComponent* WeaponComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Combat", meta = (AllowPrivateAccess = "true"))
	class USphereComponent* SphereComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Combat", meta=(AllowPrivateAccess="true"))
	TWeakObjectPtr<AEnemy> CurrentTarget;
	FTimerHandle AutoAttackTimerHandle;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Combat", meta=(AllowPrivateAccess="true"))
	bool IsShooting;

public:
	// Sets default values for this pawn's properties
	ATurret();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float AttackRange;
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;


	UFUNCTION(BlueprintCallable, Category = "Combat")
	void Target();
	
	UFUNCTION(BlueprintCallable, Category = "Combat")
	void ClearTarget();

	UFUNCTION(BlueprintCallable, Category = "Combat")
	void StartAttack();

	UFUNCTION(BlueprintCallable, Category = "Combat")
	void StopAttack();

private:
		
	void Attack();
	
};
