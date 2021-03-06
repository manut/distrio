/**
 * @author Manuel Traut <manut@mecka.net>
 * @licence GPLv2
 */

#include <iostream>
#include "distrio_helper.h"

static pthread_t orb_thread;

int init_corba (int argc, char **argv)
{
	int ret = 0;
	CORBA::Object_var obj, root_poa, naming_service, manager_obj;
	CosNaming::Name name;

	try {
		ref.orb = CORBA::ORB_init (argc, argv);
		root_poa = ref.orb->resolve_initial_references ("RootPOA");
		ref.poa = PortableServer::POA::_narrow (root_poa.in ());

		naming_service = ref.orb->resolve_initial_references ("NameService");
		if (CORBA::is_nil (naming_service)) {
			std::cerr << "can't resolve NameService" << std::endl;
			ret = -EINVAL;
			goto out;
		}
		ref.nc = CosNaming::NamingContext::_narrow (naming_service.in ());
		if (CORBA::is_nil (ref.nc)) {
			std::cerr << "resolved invalid NameService object" << std::endl;
			ret = -EINVAL;
			goto out;
		}
		name.length (1);
		name[0].id = CORBA::string_dup ("distrio_manager");
		name[0].kind = CORBA::string_dup ("");
		manager_obj = ref.nc->resolve (name);
		if (CORBA::is_nil (manager_obj)) {
			std::cerr << "can't resolve distrio_manager @naming service" << std::endl;
			ret = -EINVAL;
			goto out;
		}
		ref.manager = Distrio::Manager::_narrow (manager_obj);
		if (CORBA::is_nil (ref.manager)) {
			std::cerr << "resolved invalid distrio_manager object" << std::endl;
			ret = -EINVAL;
			goto out;
		}
	} catch (CORBA::Exception &e) {
		std::cerr << "CORBA initialization failed: " << e << std::endl;
		ret = -EINVAL;
		goto out;
	}

	ref.init = ORB_INIT;

out:
	return ret;
}

void *orb_runner (void *args)
{
	try {
		ref.poa_mgr = ref.poa->the_POAManager ();
		ref.poa_mgr->activate ();
		ref.orb->run ();
	} catch (CORBA::Exception &e) {
		std::cerr << "run CORBA orb failed: " << e << std::endl;
	}
}

int run_orb ()
{
	if (ref.init != ORB_INIT) {
		std::cerr << "corba not initialized or orb already running" << std::endl;
		return -1;
	}

	if (pthread_create (&orb_thread, NULL, orb_runner, NULL)) {
		std::cerr << "create thread for corba orb failed" << std::endl;
		return -1;
	}

	ref.init = ORB_RUNNING;

	return 0;
}

int destroy_orb ()
{
	if (ref.init != ORB_RUNNING) {
		std::cerr << "corba not initialized or orb not running" << std::endl;
		return -1;
	}

	try {
		ref.orb->destroy ();
		ref.init = ORB_INIT;
	} catch (CORBA::Exception &e) {
		std::cerr << "destroy CORBA orb failed: " << e << std::endl;

		return -1;
	}

	return 0;
}

int join_orb ()
{
	return pthread_join (orb_thread, NULL);
}

int register_digital (Distrio_Digital_i *digital)
{
	CosNaming::Name name;
	CORBA::Object_var obj, manager_obj;
	PortableServer::ObjectId_var oid;
	Distrio::Digital_ptr ptr;
	Distrio::Error *e;

	if (ref.init != ORB_RUNNING) {
		std::cerr << "corba not initialized" << std::endl;
		return -1;
	}

	try {
		oid = ref.poa->activate_object (digital);
		obj = digital->_this ();
		name.length (1);
		e = digital->name (name[0].id);
		free (e);
		name[0].kind = CORBA::string_dup ("digital_io");
		ref.nc->rebind (name, obj.in ());
	} catch (CORBA::Exception &exc) {
		std::cerr << "CORBA bind digital io at naming service failed: "
			<< exc << std::endl;
		return -1;
	}

	try {
		ptr = Distrio::Digital::_narrow (obj);
		e = ref.manager->register_io_digital (ptr);
		std::cout << e->description << std::endl;
		free (e);
	} catch (CORBA::Exception &_e) {
		std::cerr << "CORBA register digital io at distrio manager failed: "
			<< _e << std::endl;
		return -1;
	}

	return 0;
}

int register_analog (Distrio_Analog_i *analog)
{
	CosNaming::Name name;
	CORBA::Object_var obj, manager_obj;
	PortableServer::ObjectId_var oid;
	Distrio::Analog_ptr ptr;
	Distrio::Error *e;

	if (ref.init != ORB_RUNNING) {
		std::cerr << "corba not initialized" << std::endl;
		return -1;
	}

	try {
		oid = ref.poa->activate_object (analog);
		obj = analog->_this ();
		name.length (1);
		e = analog->name (name[0].id);
		free (e);
		name[0].kind = CORBA::string_dup ("analog_io");
		ref.nc->rebind (name, obj.in ());
	} catch (CORBA::Exception &exc) {
		std::cerr << "CORBA bind analog io at naming service failed: "
			<< exc << std::endl;
		return -1;
	}

	try {
		ptr = Distrio::Analog::_narrow (obj);
		e = ref.manager->register_io_analog (ptr);
		std::cout << e->description << std::endl;
		free (e);
	} catch (CORBA::Exception &_e) {
		std::cerr << "CORBA register analog io at distrio manager failed: "
			<< _e << std::endl;
		return -1;
	}

	return 0;
}

int register_device (Distrio_Device_i *dev)
{
	CosNaming::Name name;
	CORBA::Object_var obj, manager_obj;
	PortableServer::ObjectId_var oid;
	Distrio::Device_ptr ptr;
	Distrio::Error *e;

	if (ref.init != ORB_RUNNING) {
		std::cerr << "corba not initialized" << std::endl;
		return -1;
	}

	try {
		oid = ref.poa->activate_object (dev);
		obj = dev->_this ();
		name.length (1);
		e = dev->name (name[0].id);
		free (e);
		name[0].kind = CORBA::string_dup ("devices");
		ref.nc->rebind (name, obj.in ());
	} catch (CORBA::Exception &e) {
		std::cerr << "CORBA bind device at naming service failed: "
			<< e << std::endl;
		return -1;
	}

	try {
		ptr = Distrio::Device::_narrow (obj);
		e = ref.manager->register_io_device (ptr);
		std::cout << e->description << std::endl;
		free (e);
	} catch (CORBA::Exception &_e) {
		std::cerr << "CORBA register device at distrio manager failed: "
			<< _e << std::endl;
		return -1;
	}

	return 0;
}

void get_device_list (Distrio::Device_list_var *dev_list)
{
	CORBA::Object_var obj;
	Distrio::Error *e;

	if (ref.init != ORB_RUNNING) {
		std::cerr << "corba not initialized" << std::endl;
		return;
	}

	try {
		e = ref.manager->device (*dev_list);
		free (e);
	} catch (CORBA::Exception &_e) {
		std::cerr << "CORBA get digital list failed: "
			<< _e << std::endl;
	}
}

void get_analog_list (Distrio::Analog_list_var *ana_list)
{
	CORBA::Object_var obj;
	Distrio::Error *e;

	if (ref.init != ORB_RUNNING) {
		std::cerr << "corba not initialized" << std::endl;
		return;
	}

	try {
		e = ref.manager->analog (*ana_list);
		free (e);
	} catch (CORBA::Exception &_e) {
		std::cerr << "CORBA get digital list failed: "
			<< _e << std::endl;
	}
}

void get_digital_list (Distrio::Digital_list_var *dig_list)
{
	CORBA::Object_var obj;
	Distrio::Error *e;

	if (ref.init != ORB_RUNNING) {
		std::cerr << "corba not initialized" << std::endl;
		return;
	}

	try {
		e = ref.manager->digital (*dig_list);
		free (e);
	} catch (CORBA::Exception &_e) {
		std::cerr << "CORBA get digital list failed: "
			<< _e << std::endl;
	}
}

int lookup_analog (std::string _name, Distrio::Analog_list_var ana_list,
	Distrio::Analog **ptr)
{
	if (ref.init != ORB_RUNNING) {
		std::cerr << "corba not initialized" << std::endl;
		return -EINVAL;
	}

	for (unsigned int i = 0; i < ana_list->length (); i++) {
		::CORBA::String_var name;
		Distrio::Error *e;
		try {
			e = ana_list[i]->name (name);
			if (!::CORBA::is_nil (e))
				free (e);
			if (! _name.compare (name.in ())) {
				*ptr = ana_list[i];
				return 0;
			}
		} catch (::CORBA::Exception &ex) {
			std::cerr << "get name of analog io failed\n" << ex << std::cerr;
		}
	}
	return -EHOSTDOWN;
}

int lookup_digital (std::string _name, Distrio::Digital_list_var dig_list,
	Distrio::Digital **ptr)
{
	if (ref.init != ORB_RUNNING) {
		std::cerr << "corba not initialized" << std::endl;
		return -EINVAL;
	}

	for (unsigned int i = 0; i < dig_list->length (); i++) {
		::CORBA::String_var name;
		Distrio::Error *e;
		try {
			e = dig_list[i]->name (name);
			if (!::CORBA::is_nil (e))
				free (e);
			if (! _name.compare (name.in ())) {
				*ptr = dig_list[i];
				return 0;
			}
		} catch (::CORBA::Exception &ex) {
			std::cerr << "get name of digital io failed\n" << ex << std::cerr;
		}
	}
	return -EHOSTDOWN;
}

int lookup_device (std::string _name, Distrio::Device_list_var dev_list,
	Distrio::Device **ptr)
{
	if (ref.init != ORB_RUNNING) {
		std::cerr << "corba not initialized" << std::endl;
		return -EINVAL;
	}

	for (unsigned int i = 0; i < dev_list->length (); i++) {
		::CORBA::String_var name;
		Distrio::Error *e;
		try {
			e = dev_list[i]->name (name);
			if (!::CORBA::is_nil (e))
				free (e);
			if (! _name.compare (name.in ())) {
				*ptr = dev_list[i];
				return 0;
			}
		} catch (::CORBA::Exception &ex) {
			std::cerr << "get name of device failed\n" << ex << std::cerr;
		}
	}
	return -EHOSTDOWN;
}
