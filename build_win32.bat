
cl /nologo /Ox /EHsc /c hptl.c
lib /nologo hptl.obj /out:hptl.win32.lib
del hptl.obj

