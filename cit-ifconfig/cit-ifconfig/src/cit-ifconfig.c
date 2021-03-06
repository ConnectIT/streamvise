
/* 
 * Copyright (c) 2013, Chris Mavrakis, All Rights Reserved.
 * Full license can be found in LICENSE file.

*** Generated by yangdump 2.2.1731

    Combined SIL module
    module cit-ifconfig
    revision 2012-02-14
    namespace http://netconfcentral.org/ns/cit-ifconfig
    organization ConnectIT

 */

#include <xmlstring.h>

#include "procdefs.h"
#include "agt.h"
#include "agt_cb.h"
#include "agt_timer.h"
#include "agt_util.h"
#include "dlq.h"
#include "ncx.h"
#include "ncx_feature.h"
#include "ncxmod.h"
#include "ncxtypes.h"
#include "status.h"
#include "cit-ifconfig.h"
#include "cit-helper.h"

/* module static variables */
static ncx_module_t *cit_ifconfig_mod;
static obj_template_t *ifconfig_obj;
static val_value_t *ifconfig_val;

/* put your static variables here */

/********************************************************************
* FUNCTION y_cit_ifconfig_init_static_vars
* 
* initialize module static variables
* 
********************************************************************/
static void y_cit_ifconfig_init_static_vars (void)
{
    cit_ifconfig_mod = NULL;
    ifconfig_obj = NULL;
    ifconfig_val = NULL;

    /* init your static variables here */

} /* y_cit_ifconfig_init_static_vars */


/********************************************************************
* FUNCTION cit_ifconfig_ifconfig_interface_name_edit
* 
* Edit database object callback
* Path: /ifconfig/interface/name
* Add object instrumentation in COMMIT phase.
* 
* INPUTS:
*     see agt/agt_cb.h for details
* 
* RETURNS:
*     error status
********************************************************************/
static status_t cit_ifconfig_ifconfig_interface_name_edit (
    ses_cb_t *scb,
    rpc_msg_t *msg,
    agt_cbtyp_t cbtyp,
    op_editop_t editop,
    val_value_t *newval,
    val_value_t *curval)
{
    status_t res = NO_ERR;
    val_value_t *errorval = (curval) ? curval : newval;

    if (LOGDEBUG) {
        log_debug("\nEnter cit_ifconfig_ifconfig_interface_name_edit callback for %s phase",
            agt_cbtype_name(cbtyp));
    }

    switch (cbtyp) {
    case AGT_CB_VALIDATE:
        /* description-stmt validation here */
        break;
    case AGT_CB_APPLY:
        /* database manipulation done here */
        break;
    case AGT_CB_COMMIT:
        /* device instrumentation done here */
        switch (editop) {
        case OP_EDITOP_LOAD:
            break;
        case OP_EDITOP_MERGE:
            break;
        case OP_EDITOP_REPLACE:
            break;
        case OP_EDITOP_CREATE:
            break;
        case OP_EDITOP_DELETE:
            break;
        default:
            res = SET_ERROR(ERR_INTERNAL_VAL);
        }
        break;
    case AGT_CB_ROLLBACK:
        /* undo device instrumentation here */
        break;
    default:
        res = SET_ERROR(ERR_INTERNAL_VAL);
    }

    if (res != NO_ERR) {
        agt_record_error(
            scb,
            &msg->mhdr,
            NCX_LAYER_CONTENT,
            res,
            NULL,
            (errorval) ? NCX_NT_VAL : NCX_NT_NONE,
            errorval,
            (errorval) ? NCX_NT_VAL : NCX_NT_NONE,
            errorval);
    }
    return res;

} /* cit_ifconfig_ifconfig_interface_name_edit */


/********************************************************************
* FUNCTION cit_ifconfig_ifconfig_interface_up_edit
* 
* Edit database object callback
* Path: /ifconfig/interface/up
* Add object instrumentation in COMMIT phase.
* 
* INPUTS:
*     see agt/agt_cb.h for details
* 
* RETURNS:
*     error status
********************************************************************/
static status_t cit_ifconfig_ifconfig_interface_up_edit (
    ses_cb_t *scb,
    rpc_msg_t *msg,
    agt_cbtyp_t cbtyp,
    op_editop_t editop,
    val_value_t *newval,
    val_value_t *curval)
{
    status_t res = NO_ERR;
    val_value_t *errorval = (curval) ? curval : newval;

    if (LOGDEBUG) {
        log_debug("\nEnter cit_ifconfig_ifconfig_interface_up_edit callback for %s phase",
            agt_cbtype_name(cbtyp));
    }

    switch (cbtyp) {
    case AGT_CB_VALIDATE:
        /* description-stmt validation here */
        break;
    case AGT_CB_APPLY:
        /* database manipulation done here */
        break;
    case AGT_CB_COMMIT:
        {
		char cmd[512];

	//	FIND INTERFACE NAME (ALT)
		char iface[] = "eth11"; //holds the interface name 
		sprintf(iface,"%s",VAL_STRING(val_get_first_child(newval->parent)));

	//	COMPILE STRING
		if (VAL_BOOL(newval)){//if true, bring iface up
			int length = sprintf(cmd, "sudo ifconfig %s up", iface);
		}else{
			int length = sprintf(cmd, "sudo ifconfig %s down", iface);
		}
		int resultss = runsystem(cmd); //Send command for running

        	switch (editop) {
	        case OP_EDITOP_LOAD:
	            break;
	        case OP_EDITOP_MERGE:
	            break;
	        case OP_EDITOP_REPLACE:
	            break;
        	case OP_EDITOP_CREATE:
	            break;
	        case OP_EDITOP_DELETE:
	            break;
        	default:
	            res = SET_ERROR(ERR_INTERNAL_VAL);
	        }
	}
        break;
    case AGT_CB_ROLLBACK:
        /* undo device instrumentation here */
        break;
    default:
        res = SET_ERROR(ERR_INTERNAL_VAL);
    }

    if (res != NO_ERR) {
        agt_record_error(
            scb,
            &msg->mhdr,
            NCX_LAYER_CONTENT,
            res,
            NULL,
            (errorval) ? NCX_NT_VAL : NCX_NT_NONE,
            errorval,
            (errorval) ? NCX_NT_VAL : NCX_NT_NONE,
            errorval);
    }
    return res;

} /* cit_ifconfig_ifconfig_interface_up_edit */


/********************************************************************
* FUNCTION cit_ifconfig_ifconfig_interface_mtu_edit
* 
* Edit database object callback
* Path: /ifconfig/interface/mtu
* Add object instrumentation in COMMIT phase.
* 
* INPUTS:
*     see agt/agt_cb.h for details
* 
* RETURNS:
*     error status
********************************************************************/
static status_t cit_ifconfig_ifconfig_interface_mtu_edit (
    ses_cb_t *scb,
    rpc_msg_t *msg,
    agt_cbtyp_t cbtyp,
    op_editop_t editop,
    val_value_t *newval,
    val_value_t *curval)
{
    status_t res = NO_ERR;
    val_value_t *errorval = (curval) ? curval : newval;

    if (LOGDEBUG) {
        log_debug("\nEnter cit_ifconfig_ifconfig_interface_mtu_edit callback for %s phase",
            agt_cbtype_name(cbtyp));
    }

    switch (cbtyp) {
    case AGT_CB_VALIDATE:
        /* description-stmt validation here */
        break;
    case AGT_CB_APPLY:
        /* database manipulation done here */
        break;
    case AGT_CB_COMMIT:
        {
	
		char cmd[512];
		int mtu = VAL_INT(newval);

	//	FIND INTERFACE NAME (ALT)
		char iface[] = "eth11"; //holds the interface name 
		sprintf(iface,"%s",VAL_STRING(val_get_first_child(newval->parent)));

	//	COMPILE STRING
		int length = sprintf(cmd, "sudo ifconfig %s mtu %i",iface, mtu);
		int resultss = runsystem(cmd); //Send command for running
	
        	switch (editop) {
	        case OP_EDITOP_LOAD:
	            break;
	        case OP_EDITOP_MERGE:
	            break;
	        case OP_EDITOP_REPLACE:
	            break;
        	case OP_EDITOP_CREATE:
	            break;
	        case OP_EDITOP_DELETE:
	            break;
        	default:
	            res = SET_ERROR(ERR_INTERNAL_VAL);
	        }
	}
    case AGT_CB_ROLLBACK:
        /* undo device instrumentation here */
        break;
    default:
        res = SET_ERROR(ERR_INTERNAL_VAL);
    }

    if (res != NO_ERR) {
        agt_record_error(
            scb,
            &msg->mhdr,
            NCX_LAYER_CONTENT,
            res,
            NULL,
            (errorval) ? NCX_NT_VAL : NCX_NT_NONE,
            errorval,
            (errorval) ? NCX_NT_VAL : NCX_NT_NONE,
            errorval);
    }
    return res;

} /* cit_ifconfig_ifconfig_interface_mtu_edit */


/********************************************************************
* FUNCTION cit_ifconfig_ifconfig_interface_ip_address_edit
* 
* Edit database object callback
* Path: /ifconfig/interface/ip-address
* Add object instrumentation in COMMIT phase.
* 
* INPUTS:
*     see agt/agt_cb.h for details
* 
* RETURNS:
*     error status
********************************************************************/
static status_t cit_ifconfig_ifconfig_interface_ip_address_edit (
    ses_cb_t *scb,
    rpc_msg_t *msg,
    agt_cbtyp_t cbtyp,
    op_editop_t editop,
    val_value_t *newval,
    val_value_t *curval)
{
    status_t res = NO_ERR;
    val_value_t *errorval = (curval) ? curval : newval;

    if (LOGDEBUG) {
        log_debug("\nEnter cit_ifconfig_ifconfig_interface_ip_address_edit callback for %s phase",
            agt_cbtype_name(cbtyp));
    }

    switch (cbtyp) {
    case AGT_CB_VALIDATE:
        /* description-stmt validation here */
        break;
    case AGT_CB_APPLY:
        /* database manipulation done here */
        break;
    case AGT_CB_COMMIT:
	{

		char cmd[512];
		char *ip = VAL_STRING(newval);

	//	FIND INTERFACE NAME (ALT)
		char iface[] = "eth11"; //holds the interface name 
		sprintf(iface,"%s",VAL_STRING(val_get_first_child(newval->parent)));

	//	COMPILE STRING
		int length = sprintf(cmd, "sudo ifconfig %s %s",iface, ip);
		int resultss = runsystem(cmd); //Send command for running

        	switch (editop) {
	        case OP_EDITOP_LOAD:
	            break;
	        case OP_EDITOP_MERGE:
	            break;
	        case OP_EDITOP_REPLACE:
	            break;
        	case OP_EDITOP_CREATE:
	            break;
	        case OP_EDITOP_DELETE:
	            break;
        	default:
	            res = SET_ERROR(ERR_INTERNAL_VAL);
	        }
	}
        break;
    case AGT_CB_ROLLBACK:
        /* undo device instrumentation here */
        break;
    default:
        res = SET_ERROR(ERR_INTERNAL_VAL);
    }

    if (res != NO_ERR) {
        agt_record_error(
            scb,
            &msg->mhdr,
            NCX_LAYER_CONTENT,
            res,
            NULL,
            (errorval) ? NCX_NT_VAL : NCX_NT_NONE,
            errorval,
            (errorval) ? NCX_NT_VAL : NCX_NT_NONE,
            errorval);
    }
    return res;

} /* cit_ifconfig_ifconfig_interface_ip_address_edit */


/********************************************************************
* FUNCTION cit_ifconfig_ifconfig_interface_subnet_mask_edit
* 
* Edit database object callback
* Path: /ifconfig/interface/subnet-mask
* Add object instrumentation in COMMIT phase.
* 
* INPUTS:
*     see agt/agt_cb.h for details
* 
* RETURNS:
*     error status
********************************************************************/
static status_t cit_ifconfig_ifconfig_interface_subnet_mask_edit (
    ses_cb_t *scb,
    rpc_msg_t *msg,
    agt_cbtyp_t cbtyp,
    op_editop_t editop,
    val_value_t *newval,
    val_value_t *curval)
{
    status_t res = NO_ERR;
    val_value_t *errorval = (curval) ? curval : newval;

    if (LOGDEBUG) {
        log_debug("\nEnter cit_ifconfig_ifconfig_interface_subnet_mask_edit callback for %s phase",
            agt_cbtype_name(cbtyp));
    }

    switch (cbtyp) {
    case AGT_CB_VALIDATE:
        /* description-stmt validation here */
        break;
    case AGT_CB_APPLY:
        /* database manipulation done here */
        break;
    case AGT_CB_COMMIT:
 	{

		char cmd[512];
		char *ip = VAL_STRING(newval);

	//	FIND INTERFACE NAME (ALT)
		char iface[] = "eth11"; //holds the interface name 
		sprintf(iface,"%s",VAL_STRING(val_get_first_child(newval->parent)));

	//	COMPILE STRING
		int length = sprintf(cmd, "sudo ifconfig %s netmask %s",iface, ip);
		int resultss = runsystem(cmd); //Send command for running

        	switch (editop) {
	        case OP_EDITOP_LOAD:
	            break;
	        case OP_EDITOP_MERGE:
	            break;
	        case OP_EDITOP_REPLACE:
	            break;
        	case OP_EDITOP_CREATE:
	            break;
	        case OP_EDITOP_DELETE:
	            break;
        	default:
	            res = SET_ERROR(ERR_INTERNAL_VAL);
	        }
	}
        break;
    case AGT_CB_ROLLBACK:
        /* undo device instrumentation here */
        break;
    default:
        res = SET_ERROR(ERR_INTERNAL_VAL);
    }

    if (res != NO_ERR) {
        agt_record_error(
            scb,
            &msg->mhdr,
            NCX_LAYER_CONTENT,
            res,
            NULL,
            (errorval) ? NCX_NT_VAL : NCX_NT_NONE,
            errorval,
            (errorval) ? NCX_NT_VAL : NCX_NT_NONE,
            errorval);
    }
    return res;

} /* cit_ifconfig_ifconfig_interface_subnet_mask_edit */


/********************************************************************
* FUNCTION cit_ifconfig_ifconfig_interface_mac_address_edit
* 
* Edit database object callback
* Path: /ifconfig/interface/mac-address
* Add object instrumentation in COMMIT phase.
* 
* INPUTS:
*     see agt/agt_cb.h for details
* 
* RETURNS:
*     error status
********************************************************************/
static status_t cit_ifconfig_ifconfig_interface_mac_address_edit (
    ses_cb_t *scb,
    rpc_msg_t *msg,
    agt_cbtyp_t cbtyp,
    op_editop_t editop,
    val_value_t *newval,
    val_value_t *curval)
{
    status_t res = NO_ERR;
    val_value_t *errorval = (curval) ? curval : newval;

    if (LOGDEBUG) {
        log_debug("\nEnter cit_ifconfig_ifconfig_interface_mac_address_edit callback for %s phase",
            agt_cbtype_name(cbtyp));
    }

    switch (cbtyp) {
    case AGT_CB_VALIDATE:
        /* description-stmt validation here */
        break;
    case AGT_CB_APPLY:
        /* database manipulation done here */
        break;
    case AGT_CB_COMMIT:
        /* device instrumentation done here */
        switch (editop) {
        case OP_EDITOP_LOAD:
            break;
        case OP_EDITOP_MERGE:
            break;
        case OP_EDITOP_REPLACE:
            break;
        case OP_EDITOP_CREATE:
            break;
        case OP_EDITOP_DELETE:
            break;
        default:
            res = SET_ERROR(ERR_INTERNAL_VAL);
        }
        break;
    case AGT_CB_ROLLBACK:
        /* undo device instrumentation here */
        break;
    default:
        res = SET_ERROR(ERR_INTERNAL_VAL);
    }

    if (res != NO_ERR) {
        agt_record_error(
            scb,
            &msg->mhdr,
            NCX_LAYER_CONTENT,
            res,
            NULL,
            (errorval) ? NCX_NT_VAL : NCX_NT_NONE,
            errorval,
            (errorval) ? NCX_NT_VAL : NCX_NT_NONE,
            errorval);
    }
    return res;

} /* cit_ifconfig_ifconfig_interface_mac_address_edit */


/********************************************************************
* FUNCTION cit_ifconfig_ifconfig_interface_edit
* 
* Edit database object callback
* Path: /ifconfig/interface
* Add object instrumentation in COMMIT phase.
* 
* INPUTS:
*     see agt/agt_cb.h for details
* 
* RETURNS:
*     error status
********************************************************************/
static status_t cit_ifconfig_ifconfig_interface_edit (
    ses_cb_t *scb,
    rpc_msg_t *msg,
    agt_cbtyp_t cbtyp,
    op_editop_t editop,
    val_value_t *newval,
    val_value_t *curval)
{
    status_t res = NO_ERR;
    val_value_t *errorval = (curval) ? curval : newval;

    if (LOGDEBUG) {
        log_debug("\nEnter cit_ifconfig_ifconfig_interface_edit callback for %s phase",
            agt_cbtype_name(cbtyp));
    }

    switch (cbtyp) {
    case AGT_CB_VALIDATE:
        /* description-stmt validation here */
        break;
    case AGT_CB_APPLY:
        /* database manipulation done here */
        break;
    case AGT_CB_COMMIT:
        /* device instrumentation done here */
        switch (editop) {
        case OP_EDITOP_LOAD:
            break;
        case OP_EDITOP_MERGE:
            break;
        case OP_EDITOP_REPLACE:
            break;
        case OP_EDITOP_CREATE:
            break;
        case OP_EDITOP_DELETE:
            break;
        default:
            res = SET_ERROR(ERR_INTERNAL_VAL);
        }
        break;
    case AGT_CB_ROLLBACK:
        /* undo device instrumentation here */
        break;
    default:
        res = SET_ERROR(ERR_INTERNAL_VAL);
    }

    if (res != NO_ERR) {
        agt_record_error(
            scb,
            &msg->mhdr,
            NCX_LAYER_CONTENT,
            res,
            NULL,
            (errorval) ? NCX_NT_VAL : NCX_NT_NONE,
            errorval,
            (errorval) ? NCX_NT_VAL : NCX_NT_NONE,
            errorval);
    }
    return res;

} /* cit_ifconfig_ifconfig_interface_edit */


/********************************************************************
* FUNCTION cit_ifconfig_ifconfig_edit
* 
* Edit database object callback
* Path: /ifconfig
* Add object instrumentation in COMMIT phase.
* 
* INPUTS:
*     see agt/agt_cb.h for details
* 
* RETURNS:
*     error status
********************************************************************/
static status_t cit_ifconfig_ifconfig_edit (
    ses_cb_t *scb,
    rpc_msg_t *msg,
    agt_cbtyp_t cbtyp,
    op_editop_t editop,
    val_value_t *newval,
    val_value_t *curval)
{
    status_t res = NO_ERR;
    val_value_t *errorval = (curval) ? curval : newval;

    if (LOGDEBUG) {
        log_debug("\nEnter cit_ifconfig_ifconfig_edit callback for %s phase",
            agt_cbtype_name(cbtyp));
    }

    switch (cbtyp) {
    case AGT_CB_VALIDATE:
        /* description-stmt validation here */
        break;
    case AGT_CB_APPLY:
        /* database manipulation done here */
        break;
    case AGT_CB_COMMIT:
        /* device instrumentation done here */
        switch (editop) {
        case OP_EDITOP_LOAD:
            break;
        case OP_EDITOP_MERGE:
            break;
        case OP_EDITOP_REPLACE:
            break;
        case OP_EDITOP_CREATE:
            break;
        case OP_EDITOP_DELETE:
            break;
        default:
            res = SET_ERROR(ERR_INTERNAL_VAL);
        }

        if (res == NO_ERR) {
            res = agt_check_cache(&ifconfig_val, newval, curval, editop);
        }
        
        break;
    case AGT_CB_ROLLBACK:
        /* undo device instrumentation here */
        break;
    default:
        res = SET_ERROR(ERR_INTERNAL_VAL);
    }

    if (res != NO_ERR) {
        agt_record_error(
            scb,
            &msg->mhdr,
            NCX_LAYER_CONTENT,
            res,
            NULL,
            (errorval) ? NCX_NT_VAL : NCX_NT_NONE,
            errorval,
            (errorval) ? NCX_NT_VAL : NCX_NT_NONE,
            errorval);
    }
    return res;

} /* cit_ifconfig_ifconfig_edit */

/********************************************************************
* FUNCTION y_cit_ifconfig_init
* 
* initialize the cit-ifconfig server instrumentation library
* 
* INPUTS:
*    modname == requested module name
*    revision == requested version (NULL for any)
* 
* RETURNS:
*     error status
********************************************************************/
status_t y_cit_ifconfig_init (
    const xmlChar *modname,
    const xmlChar *revision)
{
    status_t res = NO_ERR;
    agt_profile_t *agt_profile = agt_get_profile();

    y_cit_ifconfig_init_static_vars();

    /* change if custom handling done */
    if (xml_strcmp(modname, y_cit_ifconfig_M_cit_ifconfig)) {
        return ERR_NCX_UNKNOWN_MODULE;
    }

    if (revision && xml_strcmp(revision, y_cit_ifconfig_R_cit_ifconfig)) {
        return ERR_NCX_WRONG_VERSION;
    }
    res = ncxmod_load_module(
        y_cit_ifconfig_M_cit_ifconfig,
        y_cit_ifconfig_R_cit_ifconfig,
        &agt_profile->agt_savedevQ,
        &cit_ifconfig_mod);
    if (res != NO_ERR) {
        return res;
    }

    ifconfig_obj = ncx_find_object(
        cit_ifconfig_mod,
        y_cit_ifconfig_N_ifconfig);
    if (cit_ifconfig_mod == NULL) {
        return SET_ERROR(ERR_NCX_DEF_NOT_FOUND);
    }
    res = agt_cb_register_callback(
        y_cit_ifconfig_M_cit_ifconfig,
        (const xmlChar *)"/ifconfig",
        y_cit_ifconfig_R_cit_ifconfig,
        cit_ifconfig_ifconfig_edit);
    if (res != NO_ERR) {
        return res;
    }

    res = agt_cb_register_callback(
        y_cit_ifconfig_M_cit_ifconfig,
        (const xmlChar *)"/ifconfig/interface",
        y_cit_ifconfig_R_cit_ifconfig,
        cit_ifconfig_ifconfig_interface_edit);
    if (res != NO_ERR) {
        return res;
    }

    res = agt_cb_register_callback(
        y_cit_ifconfig_M_cit_ifconfig,
        (const xmlChar *)"/ifconfig/interface/name",
        y_cit_ifconfig_R_cit_ifconfig,
        cit_ifconfig_ifconfig_interface_name_edit);
    if (res != NO_ERR) {
        return res;
    }

    res = agt_cb_register_callback(
        y_cit_ifconfig_M_cit_ifconfig,
        (const xmlChar *)"/ifconfig/interface/up",
        y_cit_ifconfig_R_cit_ifconfig,
        cit_ifconfig_ifconfig_interface_up_edit);
    if (res != NO_ERR) {
        return res;
    }

    res = agt_cb_register_callback(
        y_cit_ifconfig_M_cit_ifconfig,
        (const xmlChar *)"/ifconfig/interface/mtu",
        y_cit_ifconfig_R_cit_ifconfig,
        cit_ifconfig_ifconfig_interface_mtu_edit);
    if (res != NO_ERR) {
        return res;
    }

    res = agt_cb_register_callback(
        y_cit_ifconfig_M_cit_ifconfig,
        (const xmlChar *)"/ifconfig/interface/ip-address",
        y_cit_ifconfig_R_cit_ifconfig,
        cit_ifconfig_ifconfig_interface_ip_address_edit);
    if (res != NO_ERR) {
        return res;
    }

    res = agt_cb_register_callback(
        y_cit_ifconfig_M_cit_ifconfig,
        (const xmlChar *)"/ifconfig/interface/subnet-mask",
        y_cit_ifconfig_R_cit_ifconfig,
        cit_ifconfig_ifconfig_interface_subnet_mask_edit);
    if (res != NO_ERR) {
        return res;
    }

    res = agt_cb_register_callback(
        y_cit_ifconfig_M_cit_ifconfig,
        (const xmlChar *)"/ifconfig/interface/mac-address",
        y_cit_ifconfig_R_cit_ifconfig,
        cit_ifconfig_ifconfig_interface_mac_address_edit);
    if (res != NO_ERR) {
        return res;
    }

    /* put your module initialization code here */
    
    return res;
} /* y_cit_ifconfig_init */

/********************************************************************
* FUNCTION y_cit_ifconfig_init2
* 
* SIL init phase 2: non-config data structures
* Called after running config is loaded
* 
* RETURNS:
*     error status
********************************************************************/
status_t y_cit_ifconfig_init2 (void)
{
    status_t res = NO_ERR;

    ifconfig_val = agt_init_cache(
        y_cit_ifconfig_M_cit_ifconfig,
        y_cit_ifconfig_N_ifconfig,
        &res);
    if (res != NO_ERR) {
        return res;
    }

    /* put your init2 code here */

    return res;
} /* y_cit_ifconfig_init2 */

/********************************************************************
* FUNCTION y_cit_ifconfig_cleanup
*    cleanup the server instrumentation library
* 
********************************************************************/
void y_cit_ifconfig_cleanup (void)
{
    agt_cb_unregister_callbacks(
        y_cit_ifconfig_M_cit_ifconfig,
        (const xmlChar *)"/ifconfig");

    agt_cb_unregister_callbacks(
        y_cit_ifconfig_M_cit_ifconfig,
        (const xmlChar *)"/ifconfig/interface");

    agt_cb_unregister_callbacks(
        y_cit_ifconfig_M_cit_ifconfig,
        (const xmlChar *)"/ifconfig/interface/name");

    agt_cb_unregister_callbacks(
        y_cit_ifconfig_M_cit_ifconfig,
        (const xmlChar *)"/ifconfig/interface/up");

    agt_cb_unregister_callbacks(
        y_cit_ifconfig_M_cit_ifconfig,
        (const xmlChar *)"/ifconfig/interface/mtu");

    agt_cb_unregister_callbacks(
        y_cit_ifconfig_M_cit_ifconfig,
        (const xmlChar *)"/ifconfig/interface/ip-address");

    agt_cb_unregister_callbacks(
        y_cit_ifconfig_M_cit_ifconfig,
        (const xmlChar *)"/ifconfig/interface/subnet-mask");

    agt_cb_unregister_callbacks(
        y_cit_ifconfig_M_cit_ifconfig,
        (const xmlChar *)"/ifconfig/interface/mac-address");

    /* put your cleanup code here */
    
} /* y_cit_ifconfig_cleanup */

/* END cit_ifconfig.c */
