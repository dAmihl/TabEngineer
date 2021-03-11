// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BulletTrailSpline.generated.h"

UCLASS()
class TABENGINEER_API ABulletTrailSpline : public AActor
{
	GENERATED_BODY()
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class USplineMeshComponent* SplineComponent;
	
	FTimerHandle LifetimeTimerHandle;

public:	
	// Sets default values for this actor's properties
	ABulletTrailSpline();

	UPROPERTY(EditAnywhere)
	float Lifetime;
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;


	void SetStartEnd(const FVector Start, const FVector End);

	void SelfDestroy();

};
