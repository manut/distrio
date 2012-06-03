/**
 * CORBA helpers
 *
 *  - init orb
 *  - get reference to name service
 *  - register objects @ name service
 *
 * @author Manuel Traut <manut@mecka.net>
 * @licence GPLv2
 */

#include <distrio_ioI.h>
#include <distrio_ioC.h>
#include <distrio_ioS.h>

#include <distrio_managerC.h>

#include <orbsvcs/CosNamingC.h>

#define ORB_NOT_INITIALIZED 0
#define ORB_INIT 1
#define ORB_RUNNING 2

/**
 * handle to corba objects needed for registration of new objects and running
 *  the ORB
 */
typedef struct _corba_ref {
	/** init > 0 if orb is initialized */
	int init;
	CORBA::ORB_var orb;
	PortableServer::POA_var poa;
	PortableServer::POAManager_var poa_mgr;
	CosNaming::NamingContext_var nc;
	Distrio::Manager_var manager;
} corba_ref;

static corba_ref ref = {
	.init = ORB_NOT_INITIALIZED,
};

/** initialize corba orb - argc, argv as passed to main() */
int init_corba (int argc, char **argv);
/** register a digital io with a common name at the naming service */
int register_digital (std::string _name, Distrio_Digital_i *digital);
/** lookup a digital io by a common name at the manager */
Distrio::Digital_ptr lookup_digital (std::string _name);
/** register a device with a common name at the naming service */
int register_device (std::string _name, Distrio_Device_i *dev);
/** run the orb - function blocks until orb shutdown */
int run_orb (void);
