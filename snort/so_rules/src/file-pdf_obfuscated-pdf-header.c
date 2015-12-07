/*
 * Use at your own risk.
 *
 * Copyright (C) 2005-2008 Sourcefire, Inc.
 * 
 * This file is autogenerated via rules2c, by Brian Caswell <bmc@sourcefire.com>
 */


#include "sf_snort_plugin_api.h"
#include "sf_snort_packet.h"

#include <ctype.h>

/* declare detection functions */
int rule16343eval(void *p);
int rule23180eval(void *p);

/* declare rule data structures */
/* precompile the stuff that needs pre-compiled */
/* flow:established, to_client; */
static FlowFlags rule16343flow0 = 
{
    FLOW_ESTABLISHED|FLOW_TO_CLIENT
};

static RuleOption rule16343option0 =
{
    OPTION_TYPE_FLOWFLAGS,
    {
        &rule16343flow0
    }
};

/* flowbits:isset "file.pdf"; */
static FlowBitsInfo rule16343flowbits1 =
{
    "file.pdf",
    FLOWBIT_ISSET,
    0,
};

static RuleOption rule16343option1 =
{
    OPTION_TYPE_FLOWBIT,
    {
        &rule16343flowbits1
    }
};
#ifndef CONTENT_FAST_PATTERN
#define CONTENT_FAST_PATTERN 0
#endif
// content:"obj", depth 0, nocase, fast_pattern; 
static ContentInfo rule16343content2 = 
{
    (uint8_t *) "obj", /* pattern (now in snort content format) */
    0, /* depth */
    0, /* offset */
    CONTENT_RELATIVE|CONTENT_NOCASE|CONTENT_BUF_NORMALIZED, /* flags */
    NULL, /* holder for boyer/moore PTR */
    NULL, /* more holder info - byteform */
    0, /* byteform length */
    0 /* increment length*/
};

static RuleOption rule16343option2 = 
{
    OPTION_TYPE_CONTENT,
    {
        &rule16343content2
    }
};

// content:"<<", payload raw, depth 4, relative; 
static ContentInfo rule16343content3 = 
{
    (uint8_t *) "<<", /* pattern (now in snort content format) */
    4, /* depth */
    0, /* offset */
    CONTENT_RELATIVE|CONTENT_BUF_NORMALIZED, /* flags */
    NULL, /* holder for boyer/moore PTR */
    NULL, /* more holder info - byteform */
    0, /* byteform length */
    0 /* increment length*/
};

static RuleOption rule16343option3 = 
{
    OPTION_TYPE_CONTENT,
    {
        &rule16343content3
    }
};

// content:"<<", payload raw, depth 4, relative; 
static ContentInfo rule16343content4 =
{
    (uint8_t *) "HTTP/1.1 206", /* pattern (now in snort content format) */
    12, /* depth */
    0, /* offset */
    CONTENT_BUF_NORMALIZED, /* flags */
    NULL, /* holder for boyer/moore PTR */
    NULL, /* more holder info - byteform */
    0, /* byteform length */
    0 /* increment length*/
};

static RuleOption rule16343option4 =
{
    OPTION_TYPE_CONTENT,
    {
        &rule16343content4
    }
};

// content:"|25|PDF-", payload raw; 
static ContentInfo rule16343content5 =
{
    (uint8_t *) "|25|PDF-", /* pattern (now in snort content format) */
    0, /* depth */
    0, /* offset */
    CONTENT_BUF_NORMALIZED|CONTENT_FAST_PATTERN, /* flags */
    NULL, /* holder for boyer/moore PTR */
    NULL, /* more holder info - byteform */
    0, /* byteform length */
    0 /* increment length*/
};

static RuleOption rule16343option5 =
{
    OPTION_TYPE_CONTENT,
    {
        &rule16343content5
    }
};

#ifndef MISSINGFILEDATA
static CursorInfo rule16343cursor6 =
{
   0,
   CONTENT_BUF_NORMALIZED
};

static RuleOption rule16343option6 =
{
   OPTION_TYPE_FILE_DATA,
   {
      &rule16343cursor6
   }
};
#endif

// content:"/Type /Font", payload raw; nocase; distance:0; within:20;
static ContentInfo rule16343content6 =
{
    (uint8_t *) "/Type /Font", /* pattern (now in snort content format) */
    20, /* depth */
    0, /* offset */
    CONTENT_RELATIVE|CONTENT_NOCASE|CONTENT_BUF_NORMALIZED, /* flags */
    NULL, /* holder for boyer/moore PTR */
    NULL, /* more holder info - byteform */
    0, /* byteform length */
    0 /* increment length*/
};

static RuleOption rule16343option7 =
{
    OPTION_TYPE_CONTENT,
    {
        &rule16343content6
    }
};

/* references for sid 16343 */
/* reference: url "www.adobe.com/devnet/acrobat/pdfs/PDF32000_2008.pdf"; */
static RuleReference rule16343ref1 = 
{
    "url", /* type */
    "www.adobe.com/devnet/acrobat/pdfs/PDF32000_2008.pdf" /* value */
};

static RuleReference *rule16343refs[] =
{
    &rule16343ref1,
    NULL
};
/* metadata for sid 16343 */
/* metadata:service http, policy security-ips drop; */
static RuleMetaData rule16343service1 = 
{
    "service http"
};

#ifndef MISSINGFILEDATA
static RuleMetaData rule16343service2 =
{
    "service pop3"
};

static RuleMetaData rule16343service3 =
{
    "service imap"
};
#endif

static RuleMetaData rule16343policy1 = 
{
    "policy security-ips drop"
};

static RuleMetaData rule16343policy2 =  
{
    "policy balanced-ips drop"
};


static RuleMetaData *rule16343metadata[] =
{
    &rule16343service1,
#ifndef MISSINGFILEDATA
    &rule16343service2,
    &rule16343service3,
#endif
    &rule16343policy1,
    &rule16343policy2,
    NULL
};

RuleOption *rule16343options[] =
{
    &rule16343option0,
    &rule16343option1,
    &rule16343option2,
    &rule16343option3,
    &rule16343option4,
    &rule16343option5,
#ifndef MISSINGFILEDATA
    &rule16343option6,
#endif
    &rule16343option7,
    NULL
};

Rule rule16343 = {
   
   /* rule header, akin to => tcp any any -> any any               */{
       IPPROTO_TCP, /* proto */
       "$EXTERNAL_NET", /* SRCIP     */
#ifndef MISSINGFILEDATA
       "$FILE_DATA_PORTS", /* SRCPORT   */
#else
       "$HTTP_PORTS", /* SRCPORT */
#endif
   
       0, /* DIRECTION */
       "$HOME_NET", /* DSTIP     */
   
       "any", /* DSTPORT   */
   },
   /* metadata */
   { 
       3,  /* genid */
       16343, /* sigid */
       12, /* revision */
   
       "misc-activity", /* classification */
       0,  /* hardcoded priority XXX NOT PROVIDED BY GRAMMAR YET! */
       "FILE-PDF obfuscated header in PDF",     /* message */
       rule16343refs /* ptr to references */
       ,rule16343metadata
   },
   rule16343options, /* ptr to rule options */
   &rule16343eval, /* use the built in detection function */
   0 /* am I initialized yet? */
};


static FlowFlags rule23180flow0 =
{
    FLOW_ESTABLISHED|FLOW_TO_SERVER
};

static RuleOption rule23180option0 =
{
    OPTION_TYPE_FLOWFLAGS,
    {
        &rule23180flow0
    }
};

#ifdef MISSINGFILEDATA
static ContentInfo rule16343contentDELETED =
{
    (uint8_t *) "asdf8uasdf89r89q439rq43rafhadf78y48rqy34r87ywef8as7yefa78sfh8a7shdf78", /* pattern (now in snort content format) */
    0, /* depth */
    0, /* offset */
    CONTENT_BUF_NORMALIZED|CONTENT_FAST_PATTERN, /* flags */
    NULL, /* holder for boyer/moore PTR */
    NULL, /* more holder info - byteform */
    0, /* byteform length */
    0 /* increment length*/
};

static RuleOption rule16343optionDELETED =
{
    OPTION_TYPE_CONTENT,
    {
        &rule16343contentDELETED
    }
};
#endif

RuleOption *rule23180options[] =
{
   &rule23180option0,
#ifndef MISSINGFILEDATA
   &rule16343option1, // For flowbit to be put in stub rules file
   &rule16343option5, // For fast_pattern
#else
   &rule16343optionDELETED,
#endif
   NULL
};

static RuleMetaData rule23180service1 =
{
    "service smtp"
};

static RuleMetaData *rule23180metadata[] =
{
#ifndef MISSINGFILEDATA
    &rule23180service1, // Changed service metadata but otherwise the same
    &rule16343policy1,
    &rule16343policy2,
#endif
    NULL
};


Rule rule23180 = {

   /* rule header, akin to => tcp any any -> any any               */{
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
       23180, /* sigid */
       5, /* revision */

       "misc-activity", /* classification */
       0,  /* hardcoded priority XXX NOT PROVIDED BY GRAMMAR YET! */
#ifndef MISSINGFILEDATA
       "FILE-PDF obfuscated header in PDF attachment",     /* message */
#else
       "DELETED FILE-PDF obfuscated header in PDF attachment",     /* message */
#endif
       rule16343refs /* ptr to references */ // same refs
       ,rule23180metadata
   },
   rule23180options, /* ptr to rule options */
#ifndef MISSINGFILEDATA
   &rule23180eval, /* use the built in detection function */
   0 /* am I initialized yet? */
#else
   NULL, /* use the built in detection function */
   1 /* Trick into thinking we are already enabled */
#endif
};



/* detection functions */

int DetectObfuscatedHeader(SFSnortPacket *sp) {
    const uint8_t *cursor_normal = 0;
    const uint8_t *end_of_payload = 0;
    int ascii_flag;
    int hex_flag;
    unsigned long escape_char;
    char escape_buf[3];

#ifndef MISSINGFILEDATA
    // Move to file_data.
    if(fileData(sp, rule16343options[6]->option_u.cursor, &cursor_normal) <= 0) {
        return RULE_NOMATCH;
    }
#endif

    // There is an extra indent here, but it's left to make a prettier diff.
        // flowbits:isset "file.pdf"; || content:"|25|PDF-";
        if (   processFlowbits(sp, rule16343options[1]->option_u.flowBit) > 0 ||
               contentMatch(sp, rule16343options[5]->option_u.content, &cursor_normal) > 0) {

            // If we're in a Partial Content packet, get out to avoid false positives.
            // There are some really stupid packets / multiparts out there and I can't
            // think of a good way to avoid false negatives while avoiding the false
            // positives, so may as well go for broke. 
            // content:"HTTP/1.1 206", depth 12, offset 0; 
            if(contentMatch(sp, rule16343options[4]->option_u.content, &cursor_normal) > 0)
               return RULE_NOMATCH;

            if(getBuffer(sp, CONTENT_BUF_NORMALIZED, &cursor_normal, &end_of_payload) <= 0)
               return RULE_NOMATCH;

            escape_buf[2] = 0x00;  // No need to set this every time as long as it's preset

            // content:"obj", depth 0, nocase, fast_pattern;
            while (contentMatch(sp, rule16343options[2]->option_u.content, &cursor_normal) > 0) {

                // content:"<<", payload raw, depth 4, relative; 
                if (contentMatch(sp, rule16343options[3]->option_u.content, &cursor_normal) <= 0) {
                    continue;
                }

                // content:"/Type /Font", payload raw; nocase; distance:0; within:20;
                // if we are in a font object, skip.
                // hex escaped font names are normal apparently
                if (contentMatch(sp, rule16343options[7]->option_u.content, &cursor_normal) > 0) {
                    continue;
                }

                hex_flag = 0;
                ascii_flag = 0;

                while (cursor_normal < end_of_payload) {

                    // Check for end of object header.  If found, search for new "obj<<" tag
                    if ((*cursor_normal == '>') && 
                              ((cursor_normal + 1 < end_of_payload) && (*(cursor_normal + 1) == '>'))) {
                        break;
                    }

                    if (*cursor_normal == '#') {

                        cursor_normal++; // Skip the #
                        // Make sure we've got the bytes to read
                        if ((cursor_normal + 2 > end_of_payload)) {
                            return RULE_NOMATCH;
                        }
                        escape_buf[0] = *cursor_normal++;
                        escape_buf[1] = *cursor_normal; // The pointer increment is below
                        //escape_buf[2] = 0x00;  No need to set this every time as long as it's preset
                        escape_char = strtoul(escape_buf, NULL, 16);

                        // We only care if the resultant value is alphanumeric
                        if(!isalnum(escape_char))
                           continue;

                        if (ascii_flag == 1) 
                            return RULE_MATCH;

                        hex_flag = 1;

                    } else if (*cursor_normal == '(') { // binary data in object tag

                        cursor_normal++;

                        // Run through to the end of the binary data
                        while(cursor_normal < end_of_payload) {
                           // If we come across a close parens, see if it's escaped.
                           // If not, we're at the end of the binary data.
                           if(*cursor_normal != ')')
                              cursor_normal++;
                           else if(*(cursor_normal - 1) == '\\')
                              cursor_normal++;
                           else
                              break;
                        }

                        // We'll step over the ')' at the end of the while() loop

                    } else {

                        if (isalnum(*cursor_normal)) {

                            if (hex_flag == 1)
                                return RULE_MATCH;

                            ascii_flag = 1;
                        }

                        // Fall through advances the pointer

                    }

                    cursor_normal++; // Ensure we will always advance the pointer
                }
            }
    }
    return RULE_NOMATCH;
}


int rule16343eval(void *p) {
    SFSnortPacket *sp = (SFSnortPacket *) p;

    if(sp == NULL)
        return RULE_NOMATCH;

    if(sp->payload == NULL)
        return RULE_NOMATCH;

    if(checkFlow(p, rule16343options[0]->option_u.flowFlags) <= 0)
        return RULE_NOMATCH;

    return DetectObfuscatedHeader(sp);
}


int rule23180eval(void *p) {
    SFSnortPacket *sp = (SFSnortPacket *) p;

#ifdef MISSINGFILEDATA
    return RULE_NOMATCH;
#endif 

    if(sp == NULL)
        return RULE_NOMATCH;

    if(sp->payload == NULL)
        return RULE_NOMATCH;

    if(checkFlow(p, rule23180options[0]->option_u.flowFlags) <= 0)
        return RULE_NOMATCH;

    return DetectObfuscatedHeader(sp);
}


/*
Rule *rules[] = {
    &rule16343,
    NULL
};
*/
