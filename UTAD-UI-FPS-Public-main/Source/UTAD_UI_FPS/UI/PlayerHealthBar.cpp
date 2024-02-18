// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerHealthBar.h"
#include "Kismet/GameplayStatics.h"
#include "../UTAD_UI_FPSCharacter.h"
#include "Components/ProgressBar.h"
#include "Math/Color.h"
#include "Styling/SlateColor.h"

#define BLINK_ANIMATION_TIME 1.f
#define BLINK_THRESHOLD 0.25f

void UPlayerHealthBar::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	LowHealthBlink();
}

void UPlayerHealthBar::NativeConstruct()
{
	Super::NativeConstruct();
	AUTAD_UI_FPSCharacter* Character = Cast<AUTAD_UI_FPSCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	if (Character)
	{
		Character->OnHealthChanged.BindUObject(this, &UPlayerHealthBar::UpdatePlayerHealthBar);
	}
}


void UPlayerHealthBar::Show()
{
	SetVisibility(ESlateVisibility::HitTestInvisible);
	
}

void UPlayerHealthBar::Hide()
{
	SetVisibility(ESlateVisibility::Hidden);
}

void UPlayerHealthBar::UpdatePlayerHealthBar(int NewHealth, int MaxHealth)
{
	float HealthPercentage = (float)NewHealth / (float)MaxHealth;
	PlayerHealthBar->SetPercent(HealthPercentage);
	if (HealthPercentage <= BLINK_THRESHOLD)
	{
		bIsLowHealth = true;
	}
	else
	{
		bIsLowHealth = false;
	}
}

void UPlayerHealthBar::LowHealthBlink()
{
	FProgressBarStyle HealthBarStyle = PlayerHealthBar->GetWidgetStyle();
	if (bIsLowHealth)
	{

		BlinkTimer += GetWorld()->GetDeltaSeconds();
		if (BlinkTimer >= BLINK_ANIMATION_TIME)
		{
			BlinkTimer = 0.f;
			bBlinkTurningRed = !bBlinkTurningRed;
		}
		if (bBlinkTurningRed)
		{
			HealthBarStyle.FillImage.TintColor = FSlateColor(FLinearColor(1.f, 0.f, 0.f, 1.f));
		}
		else
		{
			HealthBarStyle.FillImage.TintColor = FSlateColor(FLinearColor(0.f, 1.f, 0.f, 1.f));
		}
	}
	else
	{
		HealthBarStyle.FillImage.TintColor = FSlateColor(FLinearColor(0.f, 1.f, 0.f, 1.f));
	}

}
