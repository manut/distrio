/**
 * distrio error helper
 *
 *  - inline functions to ease handling of Distrio::Error
 *
 * @author Manuel Traut <manut@mecka.net>
 * @licence GPLv2
 */

#include <time.h>

inline Distrio::Error *distrio_error (::Distrio::Error_code code,
	::Distrio::Error_level level,
	long module_id,
	std::string description)
{
	struct timespec ts;
	Distrio::Error *e = new Distrio::Error;

	clock_gettime (CLOCK_REALTIME, &ts);

	e->code = code;
	e->level = level;
	e->time.seconds = ts.tv_sec;
	e->time.nanoseconds = ts.tv_nsec;
	e->module_id = module_id;
	e->description = CORBA::string_dup (description.c_str ());

	return e;
}

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
