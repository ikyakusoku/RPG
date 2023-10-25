// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "DetectionRangeComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ARPGAME_API UDetectionRangeComponent : public USceneComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UDetectionRangeComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "detect", meta = (AllowPrivateAccess = "true"))
	int extraRange;

	//Բ���巶Χ��z��ΧΪ��������������� +��pawn�ĸ߶�+actor���box�ĸ߶ȣ�/2+extraRange ~ �������������-actor���box�ĸ߶�/2-extraRange/2��
	//xy��ΧΪpawn��actor���ĵľ���+extraRange
	//��ü����ж�actor�ο�������mesh���Ļ��������ط����жϡ�
	UFUNCTION(BlueprintCallable, Category = "detect", meta = (AllowPrivateAccess = "true"))
	bool DetectPawnInRange();

	
	
};
