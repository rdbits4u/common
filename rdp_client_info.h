
#if !defined(_RDP_CLIENT_INFO_H)
#define _RDP_CLIENT_INFO_H

#include <stdint.h>

struct TS_EXTENDED_INFO_PACKET
{
    uint16_t clientAddressFamily;
    uint16_t cbClientAddress;
    char clientAddress[80];
    uint16_t cbClientDir;
    char clientDir[512];
    char clientTimeZone[172];
    uint32_t clientSessionId;
    uint32_t performanceFlags;
    uint16_t cbAutoReconnectCookie;
    char autoReconnectCookie[28];
    uint16_t reserved1;
    uint16_t reserved2;
    uint16_t cbDynamicDSTTimeZoneKeyName;
    char dynamicDSTTimeZoneKeyName[254];
    uint16_t dynamicDaylightTimeDisabled;
};

struct TS_INFO_PACKET
{
    uint32_t CodePage;
    uint32_t flags;
    uint16_t cbDomain;
    uint16_t cbUserName;
    uint16_t cbPassword;
    uint16_t cbAlternateShell;
    uint16_t cbWorkingDir;
    char Domain[512];
    char UserName[512];
    char Password[512];
    char AlternateShell[512];
    char WorkingDir[512];
    struct TS_EXTENDED_INFO_PACKET extraInfo;
};

#endif