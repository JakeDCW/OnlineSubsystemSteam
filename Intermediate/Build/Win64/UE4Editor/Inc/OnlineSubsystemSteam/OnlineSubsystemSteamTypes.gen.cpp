// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "Source/Public/OnlineSubsystemSteamTypes.h"
#ifdef _MSC_VER
#pragma warning (push)
#pragma warning (disable : 4883)
#endif
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeOnlineSubsystemSteamTypes() {}
// Cross Module References
	ONLINESUBSYSTEMSTEAM_API UEnum* Z_Construct_UEnum_OnlineSubsystemSteam_ESteamSession();
	UPackage* Z_Construct_UPackage__Script_OnlineSubsystemSteam();
// End Cross Module References
	static UEnum* ESteamSession_StaticEnum()
	{
		static UEnum* Singleton = nullptr;
		if (!Singleton)
		{
			Singleton = GetStaticEnum(Z_Construct_UEnum_OnlineSubsystemSteam_ESteamSession, Z_Construct_UPackage__Script_OnlineSubsystemSteam(), TEXT("ESteamSession"));
		}
		return Singleton;
	}
	static FCompiledInDeferEnum Z_CompiledInDeferEnum_UEnum_ESteamSession(ESteamSession_StaticEnum, TEXT("/Script/OnlineSubsystemSteam"), TEXT("ESteamSession"), false, nullptr, nullptr);
	uint32 Get_Z_Construct_UEnum_OnlineSubsystemSteam_ESteamSession_CRC() { return 3478649890U; }
	UEnum* Z_Construct_UEnum_OnlineSubsystemSteam_ESteamSession()
	{
#if WITH_HOT_RELOAD
		UPackage* Outer = Z_Construct_UPackage__Script_OnlineSubsystemSteam();
		static UEnum* ReturnEnum = FindExistingEnumIfHotReloadOrDynamic(Outer, TEXT("ESteamSession"), 0, Get_Z_Construct_UEnum_OnlineSubsystemSteam_ESteamSession_CRC(), false);
#else
		static UEnum* ReturnEnum = nullptr;
#endif // WITH_HOT_RELOAD
		if (!ReturnEnum)
		{
			static const UE4CodeGen_Private::FEnumeratorParam Enumerators[] = {
				{ "ESteamSession::None", (int64)ESteamSession::None },
				{ "ESteamSession::LobbySession", (int64)ESteamSession::LobbySession },
				{ "ESteamSession::AdvertisedSessionHost", (int64)ESteamSession::AdvertisedSessionHost },
				{ "ESteamSession::AdvertisedSessionClient", (int64)ESteamSession::AdvertisedSessionClient },
				{ "ESteamSession::LANSession", (int64)ESteamSession::LANSession },
			};
#if WITH_METADATA
			const UE4CodeGen_Private::FMetaDataPairParam Enum_MetaDataParams[] = {
				{ "AdvertisedSessionClient.ToolTip", "Session client of a game server session" },
				{ "AdvertisedSessionHost.ToolTip", "Session managed by master server publishing" },
				{ "LANSession.ToolTip", "Session managed by LAN beacon" },
				{ "LobbySession.ToolTip", "Session managed as a lobby on backend" },
				{ "ModuleRelativePath", "Public/OnlineSubsystemSteamTypes.h" },
				{ "None.ToolTip", "Session is undefined" },
				{ "ToolTip", "Possible session states" },
			};
#endif
			static const UE4CodeGen_Private::FEnumParams EnumParams = {
				(UObject*(*)())Z_Construct_UPackage__Script_OnlineSubsystemSteam,
				UE4CodeGen_Private::EDynamicType::NotDynamic,
				"ESteamSession",
				RF_Public|RF_Transient|RF_MarkAsNative,
				nullptr,
				(uint8)UEnum::ECppForm::Namespaced,
				"ESteamSession::Type",
				Enumerators,
				ARRAY_COUNT(Enumerators),
				METADATA_PARAMS(Enum_MetaDataParams, ARRAY_COUNT(Enum_MetaDataParams))
			};
			UE4CodeGen_Private::ConstructUEnum(ReturnEnum, EnumParams);
		}
		return ReturnEnum;
	}
PRAGMA_ENABLE_DEPRECATION_WARNINGS
#ifdef _MSC_VER
#pragma warning (pop)
#endif
