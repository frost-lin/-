# -*- coding: UTF-8 -*-
'''
@Project ：人机界面搭建
@File ：ten_csv.py
@IDE  ：PyCharm
@Author ：JackYang
@Date ：22/11/11 18:07
'''
import serial
import numpy as np
import csv
import datetime

file_time = datetime.datetime.now().strftime('%Y-%m-%d %H-%M-%S')
# print(file_time)

# csv表格设置
# 足底表格
foot_header = ['time', 'L[0/0]', 'L[0/1]', 'L[0/2]',
               'L[1/0]', 'L[1/1]', 'L[1/2]', 'L[1/3]', 'L[1/4]',
               'L[2/0]', 'L[2/1]', 'L[2/2]', 'L[2/3]', 'L[2/4]', 'L[2/5]',
               'L[3/0]', 'L[3/1]', 'L[3/2]', 'L[3/3]', 'L[3/4]', 'L[3/5]',
               'L[4/0]', 'L[4/1]', 'L[4/2]', 'L[4/3]', 'L[4/4]', 'L[4/5]',
               'L[5/0]', 'L[5/1]', 'L[5/2]', 'L[5/3]', 'L[5/4]',
               'L[6/0]', 'L[6/1]', 'L[6/2]', 'L[6/3]', 'L[6/4]',
               'L[7/0]', 'L[7/1]', 'L[7/2]', 'L[7/3]', 'L[7/4]',
               'L[8/0]', 'L[8/1]', 'L[8/2]', 'L[8/3]', 'L[8/4]',
               'L[9/0]', 'L[9/1]', 'L[9/2]', 'L[9/3]', 'L[9/4]',
               'L[10/0]', 'L[10/1]', 'L[10/2]', 'L[10/3]', 'L[10/4]',
               'L[11/0]', 'L[11/1]', 'L[11/2]', 'L[11/3]', 'L[11/4]',
               'L[12/0]', 'L[12/1]', 'L[12/2]', 'L[12/3]', 'L[12/4]',
               'L[13/0]', 'L[13/1]', 'L[13/2]', 'L[13/3]', 'L[13/4]',
               'L[14/0]',
               '', 'R[0/0]', 'R[0/1]', 'R[0/2]',
               'R[1/0]', 'R[1/1]', 'R[1/2]', 'R[1/3]', 'R[1/4]',
               'R[2/0]', 'R[2/1]', 'R[2/2]', 'R[2/3]', 'R[2/4]', 'R[2/5]',
               'R[3/0]', 'R[3/1]', 'R[3/2]', 'R[3/3]', 'R[3/4]', 'R[3/5]',
               'R[4/0]', 'R[4/1]', 'R[4/2]', 'R[4/3]', 'R[4/4]', 'R[4/5]',
               'R[5/0]', 'R[5/1]', 'R[5/2]', 'R[5/3]', 'R[5/4]',
               'R[6/0]', 'R[6/1]', 'R[6/2]', 'R[6/3]', 'R[6/4]',
               'R[7/0]', 'R[7/1]', 'R[7/2]', 'R[7/3]', 'R[7/4]',
               'R[8/0]', 'R[8/1]', 'R[8/2]', 'R[8/3]', 'R[8/4]',
               'R[9/0]', 'R[9/1]', 'R[9/2]', 'R[9/3]', 'R[9/4]',
               'R[10/0]', 'R[10/1]', 'R[10/2]', 'R[10/3]', 'R[10/4]',
               'R[11/0]', 'R[11/1]', 'R[11/2]', 'R[11/3]', 'R[11/4]',
               'R[12/0]', 'R[12/1]', 'R[12/2]', 'R[12/3]', 'R[12/4]',
               'R[13/0]', 'R[13/1]', 'R[13/2]', 'R[13/3]', 'R[13/4]',
               'R[14/0]'
               ]
foot_csv = open('foot_data' + file_time + '.csv', 'w', encoding='UTF8', newline='')
foot_writer = csv.writer(foot_csv)
foot_writer.writerow(foot_header)

# 光电表格
light_header = ['time', 'L1', 'L2', 'R1', 'R2']
light_csv = open('light_data' + file_time + '.csv', 'w', encoding='UTF8', newline='')
light_writer = csv.writer(light_csv)
light_writer.writerow(light_header)

# 串口设置
portx = "COM6"
bps = 9600

# 超时设置,None：永远等待操作，0为立即返回请求结果，其他值为等待超时时间(单位为秒）
timex = None
ser = serial.Serial(portx, bps, timeout=timex)

# 标志位，表示数据序号
sign = 0
while 1:
    # data = recv(ser)
    data = ser.read(size=151).hex()
    # print(data)

    # 判断数据头，对齐数据
    while data[0:4] != '97fa':
        ser.read(size=2)
        data = ser.read(size=151).hex()
        if data[0:4] == '97fa':
            break

    leng = int(data[0:2], 16)

    if data != b'' and data[2:4] == 'fa' and len(data) >= leng:

        try:
            str_list = list(data)
            str_list = str_list[6:len(str_list)]
            index = 0
            for i in range(73):
                str_list.insert(2 * i + 4 + index, ' ')
                index += 3
            dataprocess = ''.join(str_list)
            dlist = dataprocess.strip(' ').split(' ')
            # print(dlist)
            for i in range(len(dlist)):
                dlist[i] = int(int(dlist[i], 16) / 16)
            darr = np.array(dlist)
            print(darr)

            # 时间戳
            timestr = datetime.datetime.now().strftime('%M:%S.%f')
            timestrde = timestr[0: 8]

            foot_newrow = []
            foot_newrow.append(timestr)
            for i in range(0, 72):
                foot_newrow.append(darr[i])

            light_newrow = []
            light_newrow.append(timestr)
            for i in range(72, 74):
                light_newrow.append(darr[i])

            foot_writer.writerow(foot_newrow)
            light_writer.writerow(light_newrow)
            sign += 1

        except:
            pass

    # 设置写入的数据个数
    if sign == 100:
        break

foot_csv.close()
light_csv.close()


'''
foot_header = ['time', 'a[0/0]', 'a[0/1]', 'a[0/2]',
          'a[1/0]', 'a[1/1]', 'a[1/2]', 'a[1/3darr[0：71]`]', 'a[1/4]',
          'a[2/0]',	'a[2/1]', 'a[2/2]',	'a[2/3]', 'a[2/4]', 'a[2/5]',
          'a[3/0]', 'a[3/1]', 'a[3/2]', 'a[3/3]', 'a[3/4]', 'a[3/5]',
          'a[4/0]',	'a[4/1]', 'a[4/2]', 'a[4/3]', 'a[4/4]',	'a[4/5]',
          'a[5/0]',	'a[5/1]', 'a[5/2]',	'a[5/3]', 'a[5/4]',
          'a[6/0]', 'a[6/1]', 'a[6/2]',	'a[6/3]', 'a[6/4]',
          'a[7/0]',	'a[7/1]', 'a[7/2]',	'a[7/3]', 'a[7/4]',
          'a[8/0]',	'a[8/1]', 'a[8/2]', 'a[8/3]', 'a[8/4]',
          'a[9/0]', 'a[9/1]', 'a[9/2]',	'a[9/3]', 'a[9/4]',
          'a[10/0]', 'a[10/1]',	'a[10/2]', 'a[10/3]', 'a[10/4]',
          'a[11/0]', 'a[11/1]',	'a[11/2]', 'a[11/3]', 'a[11/4]',
          'a[12/0]', 'a[12/1]',	'a[12/2]', 'a[12/3]', 'a[12/4]',
          'a[13/0]', 'a[13/1]', 'a[13/2]', 'a[13/3]', 'a[13/4]',
          'a[14/0]'
]
'''
