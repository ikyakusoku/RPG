// Fill out your copyright notice in the Description page of Project Settings.


#include "SqlDBActor.h"
#include "Engine/DataTable.h"
#include "SQLiteDatabaseConnection.h"

// Sets default values
ASqlDBActor::ASqlDBActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
}

// Called when the game starts or when spawned
void ASqlDBActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASqlDBActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

bool ASqlDBActor::OpenDB(const FString& path)
{
	GetClass();
	FString dbPath = FPaths::ProjectUserDir() + path;
	UE_LOG(LogTemp, Warning, TEXT("Sqlite Connection Start"));

	db = new FSQLiteDatabaseConnection();
	if (!db)
	{
		UE_LOG(LogTemp, Warning, TEXT("FSQLiteDatabaseConnection creating failed"));
		return false;
	}

	//UE_LOG(LogTemp, Warning, TEXT("Wrong"));
	if (!db->Open(*dbPath, nullptr, nullptr))
	{
		UE_LOG(LogTemp, Warning, TEXT("Sqlite Connection Failed"));
		return false;
	}
	UE_LOG(LogTemp, Warning, TEXT("Sqlite Connection Succeed"));
	return true;
}

void ASqlDBActor::CloseDB()
{
	db->Close();
	delete db;
}

