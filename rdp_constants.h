
#if !defined(_RDP_CONSTANTS_H)
#define _RDP_CONSTANTS_H

#define MCS_CONNECT_INITIAL                     0x7F65
#define MCS_CONNECT_RESPONSE                    0x7F66

#define BER_TAG_BOOLEAN                         1
#define BER_TAG_INTEGER                         2
#define BER_TAG_OCTET_STRING                    4
#define BER_TAG_RESULT                          10
#define BER_TAG_SEQUENCE                        16
#define BER_TAG_CONSTRUCTED                     0x20
#define BER_TAG_CTXT_SPECIFIC                   0x80

#define MCS_TAG_DOMAIN_PARAMS                   0x30

/* Virtual channel options */
#define CHANNEL_OPTION_SHOW_PROTOCOL            0x00200000
#define CHANNEL_OPTION_COMPRESS                 0x00400000
#define CHANNEL_OPTION_COMPRESS_RDP             0x00800000
#define CHANNEL_OPTION_PRI_LOW                  0x02000000
#define CHANNEL_OPTION_PRI_MED                  0x04000000
#define CHANNEL_OPTION_PRI_HIGH                 0x08000000
#define CHANNEL_OPTION_ENCRYPT_CS               0x10000000
#define CHANNEL_OPTION_ENCRYPT_SC               0x20000000
#define CHANNEL_OPTION_ENCRYPT_RDP              0x40000000
#define CHANNEL_OPTION_INITIALIZED              0x80000000

/* Encryption Methods */
#define CRYPT_METHOD_NONE                       0x00000000
#define CRYPT_METHOD_40BIT                      0x00000001
#define CRYPT_METHOD_128BIT                     0x00000002
#define CRYPT_METHOD_56BIT                      0x00000008
#define CRYPT_METHOD_FIPS                       0x00000010

/* Encryption Levels */
#define CRYPT_LEVEL_NONE                        0x00000000
#define CRYPT_LEVEL_LOW                         0x00000001
#define CRYPT_LEVEL_CLIENT_COMPATIBLE           0x00000002
#define CRYPT_LEVEL_HIGH                        0x00000003
#define CRYPT_LEVEL_FIPS                        0x00000004

/* Client cluster constants */
#define SEC_CC_REDIRECTION_SUPPORTED            0x00000001
#define SEC_CC_REDIRECT_SESSIONID_FIELD_VALID   0x00000002
#define SEC_CC_REDIRECTED_SMARTCARD             0x00000040
#define SEC_CC_REDIRECT_VERSION_MASK            0x0000003c

#define SEC_CC_REDIRECT_VERSION_3               0x02
#define SEC_CC_REDIRECT_VERSION_4               0x03
#define SEC_CC_REDIRECT_VERSION_5               0x04
#define SEC_CC_REDIRECT_VERSION_6               0x05

#define SEC_TAG_SRV_INFO                        0x0c01
#define SEC_TAG_SRV_CRYPT                       0x0c02
#define SEC_TAG_SRV_CHANNELS                    0x0c03

#define MCS_GLOBAL_CHANNEL                      1003
#define MCS_USERCHANNEL_BASE                    1001

/* Logon flags */
#define INFO_MOUSE                              0x00000001
#define INFO_DISABLECTRLALTDEL                  0x00000002
#define INFO_AUTOLOGON                          0x00000008
#define INFO_UNICODE                            0x00000010
#define INFO_MAXIMIZESHELL                      0x00000020
#define INFO_COMPRESSION                        0x00000080	/* mppc compression with 8kB histroy buffer */
#define INFO_ENABLEWINDOWSKEY                   0x00000100
#define INFO_COMPRESSION2                       0x00000200	/* rdp5 mppc compression with 64kB history buffer */
#define INFO_REMOTE_CONSOLE_AUDIO               0x00002000
#define INFO_RAIL                               0x00008000
#define INFO_PASSWORD_IS_SC_PIN                 0x00040000
#define INFO_HIDEF_RAIL_SUPPORTED               0x02000000

#define AF_INET                                 0x0002
#define AF_INET6                                0x0017

/* Extended Info Packet performance flags */
#define IP_PERF_DISABLE_WALLPAPER               0x00000001
#define IP_PERF_DISABLE_FULLWINDOWDRAG          0x00000002
#define IP_PERF_DISABLE_MENUANIMATIONS          0x00000004
#define IP_PERF_DISABLE_THEMING                 0x00000008
#define IP_PERF_RESERVED1                       0x00000010
#define IP_PERF_DISABLE_CURSOR_SHADOW           0x00000020
#define IP_PERF_DISABLE_CURSORSETTINGS          0x00000040
#define IP_PERF_ENABLE_FONT_SMOOTHING           0x00000080
#define IP_PERF_ENABLE_DESKTOP_COMPOSITION      0x00000100
#define IP_PERF_RESERVED2                       0x80000000

/* performance flags */
#define RDP5_DISABLE_NOTHING                    0x00
#define RDP5_NO_WALLPAPER                       0x01
#define RDP5_NO_FULLWINDOWDRAG                  0x02
#define RDP5_NO_MENUANIMATIONS                  0x04
#define RDP5_NO_THEMING                         0x08
#define RDP5_NO_CURSOR_SHADOW                   0x20
#define RDP5_NO_CURSORSETTINGS                  0x40	/* disables cursor blinking */

/* TS_SECURITY_HEADER: see MS-RDPBCGR 2.2.8.1.1.2.1 */
#define SEC_CLIENT_RANDOM                       0x0001
#define SEC_ENCRYPT                             0x0008
#define SEC_LOGON_INFO                          0x0040
#define SEC_LICENCE_NEG                         0x0080

/* Stream IDs used by synchronize PDU */
#define STREAM_UNDEFINED                        0x00    /* Undefined stream priority */
#define STREAM_LOW                              0x01    /* Low-priority stream */
#define STREAM_MED                              0x02    /* Medium-priority stream */
#define STREAM_HI                               0x04    /* High-priority stream */

/* type of data PDU */
#define PDUTYPE2_UPDATE                         0x02    /* Graphics Update PDU(section 2.2.9.1.1.3) */
#define PDUTYPE2_CONTROL                        0x14    /* Control PDU(section 2.2.1.15.1) */
#define PDUTYPE2_POINTER                        0x1B    /* Pointer Update PDU(section 2.2.9.1.1.4) */
#define PDUTYPE2_INPUT                          0x1C    /* Input Event PDU(section 2.2.8.1.1.3) */
#define PDUTYPE2_SYNCHRONIZE                    0x1F    /* Synchronize PDU(section 2.2.1.14.1) */
#define PDUTYPE2_REFRESH_RECT                   0x21    /* Refresh Rect PDU(section 2.2.11.2.1) */
#define PDUTYPE2_PLAY_SOUND                     0x22    /* Play Sound PDU(section 2.2.9.1.1.5.1) */
#define PDUTYPE2_SUPPRESS_OUTPUT                0x23    /* Suppress Output PDU(section 2.2.11.3.1) */
#define PDUTYPE2_SHUTDOWN_REQUEST               0x24    /* Shutdown Request PDU(section 2.2.2.1.1) */
#define PDUTYPE2_SHUTDOWN_DENIED                0x25    /* Shutdown Request Denied PDU(section 2.2.2.2.1) */
#define PDUTYPE2_SAVE_SESSION_INFO              0x26    /* Save Session Info PDU(section 2.2.10.1.1) */
#define PDUTYPE2_FONTLIST                       0x27    /* Font List PDU(section 2.2.1.18.1) */
#define PDUTYPE2_FONTMAP                        0x28    /* Font Map PDU(section 2.2.1.22.1) */
#define PDUTYPE2_SET_KEYBOARD_INDICATORS        0x29    /* Set Keyboard Indicators PDU(section 2.2.8.2.1.1) */
#define PDUTYPE2_BITMAPCACHE_PERSISTENT_LIST    0x2B    /* Persistent Key List PDU(section 2.2.1.17.1) */
#define PDUTYPE2_BITMAPCACHE_ERROR_PDU          0x2C    /* Bitmap Cache Error PDU([MS - RDPEGDI] section 2.2.2.3.1) */
#define PDUTYPE2_SET_KEYBOARD_IME_STATUS        0x2D    /* Set Keyboard IME Status PDU(section 2.2.8.2.2.1) */
#define PDUTYPE2_OFFSCRCACHE_ERROR_PDU          0x2E    /* Offscreen Bitmap Cache Error PDU([MS - RDPEGDI] section 2.2.2.3.2) */
#define PDUTYPE2_SET_ERROR_INFO_PDU             0x2F    /* Set Error Info PDU(section 2.2.5.1.1) */
#define PDUTYPE2_DRAWNINEGRID_ERROR_PDU         0x30    /* DrawNineGrid Cache Error PDU([MS - RDPEGDI] section 2.2.2.3.3) */
#define PDUTYPE2_DRAWGDIPLUS_ERROR_PDU          0x31    /* GDI + Error PDU([MS - RDPEGDI] section 2.2.2.3.4)  */
#define PDUTYPE2_ARC_STATUS_PDU                 0x32    /* Auto - Reconnect Status PDU(section 2.2.4.1.1) */
#define PDUTYPE2_STATUS_INFO_PDU                0x36    /* Status Info PDU(section 2.2.5.2) */
#define PDUTYPE2_MONITOR_LAYOUT_PDU             0x37    /* Monitor Layout PDU(section 2.2.12.1) */
#define PDUTYPE2_FRAME_ACKNOWLEDGE              0x38    /* Send frame acknowledge */
#define PDUTYPE2_KEYBOARD_LAYOUT                0x43    /* Send keyboard layout */

#define CTRLACTION_REQUEST_CONTROL              0x0001 /* Request control */
#define CTRLACTION_GRANTED_CONTROL              0x0002 /* Granted control */
#define CTRLACTION_DETACH                       0x0003 /* Detach */
#define CTRLACTION_COOPERATE                    0x0004 /* Cooperate */

#define CTRLACTION_REQUEST_CONTROL              0x0001
#define CTRLACTION_GRANTED_CONTROL              0x0002
#define CTRLACTION_DETACH                       0x0003
#define CTRLACTION_COOPERATE                    0x0004

#define CODEPAGE_UTF8                           "UTF-8"
#define CODEPAGE_UTF16_LE                       "UTF-16LE"

#define UPDATETYPE_ORDERS                       0x0000  // Indicates an Orders Update ([MS-RDPEGDI] section 2.2.2.2).
#define UPDATETYPE_BITMAP                       0x0001  // Indicates a Bitmap Graphics Update (section 2.2.9.1.1.3.1.2).
#define UPDATETYPE_PALETTE                      0x0002  // Indicates a Palette Update (section 2.2.9.1.1.3.1.1).
#define UPDATETYPE_SYNCHRONIZE                  0x0003  // Indicates a Synchronize Update (section 2.2.9.1.1.3.1.3).

// fastpath update codes
#define FASTPATH_UPDATETYPE_ORDERS              0x0     // Indicates a Fast-Path Orders Update ([MS-RDPEGDI] section 2.2.2.2).
#define FASTPATH_UPDATETYPE_BITMAP              0x1     // Indicates a Fast-Path Bitmap Update (section 2.2.9.1.2.1.2).
#define FASTPATH_UPDATETYPE_PALETTE             0x2     // Indicates a Fast-Path Palette Update (section 2.2.9.1.2.1.1).
#define FASTPATH_UPDATETYPE_SYNCHRONIZE         0x3     // Indicates a Fast-Path Synchronize Update (section 2.2.9.1.2.1.3).
#define FASTPATH_UPDATETYPE_SURFCMDS            0x4     // Indicates a Fast-Path Surface Commands Update (section 2.2.9.1.2.1.10).
#define FASTPATH_UPDATETYPE_PTR_NULL            0x5     // Indicates a Fast-Path System Pointer Hidden Update (section 2.2.9.1.2.1.5).
#define FASTPATH_UPDATETYPE_PTR_DEFAULT         0x6     // Indicates a Fast-Path System Pointer Default Update (section 2.2.9.1.2.1.6).
#define FASTPATH_UPDATETYPE_PTR_POSITION        0x8     // Indicates a Fast-Path Pointer Position Update (section 2.2.9.1.2.1.4).
#define FASTPATH_UPDATETYPE_COLOR               0x9     // Indicates a Fast-Path Color Pointer Update (section 2.2.9.1.2.1.7).
#define FASTPATH_UPDATETYPE_CACHED              0xA     // Indicates a Fast-Path Cached Pointer Update (section 2.2.9.1.2.1.9).
#define FASTPATH_UPDATETYPE_POINTER             0xB     // Indicates a Fast-Path New Pointer Update (section 2.2.9.1.2.1.8).
#define FASTPATH_UPDATETYPE_LARGE_POINTER       0xC     // Indicates a Fast-Path Large Pointer Update (section 2.2.9.1.2.1.11).

// fastpath fragmentation flags
#define FASTPATH_FRAGMENT_SINGLE                0x0     // data in updateData field is not part of a sequence of fragments.
#define FASTPATH_FRAGMENT_LAST                  0x1     // data in updateData field contains the last fragment in a sequence of fragments.
#define FASTPATH_FRAGMENT_FIRST                 0x2     // data in updateData field contains the first fragment in a sequence of fragments.
#define FASTPATH_FRAGMENT_NEXT                  0x3     // data in updateData field contains the second or subsequent fragment in a sequence of fragments.

#define FASTPATH_OUTPUT_COMPRESSION_USED        0x2     // Indicates compressionFlags field is present.
#define FASTPATH_INPUT_ACTION_FASTPATH          0x0     // Indicates the PDU is a fast-path input PDU
#define FASTPATH_INPUT_ACTION_X224              0x3     // Indicates the presence of a TPKT Header initial version byte
#define FASTPATH_INPUT_SECURE_CHECKSUM          0x1     // Indicates MAC signature for PDU was generated using the "salted MAC generation" technique
#define FASTPATH_INPUT_ENCRYPTED                0x2     // Indicates PDU contains 8-byte MAC signature after optional length2 field

// input event codes
#define FASTPATH_INPUT_EVENT_SCANCODE           0x0     // Indicates Fast-Path Keyboard Event (section 2.2.8.1.2.2.1).
#define FASTPATH_INPUT_EVENT_MOUSE              0x1     // Indicates Fast-Path Mouse Event (section 2.2.8.1.2.2.3).
#define FASTPATH_INPUT_EVENT_MOUSEX             0x2     // Indicates Fast-Path Extended Mouse Event (section 2.2.8.1.2.2.4).
#define FASTPATH_INPUT_EVENT_SYNC               0x3     // Indicates Fast-Path Synchronize Event (section 2.2.8.1.2.2.5).
#define FASTPATH_INPUT_EVENT_UNICODE            0x4     // Indicates Fast-Path Unicode Keyboard Event (section 2.2.8.1.2.2.2).
#define FASTPATH_INPUT_EVENT_QOE_TIMESTAMP      0x6     // Indicates Fast-Path Quality of Experience (QoE) Timestamp Event (section 2.2.8.1.2.2.6).

// keyboard events; see section 2.2.8.1.2.2.1 Fast-Path Keyboard Event (TS_FP_KEYBOARD_EVENT)
#define FASTPATH_INPUT_KBDFLAGS_RELEASE         0x01    // Absence of this flag indicates key-down event, while its presence indicates key-release event.
#define FASTPATH_INPUT_KBDFLAGS_EXTENDED        0x02    // Indicates keystroke message contains extended scancode. For enhanced 101-key and
                                                        // 102-key keyboards, extended keys include the right ALT and right CTRL keys on the
                                                        // main section of the keyboard; the INS, DEL, HOME, END, PAGE UP, PAGE DOWN and ARROW
                                                        // keys in the clusters to the left of the numeric keypad; and the Divide ("/") and ENTER
                                                        // keys in the numeric keypad.
#define FASTPATH_INPUT_KBDFLAGS_EXTENDED1       0x04    // Used to send keyboard events triggered by the PAUSE key.
                                                        // A PAUSE key press and release MUST be sent as the following sequence of keyboard events:
                                                        //     CTRL (0x1D) DOWN
                                                        //     NUMLOCK (0x45) DOWN
                                                        //     CTRL (0x1D) UP
                                                        //     NUMLOCK (0x45) UP
                                                        // The CTRL DOWN and CTRL UP events MUST both include the FASTPATH_INPUT_KBDFLAGS_EXTENDED1 flag.

// mouse events
#define PTRFLAGS_HWHEEL                         0x0400  // The event is a horizontal mouse wheel rotation
#define PTRFLAGS_WHEEL                          0x0200  // The event is a vertical mouse wheel rotation.
#define PTRFLAGS_WHEEL_NEGATIVE                 0x0100  // The wheel rotation value (contained in the WheelRotationMask
                                                        // bit field) is negative and MUST be sign-extended before
                                                        // injection at the server.
#define WheelRotationMask                       0x01FF  // The bit field describing the number of rotation units the mouse
                                                        // wheel was rotated. The value is negative if the
                                                        // PTRFLAGS_WHEEL_NEGATIVE flag is set.
#define PTRFLAGS_MOVE                           0x0800  // Indicates that the mouse position MUST be updated to the
                                                        // location specified by the xPos and yPos fields.
#define PTRFLAGS_DOWN                           0x8000  // Indicates that a click event has occurred at the position
                                                        // specified by the xPos and yPos fields. The button flags
                                                        // indicate which button has been clicked and at least one of
                                                        // these flags MUST be set.
#define PTRFLAGS_BUTTON1                        0x1000  // Mouse button 1 (left button) was clicked or released.
                                                        // If the PTRFLAGS_DOWN flag is set, then the button was clicked,
                                                        // otherwise it was released.
#define PTRFLAGS_BUTTON2                        0x2000  // Mouse button 2 (right button) was clicked or released.
                                                        // If the PTRFLAGS_DOWN flag is set, then the button was clicked,
                                                        // otherwise it was released.
#define PTRFLAGS_BUTTON3                        0x4000  // Mouse button 3 (middle button or wheel) was clicked or
                                                        // released. If the PTRFLAGS_DOWN flag is set, then the button
                                                        // was clicked, otherwise it was released.

#define PTRXFLAGS_DOWN                          0x8000  // Indicates that a press event has occurred at the position specified by the xPos and
                                                        // yPos fields. The button flags indicate which button has been pressed and at least
                                                        // one of these flags MUST be set.
#define PTRXFLAGS_BUTTON1                       0x0001  // Extended mouse button 1 (also referred to as button 4) was pressed or released. If
                                                        // the PTRXFLAGS_DOWN flag is set, the button was pressed; otherwise, it was
                                                        // released.
#define PTRXFLAGS_BUTTON2                       0x0002  // Extended mouse button 2 (also referred to as button 5) was pressed or released. If
                                                        // the PTRXFLAGS_DOWN flag is set, the button was pressed; otherwise, it was
                                                        // released.


/* early capabilities flags */
#define RNS_UD_CS_SUPPORT_ERRINFO_PDU           0x0001  // Indicates client supports Set Error Info PDU (section 2.2.5.1).
#define RNS_UD_CS_WANT_32BPP_SESSION            0x0002  // Indicates client is requesting a session color depth of 32 bpp.
#define RNS_UD_CS_SUPPORT_STATUSINFO_PDU        0x0004  // Indicates client supports Server Status Info PDU (section 2.2.5.2).
#define RNS_UD_CS_STRONG_ASYMMETRIC_KEYS        0x0008  // Indicates client supports asymmetric keys larger than 512 bits
                                                        // for use with the Server Certificate (section 2.2.1.4.3.1)
                                                        // sent in the Server Security Data block (section 2.2.1.4.3).
#define RNS_UD_CS_UNUSED                        0x0010  // An unused flag that MUST be ignored by the server.
#define RNS_UD_CS_VALID_CONNECTION_TYPE         0x0020  // Indicates connectionType field contains valid data.
#define RNS_UD_CS_SUPPORT_MONITOR_LAYOUT_PDU    0x0040  // Indicates client supports the Monitor Layout PDU (section 2.2.12.1).
#define RNS_UD_CS_SUPPORT_NETCHAR_AUTODETECT    0x0080  // Indicates client supports network characteristics detection using
                                                        // the structures and PDUs described in section 2.2.14.
#define RNS_UD_CS_SUPPORT_DYNVC_GFX_PROTOCOL    0x0100  // Indicates client supports the Graphics Pipeline Extension Protocol
                                                        // described in [MS-RDPEGFX] sections 1, 2, and 3.
#define RNS_UD_CS_SUPPORT_DYNAMIC_TIME_ZONE     0x0200  // Indicates client supports Dynamic DST. Dynamic DST information is
                                                        // provided by the client in the cbDynamicDSTTimeZoneKeyName,
                                                        // dynamicDSTTimeZoneKeyName and dynamicDaylightTimeDisabled fields
                                                        // of the Extended Info Packet (section 2.2.1.11.1.1.1).
#define RNS_UD_CS_SUPPORT_HEARTBEAT_PDU         0x0400  // Indicates client supports the Heartbeat PDU (section 2.2.16.1).

/* surface command types */
#define CMDTYPE_SET_SURFACE_BITS                0x0001  // Indicates a Set Surface Bits Command (section 2.2.9.2.1).
#define CMDTYPE_FRAME_MARKER                    0x0004  // Indicates a Frame Marker Command (section 2.2.9.2.3).
#define CMDTYPE_STREAM_SURFACE_BITS             0x0006  // Indicates a Stream Surface Bits Command (section 2.2.9.2.2).

#define EX_COMPRESSED_BITMAP_HEADER_PRESENT     0x01    // Indicates that the optional exBitmapDataHeader
                                                        // field is present.

/* surface command frame action */
#define SURFACECMD_FRAMEACTION_BEGIN            0x0000  // Indicates the start of a new frame.
#define SURFACECMD_FRAMEACTION_END              0x0001  // Indicates the end of the current frame.


#define CHANNEL_FLAG_SUSPEND                    0x00000020  // All virtual channel traffic MUST be suspended. This flag is only valid in server-to-client virtual channel traffic. It MUST be ignored in client-to-server data.
#define CHANNEL_FLAG_RESUME                     0x00000040  // All virtual channel traffic MUST be resumed. This flag is only valid in server-to-client virtual channel traffic. It MUST be ignored in client-to-server data.
#define CHANNEL_FLAG_SHADOW_PERSISTENT          0x00000080  // This flag is unused and its value MUST be ignored by the client and server.
#define CHANNEL_PACKET_COMPRESSED               0x00200000  // The virtual channel data is compressed. This flag is equivalent to MPPC bit C (for more information see [RFC2118] section 3.1).

#define CHANNEL_PACKET_AT_FRONT                 0x00400000  // The decompressed packet MUST be placed at the beginning of the history buffer. This flag is equivalent to MPPC bit B (for more information see [RFC2118] section 3.1).
#define CHANNEL_PACKET_FLUSHED                  0x00800000  // The decompressor MUST reinitialize the history buffer (by filling it with zeros) and reset the HistoryOffset to zero. After it has been reinitialized, the entire history buffer is immediately regarded as valid. This flag is equivalent to MPPC bit A (for more information see [RFC2118] section 3.1). If the CHANNEL_PACKET_COMPRESSED (0x00200000) flag is also present, then the CHANNEL_PACKET_FLUSHED flag MUST be processed first.
#define CompressionTypeMask                     0x000F0000  // Indicates the compression package which was used to compress the data. See the discussion which follows this table for a list of compression packages.

// Possible compression types are as follows.
#define PACKET_COMPR_TYPE_8K                    0x0 // RDP 4.0 bulk compression (section 3.1.8.4.1).
#define PACKET_COMPR_TYPE_64K                   0x1 // RDP 5.0 bulk compression (section 3.1.8.4.2).
#define PACKET_COMPR_TYPE_RDP6                  0x2 // RDP 6.0 bulk compression ([MS-RDPEGDI] section 3.1.8.1).
#define PACKET_COMPR_TYPE_RDP61                 0x3 // RDP 6.1 bulk compression ([MS-RDPEGDI] section 3.1.8.2).

/*****************************************************************************
**                  Static virtual channel constants                        **
*****************************************************************************/

#define CHANNEL_FLAG_SUSPEND                    0x00000020  // All virtual channel traffic MUST be suspended. This flag is only valid in server-to-client virtual channel traffic. It MUST be ignored in client-to-server data.
#define CHANNEL_FLAG_RESUME                     0x00000040  // All virtual channel traffic MUST be resumed. This flag is only valid in server-to-client virtual channel traffic. It MUST be ignored in client-to-server data.
#define CHANNEL_FLAG_SHADOW_PERSISTENT          0x00000080  // This flag is unused and its value MUST be ignored by the client and server.
#define CHANNEL_PACKET_COMPRESSED               0x00200000  // The virtual channel data is compressed. This flag is equivalent to MPPC bit C (for more information see [RFC2118] section 3.1).

#define CHANNEL_PACKET_AT_FRONT                 0x00400000  // The decompressed packet MUST be placed at the beginning of the history buffer. This flag is equivalent to MPPC bit B (for more information see [RFC2118] section 3.1).
#define CHANNEL_PACKET_FLUSHED                  0x00800000  // The decompressor MUST reinitialize the history buffer (by filling it with zeros) and reset the HistoryOffset to zero. After it has been reinitialized, the entire history buffer is immediately regarded as valid. This flag is equivalent to MPPC bit A (for more information see [RFC2118] section 3.1). If the CHANNEL_PACKET_COMPRESSED (0x00200000) flag is also present, then the CHANNEL_PACKET_FLUSHED flag MUST be processed first.
#define CompressionTypeMask                     0x000F0000  // Indicates the compression package which was used to compress the data. See the discussion which follows this table for a list of compression packages.

/* ISO PDU codes */
#define ISO_PDU_CR                              0xE0    /* Connection Request */
#define ISO_PDU_CC                              0xD0    /* Connection Confirm */
#define ISO_PDU_DR                              0x80    /* Disconnect Request */
#define ISO_PDU_DT                              0xF0    /* Data */
#define ISO_PDU_ER                              0x70    /* Error */

/* MCS PDU codes */
#define MCS_EDRQ                                1   /* Erect Domain Request */
#define MCS_DPUM                                8   /* Disconnect Provider Ultimatum */
#define MCS_AURQ                                10  /* Attach User Request */
#define MCS_AUCF                                11  /* Attach User Confirm */
#define MCS_CJRQ                                14  /* Channel Join Request */
#define MCS_CJCF                                15  /* Channel Join Confirm */
#define MCS_SDRQ                                25  /* Send Data Request */
#define MCS_SDIN                                26  /* Send Data Indication */

/* TS_SHARECONTROLHEADER PDU type */
#define PDUTYPE_DEMANDACTIVEPDU                 0x1
#define PDUTYPE_CONFIRMACTIVEPDU                0x3
#define PDUTYPE_DEACTIVATEALLPDU                0x6
#define PDUTYPE_DATAPDU                         0x7
#define PDUTYPE_SERVER_REDIR_PKT                0xA

#define CODEC_ID_NONE                           0x00
#define CODEC_ID_NSCODEC                        0x01
#define CODEC_ID_JPEG                           0x02
#define CODEC_ID_REMOTEFX                       0x03
#define CODEC_ID_PNG                            0x04
#define CODEC_ID_H264                           0x05

/* CODEC_GUID_REMOTEFX 0x76772F12BD724463AFB3B73C9C6F7886 */
#define CODEC_GUID_REMOTEFX "\x12\x2F\x77\x76\x72\xBD\x63\x44\xAF\xB3\xB7\x3C\x9C\x6F\x78\x86"

#define CARDP_CAPS_CAPTURE_NON_CAC              0x00000001
#define CBY_CAPS                                0xCBC0
#define CBY_CAPSET                              0xCBC1
#define CLY_CAPSET                              0xCFC0
#define CLW_VERSION_1_0                         0x0100
#define CT_TILE_64x64                           0x0040
#define CLW_COL_CONV_ICT                        0x1
#define CLW_XFORM_DWT_53_A                      0x1
#define CLW_ENTROPY_RLGR1                       0x01
#define CLW_ENTROPY_RLGR3                       0x04

/* CODEC_GUID_JPEG 0x430C9EED1BAF4CE6869ACB8B37B66237*/
#define CODEC_GUID_JPEG "\xE6\x4C\xAF\x1B\xED\x9E\x0C\x43\x86\x9A\xCB\x8B\x37\xB6\x62\x37"

#endif
