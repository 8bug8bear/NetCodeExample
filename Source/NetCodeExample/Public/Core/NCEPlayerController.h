// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "NCEPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class NETCODEEXAMPLE_API ANCEPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	UFUNCTION(Client, Reliable)
	void Client_OnMatchIsOver();

protected:
	UFUNCTION(BlueprintImplementableEvent, DisplayName = "OnMatchIsOver")
	void BPI_OnMatchIsOver();
	
};
