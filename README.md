# I2C_memory_slave
## setup
In the picture below you see the setup that is needed to run this code. The mbed is connected to the raspberry pi via I2C.   
![setup](/images/setup.jpg "setup")
## output
This is the output we get when we run the program. There are 4 values written to each adress. the first to values are a value between 0 and 9, the two last values are a value between 0 and 16.The four values are represented as one big value, as shown below.
![output1](/images/output1.JPG "output1")  
In this program we send a random generated number to the flash ship followed by a fixed number 2. you can see this in the following picture.  
![output2](/images/output2.JPG "output2")  
We end the program with a clear that deletes all the values inside the flash chip. You can see this in the picture below.  
![output3](/images/output3.JPG "output3")