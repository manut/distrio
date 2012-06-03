#include <distrio_helper.h>
#include <distrio_ioI.h>

int main (int argc, char **argv)
{
	int ret = 0;
	Distrio_Digital_i *digital;

	if (init_corba (argc, argv))
		return -EINVAL;

	digital = new Distrio_Digital_i ();

	if (register_digital ("pin huhu", digital)) {
		ret = -EINVAL;
		goto out;
	}

	if (run_orb ())
		ret = -EINVAL;

out:
	free (digital);
	return ret;
}
