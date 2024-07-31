// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "NCEPlayerState.generated.h"

/**
 * 
 */
UCLASS()
class NETCODEEXAMPLE_API ANCEPlayerState : public APlayerState
{
	GENERATED_BODY()

protected:
	UPROPERTY(Replicated)
	int32 Kills = 0;

	UPROPERTY(Replicated)
	int32 Deaths = 0;

	void SetKills(int32 NewKills);

	void SetDeaths(int32 NewDeaths);

public:
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	UFUNCTION(BlueprintPure)
	int32 GetKills() const{return Kills;}

	UFUNCTION(BlueprintPure)
	int32 GetDeaths() const{return Deaths;}

	void AddKill();
	void AddDeath();

	void ResetKDA();
	
};
