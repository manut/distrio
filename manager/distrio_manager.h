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
// be/be_codegen.cpp:1616

#ifndef DISTRIO_MANAGERI_Z5WXNW_H_
#define DISTRIO_MANAGERI_Z5WXNW_H_

#include "distrio_managerS.h"
#include "manager_base.h"

#if !defined (ACE_LACKS_PRAGMA_ONCE)
#pragma once
#endif /* ACE_LACKS_PRAGMA_ONCE */

class  Distrio_Manager_i
  : public virtual POA_Distrio::Manager, Distrio_manager_base
{
public:
  // Constructor
  Distrio_Manager_i (void);

  // Destructor
  virtual ~Distrio_Manager_i (void);

  virtual
  ::Distrio::Error * digital (
    ::Distrio::Digital_list_out io_list);

  virtual
  ::Distrio::Error * analog (
    ::Distrio::Analog_list_out io_list);

  virtual
  ::Distrio::Error * device (
    ::Distrio::Device_list_out dev_list);

  virtual
  ::Distrio::Error * register_io_digital (
    ::Distrio::Digital_ptr & io_dig);

  virtual
  ::Distrio::Error * register_io_analog (
    ::Distrio::Analog_ptr & io_ana);

  virtual
  ::Distrio::Error * register_io_device (
    ::Distrio::Device_ptr & io_dev);

  virtual
  ::Distrio::Error * unregister_io_digital (
    ::Distrio::Digital_ptr io_dig);

  virtual
  ::Distrio::Error * unregister_io_analog (
    ::Distrio::Analog_ptr io_ana);

  virtual
  ::Distrio::Error * unregister_io_device (
    ::Distrio::Device_ptr io_dev);

  virtual
  void log_error (
    const ::Distrio::Error & error);
};


#endif /* DISTRIO_MANAGERI_H_  */
