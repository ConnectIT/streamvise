
#ifndef _H_cit_vrrp
#define _H_cit_vrrp
/* 
 * Copyright (c) 2008-2012, Andy Bierman, All Rights Reserved.
 *
 * Unless required by applicable law or agreed to in writing,
 * software distributed under the License is distributed on an
 * "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
 * KIND, either express or implied.  See the License for the
 * specific language governing permissions and limitations
 * under the License.
 *

*** Generated by yangdump 2.2-2

    Combined SIL header
    module cit-vrrp
    revision 2012-04-13
    namespace http://netconfcentral.org/ns/cit-vrrp
    organization ConnectIT

 */

#include <xmlstring.h>

#include "dlq.h"
#include "ncxtypes.h"
#include "op.h"
#include "status.h"
#include "val.h"

#ifdef __cplusplus
extern "C" {
#endif

#define y_cit_vrrp_M_cit_vrrp (const xmlChar *)"cit-vrrp"
#define y_cit_vrrp_R_cit_vrrp (const xmlChar *)"2012-04-13"

#define y_cit_vrrp_N_entryno (const xmlChar *)"entryno"
#define y_cit_vrrp_N_interface (const xmlChar *)"interface"
#define y_cit_vrrp_N_ip_address (const xmlChar *)"ip-address"
#define y_cit_vrrp_N_priority (const xmlChar *)"priority"
#define y_cit_vrrp_N_rule (const xmlChar *)"rule"
#define y_cit_vrrp_N_vrid (const xmlChar *)"vrid"
#define y_cit_vrrp_N_vrrp (const xmlChar *)"vrrp"

/* list /vrrp/rule */
typedef struct y_cit_vrrp_T_vrrp_rule_ {
    dlq_hdr_t qhdr;
    uint32 entryno;
    xmlChar *interface;
    uint32 vrid;
    uint32 priority;
    val_value_t *ip_address;
} y_cit_vrrp_T_vrrp_rule;

/* container /vrrp */
typedef struct y_cit_vrrp_T_vrrp_ {
    dlq_hdr_t rule;
} y_cit_vrrp_T_vrrp;
/********************************************************************
* FUNCTION y_cit_vrrp_init
* 
* initialize the cit-vrrp server instrumentation library
* 
* INPUTS:
*    modname == requested module name
*    revision == requested version (NULL for any)
* 
* RETURNS:
*     error status
********************************************************************/
extern status_t y_cit_vrrp_init (
    const xmlChar *modname,
    const xmlChar *revision);

/********************************************************************
* FUNCTION y_cit_vrrp_init2
* 
* SIL init phase 2: non-config data structures
* Called after running config is loaded
* 
* RETURNS:
*     error status
********************************************************************/
extern status_t y_cit_vrrp_init2 (void);

/********************************************************************
* FUNCTION y_cit_vrrp_cleanup
*    cleanup the server instrumentation library
* 
********************************************************************/
extern void y_cit_vrrp_cleanup (void);

#ifdef __cplusplus
} /* end extern 'C' */
#endif

#endif