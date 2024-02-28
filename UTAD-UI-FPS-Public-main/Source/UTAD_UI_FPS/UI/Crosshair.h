// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Crosshair.generated.h"

class AUTAD_UI_FPSCharacter;

/**
 * 
 */
UCLASS()
class UTAD_UI_FPS_API UCrosshair : public UUserWidget
{
	GENERATED_BODY()

	float AnimationTimer = 0;
	AUTAD_UI_FPSCharacter* Character;
	virtual void NativeConstruct() override;

public:

	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = UI)
	float AnimationTime = 0.2f;



	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;


	UFUNCTION(BlueprintCallable, Category = Visibility)
	void Show();

	UFUNCTION(BlueprintCallable, Category = Visibility)
	void Hide();

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UImage* Crosshair;

	void SetCrosshairColor(bool EnemyDetected);

	void ShotAnimation();

	void MoveAnimation(bool Moving);
};
