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

    char buffer_adresses[32] = { 0x00, 0x01, 0x02, 0x03,
                                0x04, 0x05, 0x06, 0x07,
                                0x08, 0x09, 0x0a, 0x0b,
                                0x0c, 0x0d, 0x0e, 0x0f,
                                0x10, 0x11, 0x12, 0x13,
                                0x14, 0x15, 0x16, 0x17,
                                0x18, 0x19, 0x1a, 0x1b,
                                0x1c, 0x1d, 0x1e, 0x1f
                            };
    
    for (int i; i < 32; i++){
        char buffer_send[32] = { 0x00, buffer_adresses[i], 5, 0, 0, 0};
        write(i2cfile, buffer_send, 6) != 6;
    }

    std::this_thread::sleep_for(std::chrono::milliseconds(1000));

    char buffer5[] = { 0x03 };
    if (write(i2cfile, buffer5, 1) != 1) {
        cout << "Successfully wrote to the i2c device." << endl;
    } else {
        cout << "Failed to write to the i2c device." << endl;
    }

    std::this_thread::sleep_for(std::chrono::milliseconds(1000));


    char buffer6[BUFFER_SIZE] = { 0x01, 0x00 };
    write(i2cfile, buffer6, 2);
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    if (read(i2cfile, buffer6, 5) != 5) {
        cout << "Failed to read from the i2c device." << endl;
    } else {
        cout << "Read from device: " << endl;
        for (int i; i < 5; i++){
            if (i == 0){
                cout << std::hex << "Adress: 0x" << (int)buffer6[i] << " bevat de data : ";   
            }else if(i == 4){
                cout << (int)buffer6[i] << endl;
            }else{
                cout << (int)buffer6[i] << ", ";
            }
        }
    }
    
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));

    char buffer7[] = { 0x02 };
    if (write(i2cfile, buffer7, 1) != 1) {
        cout << "Successfully cleared the i2c device." << endl;
    } else {
        cout << "Failed to clear the i2c device." << endl;
    }

    std::this_thread::sleep_for(std::chrono::milliseconds(1000));

    if (write(i2cfile, buffer5, 1) != 1) {
        cout << "Successfully wrote to the i2c device." << endl;
    } else {
        cout << "Failed to write to the i2c device." << endl;
    }
    
  close(i2cfile);

  return 0;
}