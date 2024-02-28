// Fill out your copyright notice in the Description page of Project Settings.


#include "Crosshair.h"
#include "Components/Image.h"

void UCrosshair::Show()
{
	SetVisibility(ESlateVisibility::HitTestInvisible);
}

void UCrosshair::Hide()
{
	SetVisibility(ESlateVisibility::Hidden);
}

void UCrosshair::SetCrosshairColor(bool EnemyDetected)
{
	Crosshair->SetBrushTintColor(EnemyDetected ? FLinearColor::Red : FLinearColor::White);
}
