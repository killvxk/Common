//---------------------------------------------------------------------------
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

#ifndef UtilsH
#define UtilsH

//#define _WIN32
//#undef  _NO_COM

#define WIN32_LEAN_AND_MEAN		 // Exclude rarely-used stuff from Windows headers
//#define _WIN32_WINNT  0x0501     // For CoInitializeEx support

#include <Windows.h>
#include <tlhelp32.h>   // Required for tool help declarations

//#include "BLOWFISH.h"
//#include "MiniString.h"
//#include "json.h"
//#include "crc32.h"
//#include "sha256.h"

//---------------------------------------------------------------------------
#define PATHDLMR 0x2F
#define PATHDLML 0x5C

#define LOGTHID       // ???????????
#define LOGTICK

#define OUTMSG(msg,...) LogProc(NULL,msg,__VA_ARGS__)
#define OUTHEX(buf,len) OUTMSG(NULL,len,buf)  
#ifdef NOLOG
#define LOGMSG(msg,...)
#define LOGTXT(txt,len)
#define LOGHEX(buf,len)
#define DBGMSG LOGMSG
#else
#define LOGMSG(msg,...) LogProc(_PRNM_,msg,__VA_ARGS__)
#define LOGTXT(txt,len) LogProc((char*)1,txt,len);
#define LOGHEX(buf,len) LOGMSG(NULL,len,buf)          // TODO: Optionally attach HEX buffer to a message that it and dump go in one sync logging  

#ifdef _DEBUG
#define DBGMSG LOGMSG
#else
#define DBGMSG(msg,...)
#endif

#endif
#define FOREGROUND_YELLOW (FOREGROUND_RED|FOREGROUND_GREEN)

#ifdef __BORLANDC__
#define _PRNM_ __FUNC__
#else
#define _PRNM_ __FUNCTION__
#endif


enum ELogModes {lmNone=0,lmFile=0x01,lmCons=0x02,lmSErr=0x04,lmProc=0x08,lmFileUpd=0x10};
void   _cdecl LogProc(char* ProcName, char* Message, ...);
extern void (_cdecl *pLogProc)(LPSTR, UINT);
extern int  LogMode;
extern BYTE LogFilePath[MAX_PATH];


#if !defined NTSTATUS
typedef LONG NTSTATUS;
#endif

#if defined _M_X64
#define MEMORY_BASIC_INFO MEMORY_BASIC_INFORMATION64
#else
#define MEMORY_BASIC_INFO MEMORY_BASIC_INFORMATION32
#endif

#define CALL_VDESTR(Class) __asm { __asm lea  ECX, Class  \
                                   __asm mov  EAX, [ECX]  \
                                   __asm call [EAX]       }
     

#define _L(quote) _L2(quote)
#define _L2(quote) L##quote
//====================================================================================
bool _stdcall DeleteFolder(LPSTR FolderPath);
bool _stdcall DeleteFolderW(PWSTR FolderPath);
bool _stdcall IsAddrInModule(PVOID Addr, PVOID ModBase, UINT ModSize);
BOOL _stdcall IsKeyCombinationPressed(DWORD Combination);
bool  _stdcall IsLogHandle(HANDLE Hnd);
void  _stdcall DumpHexData(PBYTE Data, UINT Size, UINT RowLen=32);
void  _stdcall DumpHexDataFmt(PBYTE Data, UINT Size, UINT RowLen=32);
int   _stdcall RefreshINIValueInt(LPSTR SectionName, LPSTR ValueName, int Default, LPSTR FileName);
int   _stdcall RefreshINIValueStr(LPSTR SectionName, LPSTR ValueName, LPSTR Default, LPSTR RetString, DWORD Size, LPSTR FileName);
int   _stdcall RefreshINIValueStr(LPSTR SectionName, LPSTR ValueName, LPSTR Default, PWSTR RetString, DWORD Size, LPSTR FileName);
void  _stdcall SetINIValueInt(LPSTR SectionName, LPSTR ValueName, int Value, LPSTR FileName);
//int   _stdcall ByteArrayToHexStrSwap(PBYTE Buffer, LPSTR DstStr, UINT HexByteCnt);
int   _stdcall ByteArrayToHexStr(PBYTE Buffer, LPSTR DstStr, UINT HexByteCnt, bool UpCase=true);
int _stdcall HexStrToByteArray(PBYTE Buffer, LPSTR SrcStr, UINT HexByteCnt=0);
//UINT  _stdcall TrimFilePath(LPSTR FullPath);
void _stdcall CreateDirectoryPath(LPSTR Path);
SIZE_T _stdcall GetRealModuleSize(PVOID ModuleBase);
__int64   _stdcall GetTime64(bool Local=false);
bool  _stdcall IsValidAsciiString(PBYTE Ptr, UINT MinLen, UINT MaxLen);
bool  _stdcall IsStringContains(LPSTR String, LPSTR Target, UINT StrLen=0, UINT TgtLen=0);
long  _fastcall CharToHex(BYTE CharValue); 
WORD  _fastcall HexToChar(BYTE Value, bool UpCase=true);
//char* _fastcall DecNumToStrU(UINT64 Val, char* buf, int* Len);
BYTE  _stdcall CharToLowCase(BYTE CharValue);
UINT64 _fastcall DecStrToNum(char* Str);  //UINT _fastcall DecStrToNum(char* Str);
UINT64 _fastcall HexStrToNum(char* Str);
DWORD _stdcall DecStrToDW(LPSTR String, UINT* Len=NULL);
DWORD _stdcall HexStrToDW(LPSTR String, UINT Bytes);
DWORD _stdcall WriteLocalProtectedMemory(PVOID Address, PVOID Data, DWORD DataSize, bool RestoreProt);
int   _stdcall SizeOfSignatureData(LPSTR Signature, UINT SigLen=0);
bool  _stdcall IsMemSignatureMatch(PVOID Address, LPSTR Signature, UINT SigLen=0);
PBYTE _stdcall FindMemSignatureInRange(PBYTE AddrLo, PBYTE AddrHi, LPSTR Signature, UINT Step=1, UINT MatchIdx=1, UINT SigLen=0);
PBYTE _stdcall FindMemSignatureInRangeSafe(PBYTE AddrLo, PBYTE AddrHi, LPSTR Signature, UINT Step=1, UINT MatchIdx=1, UINT SigLen=0);
//LPSTR _stdcall GetFileName(LPSTR FullPath);
//bool  _stdcall IsPathLink(LPSTR Name);
ULONGLONG __stdcall BinLongUMul(ULONGLONG Multiplicand, ULONGLONG Multiplier);
ULONGLONG __stdcall ShrULL(ULONGLONG Value, BYTE Shift);
ULONGLONG __stdcall ShlULL(ULONGLONG Value, BYTE Shift);
HGLOBAL _stdcall GetResource(HMODULE Module, LPSTR ResName, LPSTR ResType, PUINT ResSize);
UINT __stdcall SaveMemoryToFile(LPSTR FileName, DWORD ProcessID, DWORD Address, DWORD BlockSize, BYTE ErrorByte);
int _stdcall RedirectExports(HMODULE ModFrom, HMODULE ModTo);
int _stdcall ConvertToUTF8(PWSTR Src, LPSTR Dest, UINT DestLen);
long  _stdcall GetProcessPath(LPSTR ProcNameOrID, LPSTR PathBuffer, long BufferLngth);
UINT _stdcall GetRandomValue(UINT MinVal, UINT MaxVal);
HMODULE _stdcall FindModuleByExpName(LPSTR ModuleName);
//---------------------------------------------------------------------------


// Thread Environment Block (TEB)
/*#if defined(_M_X64) // x64
PTEB tebPtr = reinterpret_cast<PTEB>(__readgsqword(reinterpret_cast<DWORD_PTR>(&static_cast<NT_TIB*>(nullptr)->Self)));
#else // x86
PTEB tebPtr = reinterpret_cast<PTEB>(__readfsdword(reinterpret_cast<DWORD_PTR>(&static_cast<NT_TIB*>(nullptr)->Self)));
#endif

// Process Environment Block (PEB)
PPEB pebPtr = tebPtr->ProcessEnvironmentBlock;*/
//static inline PEB* NtCurrentPeb (VOID){return NtCurrentTeb()->ProcessEnvironmentBlock;}
//====================================================================================
#define ADDROFFSET(addr,offset) ((addr)+(offset))

#ifndef _REV_DW
#define _REV_DW(Value)    (((DWORD)(Value) << 24)|((DWORD)(Value) >> 24)|(((DWORD)(Value) << 8)&0x00FF0000)|(((DWORD)(Value) >> 8)&0x0000FF00))
#endif
//---------------------------------------------------------------------------
// Compiler always generates Stack Frame Pointers for member functions - used 'pop EBP' to restore it
// How to force the compiler do not make stack frame pointer ?
// How to force the compiler do not push ECX ?
// For __thiscall
#ifndef JUMPVFTMEMBER
#define JUMPVFTMEMBER(Index) __asm pop  ECX           \
                             __asm pop  EBP           \
                             __asm mov  EAX, [ECX]    \
                             __asm add  EAX, Index*4  \
                             __asm jmp  [EAX] 
//---------------------------------------------------------------------------
#endif
#ifndef JUMPEXTMEMBER                                            // for 'thiscall'
#define JUMPEXTMEMBER(Base,Offset) __asm pop  ECX                \
                                   __asm pop  EBP                \
                                   __asm mov  EAX, Base          \
                                   __asm lea  EAX, [EAX+Offset]  \
                                   __asm jmp  EAX 
//---------------------------------------------------------------------------
#endif
#ifndef JUMPEXTMEMBERDC                                           // for 'COM'
#define JUMPEXTMEMBERDC(Address) __asm pop  EBP                \
                                 __asm mov  EAX, Address       \
                                 __asm jmp  EAX 
//---------------------------------------------------------------------------
#endif
#ifndef JUMPEXTMEMBERD                                           // for 'COM'
#define JUMPEXTMEMBERD(Address) __asm pop  ECX                \
                                __asm pop  EBP                \
                                __asm mov  EAX, Address       \
                                __asm jmp  EAX 
//---------------------------------------------------------------------------
#endif

template <typename T> inline T RotL(T Value, unsigned char Shift){return (Value << Shift) | (Value >> ((sizeof(T) * 8U) - Shift));}
template <typename T> inline T RotR(T Value, unsigned char Shift){return (Value >> Shift) | (Value << ((sizeof(T) * 8U) - Shift));}

template<typename N, typename M> __inline M NumToPerc(N Num, M MaxVal){return (((Num)*100)/(MaxVal));}
template<typename P, typename M> __inline M PercToNum(P Per, M MaxVal){return (((Per)*(MaxVal))/100);}                         

template<class N, class M> __inline M AlignFrwd(N Value, M Alignment){return ((((Value)/(Alignment))+((bool)((Value)%(Alignment))))*(Alignment));}
template<class N, class M> __inline M AlignBkwd(N Value, M Alignment){return (((Value)/(Alignment))*(Alignment));}


struct SAsm   // Data section must be executable to use this
{
#ifdef _AMD64_
 enum ECodes {cAddSP=0,cSubSP=6};
static PVOID GetCode(UINT Offs)
{
 BYTE Code[] = {
/*0000*/   0x58, 0x48,0x01,0xCC, 0xFF,0xE0,     // pop RAX;  add RSP, RCX; jmp RAX
/*0006*/   0x58, 0x48,0x29,0xCC, 0xFF,0xE0      // pop RAX;  sub RSP, RCX; jmp RAX
};   
 return &Code[Offs];
}
#else
enum ECodes {cAddSP=0,cSubSP=6};
static PVOID GetCode(UINT Offs)
{
 return 0;
}
#endif 
//---------------------------------------------------------------------------
static void AddSP(UINT Val)
{
 ((void (_fastcall *)(UINT))GetCode(cAddSP))(Val);
}
//---------------------------------------------------------------------------
static void SubSP(UINT Val)
{
 ((void (_fastcall *)(UINT))GetCode(cSubSP))(Val);
}
//---------------------------------------------------------------------------

};

/*

0 -> 0
1, 2, 3, 4 -> 4
5, 6, 7, 8 -> 8
9, 10, 11, 12 -> 12

template <size_t alignTo, typename T>
INLINE T HiAlignPtr(T ptr)
{
    return reinterpret_cast<T>((reinterpret_cast<size_t>(ptr) + alignTo - 1) & ~(alignTo - 1));
}

// =================================================================================================

0, 1, 2, 3 -> 0
4, 5, 6, 7 -> 4
8, 9, 10, 11 -> 8

template <size_t alignTo, typename T>
INLINE T LoAlignPtr(T ptr)
{
    return reinterpret_cast<T>(reinterpret_cast<size_t>(ptr) & ~(alignTo - 1));
}

// =================================================================================================


Returns whether pointer is N-byte aligned.

template <size_t N, typename T>
INLINE bool IsAligned(T ptr)
{
    return HiAlignPtr<N>(ptr) == ptr;
}

// =================================================================================================



*/

template<class R, class T> __inline R GetAddress(T Src){return reinterpret_cast<R>(reinterpret_cast<void* &>(Src));}
//template<class T> __inline void ZeroStruct(T &Stru){FastZeroMemory(&Stru,sizeof(Stru));}  
//template<class T> __inline void ZeroPointer(T Stru){FastZeroMemory(Stru,sizeof(*Stru));}
template<class T> __inline T*   AddressOf(T Src){return reinterpret_cast<T*>(reinterpret_cast<void* &>(Src));}
template<class T> __inline int  SetAddressInVFT(PVOID VFT, int Index, T Proc, LPSTR Signature=NULL){PVOID Addr=reinterpret_cast<PVOID>(reinterpret_cast<void* &>(Proc));return MemoryPatchLocal(&((PVOID*)VFT)[Index], &Addr, sizeof(PVOID), Signature);}
template<class T> __inline bool SetPtrAddress(PVOID Src, T &Dst, LPSTR Signature=NULL)
{
 if(IsMemSignatureMatch(Src, Signature)){Dst = reinterpret_cast<T>(Src);return false;}
   else return true;
}

__inline void __cdecl SetAddress(PVOID SrcAddr,...){((PVOID*)(((PVOID*)&SrcAddr)[1]))[0] = SrcAddr;}   // Hack :)  

	
template<typename T> struct SSPPtr   // With this we can have any static members without a separate initialization   // static SSPPtr<decltype(::NtQueryInformationThread)> NtQueryInformationThread;     
{
 inline T*& Val(){static T* v; return v;}    // A static value holder
 inline bool IsNull(void){return (Val() == 0);}     
 inline void operator = (void* p) {Val() = (T*)p;}     
 inline operator T* () {return Val();}
};


/*
All anonymous, unnamed namespaces in global scope (that is, unnamed namespaces that are not nested) of
 the same translation unit share the same namespace. This way you can make static declarations without using the 'static' keyword.
Each identifier that is enclosed within an unnamed namespace is unique within the translation unit in which the unnamed namespace is defined.
*/

 __inline bool IsFilePathDelim(WCHAR val){return ((val == PATHDLML)||(val == PATHDLMR));}
// Use a period (.) as a directory component in a path to represent the current directory.
// Use two consecutive periods (..) as a directory component in a path to represent the parent of the current directory.
template<typename T> __inline bool _stdcall IsDirSpecifier(T Name){return (((Name[0] == '.')&&(Name[1] == 0))||((Name[0] == '.')&&(Name[1] == '.')&&(Name[2] == 0)));}
//template<typename T> bool IsPathLink(T* Path){return (((Path[0] == '.')&&(Path[1] == 0))||((Path[0] == '.')&&(Path[1] == '.')&&(Path[2] == 0)));}

//====================================================================================
template <typename T> bool _fastcall IsNumberInRange(T Number, T TresholdA, T TresholdB)
{
 T vMin, vMax; 
 if(TresholdA < TresholdB){vMin=TresholdA;vMax=TresholdB;}  // Is it really necessary?
   else {vMin=TresholdB;vMax=TresholdA;}
 return ((Number >= vMin)&&(Number <= vMax));
}
//---------------------------------------------------------------------------
/*template <typename T> static CJSonItem* EnsureParam(T val, LPSTR Name, CJSonItem* Owner)  // If parameter don`t esist - creates it and sets to 'Val' else just returns pointer to it
{
 CJSonItem* res = Owner->Get(Name);
 if(!res)res = Owner->Add(CJSonItem((T)val,Name));	 //	... and  'const char*' becomes 'bool' if overloaded constr exists only for 'char*' - WHY???!!!
 return res;
}
//---------------------------------------------------------------------------
template <typename T> static CJSonItem* SetParamValue(T val, LPSTR Name, CJSonItem* Owner)
{
 CJSonItem* res = Owner->Get(Name);
 if(!res)res = Owner->Add(CJSonItem((T)val,Name));
 (*res) = (T)val;
 return res;
}*/
//---------------------------------------------------------------------------
template <typename T> static T crc_calc_dir(T base, T crc, char *str, UINT len)
{
 for(;len;str++,len--)
  {
   crc ^= *str;
   for(int ctr=0;ctr<8;ctr++)crc = ((crc & 1)?((crc >> 1) ^ base):(crc >> 1));  
  }
 return crc; 
}
//--------------------------------------------------------------------------- 
template<typename T> void _stdcall HookEntryVFT(UINT Index, PVOID VftPtr, PVOID* OrigAddr, T HookProc)
{
 PVOID  Proc = GetAddress<PVOID>(HookProc);  //  (&HookIDirect3D9::HookCreateDevice);
 if(((PVOID*)VftPtr)[Index] != Proc)
  {
   *OrigAddr = ((PVOID*)VftPtr)[Index]; 
   WriteLocalProtectedMemory(&((PVOID*)VftPtr)[Index], &Proc, sizeof(PVOID), TRUE);
  }
}
//--------------------------------------------------------------------------- 
template<typename T> bool _stdcall IsPathLink(T Name)
{
 if((Name[0] == '.')&&(Name[1] == 0))return true;
 if((Name[0] == '.')&&(Name[1] == '.')&&(Name[2] == 0))return true;
 return false;
}
//---------------------------------------------------------------------------
template<typename T> char* _fastcall DecNumToStrU(T Val, char* buf, int* Len)
{
 if(Val == 0){if(Len)*Len = 1; return "0";}
 buf  = &buf[20];
 *buf = 0;
 char* end = buf;
 for(buf--;Val;buf--)
  {
   *buf  = (Val % 10) + '0';
   Val  /= 10;
  }
 buf++;
 if(Len)*Len = end-buf; 
  else buf[end-buf] = 0;
 return buf;
}
//--------------------------------------------------------------------------- 
static _inline BYTE _fastcall CharLowSimple(BYTE val){return (((val >= 'A')&&(val <= 'Z'))?(val + 0x20):(val));}    // TODO: Use lambda in template (But no BDS 2006 then :( )
template<typename A, typename B> int GetSubStrOffsSimpleIC(A StrVal, B StrBase, UINT Offs=0, UINT Len=0)   // NOTE: Keep usage of WinAPI to a minimum and try to support both CHAR and WCHAR
{
 if(!StrBase || !StrVal || !*StrVal || (Offs > Len))return -2;
 for(int voffs=0;StrBase[Offs];Offs++)
  {
   if(CharLowSimple(StrBase[Offs]) != CharLowSimple(StrVal[voffs]))voffs = 0;  // Reset scan
    else { voffs++; if(!StrVal[voffs])return Offs-voffs+1; }  // Exit if Full sub str match found        
  }
 return -1;
}
//--------------------------------------------------------------------------- 
template<typename A, typename B> int IsContainSubStrSimpleIC(B StrBase, A StrVal){return (GetSubStrOffsSimpleIC(StrVal, StrBase) >= 0);}
template<typename A, typename B> int StrCompareSimpleIC(A StrValA, B StrValB)  // Not exactly standart!
{
 if(!StrValA || !StrValB)return -1;
 for(int voffs=0;;voffs++)
  {
   if(!StrValA[voffs])return 0;;     
   if(CharLowSimple(StrValA[voffs]) != CharLowSimple(StrValB[voffs]))return voffs+1;
  }
}
//--------------------------------------------------------------------------- 
template<typename T> int _stdcall GetSubStrOffs(T* Str, T* SubStr, int Length=0, bool CaseSens=false)   // if constexpr (...)   // Zero-Terminated strings only! - Fix this
{
 Length = lstrlen(SubStr);
 DWORD Flags = (!CaseSens)?(NORM_IGNORECASE):(0);
 for(int Offs=0;*Str;Offs++,Str++)
  {
   if(CompareString(LOCALE_INVARIANT,Flags,Str,LenSubStr,SubStr,LenSubStr) == CSTR_EQUAL)return Offs;
  }
 return -1;
}
//------------------------------------------------------------------------------------------------------------
template<typename T> UINT TrimFilePath(T Path)
{
 int SLast = -1;
 for(int ctr=0;Path[ctr];ctr++)
  {
   if((Path[ctr] == 0x2F)||(Path[ctr] == 0x5C))SLast = ctr;
  }
 SLast++;
 if(SLast > 0)Path[SLast] = 0;
 return SLast;
}
//---------------------------------------------------------------------------
template<typename T> UINT StrLen(T Path)
{
 UINT len = 0;
 for(;Path[len];len++);
 return len;
}
//---------------------------------------------------------------------------
template<typename D, typename S> UINT StrCopy(D Dst, S Src)
{
 UINT len = 0;
 for(;Src[len];len++)Dst[len] = Src[len];
 Dst[len] = 0;
 return len;
}
//---------------------------------------------------------------------------
template<typename D, typename S> UINT StrCopy(D Dst, S Src, UINT MaxLen)
{
 UINT len = 0;
 for(;Src[len] && (len < MaxLen);len++)Dst[len] = Src[len];
 Dst[len] = 0;
 return len;
}
//---------------------------------------------------------------------------
template<typename T> T GetFileName(T FullPath)    // TODO: Just scan forward, no StrLen and backward scan  // Set constexpr 'IF' in case a T is a str obj an its size is known?
{
 int LastDel = -1; 
 for(int ctr=0;BYTE val=FullPath[ctr];ctr++){if(IsFilePathDelim(val))LastDel=ctr;}
 return &FullPath[LastDel+1];
}
//---------------------------------------------------------------------------
template<typename T> T GetFileExt(T FullPath) 
{
 int LastDel = -1;
 int ctr = 0;
 for(;BYTE val=FullPath[ctr];ctr++){if(val=='.')LastDel=ctr;}
 if(LastDel < 0)LastDel = ctr-1;
 return &FullPath[LastDel+1];
}
//---------------------------------------------------------------------------
template<typename T> bool IsFileExists(T FilePath)
{
 return !(((sizeof(*FilePath) > 1)?(GetFileAttributesW((PWSTR)FilePath)):(GetFileAttributesA((LPSTR)FilePath))) == INVALID_FILE_ATTRIBUTES);
}
//---------------------------------------------------------------------------
template<typename T> int NormalizeFileName(T FileName, char rep='_')  // Use counter that T may be an object with [] operator
{
 int Total = 0;
 for(int ctr=0;BYTE val=FileName[ctr];ctr++)
  {
   if((val == '|')||(val == '<')||(val == '>')||(val == '"')||(val == '?')||(val == '*')||(val == ':')/*||(val == '\\')||(val == '/')*/){FileName[ctr] = rep; Total++;}
  }
 return Total;
} 
//---------------------------------------------------------------------------
template<typename T> T IncrementFileName(T FileName)
{
 if(!IsFileExists(FileName))return FileName;
 BYTE Buf[32];
 T ExtPtr = GetFileExt(FileName);
 StrCopy((T)&Buf, &ExtPtr[-1]);
 for(UINT ctr=0;;ctr++) 
  {
   if(sizeof(*FileName) > 1)wsprintfW((PWSTR)ExtPtr,L"%u%ls",ctr,&Buf);   // TODO: Use own templated NumToStr function
     else wsprintfA((LPSTR)ExtPtr,"%u%s",ctr,&Buf);
   if(!IsFileExists(FileName))break;
  }
 return FileName;
}
//---------------------------------------------------------------------------
/*template<typename T> T GetCmdLineBegin(T CmdLine)
{
 char SFch = '"';
 while(*CmdLine && (*CmdLine <= 0x20))CmdLine++;
 if(*CmdLine == SFch)CmdLine++;
   else SFch = 0x20;
 while(*CmdLine && (*CmdLine != SFch))CmdLine++;
 if(*CmdLine)CmdLine++;
 while(*CmdLine && (*CmdLine <= 0x20))CmdLine++;
 return CmdLine; 
}*/
//---------------------------------------------------------------------------
template<typename T> T GetCmdLineParam(T CmdLine, T Param, PUINT ParLen=NULL)  //, unsigned int ParLen)  // Return size of Param string? // May overflow without 'ParLen'
{
 char SFch = '"';
 while(*CmdLine && (*CmdLine <= 0x20))CmdLine++;  // Skip any spaces before
 if(*CmdLine == SFch)CmdLine++;  // Skip opening quote
   else SFch = 0x20;             // No quotes, scan until a first space
 T ParBeg = CmdLine;
 if(Param)
  {
   UINT MaxLen = (ParLen)?(*ParLen):(-1);  // -1 is MaxUINT
   while(*CmdLine && (*CmdLine != SFch) && MaxLen--)*(Param++) = *(CmdLine++); 
   *Param = 0;
  }
  else {while(*CmdLine && (*CmdLine != SFch))CmdLine++;}
 if(ParLen)*ParLen = CmdLine - ParBeg;  // In Chars
 if(*CmdLine)CmdLine++;  // Skip last Quote or Space
// while(*CmdLine && (*CmdLine <= 0x20))CmdLine++; // Skip any spaces after 
 return CmdLine; 
}
//---------------------------------------------------------------------------
// Return address always points to Number[16-MaxDigits];
//
template<typename T, typename S> S ConvertToHexStr(T Value, int MaxDigits, S NumBuf, bool UpCase) 
{
 const int cmax = sizeof(T)*2;      // Number of byte halves (Digits)
 char  HexNums[] = "0123456789ABCDEF0123456789abcdef";
 UINT Case = UpCase?0:16;

 if(MaxDigits <= 0)MaxDigits = (Value > 0xFFFFFFFF)?(16):((Value > 0xFFFF)?(8):((Value > 0xFF)?(4):(2)));    // Auto set max digits
 S DstPtr = &NumBuf[MaxDigits-1];
 for(int Ctr = 0;DstPtr >= NumBuf;DstPtr--)   // Start from last digit
  {
   if(Ctr < cmax)
    {
     *DstPtr = HexNums[(Value & 0x0000000F)+Case];   // From end of buffer
     Value = Value >> 4;
     Ctr++;
    }
     else *DstPtr = '0';
  }
 NumBuf[MaxDigits] = 0;
 return NumBuf; 
}
//---------------------------------------------------------------------------
template<typename T> T _fastcall CharLowSimple(T val) {return (((val >= 'A') && (val <= 'Z')) ? (val + 0x20) : (val));}

template<typename T> bool _fastcall IsStrEqSimpleIC(T StrA, T StrB, int MaxLen)
{
 for(int ctr = 0; (MaxLen < 0) || (ctr < MaxLen); ctr++)
  {
   if(CharLowSimple(StrA[ctr]) != CharLowSimple(StrB[ctr]))return false;
   if(!StrA[ctr])break;
  }
 return true;
}
//---------------------------------------------------------------------------
template<typename T, typename S> S DecNumToStrS(T Val, S buf, int* Len=0)     
{
 if(Val == 0){if(Len)*Len = 1; *buf = '0'; buf[1] = 0; return buf;}
 bool isNeg = (Val < 0);
 if(isNeg) Val = -Val;
 buf  = &buf[20];
 *buf = 0;
 S end = buf;
 for(buf--;Val;buf--)
  {
   *buf  = (Val % 10) + '0';
   Val  /= 10;
  }
 if(isNeg)*buf = '-';
   else buf++;
 if(Len)*Len = end-buf;
 return buf;
} 
//---------------------------------------------------------------------------
inline BYTE EncryptByteWithCtr(BYTE Val, BYTE Key, UINT ctr){return ((Val ^ Key)+(BYTE)(ctr * (UINT)Key));}
inline BYTE DecryptByteWithCtr(BYTE Val, BYTE Key, UINT ctr){return ((Val - (BYTE)(ctr * (UINT)Key)) ^ Key);}
inline void EncryptStrSimple(LPSTR SrcStr, LPSTR DstStr, BYTE Key, UINT Size=0)
{
 if(!SrcStr || !Key)return; 
 if(!DstStr)DstStr = SrcStr;
 UINT ctr = 0; 
 if(!Size)Size = -1;
 for(;SrcStr[ctr] && (ctr < Size);ctr++)DstStr[ctr] = EncryptByteWithCtr(SrcStr[ctr], Key, ctr); 
 DstStr[ctr]=EncryptByteWithCtr(SrcStr[ctr], Key, ctr);   // Encrypt Terminating 0
}
//---------------------------------------------------------------------------
inline void DecryptStrSimple(LPSTR SrcStr, LPSTR DstStr, BYTE Key, UINT Size=0)
{
 if(!SrcStr || !Key)return; 
 if(!DstStr)DstStr = SrcStr;
 UINT ctr = 0; 
 if(!Size)Size = -1;
 for(;ctr < Size;ctr++)
  {
   DstStr[ctr] = DecryptByteWithCtr(SrcStr[ctr], Key, ctr); 
   if(!DstStr[ctr])break;    // A terminating 0 decrypted
  }
}
//---------------------------------------------------------------------------
template<typename S> UINT BinToBlobArray(S& OutStrm, PBYTE BinPtr, UINT SizeInBytes, BYTE XorKey=0, UINT ESize=sizeof(void*))
{
 BYTE Line[768];
 OutStrm += "unsigned int BSize = ";            
 OutStrm += (int)SizeInBytes;
 OutStrm += ";\r\n";
 if(ESize == 1)OutStrm += "unsigned char Blob[] = {\r\n";
 else if(ESize == 2)OutStrm += "unsigned short Blob[] = {\r\n";
 else if(ESize == 4)OutStrm += "unsigned long Blob[] = {\r\n";
  else OutStrm += "unsigned __int64 Blob[] = {\r\n";
 UINT ElemSize = ESize*sizeof(WORD);  
 while(SizeInBytes > 0)
  {       
   UINT Offs = 0;
   Line[Offs++] = '\t'; 
   while(((Offs+ElemSize) < (sizeof(Line)-3))&&(SizeInBytes > 0))    // 3 = 0x,
    { 
     Line[Offs++] = '0';
     Line[Offs++] = 'x';
     PWORD BPtr = (PWORD)&Line[Offs];
     Offs += ElemSize;
     PWORD EPtr = (PWORD)&Line[Offs];      
     for(UINT ctr=0;ctr < ESize;ctr++)
      {
       EPtr--; 
       if(SizeInBytes){*EPtr = HexToChar(EncryptByteWithCtr(*BinPtr,XorKey,SizeInBytes)); BinPtr++; SizeInBytes--;} 
        else *EPtr = 0x3030;  // '00'
      }
     if(SizeInBytes)Line[Offs++] = ',';
    }
   Line[Offs++] = '\r';
   Line[Offs++] = '\n';
   Line[Offs++] = 0;
   OutStrm += (char*)&Line;
  }
 OutStrm += "};\r\n";
 return OutStrm.Length();
}
//---------------------------------------------------------------------------


//#if defined _M_X64
//#pragma pack(push,8)	// NOTE: Why 'pack(push,8)' is not working here?
//#else
//#pragma pack(push,4)
//#endif

/*
typedef struct _LSA_UNICODE_STRING {
    USHORT Length;
    USHORT MaximumLength;
    PWSTR  Buffer;
} UNICODE_STRING, *PUNICODE_STRING;

struct FILE_BASIC_INFORMATION 
{
  LARGE_INTEGER CreationTime;
  LARGE_INTEGER LastAccessTime;
  LARGE_INTEGER LastWriteTime;
  LARGE_INTEGER ChangeTime;
  ULONG         FileAttributes;
#if defined _M_X64
  ULONG Bogus;
#endif
};

struct FILE_STANDARD_INFORMATION 
{
  LARGE_INTEGER AllocationSize;
  LARGE_INTEGER EndOfFile;
  ULONG         NumberOfLinks;
  BOOLEAN       DeletePending;
  BOOLEAN       Directory;
};

// ...
struct FILE_ALL_INFORMATION 
{
  FILE_BASIC_INFORMATION     BasicInformation;
  FILE_STANDARD_INFORMATION  StandardInformation;
//  FILE_INTERNAL_INFORMATION  InternalInformation;
//  FILE_EA_INFORMATION        EaInformation;
//  FILE_ACCESS_INFORMATION    AccessInformation;
//  FILE_POSITION_INFORMATION  PositionInformation;
//  FILE_MODE_INFORMATION      ModeInformation;
//  FILE_ALIGNMENT_INFORMATION AlignmentInformation;
//  FILE_NAME_INFORMATION      NameInformation;
};

#define FILE_SUPERSEDE                  0x00000000
#define FILE_OPEN                       0x00000001
#define FILE_CREATE                     0x00000002
#define FILE_OPEN_IF                    0x00000003
#define FILE_OVERWRITE                  0x00000004
#define FILE_OVERWRITE_IF               0x00000005
#define FILE_MAXIMUM_DISPOSITION        0x00000005

typedef struct _OBJECT_ATTRIBUTES {
    ULONG Length;
    HANDLE RootDirectory;
    PUNICODE_STRING ObjectName;
    ULONG Attributes;
    PVOID SecurityDescriptor;        // Points to type SECURITY_DESCRIPTOR
    PVOID SecurityQualityOfService;  // Points to type SECURITY_QUALITY_OF_SERVICE
} OBJECT_ATTRIBUTES;
typedef OBJECT_ATTRIBUTES *POBJECT_ATTRIBUTES;

typedef struct _IO_STATUS_BLOCK {
    union {
        ULONG Status;
        PVOID Pointer;
    };

    ULONG_PTR Information;
} IO_STATUS_BLOCK, *PIO_STATUS_BLOCK;

typedef
VOID
(NTAPI *PIO_APC_ROUTINE) (
    IN PVOID ApcContext,
    IN PIO_STATUS_BLOCK IoStatusBlock,
    IN ULONG Reserved
    );
     */
//#pragma pack(pop)
//---------------------------------------------------------------------------
class CHndl
{
 HANDLE hHand;
public:
 CHndl(void){this->hHand = INVALID_HANDLE_VALUE;}
 CHndl(HANDLE hVal){this->hHand = hVal;}
 ~CHndl(){this->Close();}
 void Close(void){if(this->IsValid()){CloseHandle(this->hHand); this->hHand = INVALID_HANDLE_VALUE;}}
 bool IsValid(void){return (((ULONG_PTR)this->hHand + 1) > 1);}
 operator   const HANDLE() {return this->hHand;}
 operator   const bool() {return this->IsValid();}
}; 
//---------------------------------------------------------------------------
template<typename T> class CArr
{
public:
 T* Data;

 CArr(void){this->Data = NULL;}
 CArr(UINT Cnt){this->Data = NULL; this->Resize(Cnt);}
 ~CArr(){this->Resize(0);}
 operator   const T*() {return this->Data;}
 UINT Count(void){return (this->Size / sizeof(T));}
 UINT Size(void){return ((this->Data)?(((size_t*)this->Data)[-1]):(0));}
 bool Resize(UINT Cnt)
 {
  Cnt = (Cnt*sizeof(T))+sizeof(size_t);
  HANDLE hHeap = GetProcessHeap();
  size_t* Ptr = (size_t*)this->Data;
  if(Cnt && this->Data)Ptr = (size_t*)HeapReAlloc(hHeap,HEAP_ZERO_MEMORY,&Ptr[-1],Cnt);
	else if(!this->Data)Ptr = (size_t*)HeapAlloc(hHeap,HEAP_ZERO_MEMORY,Cnt);
	  else if(!Cnt && this->Data){HeapFree(hHeap,0,&Ptr[-1]); this->Data=NULL; return false;}
  *Ptr = Cnt;
  this->Data = (T*)(++Ptr);
  return true;
 }
}; 
//---------------------------------------------------------------------------
template<typename T, int PreAll=0> class CGrowArray
{
 T* Data;

public:
 CGrowArray(void){this->Data=NULL; if(PreAll)this->Resize(PreAll);}   // Constructor of CDynBuffer will be called
 ~CGrowArray(){this->Resize(0);}      // Destructor of CDynBuffer will be called
 UINT Count(void){return (this->Data)?(((PDWORD)this->Data)[-2]):(0);}
 T* c_data(void){return this->Data;}
 T* Resize(UINT Elems) // Only enlarges the array // Used to avoid excess reallocations of a small blocks
 {
  if(!Elems){if(this->Data)HeapFree(GetProcessHeap(),0,&((PDWORD)this->Data)[-2]);}
   else
	{
	 PDWORD Val = &((PDWORD)this->Data)[-2];
	 UINT Size = (Elems*sizeof(T))+(sizeof(DWORD)*3);
	 if(!this->Data)Val = (PDWORD)HeapAlloc(GetProcessHeap(),0,Size);
	   else
		{
		 if(Elems <= Val[1]){Val[0] = Elems;return this->Data;}  // Only update the Count
		 Val = (PDWORD)HeapReAlloc(GetProcessHeap(),0,Val,Size);
		}
	 Val[0] = Val[1] = Elems;
	 this->Data = (T*)&Val[2];
	}
  return this->Data;
 }
 T&         operator [] (int index){return this->Data[index];}
//-------------
};
//---------------------------------------------------------------------------
template<int ChunkSize=0> class CChunkStream
{
 struct SChunk
  {
   UINT Size;
   UINT Free;
   SChunk* Next;
   BYTE Data[0];
  }*FirstChk;
 UINT Size;

public:
 CChunkStream(void){this->Data = NULL; this->Size = 0;}   // Constructor of CDynBuffer will be called
 ~CChunkStream(){this->Free();}      // Destructor of CDynBuffer will be called
 UINT GetSize(void){return this->Size;}
//-------------
 void* Append(void* Data, UINT Size, UINT Extra=0)
  {
   UINT DatSize = Size+Extra;
   UINT ChkSize = (DatSize > ChunkSize)?(DatSize):(ChunkSize);
   if(!this->FirstChk)
	{
	 this->FirstChk = (SChunk*)HeapAlloc(GetProcessHeap(),0,ChkSize+sizeof(SChunk));
	 this->FirstChk->Size = ChkSize;
	 this->FirstChk->Free = ChkSize;
	 this->FirstChk->Next = NULL;
	}
   SChunk* CurChk = NULL;
   SChunk* LstChk = this->FirstChk;
   for(SChunk* Chk = this->FirstChk;Chk;LstChk=Chk,Chk=Chk->Next)
	{
	 if(Chk->Free >= DatSize){CurChk = Chk; break;}
	}
   if(!CurChk)
	{
	 LstChk->Next = (SChunk*)HeapAlloc(GetProcessHeap(),HEAP_ZERO_MEMORY,ChkSize+sizeof(SChunk));
	 LstChk->Next->Size = ChkSize;
	 LstChk->Next->Free = ChkSize;
	 LstChk->Next->Next = NULL;
	 CurChk = LstChk->Next;
	}
   UINT Offs = CurChk->Size - CurChk->Free;
   CurChk->Free -= DatSize;
   this->Size   += DatSize;
   PVOID Dst = &CurChk->Data[Offs];
   memcpy(&((PBYTE)Dst)[Extra],Data,Size);
   return Dst;
  }
//-------------
 void Free(void)
  {
   SChunk* NxtChk = NULL;
   for(SChunk* Chk = this->FirstChk;Chk;Chk=NxtChk)
	{
	 NxtChk = Chk->Next;
	 HeapFree(GetProcessHeap(),0,Chk);
	}
   this->FirstChk = NULL;
   this->Size = 0;
  }
//-------------
};
//---------------------------------------------------------------------------
/*using namespace std;

class CXmlTableWriter
{
 bool ValsInTags;
 std::ofstream fs;
 xml::writer xw;
 xml::element* tbl;
 xml::element* rec;
 xml::element* srec;

public: 
CXmlTableWriter(LPSTR FilePath, bool UseTags): xw(fs),fs(FilePath,std::ofstream::binary|std::ofstream::trunc)  //,tbl(Name,xw)
{
 ValsInTags = UseTags;
 tbl = rec = srec = NULL;
}
//----------------------------
~CXmlTableWriter()
{
 if(tbl)delete(tbl);
 if(rec)delete(rec);
}
//----------------------------
void BeginTable(UINT Id, LPSTR Name, LPSTR Type, LPSTR ReleaseModule, LPSTR ReleaseSide)
{
 BYTE buff[64];
 tbl = new xml::element(Name,xw);  // Name is "table"
 tbl->attr("id", DecNumToStrU(Id, buff, NULL)).attr("type", Type).attr("release-module", ReleaseModule).attr("release-side", ReleaseSide).attr("version", "0.9");
}
//----------------------------
void EndTable(void)
{
 delete(tbl);
 tbl = NULL;
}
//----------------------------
void BeginRecord(LPSTR Name)
{
 rec = new xml::element(Name,xw); //,(LPSTR)&Tabuls);
}
//----------------------------
void EndRecord(void)
{
 delete(rec);
 rec = NULL;
}
//----------------------------
void BeginSubRecord(LPSTR Name)
{
 srec = new xml::element(Name,xw); //,(LPSTR)&Tabuls);
}
//----------------------------
void EndSubRecord(void)
{
 delete(srec);
 srec = NULL;
}
//----------------------------
void AddValue(LPSTR Name, LPSTR Value)
{
 if(!Value)Value = "";
 if(this->ValsInTags)
  {
   xml::element elem(Name,xw);
   elem.contents(Value);
  }
   else rec->attr(Name, Value);
}
//----------------------------
}; */
//---------------------------------------------------------------------------



#ifndef CompTimeH
#define ctENCSA(Str) (Str)
#define ctENCSW(Str) (Str)
#endif

#ifdef _DEBUG
#define DSIG(sig,cmnt)  sig##": "##cmnt
#else
#define DSIG(sig,cmnt)  sig
#endif

#define AddrBySig(sig,midx,base,size) AddrBySigInRange<__COUNTER__,midx>(sig, base, size) 
template<int Ctr, int MIdx, typename T> constexpr __forceinline PBYTE _stdcall AddrBySigInRange(T& Str, PBYTE Base, UINT Size)    // Passed an encryptes sig str but decrypted it only if the ptr is NULL  // Only as 'T&' it is passed as expected to the decryptor
{
 static PBYTE Addr = NULL; 
 if(!Addr)Addr = FindMemSignatureInRange(Base, &Base[Size], (LPSTR)&ctENCSA(Str)[0], 1, MIdx, 0);    // Include CompileTime.h or define an empty ctENCSA macro 
 return Addr;
}
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
#endif