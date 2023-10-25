// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SqlDBActor.generated.h"

UCLASS()
class ARPGAME_API ASqlDBActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASqlDBActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:
	//�������ӡ��β�ΪGames�ļ����µ�·�����磺"Content/DB/MonsterCard.db"
	UFUNCTION(BlueprintCallable, Category = "DBConnection,BlueprintFunc")
	bool OpenDB(const FString& path);
	//�ر�����
	UFUNCTION(BlueprintCallable, Category = "DBConnection,BlueprintFunc")
	void CloseDB();

private:
	class FSQLiteDatabaseConnection* db;
};
