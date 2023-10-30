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
	
//�����Ʒ
public:
	//������������ͼ��ʵ�֣������Ʒ,��Ҫ����AddItem_Implementation(AItem* item_toAdd)
	UFUNCTION(BlueprintNativeEvent)
	void AddItem(AItem* item_toAdd);

	//����inventoryָ��
	UFUNCTION(BlueprintCallable)
	class AInventory* GetImpl();

	//����inventoryָ��
	UFUNCTION(BlueprintCallable)
	void SetImpl(class AInventory* inv);

protected:
	//��inventory����ڹ���,ͨ���˷�����ӿ��޸��ڲ�����
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	class AInventory* inventory;

public:

};
