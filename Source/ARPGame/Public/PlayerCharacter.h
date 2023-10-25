// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputActionValue.h"
#include "InventoryComponent.h"
#include "PlayerCharacter.generated.h"

UCLASS()
class ARPGAME_API APlayerCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	APlayerCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:

//���������
#pragma region CameraSetting
	/** Camera boom positioning the camera behind the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* FollowCamera;
#pragma endregion CameraSetting

//����������
#pragma region InventorySetting
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	UInventoryComponent* backPack;
#pragma endregion InventorySetting

//��ǿ����ϵͳ���
#pragma region EnhancedInput

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "EnhancedInput", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UInputMappingContext> InputMappingContext;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "EnhancedInput|Action", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UInputAction> IA_MoveForward;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "EnhancedInput|Action", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UInputAction> IA_MoveRight;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "EnhancedInput|Action", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UInputAction> IA_Turn;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "EnhancedInput|Action", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UInputAction> IA_LookUp;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "EnhancedInput|Action", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UInputAction> IA_Jump;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "EnhancedInput|Action", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UInputAction> IA_OpenInventory;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "EnhancedInput|Action", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UInputAction> IA_PickUp;

#pragma endregion EnhancedInput

	void MoveForward(const FInputActionValue& InputActionValue);
	void MoveRight(const FInputActionValue& InputActionValue);
	void TurnAtRate(const FInputActionValue& InputActionValue);
	void LookUpAtRate(const FInputActionValue& InputActionValue);

	bool CheckInventoryComponent() {
		if (!backPack) {
			return false;
		}
		return true;
	}

	void OpenInventoryUI(const FInputActionValue& InputActionValue);

	//��Eʰȡ��������inventoryComponent�Ĺ�����������뱳����Ȼ����������ʧ��
	void Pickup(const FInputActionValue& InputActionValue);

//��ɫ����
#pragma region attribute
private:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Attribute", meta = (AllowPrivateAccess = "true"))
	int atkVal;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Attribute", meta = (AllowPrivateAccess = "true"))
	int defVal;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Attribute", meta = (AllowPrivateAccess = "true"))
	int hpVal;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Attribute", meta = (AllowPrivateAccess = "true"))
	int mpVal;
#pragma endregion Attribute

//ʰȡ���
#pragma region AboutPickup
private:
	class AStorableItem* nearestPickup{};
	//��ǰ�����ʰȡ��Ʒ����ҵľ���
	float dist{};
public:
	void SetNearestPickup(AStorableItem* newPickup, float _dist);//���������ʰȡ��Ʒ������ʰȡ��Ʒ���á�
#pragma endregion AboutPickup

};
