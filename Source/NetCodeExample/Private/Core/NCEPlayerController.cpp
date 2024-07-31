// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/NCEPlayerController.h"

void ANCEPlayerController::Client_OnMatchIsOver_Implementation()
{
	BPI_OnMatchIsOver();
}