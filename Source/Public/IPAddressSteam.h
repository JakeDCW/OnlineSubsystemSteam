// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "IPAddress.h"
#include "OnlineSubsystemSteamTypes.h"
#include "OnlineSubsystemSteamPackage.h"

/**
 * Represents an internet ip address, using the relatively standard SOCKADDR_IN structure. All data is in network byte order
 */
class ONLINESUBSYSTEMSTEAM_API FInternetAddrSteam : public FInternetAddr
{
public:
	/** The Steam id to connect to */
	FUniqueNetIdSteam SteamId;
	/** Steam channel to communicate on */
	int32 SteamChannel;

	/**
	 * Copy Constructor
	 */
	FInternetAddrSteam(const FInternetAddrSteam& Src) :
		SteamId(Src.SteamId),
		SteamChannel(Src.SteamChannel)
	{
	}

	/**
	 * Constructor. Sets address to default state
	 */
	FInternetAddrSteam() :
		SteamId((uint64)0),
		SteamChannel(0)
	{
	}
	/**
	 * Constructor. Sets address to default state
	 */
	explicit FInternetAddrSteam(const FUniqueNetIdSteam& InSteamId) :
		SteamId(InSteamId),
		SteamChannel(0)
	{
	}

	/**
	 * Gets the ip address in a raw array stored in network byte order.
	 *
	 * @return The raw address stored in an array
	 */
	virtual TArray<uint8> GetRawIp() const override;

	/**
	 * Sets the ip address from a raw network byte order array.
	 *
	 * @param RawAddr the new address to use (must be converted to network byte order)
	 */
	virtual void SetRawIp(const TArray<uint8>& RawAddr) override;

	/**
	 * Sets the ip address from a host byte order uint32
	 *
	 * @param InAddr the new address to use (must convert to network byte order)
	 */
	void SetIp(uint32 InAddr) override
	{
		UE_LOG_ONLINE(Warning, TEXT("FInternetAddrSteam::SetIp is not supported."));
	}

	/**
	 * Sets the ip address from a string ("A.B.C.D")
	 *
	 * @param InAddr the string containing the new ip address to use
	 */
	void SetIp(const TCHAR* InAddr, bool& bIsValid) override;

	/**
	 * Copies the network byte order ip address to a host byte order dword
	 *
	 * @param OutAddr the out param receiving the ip address
	 */
	void GetIp(uint32& OutAddr) const override
	{
		OutAddr = 0;
		UE_LOG_ONLINE(Warning, TEXT("FInternetAddrSteam::GetIp is not supported and will set OutAddr to 0."));
	}

	/**
	 * Sets the port number from a host byte order int
	 *
	 * @param InPort the new port to use (must convert to network byte order)
	 */
	void SetPort(int32 InPort) override
	{
		SteamChannel = InPort;
	}

	/**
	 * Copies the port number from this address and places it into a host byte order int
	 *
	 * @param OutPort the host byte order int that receives the port
	 */
	void GetPort(int32& OutPort) const override
	{
		OutPort = SteamChannel;
	}

	/**
	 * Returns the port number from this address in host byte order
	 */
	int32 GetPort() const override
	{
		return SteamChannel;
	}

	/** Sets the address to be any address */
	void SetAnyAddress() override
	{
	}

	/** Sets the address to broadcast */
	void SetBroadcastAddress() override
	{
	}

	/** Sets the address to the loopback address */
	void SetLoopbackAddress() override
	{
	}

	/**
	 * Converts this internet ip address to string form
	 *
	 * @param bAppendPort whether to append the port information or not
	 */
	FString ToString(bool bAppendPort) const override
	{
		if (bAppendPort)
		{
			return FString::Printf(TEXT("%lld:%d"), SteamId.UniqueNetId, SteamChannel);
		}
		else
		{
			return FString::Printf(TEXT("%lld"), SteamId.UniqueNetId);
		}
	}

	/**
	 * Compares two internet ip addresses for equality
	 *
	 * @param Other the address to compare against
	 */
	virtual bool operator==(const FInternetAddr& Other) const override
	{
		FInternetAddrSteam& SteamOther = (FInternetAddrSteam&)Other;
		return SteamId == SteamOther.SteamId && SteamChannel == SteamOther.SteamChannel;
	}

	bool operator!=(const FInternetAddrSteam& Other) const
	{
		return !(FInternetAddrSteam::operator==(Other));
	}

	virtual uint32 GetTypeHash() override
	{
		return ::GetTypeHash(*(uint64*)SteamId.GetBytes());
	}

	/**
	 * Is this a well formed internet address
	 *
	 * @return true if a valid IP, false otherwise
	 */
	virtual bool IsValid() const override
	{
		return SteamId.IsValid();
	}

	virtual TSharedRef<FInternetAddr> Clone() const override
	{
		TSharedRef<FInternetAddrSteam> NewAddress = MakeShareable(new FInternetAddrSteam);
		NewAddress->SteamId = SteamId;
		NewAddress->SteamChannel = SteamChannel;
		return NewAddress;
	}
};
