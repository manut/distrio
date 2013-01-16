#include <distrio_helper.h>
#include <distrio_error.h>
#include <distrio_io.h>

#include <ace/Task.h>

#include <iostream>
#include <map>
#include <string>

#include <gpio.h>
#include <poll.h>

#include "ini.h"

#define MODULE_ID 1212

static void err (const char *s)
{
	fprintf (stderr, s);
}

class GPIO : public Distrio_Digital_i {
	public:
		GPIO (std::string name, ::Distrio::Direction dir, gpio_pin _p) :
			Distrio_Digital_i (name, dir) { p = _p; }

		int update_input (void) {
			gpio_value v;
			int ret = gpio_get_value (&p, &v);

			if (ret) {
				std::cerr << "update gpio " << io_name << " failed: " << ret << std::endl;
				return -1;
			}

			update_timestamp ();

			if (val)
				raise ();
			else
				fall ();
		}

		::Distrio::Error *set () {

			if (gpio_set_value (&p, GPIO_HIGH))
				return distrio_error (Distrio::E_NOTSUPPORTED,
					Distrio::L_NORMAL,
					MODULE_ID,
					"set gpio failed");

			update_timestamp ();
			val = 1;
			std::cout << "set" << std::endl;
			return distrio_success ();
			
		}

		::Distrio::Error *reset () {

			if (gpio_set_value (&p, GPIO_LOW))
				return distrio_error (Distrio::E_NOTSUPPORTED,
						Distrio::L_NORMAL,
						MODULE_ID,
						"reset gpio failed");

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

class Input_observer : public  ACE_Task < ACE_MT_SYNCH > {
	public:
		Input_observer (std::map <int, GPIO *> _input_list) {
			input_list = _input_list;
		}
		~Input_observer () { }
	private:
		std::map <int, GPIO *> input_list;
		int svc (void) {
			struct pollfd *fds = (struct pollfd *)
				malloc (input_list.size () * sizeof (struct pollfd));
			int fd_cnt = 0;

			for (std::map <int, GPIO *> :: iterator it = input_list.begin ();
				it != input_list.end ();
				it++)
			{
				fds[fd_cnt].fd = it->first;
				fds[fd_cnt].events = POLLPRI | POLLERR;
			}

			while (1) {
				int pos = 0;
				int ret = poll (fds, input_list.size (), -1);

				while (ret > 0) {
					if (fds [pos].revents) {
						if (fds [pos].revents & POLLPRI)
							input_list[pos]->update_input ();
						ret--;
					}
					pos++;
					if (pos > input_list.size ()) {
						std::cerr << "fatal error in poll checker" << std::endl;
						abort ();
					}
				}
			}
		}
};

ACE_TMAIN (int argc, ACE_TCHAR *argv[])
{
	int ret = 0, num = 0, i = 0;
	std::map<int, GPIO *> input_list;
	std::list<GPIO *> output_list;
	Input_observer *obs;
	dictionary *d;

	d = _iniparser_load (GPIO_CONFIG);

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
		GPIO *g;
		gpio_pin p;
		::Distrio::Direction dir;
		char tmp [255];
		int id;
		int rising = 0, falling = 0;
		int ret = -1;
		char *direction;
		char *name = _iniparser_getsecname (d, i);

		sprintf (tmp, "%s:id", name);
		id = _iniparser_getint (d, tmp, -1);
		sprintf (tmp, "%s:direction", name);
		direction = _iniparser_getstring (d, tmp, (char *) "unknown");

		if (strcmp (direction, "in") == 0)
			dir = ::Distrio::INPUT;
		else
			dir = ::Distrio::OUTPUT;

		std::cout << " new gpio: " << id << ": " << name << std::endl;

		if (dir == ::Distrio::OUTPUT)
			ret = gpio_open_dir (&p, id, GPIO_OUT);
		if (dir == ::Distrio::INPUT)
			ret = gpio_open_dir (&p, id, GPIO_IN);

		if (ret) {
			std::cerr << "open gpio: " << id << ": " << name << "failed" << std::endl;
			continue;
		}

		if (dir == ::Distrio::INPUT) {
			sprintf (tmp, "%s:rising", name);
			rising = _iniparser_getint (d, tmp, -1);
			sprintf (tmp, "%s:falling", name);
			falling = _iniparser_getint (d, tmp, -1);

			if (((rising == -1) && (falling == -1)) || (!rising && !falling)) {
				std::cout << "gpio: " << id << ": " << name;
				std::cout << "no edge defined.";
				std::cout << "events will be emitted on rising and falling edge";
				ret = gpio_enable_irq (&p, GPIO_BOTH);
			}
			else if (rising && falling)
				ret = gpio_enable_irq (&p, GPIO_BOTH);
			else if (rising)
				ret = gpio_enable_irq (&p, GPIO_RISING);
			else if (falling)
				ret = gpio_enable_irq (&p, GPIO_FALLING);
			else {
				std::cerr << "gpio: " << id << ": " << name;
				std::cerr << "no edge defined - gpio will be skipped." << std::endl;
				continue;
			}

			if (ret) {
				std::cerr << "gpio: " << id << ": " << name;
				std::cerr << "enable irq failed - gpio will be skipped." << std::endl;
				continue;
			}
		}

		g = new GPIO (std::string (name), dir, p);

		if (register_digital (g)) {
			err ("register gpio object at the manager failed\n");
			delete g;
			continue;
		}

		if (dir == ::Distrio::INPUT) {
			int fd = gpio_get_fd (&p);
			input_list[fd] = g;
		} else
			output_list.push_back (g);

		std::cout << "registered gpio " << name <<" with id: " << g->id () << std::endl;
	}

	_iniparser_freedict (d);

	obs = new Input_observer (input_list);

	join_orb ();

out:
	/* input_list.erase (); */
	/* output_list.erase (); */
	return ret;
}
