.intel_syntax

.data

    .align 4
.global __ZN6inject14gnuinjectStateE
__ZN6inject14gnuinjectStateE:
local.isaac:
    .long 0
local.MTRandomLockedValue:
    .long 0
utils.Utf8Cprintf:
    .long 0
GetConsoleWindow:
    .long 0
_cprintf:
    .long 0
callbacks.PreSwapBuffers:
    .long 0
callbacks.OnExecuteCommand:
    .long 0
callbacks.OnConsoleOutput:
    .long 0
callbacks.PreWndProc:
    .long 0

tmpRetIP:
    .long 0
tmpLogLevel:
    .long 0
logPreFix:
    .long logPreFixCStr
logPreFixCStr:
    .asciz "[LOG(%d)] "

.text

.global __ZN6inject9LogPrintfEiPKcz
__ZN6inject9LogPrintfEiPKcz:
    call [GetConsoleWindow]
    test eax, eax
    je flag1
    push [esp + 0x04]
    push [logPreFix]
    call [_cprintf]
    add esp, 0x08
    pop [tmpRetIP]
    pop [tmpLogLevel]
    call [utils.Utf8Cprintf]
    push tmpLogLevel
    push tmpRetIP
    flag1 : push ebp
    mov ebp, esp
    and esp, -0x08
    mov eax, [local.isaac]
    add eax, 0x55E336
    jmp eax

.global @_ZN6inject14ExecuteCommandERN5isaac7ConsoleEPKvRKNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEEii@20
@_ZN6inject14ExecuteCommandERN5isaac7ConsoleEPKvRKNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEEii@20:
    push ecx
    push [esp + 0x10]
    push [esp + 0x10]
    push [esp + 0x10]
    call [callbacks.OnExecuteCommand]
    add esp, 0x0C
    pop ecx
    test eax, eax
    jne flag2
    push ebp
    mov ebp, esp
    push - 0x01
    mov eax, [local.isaac]
    add eax, 0x2655C5
    jmp eax
    flag2 : ret 0x0C

.global @_ZN6inject13ConsoleOutputERN5isaac7ConsoleEPKvRKNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEEjj@20
@_ZN6inject13ConsoleOutputERN5isaac7ConsoleEPKvRKNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEEjj@20:
    push ecx
    push [esp + 0x10]
    push [esp + 0x10]
    push [esp + 0x10]
    call [callbacks.OnConsoleOutput]
    add esp, 0x0C
    pop ecx
    test eax, eax
    jne flag3
    push ebp
    mov ebp, esp
    push - 0x01
    mov eax, [local.isaac]
    add eax, 0x26AEC5
    jmp eax
    flag3 : ret 0x0C

.global __ZN6inject8MTRandomEv
__ZN6inject8MTRandomEv:
    shr eax, 0x12
    xor eax, ecx
    push ebx
    mov ebx, [local.MTRandomLockedValue]
    cmp dword ptr [ebx], 0
    je flag4
    mov eax, [ebx]
    flag4 : pop ebx
    ret

.global __ZN6inject7WndProcEP6HWND__jjl@16
__ZN6inject7WndProcEP6HWND__jjl@16:
    call [callbacks.PreWndProc]
    test eax, eax
    jne flag5
    push ebp
    mov ebp, esp
    and esp, -0x40
    mov eax, [local.isaac]
    add eax, 0X5971D6
    jmp eax
    flag5 : ret 0x10

.global __ZN6inject11SwapBuffersEv
__ZN6inject11SwapBuffersEv:
    call [callbacks.PreSwapBuffers]
    test eax, eax
    je flag_r0
    add esp, 0x04
    jmp flag_r1
    flag_r0 : call edi
    flag_r1 : pop edi
    pop esi
    mov esp, ebp
    mov eax, local.isaac
    add eax, 0x4B107C
    jmp eax

.global ___security_cookie
___security_cookie:
    ret

.global @__security_check_cookie@4
@__security_check_cookie@4:
    ret 4
