// Fill out your copyright notice in the Description page of Project Settings.


#include "InventoryWidget.h"
#include "Inventory.h"

//void UInventoryWidget::AddItem()
//{
//}

void UInventoryWidget::AddItem_Implementation(AItem* item_toAdd)
{

}

AInventory* UInventoryWidget::GetImpl()
{
	if (inventory != nullptr) {
		GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Black, FString::Printf(TEXT("GetImpl")));
	}
	return inventory;
}

void UInventoryWidget::SetImpl(AInventory* inv)
{
	inventory=inv;
}
