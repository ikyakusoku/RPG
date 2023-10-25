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

	//圆柱体范围：z范围为：外包正方体中心 +（pawn的高度+actor外包box的高度）/2+extraRange ~ 外包正方体中心-actor外包box的高度/2-extraRange/2；
	//xy范围为pawn到actor中心的距离+extraRange
	//最好加上判定actor参考坐标是mesh中心还是其他地方来判断。
	UFUNCTION(BlueprintCallable, Category = "detect", meta = (AllowPrivateAccess = "true"))
	bool DetectPawnInRange();

	
	
};
