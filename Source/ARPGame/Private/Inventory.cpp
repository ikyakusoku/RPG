// Fill out your copyright notice in the Description page of Project Settings.


#include "Inventory.h"
#include "Components/WidgetComponent.h"

// Sets default values
AInventory::AInventory()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	//初始化数组
	itemArray.SetNum(inventorySize);
	firstNull = 0;
	////UI
	//if (inventoryUIClass.Get()) {
	//	inventoryUIInstance = Cast<UInventoryWidget>(CreateWidget(GetWorld(), inventoryUIClass));
	//}
	
}

// Called when the game starts or when spawned
void AInventory::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AInventory::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AInventory::SetUI(UInventoryWidget* _inventoryUI)
{
	if (_inventoryUI) {
		GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Blue, FString::Printf(TEXT("SetUI.")));
		inventoryUIInstance = _inventoryUI;
		_inventoryUI->SetImpl(this);
	}
}

void AInventory::AddItem(AItem* _item_toAdd)
{
	GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Blue, FString::Printf(TEXT("addItem()")));
	//如果背包已达上限
	if (firstNull >= itemArray.Num()) {
		GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Blue, FString::Printf(TEXT("Backpack full")));
		return;
	}
	//未达上限
	itemArray[firstNull++] = _item_toAdd;
	GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Blue, FString::Printf(TEXT("array size: %d"),firstNull));
}

void AInventory::DeleteItem(AItem* _item_toDelete)
{
	GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Blue, FString::Printf(TEXT("deleteItem")));
}

void AInventory::Sort()
{
	GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Blue, FString::Printf(TEXT("sort")));
}

UInventoryWidget* AInventory::GetUI()
{
	if (inventoryUIInstance != nullptr) {
		GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Blue, FString::Printf(TEXT("inventory.GetUI")));
		return inventoryUIInstance;
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Blue, FString::Printf(TEXT("no inventoryUIInstance")));
		return inventoryUIInstance;
	}
}

