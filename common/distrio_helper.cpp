/**
 * @author Manuel Traut <manut@mecka.net>
 * @licence GPLv2
 */

#include <iostream>
#include "distrio_helper.h"

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

Distrio::Digital_ptr lookup_digital (std::string _name)
{
	CORBA::Object_var obj;
	Distrio::Digital_var ret;
	Distrio::Digital_list_var dig_list;
	Distrio::Error *e;

	if (ref.init != ORB_RUNNING) {
		std::cerr << "corba not initialized" << std::endl;
		return NULL;
	}

	try {
		e = ref.manager->digital (dig_list);
		free (e);
	} catch (CORBA::Exception &_e) {
		std::cerr << "CORBA lookup digital io "<< _name <<" failed: "
			<< _e << std::endl;
		return NULL;
	}

	for (unsigned int i = 0; i < dig_list->length (); i++) {
		::CORBA::String_var name;
		Distrio::Error *e;

		e = dig_list[i]->name (name);
		free (e);

		if (! _name.compare (name.in ())) {
			Distrio::Digital_ptr ptr = dig_list[i];
			return ptr;
		}
	}

	return NULL;
}

int register_device (std::string _name, Distrio_Device_i *dev)
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
		name[0].id = CORBA::string_dup (_name.c_str ());
		name[0].kind = CORBA::string_dup ("devices");
		ref.nc->rebind (name, obj.in ());
	} catch (CORBA::Exception &e) {
		std::cerr << "CORBA bind digital io at naming service failed: "
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

pthread_t orb_thread;

void *orb_runner (void *args)
{
	try {
		ref.poa_mgr = ref.poa->the_POAManager ();
		ref.poa_mgr->activate ();
		ref.orb->run ();
		ref.orb->destroy ();
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
