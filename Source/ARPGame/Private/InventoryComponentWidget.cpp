// Fill out your copyright notice in the Description page of Project Settings.


#include "InventoryComponentWidget.h"
#include "InventoryWidget.h"

void UInventoryComponentWidget::NativeConstruct()
{
	//if (weaponUIClass.Get() == nullptr) {
	//	UE_LOG(LogTemp, Warning, TEXT("weapon inventory UI Class load wrong."))
	//}
	//else {
	//	weaponUIInstance = CreateWidget<UInventoryWidget>(GetWorld(), weaponUIClass);
	//}

	//if (propUIClass.Get() == nullptr) {
	//	UE_LOG(LogTemp, Warning, TEXT("prop inventory UI Class load wrong."))
	//}
	//else {
	//	propUIInstance = CreateWidget<UInventoryWidget>(GetWorld(), propUIClass);
	//}

	//if (taskPropUIClass.Get() == nullptr) {
	//	UE_LOG(LogTemp, Warning, TEXT("taskProp inventory UI Class load wrong."))
	//}
	//else {
	//	taskPropUIInstance = CreateWidget<UInventoryWidget>(GetWorld(), propUIClass);
	//}
}

UInventoryWidget* UInventoryComponentWidget::GetWeaponUIRef()
{
	return weaponUIInstance;
}

UInventoryWidget* UInventoryComponentWidget::GetPropUIRef()
{
	return propUIInstance;
}

UInventoryWidget* UInventoryComponentWidget::GetTaskPropUIRef()
{
	return taskPropUIInstance;
}
