# webby

A minimalist web browser.

---
Compile:

```
MINGW/$ gcc -o window.exe window.c -lgdi32 -Wl,--subsystem,windows

MSVC:\> cl gdi32.lib user32.lib window.c /link /subsystem:windows
```

---
Reference:

* [Parsing HTML documents - HTML standard (whatwg)](https://html.spec.whatwg.org/multipage/parsing.html#parsing)
* [HTML 2.0 - RFC 1866](https://www.rfc-editor.org/rfc/rfc1866.html)
