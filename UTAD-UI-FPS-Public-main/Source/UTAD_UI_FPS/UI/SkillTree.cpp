// Fill out your copyright notice in the Description page of Project Settings.


#include "SkillTree.h"
#include "Components/TextBlock.h"
#include "Components/Button.h"
#include "RequirementsNotMet.h"
#include "ConfirmationPanel.h"
#include "Components/CanvasPanel.h"
#include "SkillTreeNode.h"

void USkillTree::NativeConstruct()
{
	Super::NativeConstruct();


	NumberSkillPoints->SetText(FText::FromString(FString::FromInt(TotalSkillPoints)));

	SkillPoints.Add(ESkillType::Speed, 0);
	SkillPoints.Add(ESkillType::Health, 0);
	SkillPoints.Add(ESkillType::Damage, 0);

	TArray<UWidget*> CanvasChildren = CanvasPanel->GetAllChildren();
	for (UWidget* Widget : CanvasChildren)
	{
		USkillTreeNode* SkillTreeNode = Cast<USkillTreeNode>(Widget);
		if (SkillTreeNode)
		{
			SkillTreeNode->SkillTreeInstance = this;
			if (SkillTreeNode->SkillPoints > 1)
			{
				SkillTreeNode->Hide();
			}
			SkillButtons.Add(SkillTreeNode);
		}
	}

	if (ConfirmationPanelWidget)
	{
		ConfirmationPanelInstance = CreateWidget<UConfirmationPanel>(GetWorld(), ConfirmationPanelWidget);
		ConfirmationPanelInstance->SkillTreeInstance = this;
		ConfirmationPanelInstance->AddToViewport();
		ConfirmationPanelInstance->Hide();
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Confirmation Panel Widget not assigned to Skill Tree"));
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Confirmation Panel Widget not assigned to Skill Tree"));
	}
	if (RequirementsNotMetWidget)
	{
		RequirementsNotMetInstance = CreateWidget<URequirementsNotMet>(GetWorld(), RequirementsNotMetWidget);
		RequirementsNotMetInstance->SkillTreeInstance = this;
		RequirementsNotMetInstance->AddToViewport();
		RequirementsNotMetInstance->Hide();
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Requirements Not Met Widget not assigned to Skill Tree"));
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Requirements Not Met Widget not assigned to Skill Tree"));
	}

	
}

void USkillTree::Show()
{
	APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
	PlayerController->SetInputMode(FInputModeGameAndUI());
	PlayerController->bShowMouseCursor = true;
	PlayerController->Pause();

	SetVisibility(ESlateVisibility::Visible);
	
}

void USkillTree::Hide()
{
	APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
	PlayerController->SetInputMode(FInputModeGameOnly());
	PlayerController->bShowMouseCursor = false;
	PlayerController->SetPause(false);

	SetVisibility(ESlateVisibility::Hidden);
}


void USkillTree::UpgradeSkill(ESkillType SkillType, int Points)
{
	if (TotalSkillPoints < Points || SkillPoints[SkillType] != Points-1)
	{
		RequirementsNotMetInstance->Show();
		return;
	}
	TotalSkillPoints -= Points;
	SkillPoints.Add(SkillType, Points);

	int ButtonToActivate = (int)SkillType * 3 + Points - 1;


	SkillButtons[ButtonToActivate]->Activated();
	if (Points < 3)
	{
		SkillButtons[ButtonToActivate + 1]->Show();
	}

	NumberSkillPoints->SetText(FText::FromString(FString::Printf(TEXT("%i"), TotalSkillPoints)));
}

void USkillTree::ShowConfirmationPanel(ESkillType SkillType, int Points)
{
	ConfirmationPanelInstance->SkillType = SkillType;
	ConfirmationPanelInstance->SkillLevel = Points;
	ConfirmationPanelInstance->Show();
}
