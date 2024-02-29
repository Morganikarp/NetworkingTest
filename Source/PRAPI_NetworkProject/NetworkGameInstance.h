// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"

#include "Interfaces/OnlineSessionInterface.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "OnlineSessionSettings.h"

#include "NetworkGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class PRAPI_NETWORKPROJECT_API UNetworkGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite) int32 FoundSearchNum;
	UPROPERTY(EditAnywhere, BlueprintReadWrite) int32 BuildServerID;
	UPROPERTY(EditAnywhere, BlueprintReadWrite) int32 FoundServerID;
	UPROPERTY(EditAnywhere, BlueprintReadWrite) FString DeclaredServerName;
	UPROPERTY(EditAnywhere, BlueprintReadWrite) bool ServerFound;
	UPROPERTY(EditAnywhere, BlueprintReadWrite) bool FailedSearch;
	
	IOnlineSessionPtr SessionInterface;

	TSharedPtr<FOnlineSessionSearch> ServerSearch;

	FOnlineSessionSearchResult FoundServer;

	virtual void Init() override;


	UFUNCTION(BlueprintCallable) void CreateServer(int32 NumPublicConnections, bool IsLANMatch);
	virtual void OnCreateSessionComplete(FName ServerName, bool Succeeded);

	UFUNCTION(BlueprintCallable) void FindServer();
	virtual void OnFindSessionsComplete(bool Succeeded);


	UFUNCTION(BlueprintCallable) void JoinServer();
	virtual void OnJoinSessionComplete(FName SessionName, EOnJoinSessionCompleteResult::Type Result);
};
