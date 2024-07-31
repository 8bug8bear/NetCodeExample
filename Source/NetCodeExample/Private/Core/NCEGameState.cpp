// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/NCEGameState.h"

#include "Net/UnrealNetwork.h"
#include "Net/Core/PushModel/PushModel.h"

void ANCEGameState::DefaultTimer()
{
	Super::DefaultTimer();

	if(!IsNetMode(NM_DedicatedServer))
	{
		return;
	}
	
	if(ElapsedTime >= MaxGameSessionTime && IsMatchInProgress() && MaxGameSessionTime != 0) // In case the maximum time is not initialized
	{
		OnGameTimeIsOverDelegate.ExecuteIfBound();
	}
}

void ANCEGameState::SetMaxGameSessionTime(int32 NewGameSessionTime)
{
	if(NewGameSessionTime > 0)
	{
		MaxGameSessionTime = NewGameSessionTime;
	}
}

void ANCEGameState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	
	DOREPLIFETIME(ANCEGameState, MaxGameSessionTime);
}
