/*
 * COPYRIGHT:   See COPYING in the top level directory
 * PROJECT:     ReactOS TCP/IP protocol driver
 * FILE:        include/receive.h
 * PURPOSE:     Internet Protocol receive prototypes
 */

#pragma once

#include <ip.h>

/* Number of seconds before destroying the IPDR */
#define MAX_TIMEOUT_COUNT 3

/* IP datagram fragment descriptor. Used to store IP datagram fragments */
typedef struct IP_FRAGMENT {
    LIST_ENTRY ListEntry; /* Entry on list */
    PNDIS_PACKET Packet;  /* NDIS packet containing fragment data */
    BOOLEAN ReturnPacket; /* States whether to call NdisReturnPackets */
    UINT PacketOffset;    /* Offset into NDIS packet where data is */
    UINT Offset;          /* Offset into datagram where this fragment is */
    UINT Size;            /* Size of this fragment */
} IP_FRAGMENT, *PIP_FRAGMENT;

/* IP datagram hole descriptor. Used to reassemble IP datagrams */
typedef struct IPDATAGRAM_HOLE {
    LIST_ENTRY ListEntry; /* Entry on list */
    UINT First;           /* Offset of first octet of the hole */
    UINT Last;            /* Offset of last octet of the hole */
} IPDATAGRAM_HOLE, *PIPDATAGRAM_HOLE;

/* IP datagram reassembly information */
typedef struct IPDATAGRAM_REASSEMBLY {
    LIST_ENTRY ListEntry;        /* Entry on list */
    KSPIN_LOCK Lock;             /* Protecting spin lock */
    UINT DataSize;               /* Size of datagram data area */
    IP_ADDRESS SrcAddr;          /* Source address */
    IP_ADDRESS DstAddr;          /* Destination address */
    UCHAR Protocol;              /* Internet Protocol number */
    USHORT Id;                   /* Identification number */
    PIP_HEADER IPv4Header;       /* Pointer to IP header */
    UINT HeaderSize;             /* Length of IP header */
    LIST_ENTRY FragmentListHead; /* IP fragment list */
    LIST_ENTRY HoleListHead;     /* IP datagram hole list */
    UINT TimeoutCount;           /* Timeout counter */
} IPDATAGRAM_REASSEMBLY, *PIPDATAGRAM_REASSEMBLY;


extern LIST_ENTRY ReassemblyListHead;
extern KSPIN_LOCK ReassemblyListLock;
extern NPAGED_LOOKASIDE_LIST IPDRList;
extern NPAGED_LOOKASIDE_LIST IPFragmentList;
extern NPAGED_LOOKASIDE_LIST IPHoleList;


VOID IPFreeReassemblyList(
    VOID);

VOID IPDatagramReassemblyTimeout(
    VOID);

VOID IPReceive(
    PIP_INTERFACE IF,
    PIP_PACKET IPPacket);

/* EOF */
