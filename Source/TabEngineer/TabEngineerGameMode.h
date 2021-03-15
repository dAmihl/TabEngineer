// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"


#include "BaseCore.h"
#include "Enemy.h"
#include "EnemySpawn.h"
#include "GameFramework/GameModeBase.h"
#include "TabEngineerGameMode.generated.h"

UCLASS(minimalapi)
class ATabEngineerGameMode : public AGameModeBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess="true"))
	TSubclassOf<AEnemy> EnemyBP;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess="true"))
	TSubclassOf<ABaseCore> CoreBP;

	UPROPERTY()
	TArray<AActor*> EnemySpawnPoints;

	UPROPERTY()
	ABaseCore* MainCore;

public:
	ATabEngineerGameMode();

	virtual void BeginPlay() override;

private:
	void SpawnEnemy();
	void StartRound();
	void SpawnCore();
};



