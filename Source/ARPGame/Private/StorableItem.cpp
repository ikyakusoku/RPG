// Fill out your copyright notice in the Description page of Project Settings.


#include "StorableItem.h"
#include "PlayerCharacter.h"

// Sets default values
AStorableItem::AStorableItem()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	detectComp = CreateDefaultSubobject<UDetectionRangeComponent>(TEXT("DetectComponent"));

	mesh->SetupAttachment(RootComponent);
	detectComp->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void AStorableItem::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AStorableItem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	NortifyPlayerCharactertoPickup();
}

void AStorableItem::NortifyPlayerCharactertoPickup()
{
	if (detectComp->DetectPawnInRange()) {
		//获取玩家位置
		APlayerController* currentController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
		APawn* currentPawn = currentController->GetPawn();
		FVector pawnLocation{};
		if (currentPawn) {
			pawnLocation = currentPawn->GetActorLocation();
		}

		//获取物品自身位置并计算距离
		float distance = FVector::Distance(GetActorLocation(), pawnLocation);

		//交给playercharacter
		APlayerCharacter* pc = Cast<APlayerCharacter>(currentPawn);
		pc->SetNearestPickup(this, distance);
	}
}
