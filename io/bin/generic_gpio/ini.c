#include "ini.h"
int init (){;}
dictionary *_iniparser_load (const char *conf) {
	return iniparser_load (conf);
}

int _iniparser_getnsec (dictionary *d) {
	return iniparser_getnsec (d);
}

char *_iniparser_getsecname (dictionary *d, int i) {
	return iniparser_getsecname (d, i);
}

void _iniparser_freedict (dictionary *d) {
	iniparser_freedict (d);
}
