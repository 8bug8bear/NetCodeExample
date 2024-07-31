// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "BarrelComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class NETCODEEXAMPLE_API UBarrelComponent : public USceneComponent
{
	GENERATED_BODY()

protected:
	float FireRange = 999999.0f;
	float DamageAmount = 40.0f;

public:
	void SetDamageAmount(float NewDamage);

	UFUNCTION()
	void Shoot(FVector Start, FVector Direction, AController* Controller, AActor* IgnoreActor) const;
	
	UBarrelComponent();
	
};
