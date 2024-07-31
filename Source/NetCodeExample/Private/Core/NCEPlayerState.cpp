// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/NCEPlayerState.h"
#include "Net/UnrealNetwork.h"
#include "Net/Core/PushModel/PushModel.h"

void ANCEPlayerState::SetKills(const int32 NewKills)
{
	if(NewKills<0)
	{
		Kills = 0;
		return;
	}
	Kills = NewKills;
}

void ANCEPlayerState::SetDeaths(const int32 NewDeaths)
{
	if(NewDeaths<0)
	{
		Deaths = 0;
		return;
	}
	Deaths = NewDeaths;
}

void ANCEPlayerState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	
	DOREPLIFETIME(ANCEPlayerState, Kills);
	DOREPLIFETIME(ANCEPlayerState, Deaths);
}

void ANCEPlayerState::AddKill()
{
	if(IsNetMode(NM_DedicatedServer))
	{
		SetKills(Kills+1);
	}
}

void ANCEPlayerState::AddDeath()
{
	if(IsNetMode(NM_DedicatedServer))
	{
		SetDeaths(Deaths+1);
	}
}

void ANCEPlayerState::ResetKDA()
{
	if(!IsNetMode(NM_DedicatedServer))
	{
		return;
	}

	SetKills(0);
	SetDeaths(0);
}

