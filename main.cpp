// Compile using g++ -std=c++11 main.cpp -o i2c
#include <iostream>
#include <unistd.h>   // close
#include <fcntl.h>    // O_RDWR
#include <sys/ioctl.h>
#include <linux/i2c-dev.h>  // I2C_SLAVE
#include <chrono>
#include <thread>
#include <stdio.h>      /* printf, scanf, puts, NULL */
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */

using namespace std;

    int main(void) {
    const std::string DEVICE = "/dev/i2c-1";
    const unsigned int BUFFER_SIZE = 5;

    srand (time(NULL));

    int i2cfile;
    if ((i2cfile = open(DEVICE.c_str(), O_RDWR)) < 0) {
        cout << "Could not open bus" << endl;
        exit(1);
    }
    cout << "Successfully opened the i2c bus" << endl;

    const int SLAVE_ADDRESS = 0x14;          // The I2C address of the slave device
    if (ioctl(i2cfile, I2C_SLAVE, SLAVE_ADDRESS) < 0) {
        cout << "Failed to acquire bus access and/or talk to slave." << endl;
        exit(1);
    }
    cout << "Ready to communicate with slave device" << endl;

    char adress_buffer[32] = { 0x00, 0x01, 0x02, 0x03,
                                0x04, 0x05, 0x06, 0x07,
                                0x08, 0x09, 0x0a, 0x0b,
                                0x0c, 0x0d, 0x0e, 0x0f,
                                0x10, 0x11, 0x12, 0x13,
                                0x14, 0x15, 0x16, 0x17,
                                0x18, 0x19, 0x1a, 0x1b,
                                0x1c, 0x1d, 0x1e, 0x1f
                            };
    

    for (int i = 0; i < 32; i++){
        int rand1 = rand() % 9;
        int rand2 = rand() % 9;
        const char char_max = -1;
        char rand_1 = (rand1 & char_max);
        char rand_2 = (rand2 & char_max);
        char send_buffer[6] = { 0x00, adress_buffer[i], rand_1, 2, 0, 0 };
        write(i2cfile, send_buffer, 6) != 6;
    }

    std::this_thread::sleep_for(std::chrono::milliseconds(1000));

    char print_buffer[] = { 0x03 };
    if (write(i2cfile, print_buffer, 1) != 1) {
        cout << "Successfully wrote to the i2c device." << endl;
    } else {
        cout << "Failed to write to the i2c device." << endl;
    }

    std::this_thread::sleep_for(std::chrono::milliseconds(1000));

for (int i = 0; i < 32; i++){
    char pull_buffer[BUFFER_SIZE] = { 0x01, adress_buffer[i] };
    write(i2cfile, pull_buffer, 2);
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    if (read(i2cfile, pull_buffer, 5) != 5) {
        cout << "Failed to read from the i2c device." << endl;
    } else {
        for (int i = 0; i < 5; i++){
            if (i == 0){
                cout << std::hex << "Adress: 0x" << (int)pull_buffer[i] << " bevat de data : ";   
                std::this_thread::sleep_for(std::chrono::milliseconds(100));
            }else if(i == 4){
                cout << (int)pull_buffer[i] << endl;
            }else{
                cout << (int)pull_buffer[i] << ", ";
            }
        }
    }
}
    
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));

    char clear_buffer[] = { 0x02 };
    if (write(i2cfile, clear_buffer, 1) != 1) {
        cout << "Successfully cleared the i2c device." << endl;
    } else {
        cout << "Failed to clear the i2c device." << endl;
    }

    std::this_thread::sleep_for(std::chrono::milliseconds(1000));

    if (write(i2cfile, print_buffer, 1) != 1) {
        cout << "Successfully wrote to the i2c device." << endl;
    } else {
        cout << "Failed to write to the i2c device." << endl;
    }
    
  close(i2cfile);
  return 0;
}