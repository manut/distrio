/**
 * distrio manager implementation
 *
 *  - instances a manager object
 *  - registers the manager object at the NamingService
 *
 * @author Manuel Traut <manut@mecka.net>
 * @licence GPLv2
 */

#include "distrio_manager.h"

#include <distrio_error.h>

#include <orbsvcs/CosNamingC.h>

#include <iostream>

// Implementation skeleton constructor
Distrio_Manager_i::Distrio_Manager_i (void)
{
}

// Implementation skeleton destructor
Distrio_Manager_i::~Distrio_Manager_i (void)
{
}

::Distrio::Error * Distrio_Manager_i::digital (
  ::Distrio::Digital_list_out io_list)
{
	io_list = new ::Distrio::Digital_list (digital_list);
	return distrio_success ();
}

::Distrio::Error * Distrio_Manager_i::analog (
  ::Distrio::Analog_list_out io_list)
{
	io_list = new ::Distrio::Analog_list (analog_list);
	return distrio_success ();
}

::Distrio::Error * Distrio_Manager_i::device (
  ::Distrio::Device_list_out dev_list)
{
	dev_list = new ::Distrio::Device_list (device_list);
	return distrio_success ();
}

/* TODO: think about locking!!! */

::Distrio::Error * Distrio_Manager_i::register_io_digital (
  ::Distrio::Digital_ptr & io_digi)
{
	Distrio::Digital_var dig;

	try {
		dig = Distrio::Digital::_narrow (io_digi);
		dig->id (new_id ());
	} catch (::CORBA::Exception &exc) {
		std::cerr << "register digital io failed" << std::endl;
	}
	digital_list.length (digital_list.length () + 1);
	digital_list [digital_list.length () - 1] = dig;

	return distrio_success ();
}

::Distrio::Error * Distrio_Manager_i::register_io_analog (
  ::Distrio::Analog_ptr & io_ana)
{
	Distrio::Analog_var analog;

	try {
		analog = Distrio::Analog::_narrow (io_ana);
		analog->id (new_id ());
	} catch (::CORBA::Exception &exc) {
		std::cerr << "register analog io failed" << std::endl;
	}
	analog_list.length (analog_list.length () + 1);
	analog_list [analog_list.length () - 1] = analog;

	return distrio_success ();
}

::Distrio::Error * Distrio_Manager_i::register_io_device (
  ::Distrio::Device_ptr & io_dev)
{
	Distrio::Device_var dev;

	try {
		dev = Distrio::Device::_narrow (io_dev);
		dev->id (new_id ());
	} catch (::CORBA::Exception &exc) {
		std::cerr << "register device failed" << std::endl;
	}
	device_list.length (device_list.length () + 1);
	device_list [device_list.length () - 1] = dev;

	return distrio_success ();
}

::Distrio::Error * Distrio_Manager_i::unregister_io_digital (
  ::Distrio::Digital_ptr io_dig)
{
  // Add your implementation here
}

::Distrio::Error * Distrio_Manager_i::unregister_io_analog (
  ::Distrio::Analog_ptr io_ana)
{
  // Add your implementation here
}

::Distrio::Error * Distrio_Manager_i::unregister_io_device (
  ::Distrio::Device_ptr io_dev)
{
  // Add your implementation here
}

void Distrio_Manager_i::log_error (
  const ::Distrio::Error & error)
{
  // Add your implementation here
}

ACE_TMAIN (int argc, ACE_TCHAR *argv[])
{
	std::cout << __FILE__ << " build " << __DATE__ << " " << __TIME__ <<std::endl;

	int ret = 0;
	CORBA::ORB_var orb;
	CORBA::Object_var distrio_manager_obj, root_poa, naming_service;
	PortableServer::POA_var poa;
	PortableServer::POAManager_var poa_mgr;
	CosNaming::NamingContext_var nc;
	CosNaming::Name name;

	Distrio_Manager_i *distrio_manager;
	PortableServer::ObjectId_var distrio_manager_oid;

	distrio_manager = new Distrio_Manager_i ();

	try {
		std::cout << "initialize CORBA orb" << std::endl;
		orb = CORBA::ORB_init (argc, argv);
		root_poa = orb->resolve_initial_references ("RootPOA");
		poa = PortableServer::POA::_narrow (root_poa.in ());
		distrio_manager_oid = poa->activate_object (distrio_manager);
		distrio_manager_obj = distrio_manager->_this ();

		std::cout << "get context of NameService" << std::endl;
		naming_service = orb->resolve_initial_references ("NameService");
		if (CORBA::is_nil (naming_service)) {
			std::cerr << "can't resolve NameService" << std::endl;
			ret = -EINVAL;
			goto out;
		}
		nc = CosNaming::NamingContext::_narrow (naming_service.in ());
		if (CORBA::is_nil (nc)) {
			std::cerr << "resolved invalid NameService object" << std::endl;
			ret = -EINVAL;
			goto out;
		}

		std::cout << "bind manager object at NameService" << std::endl;
		/* TODO: find out how to build a tree @ the nameservice "distrio/manager" */
		name.length (1);
		name[0].id = CORBA::string_dup ("distrio_manager");
		nc->rebind (name, distrio_manager_obj.in ());

		std::cout << "activate POA Manager" << std::endl;
		poa_mgr = poa->the_POAManager ();
		poa_mgr->activate ();

		std::cout << "distrio_manager ready" << std::endl;
		orb->run ();
		orb->destroy ();
	} catch (CORBA::SystemException &e) {
		std::cerr << "CORBA initialization failed: " << e << std::endl;
		ret = -EINVAL;
		goto out;
	} catch(CORBA::Exception &e) {
		std::cerr << "CORBA initialization failed: " << e << std::endl;
		ret = -EINVAL;
		goto out;
	}

out:
	free (distrio_manager);
	return ret;
}
