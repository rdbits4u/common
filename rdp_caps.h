
#if !defined(_RDP_CAPS_H)
#define _RDP_CAPS_H

#include <stdint.h>

#define CAPSTYPE_GENERAL                    0x0001 // General Capability Set (section 2.2.7.1.1)
#define CAPSTYPE_BITMAP                     0x0002 // Bitmap Capability Set (section 2.2.7.1.2)
#define CAPSTYPE_ORDER                      0x0003 // Order Capability Set (section 2.2.7.1.3)
#define CAPSTYPE_BITMAPCACHE                0x0004 // Revision 1 Bitmap Cache Capability Set (section 2.2.7.1.4.1)
#define CAPSTYPE_CONTROL                    0x0005 // Control Capability Set (section 2.2.7.2.2)
#define CAPSTYPE_ACTIVATION                 0x0007 // Window Activation Capability Set (section 2.2.7.2.3)
#define CAPSTYPE_POINTER                    0x0008 // Pointer Capability Set (section 2.2.7.1.5)
#define CAPSTYPE_SHARE                      0x0009 // Share Capability Set (section 2.2.7.2.4)
#define CAPSTYPE_COLORCACHE                 0x000A // Color Table Cache Capability Set ([MS-RDPEGDI] section 2.2.1.1)
#define CAPSTYPE_SOUND                      0x000C // Sound Capability Set (section 2.2.7.1.11)
#define CAPSTYPE_INPUT                      0x000D // Input Capability Set (section 2.2.7.1.6)
#define CAPSTYPE_FONT                       0x000E // Font Capability Set (section 2.2.7.2.5)
#define CAPSTYPE_BRUSH                      0x000F // Brush Capability Set (section 2.2.7.1.7)
#define CAPSTYPE_GLYPHCACHE                 0x0010 // Glyph Cache Capability Set (section 2.2.7.1.8)
#define CAPSTYPE_OFFSCREENCACHE             0x0011 // Offscreen Bitmap Cache Capability Set (section 2.2.7.1.9)
#define CAPSTYPE_BITMAPCACHE_HOSTSUPPORT    0x0012 // Bitmap Cache Host Support Capability Set (section 2.2.7.2.1)
#define CAPSTYPE_BITMAPCACHE_REV2           0x0013 // Revision 2 Bitmap Cache Capability Set (section 2.2.7.1.4.2)
#define CAPSTYPE_VIRTUALCHANNEL             0x0014 // Virtual Channel Capability Set (section 2.2.7.1.10)
#define CAPSTYPE_DRAWNINEGRIDCACHE          0x0015 // DrawNineGrid Cache Capability Set ([MS-RDPEGDI] section 2.2.1.2)
#define CAPSTYPE_DRAWGDIPLUS                0x0016 // Draw GDI+ Cache Capability Set ([MS-RDPEGDI] section 2.2.1.3)
#define CAPSTYPE_RAIL                       0x0017 // Remote Programs Capability Set ([MS-RDPERP] section 2.2.1.1.1)
#define CAPSTYPE_WINDOW                     0x0018 // Window List Capability Set ([MS-RDPERP] section 2.2.1.1.2)
#define CAPSETTYPE_COMPDESK                 0x0019 // Desktop Composition Extension Capability Set (section 2.2.7.2.8)
#define CAPSETTYPE_MULTIFRAGMENTUPDATE      0x001A // Multifragment Update Capability Set (section 2.2.7.2.6)
#define CAPSETTYPE_LARGE_POINTER            0x001B // Large Pointer Capability Set (section 2.2.7.2.7)
#define CAPSETTYPE_SURFACE_COMMANDS         0x001C // Surface Commands Capability Set (section 2.2.7.2.9)
#define CAPSETTYPE_BITMAP_CODECS            0x001D // Bitmap Codecs Capability Set (section 2.2.7.2.10)
#define CAPSSETTYPE_FRAME_ACKNOWLEDGE       0x001E // Frame Acknowledge Capability Set ([MS-RDPRFX] section 2.2.1.3)

struct TS_GENERAL_CAPABILITYSET
{
    uint16_t capabilitySetType;
    uint16_t lengthCapability;
    uint16_t osMajorType;
    uint16_t osMinorType;
    uint16_t protocolVersion;
    uint16_t pad2octetsA;
    uint16_t compressionTypes;
    uint16_t extraFlags;
    uint16_t updateCapabilityFlag;
    uint16_t remoteUnshareFlag;
    uint16_t compressionLevel;
    uint8_t refreshRectSupport;
    uint8_t suppressOutputSupport;
};

struct TS_BITMAP_CAPABILITYSET
{
    uint16_t capabilitySetType;
    uint16_t lengthCapability;
    uint16_t preferredBitsPerPixel;
    uint16_t receive1BitPerPixel;
    uint16_t receive4BitsPerPixel;
    uint16_t receive8BitsPerPixel;
    uint16_t desktopWidth;
    uint16_t desktopHeight;
    uint16_t pad2octets;
    uint16_t desktopResizeFlag;
    uint16_t bitmapCompressionFlag;
    uint8_t highColorFlags;
    uint8_t drawingFlags;
    uint16_t multipleRectangleSupport;
    uint16_t pad2octetsB;
};

struct TS_ORDER_CAPABILITYSET
{
    uint16_t capabilitySetType;
    uint16_t lengthCapability;
    char terminalDescriptor[16];
    uint32_t pad4octetsA;
    uint16_t desktopSaveXGranularity;
    uint16_t desktopSaveYGranularity;
    uint16_t pad2octetsA;
    uint16_t maximumOrderLevel;
    uint16_t numberFonts;
    uint16_t orderFlags;
    char orderSupport[32];
    uint16_t textFlags;
    uint16_t orderSupportExFlags;
    uint32_t pad4octetsB;
    uint32_t desktopSaveSize;
    uint16_t pad2octetsC;
    uint16_t pad2octetsD;
    uint16_t textANSICodePage;
    uint16_t pad2octetsE;
};

struct TS_BITMAPCACHE_CAPABILITYSET
{
    uint16_t capabilitySetType;
    uint16_t lengthCapability;
    uint32_t pad1;
    uint32_t pad2;
    uint32_t pad3;
    uint32_t pad4;
    uint32_t pad5;
    uint32_t pad6;
    uint16_t Cache0Entries;
    uint16_t Cache0MaximumCellSize;
    uint16_t Cache1Entries;
    uint16_t Cache1MaximumCellSize;
    uint16_t Cache2Entries;
    uint16_t Cache2MaximumCellSize;
};

struct TS_CONTROL_CAPABILITYSET
{
    uint16_t capabilitySetType;
    uint16_t lengthCapability;
    uint16_t controlFlags;
    uint16_t remoteDetachFlag;
    uint16_t controlInterest;
    uint16_t detachInterest;
};

struct TS_WINDOWACTIVATION_CAPABILITYSET
{
    uint16_t capabilitySetType;
    uint16_t lengthCapability;
    uint16_t helpKeyFlag;
    uint16_t helpKeyIndexFlag;
    uint16_t helpExtendedKeyFlag;
    uint16_t windowManagerKeyFlag;
};

struct TS_POINTER_CAPABILITYSET
{
    uint16_t capabilitySetType;
    uint16_t lengthCapability;
    uint16_t colorPointerFlag;
    uint16_t colorPointerCacheSize;
    uint16_t pointerCacheSize;
};

struct TS_SHARE_CAPABILITYSET
{
    uint16_t capabilitySetType;
    uint16_t lengthCapability;
    uint16_t nodeID;
    uint16_t pad2octets;
};

struct TS_COLORTABLE_CAPABILITYSET
{
    uint16_t capabilitySetType;
    uint16_t lengthCapability;
    uint16_t colorTableCacheSize;
    uint16_t pad2octets;
};

struct TS_SOUND_CAPABILITYSET
{
    uint16_t capabilitySetType;
    uint16_t lengthCapability;
    uint16_t soundFlags;
    uint16_t pad2octetsA;    
};

struct TS_INPUT_CAPABILITYSET
{
    uint16_t capabilitySetType;
    uint16_t lengthCapability;
    uint16_t inputFlags;
    uint16_t pad2octetsA;
    uint32_t keyboardLayout;
    uint32_t keyboardType;
    uint32_t keyboardSubType;
    uint32_t keyboardFunctionKey;
    char imeFileName[64];
};

struct TS_FONT_CAPABILITYSET
{
    uint16_t capabilitySetType;
    uint16_t lengthCapability;
    uint16_t fontSupportFlags;
    uint16_t pad2octets;
};

struct TS_BRUSH_CAPABILITYSET
{
    uint16_t capabilitySetType;
    uint16_t lengthCapability;
    uint32_t brushSupportLevel;
};

struct TS_CACHE_DEFINITION
{
    uint16_t CacheEntries;
    uint16_t CacheMaximumCellSize;
};

struct TS_GLYPHCACHE_CAPABILITYSET
{
    uint16_t capabilitySetType;
    uint16_t lengthCapability;
    struct TS_CACHE_DEFINITION GlyphCache[10];
    uint32_t FragCache;
    uint16_t GlyphSupportLevel;
    uint16_t pad2octets;
};

struct TS_OFFSCREEN_CAPABILITYSET
{
    uint16_t capabilitySetType;
    uint16_t lengthCapability;
    uint32_t offscreenSupportLevel;
    uint16_t offscreenCacheSize;
    uint16_t offscreenCacheEntries;
};

struct TS_BITMAPCACHE_HOSTSUPPORT_CAPABILITYSET
{
    uint16_t capabilitySetType;
    uint16_t lengthCapability;
    uint8_t cacheVersion;
    uint8_t pad1;
    uint16_t pad2;
};

struct TS_BITMAPCACHE_CAPABILITYSET_REV2
{
    uint16_t capabilitySetType;
    uint16_t lengthCapability;
    uint16_t CacheFlags;
    uint8_t Pad2;
    uint8_t NumCellCaches;
    uint32_t BitmapCache0CellInfo;
    uint32_t BitmapCache1CellInfo;
    uint32_t BitmapCache2CellInfo;
    uint32_t BitmapCache3CellInfo;
    uint32_t BitmapCache4CellInfo;
    char Pad3[12];
};

struct TS_VIRTUALCHANNEL_CAPABILITYSET
{
    uint16_t capabilitySetType;
    uint16_t lengthCapability;
    uint32_t flags;
    uint32_t VCChunkSize;
};

struct TS_DRAW_NINEGRID_CAPABILITYSET
{
    uint16_t capabilitySetType;
    uint16_t lengthCapability;
    uint32_t drawNineGridSupportLevel;
    uint16_t drawNineGridCacheSize;
    uint16_t drawNineGridCacheEntries;
};

struct TS_GDIPLUS_CACHE_ENTRIES
{
    uint16_t GdipGraphicsCacheEntries;
    uint16_t GdipBrushCacheEntries;
    uint16_t GdipPenCacheEntries;
    uint16_t GdipImageCacheEntries;
    uint16_t GdipImageAttributesCacheEntries;
};

struct TS_GDIPLUS_CACHE_CHUNK_SIZE
{
    uint16_t GdipGraphicsCacheChunkSize;
    uint16_t GdipObjectBrushCacheChunkSize;
    uint16_t GdipObjectPenCacheChunkSize;
    uint16_t GdipObjectImageAttributesCacheChunkSize;
};

struct TS_GDIPLUS_IMAGE_CACHE_PROPERTIES
{
    uint16_t GdipObjectImageCacheChunkSize;
    uint16_t GdipObjectImageCacheTotalSize;
    uint16_t GdipObjectImageCacheMaxSize;
};

struct TS_DRAW_GDIPLUS_CAPABILITYSET
{
    uint16_t capabilitySetType;
    uint16_t lengthCapability;
    uint32_t drawGDIPlusSupportLevel;
    uint32_t GdipVersion;
    uint32_t drawGdiplusCacheLevel;
    struct TS_GDIPLUS_CACHE_ENTRIES GdipCacheEntries;
    struct TS_GDIPLUS_CACHE_CHUNK_SIZE GdipCacheChunkSize;
    struct TS_GDIPLUS_IMAGE_CACHE_PROPERTIES GdipImageCacheProperties;
};

struct TS_RAIL_CAPABILITYSET
{
    uint16_t capabilitySetType;
    uint16_t lengthCapability;
    uint32_t RailSupportLevel;
};

struct TS_WINDOWLIST_CAPABILITYSET
{
    uint16_t capabilitySetType;
    uint16_t lengthCapability;
    uint32_t WndSupportLevel;
    uint8_t NumIconCaches;
    uint16_t NumIconCacheEntries;
};

struct TS_COMPDESK_CAPABILITYSET
{
    uint16_t capabilitySetType;
    uint16_t lengthCapability;
    uint16_t CompDeskSupportLevel;
};

struct TS_MULTIFRAGMENTUPDATE_CAPABILITYSET
{
    uint16_t capabilitySetType;
    uint16_t lengthCapability;
    uint32_t MaxRequestSize;
};

struct TS_LARGE_POINTER_CAPABILITYSET
{
    uint16_t capabilitySetType;
    uint16_t lengthCapability;
    uint16_t largePointerSupportFlags;
};

struct TS_SURFCMDS_CAPABILITYSET
{
    uint16_t capabilitySetType;
    uint16_t lengthCapability;
    uint32_t cmdFlags;
    uint32_t reserved;
};

struct TS_BITMAPCODECS_CAPABILITYSET
{
    uint16_t capabilitySetType;
    uint16_t lengthCapability;
    char supportedBitmapCodecs[512]; // ?
};


struct TS_FRAME_ACKNOWLEDGE_CAPABILITYSET
{
    uint16_t capabilitySetType;
    uint16_t lengthCapability;
    uint32_t maxUnacknowledgedFrameCount;
};

struct TS_CAPS_SET
{
    struct TS_GENERAL_CAPABILITYSET general;
    struct TS_BITMAP_CAPABILITYSET bitmap;
    struct TS_ORDER_CAPABILITYSET order;
    struct TS_BITMAPCACHE_CAPABILITYSET bitmapcache;
    struct TS_CONTROL_CAPABILITYSET control;
    struct TS_WINDOWACTIVATION_CAPABILITYSET windowactivation;
    struct TS_POINTER_CAPABILITYSET pointer;
    struct TS_SHARE_CAPABILITYSET share;
    struct TS_COLORTABLE_CAPABILITYSET colortable;
    struct TS_SOUND_CAPABILITYSET sound;
    struct TS_INPUT_CAPABILITYSET input;
    struct TS_FONT_CAPABILITYSET font;
    struct TS_BRUSH_CAPABILITYSET brush;
    struct TS_GLYPHCACHE_CAPABILITYSET glyphcache;
    struct TS_OFFSCREEN_CAPABILITYSET offscreen;
    struct TS_BITMAPCACHE_HOSTSUPPORT_CAPABILITYSET bitmapcache_hostsupport;
    struct TS_BITMAPCACHE_CAPABILITYSET_REV2 bitmapcache_rev2;
    struct TS_VIRTUALCHANNEL_CAPABILITYSET vurtualchannel;
    struct TS_DRAW_NINEGRID_CAPABILITYSET draw_ninegrid;
    struct TS_DRAW_GDIPLUS_CAPABILITYSET draw_gdiplus;
    struct TS_RAIL_CAPABILITYSET rail;
    struct TS_WINDOWLIST_CAPABILITYSET windowlist;
    struct TS_COMPDESK_CAPABILITYSET compdesk;
    struct TS_MULTIFRAGMENTUPDATE_CAPABILITYSET multifragmentupdate;
    struct TS_LARGE_POINTER_CAPABILITYSET large_pointer;
    struct TS_SURFCMDS_CAPABILITYSET surfcmds;
    struct TS_BITMAPCODECS_CAPABILITYSET bitmapcodecs;
    struct TS_FRAME_ACKNOWLEDGE_CAPABILITYSET frame_acknowledge;
};

#endif
