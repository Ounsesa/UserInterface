// Fill out your copyright notice in the Description page of Project Settings.


#include "GameOver.h"
#include "Components/Button.h"
#include "../UTAD_UI_FPSCharacter.h"
#include "Kismet/KismetSystemLibrary.h"

void UGameOver::NativeConstruct()
{
	Super::NativeConstruct();

	RestartButton->OnClicked.AddDynamic(this, &UGameOver::RestartGame);
	QuitButton->OnClicked.AddDynamic(this, &UGameOver::QuitGame);
}

void UGameOver::Show()
{
	APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
	PlayerController->SetInputMode(FInputModeUIOnly());
	PlayerController->bShowMouseCursor = true;
	PlayerController->Pause();

	RestartButton->SetFocus();
}

void UGameOver::RestartGame()
{
	APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
	PlayerController->RestartLevel();
	PlayerController->SetInputMode(FInputModeGameOnly());
	PlayerController->bShowMouseCursor = false;	

}

void UGameOver::QuitGame()
{
	UKismetSystemLibrary::QuitGame(GetWorld(), NULL, EQuitPreference::Quit, true);
}
