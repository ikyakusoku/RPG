// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Item.generated.h"


UCLASS()
class ARPGAME_API AItem : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AItem();

	AItem(class AStorableItem* _storable);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:
	

#pragma region UISetting
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<UUserWidget> itemUIClass;
	//��ƷUI
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = ItemProperty, meta = (AllowPrivateAccess = "true"))
	UUserWidget* itemUI;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<UUserWidget> itemListUIClass;
	//��Ʒ��ִ�в���UI
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = ItemProperty, meta = (AllowPrivateAccess = "true"))
	UUserWidget* itemListUI;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<UUserWidget> descriptionUIClass;
	//��Ʒ����UI
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = ItemProperty, meta = (AllowPrivateAccess = "true"))
	UUserWidget* descriptionUI;

	UFUNCTION(BlueprintCallable, Category = "ItemFunc")
	UUserWidget* GetUI();

#pragma endregion UISetting
};
