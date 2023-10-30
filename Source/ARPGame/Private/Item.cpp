// Fill out your copyright notice in the Description page of Project Settings.


#include "Item.h"
#include"StorableItem.h"
#include "Components/WidgetComponent.h"

// Sets default values
AItem::AItem()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	ConstructorHelpers::FClassFinder<UUserWidget> itemUIHelper(TEXT("/Game/BluePrint/UI/BP_ItemWidget"));
	if (itemUIHelper.Succeeded()) {
		itemUIClass = itemUIHelper.Class;
	}
	itemUI = CreateWidget(GetWorld(), itemUIClass);
	
}

AItem::AItem(AStorableItem* _storable)
{
	PrimaryActorTick.bCanEverTick = true;

	ConstructorHelpers::FClassFinder<UUserWidget> itemUIHelper(TEXT("/Game/BluePrint/UI/BP_ItemWidget"));
	if (itemUIHelper.Succeeded()) {
		itemUIClass = itemUIHelper.Class;
	}
	itemUI->SetVisibility(ESlateVisibility::Visible);
}

// Called when the game starts or when spawned
void AItem::BeginPlay()
{
	Super::BeginPlay();
	GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Blue, FString::Printf(TEXT("%s"), *itemUIClass.Get()->GetName()));
	
	
}

// Called every frame
void AItem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

UUserWidget* AItem::GetUI()
{
	if (itemUI != nullptr) {
		GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Blue, FString::Printf(TEXT("Class:%s"), *this->GetClass()->GetName()));
		GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Blue, FString::Printf(TEXT("Class:%s"), *itemUI->GetClass()->GetName()));
	}
	else {
		GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Blue, FString::Printf(TEXT("itemUI nullptr.")));
	}
	return itemUI;
	
}

