//============================亚博智能========================================
//  智能小车微信遥控实验
//=============================================================================



int buzzer = 3;              //设置控制蜂鸣器的数字IO脚

/*协议需要用到的*/
int incomingByte = 0;       // 接收到的 data byte
String inputString = "";         // 用来储存接收到的内容
boolean newLineReceived = false; // 前一次数据结束标志
boolean startBit  = false;  //协议开始标志

/*超声波*/
int Echo = A1;  // Echo回声脚(P1.1)
int Trig =A0;  //  Trig 触发脚(P1.0)
int Distance = 0;
String returntemp = ""; //存储返回值 

void setup()
{  
  pinMode(buzzer,OUTPUT);//设置数字IO脚模式，OUTPUT为输出 
  pinMode(Echo, INPUT);    // 定义超声波输入脚
  pinMode(Trig, OUTPUT);   // 定义超声波输出脚
  
  Serial.begin(9600);	//波特率9600 （蓝牙通讯设定波特率）
 
  digitalWrite(buzzer,HIGH);    //不发声
  
}

void Distance_test()   // 量出前方距离 (对应 自定义显示2)
{
  digitalWrite(Trig, LOW);   // 给触发脚低电平2μs
  delayMicroseconds(2);
  digitalWrite(Trig, HIGH);  // 给触发脚高电平10μs，这里至少是10μs
  delayMicroseconds(10);
  digitalWrite(Trig, LOW);    // 持续给触发脚低电
  float Fdistance = pulseIn(Echo, HIGH);  // 读取高电平时间(单位：微秒)
  Fdistance= Fdistance/58;       //为什么除以58等于厘米，  Y米=（X秒*344）/2
  // X秒=（ 2*Y米）/344 ==》X秒=0.0058*Y米 ==》厘米=微秒/58
  //Serial.print("Distance:");      //输出距离（单位：厘米）
  //Serial.println(Fdistance);         //显示距离
  Distance = Fdistance;
}  

void whistle()   //鸣笛 对应 (自定义3) 
{
    int i;
    for(i=0;i<80;i++)//输出一个频率的声音
    { 
      digitalWrite(buzzer,LOW);//发声音
      delay(10);//延时1ms 
      digitalWrite(buzzer,HIGH);//不发声音
      delay(1);//延时ms 
    } 
    for(i=0;i<100;i++)//输出另一个频率的声音 
    { 
      digitalWrite(buzzer,LOW);//发声音
      delay(20);//延时2ms 
      digitalWrite(buzzer,HIGH);//不发声音
      delay(2);//延时2ms 
    } 
}

/*程序主循环入口*/
void loop() 
{     
    if (newLineReceived)
    {    
       if(inputString[5] == '1')  //鸣笛 对应 (自定义3)
       {
          whistle();//这里你可以对应自定义3做其他自己想做的任务,例如点灯唱歌等。
          Serial.print("whistle\r\n");
       }
      
       //返回状态
       Distance_test();//超声波测距离
      //组装协议数，这里必须把所有协议数据组成一包发，不能只发送一个,根据协议填写对应的位
       returntemp = "$0,0,0,0,0,0,0,0,0,0,0,";
       returntemp.concat(Distance); //追加到超声波(自定义显示2)，这里你可以用自定义显示2显示其他的东西
       returntemp += "cm,8.2V#"; //这里追加最后一个自定义显示1的值
       Serial.print(returntemp); //返回协议数据包       
       inputString = "";   // clear the string
       newLineReceived = false;    
 
    }
    
}
  
//serialEvent()是IDE1.0及以后版本新增的功能，不清楚为什么大部份人不愿意用，这个可是相当于中断功能一样的啊!  
void serialEvent()
{
  while (Serial.available()) 
  {    
    incomingByte = Serial.read();              //一个字节一个字节地读，下一句是读到的放入字符串数组中组成一个完成的数据包
    if(incomingByte == '$') //判断协议，则开始接收正常的协议包数据
    {
      startBit= true;
    }
    if(startBit == true)
    {
       inputString += (char) incomingByte;     // 全双工串口可以不用在下面加延时，半双工则要加的//
    }  
    if (incomingByte == '#')//接收到协议尾，停止接，等待主循环解析协议
    {
       newLineReceived = true; 
       startBit = false;
    }
  }
}



