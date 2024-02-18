// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "../UTAD_UI_FPSCharacter.h"
#include "SkillTree.generated.h"



class UConfirmationPanel;
class URequirementsNotMet;


/**
 *
 */
UCLASS()
class UTAD_UI_FPS_API USkillTree : public UUserWidget
{
	GENERATED_BODY()

private:
	AUTAD_UI_FPSCharacter* PlayerCharacter;


public:
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UButton* SpeedSkill1;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UButton* SpeedSkill2;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UButton* SpeedSkill3;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UButton* DamageSkill1;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UButton* DamageSkill2;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UButton* DamageSkill3;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UButton* HealthSkill1;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UButton* HealthSkill2;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UButton* HealthSkill3;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UTextBlock* NumberSkillPoints;

public:
	virtual void NativeConstruct() override;

	void Show();

	void Hide();

	void UpgradeSkill(ESkillType SkillType, int Points);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = UI)
	TSubclassOf<class UConfirmationPanel> ConfirmationPanelWidget;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = UI)
	TSubclassOf<class URequirementsNotMet> RequirementsNotMetWidget;



private:
	UFUNCTION()
	void SpeedSkill1Clicked();

	UFUNCTION()
	void SpeedSkill2Clicked();

	UFUNCTION()
	void SpeedSkill3Clicked();

	UFUNCTION()
	void DamageSkill1Clicked();

	UFUNCTION()
	void DamageSkill2Clicked();

	UFUNCTION()
	void DamageSkill3Clicked();

	UFUNCTION()
	void HealthSkill1Clicked();

	UFUNCTION()
	void HealthSkill2Clicked();

	UFUNCTION()
	void HealthSkill3Clicked();


	UConfirmationPanel* ConfirmationPanelInstance;
	URequirementsNotMet* RequirementsNotMetInstance;
};
