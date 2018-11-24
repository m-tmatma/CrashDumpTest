#include "pch.h"
#include <windows.h>
#include <tchar.h>
#include <dbghelp.h>
#include "DbgHelpUtil.h"

#define DEVELOP_DBG_UTIL	1
#if DEVELOP_DBG_UTIL
#include <stdio.h>
#endif // DEVELOP_DBG_UTIL

HMODULE CDbgHelpUtil::m_DbgHelpDll = (HMODULE)INVALID_HANDLE_VALUE;
MINIDUMPWRITEDUMP CDbgHelpUtil::m_MiniDumpWriteDump = NULL;
SYMINITIALIZE CDbgHelpUtil::m_SymInitialize = NULL;
SYMSETOPTIONS CDbgHelpUtil::m_SymSetOptions = NULL;
SYMGETOPTIONS CDbgHelpUtil::m_SymGetOptions = NULL;
SYMCLEANUP CDbgHelpUtil::m_SymCleanup = NULL;
SYMGETTYPEINFO CDbgHelpUtil::m_SymGetTypeInfo = NULL;
SYMGETLINEFROMADDR64 CDbgHelpUtil::m_SymGetLineFromAddr64 = NULL;
SYMENUMSYMBOLS CDbgHelpUtil::m_SymEnumSymbols = NULL;
SYMSETCONTEXT CDbgHelpUtil::m_SymSetContext = NULL;
SYMFROMADDR CDbgHelpUtil::m_SymFromAddr = NULL;
STACKWALK64 CDbgHelpUtil::m_StackWalk64 = NULL;
SYMFUNCTIONTABLEACCESS64 CDbgHelpUtil::m_SymFunctionTableAccess64 = NULL;
SYMGETMODULEBASE64 CDbgHelpUtil::m_SymGetModuleBase64 = NULL;

CDbgHelpUtil::CDbgHelpUtil()
{
}

CDbgHelpUtil::~CDbgHelpUtil()
{
}

FARPROC CDbgHelpUtil::GetAPI(LPCSTR lpProcName)
{
	return ::GetProcAddress(m_DbgHelpDll, lpProcName);
}


bool CDbgHelpUtil::LoadDll(void)
{
	m_DbgHelpDll = ::LoadLibrary(_T("dbghelp.dll"));
	if (m_DbgHelpDll == NULL)
	{
		return false;
	}

	m_MiniDumpWriteDump = (MINIDUMPWRITEDUMP)GetAPI("MiniDumpWriteDump");
	if (m_MiniDumpWriteDump == NULL)
	{
		goto cleanup;
	}

	m_SymInitialize = (SYMINITIALIZE)GetAPI("SymInitialize");
	if (m_SymInitialize == NULL)
	{
		goto cleanup;
	}

	m_SymSetOptions = (SYMSETOPTIONS)GetAPI("SymSetOptions");
	if (m_SymSetOptions == NULL)
	{
		goto cleanup;
	}

	m_SymGetOptions = (SYMGETOPTIONS)GetAPI("SymGetOptions");
	if (m_SymGetOptions == NULL)
	{
		goto cleanup;
	}

	m_SymCleanup = 	(SYMCLEANUP)GetAPI("SymCleanup");
	if (m_SymCleanup == NULL)
	{
		goto cleanup;
	}

	m_SymGetTypeInfo = (SYMGETTYPEINFO)GetAPI("SymGetTypeInfo");
	if (m_SymGetTypeInfo == NULL)
	{
		goto cleanup;
	}
	m_SymGetLineFromAddr64 = (SYMGETLINEFROMADDR64)GetAPI("SymGetLineFromAddr64");
	if (m_SymGetLineFromAddr64 == NULL)
	{
		goto cleanup;
	}

	m_SymEnumSymbols = (SYMENUMSYMBOLS)GetAPI("SymEnumSymbols");
	if (m_SymEnumSymbols == NULL)
	{
		goto cleanup;
	}

	m_SymSetContext = (SYMSETCONTEXT)GetAPI("SymSetContext");
	if (m_SymSetContext == NULL)
	{
		goto cleanup;
	}

	m_SymFromAddr = (SYMFROMADDR)GetAPI("SymFromAddr");
	if (m_SymFromAddr == NULL)
	{
		goto cleanup;
	}

	m_StackWalk64 = (STACKWALK64)GetAPI("StackWalk64");
	if (m_StackWalk64 == NULL)
	{
		goto cleanup;
	}

	m_SymFunctionTableAccess64 = (SYMFUNCTIONTABLEACCESS64)GetAPI("SymFunctionTableAccess64");
	if (m_SymFunctionTableAccess64 == NULL)
	{
		goto cleanup;
	}

	m_SymGetModuleBase64 = (SYMGETMODULEBASE64)GetAPI("SymGetModuleBase64");
	if (m_SymGetModuleBase64 == NULL)
	{
		goto cleanup;
	}

	m_SymSetOptions(m_SymGetOptions() | SYMOPT_LOAD_LINES | SYMOPT_DEFERRED_LOADS);
	m_SymInitialize(::GetCurrentProcess(), NULL, TRUE);

	::SetUnhandledExceptionFilter(ExceptionHandler);
	return true;

cleanup:
	UnloadDll();
	return false;
}

void CDbgHelpUtil::UnloadDll(void)
{
	if (m_DbgHelpDll != NULL)
	{
		::FreeLibrary(m_DbgHelpDll);
		m_DbgHelpDll = NULL;
	}
}

LONG WINAPI CDbgHelpUtil::ExceptionHandler(PEXCEPTION_POINTERS ptrs)
{
#if DEVELOP_DBG_UTIL
	fprintf(stdout, "found: ERROR: ExceptionCode = %08x", ptrs->ExceptionRecord->ExceptionCode);
#endif
	return EXCEPTION_EXECUTE_HANDLER;
}
