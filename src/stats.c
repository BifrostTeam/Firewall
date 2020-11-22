#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <inttypes.h>
#include <errno.h>

#include "utils.h"

/**
 * Retrieves the current PPS on an interface based off of the main program.
 * 
 * @param interface The interface to get the total incoming (RX) packets on.
 * @param totpckts A pointer to an unsigned 64-bit integer (uint64_t) representing the last amount of total packets per previous scan.
 * 
 * @return void
 */
void dopps(const char *interface, uint64_t *totpckts)
{
    // Path to RX packets path on Linux file system.
    char path[255];
    sprintf(path, "/sys/class/net/%s/statistics/rx_packets", interface);

    // Retrieve current amount of packets per second and store in pps.
    uint64_t pcktsnow = getstat((const char *)path);      
    uint64_t pps = pcktsnow - *totpckts;

    /* Do stuff with PPS such as reporting it to the back-end. */

    // Update our total packets pointer since we've updated.
    *totpckts = getstat((const char *)path);
}