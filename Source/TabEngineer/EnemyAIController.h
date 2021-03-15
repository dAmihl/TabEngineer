// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "BaseCore.h"

#include "EnemyAIController.generated.h"

/**
 * 
 */
UCLASS()
class TABENGINEER_API AEnemyAIController : public AAIController
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess="true"))
	class UBehaviorTree* BehaviorTree;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess="true"))
	ABaseCore* CoreTarget;

	
public:
	AEnemyAIController();

	virtual void OnPossess(APawn* InPawn) override;
	void SetCoreTarget(ABaseCore* Target);
	void UnsetCoreTarget();
};
