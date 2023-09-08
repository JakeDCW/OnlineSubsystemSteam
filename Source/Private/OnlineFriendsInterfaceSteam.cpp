// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#include "OnlineFriendsInterfaceSteam.h"
#include "OnlineSubsystemSteam.h"
#include "OnlineSubsystemSteamTypes.h"
#include "Engine/Texture2D.h"
#include "Misc/ScopeLock.h"

#define MAX_CACHED_AVATARS (64)

// FOnlineFriendSteam
FOnlineFriendSteam::FOnlineFriendSteam(const CSteamID& InUserId)
	: UserId(new FUniqueNetIdSteam(InUserId))
{
}

TSharedRef<const FUniqueNetId> FOnlineFriendSteam::GetUserId() const
{
	return UserId;
}

FString FOnlineFriendSteam::GetRealName() const
{
	FString Result;
	GetAccountData(TEXT("nickname"),Result);
	return Result;
}

FString FOnlineFriendSteam::GetDisplayName(const FString& Platform) const
{
	FString Result;
	GetAccountData(TEXT("nickname"),Result);
	return Result;
}

bool FOnlineFriendSteam::GetUserAttribute(const FString& AttrName, FString& OutAttrValue) const
{
	return GetAccountData(AttrName,OutAttrValue);
}

EInviteStatus::Type FOnlineFriendSteam::GetInviteStatus() const
{
	return EInviteStatus::Accepted;
}

const FOnlineUserPresence& FOnlineFriendSteam::GetPresence() const
{
	return Presence;
}

// FOnlineFriendsStream

FOnlineFriendsSteam::FOnlineFriendsSteam(FOnlineSubsystemSteam* InSteamSubsystem) :
	SteamSubsystem(InSteamSubsystem),
	SteamUserPtr(NULL),
	SteamFriendsPtr(NULL)
{
	check(SteamSubsystem);
	SteamUserPtr = SteamUser();
	SteamFriendsPtr = SteamFriends();
}

bool FOnlineFriendsSteam::ReadFriendsList(int32 LocalUserNum, const FString& ListName, const FOnReadFriendsListComplete& Delegate /*= FOnReadFriendsListComplete()*/)
{
	FString ErrorStr;
	if (LocalUserNum < MAX_LOCAL_PLAYERS &&
		SteamUserPtr != NULL &&
		SteamUserPtr->BLoggedOn() &&
		SteamFriendsPtr != NULL)
	{
		SteamSubsystem->QueueAsyncTask(new FOnlineAsyncTaskSteamReadFriendsList(this, LocalUserNum, ListName, Delegate));
	}
	else
	{
		ErrorStr = FString::Printf(TEXT("No valid LocalUserNum=%d"), LocalUserNum);
	}
	if (!ErrorStr.IsEmpty())
	{
		Delegate.ExecuteIfBound(LocalUserNum, false, ListName, ErrorStr);
		return false;
	}
	return true;
}

bool FOnlineFriendsSteam::DeleteFriendsList(int32 LocalUserNum, const FString& ListName, const FOnDeleteFriendsListComplete& Delegate /*= FOnDeleteFriendsListComplete()*/)
{
	Delegate.ExecuteIfBound(LocalUserNum, false, ListName, FString(TEXT("DeleteFriendsList() is not supported")));
	return false;
}

bool FOnlineFriendsSteam::SendInvite(int32 LocalUserNum, const FUniqueNetId& FriendId, const FString& ListName, const FOnSendInviteComplete& Delegate /*= FOnSendInviteComplete()*/)
{
	Delegate.ExecuteIfBound(LocalUserNum, false, FriendId, ListName, FString(TEXT("SendInvite() is not supported")));
	return false;
}

bool FOnlineFriendsSteam::AcceptInvite(int32 LocalUserNum, const FUniqueNetId& FriendId, const FString& ListName, const FOnAcceptInviteComplete& Delegate /*= FOnAcceptInviteComplete()*/)
{
	Delegate.ExecuteIfBound(LocalUserNum, false, FriendId, ListName, FString(TEXT("AcceptInvite() is not supported")));
	return false;
}

bool FOnlineFriendsSteam::RejectInvite(int32 LocalUserNum, const FUniqueNetId& FriendId, const FString& ListName)
{
	TriggerOnRejectInviteCompleteDelegates(LocalUserNum, false, FriendId, ListName, FString(TEXT("RejectInvite() is not supported")));
	return false;
}

bool FOnlineFriendsSteam::DeleteFriend(int32 LocalUserNum, const FUniqueNetId& FriendId, const FString& ListName)
{
	TriggerOnDeleteFriendCompleteDelegates(LocalUserNum, false, FriendId, ListName, FString(TEXT("DeleteFriend() is not supported")));
	return false;
}

bool FOnlineFriendsSteam::GetFriendsList(int32 LocalUserNum, const FString& ListName, TArray< TSharedRef<FOnlineFriend> >& OutFriends)
{
	bool bResult = false;
	if (LocalUserNum < MAX_LOCAL_PLAYERS &&
		SteamUserPtr != NULL &&
		SteamUserPtr->BLoggedOn() &&
		SteamFriendsPtr != NULL)
	{
		FSteamFriendsList* FriendsList = FriendsLists.Find(LocalUserNum);
		if (FriendsList != NULL)
		{
			for (int32 FriendIdx=0; FriendIdx < FriendsList->Friends.Num(); FriendIdx++)
			{
				OutFriends.Add(FriendsList->Friends[FriendIdx]);
			}
			bResult = true;
		}
	}
	return bResult;
}

TSharedPtr<FOnlineFriend> FOnlineFriendsSteam::GetFriend(int32 LocalUserNum, const FUniqueNetId& FriendId, const FString& ListName)
{
	TSharedPtr<FOnlineFriend> Result;
	if (LocalUserNum < MAX_LOCAL_PLAYERS &&
		SteamUserPtr != NULL &&
		SteamUserPtr->BLoggedOn() &&
		SteamFriendsPtr != NULL)
	{
		FSteamFriendsList* FriendsList = FriendsLists.Find(LocalUserNum);
		if (FriendsList != NULL)
		{
			for (int32 FriendIdx=0; FriendIdx < FriendsList->Friends.Num(); FriendIdx++)
			{
				if (*FriendsList->Friends[FriendIdx]->GetUserId() == FriendId)
				{
					Result = FriendsList->Friends[FriendIdx];
					break;
				}
			}
		}
	}
	return Result;
}

bool FOnlineFriendsSteam::IsFriend(int32 LocalUserNum, const FUniqueNetId& FriendId, const FString& ListName)
{
	bool bIsFriend = false;
	if (LocalUserNum < MAX_LOCAL_PLAYERS &&
		SteamUserPtr != NULL &&
		SteamUserPtr->BLoggedOn() &&
		SteamFriendsPtr != NULL)
	{
		// Ask Steam if they are on the buddy list
		const CSteamID SteamPlayerId(*(uint64*)FriendId.GetBytes());
		bIsFriend = SteamFriendsPtr->GetFriendRelationship(SteamPlayerId) == k_EFriendRelationshipFriend;
	}
	return bIsFriend;
}

bool FOnlineFriendsSteam::QueryRecentPlayers(const FUniqueNetId& UserId, const FString& Namespace)
{
	UE_LOG_ONLINE_FRIEND(Verbose, TEXT("FOnlineFriendsSteam::QueryRecentPlayers()"));

	TriggerOnQueryRecentPlayersCompleteDelegates(UserId, Namespace, false, TEXT("not implemented"));

	return false;
}

bool FOnlineFriendsSteam::GetRecentPlayers(const FUniqueNetId& UserId, const FString& Namespace, TArray< TSharedRef<FOnlineRecentPlayer> >& OutRecentPlayers)
{
	return false;
}

void FOnlineFriendsSteam::DumpRecentPlayers() const
{
}

bool FOnlineFriendsSteam::BlockPlayer(int32 LocalUserNum, const FUniqueNetId& PlayerId)
{
	return false;
}

bool FOnlineFriendsSteam::UnblockPlayer(int32 LocalUserNum, const FUniqueNetId& PlayerId)
{
	return false;
}

bool FOnlineFriendsSteam::QueryBlockedPlayers(const FUniqueNetId& UserId)
{
	return false;
}

bool FOnlineFriendsSteam::GetBlockedPlayers(const FUniqueNetId& UserId, TArray< TSharedRef<FOnlineBlockedPlayer> >& OutBlockedPlayers)
{
	return false;
}

void FOnlineFriendsSteam::DumpBlockedPlayers() const
{
}

bool FOnlineAsyncTaskSteamReadFriendsList::CanAddUserToList(bool bIsOnline, bool bIsPlayingThisGame, bool bIsPlayingGameInSession)
{
	switch (FriendsListFilter)
	{
		default:
		case EFriendsLists::Default:
			return true;
		case EFriendsLists::OnlinePlayers:
			return bIsOnline;
		case EFriendsLists::InGamePlayers:
			return bIsOnline && bIsPlayingThisGame;
		case EFriendsLists::InGameAndSessionPlayers:
			return bIsOnline && bIsPlayingThisGame && bIsPlayingGameInSession;
	}

	return false;
}

void FOnlineAsyncTaskSteamReadFriendsList::Finalize()
{
	FOnlineSubsystemSteam* SteamSubsystem = FriendsPtr->SteamSubsystem;
	ISteamFriends* SteamFriendsPtr = FriendsPtr->SteamFriendsPtr;
	FOnlineFriendsSteam::FSteamFriendsList& FriendsList = FriendsPtr->FriendsLists.FindOrAdd(LocalUserNum);

	const int32 NumFriends = SteamFriendsPtr->GetFriendCount(k_EFriendFlagImmediate);
	// Pre-size the array for minimal re-allocs
	FriendsList.Friends.Empty(NumFriends);
	// Loop through all the friends adding them one at a time
	for (int32 Index = 0; Index < NumFriends; Index++)
	{
		const CSteamID SteamPlayerId = SteamFriendsPtr->GetFriendByIndex(Index, k_EFriendFlagImmediate);
		const FString NickName(UTF8_TO_TCHAR(SteamFriendsPtr->GetFriendPersonaName(SteamPlayerId)));

		// Get this user's friend information so we can figure out if we can add them to our list.
		bool bInASession;
		FriendGameInfo_t FriendGameInfo;
		bool bIsPlayingAGame = SteamFriendsPtr->GetFriendGamePlayed(SteamPlayerId, &FriendGameInfo);
		bool bIsOnline = (SteamFriendsPtr->GetFriendPersonaState(SteamPlayerId) >= k_EPersonaStateOnline);
		bool bIsPlayingThisGame = (FriendGameInfo.m_gameID.AppID() == SteamSubsystem->GetSteamAppId());
		bool bHasConnectInformation = (SteamFriendsPtr->GetFriendRichPresence(SteamPlayerId, "connect") != nullptr);
		FString JoinablePresenceString = UTF8_TO_TCHAR(SteamFriendsPtr->GetFriendRichPresence(SteamPlayerId, "Joinable"));

		// Platforms can override joinability using the "Joinable", which overrides the default check
		// Remote friend is responsible for updating their presence to have the joinable status
		if (!JoinablePresenceString.IsEmpty())
		{
			bInASession = (JoinablePresenceString == TEXT("true"));
		}
		else
		{
			bInASession = bIsPlayingThisGame && bHasConnectInformation;
		}

		// Skip invalid entries and ones that do not fit our current filters.
		if (NickName.Len() > 0 && CanAddUserToList(bIsOnline, bIsPlayingThisGame, bInASession))
		{
			// Add to list
			TSharedRef<FOnlineFriendSteam> Friend(new FOnlineFriendSteam(SteamPlayerId));
			FriendsList.Friends.Add(Friend);

			// Now fill in the friend info
			Friend->AccountData.Add(TEXT("nickname"), NickName);
			Friend->Presence.Status.StatusStr = UTF8_TO_TCHAR(SteamFriendsPtr->GetFriendRichPresence(SteamPlayerId,"status"));
			Friend->Presence.bIsJoinable = bInASession;
			Friend->Presence.bIsOnline = bIsOnline;
			Friend->Presence.bIsPlaying = bIsPlayingAGame;
			Friend->Presence.bIsPlayingThisGame = bIsPlayingThisGame;

			switch (SteamFriendsPtr->GetFriendPersonaState(SteamPlayerId))
			{
				case k_EPersonaStateOffline:
					Friend->Presence.Status.State = EOnlinePresenceState::Offline;
					break;
				case k_EPersonaStateBusy:
					Friend->Presence.Status.State = EOnlinePresenceState::DoNotDisturb;
					break;
				case k_EPersonaStateAway:
					Friend->Presence.Status.State = EOnlinePresenceState::Away;
					break;
				case k_EPersonaStateSnooze:
					Friend->Presence.Status.State = EOnlinePresenceState::ExtendedAway;
					break;
				default:
					Friend->Presence.Status.State = EOnlinePresenceState::Online;
					break;
			}
			// Remote friend is responsible for updating their presence to have the voice flag
			FString VoicePresenceString = UTF8_TO_TCHAR(SteamFriendsPtr->GetFriendRichPresence(SteamPlayerId,"HasVoice"));
			// Determine if the user has voice support
			Friend->Presence.bHasVoiceSupport = VoicePresenceString == TEXT("true");
		}
	}
}

void FOnlineAsyncTaskSteamReadFriendsList::TriggerDelegates(void)
{
	FOnlineAsyncTask::TriggerDelegates();

	Delegate.ExecuteIfBound(LocalUserNum, true, EFriendsLists::ToString(FriendsListFilter), FString());
}

void FOnlineFriendsSteam::ShowInviteFriendsDialog(const FUniqueNetId& LobbyId)
{
	if (SteamSubsystem != nullptr && SteamSubsystem->IsEnabled())
	{
		SteamFriendsPtr->ActivateGameOverlayInviteDialog(*(uint64*)LobbyId.GetBytes());
	}
}

void FOnlineFriendsSteam::CachePlayerAvatar(const FUniqueNetId& UserId)
{
	FScopeLock lock(&CachedAvatarsLock);

	const FUniqueNetIdSteam player(UserId);
	EFriendsLists::PlayerAvatarSize Size(EFriendsLists::PlayerAvatarSize::Avatar_Medium);

	if (player.IsValid() && CachedAvatarsInFlight.RemoveAndCopyValue(player, Size))
	{
		int avatarId;

		switch (Size)
		{
		case EFriendsLists::PlayerAvatarSize::Avatar_Small: avatarId = SteamFriends()->GetSmallFriendAvatar(player); break;
		case EFriendsLists::PlayerAvatarSize::Avatar_Medium: avatarId = SteamFriends()->GetMediumFriendAvatar(player); break;
		case EFriendsLists::PlayerAvatarSize::Avatar_Large: default: avatarId = SteamFriends()->GetLargeFriendAvatar(player); break;
		}

		if (avatarId == 0)
		{
			UE_LOG_ONLINE(Warning, TEXT("FOnlineFriendsSteam::CachePlayerAvatar: Avatar for player %llu not cached!"), player.UniqueNetId);
			return;
		}

		if (avatarId == -1)
		{
			UE_LOG_ONLINE(Display, TEXT("FOnlineFriendsSteam::CachePlayerAvatar: Avatar for player %llu still loading, postponing cache..."), player.UniqueNetId);
			CachedAvatarsInFlight.Add(player, EFriendsLists::PlayerAvatarSize::Avatar_Large);
			return;
		}

		uint32 width = 0, height = 0;
		if (!SteamUtils()->GetImageSize(avatarId, &width, &height))
		{
			UE_LOG_ONLINE(Warning, TEXT("FOnlineFriendsSteam::CachePlayerAvatar: GetImageSize for player %%llu failed!"), player.UniqueNetId);
			return;
		}

		const uint32 size = width * height * 4;
		auto data = new uint8[size];

		if (!SteamUtils()->GetImageRGBA(avatarId, data, size))
		{
			UE_LOG_ONLINE(Warning, TEXT("FOnlineFriendsSteam::CachePlayerAvatar: GetImageRGBA for player %%llu failed!"), player.UniqueNetId);
			delete[] data;
			return;
		}

		const TStrongObjectPtr<UTexture2D> avatar(UTexture2D::CreateTransient(width, height, PF_R8G8B8A8));

		auto mipData = (uint8*)avatar->PlatformData->Mips[0].BulkData.Lock(LOCK_READ_WRITE);
		FMemory::Memcpy(mipData, data, size);
		avatar->PlatformData->Mips[0].BulkData.Unlock();

		delete[] data;

		avatar->PlatformData->NumSlices = 1;
		avatar->NeverStream = true;
		avatar->AddressX = TA_Clamp;
		avatar->AddressY = TA_Clamp;
		avatar->Filter = TF_Bilinear;

		avatar->UpdateResource();

		CachedAvatars.Add(player, TPair<const TStrongObjectPtr<UTexture2D>, double>(avatar, FPlatformTime::Seconds()));

		UE_LOG_ONLINE(Verbose, TEXT("FOnlineFriendsSteam::CachePlayerAvatar: Cached avatar for player %llu."), player.UniqueNetId);

		if (CachedAvatars.Num() > MAX_CACHED_AVATARS)
		{
			double oldestTime = MAX_dbl;
			FUniqueNetIdSteam oldestKey;
			for (TMap<const FUniqueNetIdSteam, TPair<const TStrongObjectPtr<UTexture2D>, double>>::TConstIterator i
				= CachedAvatars.CreateConstIterator(); i; ++i)
			{
				if (i.Value().Value < oldestTime && i.Key() != FUniqueNetIdSteam(SteamUser()->GetSteamID()))
				{
					oldestTime = i.Value().Value;
					oldestKey = i.Key();
				}
			}
			CachedAvatars.Remove(oldestKey);
			UE_LOG_ONLINE(Verbose, TEXT("FOnlineFriendsSteam::CachePlayerAvatar: Removed cached avatar for player %llu."), oldestKey.UniqueNetId);
		}
	}
	else
	{
		UE_LOG_ONLINE(Warning, TEXT("FOnlineFriendsSteam::CachePlayerAvatar: Invalid Player Id %llu"), player.UniqueNetId);
	}
}

UTexture2D* FOnlineFriendsSteam::GetFriendAvatar(const FUniqueNetId& UserId, EFriendsLists::PlayerAvatarSize AvatarSize)
{
	FScopeLock lock(&CachedAvatarsLock);

	const FUniqueNetIdSteam userId(UserId);

	if (userId.IsValid())
	{
		TPair<const TStrongObjectPtr<UTexture2D>, double>* const currentAvatar = CachedAvatars.Find(userId);
		if (currentAvatar != nullptr)
		{
			currentAvatar->Value = FPlatformTime::Seconds();

			UE_LOG_ONLINE(Verbose, TEXT("FOnlineFriendsSteam::GetFriendAvatar: Retrieved cached avatar for user %llu."), userId.UniqueNetId);

			return currentAvatar->Key.Get();
		}
		else if (!CachedAvatarsInFlight.Contains(userId))
		{
			if (!SteamFriends()->RequestUserInformation(userId, false))
			{
				CachedAvatarsInFlight.Add(userId, AvatarSize);

				CachePlayerAvatar(userId);

				TPair<const TStrongObjectPtr<UTexture2D>, double>* const currentAvatarRetry = CachedAvatars.Find(userId);
				if (currentAvatarRetry != nullptr)
				{
					currentAvatarRetry->Value = FPlatformTime::Seconds();

					UE_LOG_ONLINE(Verbose, TEXT("FOnlineFriendsSteam::GetFriendAvatar: Retrieved cached avatar for user %llu."), userId.UniqueNetId);

					return currentAvatarRetry->Key.Get();
				}

				CachedAvatarsInFlight.Remove(userId);

				UE_LOG_ONLINE(Verbose, TEXT("FOnlineFriendsSteam::GetFriendAvatar: RequestUserInformation for user %llu failed!"), userId.UniqueNetId);
				return nullptr;
			}

			CachedAvatarsInFlight.Add(userId, AvatarSize);

			UE_LOG_ONLINE(Verbose, TEXT("FOnlineFriendsSteam::GetFriendAvatar: Avatar for user %llu is not cached. Fetching..."), userId.UniqueNetId);
		}
		else
		{
			UE_LOG_ONLINE(Verbose, TEXT("FOnlineFriendsSteam::GetFriendAvatar: Trying to get avatar for user %llu that is still fetching..."), userId.UniqueNetId);
		}
	}

	return nullptr;
}
