// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Item.h"
#include "InventoryWidget.h"
#include "Inventory.generated.h"

UCLASS()
class ARPGAME_API AInventory : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AInventory();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	TArray<AItem*> itemArray;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Array", meta = (AllowPrivateAccess = "true"))
	int inventorySize = 40;

	//记录下第一个为空的格子的位置，每次添加物品就是对该格子创建对象。
	int firstNull{};


	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<UInventoryWidget> inventoryUIClass;
	//对应的存储格界面
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI", meta = (AllowPrivateAccess = "true"))
	UInventoryWidget* inventoryUIInstance;

public:
	void SetUI(UInventoryWidget* _inventoryUI);
	//增加item
	UFUNCTION(BlueprintCallable,Category="InventoryFunc")
	void AddItem(AItem* _item_toAdd);

	//删除item
	UFUNCTION(BlueprintCallable, Category = "InventoryFunc")
	void DeleteItem(AItem* _item_toDelete);

	//排序/整理物品格
	void Sort();

	UFUNCTION(BlueprintCallable, Category = "InventoryFunc")
	UInventoryWidget* GetUI();
};
