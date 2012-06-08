#include <distrio_helper.h>
#include <distrio_error.h>

#include <distrio_io.h>

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
		::Distrio::Error *execute (::Distrio::Dev_function &func) {
			switch (func.id) {
				case ::Distrio::DEV_START:
					std::cout << "start simple_dev" << std::endl;
					huhu_pin->set ();
					return distrio_success ();
				case ::Distrio::DEV_STOP:
					std::cout << "stop simple_dev" << std::endl;
					huhu_pin->reset ();
					return distrio_success ();
			}
			return distrio_error (::Distrio::E_NOTSUPPORTED, ::Distrio::L_NORMAL,
				dev_id, "function not implemented");
		}
		::Distrio::Error *functions (::Distrio::Dev_function_list_out fl) {
			fl = new ::Distrio::Dev_function_list (function_list);
			return distrio_success ();
		}
		::Distrio::Error *callback_digital (::Distrio::Digital_ptr io_dig)
		{
			std::cout << "digital callback: " << io_dig->id () << std::endl;
			return distrio_success ();
		}
		::Distrio::Digital_list_var digitals;
		::Distrio::Dev_function_list function_list;
		::Distrio::Digital_ptr huhu_pin;
	private:
		std::string dev_name;
		::CORBA::Long dev_id;
};

ACE_TMAIN (int argc, ACE_TCHAR *argv[])
{
	int ret = 0;
	My_device *dev;

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
	if (lookup_digital ("pin huhu", dev->digitals, &(dev->huhu_pin))) {
		std::cerr << "unable to get requested io" << std::endl;
		goto out;
	}

	try {
		dev->huhu_pin->register_callback ( (Distrio::Device_ptr) dev,
			Distrio::TRIGGER_FALLING_EDGE);
	} catch (::CORBA::Exception &ex) {
		std::cerr << "register cb failed" << std::endl;
	}

	dev->function_list.length (2);

	dev->function_list[0].id = ::Distrio::DEV_START;
	dev->function_list[0].description =
		::CORBA::string_dup (std::string ("start simple dev").c_str ());

	dev->function_list[1].id = ::Distrio::DEV_STOP;
	dev->function_list[1].description =
		::CORBA::string_dup (std::string ("stop simple dev").c_str ());

	join_orb ();

out:
	free (dev);
	return ret;
}
