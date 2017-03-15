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

## Usage
Read the man page

## Installation
Run `make install`.
If you want to install it with a different prefix then `/usr/local` you can
override it by running: `PREFIX=/home/frobnicator/.local make install`

## Author
`mart@martlubbers.net`
