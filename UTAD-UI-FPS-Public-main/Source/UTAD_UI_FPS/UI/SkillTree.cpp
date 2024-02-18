// Fill out your copyright notice in the Description page of Project Settings.


#include "SkillTree.h"
#include "Components/TextBlock.h"
#include "Components/Button.h"
#include "ConfirmationPanel.h"
#include "RequirementsNotMet.h"

void USkillTree::NativeConstruct()
{
	Super::NativeConstruct();

	PlayerCharacter = Cast<AUTAD_UI_FPSCharacter>(GetOwningPlayerPawn());

	NumberSkillPoints->SetText(FText::FromString(FString::FromInt(PlayerCharacter->TotalSkillPoints)));

	SpeedSkill1->OnClicked.AddDynamic(this, &USkillTree::SpeedSkill1Clicked);
	SpeedSkill2->OnClicked.AddDynamic(this, &USkillTree::SpeedSkill2Clicked);
	SpeedSkill3->OnClicked.AddDynamic(this, &USkillTree::SpeedSkill3Clicked);
	DamageSkill1->OnClicked.AddDynamic(this, &USkillTree::DamageSkill1Clicked);
	DamageSkill2->OnClicked.AddDynamic(this, &USkillTree::DamageSkill2Clicked);
	DamageSkill3->OnClicked.AddDynamic(this, &USkillTree::DamageSkill3Clicked);
	HealthSkill1->OnClicked.AddDynamic(this, &USkillTree::HealthSkill1Clicked);
	HealthSkill2->OnClicked.AddDynamic(this, &USkillTree::HealthSkill2Clicked);
	HealthSkill3->OnClicked.AddDynamic(this, &USkillTree::HealthSkill3Clicked);

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

void USkillTree::SpeedSkill1Clicked()
{
	ConfirmationPanelInstance->SkillType = ESkillType::Speed;
	ConfirmationPanelInstance->SkillLevel = 1;
	ConfirmationPanelInstance->Show();
}

void USkillTree::SpeedSkill2Clicked()
{
	ConfirmationPanelInstance->SkillType = ESkillType::Speed;
	ConfirmationPanelInstance->SkillLevel = 2;
	ConfirmationPanelInstance->Show();
}

void USkillTree::SpeedSkill3Clicked()
{
	ConfirmationPanelInstance->SkillType = ESkillType::Speed;
	ConfirmationPanelInstance->SkillLevel = 3;
	ConfirmationPanelInstance->Show();
}

void USkillTree::DamageSkill1Clicked()
{
	ConfirmationPanelInstance->SkillType = ESkillType::Damage;
	ConfirmationPanelInstance->SkillLevel = 1;
	ConfirmationPanelInstance->Show();
}

void USkillTree::DamageSkill2Clicked()
{
	ConfirmationPanelInstance->SkillType = ESkillType::Damage;
	ConfirmationPanelInstance->SkillLevel = 2;
	ConfirmationPanelInstance->Show();
}

void USkillTree::DamageSkill3Clicked()
{
	ConfirmationPanelInstance->SkillType = ESkillType::Damage;
	ConfirmationPanelInstance->SkillLevel = 3;
	ConfirmationPanelInstance->Show();
}

void USkillTree::HealthSkill1Clicked()
{
	ConfirmationPanelInstance->SkillType = ESkillType::Health;
	ConfirmationPanelInstance->SkillLevel = 1;
	ConfirmationPanelInstance->Show();
}

void USkillTree::HealthSkill2Clicked()
{
	ConfirmationPanelInstance->SkillType = ESkillType::Health;
	ConfirmationPanelInstance->SkillLevel = 2;
	ConfirmationPanelInstance->Show();
}

void USkillTree::HealthSkill3Clicked()
{
	ConfirmationPanelInstance->SkillType = ESkillType::Health;
	ConfirmationPanelInstance->SkillLevel = 3;
	ConfirmationPanelInstance->Show();
}

void USkillTree::UpgradeSkill(ESkillType SkillType, int Points)
{
	if (PlayerCharacter->TotalSkillPoints < Points || PlayerCharacter->SkillPoints[SkillType] != Points-1)
	{
		RequirementsNotMetInstance->Show();
		return;
	}
	PlayerCharacter->TotalSkillPoints -= Points;
	PlayerCharacter->SkillPoints.Add(SkillType, Points);
	NumberSkillPoints->SetText(FText::FromString(FString::Printf(TEXT("%d"), PlayerCharacter->TotalSkillPoints)));
}
