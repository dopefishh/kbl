# KBL
`kbl` is a tool that prints the current active keyboard layout. This tool is
designed for multilayout keyboard config with a switch key such as:

```
xkb_keymap {
	xkb_keycodes  { include "evdev+aliases(qwerty)"	};
	xkb_types     { include "complete"	};
	xkb_compat    { include "complete"	};
	xkb_symbols   { include "pc+us(dvorak)+ru(phonetic_dvorak):2+us:3+inet(evdev)+group(menu_toggle)+compose(ralt)"	};
	xkb_geometry  { include "pc(pc105)"	};
};
```

## Requirements
A C compiler and the `X11` development headers. On a debian like system this
can be acquired by running `# apt-get install libx11-dev make gcc`. If you also
want to build the manpage you need `help2man` and `gzip`.

## Usage
To build the program run `make`
Read the man page

## Installation
Run `make install`.
If you want to install it with a different prefix then `/usr/local` you can
override it by running: `PREFIX=/home/frobnicator/.local make install`

## Author
`mart@martlubbers.net`
