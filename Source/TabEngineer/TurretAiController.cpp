// Fill out your copyright notice in the Description page of Project Settings.


#include "TurretAiController.h"
#include "BehaviorTree/BehaviorTree.h"

ATurretAiController::ATurretAiController()
{
	ConstructorHelpers::FObjectFinder<UBehaviorTree> CHFBehaviorTree(TEXT("BehaviorTree'/Game/AI/TurretBehaviorTree.TurretBehaviorTree'"));
	BehaviorTree = CHFBehaviorTree.Object;
}

void ATurretAiController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
	RunBehaviorTree(BehaviorTree);
}
