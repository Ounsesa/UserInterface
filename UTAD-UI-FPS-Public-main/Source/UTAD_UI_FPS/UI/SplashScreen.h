// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SplashScreen.generated.h"

/**
 * 
 */
UCLASS()
class UTAD_UI_FPS_API USplashScreen : public UUserWidget
{
	GENERATED_BODY()
	
public:
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

private:
	float SplashScreenTimer = 0.f;

};
