#pragma once
#ifdef __APPLE__
#include <CUESDK/CUESDK.h>
#else
#include <CUESDK.h>
#endif
#include "lua.hpp"
#include "luahelpers.h"
//#include "lcuelib_led.h"
#include "lcuelib_device.h"

const char* ErrorToString(CorsairError error);
LUALIB_API int luaopen_cue(lua_State* L);
void cue_PushProtocolDetails(lua_State* L, const CorsairProtocolDetails prot);

typedef struct EnumLookup {
	const char* name;
	int en;
} EnumLookup;

#define EnumToString(en) static const EnumLookup en ## Set[]

EnumToString(CorsairDeviceType) = {
	{"CDT_Unknown", CDT_Unknown},
	{"CDT_Mouse", CDT_Mouse},
	{"CDT_Keyboard", CDT_Keyboard},
	{"CDT_Headset", CDT_Headset},
	{"CDT_MouseMat", CDT_MouseMat},
	{"CDT_HeadsetStand", CDT_HeadsetStand},
	{"CDT_CommanderPro", CDT_CommanderPro},
	{"CDT_LightingNodePro", CDT_LightingNodePro},
	{"CDT_MemoryModule", CDT_MemoryModule},
	{"CDT_Cooler", CDT_Cooler},
	{NULL,NULL}
};

EnumToString(CorsairPhysicalLayout) = {
	{"CPL_Invalid", CPL_Invalid},

	{"CPL_US", CPL_US},
	{"CPL_UK", CPL_UK},
	{"CPL_BR", CPL_BR},
	{"CPL_JP", CPL_JP},
	{"CPL_KR", CPL_KR},

	{"CPL_Zones1", CPL_Zones1},
	{"CPL_Zones2", CPL_Zones2},
	{"CPL_Zones3", CPL_Zones3},
	{"CPL_Zones4", CPL_Zones4},
	{NULL,NULL}
};

EnumToString(CorsairLogicalLayout) = {
	{"CLL_Invalid", CLL_Invalid},
	{"CLL_US_Int", CLL_US_Int},
	{"CLL_NA", CLL_NA},
	{"CLL_EU", CLL_EU},
	{"CLL_UK", CLL_UK},
	{"CLL_BE", CLL_BE},
	{"CLL_BR", CLL_BR},
	{"CLL_CH", CLL_CH},
	{"CLL_CN", CLL_CN},
	{"CLL_DE", CLL_DE},
	{"CLL_ES", CLL_ES},
	{"CLL_FR", CLL_FR},
	{"CLL_IT", CLL_IT},
	{"CLL_ND", CLL_ND},
	{"CLL_RU", CLL_RU},
	{"CLL_JP", CLL_JP},
	{"CLL_KR", CLL_KR},
	{"CLL_TW", CLL_TW},
	{"CLL_MEX", CLL_MEX},
	{NULL,NULL}
};

EnumToString(CorsairDeviceCaps) = {
	{"CDC_None", CDC_None},
	{"CDC_Lighting", CDC_Lighting},
	{"CDC_PropertyLookup", CDC_PropertyLookup},
	{NULL,NULL}
};

EnumToString(CorsairAccessMode) = {
	{"CAM_ExclusiveLightingControl", CAM_ExclusiveLightingControl},
	{NULL,NULL}
};

EnumToString(CorsairError) = {
	{"CE_Success", CE_Success},
	{"CE_ServerNotFound", CE_ServerNotFound},
	{"CE_NoControl", CE_NoControl},
	{"CE_ProtocolHandshakeMissing", CE_ProtocolHandshakeMissing},
	{"CE_IncompatibleProtocol", CE_IncompatibleProtocol},
	{"CE_InvalidArguments", CE_InvalidArguments},
	{NULL,NULL}
};

EnumToString(CorsairChannelDeviceType) = {
	{"CCDT_Invalid", CCDT_Invalid},
	{"CCDT_HD_Fan", CCDT_HD_Fan},
	{"CCDT_SP_Fan", CCDT_SP_Fan},
	{"CCDT_LL_Fan", CCDT_LL_Fan},
	{"CCDT_ML_Fan", CCDT_ML_Fan},
	{"CCDT_Strip", CCDT_Strip},
	{"CCDT_DAP", CCDT_DAP},
	{"CCDT_Pump", CCDT_Pump},
	{NULL,NULL}
};

EnumToString(CorsairDevicePropertyType) = {
	{"CDPT_Boolean", CDPT_Boolean},
	{"CDPT_Int32", CDPT_Int32},
	{NULL,NULL}
};

EnumToString(CorsairDevicePropertyId) = {
	{"CDPI_Headset_MicEnabled", CDPI_Headset_MicEnabled},
	{"CDPI_Headset_SurroundSoundEnabled", CDPI_Headset_SurroundSoundEnabled},
	{"CDPI_Headset_SidetoneEnabled", CDPI_Headset_SidetoneEnabled},
	{"CDPI_Headset_EqualizerPreset", CDPI_Headset_EqualizerPreset},
	{NULL,NULL}
};

EnumToString(CorsairEventId) = {
	{"CEI_Invalid", CEI_Invalid},
	{"CEI_DeviceConnectionStatusChangedEvent", CEI_DeviceConnectionStatusChangedEvent},
	{"CEI_KeyEvent", CEI_KeyEvent},
	{NULL,NULL}
};

EnumToString(CorsairLedId) = {
	{"CLI_Invalid", CLI_Invalid},
	{"CLK_Escape", CLK_Escape},
	{"CLK_F1", CLK_F1},
	{"CLK_F2", CLK_F2},
	{"CLK_F3", CLK_F3},
	{"CLK_F4", CLK_F4},
	{"CLK_F5", CLK_F5},
	{"CLK_F6", CLK_F6},
	{"CLK_F7", CLK_F7},
	{"CLK_F8", CLK_F8},
	{"CLK_F9", CLK_F9},
	{"CLK_F10", CLK_F10},
	{"CLK_F11", CLK_F11},
	{"CLK_GraveAccentAndTilde", CLK_GraveAccentAndTilde},
	{"CLK_1", CLK_1},
	{"CLK_2", CLK_2},
	{"CLK_3", CLK_3},
	{"CLK_4", CLK_4},
	{"CLK_5", CLK_5},
	{"CLK_6", CLK_6},
	{"CLK_7", CLK_7},
	{"CLK_8", CLK_8},
	{"CLK_9", CLK_9},
	{"CLK_0", CLK_0},
	{"CLK_MinusAndUnderscore", CLK_MinusAndUnderscore},
	{"CLK_Tab", CLK_Tab},
	{"CLK_Q", CLK_Q},
	{"CLK_W", CLK_W},
	{"CLK_E", CLK_E},
	{"CLK_R", CLK_R},
	{"CLK_T", CLK_T},
	{"CLK_Y", CLK_Y},
	{"CLK_U", CLK_U},
	{"CLK_I", CLK_I},
	{"CLK_O", CLK_O},
	{"CLK_P", CLK_P},
	{"CLK_BracketLeft", CLK_BracketLeft},
	{"CLK_CapsLock", CLK_CapsLock},
	{"CLK_A", CLK_A},
	{"CLK_S", CLK_S},
	{"CLK_D", CLK_D},
	{"CLK_F", CLK_F},
	{"CLK_G", CLK_G},
	{"CLK_H", CLK_H},
	{"CLK_J", CLK_J},
	{"CLK_K", CLK_K},
	{"CLK_L", CLK_L},
	{"CLK_SemicolonAndColon", CLK_SemicolonAndColon},
	{"CLK_ApostropheAndDoubleQuote", CLK_ApostropheAndDoubleQuote},
	{"CLK_LeftShift", CLK_LeftShift},
	{"CLK_NonUsBackslash", CLK_NonUsBackslash},
	{"CLK_Z", CLK_Z},
	{"CLK_X", CLK_X},
	{"CLK_C", CLK_C},
	{"CLK_V", CLK_V},
	{"CLK_B", CLK_B},
	{"CLK_N", CLK_N},
	{"CLK_M", CLK_M},
	{"CLK_CommaAndLessThan", CLK_CommaAndLessThan},
	{"CLK_PeriodAndBiggerThan", CLK_PeriodAndBiggerThan},
	{"CLK_SlashAndQuestionMark", CLK_SlashAndQuestionMark},
	{"CLK_LeftCtrl", CLK_LeftCtrl},
	{"CLK_LeftGui", CLK_LeftGui},
	{"CLK_LeftAlt", CLK_LeftAlt},
	{"CLK_Lang2", CLK_Lang2},
	{"CLK_Space", CLK_Space},
	{"CLK_Lang1", CLK_Lang1},
	{"CLK_International2", CLK_International2},
	{"CLK_RightAlt", CLK_RightAlt},
	{"CLK_RightGui", CLK_RightGui},
	{"CLK_Application", CLK_Application},
	{"CLK_LedProgramming", CLK_LedProgramming},
	{"CLK_Brightness", CLK_Brightness},
	{"CLK_F12", CLK_F12},
	{"CLK_PrintScreen", CLK_PrintScreen},
	{"CLK_ScrollLock", CLK_ScrollLock},
	{"CLK_PauseBreak", CLK_PauseBreak},
	{"CLK_Insert", CLK_Insert},
	{"CLK_Home", CLK_Home},
	{"CLK_PageUp", CLK_PageUp},
	{"CLK_BracketRight", CLK_BracketRight},
	{"CLK_Backslash", CLK_Backslash},
	{"CLK_NonUsTilde", CLK_NonUsTilde},
	{"CLK_Enter", CLK_Enter},
	{"CLK_International1", CLK_International1},
	{"CLK_EqualsAndPlus", CLK_EqualsAndPlus},
	{"CLK_International3", CLK_International3},
	{"CLK_Backspace", CLK_Backspace},
	{"CLK_Delete", CLK_Delete},
	{"CLK_End", CLK_End},
	{"CLK_PageDown", CLK_PageDown},
	{"CLK_RightShift", CLK_RightShift},
	{"CLK_RightCtrl", CLK_RightCtrl},
	{"CLK_UpArrow", CLK_UpArrow},
	{"CLK_LeftArrow", CLK_LeftArrow},
	{"CLK_DownArrow", CLK_DownArrow},
	{"CLK_RightArrow", CLK_RightArrow},
	{"CLK_WinLock", CLK_WinLock},
	{"CLK_Mute", CLK_Mute},
	{"CLK_Stop", CLK_Stop},
	{"CLK_ScanPreviousTrack", CLK_ScanPreviousTrack},
	{"CLK_PlayPause", CLK_PlayPause},
	{"CLK_ScanNextTrack", CLK_ScanNextTrack},
	{"CLK_NumLock", CLK_NumLock},
	{"CLK_KeypadSlash", CLK_KeypadSlash},
	{"CLK_KeypadAsterisk", CLK_KeypadAsterisk},
	{"CLK_KeypadMinus", CLK_KeypadMinus},
	{"CLK_KeypadPlus", CLK_KeypadPlus},
	{"CLK_KeypadEnter", CLK_KeypadEnter},
	{"CLK_Keypad7", CLK_Keypad7},
	{"CLK_Keypad8", CLK_Keypad8},
	{"CLK_Keypad9", CLK_Keypad9},
	{"CLK_KeypadComma", CLK_KeypadComma},
	{"CLK_Keypad4", CLK_Keypad4},
	{"CLK_Keypad5", CLK_Keypad5},
	{"CLK_Keypad6", CLK_Keypad6},
	{"CLK_Keypad1", CLK_Keypad1},
	{"CLK_Keypad2", CLK_Keypad2},
	{"CLK_Keypad3", CLK_Keypad3},
	{"CLK_Keypad0", CLK_Keypad0},
	{"CLK_KeypadPeriodAndDelete", CLK_KeypadPeriodAndDelete},
	{"CLK_G1", CLK_G1},
	{"CLK_G2", CLK_G2},
	{"CLK_G3", CLK_G3},
	{"CLK_G4", CLK_G4},
	{"CLK_G5", CLK_G5},
	{"CLK_G6", CLK_G6},
	{"CLK_G7", CLK_G7},
	{"CLK_G8", CLK_G8},
	{"CLK_G9", CLK_G9},
	{"CLK_G10", CLK_G10},
	{"CLK_VolumeUp", CLK_VolumeUp},
	{"CLK_VolumeDown", CLK_VolumeDown},
	{"CLK_MR", CLK_MR},
	{"CLK_M1", CLK_M1},
	{"CLK_M2", CLK_M2},
	{"CLK_M3", CLK_M3},
	{"CLK_G11", CLK_G11},
	{"CLK_G12", CLK_G12},
	{"CLK_G13", CLK_G13},
	{"CLK_G14", CLK_G14},
	{"CLK_G15", CLK_G15},
	{"CLK_G16", CLK_G16},
	{"CLK_G17", CLK_G17},
	{"CLK_G18", CLK_G18},
	{"CLK_International5", CLK_International5},
	{"CLK_International4", CLK_International4},
	{"CLK_Fn", CLK_Fn},

	{"CLM_1", CLM_1},
	{"CLM_2", CLM_2},
	{"CLM_3", CLM_3},
	{"CLM_4", CLM_4},

	{"CLH_LeftLogo", CLH_LeftLogo},
	{"CLH_RightLogo", CLH_RightLogo},

	{"CLK_Logo", CLK_Logo},

	{"CLMM_Zone1", CLMM_Zone1},
	{"CLMM_Zone2", CLMM_Zone2},
	{"CLMM_Zone3", CLMM_Zone3},
	{"CLMM_Zone4", CLMM_Zone4},
	{"CLMM_Zone5", CLMM_Zone5},
	{"CLMM_Zone6", CLMM_Zone6},
	{"CLMM_Zone7", CLMM_Zone7},
	{"CLMM_Zone8", CLMM_Zone8},
	{"CLMM_Zone9", CLMM_Zone9},
	{"CLMM_Zone10", CLMM_Zone10},
	{"CLMM_Zone11", CLMM_Zone11},
	{"CLMM_Zone12", CLMM_Zone12},
	{"CLMM_Zone13", CLMM_Zone13},
	{"CLMM_Zone14", CLMM_Zone14},
	{"CLMM_Zone15", CLMM_Zone15},

	{"CLKLP_Zone1", CLKLP_Zone1},
	{"CLKLP_Zone2", CLKLP_Zone2},
	{"CLKLP_Zone3", CLKLP_Zone3},
	{"CLKLP_Zone4", CLKLP_Zone4},
	{"CLKLP_Zone5", CLKLP_Zone5},
	{"CLKLP_Zone6", CLKLP_Zone6},
	{"CLKLP_Zone7", CLKLP_Zone7},
	{"CLKLP_Zone8", CLKLP_Zone8},
	{"CLKLP_Zone9", CLKLP_Zone9},
	{"CLKLP_Zone10", CLKLP_Zone10},
	{"CLKLP_Zone11", CLKLP_Zone11},
	{"CLKLP_Zone12", CLKLP_Zone12},
	{"CLKLP_Zone13", CLKLP_Zone13},
	{"CLKLP_Zone14", CLKLP_Zone14},
	{"CLKLP_Zone15", CLKLP_Zone15},
	{"CLKLP_Zone16", CLKLP_Zone16},
	{"CLKLP_Zone17", CLKLP_Zone17},
	{"CLKLP_Zone18", CLKLP_Zone18},
	{"CLKLP_Zone19", CLKLP_Zone19},

	{"CLM_5", CLM_5},
	{"CLM_6", CLM_6},

	{"CLHSS_Zone1", CLHSS_Zone1},
	{"CLHSS_Zone2", CLHSS_Zone2},
	{"CLHSS_Zone3", CLHSS_Zone3},
	{"CLHSS_Zone4", CLHSS_Zone4},
	{"CLHSS_Zone5", CLHSS_Zone5},
	{"CLHSS_Zone6", CLHSS_Zone6},
	{"CLHSS_Zone7", CLHSS_Zone7},
	{"CLHSS_Zone8", CLHSS_Zone8},
	{"CLHSS_Zone9", CLHSS_Zone9},

	{"CLD_C1_1", CLD_C1_1},
	{"CLD_C1_2", CLD_C1_2},
	{"CLD_C1_3", CLD_C1_3},
	{"CLD_C1_4", CLD_C1_4},
	{"CLD_C1_5", CLD_C1_5},
	{"CLD_C1_6", CLD_C1_6},
	{"CLD_C1_7", CLD_C1_7},
	{"CLD_C1_8", CLD_C1_8},
	{"CLD_C1_9", CLD_C1_9},
	{"CLD_C1_10", CLD_C1_10},
	{"CLD_C1_11", CLD_C1_11},
	{"CLD_C1_12", CLD_C1_12},
	{"CLD_C1_13", CLD_C1_13},
	{"CLD_C1_14", CLD_C1_14},
	{"CLD_C1_15", CLD_C1_15},
	{"CLD_C1_16", CLD_C1_16},
	{"CLD_C1_17", CLD_C1_17},
	{"CLD_C1_18", CLD_C1_18},
	{"CLD_C1_19", CLD_C1_19},
	{"CLD_C1_20", CLD_C1_20},
	{"CLD_C1_21", CLD_C1_21},
	{"CLD_C1_22", CLD_C1_22},
	{"CLD_C1_23", CLD_C1_23},
	{"CLD_C1_24", CLD_C1_24},
	{"CLD_C1_25", CLD_C1_25},
	{"CLD_C1_26", CLD_C1_26},
	{"CLD_C1_27", CLD_C1_27},
	{"CLD_C1_28", CLD_C1_28},
	{"CLD_C1_29", CLD_C1_29},
	{"CLD_C1_30", CLD_C1_30},
	{"CLD_C1_31", CLD_C1_31},
	{"CLD_C1_32", CLD_C1_32},
	{"CLD_C1_33", CLD_C1_33},
	{"CLD_C1_34", CLD_C1_34},
	{"CLD_C1_35", CLD_C1_35},
	{"CLD_C1_36", CLD_C1_36},
	{"CLD_C1_37", CLD_C1_37},
	{"CLD_C1_38", CLD_C1_38},
	{"CLD_C1_39", CLD_C1_39},
	{"CLD_C1_40", CLD_C1_40},
	{"CLD_C1_41", CLD_C1_41},
	{"CLD_C1_42", CLD_C1_42},
	{"CLD_C1_43", CLD_C1_43},
	{"CLD_C1_44", CLD_C1_44},
	{"CLD_C1_45", CLD_C1_45},
	{"CLD_C1_46", CLD_C1_46},
	{"CLD_C1_47", CLD_C1_47},
	{"CLD_C1_48", CLD_C1_48},
	{"CLD_C1_49", CLD_C1_49},
	{"CLD_C1_50", CLD_C1_50},
	{"CLD_C1_51", CLD_C1_51},
	{"CLD_C1_52", CLD_C1_52},
	{"CLD_C1_53", CLD_C1_53},
	{"CLD_C1_54", CLD_C1_54},
	{"CLD_C1_55", CLD_C1_55},
	{"CLD_C1_56", CLD_C1_56},
	{"CLD_C1_57", CLD_C1_57},
	{"CLD_C1_58", CLD_C1_58},
	{"CLD_C1_59", CLD_C1_59},
	{"CLD_C1_60", CLD_C1_60},
	{"CLD_C1_61", CLD_C1_61},
	{"CLD_C1_62", CLD_C1_62},
	{"CLD_C1_63", CLD_C1_63},
	{"CLD_C1_64", CLD_C1_64},
	{"CLD_C1_65", CLD_C1_65},
	{"CLD_C1_66", CLD_C1_66},
	{"CLD_C1_67", CLD_C1_67},
	{"CLD_C1_68", CLD_C1_68},
	{"CLD_C1_69", CLD_C1_69},
	{"CLD_C1_70", CLD_C1_70},
	{"CLD_C1_71", CLD_C1_71},
	{"CLD_C1_72", CLD_C1_72},
	{"CLD_C1_73", CLD_C1_73},
	{"CLD_C1_74", CLD_C1_74},
	{"CLD_C1_75", CLD_C1_75},
	{"CLD_C1_76", CLD_C1_76},
	{"CLD_C1_77", CLD_C1_77},
	{"CLD_C1_78", CLD_C1_78},
	{"CLD_C1_79", CLD_C1_79},
	{"CLD_C1_80", CLD_C1_80},
	{"CLD_C1_81", CLD_C1_81},
	{"CLD_C1_82", CLD_C1_82},
	{"CLD_C1_83", CLD_C1_83},
	{"CLD_C1_84", CLD_C1_84},
	{"CLD_C1_85", CLD_C1_85},
	{"CLD_C1_86", CLD_C1_86},
	{"CLD_C1_87", CLD_C1_87},
	{"CLD_C1_88", CLD_C1_88},
	{"CLD_C1_89", CLD_C1_89},
	{"CLD_C1_90", CLD_C1_90},
	{"CLD_C1_91", CLD_C1_91},
	{"CLD_C1_92", CLD_C1_92},
	{"CLD_C1_93", CLD_C1_93},
	{"CLD_C1_94", CLD_C1_94},
	{"CLD_C1_95", CLD_C1_95},
	{"CLD_C1_96", CLD_C1_96},
	{"CLD_C1_97", CLD_C1_97},
	{"CLD_C1_98", CLD_C1_98},
	{"CLD_C1_99", CLD_C1_99},
	{"CLD_C1_100", CLD_C1_100},
	{"CLD_C1_101", CLD_C1_101},
	{"CLD_C1_102", CLD_C1_102},
	{"CLD_C1_103", CLD_C1_103},
	{"CLD_C1_104", CLD_C1_104},
	{"CLD_C1_105", CLD_C1_105},
	{"CLD_C1_106", CLD_C1_106},
	{"CLD_C1_107", CLD_C1_107},
	{"CLD_C1_108", CLD_C1_108},
	{"CLD_C1_109", CLD_C1_109},
	{"CLD_C1_110", CLD_C1_110},
	{"CLD_C1_111", CLD_C1_111},
	{"CLD_C1_112", CLD_C1_112},
	{"CLD_C1_113", CLD_C1_113},
	{"CLD_C1_114", CLD_C1_114},
	{"CLD_C1_115", CLD_C1_115},
	{"CLD_C1_116", CLD_C1_116},
	{"CLD_C1_117", CLD_C1_117},
	{"CLD_C1_118", CLD_C1_118},
	{"CLD_C1_119", CLD_C1_119},
	{"CLD_C1_120", CLD_C1_120},
	{"CLD_C1_121", CLD_C1_121},
	{"CLD_C1_122", CLD_C1_122},
	{"CLD_C1_123", CLD_C1_123},
	{"CLD_C1_124", CLD_C1_124},
	{"CLD_C1_125", CLD_C1_125},
	{"CLD_C1_126", CLD_C1_126},
	{"CLD_C1_127", CLD_C1_127},
	{"CLD_C1_128", CLD_C1_128},
	{"CLD_C1_129", CLD_C1_129},
	{"CLD_C1_130", CLD_C1_130},
	{"CLD_C1_131", CLD_C1_131},
	{"CLD_C1_132", CLD_C1_132},
	{"CLD_C1_133", CLD_C1_133},
	{"CLD_C1_134", CLD_C1_134},
	{"CLD_C1_135", CLD_C1_135},
	{"CLD_C1_136", CLD_C1_136},
	{"CLD_C1_137", CLD_C1_137},
	{"CLD_C1_138", CLD_C1_138},
	{"CLD_C1_139", CLD_C1_139},
	{"CLD_C1_140", CLD_C1_140},
	{"CLD_C1_141", CLD_C1_141},
	{"CLD_C1_142", CLD_C1_142},
	{"CLD_C1_143", CLD_C1_143},
	{"CLD_C1_144", CLD_C1_144},
	{"CLD_C1_145", CLD_C1_145},
	{"CLD_C1_146", CLD_C1_146},
	{"CLD_C1_147", CLD_C1_147},
	{"CLD_C1_148", CLD_C1_148},
	{"CLD_C1_149", CLD_C1_149},
	{"CLD_C1_150", CLD_C1_150},

	{"CLD_C2_1", CLD_C2_1},
	{"CLD_C2_2", CLD_C2_2},
	{"CLD_C2_3", CLD_C2_3},
	{"CLD_C2_4", CLD_C2_4},
	{"CLD_C2_5", CLD_C2_5},
	{"CLD_C2_6", CLD_C2_6},
	{"CLD_C2_7", CLD_C2_7},
	{"CLD_C2_8", CLD_C2_8},
	{"CLD_C2_9", CLD_C2_9},
	{"CLD_C2_10", CLD_C2_10},
	{"CLD_C2_11", CLD_C2_11},
	{"CLD_C2_12", CLD_C2_12},
	{"CLD_C2_13", CLD_C2_13},
	{"CLD_C2_14", CLD_C2_14},
	{"CLD_C2_15", CLD_C2_15},
	{"CLD_C2_16", CLD_C2_16},
	{"CLD_C2_17", CLD_C2_17},
	{"CLD_C2_18", CLD_C2_18},
	{"CLD_C2_19", CLD_C2_19},
	{"CLD_C2_20", CLD_C2_20},
	{"CLD_C2_21", CLD_C2_21},
	{"CLD_C2_22", CLD_C2_22},
	{"CLD_C2_23", CLD_C2_23},
	{"CLD_C2_24", CLD_C2_24},
	{"CLD_C2_25", CLD_C2_25},
	{"CLD_C2_26", CLD_C2_26},
	{"CLD_C2_27", CLD_C2_27},
	{"CLD_C2_28", CLD_C2_28},
	{"CLD_C2_29", CLD_C2_29},
	{"CLD_C2_30", CLD_C2_30},
	{"CLD_C2_31", CLD_C2_31},
	{"CLD_C2_32", CLD_C2_32},
	{"CLD_C2_33", CLD_C2_33},
	{"CLD_C2_34", CLD_C2_34},
	{"CLD_C2_35", CLD_C2_35},
	{"CLD_C2_36", CLD_C2_36},
	{"CLD_C2_37", CLD_C2_37},
	{"CLD_C2_38", CLD_C2_38},
	{"CLD_C2_39", CLD_C2_39},
	{"CLD_C2_40", CLD_C2_40},
	{"CLD_C2_41", CLD_C2_41},
	{"CLD_C2_42", CLD_C2_42},
	{"CLD_C2_43", CLD_C2_43},
	{"CLD_C2_44", CLD_C2_44},
	{"CLD_C2_45", CLD_C2_45},
	{"CLD_C2_46", CLD_C2_46},
	{"CLD_C2_47", CLD_C2_47},
	{"CLD_C2_48", CLD_C2_48},
	{"CLD_C2_49", CLD_C2_49},
	{"CLD_C2_50", CLD_C2_50},
	{"CLD_C2_51", CLD_C2_51},
	{"CLD_C2_52", CLD_C2_52},
	{"CLD_C2_53", CLD_C2_53},
	{"CLD_C2_54", CLD_C2_54},
	{"CLD_C2_55", CLD_C2_55},
	{"CLD_C2_56", CLD_C2_56},
	{"CLD_C2_57", CLD_C2_57},
	{"CLD_C2_58", CLD_C2_58},
	{"CLD_C2_59", CLD_C2_59},
	{"CLD_C2_60", CLD_C2_60},
	{"CLD_C2_61", CLD_C2_61},
	{"CLD_C2_62", CLD_C2_62},
	{"CLD_C2_63", CLD_C2_63},
	{"CLD_C2_64", CLD_C2_64},
	{"CLD_C2_65", CLD_C2_65},
	{"CLD_C2_66", CLD_C2_66},
	{"CLD_C2_67", CLD_C2_67},
	{"CLD_C2_68", CLD_C2_68},
	{"CLD_C2_69", CLD_C2_69},
	{"CLD_C2_70", CLD_C2_70},
	{"CLD_C2_71", CLD_C2_71},
	{"CLD_C2_72", CLD_C2_72},
	{"CLD_C2_73", CLD_C2_73},
	{"CLD_C2_74", CLD_C2_74},
	{"CLD_C2_75", CLD_C2_75},
	{"CLD_C2_76", CLD_C2_76},
	{"CLD_C2_77", CLD_C2_77},
	{"CLD_C2_78", CLD_C2_78},
	{"CLD_C2_79", CLD_C2_79},
	{"CLD_C2_80", CLD_C2_80},
	{"CLD_C2_81", CLD_C2_81},
	{"CLD_C2_82", CLD_C2_82},
	{"CLD_C2_83", CLD_C2_83},
	{"CLD_C2_84", CLD_C2_84},
	{"CLD_C2_85", CLD_C2_85},
	{"CLD_C2_86", CLD_C2_86},
	{"CLD_C2_87", CLD_C2_87},
	{"CLD_C2_88", CLD_C2_88},
	{"CLD_C2_89", CLD_C2_89},
	{"CLD_C2_90", CLD_C2_90},
	{"CLD_C2_91", CLD_C2_91},
	{"CLD_C2_92", CLD_C2_92},
	{"CLD_C2_93", CLD_C2_93},
	{"CLD_C2_94", CLD_C2_94},
	{"CLD_C2_95", CLD_C2_95},
	{"CLD_C2_96", CLD_C2_96},
	{"CLD_C2_97", CLD_C2_97},
	{"CLD_C2_98", CLD_C2_98},
	{"CLD_C2_99", CLD_C2_99},
	{"CLD_C2_100", CLD_C2_100},
	{"CLD_C2_101", CLD_C2_101},
	{"CLD_C2_102", CLD_C2_102},
	{"CLD_C2_103", CLD_C2_103},
	{"CLD_C2_104", CLD_C2_104},
	{"CLD_C2_105", CLD_C2_105},
	{"CLD_C2_106", CLD_C2_106},
	{"CLD_C2_107", CLD_C2_107},
	{"CLD_C2_108", CLD_C2_108},
	{"CLD_C2_109", CLD_C2_109},
	{"CLD_C2_110", CLD_C2_110},
	{"CLD_C2_111", CLD_C2_111},
	{"CLD_C2_112", CLD_C2_112},
	{"CLD_C2_113", CLD_C2_113},
	{"CLD_C2_114", CLD_C2_114},
	{"CLD_C2_115", CLD_C2_115},
	{"CLD_C2_116", CLD_C2_116},
	{"CLD_C2_117", CLD_C2_117},
	{"CLD_C2_118", CLD_C2_118},
	{"CLD_C2_119", CLD_C2_119},
	{"CLD_C2_120", CLD_C2_120},
	{"CLD_C2_121", CLD_C2_121},
	{"CLD_C2_122", CLD_C2_122},
	{"CLD_C2_123", CLD_C2_123},
	{"CLD_C2_124", CLD_C2_124},
	{"CLD_C2_125", CLD_C2_125},
	{"CLD_C2_126", CLD_C2_126},
	{"CLD_C2_127", CLD_C2_127},
	{"CLD_C2_128", CLD_C2_128},
	{"CLD_C2_129", CLD_C2_129},
	{"CLD_C2_130", CLD_C2_130},
	{"CLD_C2_131", CLD_C2_131},
	{"CLD_C2_132", CLD_C2_132},
	{"CLD_C2_133", CLD_C2_133},
	{"CLD_C2_134", CLD_C2_134},
	{"CLD_C2_135", CLD_C2_135},
	{"CLD_C2_136", CLD_C2_136},
	{"CLD_C2_137", CLD_C2_137},
	{"CLD_C2_138", CLD_C2_138},
	{"CLD_C2_139", CLD_C2_139},
	{"CLD_C2_140", CLD_C2_140},
	{"CLD_C2_141", CLD_C2_141},
	{"CLD_C2_142", CLD_C2_142},
	{"CLD_C2_143", CLD_C2_143},
	{"CLD_C2_144", CLD_C2_144},
	{"CLD_C2_145", CLD_C2_145},
	{"CLD_C2_146", CLD_C2_146},
	{"CLD_C2_147", CLD_C2_147},
	{"CLD_C2_148", CLD_C2_148},
	{"CLD_C2_149", CLD_C2_149},
	{"CLD_C2_150", CLD_C2_150},

	{"CLI_Oem1", CLI_Oem1},
	{"CLI_Oem2", CLI_Oem2},
	{"CLI_Oem3", CLI_Oem3},
	{"CLI_Oem4", CLI_Oem4},
	{"CLI_Oem5", CLI_Oem5},
	{"CLI_Oem6", CLI_Oem6},
	{"CLI_Oem7", CLI_Oem7},
	{"CLI_Oem8", CLI_Oem8},
	{"CLI_Oem9", CLI_Oem9},
	{"CLI_Oem10", CLI_Oem10},
	{"CLI_Oem11", CLI_Oem11},
	{"CLI_Oem12", CLI_Oem12},
	{"CLI_Oem13", CLI_Oem13},
	{"CLI_Oem14", CLI_Oem14},
	{"CLI_Oem15", CLI_Oem15},
	{"CLI_Oem16", CLI_Oem16},
	{"CLI_Oem17", CLI_Oem17},
	{"CLI_Oem18", CLI_Oem18},
	{"CLI_Oem19", CLI_Oem19},
	{"CLI_Oem20", CLI_Oem20},
	{"CLI_Oem21", CLI_Oem21},
	{"CLI_Oem22", CLI_Oem22},
	{"CLI_Oem23", CLI_Oem23},
	{"CLI_Oem24", CLI_Oem24},
	{"CLI_Oem25", CLI_Oem25},
	{"CLI_Oem26", CLI_Oem26},
	{"CLI_Oem27", CLI_Oem27},
	{"CLI_Oem28", CLI_Oem28},
	{"CLI_Oem29", CLI_Oem29},
	{"CLI_Oem30", CLI_Oem30},
	{"CLI_Oem31", CLI_Oem31},
	{"CLI_Oem32", CLI_Oem32},
	{"CLI_Oem33", CLI_Oem33},
	{"CLI_Oem34", CLI_Oem34},
	{"CLI_Oem35", CLI_Oem35},
	{"CLI_Oem36", CLI_Oem36},
	{"CLI_Oem37", CLI_Oem37},
	{"CLI_Oem38", CLI_Oem38},
	{"CLI_Oem39", CLI_Oem39},
	{"CLI_Oem40", CLI_Oem40},
	{"CLI_Oem41", CLI_Oem41},
	{"CLI_Oem42", CLI_Oem42},
	{"CLI_Oem43", CLI_Oem43},
	{"CLI_Oem44", CLI_Oem44},
	{"CLI_Oem45", CLI_Oem45},
	{"CLI_Oem46", CLI_Oem46},
	{"CLI_Oem47", CLI_Oem47},
	{"CLI_Oem48", CLI_Oem48},
	{"CLI_Oem49", CLI_Oem49},
	{"CLI_Oem50", CLI_Oem50},
	{"CLI_Oem51", CLI_Oem51},
	{"CLI_Oem52", CLI_Oem52},
	{"CLI_Oem53", CLI_Oem53},
	{"CLI_Oem54", CLI_Oem54},
	{"CLI_Oem55", CLI_Oem55},
	{"CLI_Oem56", CLI_Oem56},
	{"CLI_Oem57", CLI_Oem57},
	{"CLI_Oem58", CLI_Oem58},
	{"CLI_Oem59", CLI_Oem59},
	{"CLI_Oem60", CLI_Oem60},
	{"CLI_Oem61", CLI_Oem61},
	{"CLI_Oem62", CLI_Oem62},
	{"CLI_Oem63", CLI_Oem63},
	{"CLI_Oem64", CLI_Oem64},
	{"CLI_Oem65", CLI_Oem65},
	{"CLI_Oem66", CLI_Oem66},
	{"CLI_Oem67", CLI_Oem67},
	{"CLI_Oem68", CLI_Oem68},
	{"CLI_Oem69", CLI_Oem69},
	{"CLI_Oem70", CLI_Oem70},
	{"CLI_Oem71", CLI_Oem71},
	{"CLI_Oem72", CLI_Oem72},
	{"CLI_Oem73", CLI_Oem73},
	{"CLI_Oem74", CLI_Oem74},
	{"CLI_Oem75", CLI_Oem75},
	{"CLI_Oem76", CLI_Oem76},
	{"CLI_Oem77", CLI_Oem77},
	{"CLI_Oem78", CLI_Oem78},
	{"CLI_Oem79", CLI_Oem79},
	{"CLI_Oem80", CLI_Oem80},
	{"CLI_Oem81", CLI_Oem81},
	{"CLI_Oem82", CLI_Oem82},
	{"CLI_Oem83", CLI_Oem83},
	{"CLI_Oem84", CLI_Oem84},
	{"CLI_Oem85", CLI_Oem85},
	{"CLI_Oem86", CLI_Oem86},
	{"CLI_Oem87", CLI_Oem87},
	{"CLI_Oem88", CLI_Oem88},
	{"CLI_Oem89", CLI_Oem89},
	{"CLI_Oem90", CLI_Oem90},
	{"CLI_Oem91", CLI_Oem91},
	{"CLI_Oem92", CLI_Oem92},
	{"CLI_Oem93", CLI_Oem93},
	{"CLI_Oem94", CLI_Oem94},
	{"CLI_Oem95", CLI_Oem95},
	{"CLI_Oem96", CLI_Oem96},
	{"CLI_Oem97", CLI_Oem97},
	{"CLI_Oem98", CLI_Oem98},
	{"CLI_Oem99", CLI_Oem99},
	{"CLI_Oem100", CLI_Oem100},

	{"CLDRAM_1", CLDRAM_1},
	{"CLDRAM_2", CLDRAM_2},
	{"CLDRAM_3", CLDRAM_3},
	{"CLDRAM_4", CLDRAM_4},
	{"CLDRAM_5", CLDRAM_5},
	{"CLDRAM_6", CLDRAM_6},
	{"CLDRAM_7", CLDRAM_7},
	{"CLDRAM_8", CLDRAM_8},
	{"CLDRAM_9", CLDRAM_9},
	{"CLDRAM_10", CLDRAM_10},
	{"CLDRAM_11", CLDRAM_11},
	{"CLDRAM_12", CLDRAM_12},

	{"CLD_C3_1", CLD_C3_1},
	{"CLD_C3_2", CLD_C3_2},
	{"CLD_C3_3", CLD_C3_3},
	{"CLD_C3_4", CLD_C3_4},
	{"CLD_C3_5", CLD_C3_5},
	{"CLD_C3_6", CLD_C3_6},
	{"CLD_C3_7", CLD_C3_7},
	{"CLD_C3_8", CLD_C3_8},
	{"CLD_C3_9", CLD_C3_9},
	{"CLD_C3_10", CLD_C3_10},
	{"CLD_C3_11", CLD_C3_11},
	{"CLD_C3_12", CLD_C3_12},
	{"CLD_C3_13", CLD_C3_13},
	{"CLD_C3_14", CLD_C3_14},
	{"CLD_C3_15", CLD_C3_15},
	{"CLD_C3_16", CLD_C3_16},
	{"CLD_C3_17", CLD_C3_17},
	{"CLD_C3_18", CLD_C3_18},
	{"CLD_C3_19", CLD_C3_19},
	{"CLD_C3_20", CLD_C3_20},
	{"CLD_C3_21", CLD_C3_21},
	{"CLD_C3_22", CLD_C3_22},
	{"CLD_C3_23", CLD_C3_23},
	{"CLD_C3_24", CLD_C3_24},
	{"CLD_C3_25", CLD_C3_25},
	{"CLD_C3_26", CLD_C3_26},
	{"CLD_C3_27", CLD_C3_27},
	{"CLD_C3_28", CLD_C3_28},
	{"CLD_C3_29", CLD_C3_29},
	{"CLD_C3_30", CLD_C3_30},
	{"CLD_C3_31", CLD_C3_31},
	{"CLD_C3_32", CLD_C3_32},
	{"CLD_C3_33", CLD_C3_33},
	{"CLD_C3_34", CLD_C3_34},
	{"CLD_C3_35", CLD_C3_35},
	{"CLD_C3_36", CLD_C3_36},
	{"CLD_C3_37", CLD_C3_37},
	{"CLD_C3_38", CLD_C3_38},
	{"CLD_C3_39", CLD_C3_39},
	{"CLD_C3_40", CLD_C3_40},
	{"CLD_C3_41", CLD_C3_41},
	{"CLD_C3_42", CLD_C3_42},
	{"CLD_C3_43", CLD_C3_43},
	{"CLD_C3_44", CLD_C3_44},
	{"CLD_C3_45", CLD_C3_45},
	{"CLD_C3_46", CLD_C3_46},
	{"CLD_C3_47", CLD_C3_47},
	{"CLD_C3_48", CLD_C3_48},
	{"CLD_C3_49", CLD_C3_49},
	{"CLD_C3_50", CLD_C3_50},
	{"CLD_C3_51", CLD_C3_51},
	{"CLD_C3_52", CLD_C3_52},
	{"CLD_C3_53", CLD_C3_53},
	{"CLD_C3_54", CLD_C3_54},
	{"CLD_C3_55", CLD_C3_55},
	{"CLD_C3_56", CLD_C3_56},
	{"CLD_C3_57", CLD_C3_57},
	{"CLD_C3_58", CLD_C3_58},
	{"CLD_C3_59", CLD_C3_59},
	{"CLD_C3_60", CLD_C3_60},
	{"CLD_C3_61", CLD_C3_61},
	{"CLD_C3_62", CLD_C3_62},
	{"CLD_C3_63", CLD_C3_63},
	{"CLD_C3_64", CLD_C3_64},
	{"CLD_C3_65", CLD_C3_65},
	{"CLD_C3_66", CLD_C3_66},
	{"CLD_C3_67", CLD_C3_67},
	{"CLD_C3_68", CLD_C3_68},
	{"CLD_C3_69", CLD_C3_69},
	{"CLD_C3_70", CLD_C3_70},
	{"CLD_C3_71", CLD_C3_71},
	{"CLD_C3_72", CLD_C3_72},
	{"CLD_C3_73", CLD_C3_73},
	{"CLD_C3_74", CLD_C3_74},
	{"CLD_C3_75", CLD_C3_75},
	{"CLD_C3_76", CLD_C3_76},
	{"CLD_C3_77", CLD_C3_77},
	{"CLD_C3_78", CLD_C3_78},
	{"CLD_C3_79", CLD_C3_79},
	{"CLD_C3_80", CLD_C3_80},
	{"CLD_C3_81", CLD_C3_81},
	{"CLD_C3_82", CLD_C3_82},
	{"CLD_C3_83", CLD_C3_83},
	{"CLD_C3_84", CLD_C3_84},
	{"CLD_C3_85", CLD_C3_85},
	{"CLD_C3_86", CLD_C3_86},
	{"CLD_C3_87", CLD_C3_87},
	{"CLD_C3_88", CLD_C3_88},
	{"CLD_C3_89", CLD_C3_89},
	{"CLD_C3_90", CLD_C3_90},
	{"CLD_C3_91", CLD_C3_91},
	{"CLD_C3_92", CLD_C3_92},
	{"CLD_C3_93", CLD_C3_93},
	{"CLD_C3_94", CLD_C3_94},
	{"CLD_C3_95", CLD_C3_95},
	{"CLD_C3_96", CLD_C3_96},
	{"CLD_C3_97", CLD_C3_97},
	{"CLD_C3_98", CLD_C3_98},
	{"CLD_C3_99", CLD_C3_99},
	{"CLD_C3_100", CLD_C3_100},
	{"CLD_C3_101", CLD_C3_101},
	{"CLD_C3_102", CLD_C3_102},
	{"CLD_C3_103", CLD_C3_103},
	{"CLD_C3_104", CLD_C3_104},
	{"CLD_C3_105", CLD_C3_105},
	{"CLD_C3_106", CLD_C3_106},
	{"CLD_C3_107", CLD_C3_107},
	{"CLD_C3_108", CLD_C3_108},
	{"CLD_C3_109", CLD_C3_109},
	{"CLD_C3_110", CLD_C3_110},
	{"CLD_C3_111", CLD_C3_111},
	{"CLD_C3_112", CLD_C3_112},
	{"CLD_C3_113", CLD_C3_113},
	{"CLD_C3_114", CLD_C3_114},
	{"CLD_C3_115", CLD_C3_115},
	{"CLD_C3_116", CLD_C3_116},
	{"CLD_C3_117", CLD_C3_117},
	{"CLD_C3_118", CLD_C3_118},
	{"CLD_C3_119", CLD_C3_119},
	{"CLD_C3_120", CLD_C3_120},
	{"CLD_C3_121", CLD_C3_121},
	{"CLD_C3_122", CLD_C3_122},
	{"CLD_C3_123", CLD_C3_123},
	{"CLD_C3_124", CLD_C3_124},
	{"CLD_C3_125", CLD_C3_125},
	{"CLD_C3_126", CLD_C3_126},
	{"CLD_C3_127", CLD_C3_127},
	{"CLD_C3_128", CLD_C3_128},
	{"CLD_C3_129", CLD_C3_129},
	{"CLD_C3_130", CLD_C3_130},
	{"CLD_C3_131", CLD_C3_131},
	{"CLD_C3_132", CLD_C3_132},
	{"CLD_C3_133", CLD_C3_133},
	{"CLD_C3_134", CLD_C3_134},
	{"CLD_C3_135", CLD_C3_135},
	{"CLD_C3_136", CLD_C3_136},
	{"CLD_C3_137", CLD_C3_137},
	{"CLD_C3_138", CLD_C3_138},
	{"CLD_C3_139", CLD_C3_139},
	{"CLD_C3_140", CLD_C3_140},
	{"CLD_C3_141", CLD_C3_141},
	{"CLD_C3_142", CLD_C3_142},
	{"CLD_C3_143", CLD_C3_143},
	{"CLD_C3_144", CLD_C3_144},
	{"CLD_C3_145", CLD_C3_145},
	{"CLD_C3_146", CLD_C3_146},
	{"CLD_C3_147", CLD_C3_147},
	{"CLD_C3_148", CLD_C3_148},
	{"CLD_C3_149", CLD_C3_149},
	{"CLD_C3_150", CLD_C3_150},

	{"CLLC_C1_1", CLLC_C1_1},
	{"CLLC_C1_2", CLLC_C1_2},
	{"CLLC_C1_3", CLLC_C1_3},
	{"CLLC_C1_4", CLLC_C1_4},
	{"CLLC_C1_5", CLLC_C1_5},
	{"CLLC_C1_6", CLLC_C1_6},
	{"CLLC_C1_7", CLLC_C1_7},
	{"CLLC_C1_8", CLLC_C1_8},
	{"CLLC_C1_9", CLLC_C1_9},
	{"CLLC_C1_10", CLLC_C1_10},
	{"CLLC_C1_11", CLLC_C1_11},
	{"CLLC_C1_12", CLLC_C1_12},
	{"CLLC_C1_13", CLLC_C1_13},
	{"CLLC_C1_14", CLLC_C1_14},
	{"CLLC_C1_15", CLLC_C1_15},
	{"CLLC_C1_16", CLLC_C1_16},
	{"CLLC_C1_17", CLLC_C1_17},
	{"CLLC_C1_18", CLLC_C1_18},
	{"CLLC_C1_19", CLLC_C1_19},
	{"CLLC_C1_20", CLLC_C1_20},
	{"CLLC_C1_21", CLLC_C1_21},
	{"CLLC_C1_22", CLLC_C1_22},
	{"CLLC_C1_23", CLLC_C1_23},
	{"CLLC_C1_24", CLLC_C1_24},
	{"CLLC_C1_25", CLLC_C1_25},
	{"CLLC_C1_26", CLLC_C1_26},
	{"CLLC_C1_27", CLLC_C1_27},
	{"CLLC_C1_28", CLLC_C1_28},
	{"CLLC_C1_29", CLLC_C1_29},
	{"CLLC_C1_30", CLLC_C1_30},
	{"CLLC_C1_31", CLLC_C1_31},
	{"CLLC_C1_32", CLLC_C1_32},
	{"CLLC_C1_33", CLLC_C1_33},
	{"CLLC_C1_34", CLLC_C1_34},
	{"CLLC_C1_35", CLLC_C1_35},
	{"CLLC_C1_36", CLLC_C1_36},
	{"CLLC_C1_37", CLLC_C1_37},
	{"CLLC_C1_38", CLLC_C1_38},
	{"CLLC_C1_39", CLLC_C1_39},
	{"CLLC_C1_40", CLLC_C1_40},
	{"CLLC_C1_41", CLLC_C1_41},
	{"CLLC_C1_42", CLLC_C1_42},
	{"CLLC_C1_43", CLLC_C1_43},
	{"CLLC_C1_44", CLLC_C1_44},
	{"CLLC_C1_45", CLLC_C1_45},
	{"CLLC_C1_46", CLLC_C1_46},
	{"CLLC_C1_47", CLLC_C1_47},
	{"CLLC_C1_48", CLLC_C1_48},
	{"CLLC_C1_49", CLLC_C1_49},
	{"CLLC_C1_50", CLLC_C1_50},
	{"CLLC_C1_51", CLLC_C1_51},
	{"CLLC_C1_52", CLLC_C1_52},
	{"CLLC_C1_53", CLLC_C1_53},
	{"CLLC_C1_54", CLLC_C1_54},
	{"CLLC_C1_55", CLLC_C1_55},
	{"CLLC_C1_56", CLLC_C1_56},
	{"CLLC_C1_57", CLLC_C1_57},
	{"CLLC_C1_58", CLLC_C1_58},
	{"CLLC_C1_59", CLLC_C1_59},
	{"CLLC_C1_60", CLLC_C1_60},
	{"CLLC_C1_61", CLLC_C1_61},
	{"CLLC_C1_62", CLLC_C1_62},
	{"CLLC_C1_63", CLLC_C1_63},
	{"CLLC_C1_64", CLLC_C1_64},
	{"CLLC_C1_65", CLLC_C1_65},
	{"CLLC_C1_66", CLLC_C1_66},
	{"CLLC_C1_67", CLLC_C1_67},
	{"CLLC_C1_68", CLLC_C1_68},
	{"CLLC_C1_69", CLLC_C1_69},
	{"CLLC_C1_70", CLLC_C1_70},
	{"CLLC_C1_71", CLLC_C1_71},
	{"CLLC_C1_72", CLLC_C1_72},
	{"CLLC_C1_73", CLLC_C1_73},
	{"CLLC_C1_74", CLLC_C1_74},
	{"CLLC_C1_75", CLLC_C1_75},
	{"CLLC_C1_76", CLLC_C1_76},
	{"CLLC_C1_77", CLLC_C1_77},
	{"CLLC_C1_78", CLLC_C1_78},
	{"CLLC_C1_79", CLLC_C1_79},
	{"CLLC_C1_80", CLLC_C1_80},
	{"CLLC_C1_81", CLLC_C1_81},
	{"CLLC_C1_82", CLLC_C1_82},
	{"CLLC_C1_83", CLLC_C1_83},
	{"CLLC_C1_84", CLLC_C1_84},
	{"CLLC_C1_85", CLLC_C1_85},
	{"CLLC_C1_86", CLLC_C1_86},
	{"CLLC_C1_87", CLLC_C1_87},
	{"CLLC_C1_88", CLLC_C1_88},
	{"CLLC_C1_89", CLLC_C1_89},
	{"CLLC_C1_90", CLLC_C1_90},
	{"CLLC_C1_91", CLLC_C1_91},
	{"CLLC_C1_92", CLLC_C1_92},
	{"CLLC_C1_93", CLLC_C1_93},
	{"CLLC_C1_94", CLLC_C1_94},
	{"CLLC_C1_95", CLLC_C1_95},
	{"CLLC_C1_96", CLLC_C1_96},
	{"CLLC_C1_97", CLLC_C1_97},
	{"CLLC_C1_98", CLLC_C1_98},
	{"CLLC_C1_99", CLLC_C1_99},
	{"CLLC_C1_100", CLLC_C1_100},
	{"CLLC_C1_101", CLLC_C1_101},
	{"CLLC_C1_102", CLLC_C1_102},
	{"CLLC_C1_103", CLLC_C1_103},
	{"CLLC_C1_104", CLLC_C1_104},
	{"CLLC_C1_105", CLLC_C1_105},
	{"CLLC_C1_106", CLLC_C1_106},
	{"CLLC_C1_107", CLLC_C1_107},
	{"CLLC_C1_108", CLLC_C1_108},
	{"CLLC_C1_109", CLLC_C1_109},
	{"CLLC_C1_110", CLLC_C1_110},
	{"CLLC_C1_111", CLLC_C1_111},
	{"CLLC_C1_112", CLLC_C1_112},
	{"CLLC_C1_113", CLLC_C1_113},
	{"CLLC_C1_114", CLLC_C1_114},
	{"CLLC_C1_115", CLLC_C1_115},
	{"CLLC_C1_116", CLLC_C1_116},
	{"CLLC_C1_117", CLLC_C1_117},
	{"CLLC_C1_118", CLLC_C1_118},
	{"CLLC_C1_119", CLLC_C1_119},
	{"CLLC_C1_120", CLLC_C1_120},
	{"CLLC_C1_121", CLLC_C1_121},
	{"CLLC_C1_122", CLLC_C1_122},
	{"CLLC_C1_123", CLLC_C1_123},
	{"CLLC_C1_124", CLLC_C1_124},
	{"CLLC_C1_125", CLLC_C1_125},
	{"CLLC_C1_126", CLLC_C1_126},
	{"CLLC_C1_127", CLLC_C1_127},
	{"CLLC_C1_128", CLLC_C1_128},
	{"CLLC_C1_129", CLLC_C1_129},
	{"CLLC_C1_130", CLLC_C1_130},
	{"CLLC_C1_131", CLLC_C1_131},
	{"CLLC_C1_132", CLLC_C1_132},
	{"CLLC_C1_133", CLLC_C1_133},
	{"CLLC_C1_134", CLLC_C1_134},
	{"CLLC_C1_135", CLLC_C1_135},
	{"CLLC_C1_136", CLLC_C1_136},
	{"CLLC_C1_137", CLLC_C1_137},
	{"CLLC_C1_138", CLLC_C1_138},
	{"CLLC_C1_139", CLLC_C1_139},
	{"CLLC_C1_140", CLLC_C1_140},
	{"CLLC_C1_141", CLLC_C1_141},
	{"CLLC_C1_142", CLLC_C1_142},
	{"CLLC_C1_143", CLLC_C1_143},
	{"CLLC_C1_144", CLLC_C1_144},
	{"CLLC_C1_145", CLLC_C1_145},
	{"CLLC_C1_146", CLLC_C1_146},
	{"CLLC_C1_147", CLLC_C1_147},
	{"CLLC_C1_148", CLLC_C1_148},
	{"CLLC_C1_149", CLLC_C1_149},
	{"CLLC_C1_150", CLLC_C1_150},

	{"CLI_Last", CLLC_C1_150},
	{NULL, NULL}
};