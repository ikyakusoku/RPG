// Fill out your copyright notice in the Description page of Project Settings.


#include "InventoryComponent.h"
#include "Kismet/GameplayStatics.h"
#include"Inventory.h"
#include"InventoryComponentWidget.h"

// Sets default values for this component's properties
UInventoryComponent::UInventoryComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	//if (!inventoryComponentUI) {
	//	GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Blue, FString::Printf(TEXT("no inventoryComponentUI")));
	//}
	//ConstructorHelpers::FClassFinder<UUserWidget> UIFinder(TEXT("/Game/BluePrint/UI/BP_InventoryWidget.BP_InventoryWidget"));
	//if (UIFinder.Succeeded()) {
	//	inventoryComponentUIClass = UIFinder.Class;
	//}
	// ...
//#pragma region InitArray
//
//#pragma endregion InitArray
	//inventoryComponentUI = Cast<UInventoryComponentWidget>(CreateWidget(GetWorld(), inventoryComponentUIClass));
	
}


// Called when the game starts
void UInventoryComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	//��ª
	inventoryComponentUI = CreateWidget<UInventoryComponentWidget>(GetWorld(), inventoryComponentUIClass);
	//-----------��ʼ��inventoryArray--------------------
	FTransform defaultLocation;
	//��ʼ������inventory
	AInventory* weaponInv = GetWorld()->SpawnActor<AInventory>(AInventory::StaticClass());
	//��ʼ��inventoryUI
	UInventoryWidget* weaponInvUI = inventoryComponentUI->GetWeaponUIRef();
	weaponInv->SetUI(weaponInvUI);
	inventoryArray.Push(weaponInv);

	//��ʼ������inventory
	AInventory* propInv = GetWorld()->SpawnActor<AInventory>(AInventory::StaticClass());
	//��ʼ��inventoryUI
	UInventoryWidget* propInvUI = inventoryComponentUI->GetPropUIRef();
	propInv->SetUI(propInvUI);
	inventoryArray.Push(propInv);

	//��ʼ���������inventory
	AInventory* taskPropInv = GetWorld()->SpawnActor<AInventory>(AInventory::StaticClass());
	//��ʼ��inventoryUI
	UInventoryWidget* taskPropInvUI = inventoryComponentUI->GetTaskPropUIRef();
	taskPropInv->SetUI(taskPropInvUI);
	inventoryArray.Push(taskPropInv);
}


// Called every frame
void UInventoryComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UInventoryComponent::Open()
{
	inventoryComponentUI->AddToViewport();
}

void UInventoryComponent::Close()
{
	inventoryComponentUI->RemoveFromParent();
}

void UInventoryComponent::InteractWithPlayer()
{
	if (!inventoryComponentUI) {
		GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Blue, FString::Printf(TEXT("no inventoryComponentUI")));
		return;
	}

	//���UI���سɹ�
	APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	if (inventoryComponentUI->IsInViewport()) {
		//��������ģʽΪ��Ϸ
		PlayerController->bShowMouseCursor = false;
		PlayerController->SetInputMode(FInputModeGameOnly());

		Close();
	}
	else {
		Open();

		//��������ģʽΪ��Ϸ�� UI
		FInputModeGameAndUI InputMode;
		PlayerController->SetInputMode(InputMode);
		//��ʾ���
		PlayerController->bShowMouseCursor = true;
	}
}

void UInventoryComponent::AddItemToInventory(AItem* _item_toAdd)
{
	//copy���?
	for (auto& inventoryPtr : inventoryArray) {
		GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Blue, FString::Printf(TEXT("additem")));
		inventoryPtr->GetUI()->AddItem(GetWorld()->SpawnActor<AItem>(_item_toAdd->GetClass()));
	}
}
