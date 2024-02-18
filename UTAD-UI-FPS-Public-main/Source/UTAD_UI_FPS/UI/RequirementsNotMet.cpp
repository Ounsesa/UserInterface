// Fill out your copyright notice in the Description page of Project Settings.


#include "RequirementsNotMet.h"
#include "Components/Button.h"
#include "SkillTree.h"

void URequirementsNotMet::NativeConstruct()
{
	Super::NativeConstruct();

	BackButton->OnClicked.AddDynamic(this, &URequirementsNotMet::Hide);
}

void URequirementsNotMet::Show()
{
	SetVisibility(ESlateVisibility::Visible);
	SkillTreeInstance->SetVisibility(ESlateVisibility::Hidden);
}

void URequirementsNotMet::Hide()
{
	SetVisibility(ESlateVisibility::Hidden);
	SkillTreeInstance->SetVisibility(ESlateVisibility::Visible);
}