// Fill out your copyright notice in the Description page of Project Settings.


#include "NetworkGameInstance.h"

#include "OnlineSubsystem.h"
#include "Kismet/GameplayStatics.h"
#include "OnlineSessionSettings.h"
#include "OnlineSubsystemUtils.h"
#include <Online/OnlineSessionNames.h>

void UNetworkGameInstance::Init()
{
	if (IOnlineSubsystem* SubSystem = IOnlineSubsystem::Get())
	{
		SessionInterface = SubSystem->GetSessionInterface();

		if (SessionInterface.IsValid()) {

			SessionInterface->OnCreateSessionCompleteDelegates.AddUObject(this, &UNetworkGameInstance::OnCreateSessionComplete);
			SessionInterface->OnFindSessionsCompleteDelegates.AddUObject(this, &UNetworkGameInstance::OnFindSessionsComplete);
			SessionInterface->OnJoinSessionCompleteDelegates.AddUObject(this, &UNetworkGameInstance::OnJoinSessionComplete);
		}
	}
}

void UNetworkGameInstance::CreateServer(int32 NumPublicConnections, bool IsLANMatch)
{
	
	FOnlineSessionSettings SessionSettings;
	SessionSettings.bAllowJoinInProgress = true;
	SessionSettings.bIsDedicated = false;
	SessionSettings.bIsLANMatch = IsLANMatch;
	SessionSettings.bShouldAdvertise = true;
	SessionSettings.bUsesPresence = true;
	SessionSettings.NumPublicConnections = NumPublicConnections;;
	
	SessionInterface->CreateSession(0, FName("Server"), SessionSettings);
}

void UNetworkGameInstance::OnCreateSessionComplete(FName ServerName, bool Succeeded)
{
	if (Succeeded)
	{
		GetWorld()->ServerTravel("/Game/ThirdPerson/Maps/ThirdPersonMap?listen");
	}
}

void UNetworkGameInstance::FindServer()
{
	ServerFound = false;
	FailedSearch = false;
	ServerSearch = MakeShareable(new FOnlineSessionSearch());
	ServerSearch->bIsLanQuery = true;
	ServerSearch->MaxSearchResults = 100;
	ServerSearch->QuerySettings.Set(SEARCH_PRESENCE, true, EOnlineComparisonOp::Equals);

	SessionInterface->FindSessions(0, ServerSearch.ToSharedRef());
}

void UNetworkGameInstance::OnFindSessionsComplete(bool Succeeded)
{
	if (Succeeded) {

		TArray<FOnlineSessionSearchResult> SearchResults = ServerSearch->SearchResults;
		FoundSearchNum = SearchResults.Num();

		if (FoundSearchNum)
		{
			FoundServer = SearchResults[0];
			ServerFound = true;
		}

		else {
			FailedSearch = true;
		}
	}
}

void UNetworkGameInstance::JoinServer()
{
    SessionInterface->JoinSession(0, "Server", FoundServer);
}

void UNetworkGameInstance::OnJoinSessionComplete(FName SessionName, EOnJoinSessionCompleteResult::Type Result)
{
	if (APlayerController* PController = UGameplayStatics::GetPlayerController(GetWorld(), 0))
	{
		FString JoinAddress;
		SessionInterface->GetResolvedConnectString(SessionName, JoinAddress);
		if (JoinAddress != "") {
			PController->ClientTravel(JoinAddress, ETravelType::TRAVEL_Absolute);
		}
	}
}