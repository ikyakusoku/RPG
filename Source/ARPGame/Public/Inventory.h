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

	//��¼�µ�һ��Ϊ�յĸ��ӵ�λ�ã�ÿ�������Ʒ���ǶԸø��Ӵ�������
	int firstNull{};


	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<UInventoryWidget> inventoryUIClass;
	//��Ӧ�Ĵ洢�����
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI", meta = (AllowPrivateAccess = "true"))
	UInventoryWidget* inventoryUIInstance;

public:
	void SetUI(UInventoryWidget* _inventoryUI);
	//����item
	UFUNCTION(BlueprintCallable,Category="InventoryFunc")
	void AddItem(AItem* _item_toAdd);

	//ɾ��item
	UFUNCTION(BlueprintCallable, Category = "InventoryFunc")
	void DeleteItem(AItem* _item_toDelete);

	//����/������Ʒ��
	void Sort();

	UFUNCTION(BlueprintCallable, Category = "InventoryFunc")
	UInventoryWidget* GetUI();
};
