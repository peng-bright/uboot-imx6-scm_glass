#include <video_fb.h>
#include <linux/types.h>
#include <splash.h>
#include "gui.h"
#include <command.h>
#include <common.h>
#include <fs.h>
#include "font.h"
#define VIDEO_VISIBLE_COLS1	(pGD->winSizeX)
#define VIDEO_COLS1		VIDEO_VISIBLE_COLS1
#define VIDEO_LINE_LEN1		(VIDEO_COLS1*VIDEO_PIXEL_SIZE1)
#define VIDEO_PIXEL_SIZE1	(pGD->gdfBytesPP)


#define VIDEO_X	(pGD->winSizeX)
#define VIDEO_Y	(pGD->winSizeY)
#define VIDEO_PIX_SIZE	(pGD->gdfBytesPP)

#define VIDEO_SIZE_GUI VIDEO_X*VIDEO_Y*VIDEO_PIX_SIZE

extern  GraphicDevice *pGD;

u8 chinese_character_information1[72];
u8 chinese_character_informations[12][72]={
{0x40,0x00,0x4f,0xfe,0x48,0x14,0x48,0x24,0x48,0x44,0x7f,0x84,0x48,0x04,0x48,0x04,
0x48,0x04,0x7f,0x84,0x48,0x44,0x48,0x44,0x48,0x44,0x4f,0xfe,0x40,0x00,0x00,0x00,
0x40,0x80,0x43,0x00,0x7f,0xfe,0x42,0x08,0x43,0xfc,0x00,0x00,0x4f,0xfe,0x48,0x14,
0x48,0x64,0x7f,0x84,0x48,0x04,0x7f,0xc4,0x48,0x24,0x48,0x24,0x4f,0xfe,0x00,0x00,
0x40,0x80,0x41,0x00,0x47,0xfe,0x7a,0x08},
{0x01,0x01,0x09,0x01,0x31,0x01,0x21,0x02,0x21,0xe2,0x2f,0x14,0xa5,0x14,0x61,0x08,
0x21,0x14,0x21,0x24,0x21,0xc2,0x21,0x03,0x29,0x02,0x31,0x00,0x21,0x00,0x00,0x00,
0x02,0x00,0x04,0x00,0x1f,0xfe,0xea,0x00,0x42,0x00,0x27,0xf8,0x2a,0x90,0x32,0x90,
0xe7,0xfc,0x22,0x92,0x32,0x92,0x2b,0xf2,0x24,0x02,0x22,0x02,0x02,0x0e,0x00,0x00,
0x08,0x40,0x08,0x42,0x08,0x81,0xff,0xfe},
{0x00,0x00,0x08,0x22,0x10,0x22,0x3f,0xa4,0xea,0xa4,0x2a,0xa8,0x2a,0xb0,0x2a,0xff,
0xbf,0xa0,0x6a,0xb0,0x2a,0xa8,0x2a,0xa4,0x2a,0xa6,0x00,0xa4,0x00,0x20,0x00,0x00,
0x00,0x02,0x00,0x04,0x40,0x09,0x40,0x31,0x41,0xc2,0x7e,0x02,0x41,0x84,0x40,0x68,
0x42,0x10,0x4f,0x10,0x72,0x68,0x03,0x84,0x02,0x06,0x00,0x03,0x00,0x02,0x00,0x00,
0x00,0x00,0x00,0x04,0x04,0x1c,0x08,0x00},
{0x10,0x02,0x10,0x02,0x10,0x04,0x10,0x08,0x10,0x30,0x10,0xc0,0x9f,0x00,0x52,0x00,
0x32,0x04,0x12,0x02,0x12,0x02,0x13,0xfc,0x10,0x00,0x10,0x00,0x10,0x00,0x00,0x00,
0x00,0x02,0x00,0x1c,0x7f,0xe0,0x48,0x84,0x48,0x82,0x7f,0xfc,0x10,0x01,0x10,0x06,
0x10,0x38,0x9f,0xc0,0x52,0x00,0x32,0x02,0x12,0x01,0x13,0xfe,0x10,0x00,0x00,0x00,
0x00,0x02,0x00,0x0c,0x3f,0xf0,0x29,0x01},
{0x00,0x00,0x00,0x00,0x1f,0xf0,0x12,0x20,0x12,0x20,0x12,0x20,0x12,0x20,0xff,0xfc,
0x12,0x22,0x12,0x22,0x12,0x22,0x12,0x22,0x1f,0xf2,0x00,0x02,0x00,0x0e,0x00,0x00,
0x02,0x00,0x04,0x00,0x0f,0xfe,0x34,0x00,0xe0,0x00,0x40,0x00,0x3f,0xfc,0x21,0x08,
0x21,0x08,0x21,0x08,0x3f,0xf8,0x21,0x08,0x21,0x08,0x21,0x08,0x3f,0xfc,0x00,0x00,
0x02,0x00,0x04,0x00,0x18,0x00,0xe7,0xf8},
{0x00,0x80,0x00,0x80,0x40,0x80,0x40,0x80,0x40,0x80,0x40,0x82,0x40,0x81,0x47,0xfe,
0x48,0x80,0x50,0x80,0x60,0x80,0x40,0x80,0x40,0x80,0x01,0x80,0x00,0x80,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x1f,0xff,0x12,0x22,0x12,0x22,0x32,0x22,0xd2,0x22,
0x52,0x22,0x12,0x22,0x12,0x22,0x12,0x22,0x1f,0xff,0x00,0x00,0x30,0xf0,0x00,0x00,
0x08,0x20,0x06,0x3f,0x80,0xe0,0x67,0x00},
{0x08,0x20,0x48,0x40,0x49,0x80,0x4e,0x00,0x7f,0xff,0x8a,0x00,0x89,0x20,0x00,0x20,
0x44,0x20,0x33,0x40,0x00,0x40,0x00,0x40,0xff,0xff,0x00,0x80,0x00,0x80,0x00,0x00,
0x00,0x80,0x21,0x02,0x2a,0x04,0x2a,0x04,0x2a,0x78,0x2a,0x40,0x2a,0x40,0xfa,0x40,
0x2a,0x40,0x2a,0x7c,0x2a,0x02,0x2a,0x02,0x22,0x82,0x23,0x0e,0x02,0x00,0x00,0x00,
0x3f,0xf0,0x20,0x40,0x20,0x40,0x20,0x40},
{0x10,0x80,0x10,0x82,0x11,0x01,0xff,0xfe,0x12,0x00,0x14,0x02,0x00,0x02,0x13,0x04,
0x12,0xc8,0x12,0x30,0xfe,0x30,0x12,0x48,0x13,0x84,0x12,0x06,0x10,0x04,0x00,0x00,
0x00,0x08,0x50,0x29,0x50,0x29,0x5f,0xaa,0x5a,0xaa,0xfa,0xfc,0x0a,0xac,0x0f,0xa8,
0x0a,0xa8,0xea,0xfc,0x5a,0xaa,0x5f,0xab,0x50,0x28,0x50,0x28,0x10,0x08,0x00,0x00,
0x00,0x20,0x11,0x20,0x11,0x20,0x52,0x20},
{0x00,0x40,0x20,0x80,0x21,0x00,0x22,0x00,0x27,0xff,0x2c,0x90,0x34,0x90,0xe4,0x90,
0x24,0x94,0x24,0x92,0x24,0x93,0x27,0xfe,0x20,0x00,0x20,0x00,0x20,0x00,0x00,0x00,
0x10,0x02,0x10,0x04,0x10,0x09,0x10,0x11,0x10,0x62,0x13,0x82,0xfe,0x84,0x12,0x48,
0x12,0x30,0x12,0x30,0x12,0xc8,0x13,0x04,0x10,0x06,0x10,0x03,0x10,0x02,0x00,0x00,
0x10,0x20,0x10,0x40,0x10,0x80,0x11,0x00},
{0x7f,0xff,0x40,0x00,0x4c,0x40,0x72,0x20,0x41,0xc0,0x00,0x00,0x7f,0xff,0x52,0x02,
0x53,0x04,0x52,0xc0,0x52,0x30,0x52,0x48,0x7e,0x84,0x00,0x06,0x00,0x04,0x00,0x00,
0x02,0x04,0x06,0x44,0x1a,0xc4,0xe3,0x48,0x46,0x48,0x00,0x48,0x09,0x04,0x09,0x04,
0x09,0x08,0xff,0xc8,0x09,0x30,0x49,0x28,0x39,0x44,0x29,0x02,0x01,0x1f,0x00,0x00,
0x08,0x20,0x08,0xc0,0x0b,0x00,0xff,0xff},
{0x00,0x00,0x00,0x80,0x01,0x04,0x02,0x0e,0x0c,0x14,0x70,0x24,0x21,0xc4,0x00,0x8c,
0x00,0x08,0x70,0x08,0x08,0x28,0x06,0x1e,0x03,0x0c,0x01,0x80,0x01,0x00,0x00,0x00,
0x00,0x00,0x08,0x00,0x30,0x00,0x20,0x3e,0x2f,0xa2,0x29,0x22,0x29,0x22,0xa9,0x22,
0x69,0x22,0x29,0x22,0x29,0x22,0x2f,0xa2,0x28,0x3e,0x30,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x40,0x00,0x4f,0x80},
{0x00,0x00,0x08,0x00,0x49,0xf8,0x49,0x20,0x49,0x20,0x49,0x20,0x49,0x20,0x49,0x20,
0x49,0x20,0x49,0xf0,0x48,0x00,0x40,0x04,0x40,0x02,0x7f,0xfc,0x00,0x00,0x00,0x00,
0x00,0x02,0x02,0x02,0x07,0x22,0x1a,0x62,0x72,0xa2,0x23,0x22,0x06,0x22,0x00,0x02,
0x02,0x22,0x0f,0x62,0x7a,0xa2,0x23,0x22,0x0e,0x22,0x04,0x26,0x00,0x02,0x00,0x00,
0x00,0x42,0x40,0x82,0x43,0x04,0x4d,0x04}};

void LCD_DrawPoint(int xx, int yy,u16 color) 
{
	u16 *dest0;
    unsigned int  offset;
	
	// æ ¹æ®x,yæŸfbçåç§»é
	// åè¯¥åç§»éçåå­äž­åå¥é¢è²
	// rgb 565 888 
	offset = yy * VIDEO_LINE_LEN1 + xx * VIDEO_PIXEL_SIZE1;     
	dest0 = (u16 *)(pGD->frameAdrs + offset);
	
	// rgb 565 888 
	  dest0[0] = color;	
}


//gao
void LCD_DrawPoint1(int xx, int yy,int i) 
{
	u16 *dest0;
        int  offset;

	// æ ¹æ®x,yæŸfbçåç§»é
	// åè¯¥åç§»éçåå­äž­åå¥é¢è²
	// rgb 565 888 
	offset = yy * VIDEO_LINE_LEN1 + xx * VIDEO_PIXEL_SIZE1;     
	dest0 = pGD->frameAdrs+ offset;
	// rgb 565 888 
	if(i == 0)
	{
	  dest0[0] = 0x0000;
	}else

	dest0[0] = 0xffff;  
	

}

void LCD_GBK(u16 x,u16 y,unsigned char *code,u8 size,u8 mode)
{
	unsigned char qh,ql;
	unsigned char i;					  
	unsigned long foffset;
	 unsigned long *ff;
	u32 temp,t,t1;
	u16 y0=y;
	qh=*code;
	ql=*(++code);
	ql-=0x41;
	qh-=0x81;
	foffset=((unsigned long)190*qh+ql)*32;
	for(i=0;i<72;i++)
	{
		ff=(foffset+0x12000000+i);
		chinese_character_information1[i]=*ff;
	}
	for(t=0;t<32;t++)
	{   												   
		temp=chinese_character_information1[t];			
		for(t1=0;t1<8;t1++)
		{
			if(temp&0x80)LCD_DrawPoint1(x,y,2);
			else if(mode==0)LCD_DrawPoint1(x,y,0); 
			temp<<=1;
			y++;
			if((y-y0)==size)
			{
				y=y0;
				x++;
				break;
			}
		}  	 
	}

	flush_cache(pGD->frameAdrs, VIDEO_SIZE_GUI);
}
void LCD_False_GBK(u16 x,u16 y)
{
	u32 temp,t,i,t1;
	u16 y0=y;
	u8 size=16;
	u8 mode=0;
	for(i=0;i<12;i++)
		{
			for(t=0;t<32;t++)
			{   												   
				temp=chinese_character_informations[i][t];			
				for(t1=0;t1<8;t1++)
				{
					if(temp&0x80)LCD_DrawPoint1(x,y,2);
					else if(mode==0)LCD_DrawPoint1(x,y,0); 
					temp<<=1;
					y++;
				if((y-y0)==size)
				{
					y=y0;
					x++;
					break;
					}
				}  	 
			}
			flush_cache(pGD->frameAdrs, VIDEO_SIZE_GUI);
		}
}

void LCD_ShowChar(u16 x,u16 y,u8 num,u8 size,u8 mode)
{  							  
    u8 temp,t1,t;
	u16 y0=y;
	u8 csize=(size/8+((size%8)?1:0))*(size/2);		//��?��?��?��?��???��?��???��|��??��?��?��??��?��??����y	
	//����??���?��		   
	num=num-' ';//��?��???��?o����??��
	for(t=0;t<csize;t++)
	{   
		if(size==12)temp=asc2_1206[num][t]; 	 	//�̡¨�?1206��?��?
		else if(size==16)temp=asc2_1608[num][t];	//�̡¨�?1608��?��?
		else if(size==24)temp=asc2_2412[num][t];	//�̡¨�?2412��?��?
		else return;								//??��D��?��??a
		for(t1=0;t1<8;t1++)
		{			    
			if(temp&0x80)LCD_DrawPoint1(x,y,2);
			else if(mode==0)LCD_DrawPoint1(x,y,0);
			temp<<=1;
			y++;

			if((y-y0)==size)
			{
				y=y0;
				x++;
				break;
			}
		}  	 
	}  	    	   	 	  
}   

void Show_Str(u16 x,u16 y,u16 width,u16 height,char*str)
{					
	u16 x0=x;
	u16 y0=y;	
	u8 size=16;
	u8 mode=0;
    u8 bHz=0;     //��?��??��???D??  	    				    				  	  
    while(*str!=0)//��y?Y?��?����?
    { 
        if(!bHz)
        {
	        if(*str>0x80)bHz=1;//?D?? 
	        else              //��?��?
	        {      
                if(x>(x0+width-size/2))//??DD
				{				   
					y+=size;
					x=x0;	   
				}							    
		        if(y>(y0+height-size))break;//????����??      
		        if(*str==13)//??DD��?o?
		        {         
		            y+=size;
					x=x0;
		            str++; 
		        }  
		        else LCD_ShowChar(x,y,*str,size,mode);//��DD��2?��?D�䨨? 
				str++; 
		        x+=size/2; //��?��?,?a��?��?��?��?��? 
	        }
        }else//?D?? 
        {     
            bHz=0;//��Doo��??a    
            if(x>(x0+width-size))//??DD
			{	    
				y+=size;
				x=x0;		  
			}
	        if(y>(y0+height-size))break;//????����??  						     
	       LCD_GBK(x,y,str,size,mode); //??��??a??oo��?,??D???��? 
	        str+=2; 
	        x+=size;//??��???oo��???��?	    
        }						 
    }   
}  		

void LCD_Fill(u16 sx,u16 sy,u16 ex,u16 ey,u16 color)
{          
	u16 j,i=0;
	u16 xlen=0;
	xlen=ex-sx+1;	 
	for(i=sy;i<=ey;i++)
	{
		   			 
		for(j=0;j<xlen;j++)
			LCD_DrawPoint((j+sx),i,color);
		
	}
	flush_cache(pGD->frameAdrs, VIDEO_SIZE_GUI);	 
}  

// »­Ö±Ïß
//x1,y1 Æðµã×ø±ê
//x2,y2 ÖÕµãµã×ø±ê
void LCD_DrawLine(u16 x1, u16 y1, u16 x2, u16 y2,u16 color)
{
	u16 t,rew;
	rew = color; 
	int xerr=0,yerr=0,delta_x,delta_y,distance; 
	int incx,incy,uRow1,uCol1; 
	delta_x=x2-x1; 
	delta_y=y2-y1; 
	uRow1=x1; 
	uCol1=y1; 
	if(delta_x>0)incx=1; 
	else if(delta_x==0)incx=0;
	else {incx=-1;delta_x=-delta_x;} 
	if(delta_y>0)incy=1; 
	else if(delta_y==0)incy=0;
	else{incy=-1;delta_y=-delta_y;} 
	if( delta_x>delta_y)distance=delta_x; 
	else distance=delta_y; 
	for(t=0;t<=distance+1;t++ )
	{  
		
		LCD_DrawPoint(uRow1,uCol1,rew);
		xerr+=delta_x ; 
		yerr+=delta_y ; 
		if(xerr>distance) 
		{ 
			xerr-=distance; 
			uRow1+=incx; 
		} 
		if(yerr>distance) 
		{ 
			yerr-=distance; 
			uCol1+=incy; 
		} 
	} 
	flush_cache(pGD->frameAdrs, VIDEO_SIZE_GUI); 
} 
void LCD_Straight_Line(u16 x1, u16 y1,u16 size)
{
	u16 x2,y2;
	x2=x1+size/2;
	y2=y1-size/2;
	LCD_DrawLine(x1,y1,(x1+size),y1,0xffff);
	LCD_DrawLine(x2,y2,x2,(y2+size),0xffff);
	flush_cache(pGD->frameAdrs, VIDEO_SIZE_GUI);
}

//»­Ô²
//x0,y0ÖÐÐÄµã×ø±ê£¬r °ëŸ¶
void LCD_Draw_Circle1(u16 x0,u16 y0,int r,u16 color)
{
	int a,b;
	int di;
	a=0;b=r;	  
	di=3-(r<<1);             //ÃÃÂ¶ÃÃÃÂžÃ¶ÂµÃ£ÃÂ»ÃÃÂµÃÂ±ÃªÃÂŸ
	while(a<=b)
	{
		LCD_DrawPoint(x0+a,y0-b,color);             //5
 		LCD_DrawPoint(x0+b,y0-a,color);             //0           
		LCD_DrawPoint(x0+b,y0+a,color);             //4               
		LCD_DrawPoint(x0+a,y0+b,color);             //6 
		LCD_DrawPoint(x0-a,y0+b,color);             //1       
 		LCD_DrawPoint(x0-b,y0+a,color);             
		LCD_DrawPoint(x0-a,y0-b,color);             //2             
  		LCD_DrawPoint(x0-b,y0-a,color);             //7     	         
		a++;
		//ÃÂ¹ÃÃBresenhamÃÃ£Â·ÂšÂ»Â­ÃÂ²     
		if(di<0)di +=4*a+6;	  
		else
		{
			di+=10+4*(a-b);   
			b--;
		} 						    
	}
	flush_cache(pGD->frameAdrs, VIDEO_SIZE_GUI);
}
//»­ŸØÐÎ
//(x1,y1),(x2,y2):ŸØÐÎµÄ¶ÔœÇ×ø±ê
void LCD_DrawRectangle(u16 x1, u16 y1, u16 x2, u16 y2,u16 color)
	{
	u16 row;
	row = color;
	LCD_DrawLine(x1,y1,x2,y1,row );
	LCD_DrawLine(x1,y1,x1,y2,row );
	LCD_DrawLine(x1,y2,x2,y2,row );
	LCD_DrawLine(x2,y1,x2,y2,row );
	flush_cache(pGD->frameAdrs, VIDEO_SIZE_GUI);
	}
