// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "Source/Classes/SteamNetConnection.h"
#ifdef _MSC_VER
#pragma warning (push)
#pragma warning (disable : 4883)
#endif
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeSteamNetConnection() {}
// Cross Module References
	ONLINESUBSYSTEMSTEAM_API UClass* Z_Construct_UClass_USteamNetConnection_NoRegister();
	ONLINESUBSYSTEMSTEAM_API UClass* Z_Construct_UClass_USteamNetConnection();
	ONLINESUBSYSTEMUTILS_API UClass* Z_Construct_UClass_UIpConnection();
	UPackage* Z_Construct_UPackage__Script_OnlineSubsystemSteam();
// End Cross Module References
	void USteamNetConnection::StaticRegisterNativesUSteamNetConnection()
	{
	}
	UClass* Z_Construct_UClass_USteamNetConnection_NoRegister()
	{
		return USteamNetConnection::StaticClass();
	}
	struct Z_Construct_UClass_USteamNetConnection_Statics
	{
		static UObject* (*const DependentSingletons[])();
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_bIsPassthrough_MetaData[];
#endif
		static void NewProp_bIsPassthrough_SetBit(void* Obj);
		static const UE4CodeGen_Private::FBoolPropertyParams NewProp_bIsPassthrough;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UE4CodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_USteamNetConnection_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_UIpConnection,
		(UObject* (*)())Z_Construct_UPackage__Script_OnlineSubsystemSteam,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_USteamNetConnection_Statics::Class_MetaDataParams[] = {
		{ "IncludePath", "SteamNetConnection.h" },
		{ "ModuleRelativePath", "Classes/SteamNetConnection.h" },
	};
#endif
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_USteamNetConnection_Statics::NewProp_bIsPassthrough_MetaData[] = {
		{ "ModuleRelativePath", "Classes/SteamNetConnection.h" },
		{ "ToolTip", "Is this net connection passthrough to IpConnection" },
	};
#endif
	void Z_Construct_UClass_USteamNetConnection_Statics::NewProp_bIsPassthrough_SetBit(void* Obj)
	{
		((USteamNetConnection*)Obj)->bIsPassthrough = 1;
	}
	const UE4CodeGen_Private::FBoolPropertyParams Z_Construct_UClass_USteamNetConnection_Statics::NewProp_bIsPassthrough = { UE4CodeGen_Private::EPropertyClass::Bool, "bIsPassthrough", RF_Public|RF_Transient|RF_MarkAsNative, (EPropertyFlags)0x0010000000000000, 1, nullptr, sizeof(bool), UE4CodeGen_Private::ENativeBool::Native, sizeof(USteamNetConnection), &Z_Construct_UClass_USteamNetConnection_Statics::NewProp_bIsPassthrough_SetBit, METADATA_PARAMS(Z_Construct_UClass_USteamNetConnection_Statics::NewProp_bIsPassthrough_MetaData, ARRAY_COUNT(Z_Construct_UClass_USteamNetConnection_Statics::NewProp_bIsPassthrough_MetaData)) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_USteamNetConnection_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_USteamNetConnection_Statics::NewProp_bIsPassthrough,
	};
	const FCppClassTypeInfoStatic Z_Construct_UClass_USteamNetConnection_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<USteamNetConnection>::IsAbstract,
	};
	const UE4CodeGen_Private::FClassParams Z_Construct_UClass_USteamNetConnection_Statics::ClassParams = {
		&USteamNetConnection::StaticClass,
		DependentSingletons, ARRAY_COUNT(DependentSingletons),
		0x000000ACu,
		nullptr, 0,
		Z_Construct_UClass_USteamNetConnection_Statics::PropPointers, ARRAY_COUNT(Z_Construct_UClass_USteamNetConnection_Statics::PropPointers),
		"Engine",
		&StaticCppClassTypeInfo,
		nullptr, 0,
		METADATA_PARAMS(Z_Construct_UClass_USteamNetConnection_Statics::Class_MetaDataParams, ARRAY_COUNT(Z_Construct_UClass_USteamNetConnection_Statics::Class_MetaDataParams))
	};
	UClass* Z_Construct_UClass_USteamNetConnection()
	{
		static UClass* OuterClass = nullptr;
		if (!OuterClass)
		{
			UE4CodeGen_Private::ConstructUClass(OuterClass, Z_Construct_UClass_USteamNetConnection_Statics::ClassParams);
		}
		return OuterClass;
	}
	IMPLEMENT_CLASS(USteamNetConnection, 2991363283);
	static FCompiledInDefer Z_CompiledInDefer_UClass_USteamNetConnection(Z_Construct_UClass_USteamNetConnection, &USteamNetConnection::StaticClass, TEXT("/Script/OnlineSubsystemSteam"), TEXT("USteamNetConnection"), false, nullptr, nullptr, nullptr);
	DEFINE_VTABLE_PTR_HELPER_CTOR(USteamNetConnection);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
#ifdef _MSC_VER
#pragma warning (pop)
#endif
