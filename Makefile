all: window.exe

clean:
	del *.exe *.obj

window.exe:
	cl.exe gdi32.lib user32.lib $(CFLAGS) window.c /link /subsystem:windows
