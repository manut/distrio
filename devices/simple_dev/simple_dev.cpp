#include <distrio_helper.h>
#include <distrio_error.h>

#include <distrio_ioI.h>

#include <iostream>

class My_device : public Distrio_Device_i {
	public:
		My_device (std::string name) { dev_name = name; }
		~My_device () { }

		::CORBA::Long id (void) {
			return dev_id;
		}
		void id (::CORBA::Long id) {
			dev_id = id;
		}
		::Distrio::Error *name (::CORBA::String_out _name) {
			_name = ::CORBA::string_dup (dev_name.c_str ());
			return distrio_success ();
		}
		::Distrio::Digital_list_var digitals;
	private:
		std::string dev_name;
		::CORBA::Long dev_id;
};

ACE_TMAIN (int argc, ACE_TCHAR *argv[])
{
	int ret = 0;
	My_device *dev;
	Distrio::Digital_ptr digital_io;

	if (init_corba (argc, argv))
		return -EINVAL;

	if (run_orb ())
		return -EINVAL;

	dev = new My_device ("simple_dev");

	if (register_device (dev)) {
		ret = -EINVAL;
		goto out;
	}

	std::cout << "registered id: " << dev->id () << std::endl;

	get_digital_list (&dev->digitals);
	lookup_digital ("pin huhu", dev->digitals, &digital_io);

	while (1)
	{
		try {
			digital_io->set ();
			sleep (1);
			digital_io->reset ();
			sleep (1);
		} catch (::CORBA::Exception *ex) {
			std::cerr << "sth went wrong " << ex << std::endl;
		}
	}

out:
	free (dev);
	return ret;
}
