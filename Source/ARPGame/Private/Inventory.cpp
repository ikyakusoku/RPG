// Fill out your copyright notice in the Description page of Project Settings.


#include "Inventory.h"
#include "Components/WidgetComponent.h"

// Sets default values
AInventory::AInventory()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	//��ʼ������
	itemArray.SetNum(inventorySize);
	firstNull = 0;
	
	//UI
	inventoryUIInstance = CreateWidget(GetWorld(),inventoryUIClass);
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

void AInventory::AddItem(AItem* _item_toAdd)
{
	GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Blue, FString::Printf(TEXT("addItem")));
	//��������Ѵ�����
	if (firstNull >= itemArray.Num()) {
		GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Blue, FString::Printf(TEXT("Backpack full")));
		return;
	}

	//δ������
	itemArray[firstNull++] = _item_toAdd;

	
	
}

void AInventory::DeleteItem(AItem* _item_toDelete)
{
	GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Blue, FString::Printf(TEXT("deleteItem")));
}

void AInventory::Sort()
{
	GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Blue, FString::Printf(TEXT("sort")));
}
