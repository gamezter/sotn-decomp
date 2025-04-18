// SPDX-License-Identifier: AGPL-3.0-or-later
#include "../dra/dra.h"
#include "../dra/dra_bss.h"

s16 SsSeqOpen(u32 addr, s16 vab_id);

extern s32 D_8B42064;
extern s32 D_psp_08B42060;
extern s8* D_psp_09190C18[];
extern s16 D_psp_09187240[][2];
extern s8* D_psp_091893B8[];
extern Point32 D_psp_09189D40[];
extern s32 D_psp_09189D68;
extern char D_psp_09189D70[];
extern char D_psp_09189D80[];
extern char D_psp_09189DB0[];
extern char D_psp_09189DB8[];
extern SpuVoiceAttr D_psp_09236838;
extern s32 D_psp_09236880;
extern char D_psp_09236888[];
extern s32 D_psp_09236910;
extern s32 D_psp_09236920;
extern s32 D_psp_09236928;
extern s8 D_psp_09237488;
extern s16 D_psp_092374A0;
extern s16 D_psp_092374B0;
extern s16 D_psp_092374B8;
extern s16 D_psp_092374C0;
extern SpuVoiceAttr* D_psp_09237578;

void func_psp_09140588(s32 arg0) {
    if (!func_psp_09141550(arg0)) {
        D_psp_092374B8 = arg0;
    }
    D_psp_092374B0 = arg0;
}

void MuteCd(void) {
    g_MuteCd = 1;
    D_8013B694 = 0;
}

void UnMuteCd(void) {
    g_MuteCd = 0;
    D_8013B694++;
}

s32 func_80131F28(void) { return D_80138F7C; }

bool func_80131F68(void) {
    bool ret;
    if (D_8013B61C) {
        ret = 1;
    } else {
        ret = (D_psp_092374B8 != 0);
    }
    return ret;
}

s16 GetCdVolume(void) { return g_CdVolume; }

void SetReverbDepth(short depth) { SsUtSetReverbDepth(depth, depth); }

void func_80131FCC(void) {
    switch (D_8013B680) {
    case 0:
        D_80138F7C = 0;
        break;
    case 1:
    case 2:
        D_80138F7C++;
        break;
    }
    D_8013B680 = 0;
}

u8 DoCdCommand(u_char com, u_char* param, u_char* result) {
    g_CdCommandStatus = CdSync(1, g_CdCommandResult);

    if (com == CdlGetlocL) {
        if (g_CdCommandStatus != CdlComplete) {
            CdControl(CdlNop, 0, 0);
            D_8013B680 = 2;
            return D_8013B680;
        }
    } else if (*g_CdCommandResult & CdlStatShellOpen) {
        CdControl(CdlNop, 0, 0);
        D_8013B680 = 2;
        return D_8013B680;
    } else if (*g_CdCommandResult & CdlStatSeekError) {
        CdControl(CdlNop, 0, 0);
        D_8013B680 = 2;
        return D_8013B680;
    }

    if (g_CdCommandStatus == CdlComplete) {
        if (CdControl(com, param, result)) {
            D_8013B680 = 0;
            return D_8013B680;
        }
    }

    D_8013B680 = 1;
    return D_8013B680;
}

void SetMaxVolume(void) {
    g_volumeL = 127;
    g_volumeR = 127;
    SsSetMVol(g_volumeL, g_volumeR);
}

void InitSoundVars3(void) {
    s32 i;

    for (i = 0; i < 4; i++) {
        g_SfxScriptVolume[i] = 0;
        g_SfxScriptDistance[i] = 0;
        g_CurrentSfxScriptSfxId[i] = 0;
        g_SfxScriptTimer[i] = 0;
        g_SfxScriptMode[i] = 0;
        g_CurrentSfxScript[i] = 0;
        g_CurrentSfxScriptSfxId2[i] = 0;
        g_SfxScriptUnk6[i] = 0;
    }
}

void InitSoundVars2(void) {
    s32 i;

    InitSoundVars3();
    D_8013B690 = 0;

    for (i = 0; i < NUM_CH_2; i++) {
        g_CurrentSfxId12_19[i] = 0;
        D_8013AED4[i] = 0;
    }
    g_CurSfxId22_23 = 0;
    g_CurSfxId20_21 = 0;
}

void InitSoundVars1(void) {
    D_80138FB4 = &D_psp_09236838;
    D_801390C8 = &D_psp_09236838;
    D_801390CC = &D_psp_09236838;
    D_psp_09237578 = &D_psp_09236838;

    InitSoundVars2();
    g_CdSoundCommand16 = 0;
    for (D_80138454 = 0; D_80138454 < LEN(g_SeqPointers); D_80138454++) {
        g_SeqPointers[D_80138454] = 0;
    }
    for (D_80138454 = 0; D_80138454 < MAX_SND_COUNT; D_80138454++) {
        g_CdSoundCommandQueue[D_80138454] = 0;
    }

    g_CdSoundCommandQueuePos = 0;
    D_8013AEE8 = 0;
    for (D_80138454 = 0; D_80138454 < MAX_SND_COUNT; D_80138454++) {
        g_SoundCommandRingBuffer[D_80138454] = 0;
    }

    g_SoundCommandRingBufferReadPos = 0;
    g_SoundCommandRingBufferWritePos = 0;
    for (D_80138454 = 0; D_80138454 < MAX_SND_COUNT; D_80138454++) {
        g_SfxRingBuffer[D_80138454].sndId = 0;
        g_SfxRingBuffer[D_80138454].sndVol = 0;
        g_SfxRingBuffer[D_80138454].sndPan = 0;
    }

    g_SfxRingBufferReadPos = 0;
    g_sfxRingBufferWritePos = 0;
    g_SeqIsPlaying = 0;
    g_CurSfxVol22_23 = 0;
    g_CurSfxDistance22_23 = 0;
    g_CurSfxVol20_21 = 0;
    g_CurSfxDistance20_21 = 0;
    D_80139A74 = 0;
    D_8013B69C = 0;
    g_SeqAccessNum = 0;
    D_80138FBC = 0;
    D_psp_092374B8 = 0;
    D_psp_092374B0 = 0;
    D_psp_092374C0 = 0;
    D_psp_092374A0 = 0;
    D_80139014 = 0;
    D_psp_09237488 = 0;
    D_8013980C = 0;
    g_CdSoundCommandStep = 0;
    D_801390A0 = 0;
    g_XaVolumeMultiplier = 0x20;
    g_SfxVolumeMultiplier = 0x7F;
    g_SeqVolume1 = 0x70;
    g_SeqVolume2 = 0x70;
    D_8013B680 = 0;
    D_80138F7C = 0;
    D_801390D8 = 0;
    g_KeyOffChannels = 0;
    g_MuteCd = 0;
    D_8013B694 = 0;
    D_8013B61C = 0;
}

void SetCdVolume(s8 s_num, s16 arg1, s16 arg2) {
    SsSetSerialVol((arg1 << 0xF) / 127, arg1, arg2);
}

void SetMonoStereo(u8 soundMode) {
    CdlATV audioVolume;

    switch (soundMode) {
    case MONO_SOUND:
        if (D_801390A8 != MONO_SOUND) {
            SsSetMono();
            audioVolume.val2 = 128; // CD (R) --> SPU (R)
            audioVolume.val0 = 128; // CD (L) --> SPU (L)
            audioVolume.val3 = 128; // CD Right sound transferred to left
            audioVolume.val1 = 128; // CD Left sound transferred to right
            CdMix(&audioVolume);
            g_SfxVolumeMultiplier = 108;
            D_801390A8 = MONO_SOUND;
        }
        break;

    case STEREO_SOUND:
        if (D_801390A8 != STEREO_SOUND) {
            SsSetStereo();
            audioVolume.val2 = 224; // CD (R) --> SPU (R)
            audioVolume.val0 = 224; // CD (L) --> SPU (L)
            audioVolume.val3 = 0;
            audioVolume.val1 = 0;
            CdMix(&audioVolume);
            g_SfxVolumeMultiplier = 127;
            D_801390A8 = STEREO_SOUND;
        }
        break;
    }
}

void SoundInit(void) {
    g_SoundInitialized = 1;
    SetMonoStereo(STEREO_SOUND);
    SetMaxVolume();
    g_CdVolume = 0x78;
    SetCdVolume(0, g_CdVolume, g_CdVolume);
    g_CdMode[0] = CdlModeSpeed | CdlModeRT | CdlModeSF;
    DoCdCommand(CdlSetmode, g_CdMode, 0);
    InitSoundVars1();
    SetReverbDepth(10);
}

u8 func_801326D8(void) {
    if (D_psp_092374B8) {
        return 1;
    }
    if (g_SeqPlayingId) {
        return 3;
    }
    if (D_801390D8) {
        return 2;
    }
    return 0;
}

void SoundWait(void) {
    while (func_801326D8() != 0) {
        VSync(0);
        func_801361F8();
    }
}

void MuteSound(void) {
    SsSetMVol(0, 0);
    SsSetSerialAttr(SS_SERIAL_A, SS_MIX, SS_SOFF);
    SetCdVolume(SS_SERIAL_A, 0, 0);
    SetMaxVolume();
    InitSoundVars1();
}

void KeyOnRange(s32 minVoice, s32 maxVoice, s16 vabId, s16 prog, s16 tone,
                s16 note, s16 voll, s16 volr) {
    s32 i;

    s32 didStuff = 0;
    for (i = minVoice; i < maxVoice; i += 2) {
        if (!g_KeyStatus[i]) {
            SsUtKeyOnV(i, vabId, prog, tone, note, 0, voll, volr);
            SsUtKeyOnV(i + 1, vabId, prog, tone + 1, note, 0, voll, volr);
            didStuff++;
            if (i == (maxVoice - 2)) {
                D_8013AEDC = minVoice;
            } else {
                D_8013AEDC = i + 2;
            }
            break;
        }
    }
    if (!didStuff) {
        SsUtKeyOnV(D_8013AEDC, vabId, prog, tone, note, 0, voll, volr);
        SsUtKeyOnV(D_8013AEDC + 1, vabId, prog, tone + 1, note, 0, voll, volr);
    }
}

void func_80132A04(s16 voice, s16 vabId, s16 prog, s16 tone, s16 note,
                   s16 volume, s16 distance) {
    if (!distance) {
        g_VolL = volume;
        g_VolR = volume;
    } else {
        g_VolR = (volume * D_psp_09187240[distance][0]) >> 7;
        g_VolL = (volume * D_psp_09187240[distance][1]) >> 7;
    }

    // hardware voices 0-24
    if (voice >= 0 && voice < 24) {
        SsUtKeyOnV(voice, vabId, prog, tone, note, 0, g_VolL, g_VolR);
        SsUtKeyOnV(voice + 1, vabId, prog, tone + 1, note, 0, g_VolL, g_VolR);
        return;
    }

    // virtual voices 30-33 map to hardware channels 0-4,4-8,8-12,14-18
    switch (voice) {
    case 30:
        KeyOnRange(0, 4, vabId, prog, tone, note, g_VolL, g_VolR);
        break;

    case 31:
        KeyOnRange(4, 8, vabId, prog, tone, note, g_VolL, g_VolR);
        break;

    case 32:
        KeyOnRange(8, 12, vabId, prog, tone, note, g_VolL, g_VolR);
        break;

    case 33:
        KeyOnRange(14, 18, vabId, prog, tone, note, g_VolL, g_VolR);
        break;
    }
}

static void AddCdSoundCommand(s16 arg0) {
    s32 i;
    s32 isFound;

    if (arg0 == CD_SOUND_COMMAND_6) {
        isFound = 0;
        for (i = 0; i < g_CdSoundCommandQueuePos; i++) {
            if (g_CdSoundCommandQueue[i] == CD_SOUND_COMMAND_12) {
                isFound = 1;
            }
        }
        if (isFound) {
            g_DebugEnabled++;
            g_CdSoundCommandQueue[g_CdSoundCommandQueuePos] =
                CD_SOUND_COMMAND_14;
            g_CdSoundCommandQueuePos++;
            if (g_CdSoundCommandQueuePos == MAX_SND_COUNT) {
                D_8013AEE8++;
                for (i = 1; i < MAX_SND_COUNT; i++) {
                    g_CdSoundCommandQueue[i] = 0;
                }
                g_CdSoundCommandQueuePos = 1;
                g_CdSoundCommandQueue[g_CdSoundCommandQueuePos] =
                    CD_SOUND_COMMAND_14;
                g_CdSoundCommandQueuePos++;
            }
        }
    }
    g_CdSoundCommandQueue[g_CdSoundCommandQueuePos] = arg0;
    g_CdSoundCommandQueuePos++;
    if (g_CdSoundCommandQueuePos == MAX_SND_COUNT) {
        D_8013AEE8++;
        for (i = 1; i < MAX_SND_COUNT; i++) {
            g_CdSoundCommandQueue[i] = 0;
        }
        g_CdSoundCommandQueuePos = 1;
    }
}

void func_psp_09141440(s32 arg0) {
    if ((func_892A7E0(arg0) & 0x80) == 0) {
        func_892A97C(arg0, 0x80);
        AddCdSoundCommand(2);
    }
}

static void AdvanceCdSoundCommandQueue(void) {
    s32 i;

    for (i = 0; i < MAX_SND_COUNT - 1; i++) {
        g_CdSoundCommandQueue[i] = g_CdSoundCommandQueue[i + 1];
    }
    g_CdSoundCommandQueuePos--;
}

s32 func_psp_09141550(s32 arg0) {
    if (arg0 == 2) {
        return 1;
    }
    return arg0 == 4;
}

INCLUDE_ASM("dra_psp/psp/dra_psp/63C08", func_psp_09141570);

s32 func_psp_091415E0(s32 arg0) {
    s32 sp1C;
    s32 sp18;

    func_psp_09141570(arg0, &sp1C, &sp18);
    return sp18;
}

s32 func_psp_09141608(s32 arg0) {
    u32 i;

    if (D_8B42064) {
        for (i = 0; i < 5; i++) {
            if (arg0 == (D_psp_09189D40[i].x - 0x300)) {
                return D_psp_09189D40[i].y - 0x300;
            }
        }
    }
    return arg0;
}

s32 func_psp_09141668(s32 arg0) {
    s32 sp1C;
    s32 sp18;
    s32 var_s2;
    s32 var_s0, var_s1;
    s8* temp_a3;

    var_s0 = 0;
    var_s1 = 0;
    var_s2 = func_psp_09141608(arg0);
    func_psp_09141570(var_s2, &sp1C, &sp18);
    temp_a3 = D_psp_091893B8[var_s2];
    if ((temp_a3[0] == 'P') && (temp_a3[1] == 'S') && (temp_a3[2] == '_')) {
        psp_sprintf(D_psp_09236888, D_psp_09189D70, D_psp_08B42060,
                    D_psp_091893B8[var_s2]);
        if (func_890FA7C(D_psp_09236888) < 0) {
            var_s2 = D_psp_09189D68;
        }
        D_psp_09189D68 = var_s2;
        psp_sprintf(D_psp_09236888, D_psp_09189D80, D_psp_08B42060,
                    D_psp_091893B8[var_s2]);
        if (func_psp_09141550(var_s2) != 0) {
            var_s0 = func_8933F5C();
            var_s1 = func_8933F6C();
        }
        func_892A620(~sp18 & 1, 1);
        func_892A414(sp18, D_psp_09236888, 1, sp1C, var_s0, var_s1);
    } else {
        psp_sprintf(D_psp_09236888, D_psp_09189DB0, D_psp_08B42060,
                    D_psp_091893B8[var_s2]);
        if (func_890FA7C(D_psp_09236888) < 0) {
            var_s2 = D_psp_09236880;
        }
        D_psp_09236880 = var_s2;
        psp_sprintf(D_psp_09236888, D_psp_09189DB8, D_psp_08B42060,
                    D_psp_091893B8[var_s2]);
        func_892A414(sp18, D_psp_09236888, 0, sp1C, 0, 0);
    }
    return sp1C;
}

s8* func_psp_09141860(s32 arg0) { return D_psp_091893B8[arg0]; }

void func_psp_09141878(s32 arg0) {
    func_892A620(0, 0);
    SetCdVolume(0, 0x7F, 0x7F);
    if (arg0 >= 0 && arg0 <= 0x230) {
        func_psp_09141668(arg0);
    }
}

void CdSoundCommand4(void) {
    switch (g_CdSoundCommandStep) {
    case 0:
        D_801390A0 = 1;
        g_CurrentXaConfigId = g_CurrentXaSoundId;
        if (g_CurrentXaSoundId < 0x3D) {
            g_CdSoundCommand16 = 0;
        }
        D_80139014 = g_XaMusicConfigs[g_CurrentXaConfigId].unk230;
        if (D_80139014 == 2) {
            D_8013AE90 = g_XaMusicConfigs[g_CurrentXaConfigId].unk228 + 20;
        } else {
            D_8013AE90 = g_XaMusicConfigs[g_CurrentXaConfigId].unk228;
        }
        g_CdVolume = g_XaMusicVolume =
            g_XaMusicConfigs[g_CurrentXaConfigId].volume;
        g_CdSoundCommandStep++;
        break;

    case 1:
        D_psp_09236910 = func_psp_09141668(g_CurrentXaConfigId);
        g_CdSoundCommandStep++;
        break;

    case 2:
        if (func_892A7E0(D_psp_09236910) & 2) {
            g_CdSoundCommandStep++;
        }
        if (func_892A7E0(D_psp_09236910) & 8) {
            g_CdSoundCommandStep = 0xFF;
        }
        break;

    case 3:
        D_8013AEF4 = VSync(-1);
        func_psp_09140588(g_CurrentXaConfigId);
        D_801390A0 = g_CdSoundCommandStep = 0;
        AdvanceCdSoundCommandQueue();
        break;

    default:
        D_801390A0 = g_CdSoundCommandStep = 0;
        AdvanceCdSoundCommandQueue();
        break;
    }
}

void CdSoundCommand6(void) {
    switch (g_CdSoundCommandStep) {
    case 0:
        D_801390A0 = 1;
        D_8013845C = g_CurrentXaSoundId;
        g_CdSoundCommandStep++;
        break;

    case 1:
        D_psp_09236920 = func_psp_09141668(D_8013845C);
        g_CdSoundCommandStep++;
        break;

    case 2:
        if (func_892A7E0(D_psp_09236920) & 2) {
            g_CdSoundCommandStep++;
        }
        if (func_892A7E0(D_psp_09236920) & 8) {
            g_CdSoundCommandStep = 0xFF;
        }
        break;

    case 3:
        D_8013AEF4 = VSync(-1);
        D_8013AE90 = g_XaMusicConfigs[D_8013845C + 1].unk228;
        SetReverbDepth(g_ReverbDepth);
        func_psp_09140588(D_8013845C);
        D_801390A0 = g_CdSoundCommandStep = 0;
        AdvanceCdSoundCommandQueue();
        break;

    default:
        D_801390A0 = g_CdSoundCommandStep = 0;
        AdvanceCdSoundCommandQueue();
        break;
    }
}

void CdFadeOut1(void) {
    switch (g_CdSoundCommandStep) {
    case 0:
        if (D_psp_092374B0 == 0) {
            SetMaxVolume();
            AdvanceCdSoundCommandQueue();
            break;
        }
        D_801390A0 = 1;
        g_CdVolume -= 0x20;
        if (g_CdVolume < 0) {
            g_CdVolume = 0;
        }
        SetCdVolume(0, g_CdVolume, g_CdVolume);
        if (g_CdVolume == 0) {
            g_CdSoundCommandStep++;
        }
        break;

    case 1:
        func_892A620(func_psp_091415E0(D_psp_092374B0), 0);
        func_psp_09140588(0);
        SetMaxVolume();
        D_801390A0 = g_CdSoundCommandStep = 0;
        AdvanceCdSoundCommandQueue();
        break;

    default:
        D_801390A0 = g_CdSoundCommandStep = 0;
        AdvanceCdSoundCommandQueue();
        break;
    }
}

void CdFadeOut2(void) {
    switch (g_CdSoundCommandStep) {
    case 0:
        if (D_psp_092374B8 == 0) {
            AdvanceCdSoundCommandQueue();
            break;
        }
        D_801390A0 = 1;
        g_CdVolume -= 0x20;
        if (g_CdVolume < 0) {
            g_CdVolume = 0;
        }
        SetCdVolume(0, g_CdVolume, g_CdVolume);
        if (g_CdVolume == 0) {
            g_CdSoundCommandStep++;
        }
        break;

    case 1:
        func_892A620(func_psp_091415E0(D_psp_092374B8), 0);
        func_psp_09140588(0);
        D_801390A0 = g_CdSoundCommandStep = 0;
        AdvanceCdSoundCommandQueue();
        break;

    default:
        D_801390A0 = g_CdSoundCommandStep = 0;
        AdvanceCdSoundCommandQueue();
        break;
    }
}

void func_psp_09141E30(void) {
    switch (g_CdSoundCommandStep) {
    case 0:
        if (D_psp_092374B8 == 0) {
            AdvanceCdSoundCommandQueue();
            break;
        }
        D_801390A0 = 1;
        g_CdVolume -= 0x20;
        if (g_CdVolume < 0) {
            g_CdVolume = 0;
        }
        SetCdVolume(0, g_CdVolume, g_CdVolume);
        if (g_CdVolume == 0) {
            g_CdSoundCommandStep++;
        }
        break;

    case 1:
        func_892A620(0, 0);
        func_892A620(1, 0);
        func_psp_09140588(0);
        D_801390A0 = g_CdSoundCommandStep = 0;
        AdvanceCdSoundCommandQueue();
        break;

    default:
        D_801390A0 = g_CdSoundCommandStep = 0;
        AdvanceCdSoundCommandQueue();
        break;
    }
}

void EnableCdReverb(s8 arg0) {
    SsSetSerialAttr(SS_SERIAL_A, SS_REV, arg0 == SS_SON);
}

void StopSeq(void) {
    if (g_SeqPlayingId != 0) {
        SsSeqStop(g_SeqAccessNum);
        SsSeqClose(g_SeqAccessNum);
        SetReleaseRate2();
        g_SeqPlayingId = 0;
        g_SeqIsPlaying = 0;
    }
}

void PlaySeq(s16 arg0) {
    s16 index;

    if (g_SeqPlayingId) {
        StopSeq();
    }
    index = (u8)(arg0 & 0xFF);
    g_SeqAccessNum =
        SsSeqOpen(g_SeqPointers[index], g_SeqInfo[index].unk2 >> 4);
    g_ReverbDepth = g_SeqInfo[index].reverb_depth;
    SetReverbDepth(g_ReverbDepth);
    g_SeqVolume1 = g_SeqInfo[index].volume;
    g_SeqVolume2 = g_SeqInfo[index].volume;
    SsSeqSetVol(g_SeqAccessNum, g_SeqVolume1, g_SeqVolume1);
    if ((g_SeqInfo[index].unk2 & 0xF) == 0) {
        SsSeqPlay(g_SeqAccessNum, 1, 1);
    } else {
        SsSeqPlay(g_SeqAccessNum, 1, 0);
    }
    g_SeqPlayingId = index;
    g_SeqIsPlaying = 0xE;
}

bool CdSoundCommandQueueEmpty(void) { return g_CdSoundCommandQueuePos == 0; }

bool func_80133950(void) { return !D_8013980C; }

void CdSoundCommand12(void) {
    s32 temp_a2;
    s32 i;
    s32 var_t0;

    switch (g_CdSoundCommandStep) {
    case 0:
        if (g_CdSoundCommand16 >= 2) {
            g_CdSoundCommand16 = 0;
        }
        if (D_psp_092374B0 == 0) {
            D_8013980C = 0;
            AdvanceCdSoundCommandQueue();
        } else {
            D_801390A0 = 1;
            g_CdSoundCommandStep++;
        }
        break;

    case 1:
        if (g_CdVolume > 0) {
            g_CdVolume -= 0xC;
        }
        if (g_CdVolume <= 0) {
            g_CdVolume = 0;
        }
        SetCdVolume(0, g_CdVolume, g_CdVolume);
        if (g_CdVolume == 0) {
            g_CdSoundCommandStep++;
        }
        break;

    case 2:
        if (DoCdCommand(CdlGetlocL, NULL, D_8013B688) == 0) {
            g_CdSoundCommandStep++;
        }
        break;

    case 3:
        temp_a2 = VSync(-1);
        for (i = 0; i < 8; i++) {
            D_8013B5F4[g_CdSoundCommand16].unk0[i] = D_8013B688[i];
        }
        var_t0 = D_8013AE90 - (temp_a2 - D_8013AEF4);
        if (var_t0 <= 0) {
            var_t0 = 1;
        }
        D_8013B5F4[g_CdSoundCommand16].unk8 = var_t0;
        D_8013B5F4[g_CdSoundCommand16].unkc = D_psp_092374B0;
        D_8013B5F4[g_CdSoundCommand16].unke = D_80139014;
        SsSetSerialAttr(0, 0, 0);
        if (DoCdCommand(CdlPause, NULL, NULL) == 0) {
            g_CdSoundCommandStep++;
        }
        break;

    case 4:
        func_892A70C(0);
        func_892A70C(1);
        g_CdSoundCommand16++;
        func_psp_09140588(0);
        D_801390A0 = 0;
        D_8013980C = 0;
        g_CdSoundCommandStep = 0;
        AdvanceCdSoundCommandQueue();
        break;

    default:
        D_8013980C = 0;
        D_801390A0 = g_CdSoundCommandStep = 0;
        AdvanceCdSoundCommandQueue();
        break;
    }
}

void CdSoundCommand14(void) {
    s32 i;

    switch (g_CdSoundCommandStep) {
    case 0:
        if (g_CdSoundCommand16 == 0 || g_CdSoundCommand16 > 2) {
            D_8013980C = 0;
            AdvanceCdSoundCommandQueue();
            break;
        }
        if (D_psp_092374B0 != 0) {
            D_8013980C = 0;
            AdvanceCdSoundCommandQueue();
            break;
        }
        D_801390A0 = 1;
        for (i = 0; i < 8; i++) {
            D_8013B688[i] = D_8013B5F4[g_CdSoundCommand16 - 1].unk0[i];
        }
        func_psp_09140588(D_8013B5F4[g_CdSoundCommand16 - 1].unkc);
        g_XaMusicVolume = g_XaMusicConfigs[D_psp_092374B0].volume;
        g_CdVolume = 0;
        SetCdVolume(0, 0, 0);
        g_CdMode[0] = 0xC8;
        g_CdSoundCommandStep++;
        break;

    case 1:
        if (DoCdCommand(CdlSetmode, g_CdMode, NULL) == 0) {
            g_CdMode[0] = g_XaMusicConfigs[D_psp_092374B0].filter_file;
            g_CdMode[1] = g_XaMusicConfigs[D_psp_092374B0].filter_channel_id & 0xF;
            g_CdSoundCommandStep++;
        }
        break;

    case 2:
        if (DoCdCommand(CdlSetfilter, g_CdMode, NULL) == 0) {
            g_CdSoundCommandStep++;
        }
        break;

    case 3:
        if (DoCdCommand(CdlSetloc, D_8013B688, NULL) == 0) {
            g_CdSoundCommandStep++;
        }
        break;

    case 4:
        func_892A76C(0);
        func_892A76C(1);
        D_psp_09236928 = 0;
        g_CdSoundCommandStep++;
        break;

    case 5:
        if (func_892A7E0(D_psp_09236928) & 2) {
            g_CdSoundCommandStep++;
        }
        if (func_892A7E0(D_psp_09236928) & 8) {
            g_CdSoundCommandStep = 0xFF;
        }
        break;

    case 6:
        D_8013AEF4 = VSync(-1);
        SsSetSerialAttr(0, 0, 1);
        D_8013AE90 = D_8013B5F4[g_CdSoundCommand16 - 1].unk8;
        D_80139014 = D_8013B5F4[g_CdSoundCommand16 - 1].unke;
        g_CdSoundCommandStep++;
        break;

    case 7:
        if (g_CdVolume < g_XaMusicVolume) {
            g_CdVolume += 0xC;
        }
        if (g_CdVolume >= g_XaMusicVolume) {
            g_CdVolume = g_XaMusicVolume;
            g_CdSoundCommandStep++;
        }
        SetCdVolume(0, g_CdVolume, g_CdVolume);
        break;

    case 8:
        g_CdSoundCommand16--;
        D_801390A0 = 0;
        D_8013980C = 0;
        g_CdSoundCommandStep = 0;
        AdvanceCdSoundCommandQueue();
        break;

    default:
        D_8013980C = 0;
        D_801390A0 = g_CdSoundCommandStep = 0;
        AdvanceCdSoundCommandQueue();
        break;
    }
}

void func_80133FCC(void) {
    s32 temp_v0;
    s32 i;

    func_892A8FC();
    if (D_psp_092374B8 == 0) {
        return;
    }
    if (D_801390A0 != 0) {
        return;
    }
    for (i = 0; i < 2; i++) {
        temp_v0 = func_892A7E0(i);
        if (temp_v0 & 8) {
            func_psp_09141440(i);
            if ((temp_v0 & 0x80) == 0) {
                func_892A97C(i, 0x80);
                AddCdSoundCommand(2);
            }
        }
    }
}

void SetReleaseRate1(void) {
    D_80138FB4->voice = 0;
    D_80138FB4->mask = SPU_VOICE_ADSR_RR;
    D_80138FB4->rr = 14;
    SpuSetVoiceAttr(D_80138FB4);
    g_KeyOffChannels = 0;
    InitSoundVars2();
}

void SetReleaseRate2(void) {
    D_80138FB4->voice = 0;
    D_80138FB4->mask = SPU_VOICE_ADSR_RR;
    D_80138FB4->rr = 8;
    SpuSetVoiceAttr(D_80138FB4);
    g_KeyOffChannels = 0;
    InitSoundVars2();
}

void CdSoundCommand10(void) {
    switch (g_CdSoundCommandStep) {
    case 0:
        D_801390A0 = 1;
        g_XaFadeCounter = 0;
        g_CdSoundCommandStep++;
        break;

    case 1:
        g_XaFadeCounter++;
        if (g_volumeL > 0) {
            g_volumeL =
                g_volumeR -
                (g_volumeR * g_XaVolumeMultiplier * g_XaFadeCounter) / 0x200;
            if (g_volumeL < 0) {
                g_volumeL = 0;
            }
        } else {
            g_volumeL = 0;
        }
        SsSetMVol(g_volumeL, g_volumeL);
        if (g_volumeL == 0) {
            g_CdSoundCommandStep++;
        }
        break;

    case 2:
        SetReverbDepth(0);
        StopSeq();
        AddCdSoundCommand(3);
        D_800BD1C4 = 3;
        g_CdSoundCommandStep++;
        break;

    case 3:
        D_800BD1C4--;
        if (D_800BD1C4 == 0) {
            SetReleaseRate2();
            D_8013B61C = 0;
            D_801390A0 = g_CdSoundCommandStep = 0;
            AdvanceCdSoundCommandQueue();
        }
        break;

    default:
        D_8013B61C = 0;
        D_801390A0 = g_CdSoundCommandStep = 0;
        AdvanceCdSoundCommandQueue();
        break;
    }
}

void CdSoundCommand8(void) {
    switch (g_CdSoundCommandStep) {
    case 0:
        D_801390A0 = 1;
        g_XaFadeCounter = 0;
        g_CdSoundCommandStep++;
        break;

    case 1:
        g_XaFadeCounter++;
        if (g_CdVolume > 0) {
            g_CdVolume =
                g_XaMusicVolume -
                (g_XaMusicVolume * g_XaVolumeMultiplier * g_XaFadeCounter) /
                    0x200;
            if (g_CdVolume < 0) {
                g_CdVolume = 0;
            }
        } else {
            g_CdVolume = 0;
        }
        SetCdVolume(0, g_CdVolume, g_CdVolume);
        if (g_CdVolume == 0) {
            g_CdSoundCommandStep++;
        }
        break;

    case 2:
        AddCdSoundCommand(2);
        D_8013B61C = 0;
        D_801390A0 = g_CdSoundCommandStep = 0;
        AdvanceCdSoundCommandQueue();
        break;

    default:
        D_8013B61C = 0;
        D_801390A0 = g_CdSoundCommandStep = 0;
        AdvanceCdSoundCommandQueue();
        break;
    }
}

#define MASK_22_23 ((1 << 22) | (1 << 23))
#define MASK_20_21 ((1 << 20) | (1 << 21))

void SetReleaseRateHigh20_21(void) {
    D_801390C8->voice = MASK_20_21;
    D_801390C8->mask = SPU_VOICE_ADSR_RR;
    D_801390C8->rr = 14;
    SpuSetVoiceAttr(D_801390C8);
    g_KeyOffChannels |= MASK_20_21;
}

void SetReleaseRateHigh22_23(void) {
    D_801390CC->voice = MASK_22_23;
    D_801390CC->mask = SPU_VOICE_ADSR_RR;
    D_801390CC->rr = 14;
    SpuSetVoiceAttr(D_801390CC);
    g_KeyOffChannels |= MASK_22_23;
}

void SetReleaseRateLow_20_21(void) {
    D_801390C8->voice = MASK_20_21;
    D_801390C8->mask = SPU_VOICE_ADSR_RR;
    D_801390C8->rr = 8;
    SpuSetVoiceAttr(D_801390C8);
    g_KeyOffChannels |= MASK_20_21;
}

void SetReleaseRateLow_22_23(void) {
    D_801390CC->voice = MASK_22_23;
    D_801390CC->mask = SPU_VOICE_ADSR_RR;
    D_801390CC->rr = 8;
    SpuSetVoiceAttr(D_801390CC);
    g_KeyOffChannels |= MASK_22_23;
}

s32 SetVolumeCommand22_23(s16 vol, s16 distance) {
    s32 ret = -2;
    if (g_CurSfxId22_23) {
        if (distance < -8 || distance > 8) {
            distance = 0;
            ret = -1;
        } else {
            ret = 0;
        }
        g_CurSfxVol22_23 = vol;
        g_CurSfxDistance22_23 = distance;
        g_SoundCommandRingBuffer[g_SoundCommandRingBufferWritePos] =
            SET_VOLUME_22_23;
        g_SoundCommandRingBufferWritePos++;
        if (g_SoundCommandRingBufferWritePos == MAX_SND_COUNT) {
            g_SoundCommandRingBufferWritePos = 0;
        }
    }
    return ret;
}

s32 PlaySfxVolPan(s16 sfxId, u16 sfxVol, s16 sfxPan) {
    s32 ret = 0;

    if (!g_SoundInitialized) {
        return -2;
    }
    if (sfxId > SFX_START && sfxId <= SFX_LAST) {
        g_SfxRingBuffer[g_sfxRingBufferWritePos].sndId = sfxId - SFX_START;
        g_SfxRingBuffer[g_sfxRingBufferWritePos].sndVol = sfxVol & 0x7F;
        if (sfxPan < -8 || sfxPan > 8) {
            g_SfxRingBuffer[g_sfxRingBufferWritePos].sndPan = 0;
            ret = -1;
        } else {
            g_SfxRingBuffer[g_sfxRingBufferWritePos].sndPan = sfxPan;
            ret = 0;
        }
        g_sfxRingBufferWritePos++;
        if (g_sfxRingBufferWritePos == MAX_SND_COUNT) {
            g_sfxRingBufferWritePos = 0;
        }
    } else {
        ret = -3;
    }
    return ret;
}

void PlaySfx(s16 sfxId) {
    if (!g_SoundInitialized) {
        return;
    }
    if (sfxId > SFX_START && sfxId <= SFX_LAST) {
        g_SfxRingBuffer[g_sfxRingBufferWritePos].sndId = sfxId - SFX_START;
        g_SfxRingBuffer[g_sfxRingBufferWritePos].sndVol = 0xFFFF;
        g_SfxRingBuffer[g_sfxRingBufferWritePos].sndPan = 0;
        g_sfxRingBufferWritePos++;
        if (g_sfxRingBufferWritePos == MAX_SND_COUNT) {
            g_sfxRingBufferWritePos = 0;
        }
    } else {
        switch (sfxId) {
        case 0x10:
        case 0x11:
            D_8013980C = 1;
            break;

        case 0x80:
        case 0x81:
        case 0x82:
        case 0x83:
        case 0x84:
        case 0x90:
        case 0x91:
        case 0x92:
        case 0x93:
        case 0x94:
            D_8013B61C = 1;
            break;
        }
        g_SoundCommandRingBuffer[g_SoundCommandRingBufferWritePos] = sfxId;
        g_SoundCommandRingBufferWritePos++;
        if (g_SoundCommandRingBufferWritePos == MAX_SND_COUNT) {
            g_SoundCommandRingBufferWritePos = 0;
        }
    }
}

void RestoreSfxScriptData(s16 arg0, s16 arg1) {
    g_CurrentSfxScriptSfxId[arg1] = g_CurrentSfxScriptSfxIdCopy[arg0];
    g_SfxScriptVolume[arg1] = g_SfxScriptVolumeCopy[arg0];
    g_SfxScriptDistance[arg1] = g_SfxScriptDistanceCopy[arg0];
    g_SfxScriptTimer[arg1] = g_SfxScriptTimerCopy[arg0];
    g_SfxScriptMode[arg1] = g_SfxScriptModeCopy[arg0];
    g_CurrentSfxScript[arg1] = D_801390B4[arg0];
}

void PauseSfxScripts(void) {
    s16 i;

    for (i = 0; i < NUM_CH; i++) {
        if (!g_CurrentSfxScriptSfxId[i]) {
            continue;
        }
        if (g_SfxScriptMode[i] == SFX_MODE_SCRIPT_NO_PAUSE) {
            continue;
        }
        g_CurrentSfxScriptSfxIdCopy[i] = g_CurrentSfxScriptSfxId[i];
        g_SfxScriptVolumeCopy[i] = g_SfxScriptVolume[i];
        g_SfxScriptDistanceCopy[i] = g_SfxScriptDistance[i];
        g_SfxScriptTimerCopy[i] = g_SfxScriptTimer[i];
        g_SfxScriptModeCopy[i] = g_SfxScriptMode[i];
        D_801390B4[i] = g_CurrentSfxScript[i];
        g_CurrentSfxScriptSfxId[i] = 0;
        g_SfxScriptVolume[i] = 0;
        g_SfxScriptDistance[i] = 0;
        g_SfxScriptTimer[i] = 0;
        g_SfxScriptMode[i] = 0;
        g_CurrentSfxScript[i] = 0;
        g_CurrentSfxScriptSfxId2[i] = 0;
        g_SfxScriptUnk6[i] = 0;
    }
    D_8013B690 = 1;
}

void UnpauseSfxScripts(void) {
    s16 i, j;

    for (i = 0; i < 3; i++) {
        if (!g_CurrentSfxScriptSfxIdCopy[i]) {
            continue;
        }
        for (j = 0; j < 3; j++) {
            if (!g_CurrentSfxScriptSfxId2[j]) {
                RestoreSfxScriptData(i, j);
                break;
            }
        }
        g_CurrentSfxScriptSfxIdCopy[i] = 0;
    }
    if (g_CurrentSfxScriptSfxIdCopy[3] && !g_CurrentSfxScriptSfxId2[3]) {
        RestoreSfxScriptData(3, 3);
        g_CurrentSfxScriptSfxIdCopy[3] = 0;
    }
    D_8013B690 = 0;
}

void KeyOnChannels20_21(void) {
    u16 volume;

    volume = (g_SfxVolumeMultiplier * g_SfxData[g_CurSfxId20_21].volume) >> 7;
    volume = (volume * g_CurSfxVol20_21) >> 7;
    func_80132A04(
        20, g_SfxData[g_CurSfxId20_21].vabid, g_SfxData[g_CurSfxId20_21].prog,
        g_SfxData[g_CurSfxId20_21].tone, g_SfxData[g_CurSfxId20_21].note,
        volume, g_CurSfxDistance20_21);
}

void KeyOnChannels22_23(void) {
    u16 volume;

    volume = (g_SfxVolumeMultiplier * g_SfxData[g_CurSfxId22_23].volume) >> 7;
    volume = (volume * g_CurSfxVol22_23) >> 7;
    func_80132A04(
        22, g_SfxData[g_CurSfxId22_23].vabid, g_SfxData[g_CurSfxId22_23].prog,
        g_SfxData[g_CurSfxId22_23].tone, g_SfxData[g_CurSfxId22_23].note,
        volume, g_CurSfxDistance22_23);
    g_VolR = (volume * D_psp_09187240[g_CurSfxDistance22_23][0]) >> 8;
    g_VolL = (volume * D_psp_09187240[g_CurSfxDistance22_23][1]) >> 8;
    SsUtSetVVol(22, g_VolL, g_VolR);
    SsUtSetVVol(23, g_VolL, g_VolR);
}

void SetVolume22_23(void) {
    u16 volume;

    volume = (g_SfxVolumeMultiplier * g_SfxData[g_CurSfxId22_23].volume) >> 7;
    volume = (volume * g_CurSfxVol22_23) >> 7;
    g_VolR = (volume * D_psp_09187240[g_CurSfxDistance22_23][0]) >> 8;
    g_VolL = (volume * D_psp_09187240[g_CurSfxDistance22_23][1]) >> 8;
    SsUtSetVVol(22, g_VolL, g_VolR);
    SsUtSetVVol(23, g_VolL, g_VolR);
}

void ExecSoundCommands(void) {
    s16 id;

    while (
        g_SoundCommandRingBufferReadPos != g_SoundCommandRingBufferWritePos) {
        id = g_SoundCommandRingBuffer[g_SoundCommandRingBufferReadPos];
        g_SoundCommandRingBuffer[g_SoundCommandRingBufferReadPos] = 0;
        g_SoundCommandRingBufferReadPos++;
        if (g_SoundCommandRingBufferReadPos == 0x100) {
            g_SoundCommandRingBufferReadPos = 0;
        }
        if (id > 0x200 && id < 0x206) {
            PlaySeq(id);
            continue;
        }

#ifdef VERSION_HD
        if (id > 0x300 && id < 0x531) {
#elif defined(VERSION_PSP)
        if (id > 0x300 && id < 0x532) {
#else
        if (id > 0x300 && id < 0x533) {
#endif
            if (D_psp_092374B8 != 0) {
                if (D_psp_092374B8 == (id - 0x300)) {
                    return;
                }
                AddCdSoundCommand(CD_SOUND_COMMAND_FADE_OUT_2);
            }
            g_CurrentXaSoundId = id - 0x300;
            AddCdSoundCommand(CD_SOUND_COMMAND_START_XA);
            continue;
        }
        switch (id) {
        case SET_SOUND_WAIT:
            SoundWait();
            break;

        case SET_SOUNDMODE_MONO:
            SetMonoStereo(MONO_SOUND);
            break;

        case SET_SOUNDMODE_STEREO:
            SetMonoStereo(STEREO_SOUND);
            break;

        case SET_STOP_SEQ:
            StopSeq();
            break;

        case 0x8:
            SetReleaseRate2();
            break;

        case SET_STOP_MUSIC:
            AddCdSoundCommand(CD_SOUND_COMMAND_FADE_OUT_2);
            break;

        case SET_PAUSE_SFX_SCRIPTS:
            PauseSfxScripts();
            break;

        case SET_UNPAUSE_SFX_SCRIPTS:
            UnpauseSfxScripts();
            break;

        case 0x80:
            g_XaVolumeMultiplier = 0x20;
            AddCdSoundCommand(CD_SOUND_COMMAND_10);
            break;

        case 0x81:
            g_XaVolumeMultiplier = 8;
            AddCdSoundCommand(CD_SOUND_COMMAND_10);
            break;

        case 0x82:
            g_XaVolumeMultiplier = 4;
            AddCdSoundCommand(CD_SOUND_COMMAND_10);
            break;

        case 0x83:
            g_XaVolumeMultiplier = 2;
            AddCdSoundCommand(CD_SOUND_COMMAND_10);
            break;

        case 0x84:
            g_XaVolumeMultiplier = 1;
            AddCdSoundCommand(CD_SOUND_COMMAND_10);
            break;

        case 0x90:
            g_XaVolumeMultiplier = 0x80;
            AddCdSoundCommand(CD_SOUND_COMMAND_8);
            break;

        case 0x91:
            g_XaVolumeMultiplier = 8;
            AddCdSoundCommand(CD_SOUND_COMMAND_8);
            break;

        case 0x92:
            g_XaVolumeMultiplier = 4;
            AddCdSoundCommand(CD_SOUND_COMMAND_8);
            break;

        case 0x93:
            g_XaVolumeMultiplier = 2;
            AddCdSoundCommand(CD_SOUND_COMMAND_8);
            break;

        case 0x94:
            g_XaVolumeMultiplier = 1;
            AddCdSoundCommand(CD_SOUND_COMMAND_8);
            break;

        case 0xA0:
            SetReleaseRate1();
            break;

        case SET_RELEASE_RATE_HIGH_20_21:
            SetReleaseRateHigh20_21();
            g_CurSfxId20_21 = 0;
            break;

        case 0xA5:
            SetReleaseRateHigh22_23();
            g_CurSfxId22_23 = 0;
            break;

        case 0xA2:
            SetReleaseRateLow_20_21();
            g_CurSfxId20_21 = 0;
            break;

        case SET_RELEASE_RATE_LOW_20_21:
            if (g_CurSfxId20_21 != 0) {
                SetReleaseRateLow_20_21();
            }
            break;

        case SET_KEY_ON_20_21:
            if (g_CurSfxId20_21 != 0) {
                KeyOnChannels20_21();
            }
            break;

        case 0xA6:
            SetReleaseRateLow_22_23();
            g_CurSfxId22_23 = 0;
            break;

        case SET_RELEASE_RATE_LOW_22_23:
            if (g_CurSfxId22_23 != 0) {
                SetReleaseRateLow_22_23();
            }
            break;

        case SET_KEY_ON_22_23:
            if (g_CurSfxId22_23 != 0) {
                KeyOnChannels22_23();
            }
            break;

        case SET_VOLUME_22_23:
            SetVolume22_23();
            break;

        case SET_UNK_10:
            AddCdSoundCommand(CD_SOUND_COMMAND_12);
            break;

        case SET_UNK_11:
            AddCdSoundCommand(CD_SOUND_COMMAND_14);
            break;

        case SET_UNK_12:
            AddCdSoundCommand(CD_SOUND_COMMAND_16);
            break;

        case SET_UNK_0B:
            AddCdSoundCommand(CD_SOUND_COMMAND_FADE_OUT_2);
#ifdef VERSION_PSP
            func_892A620(0, 0);
            func_892A620(1, 0);
#endif
            StopSeq();
            SetReleaseRate2();
            break;

        case SET_UNK_0C:
            AddCdSoundCommand(CD_SOUND_COMMAND_FADE_OUT_2);
#ifdef VERSION_PSP
            func_892A620(0, 0);
            func_892A620(1, 0);
#endif
            StopSeq();
            SoundWait();
            SetReleaseRate2();
            break;

        case 0x5A:
            EnableCdReverb(1);
            break;

        case 0x5B:
            EnableCdReverb(0);
            break;

        case 0x5C:
            SetReverbDepth(8);
            break;

        case 0x5D:
            SetReverbDepth(0x10);
            break;

        case 0x5E:
            SetReverbDepth(0x18);
            break;

        case 0x5F:
            SetReverbDepth(0x20);
            break;

        case 0x60:
            SetReverbDepth(0x28);
            break;

        case 0x61:
            SetReverbDepth(0x30);
            break;

        case 0x62:
            SetReverbDepth(0x38);
            break;

        case 0x63:
            SetReverbDepth(0x40);
            break;

        case 0x64:
            SetReverbDepth(0x48);
            break;

        case 0x65:
            SetReverbDepth(0x50);
            break;

        case 0x66:
            SetReverbDepth(0x58);
            break;

        case 0x67:
            SetReverbDepth(0x60);
            break;

        case 0x68:
            SetReverbDepth(0x68);
            break;

        case 0x69:
            SetReverbDepth(0x70);
            break;

        case 0x6A:
            SetReverbDepth(0x78);
            break;

        case 0x6B:
            SetReverbDepth(0x7F);
            break;
        }
    }
}

void ExecCdSoundCommands(void) {
    if (g_CdSoundCommandQueuePos == 0) {
        return;
    }
    switch (g_CdSoundCommandQueue[0]) {
    case 0:
        AdvanceCdSoundCommandQueue();
        break;

    case CD_SOUND_COMMAND_FADE_OUT_2:
        CdFadeOut2();
        break;

    case 31:
        func_psp_09141E30();
        break;

    case CD_SOUND_COMMAND_FADE_OUT_1:
        CdFadeOut1();
        break;

    case CD_SOUND_COMMAND_START_XA:
        CdSoundCommand4();
        break;

    case CD_SOUND_COMMAND_6:
        CdSoundCommand6();
        break;

    case CD_SOUND_COMMAND_8:
        CdSoundCommand8();
        break;

    case CD_SOUND_COMMAND_10:
        CdSoundCommand10();
        break;

    case CD_SOUND_COMMAND_12:
        CdSoundCommand12();
        break;

    case CD_SOUND_COMMAND_14:
        CdSoundCommand14();
        break;

    case CD_SOUND_COMMAND_16:
        g_CdSoundCommand16 = 0;
        AdvanceCdSoundCommandQueue();
        break;
    }
}

void PlaySfxScript(
    s16 arg0, s32 channel_group, bool do_key_off, u16 volume, s16 distance) {
    u16 calcVolume;
    s16 progId;

    if (volume == 0xFFFF) {
        g_SfxScriptVolume[channel_group] =
            (g_SfxVolumeMultiplier * g_SfxData[arg0].volume) >> 7;
        g_SfxScriptDistance[channel_group] = 0;
    } else {
        calcVolume = (g_SfxVolumeMultiplier * g_SfxData[arg0].volume) >> 7;
        g_SfxScriptVolume[channel_group] = (calcVolume * volume) >> 7;
        g_SfxScriptDistance[channel_group] = distance;
    }
    g_CurrentSfxScriptSfxId[channel_group] = arg0;
    g_SfxScriptMode[channel_group] = g_SfxData[arg0].mode;
    progId = g_SfxData[arg0].prog + 1;
    g_CurrentSfxScript[channel_group] = D_psp_09190C18[progId];
    g_SfxScriptTimer[channel_group] = 0;
    g_CurrentSfxScriptSfxId2[channel_group] = arg0;
    g_SfxScriptUnk6[channel_group] = g_SfxData[arg0].unk6;
}

// channel group is 0-3 so play on one of these pairs:
// (12,13),(14,15),(16,17),(18,19)
void KeyOn12_19(
    s16 arg0, s32 channel_group, bool do_key_off, u16 volume, s16 distance) {
    func_80132A04(
        (channel_group * 2) + 12, g_SfxData[arg0].vabid, g_SfxData[arg0].prog,
        g_SfxData[arg0].tone, g_SfxData[arg0].note, volume, distance);
    g_CurrentSfxId12_19[channel_group] = arg0;
    D_8013AED4[channel_group] = g_SfxData[arg0].unk6;
}

void func_8013572C(s16 arg0, u16 volume, s16 distance) {
    s32 i;

    if (!arg0) {
        return;
    }
    if (g_SfxData[arg0].vabid == 9) {
        if (!g_SeqIsPlaying) {
            for (i = 0; i < 3; i++) {
                if (arg0 == g_CurrentSfxScriptSfxId2[i]) {
                    PlaySfxScript(arg0, i, true, volume, distance);
                    return;
                }
            }
            for (i = 0; i < 3; i++) {
                if (g_CurrentSfxScriptSfxId2[i] == 0) {
                    PlaySfxScript(arg0, i, false, volume, distance);
                    return;
                }
            }
            for (i = 0; i < 3; i++) {
                if (g_SfxData[arg0].unk6 > g_SfxScriptUnk6[i]) {
                    PlaySfxScript(arg0, i, true, volume, distance);
                    return;
                }
            }
            for (i = 0; i < 3; i++) {
                if (g_SfxData[arg0].unk6 == g_SfxScriptUnk6[i]) {
                    PlaySfxScript(arg0, i, true, volume, distance);
                    return;
                }
            }
            return;
        }
        if (g_SfxData[arg0].unk6 >= g_SfxScriptUnk6[3]) {
            PlaySfxScript(arg0, 3, true, volume, distance);
        }
    } else {
        switch (g_SfxData[arg0].mode) {
        case SFX_MODE_CHANNELS_22_23:
            g_CurSfxId22_23 = arg0;
            if (volume == 0xFFFF) {
                g_CurSfxVol22_23 = 0x7F;
            } else {
                g_CurSfxVol22_23 = volume;
            }
            g_CurSfxDistance22_23 = distance;
            KeyOnChannels22_23();
            break;

        case SFX_MODE_CHANNELS_20_21:
            g_CurSfxId20_21 = arg0;
            if (volume == 0xFFFF) {
                g_CurSfxVol20_21 = 0x7F;
            } else {
                g_CurSfxVol20_21 = volume;
            }
            g_CurSfxDistance20_21 = distance;
            KeyOnChannels20_21();
            break;

        case SFX_MODE_RELEASE_22_23:
            SetReleaseRateLow_22_23();
            g_CurSfxId22_23 = 0;
            break;

        case SFX_MODE_CHANNELS_12_19:
            g_CurSfxVol12_19 =
                (g_SfxVolumeMultiplier * g_SfxData[arg0].volume) >> 7;
            if (volume == 0xFFFF) {
                g_CurSfxDistance12_19 = 0;
            } else {
                g_CurSfxVol12_19 = (g_CurSfxVol12_19 * volume) >> 7;
                g_CurSfxDistance12_19 = distance;
            }
            if (!g_SeqIsPlaying) {
                for (i = 0; i < 4; i++) {
                    if (arg0 == g_CurrentSfxId12_19[i]) {
                        KeyOn12_19(arg0, i, true, g_CurSfxVol12_19,
                                   g_CurSfxDistance12_19);
                        return;
                    }
                }
                for (i = 0; i < 4; i++) {
                    if (g_CurrentSfxId12_19[i] == 0) {
                        KeyOn12_19(arg0, i, false, g_CurSfxVol12_19,
                                   g_CurSfxDistance12_19);
                        return;
                    }
                }
                for (i = 0; i < 4; i++) {
                    if (g_SfxData[arg0].unk6 > D_8013AED4[i]) {
                        KeyOn12_19(arg0, i, true, g_CurSfxVol12_19,
                                   g_CurSfxDistance12_19);
                        return;
                    }
                }
                for (i = 0; i < 3; i++) {
                    if (g_SfxData[arg0].unk6 == D_8013AED4[i]) {
                        KeyOn12_19(arg0, i, true, g_CurSfxVol12_19,
                                   g_CurSfxDistance12_19);
                        return;
                    }
                }
                return;
            }
            if (g_CurrentSfxId12_19[3] == 0) {
                KeyOn12_19(
                    arg0, 3, false, g_CurSfxVol12_19, g_CurSfxDistance12_19);
            } else if (g_SfxData[arg0].unk6 >= D_8013AED4[3]) {
                KeyOn12_19(
                    arg0, 3, true, g_CurSfxVol12_19, g_CurSfxDistance12_19);
            }
            break;
        }
    }
}

s16 IncrementRingBufferPos(s16 sfxBufPos) {
    if (++sfxBufPos == MAX_SND_COUNT) {
        sfxBufPos = 0;
    }

    return sfxBufPos;
}

void ExecSfx(void) {
    s16 sndId;
    s16 sfxBufPos;
    bool isFound;

    if (g_sfxRingBufferWritePos == g_SfxRingBufferReadPos) {
        return;
    }
    while (g_SfxRingBufferReadPos != g_sfxRingBufferWritePos) {
        sndId = g_SfxRingBuffer[g_SfxRingBufferReadPos].sndId;
        g_SfxRingBuffer[g_SfxRingBufferReadPos].sndId = 0;
        sfxBufPos = IncrementRingBufferPos(g_SfxRingBufferReadPos);
        isFound = false;
        while (sfxBufPos != g_sfxRingBufferWritePos) {
            if (sndId == g_SfxRingBuffer[sfxBufPos].sndId) {
                isFound = true;
                break;
            }
            sfxBufPos = IncrementRingBufferPos(sfxBufPos);
        }
        if (!isFound) {
            func_8013572C(sndId, g_SfxRingBuffer[g_SfxRingBufferReadPos].sndVol,
                          g_SfxRingBuffer[g_SfxRingBufferReadPos].sndPan);
        }
        g_SfxRingBufferReadPos = IncrementRingBufferPos(g_SfxRingBufferReadPos);
    }
}

void func_80135D8C(void) {
    s32 i;

    s16 vab;
    s16 prog;
    s16 tone;
    s16 note;
    s16 volume;
    s16 distance;

    if (g_SeqIsPlaying == 0) {
        for (i = 0; i < 3; i++) {
            if (!g_CurrentSfxScriptSfxId[i]) {
                continue;
            }
            if (g_SfxScriptTimer[i] == 0) {
                vab = *g_CurrentSfxScript[i]++;
                if (vab == -1) {
                    g_CurrentSfxScriptSfxId[i] = 0;
                } else {
                    prog = *g_CurrentSfxScript[i]++;
                    note = *g_CurrentSfxScript[i]++;
                    tone = *g_CurrentSfxScript[i]++;
                    volume = *g_CurrentSfxScript[i]++;
                    volume = (g_SfxScriptVolume[i] * volume) >> 7;
                    g_SfxScriptTimer[i] = *g_CurrentSfxScript[i]++;
                    distance = g_SfxScriptDistance[i];
                    func_80132A04(
                        i + 30, vab, prog, tone, note, volume, distance);
                }
            } else {
                g_SfxScriptTimer[i]--;
            }
        }
    } else {
        if (g_CurrentSfxScriptSfxId[3] != 0) {
            if (g_SfxScriptTimer[3] == 0) {
                vab = *g_CurrentSfxScript[3]++;
                if (vab == -1) {
                    g_CurrentSfxScriptSfxId[3] = 0;
                } else {
                    prog = *g_CurrentSfxScript[3]++;
                    note = *g_CurrentSfxScript[3]++;
                    tone = *g_CurrentSfxScript[3]++;
                    volume = *g_CurrentSfxScript[3]++;
                    volume = (g_SfxScriptVolume[3] * volume) >> 7;
                    g_SfxScriptTimer[3] = *g_CurrentSfxScript[3]++;
                    distance = g_SfxScriptDistance[3];
                    func_80132A04(33, vab, prog, tone, note, volume, distance);
                }
            } else {
                g_SfxScriptTimer[3]--;
            }
        }
    }
}

void func_80136010(void) {
    s32 i;
    s8 sum;

    SpuGetAllKeysStatus(g_KeyStatus);
    if (g_SeqIsPlaying == 0) {
        for (i = 0; i < 4; i++) {
            sum = g_KeyStatus[i * 2 + 12] + g_KeyStatus[i * 2 + 13];
            if (sum == 0) {
                g_CurrentSfxId12_19[i] = 0;
                D_8013AED4[i] = 0;
            }
        }
    } else {
        sum = g_KeyStatus[18] + g_KeyStatus[19];
        if (sum == 0) {
            g_CurrentSfxId12_19[3] = 0;
            D_8013AED4[3] = 0;
        }
    }
    if (g_SeqIsPlaying == 0) {
        for (i = 0; i < 3; i++) {
            if (g_CurrentSfxScriptSfxId[i] == 0) {
                sum = g_KeyStatus[i * 4 + 0] + g_KeyStatus[i * 4 + 1] +
                      g_KeyStatus[i * 4 + 2] + g_KeyStatus[i * 4 + 3];
                if (sum == 0) {
                    g_CurrentSfxScriptSfxId2[i] = 0;
                    g_SfxScriptUnk6[i] = 0;
                }
            }
        }
        return;
    }
    if (g_CurrentSfxScriptSfxId[3] == 0) {
        sum = g_KeyStatus[14] + g_KeyStatus[15] + g_KeyStatus[16] +
              g_KeyStatus[17];
        if (sum == 0) {
            g_CurrentSfxScriptSfxId2[3] = 0;
            g_SfxScriptUnk6[3] = 0;
        }
    }
}

void func_801361F8(void) {
    if (g_SoundInitialized != 0) {
        func_80136010();
        ExecSfx();
        func_80135D8C();
        ExecSoundCommands();
        func_80133FCC();
        ExecCdSoundCommands();
        SpuSetKey(SPU_OFF, g_KeyOffChannels);
        g_KeyOffChannels = 0;
        func_80131FCC();

        if (g_MuteCd) {
            SetCdVolume(0, 0, 0);
        } else {
            SetCdVolume(0, g_CdVolume, g_CdVolume);
        }
    }
}

INCLUDE_ASM("dra_psp/psp/dra_psp/63C08", func_psp_09144C80);
