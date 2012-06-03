/**
 * @author Manuel Traut <manut@mecka.net>
 * @licence GPLv2
 */

#include <iostream>

#include "distrio_helper.h"

int init_corba (int argc, char **argv)
{
	int ret = 0;
	CORBA::Object_var obj, root_poa, naming_service;

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
	} catch (CORBA::Exception &e) {
		std::cerr << "CORBA initialization failed: " << e << std::endl;
		ret = -EINVAL;
		goto out;
	}

	ref.init = 1;

out:
	return ret;
}

int register_digital (char *_name, Distrio_Digital_i *digital)
{
	CosNaming::Name name;
	CORBA::Object_var obj;
	PortableServer::ObjectId_var oid;

	if (!ref.init) {
		std::cerr << "corba not initialized" << std::endl;
		return -1;
	}

	try {
		oid = ref.poa->activate_object (digital);
		obj = digital->_this ();
		name.length (1);
		name[0].id = CORBA::string_dup (_name);
		name[0].kind = CORBA::string_dup ("digital_io");
		ref.nc->rebind (name, obj.in ());
	} catch (CORBA::Exception &e) {
		std::cerr << "CORBA initialization failed: " << e << std::endl;
		return -1;
	}

	return 0;
}

int run_orb ()
{
	if (!ref.init) {
		std::cerr << "corba not initialized" << std::endl;
		return -1;
	}

	try {
		ref.poa_mgr = ref.poa->the_POAManager ();
		ref.poa_mgr->activate ();
		ref.orb->run ();
		ref.orb->destroy ();
	} catch (CORBA::Exception &e) {
		std::cerr << "CORBA initialization failed: " << e << std::endl;
		return -1;
	}

	return 0;
}
