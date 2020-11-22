#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <string.h>
#include <inttypes.h>
#include <errno.h>

#include "utils.h"

/**
 * Retrieves the current PPS on an interface based off of the main program.
 * 
 * @param interface The interface to get the total incoming (RX) packets on.
 * @param totpckts A pointer to an unsigned 64-bit integer (uint64_t) representing the last amount of total packets per previous scan.
 * @param lastupdate A pointer to the last update timestamp (time_t).
 * 
 * @return void
 */
void dopps(const char *interface, uint64_t *totpckts, time_t *lastupdate)
{
    // Path to RX packets path on Linux file system.
    char path[255];
    sprintf(path, "/sys/class/net/%s/statistics/rx_packets", interface);

    // Get the current time and check if we need to update.
    time_t now = time(NULL);

    if ((now - *lastupdate) > 1)
    {
        // Retrieve current amount of packets per second and store in pps.
        uint64_t pcktsnow = getstat((const char *)path);      
        uint64_t pps = pcktsnow - *totpckts;

        /* Do stuff with PPS such as reporting it to the back-end. */

        // Update our total packets and last update pointers since we've updated.
        *totpckts = getstat((const char *)path);
        *lastupdate = time(NULL);
    }
}