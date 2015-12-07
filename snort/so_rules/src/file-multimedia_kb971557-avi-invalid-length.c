/*
 * Use at your own risk.
 *
 * Copyright (C) 2005-2008 Sourcefire, Inc.
 * 
 * This file is autogenerated via rules2c, by Brian Caswell <bmc@sourcefire.com>
 */


#include "sf_snort_plugin_api.h"
#include "sf_snort_packet.h"

//#define DEBUG
#ifdef DEBUG
#define DEBUG_WRAP(code) code
#else
#define DEBUG_WRAP(code)
#endif


/* declare detection functions */
int rule15857eval(void *p);

/* declare rule data structures */
/* precompile the stuff that needs pre-compiled */
/* flow:established, to_client; */
static FlowFlags rule15857flow0 = 
{
    FLOW_ESTABLISHED|FLOW_TO_CLIENT
};

static RuleOption rule15857option0 =
{
    OPTION_TYPE_FLOWFLAGS,
    {
        &rule15857flow0
    }
};
#ifndef CONTENT_FAST_PATTERN
#define CONTENT_FAST_PATTERN 0
#endif
// content:"RIFF", depth 4, fast_pattern; 
static ContentInfo rule15857content1 = 
{
    (uint8_t *) "RIFF", /* pattern (now in snort content format) */
    4, /* depth */
    0, /* offset */
    CONTENT_FAST_PATTERN|CONTENT_BUF_NORMALIZED, /* flags */
    NULL, /* holder for boyer/moore PTR */
    NULL, /* more holder info - byteform */
    0, /* byteform length */
    0 /* increment length*/
};

static RuleOption rule15857option1 = 
{
    OPTION_TYPE_CONTENT,
    {
        &rule15857content1
    }
};
// content:"AVI", offset 4, depth 4, relative; 
static ContentInfo rule15857content2 = 
{
    (uint8_t *) "AVI", /* pattern (now in snort content format) */
    4, /* depth */
    4, /* offset */
    CONTENT_RELATIVE|CONTENT_BUF_NORMALIZED, /* flags */
    NULL, /* holder for boyer/moore PTR */
    NULL, /* more holder info - byteform */
    0, /* byteform length */
    0 /* increment length*/
};

static RuleOption rule15857option2 = 
{
    OPTION_TYPE_CONTENT,
    {
        &rule15857content2
    }
};
// content:"LIST", depth 0, relative; 
static ContentInfo rule15857content3 = 
{
    (uint8_t *) "LIST", /* pattern (now in snort content format) */
    0, /* depth */
    0, /* offset */
    CONTENT_RELATIVE|CONTENT_BUF_NORMALIZED, /* flags */
    NULL, /* holder for boyer/moore PTR */
    NULL, /* more holder info - byteform */
    0, /* byteform length */
    0 /* increment length*/
};

static RuleOption rule15857option3 = 
{
    OPTION_TYPE_CONTENT,
    {
        &rule15857content3
    }
};

// file_data
static CursorInfo rule15857file_data4 =
{
    0, /* offset */
    CONTENT_BUF_NORMALIZED /* flags */
};

static RuleOption rule15857option4 =
{
#ifndef MISSINGFILEDATA
    OPTION_TYPE_FILE_DATA,
#else
    OPTION_TYPE_SET_CURSOR,
#endif
    {
        &rule15857file_data4
    }
};

/* references for sid 15857 */
/* reference: cve "2009-1546"; */
static RuleReference rule15857ref1 = 
{
    "cve", /* type */
    "2009-1546" /* value */
};

/* reference: url "technet.microsoft.com/en-us/security/bulletin/MS09-038"; */
static RuleReference rule15857ref2 = 
{
    "url", /* type */
    "technet.microsoft.com/en-us/security/bulletin/MS09-038" /* value */
};

static RuleReference *rule15857refs[] =
{
    &rule15857ref1,
    &rule15857ref2,
    NULL
};
/* metadata for sid 15857 */
/* metadata:service http, policy balanced-ips drop, policy security-ips drop; */
static RuleMetaData rule15857service1 = 
{
    "service http"
};

static RuleMetaData rule15857policy1 =
{
   "policy max-detect-ips drop"
};

static RuleMetaData *rule15857metadata[] =
{
    &rule15857service1,
    &rule15857policy1,
    NULL
};

RuleOption *rule15857options[] =
{
    &rule15857option0,
    &rule15857option1,
    &rule15857option2,
    &rule15857option3,
    &rule15857option4,
    NULL
};

Rule rule15857 = {
   
   /* rule header, akin to => tcp any any -> any any               */{
       IPPROTO_TCP, /* proto */
       "$EXTERNAL_NET", /* SRCIP     */
       "$HTTP_PORTS", /* SRCPORT   */
   
       0, /* DIRECTION */
       "$HOME_NET", /* DSTIP     */
   
       "any", /* DSTPORT   */
   },
   /* metadata */
   { 
       3,  /* genid */
       15857, /* sigid */
       8, /* revision */
   
       "attempted-user", /* classification */
       0,  /* hardcoded priority XXX NOT PROVIDED BY GRAMMAR YET! */
       "FILE-MULTIMEDIA Microsoft Windows AVIFile media file invalid header length",     /* message */
       rule15857refs /* ptr to references */
       ,rule15857metadata
   },
   rule15857options, /* ptr to rule options */
   &rule15857eval, /* use the built in detection function */
   0 /* am I initialized yet? */
};


/* detection functions */
int rule15857eval(void *p) {
    const uint8_t *cursor_normal = 0;

    SFSnortPacket *sp = (SFSnortPacket *) p;
    const uint8_t *beg_of_payload, *end_of_payload;
    const uint8_t *cursor_detect, *cursor_temp;

    uint32_t chunk_length;
    uint32_t list_length;
    uint64_t total_length;

    if(sp == NULL)
        return RULE_NOMATCH;

    if(sp->payload == NULL)
        return RULE_NOMATCH;
    
    // flow:established, to_client;
    if (checkFlow(p, rule15857options[0]->option_u.flowFlags) > 0 ) {
        // file_data
        #ifndef MISSINGFILEDATA
        if(fileData(p, rule15857options[4]->option_u.cursor, &cursor_normal) <= 0)
           return RULE_NOMATCH;
        #else
        if(setCursor(p, rule15857options[4]->option_u.cursor, &cursor_normal) <= 0)
           return RULE_NOMATCH;
        #endif
        // content:"RIFF", depth 4, fast_pattern;
        if (contentMatch(p, rule15857options[1]->option_u.content, &cursor_normal) > 0) {
            // content:"AVI", offset 4, depth 4, relative;
            if (contentMatch(p, rule15857options[2]->option_u.content, &cursor_normal) > 0) {
                // content:"LIST", depth 0, relative;

                if(getBuffer(sp, CONTENT_BUF_NORMALIZED, &beg_of_payload, &end_of_payload) <= 0)
                  return RULE_NOMATCH;

                while (contentMatch(p, rule15857options[3]->option_u.content, &cursor_normal) > 0) {

                     if(cursor_normal + 16 >= end_of_payload)
                         return RULE_NOMATCH;

                     cursor_detect = cursor_normal;

                     list_length = *cursor_detect++;
                     list_length |= (*cursor_detect++) << 8;
                     list_length |= (*cursor_detect++) << 16;
                     list_length |= (*cursor_detect++) << 24;
                     
                     DEBUG_WRAP(printf("\n----------List Length %x\n", list_length));

                     cursor_detect += 8;
                     
                     total_length = 8; // Two chunk names

                     while ((list_length > total_length) && (cursor_detect + 4 < end_of_payload)) {

                        chunk_length = *cursor_detect++;
                        chunk_length |= (*cursor_detect++) << 8;
                        chunk_length |= (*cursor_detect++) << 16;
                        chunk_length |= (*cursor_detect++) << 24;

                        // Actual check is for 0x7ffffff8, but if we have 0x7ffffff7 in the size
                        // field, it will be padded to 0x7ffffff8.  We can't add the padding here
                        // in case we extracted 0xffffffff, which +1 would be 0 and false negative.
                        DEBUG_WRAP(printf("\n----------Chunk Length %x\n", chunk_length));
                        if(chunk_length >= 0x7ffffff7)
                            return RULE_MATCH;

                        // ckData is padded to the nearest 2 byte boundary, this padding is not
                        // included in the ckLength field, adding padding bytes to chunk_length
                        // so we are aligned correctly.
                        chunk_length += chunk_length % 2;

                        cursor_temp = cursor_detect + chunk_length + 4; 

                        // check for int overflow
                        if(cursor_temp < cursor_detect) 
                           cursor_detect = end_of_payload; // faking it to get to outer loop
                        else 
                           cursor_detect = cursor_temp;

                        total_length += chunk_length + 4; // 4 is chunk name length
                     }
                 }
            }
        }
    }
    return RULE_NOMATCH;
}

/*
Rule *rules[] = {
    &rule15857,
    NULL
};
*/

