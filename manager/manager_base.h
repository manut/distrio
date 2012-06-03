/**
 * used by interface implementation to store private attributes
 *
 * @author Manuel Traut <manut@mecka.net>
 * @licence GPLv2
 */

#include <distrio_ioC.h>

class Distrio_manager_base {
	public:
		Distrio_manager_base () {id = 0;}
		~Distrio_manager_base () {}
	protected:
		long id;
		Distrio::Device_list device_list;
		Distrio::Analog_list analog_list;
		Distrio::Digital_list digital_list;
		/* TODO: locking */
		long new_id () { return id++; }
};
