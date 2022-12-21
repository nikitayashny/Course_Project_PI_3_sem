.586
.model flat, stdcall
includelib libucrt.lib
includelib kernel32.lib

includelib "C:\Users\User\Desktop\курсач\YNS-2022\Generation\Debug\GenLib.lib
ExitProcess PROTO:DWORD 
.stack 4096

 outnum PROTO : DWORD

 outstr PROTO : DWORD

 LineLen PROTO : DWORD

 CopyLine PROTO : DWORD, : DWORD

.const
		printline byte 13, 10, 0
		L1 sdword 1
		L2 byte ' ', 0
		L3 sdword 2
		L4 sdword 10
		L5 byte 'Вывод числа из шестнадцатиричного вида в десятичный: ', 0
		L6 byte 'Функция выбирающая нечетные числа', 0
		L7 byte 'Нижний предел: ', 0
		L8 byte 'Верхний предел: ', 0
		L9 byte 'Нечeтные числа: ', 0
		L10 sdword 5
		L11 byte 'Количество чисел плюс 5: ', 0
		L12 byte 'Никита Яшный', 0
		L13 byte 'Строка: ', 0
		L14 byte 'Длина строки: ', 0
		L15 byte 'Nikita', 0
		L16 byte 'Yashny', 0
		L17 byte 'Копирование одной строки в другую: ', 0
.data
		temp sdword ?
		buffer byte 256 dup(0)
		oddi sdword 0
		Maina sdword 0
		Mainb sdword 0
		Mainq sdword 0
		Maint dword ?
		Mains dword ?
		Mainl sdword 0
		Mainn dword ?
		Mainy dword ?
		Mainp sdword 0
.code

;----------- odd ------------
odd PROC,
	oddt : sdword, oddn : sdword  
push ebx
push edx

mov edx, oddt
cmp edx, oddn

jl repeat1
jmp repeatnext1
repeat1:
push oddi
push L1
pop ebx
pop eax
add eax, ebx
push eax

pop ebx
mov oddi, ebx


push oddt
call outnum



push offset L2
call outstr


push oddt
push L3
pop ebx
pop eax
add eax, ebx
push eax

pop ebx
mov oddt, ebx

mov edx, oddt
cmp edx, oddn

jl repeat1
repeatnext1:

pop edx
pop ebx
mov eax, oddi
ret
odd ENDP
;------------------------------


;----------- MAIN ------------
main PROC
push L1

pop ebx
mov Maina, ebx

push L4

pop ebx
mov Mainb, ebx

push L4

pop ebx
mov Mainq, ebx


push offset L5
call outstr



push Mainq
call outnum


push offset printline
call outstr

mov Maint, offset L6

push Maint
call outstr


push offset printline
call outstr


push offset L7
call outstr



push Maina
call outnum


push offset printline
call outstr


push offset L8
call outstr



push Mainb
call outnum


push offset printline
call outstr


push offset L9
call outstr



push Mainb
push Maina
call  odd
push eax
push L10
pop ebx
pop eax
add eax, ebx
push eax

pop ebx
mov Maina, ebx

push offset printline
call outstr


push offset L11
call outstr



push Maina
call outnum


push offset printline
call outstr

mov Mains, offset L12

push offset L13
call outstr



push Mains
call outstr


push offset printline
call outstr


push Mains
call  LineLen
push eax

pop ebx
mov Mainl, ebx


push offset L14
call outstr



push Mainl
call outnum


push offset printline
call outstr

mov Mainn, offset L15

push Mainn
call outstr


push offset printline
call outstr

mov Mainy, offset L16

push Mainy
call outstr


push offset printline
call outstr


push offset L17
call outstr



push Mainy
push Mainn
call  CopyLine

push offset printline
call outstr

push L1
push L1
push L3
pop ebx
pop eax
add eax, ebx
push eax
pop ebx
pop eax
imul eax, ebx
push eax

pop ebx
mov Mainp, ebx

push 0
call ExitProcess
main ENDP
end main
