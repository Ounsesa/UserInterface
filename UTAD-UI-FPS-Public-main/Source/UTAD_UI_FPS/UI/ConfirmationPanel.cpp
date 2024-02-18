// Fill out your copyright notice in the Description page of Project Settings.


#include "ConfirmationPanel.h"
#include "Components/Button.h"
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