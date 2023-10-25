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

//相机相关组件
#pragma region CameraSetting
	/** Camera boom positioning the camera behind the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* FollowCamera;
#pragma endregion CameraSetting

//背包相关组件
#pragma region InventorySetting
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	UInventoryComponent* backPack;
#pragma endregion InventorySetting

//增强输入系统相关
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

	//按E拾取，并调用inventoryComponent的功能让物体加入背包，然后让物体消失。
	void Pickup(const FInputActionValue& InputActionValue);

//角色属性
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

//拾取相关
#pragma region AboutPickup
private:
	class AStorableItem* nearestPickup{};
	//当前最近可拾取物品到玩家的距离
	float dist{};
public:
	void SetNearestPickup(AStorableItem* newPickup, float _dist);//设置最近可拾取物品，被可拾取物品调用。
#pragma endregion AboutPickup

};
