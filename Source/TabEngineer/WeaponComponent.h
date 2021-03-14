// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "Enemy.h"
#include "Components/SceneComponent.h"
#include "WeaponComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TABENGINEER_API UWeaponComponent : public USceneComponent
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess="true"))
	class UStaticMeshComponent* StaticMeshComponent;

public:	
	// Sets default values for this component's properties
	UWeaponComponent();

	UPROPERTY(EditAnywhere, Category=Combat)
	TSubclassOf<class ABulletTrailSpline> ShootTrailSpline;
	
protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	virtual void Shoot(AEnemy* Target);
		
};
