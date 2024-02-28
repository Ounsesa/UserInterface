// Copyright Epic Games, Inc. All Rights Reserved.

#include "UTAD_UI_FPSCharacter.h"
#include "UTAD_UI_FPSProjectile.h"
#include "UTAD_UI_FPS_Enemy.h"
#include "Animation/AnimInstance.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "TP_WeaponComponent.h"
#include "Engine/World.h"

// UI
#include "Blueprint/UserWidget.h"
#include "UI/PlayerHUD.h"
#include "UI/GameOver.h"
#include "UI/PlayerHitMarker.h"
#include "UI/SplashScreen.h"
#include "UI/SkillTree.h"
#include "UI/Crosshair.h"

//////////////////////////////////////////////////////////////////////////
// AUTAD_UI_FPSCharacter

AUTAD_UI_FPSCharacter::AUTAD_UI_FPSCharacter()
{
	// Character doesnt have a rifle at start
	bHasRifle = false;
	
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(55.f, 96.0f);
		
	// Create a CameraComponent	
	FirstPersonCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
	FirstPersonCameraComponent->SetupAttachment(GetCapsuleComponent());
	FirstPersonCameraComponent->SetRelativeLocation(FVector(-10.f, 0.f, 60.f)); // Position the camera
	FirstPersonCameraComponent->bUsePawnControlRotation = true;

	// Create a mesh component that will be used when being viewed from a '1st person' view (when controlling this pawn)
	Mesh1P = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("CharacterMesh1P"));
	Mesh1P->SetOnlyOwnerSee(true);
	Mesh1P->SetupAttachment(FirstPersonCameraComponent);
	Mesh1P->bCastDynamicShadow = false;
	Mesh1P->CastShadow = false;
	//Mesh1P->SetRelativeRotation(FRotator(0.9f, -19.19f, 5.2f));
	Mesh1P->SetRelativeLocation(FVector(-30.f, 0.f, -150.f));

}

void AUTAD_UI_FPSCharacter::BeginPlay()
{
	// Call the base class  
	Super::BeginPlay();

	//Add Input Mapping Context
	if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}

	//Set up all UI Widgets
	SetUpUI();



	
}

void AUTAD_UI_FPSCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (bHasRifle)
	{
		FVector CameraLocation = FirstPersonCameraComponent->GetComponentLocation();
		FVector CameraForward = FirstPersonCameraComponent->GetForwardVector();
		FVector End = CameraLocation + (CameraForward * 10000.f);


		FHitResult OutHit;

		bool bHit = GetWorld()->LineTraceSingleByChannel(OutHit, CameraLocation, End, ECC_Visibility);

		if (bHit)
		{
			AUTAD_UI_FPS_Enemy* Enemy = Cast<AUTAD_UI_FPS_Enemy>(OutHit.GetActor());
			if (Enemy)
			{
				PlayerHUDInstance->CrosshairWidget->SetCrosshairColor(true);
			}
			else
			{
				PlayerHUDInstance->CrosshairWidget->SetCrosshairColor(false);
			}

		}
		else
		{
			PlayerHUDInstance->CrosshairWidget->SetCrosshairColor(false);
		}

		if (!AnimationShooting)
		{
			if (GetVelocity().Size() > 0)
			{
				PlayerHUDInstance->CrosshairWidget->MoveAnimation(true);
			}
			else
			{
				PlayerHUDInstance->CrosshairWidget->MoveAnimation(false);
			}
		}
	}



	
}

//////////////////////////////////////////////////////////////////////////// Input

void AUTAD_UI_FPSCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
	{
		//Jumping
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Triggered, this, &ACharacter::Jump);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);

		//Moving
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AUTAD_UI_FPSCharacter::Move);

		//Looking
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &AUTAD_UI_FPSCharacter::Look);

		//Skill Tree
		EnhancedInputComponent->BindAction(OpenSkillTree, ETriggerEvent::Started, this, &AUTAD_UI_FPSCharacter::OpenSkillTreeMenu);
	}
}

void AUTAD_UI_FPSCharacter::SetUpUI()
{
	// Setup Player HUD
	if (PlayerHUDWidget)
	{
		PlayerHUDInstance = CreateWidget<UPlayerHUD>(GetWorld(), PlayerHUDWidget);
		PlayerHUDInstance->AddToViewport();
		PlayerHUDInstance->ShowNoWeapon();
		OnHealthChanged.ExecuteIfBound(Health, MaxHealth);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Player HUD Widget not assigned to UTAD_UI_FPSCharacter"));
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Player HUD Widget not assigned to UTAD_UI_FPSCharacter"));
	}

	if (PlayerHitMarkerWidget)
	{
		PlayerHitMarkerInstance = CreateWidget<UPlayerHitMarker>(GetWorld(), PlayerHitMarkerWidget);
		PlayerHitMarkerInstance->AddToViewport();
		PlayerHitMarkerInstance->Hide();
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Player Hit Marker Widget not assigned to UTAD_UI_FPSCharacter"));
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Player Hit Marker Widget not assigned to UTAD_UI_FPSCharacter"));
	}

	if (SplashScreenWidget)
	{
		SplashScreenInstance = CreateWidget<USplashScreen>(GetWorld(), SplashScreenWidget);
		SplashScreenInstance->AddToViewport();
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Splash Screen Widget not assigned to UTAD_UI_FPSCharacter"));
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Splash Screen Widget not assigned to UTAD_UI_FPSCharacter"));
	}

	if (SkillTreeWidget)
	{
		SkillTreeInstance = CreateWidget<USkillTree>(GetWorld(), SkillTreeWidget);
		SkillTreeInstance->AddToViewport();
		SkillTreeInstance->Hide();
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Skill Tree Widget not assigned to UTAD_UI_FPSCharacter"));
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Skill Tree Widget not assigned to UTAD_UI_FPSCharacter"));
	}
}


void AUTAD_UI_FPSCharacter::Move(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D MovementVector = Value.Get<FVector2D>();


	if (Controller != nullptr)
	{
		// add movement 
		AddMovementInput(GetActorForwardVector(), MovementVector.Y);
		AddMovementInput(GetActorRightVector(), MovementVector.X);
	}

	
}

void AUTAD_UI_FPSCharacter::Look(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D LookAxisVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// add yaw and pitch input to controller
		AddControllerYawInput(LookAxisVector.X);
		AddControllerPitchInput(LookAxisVector.Y);
	}
}

void AUTAD_UI_FPSCharacter::OpenSkillTreeMenu(const FInputActionValue& Value)
{
	if (SkillTreeInstance->IsVisible())
	{
		SkillTreeInstance->Hide();
	}
	else
	{
		SkillTreeInstance->Show();
	}
}

void AUTAD_UI_FPSCharacter::SetHealth(int NewHealth)
{
	int ClampedNewHealth = FMath::Clamp(NewHealth, 0, MaxHealth);
	if (ClampedNewHealth != Health)
	{
		if (NewHealth < Health && PlayerHitMarkerInstance)
		{

			PlayerHitMarkerInstance->Show();
		}
		Health = ClampedNewHealth;
		OnHealthChanged.ExecuteIfBound(Health, MaxHealth);


		if (Health <= 0 && GameOverWidget)
		{
			GameOverInstance = CreateWidget<UGameOver>(GetWorld(), GameOverWidget);
			GameOverInstance->AddToViewport();
			GameOverInstance->Show();
		}				

	}
}

int AUTAD_UI_FPSCharacter::GetHealth()
{
	return Health;
}

void AUTAD_UI_FPSCharacter::SetMaxHealth(int NewMaxHealth)
{
	MaxHealth = FMath::Max(0, NewMaxHealth);
}

int AUTAD_UI_FPSCharacter::GetMaxHealth()
{
	return MaxHealth;
}

void AUTAD_UI_FPSCharacter::SetHasRifle(bool bNewHasRifle)
{
	bHasRifle = bNewHasRifle;
	PlayerHUDInstance->ShowAll();
	OnTotalBulletChanged.ExecuteIfBound(TotalBullets);
	AttachedWeaponComponent->OnCurrentNumBulletsChanged.ExecuteIfBound(AttachedWeaponComponent->GetCurrentNumBullets());

}

bool AUTAD_UI_FPSCharacter::GetHasRifle()
{
	return bHasRifle;
}

void AUTAD_UI_FPSCharacter::SetTotalBullets(int NewTotalBullets)
{
	TotalBullets = NewTotalBullets;
	OnTotalBulletChanged.ExecuteIfBound(TotalBullets);
}

int AUTAD_UI_FPSCharacter::GetTotalBullets()
{
	return TotalBullets;
}

void AUTAD_UI_FPSCharacter::AddBullets(int Bullets)
{
	TotalBullets += Bullets;
}

void AUTAD_UI_FPSCharacter::SetAttachedWeaponComponent(UTP_WeaponComponent* WeaponComponent)
{
	AttachedWeaponComponent = WeaponComponent;
}
