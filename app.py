# -*- coding: utf-8 -*-
# @Time    : 2022/4/19 16:49
# @Author  : Yuan
# @File    : app.py
from flask import Flask, render_template, request
import os
import json
from flask_cors import *
import serial
import serial.tools.list_ports
import numpy as np
import time
import threading

app = Flask(__name__)
CORS(app, supports_credentials=True)

left_sum = []
right_sum = []
indexs = []
cop_left_sum = []
cop_right_sum = []
data_left_sum = []
data_right_sum = []

class SerialPort:
    def __init__(self, port, brate):
        super(SerialPort, self).__init__()
        self.port = serial.Serial(port, brate)
        self.port.close()

        if not self.port.isOpen():
            self.port.open()

    def port_open(self):
        if not self.port.isOpen():
            self.port.open()

    def port_close(self):
        self.port.close()

    def send_data(self, data):
        n = self.port.write((data + '\n').encode())
        return n

    def read_data(self):
        # switch your send data func
        return get_blue_data(self)


port = "COM23"
brate = 9600


def get_blue_data(serial):
    left_foot = []
    right_foot = []
    cop_left = []
    cop_right = []
    data_left = []
    data_right = []
    index = 0
    while 1:
        # data1 = serial.port.read(size=147).hex()
        # while data1[0:3] != '93fa':
        #     serial.port.read(size=1)
        #     data1 = serial.port.read(size=147).hex()
        #     if data1[0:3] == '93fa':
        #         break
        data1 = serial.port.read(size=147).hex()
        # data2 = serial.port.read(size=147).hex()
        data2 = data1

        leng = int(data1[0:2], 16)
        # num = int(data[4:6], 16)
        time.sleep(1)
        if data1 != b'' and data1[2:4] == 'fa' and len(data1) >= leng:
            try:
                darr1 = data_process(data1)
                left_foot = get_left_form(darr1)  # left_foot
                cop_left = COP_left(darr1)
                data_left = footdata_left(darr1)
            except:
                pass
        if data2 != b'' and data2[2:4] == 'fa' and len(data2) >= leng:
            try:
                darr2 = data_process(data2)
                right_foot = get_right_form(darr2)  # right_foot
                cop_right = COP_right(darr2)
                data_right = footdata_right(darr2)
            except:
                pass
        yield [left_foot, right_foot, cop_left, cop_right, data_left, data_right, index]
        index += 1


def COP_left(darr):
    XC = np.array([0, 9, 18,
                   -9, 0, 9, 18, 27,
                   -18, -9, 0, 9, 18, 27,
                   -18, -9, 0, 9, 18, 27,
                   -18, -9, 0, 9, 18, 27,
                   -18, -9, 0, 9, 18,
                   -18, -9, 0, 9, 18,
                   -18, -9, 0, 9, 18,
                   -18, -9, 0, 9, 18,
                   -18, -9, 0, 9, 18,
                   -18, -9, 0, 9, 18,
                   -18, -9, 0, 9, 18,
                   -18, -9, 0, 9, 18,
                   -18, -9, 0, 9, 18,
                   0])

    YC = np.array([210, 210, 210,
                   195, 195, 195, 195, 195,
                   180, 180, 180, 180, 180, 180,
                   165, 165, 165, 165, 165, 165,
                   150, 150, 150, 150, 150, 150,
                   135, 135, 135, 135, 135,
                   120, 120, 120, 120, 120,
                   105, 105, 105, 105, 105,
                   90, 90, 90, 90, 90,
                   75, 75, 75, 75, 75,
                   60, 60, 60, 60, 60,
                   45, 45, 45, 45, 45,
                   30, 30, 30, 30, 30,
                   15, 15, 15, 15, 15,
                   0])
    # 移轴
    XCts = np.full_like(XC, -3)
    YCts = np.full_like(YC, 3)
    XC = XC + XCts
    YC = YC + YCts

    sumf = np.sum(darr)
    sumxf = np.sum(XC * darr)
    sumyf = np.sum(YC * darr)

    cop = np.array([sumxf / sumf, sumyf / sumf])
    return cop


def COP_right(darr):
    XC = np.array([-18, -9, 0,
                   -27, -18, -9, 0, 9,
                   -27, -18, -9, 0, 9, 18,
                   -27, -18, -9, 0, 9, 18,
                   -27, -18, -9, 0, 9, 18,
                   -18, -9, 0, 9, 18,
                   -18, -9, 0, 9, 18,
                   -18, -9, 0, 9, 18,
                   -18, -9, 0, 9, 18,
                   -18, -9, 0, 9, 18,
                   -18, -9, 0, 9, 18,
                   -18, -9, 0, 9, 18,
                   -18, -9, 0, 9, 18,
                   -18, -9, 0, 9, 18,
                   0])

    YC = np.array([210, 210, 210,
                   195, 195, 195, 195, 195,
                   180, 180, 180, 180, 180, 180,
                   165, 165, 165, 165, 165, 165,
                   150, 150, 150, 150, 150, 150,
                   135, 135, 135, 135, 135,
                   120, 120, 120, 120, 120,
                   105, 105, 105, 105, 105,
                   90, 90, 90, 90, 90,
                   75, 75, 75, 75, 75,
                   60, 60, 60, 60, 60,
                   45, 45, 45, 45, 45,
                   30, 30, 30, 30, 30,
                   15, 15, 15, 15, 15,
                   0])

    # 移轴
    XCts = np.full_like(XC, 3)
    YCts = np.full_like(YC, 3)
    XC = XC + XCts
    YC = YC + YCts

    sumf = np.sum(darr)
    sumxf = np.sum(XC * darr)
    sumyf = np.sum(YC * darr)

    cop = np.array([sumxf / sumf, sumyf / sumf])
    return cop


def footdata_left(darr):
    data = []
    # 压强与电压的转换系数
    co = 1

    # 最大压强
    square = 36
    maxP = np.max(darr) * co / square
    minP = np.min(darr) * co / square
    data.append(maxP)

    # 平均压强
    bsquare = np.nonzero(darr)
    csquare = np.transpose(bsquare)
    esquare = len(csquare) * square
    avgP = np.sum(darr) * co / esquare
    data.append(avgP)

    # 面积
    data.append(esquare)

    # 足部轴角
    angel = 0
    data.append(angel)

    # 足印长度
    length = 0
    data.append(length)

    # 压力中心连线增量
    P_increment = maxP - minP
    data.append(P_increment)

    # 前足负荷比
    front_plr = np.sum(darr[0:45]) / np.sum(darr)
    front_plr = front_plr * 100
    data.append(front_plr)

    # 后足负荷比
    after_plr = 100 - front_plr
    data.append(after_plr)

    # 左侧负荷比
    leftsum = np.sum(
        darr[0] + darr[3:4] + darr[8:10] + darr[14:16] + darr[20:22] + darr[26:28] + darr[31:33] + darr[36:38]
        + darr[41:43] + darr[46:48] + darr[51:53] + darr[56:58] + darr[61:63] + darr[66:68] + darr[71])
    left_plr = leftsum / np.sum(darr)
    left_plr = left_plr * 100
    data.append(left_plr)

    # 右侧负荷比
    right_plr = 100 - left_plr
    data.append(right_plr)

    return data


def footdata_right(darr):
    data = []
    # 压强与电压的转换系数
    co = 1

    # 最大压强
    square = 36
    maxP = np.max(darr) * co / square
    minP = np.min(darr) * co / square
    data.append(maxP)

    # 平均压强
    bsquare = np.nonzero(darr)
    csquare = np.transpose(bsquare)
    esquare = len(csquare) * square
    avgP = np.sum(darr) * co / esquare
    data.append(avgP)

    # 面积
    data.append(esquare)

    # 足部轴角
    angel = 0
    data.append(angel)

    # 足印长度
    length = 0
    data.append(length)

    # 压力中心连线增量
    P_increment = maxP - minP
    data.append(P_increment)

    # 前足负荷比
    front_plr = np.sum(darr[0:35]) / np.sum(darr)
    front_plr = front_plr * 100
    data.append(front_plr)

    # 后足负荷比
    after_plr = 100 - front_plr
    data.append(after_plr)

    # 左侧负荷比
    leftsum = np.sum(
        darr[0:1] + darr[3:5] + darr[8:10] + darr[14:16] + darr[20:22] + darr[26:27] + darr[31:32] + darr[36:37]
        + darr[41:42] + darr[46:47] + darr[51:52] + darr[56:57] + darr[61:62] + darr[66:67])
    left_plr = leftsum / np.sum(darr)
    left_plr = left_plr * 100
    data.append(left_plr)

    # 右侧负荷比
    right_plr = 100 - left_plr
    data.append(right_plr)

    return data


def data_process(data):
    str_list = list(data)
    str_list = str_list[6:len(str_list)]
    index = 0
    for i in range(71):
        str_list.insert(2 * i + 4 + index, ' ')
        index += 3
    dataprocess = ''.join(str_list)
    dlist = dataprocess.strip(' ').split(' ')
    for i in range(len(dlist)):
        dlist[i] = int(int(dlist[i], 16) / 16)
    darr = np.array(dlist)

    return darr


# left foot data
def get_left_form(array_left):
    left_points = [[0 for i in range(6)] for j in range(15)]
    left_blank = [2, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2]
    length = [3, 5, 6, 6, 6, 5, 5, 5, 5, 5, 5, 5, 5, 5, 1]
    temp_index = 0
    for index in range(len(left_points)):
        blank = left_blank[index]
        temp_len = length[index]
        left_points[index][blank:blank + temp_len] = array_left[temp_index:temp_index + temp_len]
        temp_index = temp_index + temp_len
    return left_points


# right foot data
def get_right_form(array_right):
    right_points = [[0 for i in range(6)] for j in range(15)]
    right_blank = [1, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 3]
    length = [3, 5, 6, 6, 6, 5, 5, 5, 5, 5, 5, 5, 5, 5, 1]
    temp_index = 0
    for index in range(len(right_points)):
        blank = right_blank[index]
        temp_len = length[index]
        right_points[index][blank:blank + temp_len] = array_right[temp_index:temp_index + temp_len]
        temp_index = temp_index + temp_len
    return right_points





def export_data():
    mSerial = SerialPort(port, brate)
    print("开始")
    blue = mSerial.read_data()
    for data in blue:
        left_point = data[0]
        right_point = data[1]
        cop_left = data[2]
        cop_right = data[3]
        data_left = data[4]
        data_right = data[5]
        index = data[6]
        left_sum.append(left_point)
        right_sum.append(right_point)
        cop_left_sum.append(cop_left)
        cop_right_sum.append(cop_right)
        data_left_sum.append(data_left)
        data_right_sum.append(data_right)
        indexs.append(index)


@app.route('/get_data', methods=["POST"])
def get_data():
    now_index = int(request.values.get("index"))
    print(now_index)
    dict_result = {
        "left_sum": left_sum[now_index:],
        "right_sum": right_sum[now_index:],
        "cop_left_sum": cop_left_sum,
        "cop_right_sum": cop_right_sum,
        "data_left_sum": data_left_sum[now_index:],
        "data_right_sum": data_right_sum[now_index:],
        "indexs": indexs[now_index:]
    }
    return json.dumps(dict_result, cls=NpEncoder)


class NpEncoder(json.JSONEncoder):
    def default(self, obj):
        if isinstance(obj, np.integer):
            return int(obj)
        elif isinstance(obj, np.floating):
            return float(obj)
        elif isinstance(obj, np.ndarray):
            return obj.tolist()
        else:
            return super(NpEncoder, self).default(obj)


@app.route('/')
def hello_world():
    return "hello"


if __name__ == '__main__':
    threading.Thread(target=export_data, args=()).start()
    app.run(debug=False, host='0.0.0.0', port='5000')  # 开启debug模式可以不用重启
