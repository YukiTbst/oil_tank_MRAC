# 精简版wyq通信协议

    为了满足实时性要求，直接使用二进制表示数据（wyqProtocol采用ASCII码）

## 消息构成

**包头**：0x77 0x79 0x71

**数据段长度**：一个字节，值等于数据段的长度，可以为0

**数据段**：至多259字节（因为总长要控制在255字节及以内）

**CRC16验证段**：两个字节，使用modbus RTU的规则。多项式为8055， 初值为ffff， 结果异或值为0000， 由于使用modbus传输信号时是低位在前，因此输入反转为true， 输出反转也为true。使用crc库时调用的函数格式如下：`crc16Val=crc16(datasToSend, len+4, 0x8005, 0xffff, 0x0000, true, true);`其中len是数据段的长度，dataTosend是整段信息的起始地址。

# 举例

数据段长度为0的信号量：

0x77 0x79 0x71 0x00 0xee 0x19
