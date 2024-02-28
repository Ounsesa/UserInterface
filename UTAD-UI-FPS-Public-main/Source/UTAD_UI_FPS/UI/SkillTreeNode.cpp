// Fill out your copyright notice in the Description page of Project Settings.


#include "SkillTreeNode.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "SkillTree.h"

void USkillTreeNode::NativeConstruct()
{
	

	SkillButton->OnClicked.AddDynamic(this, &USkillTreeNode::SkillButtonClicked);

	NumberSkillPoints->SetText(FText::FromString(FString::FromInt(SkillPoints)));
	
}

void USkillTreeNode::Show()
{
	SetVisibility(ESlateVisibility::Visible);
}

void USkillTreeNode::Hide()
{
	SetVisibility(ESlateVisibility::Hidden);
}

void USkillTreeNode::Activated()
{
	SkillButton->SetBackgroundColor(FLinearColor(0.0f, 0.67f, 0.23f, 1.0f));
}

void USkillTreeNode::SkillButtonClicked()
{
	SkillTreeInstance->ShowConfirmationPanel(SkillType, SkillPoints);
}
