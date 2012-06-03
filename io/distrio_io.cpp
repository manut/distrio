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

#include "distrio_ioI.h"

// Implementation skeleton constructor
Distrio_Digital_i::Distrio_Digital_i (void)
{
}

// Implementation skeleton destructor
Distrio_Digital_i::~Distrio_Digital_i (void)
{
}

::Distrio::Error * Distrio_Digital_i::name (
  ::CORBA::String_out name)
{
  // Add your implementation here
}

::Distrio::Error * Distrio_Digital_i::set (
  void)
{
  // Add your implementation here
}

::Distrio::Error * Distrio_Digital_i::reset (
  void)
{
  // Add your implementation here
}

::Distrio::Error * Distrio_Digital_i::get (
  ::CORBA::Long_out value)
{
  // Add your implementation here
}

::Distrio::Error * Distrio_Digital_i::register_callback (
  ::Distrio::Device_ptr dev,
  ::Distrio::Digital_trigger trigger)
{
  // Add your implementation here
}

::Distrio::Timestamp Distrio_Digital_i::last_update (
  void)
{
  // Add your implementation here
}

void Distrio_Digital_i::last_update (
  const ::Distrio::Timestamp & last_update)
{
  // Add your implementation here
}

::CORBA::Long Distrio_Digital_i::id (
  void)
{
  // Add your implementation here
}

void Distrio_Digital_i::id (
  ::CORBA::Long id)
{
  // Add your implementation here
}

// Implementation skeleton constructor
Distrio_Analog_i::Distrio_Analog_i (void)
{
}

// Implementation skeleton destructor
Distrio_Analog_i::~Distrio_Analog_i (void)
{
}

::Distrio::Error * Distrio_Analog_i::name (
  ::CORBA::String_out name)
{
  // Add your implementation here
}

::Distrio::Error * Distrio_Analog_i::min (
  ::CORBA::Long_out min)
{
  // Add your implementation here
}

::Distrio::Error * Distrio_Analog_i::max (
  ::CORBA::Long_out max)
{
  // Add your implementation here
}

::Distrio::Error * Distrio_Analog_i::set (
  ::CORBA::Long value)
{
  // Add your implementation here
}

::Distrio::Error * Distrio_Analog_i::get (
  ::CORBA::Long_out value)
{
  // Add your implementation here
}

::Distrio::Error * Distrio_Analog_i::register_callback (
  ::Distrio::Device_ptr dev,
  const ::Distrio::Analog_trigger & trigger)
{
  // Add your implementation here
}

::Distrio::Timestamp Distrio_Analog_i::last_update (
  void)
{
  // Add your implementation here
}

void Distrio_Analog_i::last_update (
  const ::Distrio::Timestamp & last_update)
{
  // Add your implementation here
}

::CORBA::Long Distrio_Analog_i::id (
  void)
{
  // Add your implementation here
}

void Distrio_Analog_i::id (
  ::CORBA::Long id)
{
  // Add your implementation here
}

// Implementation skeleton constructor
Distrio_Device_i::Distrio_Device_i (void)
{
}

// Implementation skeleton destructor
Distrio_Device_i::~Distrio_Device_i (void)
{
}

::Distrio::Error * Distrio_Device_i::name (
  ::CORBA::String_out name)
{
  // Add your implementation here
}

::Distrio::Error * Distrio_Device_i::execute (
  const ::Distrio::Dev_function & func)
{
  // Add your implementation here
}

::Distrio::Error * Distrio_Device_i::functions (
  ::Distrio::Dev_function_list_out funcs)
{
  // Add your implementation here
}

::Distrio::Error * Distrio_Device_i::callback_digital (
  ::Distrio::Digital_ptr io_dig)
{
  // Add your implementation here
}

::Distrio::Error * Distrio_Device_i::callback_analog (
  ::Distrio::Analog_ptr io_ana)
{
  // Add your implementation here
}

::CORBA::Long Distrio_Device_i::id (
  void)
{
  // Add your implementation here
}

void Distrio_Device_i::id (
  ::CORBA::Long id)
{
  // Add your implementation here
}

