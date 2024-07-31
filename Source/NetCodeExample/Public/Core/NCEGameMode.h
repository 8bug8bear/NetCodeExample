// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "NCEGameMode.generated.h"

/**
 * 
 */
UCLASS()
class NETCODEEXAMPLE_API ANCEGameMode : public AGameMode
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category=Time)
	int32 MaxGameSessionTime = 30; // 5 minutes

	// Will players spawn in random spawn points after death, or selected in advance
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category=Respawn)
	bool bIsStaticSpawnPoints = false;
	
	virtual void RestartPlayer(AController* NewPlayer) override;

	virtual void EndMatch() override;
	
public:
	ANCEGameMode();

	// The killer transfers the controller, and the one killed by the pawn for the reason that the player kills and the pawn dies.
	void ReportDeathOfPlayer(const AController* Killer, AActor* Weapon, ACharacter* Killed);

protected:
	virtual void BeginPlay() override;
	
};
