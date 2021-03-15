// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyAIController.h"
#include "BehaviorTree/BehaviorTree.h"

AEnemyAIController::AEnemyAIController()
{
	ConstructorHelpers::FObjectFinder<UBehaviorTree> CHFBehaviorTree(TEXT("BehaviorTree'/Game/AI/Enemy/EnemyBehaviorTree.EnemyBehaviorTree'"));
	BehaviorTree = CHFBehaviorTree.Object;
}

void AEnemyAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	RunBehaviorTree(BehaviorTree);
}
