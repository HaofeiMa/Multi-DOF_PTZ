#include "linux_serial.h"  
using namespace std;  
using namespace boost::asio;  
//串口相关对象  
boost::asio::io_service iosev;  
boost::asio::serial_port sp(iosev, "/dev/ttyUSB0");  
boost::system::error_code err;  
const unsigned char ender[2] = {0x0d, 0x0a};  
const unsigned char header[2] = {0x55, 0xaa};  
//发送数据共用体  
union sendData  
{  
 short d;  
 unsigned char data[2];  
}sendData2,sendData2;  
//接收数据共用体  
union receiveData  
{  
 short d;  
 unsigned char data[2];  
}receiveData1,receiveData2,receiveData3;  
//串口参数初始化  
void serialInit()  
{  
    sp.set_option(serial_port::baud_rate(115200));  
    sp.set_option(serial_port::flow_control(serial_port::flow_control::none));  
    sp.set_option(serial_port::parity(serial_port::parity::none));  
    sp.set_option(serial_port::stop_bits(serial_port::stop_bits::one));  
    sp.set_option(serial_port::character_size(8));      
}  
//将要发送的数据打包发送给下位机  
void writeSpeed(double sendData1Temp, double sendData2Temp,unsigned char ctrlFlag)  
{  
    unsigned char buf[11] = {0};//  
    int i, length = 0;  
    sendData2.d  = sendData1Temp;//mm/s  
    sendData2.d = sendData2Temp;  
    // 设置消息头  
    for(i = 0; i < 2; i++)  
        buf[i] = header[i];             //buf[0]  buf[1]  
      
    // 设置两种发送数据  
    length = 5;  
    buf[2] = length;                    //buf[2]  
    for(i = 0; i < 2; i++)  
    {  
        buf[i + 3] = sendData2.data[i];  //buf[3] buf[4]  
        buf[i + 5] = sendData2.data[i]; //buf[5] buf[6]  
    }  
    // 预留控制指令  
    buf[3 + length - 1] = ctrlFlag;       //buf[7]  
    // 设置校验值、消息尾  
    buf[3 + length] = getCrc8(buf, 3 + length);//buf[8]  
    buf[3 + length + 1] = ender[0];     //buf[9]  
    buf[3 + length + 2] = ender[1];     //buf[10]  
    // 通过串口下发数据  
    boost::asio::write(sp, boost::asio::buffer(buf));  
}  
//从下位机读取数据  
bool readSpeed(double &sendData1Temp,double &sendData2Temp,double &sendData3Temp,unsigned char &ctrlFlag)  
{  
    char i, length = 0;  
    unsigned char checkSum;  
    unsigned char buf[150]={0};  
    //读数据尾，进而读取数据的头部  
    try  
    {  
        boost::asio::streambuf response;  
        boost::asio::read_until(sp, response, "\r\n",err);     
        copy(istream_iterator<unsigned char>(istream(&response)>>noskipws),  
        istream_iterator<unsigned char>(),  
        buf);   
    }    
    catch(boost::system::system_error &err)  
    {  
        ROS_INFO("read_until error");  
    }   
    // 检查信息头  
    if (buf[0]!= header[0] || buf[1] != header[1])   //buf[0] buf[1]  
    {  
        ROS_ERROR("Received message header error!");  
        return false;  
    }  
    // 数据长度  
    length = buf[2];                                 //buf[2]  
    // 检查信息校验值  
    checkSum = getCrc8(buf, 3 + length);             //buf[10] 计算得出  
    if (checkSum != buf[3 + length])                 //buf[10] 串口接收  
    {  
        ROS_ERROR("Received data check sum error!");  
        return false;  
    }      
    // 读取速度值  
    for(i = 0; i < 2; i++)  
    {  
        receiveData1.data[i]  = buf[i + 3]; //buf[3] buf[4]  
        receiveData2.data[i] = buf[i + 5]; //buf[5] buf[6]  
        receiveData3.data[i]    = buf[i + 7]; //buf[7] buf[8]  
    }  
    // 读取控制标志位  
    ctrlFlag = buf[9];  
      
    sendData1Temp = receiveData1.d;  
    sendData2Temp = receiveData2.d;  
    sendData3Temp = receiveData3.d;  
    return true;  
}  
//获得8位循环冗余校验值  
unsigned char getCrc8(unsigned char *ptr, unsigned short len)  
{  
    unsigned char crc;  
    unsigned char i;  
    crc = 0;  
    while(len--)  
    {  
        crc ^= *ptr++;  
        for(i = 0; i < 8; i++)  
        {  
            if(crc&0x01)  
                crc=(crc>>1)^0x8C;  
            else   
                crc >>= 1;  
        }  
    }  
    return crc;  
}  
