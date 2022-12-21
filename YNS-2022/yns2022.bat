chcp 1251 >nul
call "C:\Program Files\Microsoft Visual Studio\2022\Community\VC\Auxiliary\Build\vcvarsall.bat" x86
call "C:\Users\User\Desktop\курсач\YNS-2022\Debug\YNS-2022.exe" -in:"C:\Users\User\Desktop\курсач\YNS-2022\YNS-2022\in.txt"  m l i
pause
ml /c /coff C:\Users\User\Desktop\курсач\YNS-2022\Generation\Generation\Gen.asm
link /OPT:NOREF /DEBUG C:\Users\User\Desktop\курсач\Gen.obj C:\Users\User\Desktop\курсач\YNS-2022\Generation\Debug\GenLib.lib /SUBSYSTEM:CONSOLE /NODEFAULTLIB:library
call C:\Users\User\Desktop\курсач\Gen.exe
pause