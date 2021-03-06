/*
 * Use at your own risk.
 *
 * Copyright (C) 2005-2008 Sourcefire, Inc.
 * 
 * This file is autogenerated via rules2c, by Brian Caswell <bmc@sourcefire.com>

!!! XXX USED AS A BASE FOR DETECTION ONLY XXX !!!

alert tcp $EXTERNAL_NET $HTTP_PORTS -> $HOME_NET any (msg:"WEB-CLIENT RTF control word overflow attempt"; flow:established,to_client; flowbits:isset,file.rtf; content:"|5C|dparc"; nocase; metadata: policy security-ips drop, service http; classtype:attempted-user; reference:cve,2008-1091; reference:url,technet.microsoft.com/en-us/security/bulletin/ms08-026; sid:13803; rev:1;)

 */


#include "sf_snort_plugin_api.h"
#include "sf_snort_packet.h"

//#define DEBUG
#ifdef DEBUG
#define DEBUG_WRAP(code) code
#else
#define DEBUG_WRAP(code)
#endif

typedef struct _TagCount {
    uint16_t total_count;
} TagCount;


/* declare detection functions */
int rule13803eval(void *p);

/* declare rule data structures */
/* precompile the stuff that needs pre-compiled */
/* flow:established, to_client; */
static FlowFlags rule13803flow0 = 
{
    FLOW_ESTABLISHED|FLOW_TO_CLIENT //|FLOW_ONLY_REASSMBLED
};

static RuleOption rule13803option0 =
{
    OPTION_TYPE_FLOWFLAGS,
    {
        &rule13803flow0
    }
};
/* flowbits:isset "file.rtf"; */
static FlowBitsInfo rule13803flowbits1 =
{
    "file.rtf",
    FLOWBIT_ISSET,
    0,
};

static RuleOption rule13803option1 =
{
    OPTION_TYPE_FLOWBIT,
    {
        &rule13803flowbits1
    }
};
// content:"|5C|dparc", nocase; 
static ContentInfo rule13803content2 = 
{
    (uint8_t *) "|5C|dparc", /* pattern (now in snort content format) */
    0, /* depth */
    0, /* offset */
    CONTENT_NOCASE|CONTENT_BUF_NORMALIZED|CONTENT_RELATIVE, /* flags */ // XXX - need to add CONTENT_FAST_PATTERN support
    NULL, /* holder for boyer/moore PTR */
    NULL, /* more holder info - byteform */
    0, /* byteform length */
    0 /* increment length*/
};

static RuleOption rule13803option2 = 
{
    OPTION_TYPE_CONTENT,
    {
        &rule13803content2
    }
};

/* references for sid 13803 */
/* reference: cve "2008-1091"; */
static RuleReference rule13803ref1 = 
{
    "cve", /* type */
    "2008-1091" /* value */
};

/* reference: url "technet.microsoft.com/en-us/security/bulletin/ms08-026"; */
static RuleReference rule13803ref2 = 
{
    "url", /* type */
    "technet.microsoft.com/en-us/security/bulletin/ms08-026" /* value */
};

static RuleReference *rule13803refs[] =
{
    &rule13803ref1,
    &rule13803ref2,
    NULL
};
/* metadata for sid 13803 */
/* metadata:service http, policy security-ips drop; */
static RuleMetaData rule13803service1 = 
{
    "service http"
};


//static RuleMetaData rule13803policy1 = 
//{
//    "policy security-ips drop"
//};


static RuleMetaData *rule13803metadata[] =
{
    &rule13803service1,
//    &rule13803policy1,
    NULL
};
RuleOption *rule13803options[] =
{
    &rule13803option0,
    &rule13803option1,
    &rule13803option2,
    NULL
};

Rule rule13803 = {
   
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
       3,  /* genid (HARDCODED!!!) */
       13803, /* sigid */
       11, /* revision */
   
       "attempted-user", /* classification */
       0,  /* hardcoded priority XXX NOT PROVIDED BY GRAMMAR YET! */
       "FILE-OFFICE RTF control word overflow attempt",     /* message */
       rule13803refs /* ptr to references */
       ,rule13803metadata
   },
   rule13803options, /* ptr to rule options */
   &rule13803eval, /* use the built in detection function */
   0 /* am I initialized yet? */
};

/* detection functions */
int rule13803eval(void *p) {
    const uint8_t *cursor_normal = 0, *end_of_payload = 0;
    SFSnortPacket *sp = (SFSnortPacket *) p;

    uint32_t count = 0;

    TagCount *tagcount;

    DEBUG_WRAP(printf("rule13803eval: enter\n"));

    if((sp == NULL) || (sp->stream_session_ptr == NULL))
        return RULE_NOMATCH;

    if(sp->payload == NULL)
        return RULE_NOMATCH;

    // flow:established, to_client;
    if (checkFlow(p, rule13803options[0]->option_u.flowFlags) > 0 ) {
        // flowbits:isset "file.rtf";
        if (processFlowbits(p, rule13803options[1]->option_u.flowBit) > 0) {
        
            if(getBuffer(sp, CONTENT_BUF_NORMALIZED, &cursor_normal, &end_of_payload) <= 0)
               return RULE_NOMATCH;

            tagcount = (TagCount *)getRuleData(sp, (uint32_t)rule13803.info.sigID);

            if(!tagcount) {
               tagcount = (TagCount *)allocRuleData(sizeof(TagCount));
               if (tagcount == NULL)
                  return RULE_NOMATCH;

               if(storeRuleData(sp, tagcount, rule13803.info.sigID, &freeRuleData) < 0)
               {
                  freeRuleData(tagcount);
                  return RULE_NOMATCH;
               }

               tagcount->total_count = 0;
            }
        
            DEBUG_WRAP(printf("rule13803eval: checking stored value (%d)\n", tagcount->total_count));
        
            if(tagcount->total_count >= 150)
               return RULE_NOMATCH;

            // content:"|5C|dparc", nocase;
            while(contentMatch(p, rule13803options[2]->option_u.content, &cursor_normal) > 0) {
               count++;
               DEBUG_WRAP(printf("rule13803eval: incremented count (%d)\n", count));
            }

            tagcount->total_count += count;

            DEBUG_WRAP(printf("rule13803eval: total_count=%d\n", tagcount->total_count));

            if(tagcount->total_count >= 150)
               return RULE_MATCH;
        }
    } 

    return RULE_NOMATCH;
}

/*
Rule *rules[] = {
    &rule13803,
    NULL
};
*/

