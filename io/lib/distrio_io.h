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

#ifndef DISTRIO_IOI_MYUID7_H_
#define DISTRIO_IOI_MYUID7_H_

#include "distrio_ioS.h"

#if !defined (ACE_LACKS_PRAGMA_ONCE)
#pragma once
#endif /* ACE_LACKS_PRAGMA_ONCE */

class  Distrio_Digital_i
  : public virtual POA_Distrio::Digital
{
public:
  // Constructor
  Distrio_Digital_i (std::string _name);
  Distrio_Digital_i (void);

  // Destructor
  virtual ~Distrio_Digital_i (void);

  virtual
  ::Distrio::Error * name (
    ::CORBA::String_out name);

  virtual
  ::Distrio::Error * set (
    void);

  virtual
  ::Distrio::Error * reset (
    void);

  virtual
  ::Distrio::Error * get (
    ::CORBA::Long_out value);

  virtual
  ::Distrio::Error * register_callback (
    ::Distrio::Device_ptr dev,
    ::Distrio::Digital_trigger trigger);

  virtual
  ::Distrio::Timestamp last_update (
    void);

  virtual
  void last_update (
    const ::Distrio::Timestamp & last_update);

  virtual
  ::CORBA::Long id (
    void);

  virtual
  void id (
    ::CORBA::Long id);

private:
  std::string io_name;
  ::CORBA::Long io_id;
};

class  Distrio_Analog_i
  : public virtual POA_Distrio::Analog
{
public:
  // Constructor
  Distrio_Analog_i (std::string _name);
  Distrio_Analog_i (void);

  // Destructor
  virtual ~Distrio_Analog_i (void);

  virtual
  ::Distrio::Error * name (
    ::CORBA::String_out name);

  virtual
  ::Distrio::Error * min (
    ::CORBA::Long_out min);

  virtual
  ::Distrio::Error * max (
    ::CORBA::Long_out max);

  virtual
  ::Distrio::Error * set (
    ::CORBA::Long value);

  virtual
  ::Distrio::Error * get (
    ::CORBA::Long_out value);

  virtual
  ::Distrio::Error * register_callback (
    ::Distrio::Device_ptr dev,
    const ::Distrio::Analog_trigger & trigger);

  virtual
  ::Distrio::Timestamp last_update (
    void);

  virtual
  void last_update (
    const ::Distrio::Timestamp & last_update);

  virtual
  ::CORBA::Long id (
    void);

  virtual
  void id (
    ::CORBA::Long id);
private:
  std::string io_name;
  ::CORBA::Long io_id;
};

class  Distrio_Device_i
  : public virtual POA_Distrio::Device
{
public:
  // Constructor
  Distrio_Device_i (void);

  // Destructor
  virtual ~Distrio_Device_i (void);

  virtual
  ::Distrio::Error * name (
    ::CORBA::String_out name);

  virtual
  ::Distrio::Error * execute (
    const ::Distrio::Dev_function & func);

  virtual
  ::Distrio::Error * functions (
    ::Distrio::Dev_function_list_out funcs);

  virtual
  ::Distrio::Error * callback_digital (
    ::Distrio::Digital_ptr io_dig);

  virtual
  ::Distrio::Error * callback_analog (
    ::Distrio::Analog_ptr io_ana);

  virtual
  ::CORBA::Long id (
    void);

  virtual
  void id (
    ::CORBA::Long id);
};


#endif /* DISTRIO_IOI_H_  */