# I2C_memory_slave
## setup
In the picture below you see the setup that is needed to run this code. The mbed is connected to the raspberry pi via I2C.   
![setup](/images/setup.jpg "setup")
## output
This is the output we get when we run the program. There are 4 values written to each adress. the first to values are a value between 0 and 9, the two last values are a value between 0 and 15.The four values are represented as one big value, as shown below.   
![output1](/images/output1.JPG "output1")  
This is the output we get on the pi when we read the values from the flash chip. Now you can see that the first to values are values between 0 and 9. The values three and four are values between 0 and 115. But when the value is 10, we get an "a" as output. so 10 = "a", 11 = "b", ..., 15 = "f".
![output2](/images/output2.JPG "output2")  
At the and of the program we clear the flash chip and print the values to the computer via a serial communication as shown below.   
![output3](/images/output3.JPG "output3")