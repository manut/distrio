#include <distrio_helper.h>
#include <distrio_error.h>
#include <distrio_io.h>

#include <ace/Task.h>

#include <iostream>
#include <gpio.h>

#include "ini.h"

#define MODULE_ID 1212

static void err (const char *s)
{
	fprintf (stderr, s);
}

class GPIO : public Distrio_Digital_i {
	public:
		GPIO (std::string io_name, int value, ::Distrio::Direction dir) :
			Distrio_Digital_i (io_name, dir) {
				int ret = -1;
				if (dir == ::Distrio::OUTPUT)
					ret = gpio_open_dir (&p, value, GPIO_OUT);
				if (dir == ::Distrio::INPUT)
					ret = gpio_open_dir (&p, value, GPIO_IN);
				if (ret) {
					id(-1);
					err ("open gpio failed\n");
				} else
					id(0);
		}

		::Distrio::Error *set () {

			if (gpio_set_value (&p, GPIO_HIGH))
				return distrio_error
					(Distrio::E_NOTSUPPORTED, Distrio::L_NORMAL, MODULE_ID, "set gpio failed");

			update_timestamp ();
			val = 1;
			std::cout << "set" << std::endl;
			return distrio_success ();
			
		}

		::Distrio::Error *reset () {

			if (gpio_set_value (&p, GPIO_LOW))
				return distrio_error
					(Distrio::E_NOTSUPPORTED, Distrio::L_NORMAL, MODULE_ID, "reset gpio failed");

			update_timestamp ();
			val = 0;
			std::cout << "reset" << std::endl;
			return distrio_success ();
		}

		::Distrio::Error *get (::CORBA::Long_out value) {
			value = val;
			std::cout << "get" << std::endl;
			return distrio_success ();
		}
	private:
		gpio_pin p;
};


ACE_TMAIN (int argc, ACE_TCHAR *argv[])
{
	int ret = 0, num = 0, i = 0;
	std::list<GPIO *> io_list;
	dictionary *d = _iniparser_load (GPIO_CONFIG);

	if (!d) {
		err ("load inifile failed\n");
		return -EINVAL;
	}

	num = _iniparser_getnsec (d);

	if (!num) {
		err ("no gpios configured, check config\n");
		return -ENOMEM;
	}

	if (init_corba (argc, argv))
		return -EINVAL;

	if (run_orb ())
		return -EINVAL;

	for (i = 0; i < num; i++) {
		::Distrio::Direction dir;
		char *name = _iniparser_getsecname (d, i);
		char *direction = _iniparser_getstring (d, "direction", "unknown");
		int value = _iniparser_getint (d, "value", -1);

		if (strcmp (direction, "in") == 0)
			dir = ::Distrio::INPUT;
		else
			dir = ::Distrio::OUTPUT;

		GPIO *g = new GPIO (std::string (name), value, dir);

		if (g->id () == -1) {
			err ("create gpio object failed - hw error?\n");
			delete g;
			continue;
		}

		if (register_digital (g)) {
			err ("register gpio object at the manager failed\n");
			delete g;
			continue;
		}
		std::cout << "registered gpio " << name <<" with id: " << g->id () << std::endl;
		io_list.push_back (g);
	}

	_iniparser_freedict (d);

	join_orb ();

out:
	/* io_list.erase (); */
	return ret;
}
