#include <unistd.h>
#include <stdio.h>
#include "Intel_Edison_BT_SPP.h"

Intel_Edison_BT_SPP spp = Intel_Edison_BT_SPP();

int main(){
        printf("Intel Edison BT SPP test!");
        spp.open();

        while(1){
                ssize_t size = spp.read();
                if (size != -1) {
                        printf(spp.getBuf());
                } else {
                        // Well, some error here 
                        usleep(10000000);
                }
        }
        return 0;
}
