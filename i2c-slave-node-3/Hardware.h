
// This is a guard condition so that contents of this file are not included
// more than once.  
#ifndef __HARDWARE_H
#define	__HARDWARE_H

#include <xc.h> // include processor files - each processor file is guarded.  




void intOsc8Mhz() {
    SCS = 1;
    IRCF2 = 1;
    IRCF1 = 1;
    IRCF0 = 1;
    OSTS = 0;
    HTS = 1;
}
#endif	/* XC_HEADER_TEMPLATE_H */
