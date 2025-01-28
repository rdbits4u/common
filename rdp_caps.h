
#if !defined(_RDP_CAPS_H)
#define _RDP_CAPS_H

#include <stdint.h>

// TS_CAPS_SET
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

#define OSMAJORTYPE_UNSPECIFIED 0x0000  // Unspecified platform
#define OSMAJORTYPE_WINDOWS     0x0001  // Windows platform
#define OSMAJORTYPE_OS2         0x0002  // OS/2 platform
#define OSMAJORTYPE_MACINTOSH   0x0003  // Macintosh platform
#define OSMAJORTYPE_UNIX        0x0004  // UNIX platform
#define OSMAJORTYPE_IOS         0x0005  // iOS platform
#define OSMAJORTYPE_OSX         0x0006  // OS X platform
#define OSMAJORTYPE_ANDROID     0x0007  // Android platform
#define OSMAJORTYPE_CHROME_OS   0x0008  // Chrome OS platform

#define OSMINORTYPE_UNSPECIFIED     0x0000  // Unspecified version
#define OSMINORTYPE_WINDOWS_31X     0x0001  // Windows 3.1x
#define OSMINORTYPE_WINDOWS_95      0x0002  // Windows 95
#define OSMINORTYPE_WINDOWS_NT      0x0003  // Windows NT
#define OSMINORTYPE_OS2_V21         0x0004  // OS/2 2.1
#define OSMINORTYPE_POWER_PC        0x0005  // PowerPC
#define OSMINORTYPE_MACINTOSH       0x0006  // Macintosh
#define OSMINORTYPE_NATIVE_XSERVER  0x0007  // Native X Server
#define OSMINORTYPE_PSEUDO_XSERVER  0x0008  // Pseudo X Server
#define OSMINORTYPE_WINDOWS RT      0x0009  // Windows RT

// TS_GENERAL_CAPABILITYSET::protocolVersion
#define TS_CAPS_PROTOCOLVERSION     0x0200
// TS_GENERAL_CAPABILITYSET::extraFlags
#define FASTPATH_OUTPUT_SUPPORTED   0x0001  // Advertiser supports fast-path output.<24>
#define NO_BITMAP_COMPRESSION_HDR   0x0400  // Advertiser supports excluding the 8-byte Compressed Data Header
#define LONG_CREDENTIALS_SUPPORTED  0x0004  // Advertiser supports long-length credentials for the user name,
                                            // password, or domain name in the Save Session Info PDU
#define AUTORECONNECT_SUPPORTED     0x0008  // Advertiser supports auto-reconnection (section 5.5).
#define ENC_SALTED_CHECKSUM         0x0010  // Advertiser supports salted MAC generation (section 5.3.6.1.1).

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

// TS_BITMAP_CAPABILITYSET::drawingFlags
#define DRAW_ALLOW_DYNAMIC_COLOR_FIDELITY   0x02    // Indicates support for lossy compression of 32 bpp
                                                    // bitmaps by reducing color-fidelity on a per-pixel
                                                    // basis ([MS-RDPEGDI] section 3.1.9.1.4).
#define DRAW_ALLOW_COLOR_SUBSAMPLING        0x04    // Indicates support for chroma subsampling when
                                                    // compressing 32 bpp bitmaps
                                                    // ([MS-RDPEGDI] section 3.1.9.1.3).
#define DRAW_ALLOW_SKIP_ALPHA               0x08    // Indicates that the client supports the removal of
                                                    // the alpha-channel when compressing 32 bpp bitmaps.
                                                    // In this case the alpha is assumed to be 0xFF,
                                                    // meaning the bitmap is opaque.
#define DRAW_UNUSED_FLAG                    0x10    // An unused flag that MUST be ignored by the client
                                                    // if it is present in the server-to-client Bitmap
                                                    // Capability Set.

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

// TS_ORDER_CAPABILITYSET::maximumOrderLevel
#define ORD_LEVEL_1_ORDERS  1

// TS_ORDER_CAPABILITYSET::orderFlags
#define NEGOTIATEORDERSUPPORT   0x0002  // Indicates support for specifying supported drawing orders in the
                                        // orderSupport field. This flag MUST be set.
#define ZEROBOUNDSDELTASSUPPORT 0x0008  // Indicates support for the TS_ZERO_BOUNDS_DELTAS (0x20) flag
                                        // ([MS-RDPEGDI] section 2.2.2.2.1.1.2). The client MUST set this flag.
#define COLORINDEXSUPPORT       0x0020  // Indicates support for sending color indices (not RGB values) in orders.
#define SOLIDPATTERNBRUSHONLY   0x0040  // Indicates that this party can receive only solid and pattern brushes.
#define ORDERFLAGS_EXTRA_FLAGS  0x0080  // Indicates that the orderSupportExFlags field contains valid data.

// TS_ORDER_CAPABILITYSET::orderSupport
#define TS_NEG_DSTBLT_INDEX             0x00    // DstBlt Primary Drawing Order ([MS-RDPEGDI] section 2.2.2.2.1.1.2.1).
#define TS_NEG_PATBLT_INDEX             0x01    // PatBlt Primary Drawing Order ([MS-RDPEGDI] section 2.2.2.2.1.1.2.3)
                                                // and OpaqueRect Primary Drawing Order ([MS-RDPEGDI] section 2.2.2.2.1.1.2.5).
#define TS_NEG_SCRBLT_INDEX             0x02    // ScrBlt Primary Drawing Order ([MS-RDPEGDI] section 2.2.2.2.1.1.2.7).<26>
#define TS_NEG_MEMBLT_INDEX             0x03    // MemBlt Primary Drawing Order ([MS-RDPEGDI] section 2.2.2.2.1.1.2.9).<27>
#define TS_NEG_MEM3BLT_INDEX            0x04    // Mem3Blt Primary Drawing Order ([MS-RDPEGDI] section 2.2.2.2.1.1.2.10).
#define UnusedIndex1                    0x05    // The contents of the byte at this index MUST be ignored.
#define UnusedIndex2                    0x06    // The contents of the byte at this index MUST be ignored.
#define TS_NEG_DRAWNINEGRID_INDEX       0x07    // DrawNineGrid Primary Drawing Order ([MS-RDPEGDI] section 2.2.2.2.1.1.2.21).
#define TS_NEG_LINETO_INDEX             0x08    // LineTo Primary Drawing Order ([MS-RDPEGDI] section 2.2.2.2.1.1.2.11).
#define TS_NEG_MULTI_DRAWNINEGRID_INDEX 0x09    // MultiDrawNineGrid Primary Drawing Order ([MS-RDPEGDI] section 2.2.2.2.1.1.2.22).
#define UnusedIndex3                    0x0A    // The contents of the byte at this index MUST be ignored.
#define TS_NEG_SAVEBITMAP_INDEX         0x0B    // SaveBitmap Primary Drawing Order ([MS-RDPEGDI] section 2.2.2.2.1.1.2.12).
#define UnusedIndex4                    0x0C    // The contents of the byte at this index MUST be ignored.
#define UnusedIndex5                    0x0D    // The contents of the byte at this index MUST be ignored.
#define UnusedIndex6                    0x0E    // The contents of the byte at this index MUST be ignored.
#define TS_NEG_MULTIDSTBLT_INDEX        0x0F    // MultiDstBlt Primary Drawing Order ([MS-RDPEGDI] section 2.2.2.2.1.1.2.2).
#define TS_NEG_MULTIPATBLT_INDEX        0x10    // MultiPatBlt Primary Drawing Order ([MS-RDPEGDI] section 2.2.2.2.1.1.2.4).
#define TS_NEG_MULTISCRBLT_INDEX        0x11    // MultiScrBlt Primary Drawing Order ([MS-RDPEGDI] section 2.2.2.2.1.1.2.8).
#define TS_NEG_MULTIOPAQUERECT_INDEX    0x12    // MultiOpaqueRect Primary Drawing Order ([MS-RDPEGDI] section 2.2.2.2.1.1.2.6).
#define TS_NEG_FAST_INDEX_INDEX         0x13    // FastIndex Primary Drawing Order ([MS-RDPEGDI] section 2.2.2.2.1.1.2.14).
#define TS_NEG_POLYGON_SC_INDEX         0x14    // PolygonSC Primary Drawing Order ([MS-RDPEGDI] section 2.2.2.2.1.1.2.16)
                                                // and PolygonCB Primary Drawing Order ([MS-RDPEGDI] section 2.2.2.2.1.1.2.17).
#define TS_NEG_POLYGON_CB_INDEX         0x15    // PolygonCB Primary Drawing Order ([MS-RDPEGDI] section 2.2.2.2.1.1.2.17)
                                                // and PolygonSC Primary Drawing Order ([MS-RDPEGDI] section 2.2.2.2.1.1.2.16).
#define TS_NEG_POLYLINE_INDEX           0x16    // Polyline Primary Drawing Order ([MS-RDPEGDI] section 2.2.2.2.1.1.2.18).
#define UnusedIndex7                    0x17    // The contents of the byte at this index MUST be ignored.
#define TS_NEG_FAST_GLYPH_INDEX         0x18    // FastGlyph Primary Drawing Order ([MS-RDPEGDI] section 2.2.2.2.1.1.2.15).
#define TS_NEG_ELLIPSE_SC_INDEX         0x19    // EllipseSC Primary Drawing Order ([MS-RDPEGDI] section 2.2.2.2.1.1.2.19)
                                                // and EllipseCB Primary Drawing Order ([MS-RDPEGDI] section 2.2.2.2.1.1.2.20).
#define TS_NEG_ELLIPSE_CB_INDEX         0x1A    // EllipseCB Primary Drawing Order ([MS-RDPEGDI] section 2.2.2.2.1.1.2.20)
                                                // and EllipseSC Primary Drawing Order ([MS-RDPEGDI] section 2.2.2.2.1.1.2.19).
#define TS_NEG_INDEX_INDEX              0x1B    // GlyphIndex Primary Drawing Order ([MS-RDPEGDI] section 2.2.2.2.1.1.2.13).
#define UnusedIndex8                    0x1C    // The contents of the byte at this index MUST be ignored.
#define UnusedIndex9                    0x1D    // The contents of the byte at this index MUST be ignored.
#define UnusedIndex10                   0x1E    // The contents of the byte at this index MUST be ignored.
#define UnusedIndex11                   0x1F    // The contents of the byte at this index MUST be ignored.

// TS_ORDER_CAPABILITYSET::orderSupportExFlags
#define ORDERFLAGS_EX_CACHE_BITMAP_REV3_SUPPORT     0x0002  // The Cache Bitmap (Revision 3) Secondary Drawing Order ([MS-RDPEGDI]
                                                            // section 2.2.2.2.1.2.8) is supported.
#define ORDERFLAGS_EX_ALTSEC_FRAME_MARKER_SUPPORT   0x0004  // The Frame Marker Alternate Secondary Drawing Order ([MS-RDPEGDI]
                                                            // section 2.2.2.2.1.3.7) is supported.
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

// TS_SOUND_CAPABILITYSET::soundFlags
#define SOUND_FLAG_BEEPS    0x0001  // Playing a beep sound is supported.

struct TS_SOUND_CAPABILITYSET
{
    uint16_t capabilitySetType;
    uint16_t lengthCapability;
    uint16_t soundFlags;
    uint16_t pad2octetsA;    
};

// TS_INPUT_CAPABILITYSET::inputFlags
#define INPUT_FLAG_SCANCODES            0x0001  // Indicates support for using scancodes in the Keyboard Event notifications
                                                // (sections 2.2.8.1.1.3.1.1.1 and 2.2.8.1.2.2.1).
#define INPUT_FLAG_MOUSEX               0x0004  // Indicates support for Extended Mouse Event notifications (sections
                                                // 2.2.8.1.1.3.1.1.4 and 2.2.8.1.2.2.4).
#define INPUT_FLAG_FASTPATH_INPUT       0x0008  // Advertised by RDP 5.0 and 5.1 servers to indicate support for fast-path input.
#define INPUT_FLAG_UNICODE              0x0010  // Indicates support for Unicode Keyboard Event notifications (sections
                                                // 2.2.8.1.1.3.1.1.2 and 2.2.8.1.2.2.2).
#define INPUT_FLAG_FASTPATH_INPUT2      0x0020  // Advertised by all RDP servers, except for RDP 4.0, 5.0, and 5.1 servers,
                                                // to indicate support for fast-path input. Clients that do not support this
                                                // flag will not be able to use fast-path input when connecting to RDP 5.2,
                                                // 6.0, 6.1, 7.0, 7.1, 8.0, 8.1, 10.0, 10.1, 10.2, 10.3, 10.4, and 10.5 servers.
#define INPUT_FLAG_UNUSED1              0x0040  // An unused flag that MUST be ignored by the client if it is present in the
                                                // server-to-client Input Capability Set.
#define INPUT_FLAG_MOUSE_RELATIVE       0x0080  // This flag MUST be ignored by the server if it is present in the
                                                // client-to-server Input Capability Set and the protocol version specified
                                                // in the Client Core Data (section 2.2.1.3.2) is less than 0x00080011.
                                                // If the protocol version is greater than or equal to 0x00080011, then
                                                // this flag indicates that the client supports relative mouse mode
                                                // (section 2.2.8.1.1.3.1.1.7 and section 2.2.8.1.2.2.7).
#define TS_INPUT_FLAG_MOUSE_HWHEEL      0x0100  // Indicates support for horizontal Mouse Wheel Event notifications
                                                // (sections 2.2.8.1.1.3.1.1.3 and 2.2.8.1.2.2.3).
#define TS_INPUT_FLAG_QOE_TIMESTAMPS    0x0200  // Indicates support for Quality of Experience (QoE) Timestamp Event
                                                // notifications (section 2.2.8.1.2.2.6). There is no slow-path support
                                                // for Quality of Experience (QoE) timestamps.

// TS_INPUT_CAPABILITYSET::keyboardType
//  0x00000001      IBM PC/XT or compatible (83-key) keyboard
//  0x00000002      Olivetti "ICO" (102-key) keyboard
//  0x00000003      IBM PC/AT (84-key) or similar keyboard
//  0x00000004      IBM enhanced (101- or 102-key) keyboard
//  0x00000005      Nokia 1050 and similar keyboards
//  0x00000006      Nokia 9140 and similar keyboards
//  0x00000007      Japanese keyboard

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

// TS_BRUSH_CAPABILITYSET::brushSupportLevel
#define BRUSH_DEFAULT       0x00000000  // Support for solid-color and monochrome pattern brushes with no caching.
                                        // This is an RDP 4.0 implementation.
#define BRUSH_COLOR_8x8     0x00000001  // Ability to handle color brushes (4-bit or 8-bit in RDP 5.0; 4-bit, 8-bit,
                                        // 16-bit, or 24-bit in all other RDP versions, except for RDP 4.0) and caching.
                                        // Brushes are limited to 8-by-8 pixels.
#define BRUSH_COLOR_FULL    0x00000002  // Ability to handle color brushes (4-bit or 8-bit in RDP 5.0; 4-bit, 8-bit,
                                        // 16-bit, or 24-bit in all other RDP versions, except for RDP 4.0) and caching.
                                        // Brushes can have arbitrary dimensions.

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

// TS_VIRTUALCHANNEL_CAPABILITYSET::flags
#define VCCAPS_NO_COMPR     0x00000000  // Virtual channel compression is not supported.
#define VCCAPS_COMPR_SC     0x00000001  // Indicates to the server that virtual channel compression is supported by the
                                        // client for server-to-client traffic. The highest compression level supported
                                        // by the client is advertised in the Client Info PDU (section 2.2.1.11).
#define VCCAPS_COMPR_CS_8K  0x00000002  // Indicates to the client that virtual channel compression is supported by the
                                        // server for client-to-server traffic (the compression level is limited to
                                        // RDP 4.0 bulk compression).

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

// subset of TS_CAPS_SET for client
struct client_caps
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
    struct TS_BITMAPCACHE_CAPABILITYSET_REV2 bitmapcache_rev2;
    struct TS_VIRTUALCHANNEL_CAPABILITYSET virtualchannel;
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

// subset of TS_CAPS_SET for server
struct server_caps
{
    struct TS_GENERAL_CAPABILITYSET general;
    struct TS_BITMAP_CAPABILITYSET bitmap;
    struct TS_ORDER_CAPABILITYSET order;
    struct TS_POINTER_CAPABILITYSET pointer;
    struct TS_SHARE_CAPABILITYSET share;
    struct TS_COLORTABLE_CAPABILITYSET colortable;
    struct TS_INPUT_CAPABILITYSET input;
    struct TS_FONT_CAPABILITYSET font;
    struct TS_BITMAPCACHE_HOSTSUPPORT_CAPABILITYSET bitmapcache_hostsupport;
    struct TS_VIRTUALCHANNEL_CAPABILITYSET virtualchannel;
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
