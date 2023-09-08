// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Interfaces/VoiceInterface.h"
#include "Net/VoiceDataCommon.h"
#include "VoicePacketImpl.h"
#include "OnlineSubsystemSteamTypes.h"
#include "OnlineSubsystemSteamPackage.h"
#include "OnlineSubsystemUtilsPackage.h"
#include "VoiceInterfaceImpl.h"
#include "VoiceEngineSteam.h"

/**
 * The Steam implementation of the voice interface 
 */

class ONLINESUBSYSTEMSTEAM_API FOnlineVoiceSteam : public FOnlineVoiceImpl
{
PACKAGE_SCOPE:
	FOnlineVoiceSteam() : FOnlineVoiceImpl(), RemoteVoiceVolume(DEFAULT_VOICE_VOLUME)
	{};

public:

	/** Constructor */
	FOnlineVoiceSteam(class IOnlineSubsystem* InOnlineSubsystem) :
		FOnlineVoiceImpl(InOnlineSubsystem), RemoteVoiceVolume(DEFAULT_VOICE_VOLUME)
	{
		check(InOnlineSubsystem);
	};

	virtual IVoiceEnginePtr CreateVoiceEngine() override
	{
		return MakeShareable(new FVoiceEngineSteam(OnlineSubsystem));
	}

	/** Virtual destructor to force proper child cleanup */
	virtual ~FOnlineVoiceSteam() override {};

	virtual float GetRemoteVoiceVolume() override { return RemoteVoiceVolume; }
	virtual void SetRemoteVoiceVolume(float NewVolume) override
	{
		RemoteVoiceVolume = FMath::Max(0.0f, NewVolume);
		if (VoiceEngine.IsValid())
		{
			const auto engine = StaticCastSharedPtr<FVoiceEngineSteam>(VoiceEngine);
			if (engine.IsValid())
			{
				engine->SetRemoteVoiceVolume(RemoteVoiceVolume);
			}
		}
	}

private:

	float RemoteVoiceVolume;
};

typedef TSharedPtr<FOnlineVoiceSteam, ESPMode::ThreadSafe> FOnlineVoiceSteamPtr;
