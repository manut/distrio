#include <distrio_helper.h>
#include <distrio_error.h>

#include <distrio_ioI.h>

#include <iostream>

class My_digital : public Distrio_Digital_i {
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
	My_digital *digital;

	if (init_corba (argc, argv))
		return -EINVAL;

	if (run_orb ())
		return -EINVAL;

	digital = new My_digital ();

	if (register_digital ("pin huhu", digital)) {
		ret = -EINVAL;
		goto out;
	}

	std::cout << "registered id: " << digital->id () << std::endl;

out:
	free (digital);
	return ret;
}
