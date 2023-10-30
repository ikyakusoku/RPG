// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Item.h"
#include "InventoryWidget.generated.h"

/**
 * 
 */
UCLASS()
class ARPGAME_API UInventoryWidget : public UUserWidget
{
	GENERATED_BODY()
	
//添加物品
public:
	//交给子类在蓝图中实现，添加物品,需要定义AddItem_Implementation(AItem* item_toAdd)
	UFUNCTION(BlueprintNativeEvent)
	void AddItem(AItem* item_toAdd);

	//返回inventory指针
	UFUNCTION(BlueprintCallable)
	class AInventory* GetImpl();

	//返回inventory指针
	UFUNCTION(BlueprintCallable)
	void SetImpl(class AInventory* inv);

protected:
	//与inventory类存在关联,通过此访问其接口修改内部数据
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	class AInventory* inventory;

public:

};
