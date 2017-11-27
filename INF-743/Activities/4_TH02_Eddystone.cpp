/*
 * Author: Yevgeniy Kiveisha <yevgeniy.kiveisha@intel.com>
 * Copyright (c) 2014 Intel Corporation.
 *
 * Permission is hereby granted, free of charge, to any person obtaining
 * a copy of this software and associated documentation files (the
 * "Software"), to deal in the Software without restriction, including
 * without limitation the rights to use, copy, modify, merge, publish,
 * distribute, sublicense, and/or sell copies of the Software, and to
 * permit persons to whom the Software is furnished to do so, subject to
 * the following conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE
 * LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION
 * OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION
 * WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

/*
Instrunctions:

Installing libs on Edison
    echo "src intel-iotdk https://iotdk.intel.com/repos/3.5/intelgalactic/opkg/i586/" > /etc/opkg/intel-iotdk.conf
    opkg update
    opkg upgrade mraa upm

Compiling the example
    g++ TH02_Eddystone.c -lmraa -lupm-th02 -o example -I/usr/include/upm
*/

#include <unistd.h>
#include <iostream>
#include <th02.hpp>
#include <signal.h>

int doWork = 0;
upm::TH02 *sensor = NULL;

void sig_handler(int signo)
{
    printf("got signal\n");
    if (signo == SIGINT) {
        printf("exiting application\n");
        doWork = 1;
    }
}

void updateEddystoneInfo(float temperature)
{
    // TODO: Change the system command to update the Eddystone TML beacon
    //       Including the TLM uptime, broadcast counter, and temperature
    system("hcitool -i hci0 cmd 0x08 0x0008 1a 02 01 06 03 03 aa fe 11 16 \
        aa fe 20 00 00 00 00 00 00 00 00 00 00 00 00 00 >/dev/null 2>&1");
}

int main(int argc, char **argv)
{

    system("rfkill unblock bluetooth >/dev/null 2>&1");
    system("killall bluetoothd >/dev/null 2>&1");
    system("sleep 2 >/dev/null 2>&1");
    system("hciconfig hci0 up >/dev/null 2>&1");
    system("hciconfig hci0 leadv 3 >/dev/null 2>&1");
    //! [Interesting]
    float temperature = 0.0;
    float humidity = 0.0;
    sensor = new upm::TH02 ();

    while (!doWork) {
        temperature = sensor->getTemperature ();
        humidity = sensor->getHumidity ();
        std::cout << "Temperature = " << temperature << ", Humidity = "
        << humidity << std::endl;
        updateEddystoneInfo(temperature);
        usleep (500000);
    }
    //! [Interesting]

    std::cout << "exiting application" << std::endl;

    delete sensor;

    return 0;
}
