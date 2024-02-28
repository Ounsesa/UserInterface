// Fill out your copyright notice in the Description page of Project Settings.


#include "Crosshair.h"
#include "Components/Image.h"
#include "../UTAD_UI_FPSCharacter.h"

void UCrosshair::NativeConstruct()
{
	Super::NativeConstruct();

	Character = Cast<AUTAD_UI_FPSCharacter>(GetOwningPlayerPawn());
}

void UCrosshair::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	if (AnimationTimer > 0)
	{
		AnimationTimer -= InDeltaTime;
		if (AnimationTimer <= 0)
		{
			Character->AnimationShooting = false;
		}
	}
}

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

void UCrosshair::ShotAnimation()
{
	Character->AnimationShooting = true;
	AnimationTimer = AnimationTime;
	Crosshair->SetDesiredSizeOverride(FVector2D(150, 150));
}

void UCrosshair::MoveAnimation(bool Moving)
{
	if (Moving)
	{
		Crosshair->SetDesiredSizeOverride(FVector2D(125, 125));
	}
	else
	{
		Crosshair->SetDesiredSizeOverride(FVector2D(100, 100));
	}
}