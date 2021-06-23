#include "pbdata.h"

u8 SPI_FLASH_BUF[4096];//һ��������С

void W25_GPIO_Configuration(void)
{
	GPIO_InitTypeDef   	GPIO_InitStructure;

	//SPI2 :                          NSS
	GPIO_InitStructure.GPIO_Pin=W25_NSSPort;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP;
	GPIO_Init(W25_NSSGPIO,&GPIO_InitStructure);
	
	//SPI2 :                          HOLD
	GPIO_InitStructure.GPIO_Pin=W25_HOLDPort;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP;
	GPIO_Init(W25_HOLDGPIO,&GPIO_InitStructure);
	
	//SPI2 :                          WP
	GPIO_InitStructure.GPIO_Pin=W25_WPPort;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP;
	GPIO_Init(W25_WPGPIO,&GPIO_InitStructure);
	
	W25_SET_WP(1);
	W25_SET_NSS(1);
	W25_SET_HOLD(1);
	
}

/************************************************/
//��ȡSPI_FLASH��status1״̬�Ĵ���
//BIT7  6   5   4   3   2   1   0
//SPR   RV  TB BP2 BP1 BP0 WEL BUSY
//SPR:Ĭ��0,״̬�Ĵ�������λ,���WPʹ��
//TB,BP2,BP1,BP0:FLASH����д��������
//WEL:дʹ������
//BUSY:æ���λ(1,æ;0,����)
//Ĭ��:0x00
u8 SPI_Flash_ReadSR(void)   
{  
    u8 byte=0;   
	
    W25_SET_NSS(0);                            //ʹ������   
    SPI_SendByte(W25X_ReadStatusReg);    //���Ͷ�ȡ״̬�Ĵ�������    
    byte=SPI_SendByte(0Xff);             //��ȡһ���ֽ�  
    W25_SET_NSS(1);                            //ȡ��Ƭѡ     
    return byte;   
} 

/************************************************/
//дSPI_FLASH״̬�Ĵ���
//ֻ��SPR,TB,BP2,BP1,BP0(bit 7,5,4,3,2)����д!!!
void SPI_FLASH_Write_SR(u8 sr)   
{   
    W25_SET_NSS(0);                            //ʹ������   
    SPI_SendByte(W25X_WriteStatusReg);   //����дȡ״̬�Ĵ�������    
    SPI_SendByte(sr);               //д��һ���ֽ�  
    W25_SET_NSS(1);                            //ȡ��Ƭѡ             
}   

/************************************************/
//SPI_FLASHдʹ��  
//��WEL��λ   
void SPI_FLASH_Write_Enable(void)   
{
    W25_SET_NSS(0);                            //ʹ������   
    SPI_SendByte(W25X_WriteEnable);      //����дʹ��  
    W25_SET_NSS(1);                            //ȡ��Ƭѡ             
} 

/************************************************/
//SPI_FLASHд��ֹ  
//��WEL����  
void SPI_FLASH_Write_Disable(void)   
{  
    W25_SET_NSS(0);                            //ʹ������   
    SPI_SendByte(W25X_WriteDisable);     //����д��ָֹ��    
    W25_SET_NSS(1);                            //ȡ��Ƭѡ             
}               

/************************************************/
//��ȡоƬID W25X16��ID:0XEF14
u16 SPI_Flash_ReadID(void)
{
    u16 Temp = 0;     
    W25_SET_NSS(0);                 
    SPI_SendByte(0x90);//���Ͷ�ȡID����     
    SPI_SendByte(0x00);       
    SPI_SendByte(0x00);       
    SPI_SendByte(0x00);                  
    Temp|=SPI_SendByte(0xFF)<<8;  
    Temp|=SPI_SendByte(0xFF);  
    W25_SET_NSS(1);                 
    return Temp;
}             

/************************************************/
//�ȴ�����
void SPI_Flash_Wait_Busy(void)   
{   
    while ((SPI_Flash_ReadSR()&0x01)==0x01);   // �ȴ�BUSYλ���
}  

/************************************************/
//��������оƬ
//��Ƭ����ʱ��:
//W25X16:25s 
//W25X32:40s 
//W25X64:40s 
//�ȴ�ʱ�䳬��...
void SPI_Flash_Erase_Chip(void)   
{                                             
    SPI_FLASH_Write_Enable();                  //SET WEL 
    SPI_Flash_Wait_Busy();   
    W25_SET_NSS(0);                            //ʹ������   
    SPI_SendByte(W25X_ChipErase);        //����Ƭ��������  
    W25_SET_NSS(1);                            //ȡ��Ƭѡ             
    SPI_Flash_Wait_Busy();                     //�ȴ�оƬ��������
}   

/************************************************/
//����һ������
//Dst_Addr:������ַ 0~511 for w25x16
//����һ��ɽ��������ʱ��:150ms
void SPI_Flash_Erase_Sector(u32 Dst_Addr)   
{   
    Dst_Addr*=4096;
    SPI_FLASH_Write_Enable();                  //SET WEL     
    SPI_Flash_Wait_Busy();   
    W25_SET_NSS(0);                            //ʹ������   
    SPI_SendByte(W25X_SectorErase);      //������������ָ�� 
    SPI_SendByte((u8)((Dst_Addr)>>16));  //����24bit��ַ    
    SPI_SendByte((u8)((Dst_Addr)>>8));   
    SPI_SendByte((u8)Dst_Addr);  
    W25_SET_NSS(1);                            //ȡ��Ƭѡ             
    SPI_Flash_Wait_Busy();                     //�ȴ��������
}  

/************************************************/
//�������ģʽ
void SPI_Flash_PowerDown(void)   
{ 
    W25_SET_NSS(0);                            //ʹ������   
    SPI_SendByte(W25X_PowerDown);        //���͵�������  
    W25_SET_NSS(1);                            //ȡ��Ƭѡ             
    delay_us(3);                               //�ȴ�TPD  
}   

/************************************************/
//����
void SPI_Flash_WAKEUP(void)   
{  
    W25_SET_NSS(0);                            //ʹ������   
    SPI_SendByte(W25X_ReleasePowerDown);   //  send W25X_PowerDown command 0xAB    
    W25_SET_NSS(1);                            //ȡ��Ƭѡ               
    delay_us(3);                               //�ȴ�TRES1
}   

/************************************************/
//��ȡSPI FLASH  
//��ָ����ַ��ʼ��ȡָ�����ȵ�����
//pBuffer:���ݴ洢��
//ReadAddr:��ʼ��ȡ�ĵ�ַ(24bit)
//NumByteToRead:Ҫ��ȡ���ֽ���(���65535)
void SPI_Flash_Read(u8* pBuffer,u32 ReadAddr,u16 NumByteToRead)   
{ 
    u16 i;                                                      
    W25_SET_NSS(0);                            //ʹ������   
    SPI_SendByte(W25X_ReadData);         //���Ͷ�ȡ����   
    SPI_SendByte((u8)((ReadAddr)>>16));  //����24bit��ַ    
    SPI_SendByte((u8)((ReadAddr)>>8));   
    SPI_SendByte((u8)ReadAddr);   
    for(i=0;i<NumByteToRead;i++)
    { 
        pBuffer[i]=SPI_SendByte(0XFF);   //ѭ������  
    }
    W25_SET_NSS(1);                            //ȡ��Ƭѡ             
}  

/************************************************/
//SPI��һҳ(0~65535)��д������256���ֽڵ�����
//��ָ����ַ��ʼд�����256�ֽڵ�����
//pBuffer:���ݴ洢��
//WriteAddr:��ʼд��ĵ�ַ(24bit)
//NumByteToWrite:Ҫд����ֽ���(���256),������Ӧ�ó�����ҳ��ʣ���ֽ���!!!   
void SPI_Flash_Write_Page(u8* pBuffer,u32 WriteAddr,u16 NumByteToWrite)
{
    u16 i;  
    SPI_FLASH_Write_Enable();                  //SET WEL 
    W25_SET_NSS(0);                            //ʹ������   
    SPI_SendByte(W25X_PageProgram);      //����дҳ����   
    SPI_SendByte((u8)((WriteAddr)>>16)); //����24bit��ַ    
    SPI_SendByte((u8)((WriteAddr)>>8));   
    SPI_SendByte((u8)WriteAddr);   
    for(i=0;i<NumByteToWrite;i++)
        {
            SPI_SendByte(pBuffer[i]);//ѭ��д��  
        }
    W25_SET_NSS(1);                            //ȡ��Ƭѡ 
    SPI_Flash_Wait_Busy();                     //�ȴ�д�����
} 

/************************************************/
//�޼���дSPI FLASH 
//����ȷ����д�ĵ�ַ��Χ�ڵ�����ȫ��Ϊ0XFF,�����ڷ�0XFF��д������ݽ�ʧ��!
//�����Զ���ҳ���� 
//��ָ����ַ��ʼд��ָ�����ȵ�����,����Ҫȷ����ַ��Խ��!
//pBuffer:���ݴ洢��
//WriteAddr:��ʼд��ĵ�ַ(24bit)
//NumByteToWrite:Ҫд����ֽ���(���65535)
//CHECK OK
void SPI_Flash_Write_NoCheck(u8* pBuffer,u32 WriteAddr,u16 NumByteToWrite)   
{                    
    u16 pageremain;    
    pageremain=256-WriteAddr%256; //��ҳʣ����ֽ���                
    if(NumByteToWrite<=pageremain)
        pageremain=NumByteToWrite;//������256���ֽ�
    while(1)
    {      
        SPI_Flash_Write_Page(pBuffer,WriteAddr,pageremain);
        if(NumByteToWrite==pageremain)
            break;//д�������
        else //NumByteToWrite>pageremain
        {
            pBuffer+=pageremain;
            WriteAddr+=pageremain;  

            NumByteToWrite-=pageremain;           //��ȥ�Ѿ�д���˵��ֽ���
            if(NumByteToWrite>256)
                pageremain=256; //һ�ο���д��256���ֽ�
            else pageremain=NumByteToWrite;       //����256���ֽ���
        }
    };      
} 

/************************************************/
//дSPI FLASH  
//��ָ����ַ��ʼд��ָ�����ȵ�����
//�ú�������������!
//pBuffer:���ݴ洢��
//WriteAddr:��ʼд��ĵ�ַ(24bit)
//NumByteToWrite:Ҫд����ֽ���(���65535)          
void SPI_Flash_Write(u8* pBuffer,u32 WriteAddr,u16 NumByteToWrite)   
{ 
    u32 secpos;
    u16 secoff;
    u16 secremain;     
    u16 i;    

    secpos=WriteAddr/4096;//������ַ 0~511 for w25x16
    secoff=WriteAddr%4096;//�������ڵ�ƫ��
    secremain=4096-secoff;//����ʣ��ռ��С   

    if(NumByteToWrite<=secremain)
        secremain=NumByteToWrite;//������4096���ֽ�
    while(1) 
    {   
        SPI_Flash_Read(SPI_FLASH_BUF,secpos*4096,4096);//������������������
        for(i=0;i<secremain;i++)//У������
        {
            if(SPI_FLASH_BUF[secoff+i]!=0XFF)break;//��Ҫ����     
        }
        if(i<secremain)//��Ҫ����
        {
            SPI_Flash_Erase_Sector(secpos);//�����������
            for(i=0;i<secremain;i++)       //����
            {
                SPI_FLASH_BUF[i+secoff]=pBuffer[i];   
            }
            SPI_Flash_Write_NoCheck(SPI_FLASH_BUF,secpos*4096,4096);//д����������  

        }
        else 
            SPI_Flash_Write_NoCheck(pBuffer,WriteAddr,secremain);//д�Ѿ������˵�,ֱ��д������ʣ������.                 
        if(NumByteToWrite==secremain)
            break;//д�������
        else//д��δ����
        {
            secpos++;//������ַ��1
            secoff=0;//ƫ��λ��Ϊ0    

            pBuffer+=secremain;  //ָ��ƫ��
            WriteAddr+=secremain;//д��ַƫ��       
            NumByteToWrite-=secremain;              //�ֽ����ݼ�
            if(NumByteToWrite>4096)secremain=4096;  //��һ����������д����
            else secremain=NumByteToWrite;          //��һ����������д����
        }    
    };       
}

