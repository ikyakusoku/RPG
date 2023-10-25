// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "InteractInterface.h"
#include "DetectionRangeComponent.h"
#include "Kismet/GameplayStatics.h"
#include "StorableItem.generated.h"


UCLASS()
class ARPGAME_API AStorableItem : public AActor,public IInteractInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AStorableItem();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = ItemProperty, meta = (AllowPrivateAccess = "true"))
	int itemID;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = ItemProperty, meta = (AllowPrivateAccess = "true"))
	FName itemName;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = ItemProperty, meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* mesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = ItemProperty, meta = (AllowPrivateAccess = "true"))
	UDetectionRangeComponent* detectComp;

	virtual void Interact() override { UE_LOG(LogTemp,Warning,TEXT("Store Item %d"),itemID) };


	//�ж�����ʰȡ���Ҿ�������Ļ��ͼӵ���ɫ�����ʰȡ��Ʒ�У�ע������������UDetectionRangeComponent��,û�ŵ�UDetectionRangeComponent�У�
	//�ǲ�ϣ��UDetectionRangeComponentֻ����ʰȡ�Ĺ��ܣ����ļ��������������ط�
	//���������playercharacter�࣬�������е��
	UFUNCTION(BlueprintCallable, Category = "Pickup", meta = (AllowPrivateAccess = "true"))
	void NortifyPlayerCharactertoPickup();
};
