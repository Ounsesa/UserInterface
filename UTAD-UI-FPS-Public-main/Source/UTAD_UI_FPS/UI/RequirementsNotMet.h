// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "RequirementsNotMet.generated.h"

class USkillTree;

/**
 * 
 */
UCLASS()
class UTAD_UI_FPS_API URequirementsNotMet : public UUserWidget
{
	GENERATED_BODY()
	
public:
	virtual void NativeConstruct() override;

	void Show();

	UFUNCTION()
	void Hide();

	USkillTree* SkillTreeInstance;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UTextBlock* Message;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UButton* BackButton;

};
