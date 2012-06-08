#include <distrio_helper.h>
#include <distrio_error.h>

#include <distrio_io.h>

#include <ace/Task.h>

#include <iostream>

class My_digital : public Distrio_Digital_i {
	public:
		My_digital (std::string io_name) : Distrio_Digital_i (io_name) { }

		::Distrio::Error *set () {
			update_timestamp ();
			val = 1;
			std::cout << "set" << std::endl;
			return distrio_success ();
		}

		::Distrio::Error *reset () {
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
};

class Io_simulator : public  ACE_Task < ACE_MT_SYNCH > {
	public:
		Io_simulator (My_digital *_io) { io = _io; }
		~Io_simulator () { }

	private:
		My_digital *io;

		int svc (void) {
			while (1) {
				io->raise ();
				sleep (3);
				io->fall ();
				sleep (5);
			}
		}
};

ACE_TMAIN (int argc, ACE_TCHAR *argv[])
{
	int ret = 0;
	My_digital *digital;
	Io_simulator *sim;

	if (init_corba (argc, argv))
		return -EINVAL;

	if (run_orb ())
		return -EINVAL;

	digital = new My_digital (std::string ("pin huhu"));

	if (register_digital (digital)) {
		ret = -EINVAL;
		goto out;
	}

	sim = new Io_simulator (digital);

	std::cout << "registered id: " << digital->id () << std::endl;

	sim->activate ();
	join_orb ();

out:
	free (digital);
	return ret;
}
