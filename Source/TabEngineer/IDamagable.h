// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

/**
 * 
 */
class TABENGINEER_API IDamagable
{
public:
	IDamagable();
	~IDamagable();

	virtual void Damage(const float Amount) = 0;
	virtual void Death() = 0;
	virtual bool IsDead() const = 0;
};
