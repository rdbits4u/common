
#if !defined(_RDP_GCC_H)
#define _RDP_GCC_H

#include <stdint.h>

#define CS_CORE             0xC001
#define CS_SECURITY         0xC002
#define CS_NET              0xC003
#define CS_CLUSTER          0xC004
#define CS_MONITOR          0xC005
#define CS_MCS_MSGCHANNEL   0xC006
#define CS_MONITOR_EX       0xC008
#define CS_MULTITRANSPORT   0xC00A
#define CS_UNUSED1          0xC00C

struct TS_UD_HEADER
{
    uint16_t type;
    uint16_t length;
};

#define RNS_UD_COLOR_4BPP   0xCA00
#define RNS_UD_COLOR_8BPP   0xCA01

#define RNS_UD_SAS_DEL      0xAA03

/* Connection Types, TS_UD_CS_CORE::connectionType */
#define CONNECTION_TYPE_MODEM               0x01
#define CONNECTION_TYPE_BROADBAND_LOW       0x02
#define CONNECTION_TYPE_SATELLITE           0x03
#define CONNECTION_TYPE_BROADBAND_HIGH      0x04
#define CONNECTION_TYPE_WAN                 0x05
#define CONNECTION_TYPE_LAN                 0x06

struct TS_UD_CS_CORE
{
    struct TS_UD_HEADER header; /* CS_CORE (0xC001) */
    uint32_t version;
    uint16_t desktopWidth;
    uint16_t desktopHeight;
    uint16_t colorDepth;
    uint16_t SASSequence;
    uint32_t keyboardLayout;
    uint32_t clientBuild;
    char clientName[32];
    uint32_t keyboardType;
    uint32_t keyboardSubType;
    uint32_t keyboardFunctionKey;
    char imeFileName[64];
    uint16_t postBeta2ColorDepth;
    uint16_t clientProductId;
    uint32_t serialNumber;
    uint16_t highColorDepth;
    uint16_t supportedColorDepths;
    uint16_t earlyCapabilityFlags;
    char clientDigProductId[64];
    uint8_t connectionType;
    uint8_t pad1octet;
    uint32_t serverSelectedProtocol;
    uint32_t desktopPhysicalWidth;
    uint32_t desktopPhysicalHeight;
    uint16_t desktopOrientation;
    uint32_t desktopScaleFactor;
    uint32_t deviceScaleFactor;
};

struct TS_UD_CS_SEC
{
    struct TS_UD_HEADER header; /* CS_SECURITY (0xC002) */
    uint32_t encryptionMethods;
    uint32_t extEncryptionMethods;
};

struct CHANNEL_DEF
{
    char name[8];
    uint32_t options;
};

struct TS_UD_CS_NET
{
    struct TS_UD_HEADER header; /* CS_NET (0xC003) */
    uint32_t channelCount;
    struct CHANNEL_DEF channelDefArray[16];
};

struct TS_UD_CS_CLUSTER
{
    struct TS_UD_HEADER header; /* CS_CLUSTER (0xC004) */
    uint32_t Flags;
    uint32_t RedirectedSessionID;
};

struct TS_MONITOR_DEF
{
    int32_t left;
    int32_t top;
    int32_t right;
    int32_t bottom;
    uint32_t flags;
};

struct TS_UD_CS_MONITOR
{
    struct TS_UD_HEADER header; /* CS_MONITOR (0xC005) */
    uint32_t flags;
    uint32_t monitorCount;
    struct TS_MONITOR_DEF monitorDefArray[16];
};

struct TS_UD_CS_MCS_MSGCHANNEL
{
    struct TS_UD_HEADER header; /* CS_MCS_MSGCHANNEL (0xC006) */
    uint32_t flags;
};

struct TS_MONITOR_ATTRIBUTES
{
    uint32_t physicalWidth;
    uint32_t physicalHeight;
    uint32_t orientation;
    uint32_t desktopScaleFactor;
    uint32_t deviceScaleFactor;
};

struct TS_UD_CS_MONITOR_EX
{
    struct TS_UD_HEADER header; /* CS_MONITOR_EX (0xC008) */
    uint32_t flags;
    uint32_t monitorAttributeSize;
    uint32_t monitorCount;
    struct TS_MONITOR_ATTRIBUTES monitorAttributesArray[16];
};

struct TS_UD_CS_MULTITRANSPORT
{
    struct TS_UD_HEADER header; /* CS_MULTITRANSPORT (0xC00A) */
    uint32_t flags;
};

#define SC_CORE             0x0C01
#define SC_SECURITY         0x0C02
#define SC_NET              0x0C03
#define SC_MCS_MSGCHANNEL   0x0C04
#define SC_MULTITRANSPORT   0x0C08

struct TS_UD_SC_CORE
{
    struct TS_UD_HEADER header; /* SC_CORE (0x0C01) */
    uint32_t version;
    uint32_t clientRequestedProtocols;
    uint32_t earlyCapabilityFlags;
};

struct TS_UD_SC_SEC
{
    struct TS_UD_HEADER header; /* SC_SECURITY (0x0C02) */
    uint32_t encryptionMethod;
    uint32_t encryptionLevel;
    uint32_t serverRandomLen;
    uint32_t serverCertLen;
    char serverRandom[32];
    char serverCertificate[1024];
};

struct TS_UD_SC_NET
{
    struct TS_UD_HEADER header; /* SC_NET (0x0C03) */
    uint16_t MCSChannelId;
    uint16_t channelCount;
    uint16_t channelIdArray[16];
};

struct TS_UD_SC_MCS_MSGCHANNEL
{
    struct TS_UD_HEADER header; /* SC_MCS_MSGCHANNEL (0x0C04) */
    uint16_t MCSChannelID;
};

struct TS_UD_SC_MULTITRANSPORT
{
    struct TS_UD_HEADER header; /* SC_MULTITRANSPORT (0x0C08) */
    uint32_t flags;
};

struct client_gcc
{
    struct TS_UD_CS_CORE core;
    struct TS_UD_CS_SEC sec;
    struct TS_UD_CS_NET net;
    struct TS_UD_CS_CLUSTER cluster;
    struct TS_UD_CS_MONITOR monitor;
    struct TS_UD_CS_MCS_MSGCHANNEL msgchannel;
    struct TS_UD_CS_MONITOR_EX monitor_ex;
    struct TS_UD_CS_MULTITRANSPORT multitransport;
};

struct server_gcc
{
    struct TS_UD_SC_CORE core;
    struct TS_UD_SC_SEC sec;
    struct TS_UD_SC_NET net;
    struct TS_UD_SC_MCS_MSGCHANNEL msgchannel;
    struct TS_UD_SC_MULTITRANSPORT multitransport;
};

#endif
