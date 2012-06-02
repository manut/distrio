// -*- C++ -*-
// $Id$

/**
 * Code generated by the The ACE ORB (TAO) IDL Compiler v2.1.2
 * TAO and the TAO IDL Compiler have been developed by:
 *       Center for Distributed Object Computing
 *       Washington University
 *       St. Louis, MO
 *       USA
 *       http://www.cs.wustl.edu/~schmidt/doc-center.html
 * and
 *       Distributed Object Computing Laboratory
 *       University of California at Irvine
 *       Irvine, CA
 *       USA
 * and
 *       Institute for Software Integrated Systems
 *       Vanderbilt University
 *       Nashville, TN
 *       USA
 *       http://www.isis.vanderbilt.edu/
 *
 * Information about TAO is available at:
 *     http://www.cs.wustl.edu/~schmidt/TAO.html
 **/

// TAO_IDL - Generated from
// be/be_codegen.cpp:1673

#include "distrio_managerI.h"

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
  // Add your implementation here
}

::Distrio::Error * Distrio_Manager_i::analog (
  ::Distrio::Analog_list_out io_list)
{
  // Add your implementation here
}

::Distrio::Error * Distrio_Manager_i::device (
  ::Distrio::Device_list_out dev_list)
{
  // Add your implementation here
}

::Distrio::Error * Distrio_Manager_i::register_io_digital (
  ::Distrio::Analog_ptr io_ana)
{
  // Add your implementation here
}

::Distrio::Error * Distrio_Manager_i::register_io_analog (
  ::Distrio::Digital_ptr io_dig)
{
  // Add your implementation here
}

::Distrio::Error * Distrio_Manager_i::register_io_device (
  ::Distrio::Device_ptr io_dev)
{
  // Add your implementation here
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
	CORBA::Object_var distrio_manager_obj, tmp;
	PortableServer::POA_var poa;
	PortableServer::POAManager_var poa_mgr;
	CosNaming::NamingContext_var nc;
	CosNaming::Name name;

	Distrio_Manager_i *distrio_manager;
	PortableServer::ObjectId_var distrio_manager_oid;

	distrio_manager = new Distrio_Manager_i ();

	try {
		orb = CORBA::ORB_init (argc, argv);
		tmp = orb->resolve_initial_references ("RootPOA");
		poa = PortableServer::POA::_narrow (tmp.in ());
		distrio_manager_oid = poa->activate_object (distrio_manager);
		distrio_manager_obj = distrio_manager->_this ();

		CORBA::String_var ior (orb->object_to_string (distrio_manager_obj.in ()));
		tmp = orb->resolve_initial_references ("NameService");
		name.length (2);
		name[0].id = CORBA::string_dup ("distrio");
		name[1].id = CORBA::string_dup ("manager");
		nc = CosNaming::NamingContext::_narrow (tmp.in ());
		nc->rebind (name, distrio_manager_obj.in ());

		poa_mgr = poa->the_POAManager ();
		poa_mgr->activate ();

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
