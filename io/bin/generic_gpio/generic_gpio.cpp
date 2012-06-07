#include <distrio_helper.h>
#include <distrio_error.h>

#include <distrio_ioI.h>

#include <ace/Task.h>

#include <iostream>

class Io_manager : public  ACE_Task < ACE_MT_SYNCH > {
	public:
		Io_manager () { }
		~Io_manager () { }

	private:
		int svc (void) {
			while (1) {
				std::cout << "check inputs" << std::endl;
				sleep (1);
			}
		}
};

class My_digital : public Distrio_Digital_i {
	public:
		My_digital (std::string _name) { my_name = _name; }
		~My_digital () { };

		::CORBA::Long id (void) { return my_id; }

		::Distrio::Error *name (::CORBA::String_out _name) {
			_name = CORBA::string_dup (my_name.c_str ());
			return distrio_success ();
		}

		::Distrio::Error *set () {
			std::cout << "set" << std::endl;
			return distrio_success ();
		}

		::Distrio::Error *reset () {
			std::cout << "reset" << std::endl;
			return distrio_success ();
		}

		void id (::CORBA::Long id) { my_id = id; }

	private:
		std::string my_name;
		::CORBA::Long my_id;
};

ACE_TMAIN (int argc, ACE_TCHAR *argv[])
{
	int ret = 0;
	My_digital *digital;
	Io_manager manager;

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

	manager.activate ();
	manager.wait ();

out:
	free (digital);
	return ret;
}
