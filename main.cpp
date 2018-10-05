// Compile using g++ -std=c++11 main.cpp -o i2c
#include <iostream>
#include <unistd.h>   // close
#include <fcntl.h>    // O_RDWR
#include <sys/ioctl.h>
#include <linux/i2c-dev.h>  // I2C_SLAVE
#include <chrono>
#include <thread>

using namespace std;

    int main(void) {
    const std::string DEVICE = "/dev/i2c-1";
    const unsigned int BUFFER_SIZE = 5;

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

    char buffer1[6] = { 0x00, 0x15, 1, 0, 0, 0 };
    if (write(i2cfile, buffer1, 6) != 6) {
        cout << "Failed to write to the i2c device." << endl;
    } else {
        cout << "Successfully wrote to the i2c device." << endl;
    }

    std::this_thread::sleep_for(std::chrono::milliseconds(1000));

    char buffer[] = { 0x03 };
    if (write(i2cfile, buffer, 1) != 1) {
        cout << "Failed to write to the i2c device." << endl;
    } else {
        cout << "Successfully wrote to the i2c device." << endl;
    }

    std::this_thread::sleep_for(std::chrono::milliseconds(1000));


    char buffer2[BUFFER_SIZE] = { 0x01, 0x15 };
    write(i2cfile, buffer2, 2);
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    if (read(i2cfile, buffer2, 2) != 2) {
        cout << "Failed to read from the i2c device." << endl;
    } else {
        cout << "Read from device: " << endl;
        for (int i; i < 5; i++){
            if (i == 0){
                cout << std::hex << "Adress: 0x" << (int)buffer2[i] << endl;   
            }else{
                cout << (int)buffer2[i] << endl;
            }
        }
    }
 
  close(i2cfile);

  return 0;
}