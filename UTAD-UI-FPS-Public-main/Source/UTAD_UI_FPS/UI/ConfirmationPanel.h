// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Enum.h"
#include "ConfirmationPanel.generated.h"


class USkillTree;
/**
 * 
 */
UCLASS()
class UTAD_UI_FPS_API UConfirmationPanel : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual void NativeConstruct() override;
	
	void Show();

	void Hide();

	ESkillType SkillType;
	int SkillLevel;
	USkillTree* SkillTreeInstance;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UTextBlock* Message;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UButton* YesButton;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UButton* NoButton;

private:
	UFUNCTION()
	void OnConfirmButtonClicked();

	UFUNCTION()
	void OnCancelButtonClicked();



	
	
};
