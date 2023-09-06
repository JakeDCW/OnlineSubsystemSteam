// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "Source/Classes/SteamNetDriver.h"
#ifdef _MSC_VER
#pragma warning (push)
#pragma warning (disable : 4883)
#endif
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeSteamNetDriver() {}
// Cross Module References
	ONLINESUBSYSTEMSTEAM_API UClass* Z_Construct_UClass_USteamNetDriver_NoRegister();
	ONLINESUBSYSTEMSTEAM_API UClass* Z_Construct_UClass_USteamNetDriver();
	ONLINESUBSYSTEMUTILS_API UClass* Z_Construct_UClass_UIpNetDriver();
	UPackage* Z_Construct_UPackage__Script_OnlineSubsystemSteam();
// End Cross Module References
	void USteamNetDriver::StaticRegisterNativesUSteamNetDriver()
	{
	}
	UClass* Z_Construct_UClass_USteamNetDriver_NoRegister()
	{
		return USteamNetDriver::StaticClass();
	}
	struct Z_Construct_UClass_USteamNetDriver_Statics
	{
		static UObject* (*const DependentSingletons[])();
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UE4CodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_USteamNetDriver_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_UIpNetDriver,
		(UObject* (*)())Z_Construct_UPackage__Script_OnlineSubsystemSteam,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_USteamNetDriver_Statics::Class_MetaDataParams[] = {
		{ "IncludePath", "SteamNetDriver.h" },
		{ "ModuleRelativePath", "Classes/SteamNetDriver.h" },
	};
#endif
	const FCppClassTypeInfoStatic Z_Construct_UClass_USteamNetDriver_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<USteamNetDriver>::IsAbstract,
	};
	const UE4CodeGen_Private::FClassParams Z_Construct_UClass_USteamNetDriver_Statics::ClassParams = {
		&USteamNetDriver::StaticClass,
		DependentSingletons, ARRAY_COUNT(DependentSingletons),
		0x000000ACu,
		nullptr, 0,
		nullptr, 0,
		"Engine",
		&StaticCppClassTypeInfo,
		nullptr, 0,
		METADATA_PARAMS(Z_Construct_UClass_USteamNetDriver_Statics::Class_MetaDataParams, ARRAY_COUNT(Z_Construct_UClass_USteamNetDriver_Statics::Class_MetaDataParams))
	};
	UClass* Z_Construct_UClass_USteamNetDriver()
	{
		static UClass* OuterClass = nullptr;
		if (!OuterClass)
		{
			UE4CodeGen_Private::ConstructUClass(OuterClass, Z_Construct_UClass_USteamNetDriver_Statics::ClassParams);
		}
		return OuterClass;
	}
	IMPLEMENT_CLASS(USteamNetDriver, 2206069896);
	static FCompiledInDefer Z_CompiledInDefer_UClass_USteamNetDriver(Z_Construct_UClass_USteamNetDriver, &USteamNetDriver::StaticClass, TEXT("/Script/OnlineSubsystemSteam"), TEXT("USteamNetDriver"), false, nullptr, nullptr, nullptr);
	DEFINE_VTABLE_PTR_HELPER_CTOR(USteamNetDriver);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
#ifdef _MSC_VER
#pragma warning (pop)
#endif
