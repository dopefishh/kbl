BIN:=kbl

PREFIX?=/usr/local

LDLIBS:=-lX11
CFLAGS:=-O2 -Werror -Wall -Wextra -pedantic

all: $(BIN)

%.1.gz: %
	help2man --no-discard-stderr -s "KBL" -N ./$< | gzip -9 > $@

install: kbl kbl.1.gz
	install -D -t $(PREFIX)/bin kbl
	install -D -t $(PREFIX)/man/man1 kbl.1.gz
	mandb -q

clean:
	$(RM) $(BIN) $(BIN).1.gz
