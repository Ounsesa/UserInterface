// Fill out your copyright notice in the Description page of Project Settings.


#include "ConfirmationPanel.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "SkillTree.h"

void UConfirmationPanel::NativeConstruct()
{
	Super::NativeConstruct();

	YesButton->OnClicked.AddDynamic(this, &UConfirmationPanel::OnConfirmButtonClicked);
	NoButton->OnClicked.AddDynamic(this, &UConfirmationPanel::OnCancelButtonClicked);
}


void UConfirmationPanel::Show()
{
	SetVisibility(ESlateVisibility::Visible);
	Message->SetText(FText::FromString(FString::Printf(TEXT("Are you sure you want to upgrade\n this skill for %i points?"), SkillLevel)));
	SkillTreeInstance->SetVisibility(ESlateVisibility::Hidden);
}

void UConfirmationPanel::Hide()
{
	SetVisibility(ESlateVisibility::Hidden);
	SkillTreeInstance->SetVisibility(ESlateVisibility::Visible);
}

void UConfirmationPanel::OnConfirmButtonClicked()
{
	Hide();
	if (SkillTreeInstance)
	{
		SkillTreeInstance->UpgradeSkill(SkillType, SkillLevel);
	}
}

void UConfirmationPanel::OnCancelButtonClicked()
{
	Hide();
}