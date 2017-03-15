#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>

#include <X11/XKBlib.h>

#define err(s) fputs(s "\n", stderr)

static struct option long_opts[] = {
	{"help", no_argument, 0, 'h'},
	{"version", no_argument, 0, 'v'},
	{0, 0, 0, 0}};

void usage(){
	fputs("Usage: kbl [OPTS] [DISPLAY]\n"
	      "Prints the current active keyboard layout\n"
	      "\n"
	      "Positional arguments:\n"
	      "\tDISPLAY - Optional display to use\n"
	      "Options:\n"
	      "\t--help,-h    - Print this help\n"
	      "\t--version,-v - Print the version\n", stderr);
}

int main(int argc, char **argv)
{
	Display *disp;
	char *display;
	char *layouts;
	int evCode, errRet, rsnRet;
	int min = XkbMinorVersion, maj = XkbMajorVersion;
	int opt;

	while((opt = getopt_long(argc, argv, "hv", long_opts, NULL)) != -1){
		switch(opt){
			case 'h':
				usage();
				return EXIT_SUCCESS;
			case 'v':
				puts("kbl version 0.1");
				return EXIT_SUCCESS;
			default:
				usage();
				break;
		}
	}
	if(optind + 1 < argc){
		err("Too many positional arguments");
		return EXIT_FAILURE;
	}

	display = optind + 1 == argc ? argv[optind] : "";

	disp = XkbOpenDisplay(display, &evCode, &errRet, &maj, &min, &rsnRet);
	if(disp == NULL){
		if(rsnRet == XkbOD_BadLibraryVersion)
			err("XkbLibraryVersion returned False");
		else if(rsnRet == XkbOD_ConnectionRefused)
			err("Display could not be opened");
		else if(rsnRet == XkbOD_BadServerVersion)
			err("Library and server have incompatible extension "
			    "versions");
		else if(rsnRet == XkbOD_NonXkbServer)
			err("Extension is not present in the X server");
		exit(EXIT_FAILURE);
	}

	XkbDescPtr desc = XkbAllocKeyboard();
	XkbGetNames(disp, XkbSymbolsNameMask, desc);

	Atom symNameAtom = desc->names->symbols;
	layouts = XGetAtomName(disp, symNameAtom);

	XkbStatePtr state = calloc(1, sizeof(XkbStateRec));
	XkbGetState(disp, 0x100, state);

	char *c, *d;
	for(c = layouts; *c; c++){
		if(*c == '+'){
			for(d = c+1; *d != '+' && *d != ':'; d++);
			if(state->group-- == 0){
				*d = '\0';
				puts(c+1);
				break;
			}
		}
	}

	return EXIT_SUCCESS;
}
