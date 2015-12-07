/*
 * Vuln Title: XXXX
 *
 * Copyright (C) 2005-2010 Sourcefire, Inc. All Rights Reserved
 *
 * Written by XXXX, Sourcefire VRT <XXXX@sourcefire.com>
 *
 * Auto-generated by XXXX
 *
 * This file may contain proprietary rules that were created, tested and
 * certified by Sourcefire, Inc. (the "VRT Certified Rules") as well as
 * rules that were created by Sourcefire and other third parties and
 * distributed under the GNU General Public License (the "GPL Rules").  The
 * VRT Certified Rules contained in this file are the property of
 * Sourcefire, Inc. Copyright 2005 Sourcefire, Inc. All Rights Reserved.
 * The GPL Rules created by Sourcefire, Inc. are the property of
 * Sourcefire, Inc. Copyright 2002-2005 Sourcefire, Inc. All Rights
 * Reserved.  All other GPL Rules are owned and copyrighted by their
 * respective owners (please see www.snort.org/contributors for a list of
 * owners and their respective copyrights).  In order to determine what
 * rules are VRT Certified Rules or GPL Rules, please refer to the VRT
 * Certified Rules License Agreement.
 */

#include <string.h>

#include "sf_snort_plugin_api.h"
#include "sf_snort_packet.h"

#include "so-util.h"
#include "so-util_base64-decode.h"

#define MAX_BASE64_BUFFER_SIZE 64

#ifdef DEBUG
#define DEBUG_SO(code) code
#else
#define DEBUG_SO(code)
#endif

/* declare detection functions */
int rule17693eval(void *p);

/* declare rule data structures */
/* flow:established, to_server; */
static FlowFlags rule17693flow0 = 
{
    FLOW_ESTABLISHED|FLOW_TO_SERVER
};

static RuleOption rule17693option0 =
{
    OPTION_TYPE_FLOWFLAGS,
    {
        &rule17693flow0
    }
};
#ifndef CONTENT_FAST_PATTERN
#define CONTENT_FAST_PATTERN 0
#endif
// content:"AUTH NTLM ", depth 0, nocase, fast_pattern; 
static ContentInfo rule17693content1 = 
{
    (uint8_t *) "AUTH NTLM ", /* pattern (now in snort content format) */
    0, /* depth */
    0, /* offset */
    CONTENT_NOCASE|CONTENT_FAST_PATTERN|CONTENT_BUF_NORMALIZED, /* flags */
    NULL, /* holder for boyer/moore PTR */
    NULL, /* more holder info - byteform */
    0, /* byteform length */
    0 /* increment length*/
};

static RuleOption rule17693option1 = 
{
    OPTION_TYPE_CONTENT,
    {
        &rule17693content1
    }
};

/* references for sid 17693 */

/* reference: url "secunia.com/advisories/22179/"; */
static RuleReference rule17693ref1 = 
{
    "url", /* type */
    "secunia.com/advisories/22179/" /* value */
};

static RuleReference rule17693ref2 =
{
    "bugtraq", /* type */
    "20290" /* value */
};

static RuleReference rule17693ref3 =
{
    "cve", /* type */
    "2006-5177" /* value */
};

static RuleReference rule17693ref4 =
{
    "cve", /* type */
    "2006-5176" /* value */
};


static RuleReference *rule17693refs[] =
{
    &rule17693ref1,
    &rule17693ref2,
    &rule17693ref3,
    &rule17693ref4,
    NULL
};

/* metadata for sid 17693 */
/* metadata:service smtp, policy security-ips alert; */
static RuleMetaData rule17693service1 = 
{
    "service smtp"
};


static RuleMetaData rule17693policy1 = 
{
    "policy security-ips alert"
};


static RuleMetaData *rule17693metadata[] =
{
    &rule17693service1,
    &rule17693policy1,
    NULL
};

RuleOption *rule17693options[] =
{
    &rule17693option0,
    &rule17693option1,
    NULL
};

Rule rule17693 = {
   /* rule header, akin to => tcp any any -> any any */
   {
       IPPROTO_TCP, /* proto */
       "$EXTERNAL_NET", /* SRCIP     */
       "any", /* SRCPORT   */
       0, /* DIRECTION */
       "$HOME_NET", /* DSTIP     */
       "25", /* DSTPORT   */
   },
   /* metadata */
   { 
       3,  /* genid */
       17693, /* sigid */
       5, /* revision */
       "attempted-admin", /* classification */
       0,  /* hardcoded priority XXX NOT PROVIDED BY GRAMMAR YET! */
       "SERVER-MAIL MailEnable NTLM Authentication buffer overflow attempt",     /* message */
       rule17693refs /* ptr to references */
       ,rule17693metadata
   },
   rule17693options, /* ptr to rule options */
   &rule17693eval, /* use the built in detection function */
   0 /* am I initialized yet? */
};


/* detection functions */
int rule17693eval(void *p) {
    const uint8_t *cursor_normal = 0;
    uint8_t decodedbuf[MAX_BASE64_BUFFER_SIZE], *decodedbuf_ptr;
    uint32_t decodedbytes;
    SFSnortPacket *sp = (SFSnortPacket *) p;

    if(sp == NULL)
        return RULE_NOMATCH;

    if(sp->payload == NULL)
        return RULE_NOMATCH;
    
    // flow:established, to_server;
    if (checkFlow(p, rule17693options[0]->option_u.flowFlags) > 0 ) {
        // content:"AUTH NTLM", depth 0, nocase, fast_pattern;
        if (contentMatch(p, rule17693options[1]->option_u.content, &cursor_normal) > 0) {

            DEBUG_SO(printf("Inside rule body\n"));

            if(base64decode(cursor_normal, MAX_BASE64_BUFFER_SIZE, decodedbuf, sizeof(decodedbuf), &decodedbytes) < 0) {
                return RULE_NOMATCH;
            }

            decodedbuf_ptr = decodedbuf;

            if(decodedbytes < 32) {
               DEBUG_SO(printf("Not enough data decoded to work with\n"));
               return RULE_NOMATCH;
            }
            else {
               DEBUG_SO(printf("Decoded %d bytes\n", decodedbytes));
            }

            // Make sure we are looking at the correct data
            if(strncmp("NTLMSSP", (const char *)decodedbuf_ptr, 7) != 0) {
                return RULE_NOMATCH;
            }

            // Confirm the type 
            decodedbuf_ptr += 8;

            // We could check for \x00 after "NTLMSSP", but won't bother.

            if(*decodedbuf_ptr != 0x01) {
                return RULE_NOMATCH;
            }

            // skip over 3-byte zero padding and dword flags
            decodedbuf_ptr += 8;

            // Now check the domain_length
            if((uint16_t)read_little_16(decodedbuf_ptr) > 0x0400) {
                return RULE_MATCH;
            }

            // Skip over 2-byte domain string allocation
            decodedbuf_ptr += 4;

            // Now check the domain_offset
            if((uint32_t)read_little_32(decodedbuf_ptr) > 0x00000800) {
               return RULE_MATCH;
            }

            decodedbuf_ptr += 4;

            // Now check the host_length
            if((uint16_t)read_little_16(decodedbuf_ptr) > 0x0400) {
               return RULE_MATCH;
            }

            // skip 2-byte host string allocation
            decodedbuf_ptr += 4;

            // Now check the host_offset
            if((uint32_t)read_little_32(decodedbuf_ptr) > 0x00000800) {
               return RULE_MATCH;
            }
        }
    }

    return RULE_NOMATCH;
}
/*
Rule *rules[] = {
    &rule17693,
    NULL
};
*/
