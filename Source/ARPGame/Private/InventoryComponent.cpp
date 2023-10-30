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
	//丑陋
	inventoryComponentUI = CreateWidget<UInventoryComponentWidget>(GetWorld(), inventoryComponentUIClass);
	//-----------初始化inventoryArray--------------------
	FTransform defaultLocation;
	//初始化武器inventory
	AInventory* weaponInv = GetWorld()->SpawnActor<AInventory>(AInventory::StaticClass());
	//初始化inventoryUI
	UInventoryWidget* weaponInvUI = inventoryComponentUI->GetWeaponUIRef();
	weaponInv->SetUI(weaponInvUI);
	inventoryArray.Push(weaponInv);

	//初始化道具inventory
	AInventory* propInv = GetWorld()->SpawnActor<AInventory>(AInventory::StaticClass());
	//初始化inventoryUI
	UInventoryWidget* propInvUI = inventoryComponentUI->GetPropUIRef();
	propInv->SetUI(propInvUI);
	inventoryArray.Push(propInv);

	//初始化任务道具inventory
	AInventory* taskPropInv = GetWorld()->SpawnActor<AInventory>(AInventory::StaticClass());
	//初始化inventoryUI
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

	//组件UI加载成功
	APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	if (inventoryComponentUI->IsInViewport()) {
		//设置输入模式为游戏
		PlayerController->bShowMouseCursor = false;
		PlayerController->SetInputMode(FInputModeGameOnly());

		Close();
	}
	else {
		Open();

		//设置输入模式为游戏和 UI
		FInputModeGameAndUI InputMode;
		PlayerController->SetInputMode(InputMode);
		//显示光标
		PlayerController->bShowMouseCursor = true;
	}
}

void UInventoryComponent::AddItemToInventory(AItem* _item_toAdd)
{
	//copy多份?
	for (auto& inventoryPtr : inventoryArray) {
		GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Blue, FString::Printf(TEXT("additem")));
		inventoryPtr->GetUI()->AddItem(GetWorld()->SpawnActor<AItem>(_item_toAdd->GetClass()));
	}
}
