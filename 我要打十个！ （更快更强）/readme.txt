

文件组成：

--- CMSIS    -----  Coresupport     ------  core_cm3.c  （内核定义）
             |                      |   
             |                      |
             |                      ------  core_cm3.h
             |
             |
             |
             ------  DeviceSupport  ------  startup  ----启动文件
                                    |
                                    |
                                    ------  stm32f10x.h  (外设寄存器定义 中断异常定义)
                                    |
                                    |
                                    ------  system_stm32f10x.c  (设置系统时钟，系统初始化)
                                    |
                                    |
                                    ------  system_stm32f10x.h


--- FWlib    -----  inc
             |
             |
             |
             -----  src    （标准外设库）



--- Project  -----  LIST   （list文件生成目录）
             |
             |
             -----  OBJ     （hex 文件所在目录）
             |
             |
             -----  Pro     （工程所在文件夹）


--- USER     ----- CPU  -----  stm32f10x_conf.h   (配置头文件)
             |          |
             |          |
             |          -----  stm32f10x_it.c   (编写中断服务函数)
             |          |
             |          |
             |          -----  stm32f10x_it.h  
             |
             |
             ------  main.c
             |
             |
             -------  添加的用户程序(.c/.h)
