import serial  # 导入模块
from time import sleep
import serial.tools.list_ports

port_list = list(serial.tools.list_ports.comports())
# print(port_list)
if len(port_list) == 0:
    print('无可用串口')
else:
    for i in range(0, len(port_list)):
        print(port_list[i])

portx = "COM14"
# portx = 'COM'+input("串口号数字")
bps = 9600
# 超时设置,None：永远等待操作，0为立即返回请求结果，其他值为等待超时时间(单位为秒）
timex = None
ser = serial.Serial(portx, bps, timeout=timex)


while 1:
    # data = ser.read()
    data = ser.read(size=147).hex()
    print(data)

    leng = int(data[0:2], 16)
    # print(leng)
    if data != b'' and data[2:4] == 'fa' and len(data) >= leng:
        # len = int(data[0:2], 16)
        # print(len)
        # print(data)
        try:
            print(data[4:6])
            # print(data[6:9])
            # print(int(data[6:9], 16))
            for j in range(0, 9):
                for i in range(0, 8):
                    # print(data[6+4*i+32*j:6+4*i+3+32*j], end=' ')
                    print(int(data[6+4*i+32*j:6+4*i+3+32*j], 16), end=' ')
                print()

        except:
            pass
