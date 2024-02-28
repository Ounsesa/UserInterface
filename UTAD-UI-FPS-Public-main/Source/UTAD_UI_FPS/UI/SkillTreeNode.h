// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Enum.h"
#include "SkillTreeNode.generated.h"

class UConfirmationPanel;
class URequirementsNotMet;
class USkillTree;


/**
 * 
 */
UCLASS()
class UTAD_UI_FPS_API USkillTreeNode : public UUserWidget
{
	GENERATED_BODY()
public:

	virtual void NativeConstruct() override;

	void Show();

	void Hide();

	void Activated();

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UButton* SkillButton;


	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UTextBlock* NumberSkillPoints;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = UI)
	TSubclassOf<class UConfirmationPanel> ConfirmationPanelWidget;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = UI)
	ESkillType SkillType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = UI)
	int SkillPoints;

	UFUNCTION()
	void SkillButtonClicked();

	USkillTree* SkillTreeInstance;

private:
	UConfirmationPanel* ConfirmationPanelInstance;
};
