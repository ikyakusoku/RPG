// Fill out your copyright notice in the Description page of Project Settings.


#include "InventoryComponent.h"
#include "Kismet/GameplayStatics.h"

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

}


// Called when the game starts
void UInventoryComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	inventoryComponentUI = CreateWidget(GetWorld(), inventoryComponentUIClass);
	
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
