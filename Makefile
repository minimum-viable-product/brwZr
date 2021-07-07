all: window.exe

clean:
	@del *.exe *.obj \
	|| rm -f *.exe *.obj

window.exe:
	@cl.exe gdi32.lib user32.lib $(CFLAGS) window.c /link /subsystem:windows \
	|| gcc -o window.exe window.c -lgdi32 -Wl,--subsystem,windows
