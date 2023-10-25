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

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	//物品UI
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = ItemProperty, meta = (AllowPrivateAccess = "true"))
	UUserWidget* itemUI;

	//物品可执行操作UI
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = ItemProperty, meta = (AllowPrivateAccess = "true"))
	UUserWidget* itemListUI;

	//物品详情UI
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = ItemProperty, meta = (AllowPrivateAccess = "true"))
	UUserWidget* descriptionUI;
};
