#include <distrio_helper.h>
#include <distrio_error.h>

#include <distrio_io.h>

#include <iostream>

ACE_TMAIN (int argc, ACE_TCHAR *argv[])
{
	int ret = 0;
	Distrio::Device_list_var devs;
	Distrio::Device *dev;
	Distrio::Dev_function_list_var funcs;
	::CORBA::String_var name;

	if (init_corba (argc, argv))
		return -EINVAL;

	if (run_orb ())
		return -EINVAL;

	get_device_list (&devs);
	if (lookup_device ("simple_dev", devs, &dev)) {
		std::cerr << "unable to get requested device" << std::endl;
		goto out;
	}

	/* TODO: do sth */
	dev->functions(funcs.out ());

	for (unsigned int i = 0; i < funcs->length (); i++)
	{
		std::cout << funcs[i].description << std::endl;
	}

	destroy_orb ();
	join_orb ();

out:
	return ret;
}
