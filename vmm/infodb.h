// infodb.h : definitions related to the information read-only sqlite database.
//
// (c) Ulf Frisk, 2021-2022
// Author: Ulf Frisk, pcileech@frizk.net
//
#ifndef __INFODB_H__
#define __INFODB_H__
#include "vmm.h"

/*
* Check if a certificate is well know against the database.
* -- H
* -- qwThumbprintEndSHA1 = QWORD representation of the last 64 bits of the SHA-1 certificate thumbprint.
* -- return
*/
_Success_(return)
BOOL InfoDB_CertIsWellKnown(_In_ VMM_HANDLE H, _In_ QWORD qwThumbprintEndSHA1);

/*
* Query the InfoDB for the offset of a symbol.
* Currently only szModule values of 'nt', 'ntoskrnl', 'tcpip' is supported.
* -- H
* -- szModule
* -- szSymbolName
* -- pdwSymbolOffset
* -- return
*/
_Success_(return)
BOOL InfoDB_SymbolOffset(_In_ VMM_HANDLE H, _In_ LPSTR szModule, _In_ LPSTR szSymbolName, _Out_ PDWORD pdwSymbolOffset);

/*
* Read memory pointed to at the symbol offset.
* -- H
* -- szModule
* -- vaModuleBase
* -- szSymbolName
* -- pProcess
* -- pqw
* -- return
*/
_Success_(return)
BOOL InfoDB_GetSymbolQWORD(_In_ VMM_HANDLE H, _In_ LPSTR szModule, _In_ QWORD vaModuleBase, _In_ LPSTR szSymbolName, _In_ PVMM_PROCESS pProcess, _Out_ PQWORD pqw);

/*
* Read memory pointed to at the symbol offset.
* -- H
* -- szModule
* -- vaModuleBase
* -- szSymbolName
* -- pProcess
* -- pdw
* -- return
*/
_Success_(return)
BOOL InfoDB_SymbolDWORD(_In_ VMM_HANDLE H, _In_ LPSTR szModule, _In_ QWORD vaModuleBase, _In_ LPSTR szSymbolName, _In_ PVMM_PROCESS pProcess, _Out_ PDWORD pdw);

/*
* Read memory pointed to at the symbol offset.
* -- H
* -- szModule
* -- vaModuleBase
* -- szSymbolName
* -- pProcess
* -- pv = PDWORD on 32-bit and PQWORD on 64-bit _operating_system_ architecture.
* -- return
*/
_Success_(return)
BOOL InfoDB_SymbolPTR(_In_ VMM_HANDLE H, _In_ LPSTR szModule, _In_ QWORD vaModuleBase, _In_ LPSTR szSymbolName, _In_ PVMM_PROCESS pProcess, _Out_ PVOID pv);

/*
* Query the InfoDB for a static size populated in the static_type_size table.
* -- H
* -- szModule
* -- szTypeName
* -- pdwTypeSize
* -- return
*/
_Success_(return)
BOOL InfoDB_TypeSize_Static(_In_ VMM_HANDLE H, _In_ LPSTR szModule, _In_ LPSTR szTypeName, _Out_ PDWORD pdwTypeSize);

/*
* Query the InfoDB for the size of a type.
* Currently only szModule values of 'nt' or 'ntoskrnl' is supported.
* Support for nt/ntoskrnl/tcpip.
* -- H
* -- szModule
* -- szTypeName
* -- pdwTypeSize
* -- return
*/
_Success_(return)
BOOL InfoDB_TypeSize_Dynamic(_In_ VMM_HANDLE H, _In_ LPSTR szModule, _In_ LPSTR szTypeName, _Out_ PDWORD pdwTypeSize);

/*
* Query the InfoDB for the static offset of a child inside a type - often inside a struct.
* -- H
* -- szModule
* -- szTypeName
* -- uszTypeChildName
* -- pdwTypeOffset = offset relative to type base.
* -- return
*/
_Success_(return)
BOOL InfoDB_TypeChildOffset_Static(_In_ VMM_HANDLE H, _In_ LPSTR szModule, _In_ LPSTR szTypeName, _In_ LPSTR uszTypeChildName, _Out_ PDWORD pdwTypeOffset);

/*
* Query the InfoDB for the offset of a child inside a type - often inside a struct.
* Support for nt/ntoskrnl/tcpip.
* -- H
* -- szModule
* -- szTypeName
* -- uszTypeChildName
* -- pdwTypeOffset = offset relative to type base.
* -- return
*/
_Success_(return)
BOOL InfoDB_TypeChildOffset_Dynamic(_In_ VMM_HANDLE H, _In_ LPSTR szModule, _In_ LPSTR szTypeName, _In_ LPSTR uszTypeChildName, _Out_ PDWORD pdwTypeOffset);

/*
* Return whether the InfoDB symbols are ok or not.
* -- H
* -- pfNtos
* -- pfTcpIp
*/
VOID InfoDB_IsValidSymbols(_In_ VMM_HANDLE H, _Out_opt_ PBOOL pfNtos, _Out_opt_ PBOOL pfTcpIp);

/*
* Return if the InfoDB have been successfully initialized.
* Will return fail on no-init or failure to init (missing info.db file).
* -- H
* -- return
*/
BOOL InfoDB_IsInitialized(_In_ VMM_HANDLE H);

/*
* Initialize the InfoDB (if possible):
* -- H
*/
VOID InfoDB_Initialize(_In_ VMM_HANDLE H);

#endif /* __INFODB_H__ */
