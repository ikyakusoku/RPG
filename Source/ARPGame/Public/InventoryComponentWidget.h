// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "InventoryComponentWidget.generated.h"

/**
 * 
 */
UCLASS()
class ARPGAME_API UInventoryComponentWidget : public UUserWidget
{
	GENERATED_BODY()


protected:
#pragma region inventoryUI
	//UPROPERTY(EditDefaultsOnly,BlueprintReadWrite,Category="Inv_Component", meta = (AllowPrivateAccess = "true"))
	//TSubclassOf<class UInventoryWidget> weaponUIClass;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Inv_Component", meta = (AllowPrivateAccess = "true", BindWidget))
	class UInventoryWidget* weaponUIInstance;

	//UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Inv_Component", meta = (AllowPrivateAccess = "true"))
	//TSubclassOf<class UInventoryWidget> propUIClass;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Inv_Component", meta = (AllowPrivateAccess = "true", BindWidget))
	class UInventoryWidget* propUIInstance;

	//UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Inv_Component", meta = (AllowPrivateAccess = "true"))
	//TSubclassOf<class UInventoryWidget> taskPropUIClass;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Inv_Component", meta = (AllowPrivateAccess = "true", BindWidget))
	class UInventoryWidget* taskPropUIInstance;

public:
	UFUNCTION(BlueprintCallable, Category = "Inv_Component")
		class UInventoryWidget* GetWeaponUIRef();

	UFUNCTION(BlueprintCallable, Category = "Inv_Component")
		class UInventoryWidget* GetPropUIRef();

	UFUNCTION(BlueprintCallable, Category = "Inv_Component")
		class UInventoryWidget* GetTaskPropUIRef();

#pragma endregion inventoryUI

public:
	//UUserWidget不存在默认构造函数，如果想实现类似的功能可以使用NativeConstruct
	void NativeConstruct() override;



};
