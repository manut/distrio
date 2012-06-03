/**
 * distrio error helper
 *
 *  - inline functions to ease handling of Distrio::Error
 *
 * @author Manuel Traut <manut@mecka.net>
 * @licence GPLv2
 */

#include <time.h>

inline Distrio::Error *distrio_success (void) {
	struct timespec ts;
	Distrio::Error *e = new Distrio::Error;

	clock_gettime (CLOCK_REALTIME, &ts);

	e->code = Distrio::SUCCESS;
	e->level = Distrio::L_DEBUG;
	e->time.seconds = ts.tv_sec;
	e->time.nanoseconds = ts.tv_nsec;
	e->module_id = 0;
	e->description = CORBA::string_dup (__func__);

	return e;
}
