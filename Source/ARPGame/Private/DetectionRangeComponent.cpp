// Fill out your copyright notice in the Description page of Project Settings.


#include "DetectionRangeComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values for this component's properties
UDetectionRangeComponent::UDetectionRangeComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UDetectionRangeComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UDetectionRangeComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	DetectPawnInRange();
	// ...
}

bool UDetectionRangeComponent::DetectPawnInRange()
{
	//GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Red, FString::Printf(TEXT("start detect")));
	AActor* ownerActor = GetOwner();
	FBox actorBoundingBox = ownerActor->GetComponentsBoundingBox();
	FVector BBCenter = actorBoundingBox.GetCenter();
	//GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Green, FString::Printf(TEXT("BBCenter: %f"), BBCenter.Z));
	//GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Green, FString::Printf(TEXT("actorcenter: %f"), ownerActor->GetActorLocation().Z));
	double diagonalDistance = FVector::Dist(BBCenter, actorBoundingBox.Max);//对角线距离
	//GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Green, FString::Printf(TEXT("diagonalDistance: %f"),diagonalDistance));
	double actorZDistance = actorBoundingBox.GetSize().Z;
	//GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Green, FString::Printf(TEXT("actorZDistance: %f"), actorZDistance));

	APlayerController* currentController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	APawn* currentPawn = currentController->GetPawn();
	FVector pawnLocation{};
	if (currentPawn) {
		pawnLocation = currentPawn->GetActorLocation();
	}
	double pawnZDistance = currentPawn->GetComponentsBoundingBox().GetSize().Z;
	//GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Green, FString::Printf(TEXT("pawnLocation: %f,%f,%f"), pawnLocation.X, pawnLocation.Y, pawnLocation.Z));
	//z范围，pawn的一半高度，加上圆柱体的一半高度
	//高度范围pawn的底部只要在圆柱体范围内就可以了
	double zRangeMax = (pawnZDistance + actorZDistance) / 2 + BBCenter.Z+ extraRange;
	double zRangeMin = BBCenter.Z - extraRange / 2 - actorZDistance / 2;

	//GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Green, FString::Printf(TEXT("zRangeMax: %f"), zRangeMax));
	//GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Green, FString::Printf(TEXT("zRangeMin: %f"), zRangeMin));
	if (pawnLocation.Z<zRangeMax && pawnLocation.Z>zRangeMin) {
		FVector2D pawn2DLoc = FVector2D(pawnLocation.X, pawnLocation.Y);
		FVector2D actor2DLoc = FVector2D(BBCenter.X, BBCenter.Y);
		if (FVector2D::Distance(pawn2DLoc, actor2DLoc)<diagonalDistance+extraRange) {
			//GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Blue, FString::Printf(TEXT("detect pawn")));
			return true;
		}
	}
	return false;
}

