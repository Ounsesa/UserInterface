// Fill out your copyright notice in the Description page of Project Settings.


#include "SplashScreen.h"

#define SPLASH_SCREEN_TIME 0.5f

void USplashScreen::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{	
	SplashScreenTimer += InDeltaTime;
	if (SplashScreenTimer >= SPLASH_SCREEN_TIME)
	{
		RemoveFromParent();
	}
	
}