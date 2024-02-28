// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "../UTAD_UI_FPSCharacter.h"
#include "Enum.h"
#include "SkillTree.generated.h"



class USkillTreeNode;
class URequirementsNotMet;
class UConfirmationPanel;
/**
 *
 */
UCLASS()
class UTAD_UI_FPS_API USkillTree : public UUserWidget
{
	GENERATED_BODY()



public:
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UCanvasPanel* CanvasPanel;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UTextBlock* NumberSkillPoints;

public:
	virtual void NativeConstruct() override;

	void Show();

	void Hide();

	void UpgradeSkill(ESkillType SkillType, int Points);

	void ShowConfirmationPanel(ESkillType SkillType, int Points);


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = UI)
	TSubclassOf<class URequirementsNotMet> RequirementsNotMetWidget;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = UI)
	TSubclassOf<class UConfirmationPanel> ConfirmationPanelWidget;


private:
	TArray<USkillTreeNode*> SkillButtons;
	URequirementsNotMet* RequirementsNotMetInstance;
	UConfirmationPanel* ConfirmationPanelInstance;



public:
	TMap<ESkillType, int> SkillPoints;
	int TotalSkillPoints = 15;
};
