#include <windows.h>
#include <dbghelp.h>

typedef 
BOOL
(WINAPI * MINIDUMPWRITEDUMP)(
	_In_ HANDLE hProcess,
	_In_ DWORD ProcessId,
	_In_ HANDLE hFile,
	_In_ MINIDUMP_TYPE DumpType,
	_In_opt_ PMINIDUMP_EXCEPTION_INFORMATION ExceptionParam,
	_In_opt_ PMINIDUMP_USER_STREAM_INFORMATION UserStreamParam,
	_In_opt_ PMINIDUMP_CALLBACK_INFORMATION CallbackParam
);

typedef
BOOL
(WINAPI * SYMINITIALIZE)(
	_In_ HANDLE hProcess,
	_In_opt_ PCSTR UserSearchPath,
	_In_ BOOL fInvadeProcess
);

typedef
DWORD
(WINAPI * SYMSETOPTIONS)(
	_In_ DWORD   SymOptions
);

typedef
DWORD
(WINAPI * SYMGETOPTIONS)(
	VOID
);

typedef
BOOL
(WINAPI * SYMCLEANUP)(
	_In_ HANDLE hProcess
);

typedef
BOOL
(WINAPI * SYMGETTYPEINFO)(
	_In_ HANDLE hProcess,
	_In_ DWORD64 ModBase,
	_In_ ULONG TypeId,
	_In_ IMAGEHLP_SYMBOL_TYPE_INFO GetType,
	_Out_ PVOID pInfo
);

typedef
BOOL
(WINAPI * SYMGETLINEFROMADDR64)(
	_In_ HANDLE hProcess,
	_In_ DWORD64 qwAddr,
	_Out_ PDWORD pdwDisplacement,
	_Out_ PIMAGEHLP_LINE64 Line64
);

typedef
BOOL
(WINAPI * SYMENUMSYMBOLS)(
	_In_ HANDLE hProcess,
	_In_ ULONG64 BaseOfDll,
	_In_opt_ PCSTR Mask,
	_In_ PSYM_ENUMERATESYMBOLS_CALLBACK EnumSymbolsCallback,
	_In_opt_ PVOID UserContext
);

typedef
BOOL
(WINAPI * SYMSETCONTEXT)(
	_In_ HANDLE hProcess,
	_In_ PIMAGEHLP_STACK_FRAME StackFrame,
	_In_opt_ PIMAGEHLP_CONTEXT Context
);

typedef
BOOL
(WINAPI * SYMFROMADDR)(
	_In_ HANDLE hProcess,
	_In_ DWORD64 Address,
	_Out_opt_ PDWORD64 Displacement,
	_Inout_ PSYMBOL_INFO Symbol
);

typedef
BOOL
(WINAPI * STACKWALK64)(
	_In_ DWORD MachineType,
	_In_ HANDLE hProcess,
	_In_ HANDLE hThread,
	_Inout_ LPSTACKFRAME64 StackFrame,
	_Inout_ PVOID ContextRecord,
	_In_opt_ PREAD_PROCESS_MEMORY_ROUTINE64 ReadMemoryRoutine,
	_In_opt_ PFUNCTION_TABLE_ACCESS_ROUTINE64 FunctionTableAccessRoutine,
	_In_opt_ PGET_MODULE_BASE_ROUTINE64 GetModuleBaseRoutine,
	_In_opt_ PTRANSLATE_ADDRESS_ROUTINE64 TranslateAddress
);

typedef
PVOID
(WINAPI * SYMFUNCTIONTABLEACCESS64)(
	_In_ HANDLE hProcess,
	_In_ DWORD64 AddrBase
);

typedef
DWORD64
(WINAPI * SYMGETMODULEBASE64)(
	_In_ HANDLE hProcess,
	_In_ DWORD64 qwAddr
);

class CDbgHelpUtil
{
public:
	CDbgHelpUtil();
	virtual ~CDbgHelpUtil();
	
	static bool LoadDll(void);
	static void UnloadDll(void);

private:
	static FARPROC GetAPI(LPCSTR lpProcName);

	static HMODULE m_DbgHelpDll;
	static MINIDUMPWRITEDUMP m_MiniDumpWriteDump;
	static SYMINITIALIZE m_SymInitialize;
	static SYMSETOPTIONS m_SymSetOptions;
	static SYMGETOPTIONS m_SymGetOptions;
	static SYMCLEANUP m_SymCleanup;
	static SYMGETTYPEINFO m_SymGetTypeInfo;
	static SYMGETLINEFROMADDR64 m_SymGetLineFromAddr64;
	static SYMENUMSYMBOLS m_SymEnumSymbols;
	static SYMSETCONTEXT m_SymSetContext;
	static SYMFROMADDR m_SymFromAddr;
	static STACKWALK64 m_StackWalk64;
	static SYMFUNCTIONTABLEACCESS64 m_SymFunctionTableAccess64;
	static SYMGETMODULEBASE64 m_SymGetModuleBase64;
};
