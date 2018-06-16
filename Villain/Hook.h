#pragma once

#include <Windows.h>

#include <ThirdParty\Detours\Detours.h>

#define PRE_NON_NAKED_CALL __asm				\
{												\
	__asm PUSH 0								\
	__asm PUSH EDI								\
	__asm LEA EDI, DWORD PTR DS : [ESP + 4]		\
	__asm PUSHAD								\
}

#define POST_NON_NAKED_CALL __asm				\
{												\
	__asm MOV DWORD PTR DS : [EDI], EAX			\
	__asm POPAD									\
	__asm POP EDI								\
}

#define MOV_RESULT_TO(_register) __asm			\
{												\
	__asm MOV _register, DWORD PTR DS : [ESP]	\
	__asm ADD ESP, 4							\
}

class Hook
{
	public:
		virtual void PatchCode(HANDLE process)
		{

		};

		virtual void InstallDetour()
		{

		};
};