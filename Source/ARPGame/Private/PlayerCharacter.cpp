// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/SpringArmComponent.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "StorableItem.h"
#include"Item.h"

// Sets default values
APlayerCharacter::APlayerCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// character������controller������ת�˶���
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	GetCharacterMovement()->MaxSwimSpeed = 450.f;
	GetCharacterMovement()->MaxWalkSpeed = 500.f;
	GetCharacterMovement()->JumpZVelocity = 500.f;
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f); // ...at this rotation rate

	// Create a camera boom (pulls in towards the player if there is a collision)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 400.0f; // The camera follows at this distance behind the character	
	CameraBoom->bUsePawnControlRotation = true; // Rotate the arm based on the controller


	//�����������
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("PlayerCharacterCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	FollowCamera->bUsePawnControlRotation = false;

	//���������ʼ��
	backPack = CreateDefaultSubobject<UInventoryComponent>(TEXT("BackPack"));
}

// Called when the game starts or when spawned
void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

//��ǿ����ϵͳ�� IMC��ע�ᣬ�Լ���ص�Action���ص������İ󶨡�
#pragma region EnhancedInputBind
	//ע��IMC��ֻ��ע���IMC�е�IA���ܱ�����ϵͳ�ҵ���
	//��Ҫ��IMCע�ᵽUEnhancedInputLocalPlayerSubsystem�С�
	if (APlayerController* PC = CastChecked<APlayerController>(GetController()))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PC->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(InputMappingContext, 100);
		}
	}

	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
	{
		if (IA_MoveForward)
		{
			EnhancedInputComponent->BindAction(IA_MoveForward, ETriggerEvent::Triggered, this, &APlayerCharacter::MoveForward);
		}

		if (IA_MoveRight)
		{
			EnhancedInputComponent->BindAction(IA_MoveRight, ETriggerEvent::Triggered, this, &APlayerCharacter::MoveRight);
		}

		if (IA_Turn)
		{
			EnhancedInputComponent->BindAction(IA_Turn, ETriggerEvent::Triggered, this, &APlayerCharacter::TurnAtRate);
		}

		if (IA_LookUp)
		{
			EnhancedInputComponent->BindAction(IA_LookUp, ETriggerEvent::Triggered, this, &APlayerCharacter::LookUpAtRate);
		}

		if (IA_Jump)
		{
			EnhancedInputComponent->BindAction(IA_Jump, ETriggerEvent::Started, this, &ACharacter::Jump);
			EnhancedInputComponent->BindAction(IA_Jump, ETriggerEvent::Completed, this, &ACharacter::StopJumping);
		}

		if (IA_OpenInventory) {
			//EnhancedInputComponent->BindAction(IA_OpenInventory, ETriggerEvent::Started, this, &APlayerCharacter::CheckInventoryComponent);
			EnhancedInputComponent->BindAction(IA_OpenInventory, ETriggerEvent::Completed, this, &APlayerCharacter::OpenInventoryUI);
		}

		if (IA_PickUp) {
			//EnhancedInputComponent->BindAction(IA_OpenInventory, ETriggerEvent::Started, this, &APlayerCharacter::CheckInventoryComponent);
			EnhancedInputComponent->BindAction(IA_PickUp, ETriggerEvent::Triggered, this, &APlayerCharacter::Pickup);
		}
	}
#pragma endregion EnhancedInputBind 

}

void APlayerCharacter::MoveForward(const FInputActionValue& InputActionValue)
{
	const FRotator rotation = GetController()->GetControlRotation();//controller��rotation ������ ���������µ�
	const FRotator yawRotation = FRotator(0, rotation.Yaw, 0);//ֻ��Ҫƫ����yaw�������ת����Ϊ��y����zox����ƽ�����ת��
	
	//Ϊʲô��x���ɼ�controllerĬ��������ռ��У���ǰ��Ϊx��������,Ҳ����1��0��0
	FVector direction = FRotationMatrix(yawRotation).GetUnitAxis(EAxis::X);
	AddMovementInput(direction, InputActionValue.GetMagnitude());
}

void APlayerCharacter::MoveRight(const FInputActionValue& InputActionValue)
{
	const FRotator rotation = GetController()->GetControlRotation();//controller��rotation ������ ���������µ�
	const FRotator yawRotation = FRotator(0, rotation.Yaw, 0);//ֻ��Ҫƫ����yaw�������ת����Ϊ��y����zox����ƽ�����ת��

	//Ϊʲô��x���ɼ�controllerĬ��������ռ��У���ǰ��Ϊx��������,Ҳ����1��0��0
	FVector direction = FRotationMatrix(yawRotation).GetUnitAxis(EAxis::Y);
	AddMovementInput(direction, InputActionValue.GetMagnitude());
}

void APlayerCharacter::TurnAtRate(const FInputActionValue& InputActionValue)
{

	AddControllerYawInput(InputActionValue.GetMagnitude());
}

void APlayerCharacter::LookUpAtRate(const FInputActionValue& InputActionValue)
{
	AddControllerPitchInput(InputActionValue.GetMagnitude());
	
}

void APlayerCharacter::OpenInventoryUI(const FInputActionValue& InputActionValue)
{
	if (CheckInventoryComponent())//�����������
	{
		backPack->InteractWithPlayer();
	}
	else {
		GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Blue, FString::Printf(TEXT("no inventoryComponent")));
	}
}

void APlayerCharacter::Pickup(const FInputActionValue& InputActionValue)
{
	//����inventoryComponent����Ĺ���
	if (backPack) {
		FTransform defaultLocation;
		AItem* item = GetWorld()->SpawnActor<AItem>(AItem::StaticClass());
		GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Blue, FString::Printf(TEXT("additemtoinventory.")));
		backPack->AddItemToInventory(item);
	}
	else {
		GEngine->AddOnScreenDebugMessage(1, 10, FColor::Blue, FString::Printf(TEXT("inventoryComponent hasn't load.")));
	}
}

void APlayerCharacter::SetNearestPickup(AStorableItem* newPickup, float _dist)
{
	if (_dist < dist) {
		nearestPickup = newPickup;
		dist = _dist;
	}
};




//void APlayerCharacter::MoveForward(const FInputActionValue& InputActionValue)
//{
//	LocomotionComp->MoveForward(InputActionValue.GetMagnitude());
//}
//
//void APlayerCharacter::MoveRight(const FInputActionValue& InputActionValue)
//{
//	LocomotionComp->MoveRight(InputActionValue.GetMagnitude());
//}
//
//void APlayerCharacter::TurnAtRate(const FInputActionValue& InputActionValue)
//{
//	LocomotionComp->TurnAtRate(InputActionValue.GetMagnitude());
//}
//
//void APlayerCharacter::LookUpAtRate(const FInputActionValue& InputActionValue)
//{
//	LocomotionComp->LookUpAtRate(InputActionValue.GetMagnitude());
//}
//
//void APlayerCharacter::OnJump(const FInputActionValue& InputActionValue)
//{
//	TryJump();
//}
//
//void APlayerCharacter::OnStopJumping(const FInputActionValue& InputActionValue)
//{
//}
