// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Components/WidgetComponent.h"
#include "InventoryComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ARPGAME_API UInventoryComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UInventoryComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
private:
	//�������ж�������񣬿��Էֱ�ֻ��ʾ�������ߵ��ߣ����߻����ʾ
	TArray<class AInventory*> inventoryArray;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<class UInventoryComponentWidget> inventoryComponentUIClass;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "UI", meta = (AllowPrivateAccess = "true"))
	class UInventoryComponentWidget* inventoryComponentUI;

private:
	void Open();
	void Close();
public:
	//�����򿪺͹ر�
	void InteractWithPlayer();
	//�������б�����additem()
	void AddItemToInventory(class AItem* _item_toAdd);
		
};
