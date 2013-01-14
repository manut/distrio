#include <iniparser.h>
#define GPIO_CONFIG "gpio.conf"

#ifdef __cplusplus
extern "C" {
#endif
int init (void);
dictionary * _iniparser_load (const char *conf);
int _iniparser_getnsec (dictionary *d);
char *_iniparser_getsecname (dictionary *d, int i);
void _iniparser_freedict (dictionary *d);
#ifdef __cplusplus
}
#endif
