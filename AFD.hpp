
#pragma once	

/*
  Copyright (c) 2018 Victor Sheinmann, Vicshann@gmail.com

  Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), 
  to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, 
  and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

  The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, 
  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, 
  WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE. 
*/


#define METHOD_NEITHER   3
#define FSCTL_AFD_BASE   18

//#define FSCTL_AFD_BASE                  FILE_DEVICE_NETWORK
#define _AFD_CONTROL_CODE(Operation,Method) ((FSCTL_AFD_BASE)<<12 | (Operation<<2) | Method)

/* AFD Commands */
#define AFD_BIND            0
#define AFD_CONNECT              1
#define AFD_START_LISTEN         2
#define AFD_WAIT_FOR_LISTEN      3
#define AFD_ACCEPT          4
#define AFD_RECV            5
#define AFD_RECV_DATAGRAM        6
#define AFD_SEND            7
#define AFD_SEND_DATAGRAM        8
#define AFD_SELECT          9
#define AFD_DISCONNECT           10
#define AFD_GET_SOCK_NAME        11
#define AFD_GET_PEER_NAME               12
#define AFD_GET_TDI_HANDLES      13
#define AFD_SET_INFO             14
#define AFD_GET_CONTEXT_SIZE     15
#define AFD_GET_CONTEXT          16
#define AFD_SET_CONTEXT          17
#define AFD_SET_CONNECT_DATA         18
#define AFD_SET_CONNECT_OPTIONS      19
#define AFD_SET_DISCONNECT_DATA      20
#define AFD_SET_DISCONNECT_OPTIONS   21
#define AFD_GET_CONNECT_DATA         22
#define AFD_GET_CONNECT_OPTIONS      23
#define AFD_GET_DISCONNECT_DATA      24
#define AFD_GET_DISCONNECT_OPTIONS   25
#define AFD_SET_CONNECT_DATA_SIZE       26
#define AFD_SET_CONNECT_OPTIONS_SIZE    27
#define AFD_SET_DISCONNECT_DATA_SIZE    28
#define AFD_SET_DISCONNECT_OPTIONS_SIZE 29
#define AFD_GET_INFO             30
#define AFD_EVENT_SELECT         33
#define AFD_ENUM_NETWORK_EVENTS         34
#define AFD_DEFER_ACCEPT         35
#define AFD_GET_PENDING_CONNECT_DATA 41
#define AFD_CONNECT_UNK              49
 
/* AFD IOCTLs */
 
#define IOCTL_AFD_BIND _AFD_CONTROL_CODE(AFD_BIND, METHOD_NEITHER)
#define IOCTL_AFD_CONNECT _AFD_CONTROL_CODE(AFD_CONNECT, METHOD_NEITHER)
#define IOCTL_AFD_START_LISTEN _AFD_CONTROL_CODE(AFD_START_LISTEN, METHOD_NEITHER)
#define IOCTL_AFD_WAIT_FOR_LISTEN _AFD_CONTROL_CODE(AFD_WAIT_FOR_LISTEN, METHOD_BUFFERED )
#define IOCTL_AFD_ACCEPT _AFD_CONTROL_CODE(AFD_ACCEPT, METHOD_BUFFERED )
#define IOCTL_AFD_RECV _AFD_CONTROL_CODE(AFD_RECV, METHOD_NEITHER)
#define IOCTL_AFD_RECV_DATAGRAM _AFD_CONTROL_CODE(AFD_RECV_DATAGRAM, METHOD_NEITHER)
#define IOCTL_AFD_SEND _AFD_CONTROL_CODE(AFD_SEND, METHOD_NEITHER)
#define IOCTL_AFD_SEND_DATAGRAM _AFD_CONTROL_CODE(AFD_SEND_DATAGRAM, METHOD_NEITHER)
#define IOCTL_AFD_SELECT _AFD_CONTROL_CODE(AFD_SELECT, METHOD_BUFFERED )
#define IOCTL_AFD_DISCONNECT _AFD_CONTROL_CODE(AFD_DISCONNECT, METHOD_NEITHER)
#define IOCTL_AFD_GET_SOCK_NAME _AFD_CONTROL_CODE(AFD_GET_SOCK_NAME, METHOD_NEITHER)
#define IOCTL_AFD_GET_PEER_NAME _AFD_CONTROL_CODE(AFD_GET_PEER_NAME, METHOD_NEITHER)
#define IOCTL_AFD_GET_TDI_HANDLES _AFD_CONTROL_CODE(AFD_GET_TDI_HANDLES, METHOD_NEITHER)
#define IOCTL_AFD_SET_INFO _AFD_CONTROL_CODE(AFD_SET_INFO, METHOD_NEITHER)
#define IOCTL_AFD_GET_CONTEXT_SIZE _AFD_CONTROL_CODE(AFD_GET_CONTEXT_SIZE, METHOD_NEITHER)
#define IOCTL_AFD_GET_CONTEXT _AFD_CONTROL_CODE(AFD_GET_CONTEXT, METHOD_NEITHER)
#define IOCTL_AFD_SET_CONTEXT _AFD_CONTROL_CODE(AFD_SET_CONTEXT, METHOD_NEITHER)          // 00012047
#define IOCTL_AFD_SET_CONNECT_DATA _AFD_CONTROL_CODE(AFD_SET_CONNECT_DATA, METHOD_NEITHER)
#define IOCTL_AFD_SET_CONNECT_OPTIONS _AFD_CONTROL_CODE(AFD_SET_CONNECT_OPTIONS, METHOD_NEITHER)
#define IOCTL_AFD_SET_DISCONNECT_DATA _AFD_CONTROL_CODE(AFD_SET_DISCONNECT_DATA, METHOD_NEITHER)
#define IOCTL_AFD_SET_DISCONNECT_OPTIONS _AFD_CONTROL_CODE(AFD_SET_DISCONNECT_OPTIONS, METHOD_NEITHER)
#define IOCTL_AFD_GET_CONNECT_DATA _AFD_CONTROL_CODE(AFD_GET_CONNECT_DATA, METHOD_NEITHER)
#define IOCTL_AFD_GET_CONNECT_OPTIONS _AFD_CONTROL_CODE(AFD_GET_CONNECT_OPTIONS, METHOD_NEITHER)
#define IOCTL_AFD_GET_DISCONNECT_DATA _AFD_CONTROL_CODE(AFD_GET_DISCONNECT_DATA, METHOD_NEITHER)
#define IOCTL_AFD_GET_DISCONNECT_OPTIONS _AFD_CONTROL_CODE(AFD_GET_DISCONNECT_OPTIONS, METHOD_NEITHER)
#define IOCTL_AFD_SET_CONNECT_DATA_SIZE _AFD_CONTROL_CODE(AFD_SET_CONNECT_DATA_SIZE, METHOD_NEITHER)
#define IOCTL_AFD_SET_CONNECT_OPTIONS_SIZE _AFD_CONTROL_CODE(AFD_SET_CONNECT_OPTIONS_SIZE, METHOD_NEITHER)
#define IOCTL_AFD_SET_DISCONNECT_DATA_SIZE _AFD_CONTROL_CODE(AFD_SET_DISCONNECT_DATA_SIZE, METHOD_NEITHER)
#define IOCTL_AFD_SET_DISCONNECT_OPTIONS_SIZE _AFD_CONTROL_CODE(AFD_SET_DISCONNECT_OPTIONS_SIZE, METHOD_NEITHER)
#define IOCTL_AFD_GET_INFO _AFD_CONTROL_CODE(AFD_GET_INFO, METHOD_NEITHER)
#define IOCTL_AFD_EVENT_SELECT _AFD_CONTROL_CODE(AFD_EVENT_SELECT, METHOD_NEITHER)
#define IOCTL_AFD_DEFER_ACCEPT _AFD_CONTROL_CODE(AFD_DEFER_ACCEPT, METHOD_NEITHER)
#define IOCTL_AFD_GET_PENDING_CONNECT_DATA _AFD_CONTROL_CODE(AFD_GET_PENDING_CONNECT_DATA, METHOD_NEITHER)
#define IOCTL_AFD_ENUM_NETWORK_EVENTS _AFD_CONTROL_CODE(AFD_ENUM_NETWORK_EVENTS, METHOD_NEITHER)

#define IOCTL_AFD_CONNECT_UNK _AFD_CONTROL_CODE(AFD_CONNECT_UNK, METHOD_NEITHER)

/*
#define AFD_BIND        0x12003
#define AFD_CONNECT     0x12007
#define AFD_RECV        0x12017
#define AFD_SEND        0x1201f
#define AFD_SET_CONTEXT 0x12047
#define AFD_SELECT      0x12024
#define AFD_SENDTO      0x12023
#define AFD_RECVFROM    0x1201B
#define AFD_GET_INFO    0x1207B
*/

/*struct AFD_WSABUF
{
         DWORD len;
         PCH buf;
};*/
 

/*typedef struct _AFD_WSABUF
{
    UINT  len;
    PCHAR buf;
} AFD_WSABUF, *PAFD_WSABUF;
 
typedef struct _TDI_ADDRESS_IP {
    USHORT sin_port;
    ULONG  in_addr;
    UCHAR  sin_zero[8];
} TDI_ADDRESS_IP, *PTDI_ADDRESS_IP;
 
typedef struct _TA_ADDRESS_IP {
    LONG  TAAddressCount;
    struct  _AddrIp
    {
        USHORT          AddressLength;
        USHORT          AddressType;
        TDI_ADDRESS_IP  Address[1];
    } Address [1];
} TA_IP_ADDRESS, *PTA_IP_ADDRESS;
 
typedef struct _TA_ADDRESS {
    USHORT  AddressLength;
    USHORT  AddressType;
    UCHAR   Address[1];
} TA_ADDRESS, *PTA_ADDRESS;
 
typedef struct _TRANSPORT_ADDRESS {
    LONG  TAAddressCount;
    TA_ADDRESS  Address[1];
} TRANSPORT_ADDRESS, *PTRANSPORT_ADDRESS;
  */
/*typedef struct  _AFD_SEND_INFO
{
    PAFD_WSABUF             BufferArray;
    ULONG               BufferCount;
    ULONG               AfdFlags;
    ULONG               TdiFlags;
} AFD_SEND_INFO , *PAFD_SEND_INFO ;   */

/*struct AFD_INFO
{
         AFD_WSABUF* BufferArray;
         DWORD BufferCount;
         DWORD AfdFlags;
         DWORD TdiFlags;
};

 
typedef struct  _AFD_CONNECT_INFO
{
    BOOLEAN             UseSAN;
    ULONG               Root;
    ULONG               Unknown;
    //#if 1 // bruening: based on win7 observation: i#376 
    //    SOCKADDR                            Address;
    //#else
        TRANSPORT_ADDRESS                   Address;
    //#endif
} AFD_CONNECT_INFO , *PAFD_CONNECT_INFO ;
 
/*typedef struct _AFD_BIND_DATA
{
    ULONG                               ShareType;
    #if 1 // bruening: based on win7 observation: i#376 
        SOCKADDR                            Address;
    #else
        TRANSPORT_ADDRESS                   Address;
    #endif
} AFD_BIND_DATA, *PAFD_BIND_DATA;  */
  
//============================================ Tested on: Win10 =======================================================
#pragma pack(push,1)

struct SAFD_INFO_CONN      // 0x28(Two addr?) - This structure is in InputBuffer of IOCTL_AFD_CONNECT 
{
 ULONG  Unknown0;
 ULONG  Unknown1;
 ULONG  Unknown2;
 ULONG  Unknown3;
 PVOID  UnkPtr;
 USHORT AddrCnt;      // Last addr should be empty?
 UCHAR  AddrLst[0];   // PH,PL,A0,A1,A2,A3
};

struct SAFD_INFO_CONN_UNK 
{
 PVOID  UnkPtr;       // Pointer? // On x64 8 bytes
 USHORT UnknCnt;      // 14
 USHORT AddrCnt;      // 2 // Last addr should be empty?
 UCHAR  AddrLst[0];   // PH,PL,A0,A1,A2,A3
};

struct SAFD_WSABUF
{
 SIZE_T Size;
 PBYTE  Data;
};

struct SAFD_INFO_BUFF   // PTR, 8, 8 on x64
{
/* PVOID Array;
 SIZE_T BufCnt;
 SIZE_T Flags;  */
 SAFD_WSABUF* BufArray;
 DWORD BufCnt;
 DWORD AfdFlags;
 DWORD TdiFlags;
 DWORD Unk;
};

#pragma pack(pop)
//=====================================================================================================================