/* CState05Logo1 - first logo screen, promoted from the raw C ports
 * State05_Logo1_OnEnter.c (0x4433f0) / State05_Logo1_OnExit.c
 * (0x443430). See src/cxx/README.md. */
#include "GameState.h"

extern "C" {
int PlayMusicTrack(int trackId);
/* Promoted to cdecl with an explicit name (was .img name in EAX). The
 * old __stdcall decl decorated to _LoadSpriteSet@8 and never bound to
 * the real cdecl definition - the call hit a bring-up stub, so sprites
 * never loaded. */
int LoadSpriteSet(void *container, int key, const char *imgName);
extern unsigned char DAT_00ea0e18;
extern unsigned int  DAT_00ea0e1c;
/* Takes 2 outputs, not 1 - the original's second output arrives via a
 * dropped ESI register (see src/network/BuildSystemInfoBlob.c). This
 * call site still had the stale 1-param decl/call from before that fix
 * was propagated here; blob[9] below holds both halves back-to-back
 * (blob[0..3] for param_1, blob[4..8] for param_2), matching how the
 * two halves get concatenated into the outgoing packet just below. */
void BuildSystemInfoBlob(void *outBlob, void *outBlob2);        /* fills the 36-byte system-info blob */
unsigned int SendSocketData(int handle, int len); /* channel send */
extern unsigned int DAT_007934f4;        /* outgoing packet buffer base (declared uint in the C
                                          * tree; used as a pointer here, cast locally) */
}

/* 0x4433f0 - same shape as Title's OnEnter: prime container bucket
 * 10000 (with "logomode.img"/"logo.mp3" in the loader's EAX/EDI
 * register args), reset the frame counter, start the music. */
void CState05Logo1::OnEnter()
{
    LoadSpriteSet(&DAT_00ea0e18, 10000, "logomode.img");
    m_frameCounter = 0;
    PlayMusicTrack(0);
}

/* 0x443430 - destroy container bucket 10000 (the same walk as Title's
 * OnExit), then build the 36-byte system-info blob and append it to
 * the outgoing buffer as packet 0xa000 and send - the post-logo
 * client-info handshake. The buffer layout (u16 len at +0, u16 opcode
 * at +2, u32 flag at +4, write cursor at +0x2000, send handle at
 * +0x2004) is kept as raw offsets until the send-buffer class is
 * reconstructed. */
void CState05Logo1::OnExit()
{
    unsigned int **bucket = *(unsigned int ***)(DAT_00ea0e1c + 0x1c);
    unsigned int key = (unsigned int)bucket[1];
    if (key < 0x2711) {
        for (;;) {
            if (10000 < key) {
                goto send_info;
            }
            if (key == 10000) {
                break;
            }
            bucket = (unsigned int **)bucket[7];
            key = (unsigned int)bucket[1];
        }
        unsigned int **node = (unsigned int **)bucket[4];
        while (node != bucket) {
            unsigned int **obj = (unsigned int **)*node;
            node = (unsigned int **)node[4];
            ((void (__cdecl *)(int))*obj)(1); /* scalar-deleting dtor, free=1 (true
                                               * convention __thiscall; see Title) */
        }
        bucket[3] = (unsigned int *)bucket;
        bucket[4] = (unsigned int *)bucket;
    }
send_info:
    unsigned int blob[9];
    BuildSystemInfoBlob(blob, blob + 4);
    unsigned short *buf = (unsigned short *)DAT_007934f4;
    if (buf != 0) {
        buf[1] = 0xa000;
        *(int *)((unsigned char *)buf + 0x2000) = 4;
        *(unsigned int *)(buf + 2) = 1;
        int cursor = *(int *)((unsigned char *)buf + 0x2000);
        *(int *)((unsigned char *)buf + 0x2000) = cursor + 4;
        unsigned int *dst = (unsigned int *)((unsigned char *)buf + cursor + 4);
        dst[0] = blob[0];
        dst[1] = blob[1];
        dst[2] = blob[2];
        dst[3] = blob[3];
        cursor = *(int *)((unsigned char *)buf + 0x2000);
        *(int *)((unsigned char *)buf + 0x2000) = cursor + 0x10;
        dst = (unsigned int *)((unsigned char *)buf + cursor + 0x10);
        dst[0] = blob[4];
        dst[1] = blob[5];
        dst[2] = blob[6];
        dst[3] = blob[7];
        dst[4] = blob[8];
        int len = *(int *)((unsigned char *)buf + 0x2000) + 0x14;
        *(int *)((unsigned char *)buf + 0x2000) = len;
        buf[0] = (unsigned short)len;
        SendSocketData(*(int *)((unsigned char *)buf + 0x2004), len);
    }
}
