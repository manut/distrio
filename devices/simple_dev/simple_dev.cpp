#include <distrio_helper.h>
#include <distrio_error.h>

#include <distrio_ioI.h>

#include <iostream>

class My_device : public Distrio_Device_i {
	public:
		::CORBA::Long id (void)
		{
			return my_id;
		}
		void id (::CORBA::Long id)
		{
			my_id = id;
		}
	private:
		::CORBA::Long my_id;
};

int main (int argc, char **argv)
{
	int ret = 0;
	My_device *dev;
	Distrio::Digital_ptr digital_io;

	if (init_corba (argc, argv))
		return -EINVAL;

	if (run_orb ())
		return -EINVAL;

	dev = new My_device ();

	if (register_device ("simpele device", dev)) {
		ret = -EINVAL;
		goto out;
	}

	std::cout << "registered id: " << dev->id () << std::endl;

	digital_io = lookup_digital ("pin huhu");

out:
	free (dev);
	return ret;
}
