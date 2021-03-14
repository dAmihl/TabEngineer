// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"


#include "BulletTrailSpline.h"
#include "Enemy.h"
#include "GameFramework/Character.h"
#include "EngineerCharacter.generated.h"

UCLASS()
class TABENGINEER_API AEngineerCharacter : public ACharacter
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Camera", meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* SpringCameraArm;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Camera", meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* FollowCamera;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Combat", meta = (AllowPrivateAccess = "true"))
	class USphereComponent* SphereComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Combat", meta = (AllowPrivateAccess = "true"))
	class UWeaponComponent* Weapon;

	TWeakObjectPtr<AEnemy> CurrentTarget;

	FTimerHandle AutoAttackTimerHandle;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Combat", meta=(AllowPrivateAccess="true"))
	TSubclassOf<class ATurret> TurretClass;
	
public:
	// Sets default values for this character's properties
	AEngineerCharacter();

	/** Base turn rate, in deg/sec. Other scaling may affect final turn rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera)
	float BaseTurnRate;

	/** Base look up/down rate, in deg/sec. Other scaling may affect final rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera)
	float BaseLookUpRate;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category=Animation)
	bool JumpPressed;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category=Animation)
	bool ShootPressed;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category=Combat)
	float AttackRange;
	

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void MoveForward(float Value);

	void MoveRight(float Value);

	void Jump() override;

	void StopJumping() override;

	void Turn(float Value);
	void TurnRate(float Value);

	void LookUp(float Value);
	void LookUpRate(float Value);

	void Target();
	void ClearTarget();
	
	void Attack();
	void StartAttack();
	void StopAttack();
	
	void BuildTurret();

	void MainAction();

private:

	bool RayCastFromCamera(FVector& HitLocation) const;
};
