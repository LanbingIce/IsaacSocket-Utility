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
callbacks.OnRender:
    .long 0
callbacks.OnGameUpdate:
    .long 0
callbacks.OnSpecialUpdate:
    .long 0
callbacks.OnExecuteCommand:
    .long 0
callbacks.OnConsoleOutput:
    .long 0
callbacks.OnWindowMessage:
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

.global __ZN6inject6RenderEv
__ZN6inject6RenderEv:
    call [callbacks.OnRender]
    push ebp
    mov ebp, esp
    and esp, -0x08
    mov eax, [local.isaac]
    add eax, 0x4B0606
    jmp eax

.global @_ZN6inject10GameUpdateEPN5isaac4GameE@4
@_ZN6inject10GameUpdateEPN5isaac4GameE@4:
    push ecx
    call [callbacks.OnGameUpdate]
    pop ecx
    push ebp
    mov ebp, esp
    and esp, -0x10
    mov eax, [local.isaac]
    add eax, 0x2CDCF6
    jmp eax

.global __ZN6inject13SpecialUpdateEv
__ZN6inject13SpecialUpdateEv:
    call [callbacks.OnSpecialUpdate]
    push ebp
    mov ebp, esp
    sub esp, 0x0C
    mov eax, [local.isaac]
    add eax, 0x2D0406
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
    push ebp
    mov ebp, esp
    push - 0x01
    mov eax, [local.isaac]
    add eax, 0x2655C5
    jmp eax

.global @_ZN6inject13ConsoleOutputERN5isaac7ConsoleEPKvRKNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEEjj@20
@_ZN6inject13ConsoleOutputERN5isaac7ConsoleEPKvRKNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEEjj@20:
    push ecx
    push [esp + 0x10]
    push [esp + 0x10]
    push [esp + 0x10]
    call [callbacks.OnConsoleOutput]
    add esp, 0x0C
    pop ecx
    push ebp
    mov ebp, esp
    push - 0x01
    mov eax, [local.isaac]
    add eax, 0x26AEC5
    jmp eax

.global __ZN6inject8MTRandomEv
__ZN6inject8MTRandomEv:
    shr eax, 0x12
    xor eax, ecx
    cmp dword ptr [local.MTRandomLockedValue], 0
    je flag2
    mov eax, [local.MTRandomLockedValue]
    flag2 : ret

.global __ZN6inject7WndprocEP6HWND__jjl@16
__ZN6inject7WndprocEP6HWND__jjl@16:
    call [callbacks.OnWindowMessage]
    test eax, eax
    je flag3
    push ebp
    mov ebp, esp
    and esp, -0x40
    mov eax, [local.isaac]
    add eax, 0X5971D6
    jmp eax
    flag3 : ret 0x10
