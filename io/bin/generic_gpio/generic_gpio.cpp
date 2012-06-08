#include <distrio_helper.h>
#include <distrio_error.h>

#include <distrio_io.h>

#include <ace/Task.h>

#include <iostream>

class Io_manager : public  ACE_Task < ACE_MT_SYNCH > {
	public:
		Io_manager () { }
		~Io_manager () { }

	private:
		int svc (void) {
			while (1) {
				/** TODO: implement some cyclic gpio stuff */
				sleep (1);
			}
		}
};

class My_digital : public Distrio_Digital_i {
	public:
		My_digital (std::string io_name) : Distrio_Digital_i (io_name) { }

		::Distrio::Error *set () {
			std::cout << "set" << std::endl;
			return distrio_success ();
		}

		::Distrio::Error *reset () {
			std::cout << "reset" << std::endl;
			return distrio_success ();
		}
};

ACE_TMAIN (int argc, ACE_TCHAR *argv[])
{
	int ret = 0;
	My_digital *digital;
	/* Io_manager manager; */

	if (init_corba (argc, argv))
		return -EINVAL;

	if (run_orb ())
		return -EINVAL;

	digital = new My_digital (std::string ("pin huhu"));

	if (register_digital (digital)) {
		ret = -EINVAL;
		goto out;
	}

	std::cout << "registered id: " << digital->id () << std::endl;

	/* TODO: activate if cyclic stuff is needed
	manager.activate ();
	manager.wait ();
	*/

	join_orb ();

out:
	free (digital);
	return ret;
}
