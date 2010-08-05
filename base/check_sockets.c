/***
 * Monitoring Plugin - check_sockets
 **
 *
 * check_sockets - Check number of open Sockets.
 * Copyright (C) 2010 Marius Rieder <marius.rieder@durchmesser.ch>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software Foundation,
 * Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
 *
 * $Id$
 */

const char *progname  = "check_sockets";
const char *progvers  = "0.1";
const char *progcopy  = "2010";
const char *progauth = "Marius Rieder <marius.rieder@durchmesser.ch>";
const char *progusage = "--tcp <PORT> [-w <warning count>] [-c <critical count>]";

#include "mp_common.h"

#include <errno.h>
#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <pwd.h>
#include <grp.h>
#include <time.h>

/* Global vars */
int tcpport = -1;
int udpport = -1;
int rawport = -1;
int ipv4 = 1;
int ipv6 = 1;
thresholds *socket_thresholds = NULL;

/* function prototype */
int countSocket(const char *filename, int port);

int main (int argc, char **argv) {

    int         count;
    int         status = STATE_OK;
    int         lstatus;
    char        *output = NULL;

    /* Set Default range */
    setWarnTime(&socket_thresholds, "1000");
    setCritTime(&socket_thresholds, "1024");

    /* Parse argumens */
    if (process_arguments (argc, argv) == 1)
        exit(STATE_CRITICAL);

    if (tcpport < 0 && udpport < 0 && rawport < 0)
        usage("--tcp, --udp or --raw mandatory.");

    if (mp_verbose) {
        printf("IPv4/6: %d %d\n",ipv4, ipv6);
        printf("TCP: %d\n", tcpport);
        printf("UDP: %d\n", udpport);
        printf("RAW: %d\n", rawport);
    }

    if (tcpport >=0) {
        if(ipv4 > 0) {
            count = countSocket("tcp",tcpport);
            if (count >= 0) {
                lstatus = get_status(count, socket_thresholds);
                if (mp_showperfdata)
                    perfdata_int("tcp", count, "", socket_thresholds->warning->end ,
                            socket_thresholds->critical->end, 0, 1024);
            } else {
                lstatus = STATE_UNKNOWN;
            }

            switch (lstatus) {
                case STATE_WARNING:
                    mp_strcat_comma(&output, "tcp warning");
                    status = STATE_CRITICAL != status ? lstatus : status;
                    break;
                case STATE_CRITICAL:
                    mp_strcat_comma(&output, "tcp critical");
                    status = lstatus;
                    break;
                case STATE_UNKNOWN:
                    mp_strcat_comma(&output, "Can't read tcp!");
                    status = STATE_OK == status ? lstatus : status;
                    break;
            }
        }
        if(ipv6 > 0) {
            count = countSocket("tcp6",tcpport);
            if (count >= 0) {
                lstatus = get_status(count, socket_thresholds);
                if (mp_showperfdata)
                    perfdata_int("tcp6", count, "", socket_thresholds->warning->end ,
                            socket_thresholds->critical->end, 0, 1024);
            } else {
                lstatus = STATE_UNKNOWN;
            }

            switch (lstatus) {
                case STATE_WARNING:
                    mp_strcat_comma(&output, "tcp6 warning");
                    status = STATE_CRITICAL != status ? lstatus : status;
                    break;
                case STATE_CRITICAL:
                    mp_strcat_comma(&output, "tcp6 critical");
                    break;
                case STATE_UNKNOWN:
                    mp_strcat_comma(&output, "Can't read tcp6!");
                    status = STATE_OK == status ? lstatus : status;
                    break;
            }
        }
    }
    if (udpport >=0) {
        if(ipv4 > 0) {
            count = countSocket("udp",udpport);
            if (count >= 0) {
                lstatus = get_status(count, socket_thresholds);
                if (mp_showperfdata)
                    perfdata_int("udp", count, "", socket_thresholds->warning->end ,
                            socket_thresholds->critical->end, 0, 1024);
            } else {
                lstatus = STATE_UNKNOWN;
            }

            switch (lstatus) {
                case STATE_WARNING:
                    mp_strcat_comma(&output, "udp warning");
                    status = STATE_CRITICAL != status ? lstatus : status;
                    break;
                case STATE_CRITICAL:
                    mp_strcat_comma(&output, "udp critical");
                    status = lstatus;
                    break;
                case STATE_UNKNOWN:
                    mp_strcat_comma(&output, "Can't read udp!");
                    status = STATE_OK == status ? lstatus : status;
                    break;
            }
        }
        if(ipv6 > 0) {
            count = countSocket("udp6",udpport);
            if (count >= 0) {
                lstatus = get_status(count, socket_thresholds);
                if (mp_showperfdata)
                    perfdata_int("udp", count, "", socket_thresholds->warning->end ,
                            socket_thresholds->critical->end, 0, 1024);
            } else {
                lstatus = STATE_UNKNOWN;
            }

            switch (lstatus) {
                case STATE_WARNING:
                    mp_strcat_comma(&output, "udp6 warning");
                    status = STATE_CRITICAL != status ? lstatus : status;
                    break;
                case STATE_CRITICAL:
                    mp_strcat_comma(&output, "udp6 critical");
                    status = lstatus;
                    break;
                case STATE_UNKNOWN:
                    mp_strcat_comma(&output, "Can't read udp6!");
                    status = STATE_OK == status ? lstatus : status;
                    break;
            }
        }
    }
    if (rawport >=0) {
        if(ipv4 > 0) {
            count = countSocket("raw",rawport);
            if (count >= 0) {
                lstatus = get_status(count, socket_thresholds);
                if (mp_showperfdata)
                    perfdata_int("raw", count, "", socket_thresholds->warning->end ,
                            socket_thresholds->critical->end, 0, 1024);
            } else {
                lstatus = STATE_UNKNOWN;
            }

            switch (lstatus) {
                case STATE_WARNING:
                    mp_strcat_comma(&output, "raw warning");
                    status = STATE_CRITICAL != status ? lstatus : status;
                    break;
                case STATE_CRITICAL:
                    mp_strcat_comma(&output, "raw critical");
                    status = lstatus;
                    break;
                case STATE_UNKNOWN:
                    mp_strcat_comma(&output, "Can't read raw!");
                    status = STATE_OK == status ? lstatus : status;
                    break;
            }
        }
        if(ipv6 > 0) {
            count = countSocket("raw6",rawport);
            if (count >= 0) {
                lstatus = get_status(count, socket_thresholds);
                if (mp_showperfdata)
                    perfdata_int("raw6", count, "", socket_thresholds->warning->end ,
                            socket_thresholds->critical->end, 0, 1024);
            } else {
                lstatus = STATE_UNKNOWN;
            }

            switch (lstatus) {
                case STATE_WARNING:
                    mp_strcat_comma(&output, "raw6 warning");
                    status = STATE_CRITICAL != status ? lstatus : status;
                    break;
                case STATE_CRITICAL:
                    mp_strcat_comma(&output, "raw6 critical");
                    status = lstatus;
                    break;
                case STATE_UNKNOWN:
                    mp_strcat_comma(&output, "Can't read raw6!");
                    status = STATE_OK == status ? lstatus : status;
                    break;
            }
        }
    }

    switch (status) {
        case STATE_OK:
            ok("Everithing ok.");
        case STATE_WARNING:
            warning(output);
        case STATE_CRITICAL:
            critical(output);
        case STATE_UNKNOWN:
            unknown(output);
    }

    critical("You should never reach this point.");
}

int countSocket(const char *filename, int port) {
    FILE *input;
    char buffer[256];
    char *c, *next;
    int count = 0;

    input = fopen(filename, "r");
    if (input == NULL)
        return -1;

    fgets(buffer, 256, input);

    while (fgets(buffer, 256, input) != NULL) {
        if (port > 0) {
            next = buffer;
            c = strsep(&next, ":");
            c = strsep(&next, ":");
            c = strsep(&next, " ");
            if(port == strtol(c, NULL, 16)) {
                count++;
            }
        } else {
            count++;
        }
    }
    fclose(input);

    return count;
}

int process_arguments (int argc, char **argv) {
    int c;
    int option = 0;

    static struct option longopts[] = {
        MP_LONGOPTS_DEFAULT,
        {"tcp", required_argument, NULL, (int)'t'},
        {"udp", required_argument, NULL, (int)'u'},
        {"raw", required_argument, NULL, (int)'r'},
        MP_LONGOPTS_WC,
        MP_LONGOPTS_PERF,
        MP_LONGOPTS_END,
    };

    while (1) {
        c = getopt_long(argc, argv, MP_OPTSTR_DEFAULT"t:u:r:c:w:46", longopts, &option);

        if (c == -1 || c == EOF)
            break;

        getopt_default(c);
        getopt_46(c, &ipv4, &ipv6);
        getopt_wc(c, optarg, &socket_thresholds);

        switch (c) {
            case 't':
                if (optarg)
                    tcpport = strtol(optarg,NULL,10);
                else
                    tcpport = 0;
                break;
            case 'u':
                if (optarg)
                    udpport = strtol(optarg,NULL,10);
                else
                    udpport = 0;
                break;
            case 'r':
                if (optarg)
                    rawport = strtol(optarg,NULL,10);
                else
                    rawport = 0;
                break;
        }
    }

    return(OK);
}

void print_help (void) {
    print_revision();
    print_copyright();

    printf("\n");

    printf("Check number of open Sockets.");

    printf("\n\n");

    print_usage();

    print_help_default();
    print_help_46();
    printf(" -t, --tcp=PORT\n");
    printf("      Count TCP sockets on port PORT. Port 0 for all sockets.\n");
    printf(" -u, --udp=PORT\n");
    printf("      Count UDP sockets on port PORT. Port 0 for all sockets.\n");
    printf(" -r, --raw=PORT\n");
    printf("      Count RAW sockets on port PORT. Port 0 for all sockets.\n");
    print_help_warn("socket count", "1000");
    print_help_crit("socket count", "1024");
    print_help_perf();

}

/* vim: set ts=4 sw=4 et syn=c.libdns : */