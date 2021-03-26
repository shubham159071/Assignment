import serial
from serial import Serial
ser = serial.Serial('COM1',9600)
data1 = ser.readline(1500)      
print ("\n data from COM1 \n"+data1)
ser = serial.Serial('COM3',9600)
data2 = ser.readline(1500)
print ("\n data from COM3 \n"+data2)
ser = serial.Serial('COM4',9600)
data3 = ser.readline(1500)
print ("\n data from COM4 \n"+data3)
