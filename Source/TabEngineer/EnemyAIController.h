// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
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

public:
	AEnemyAIController();

	virtual void OnPossess(APawn* InPawn) override;
};
