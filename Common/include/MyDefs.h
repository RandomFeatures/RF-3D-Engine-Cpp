
#if _MSC_VER > 1000
#pragma once    //Damn this in improtant!!!!
#endif // _MSC_VER > 1000


#define MsgBox(msg,cap) MessageBox(0,msg,cap,MB_OK);

#define _RGB16BIT565(r,g,b) ((b%32) + ((g%64) << 6) + ((r%32) << 11)) 
//Example use of the macro: 
//unsigned short pixel = _RGB16BIT565(red, green, blue);

//In order to avoid finger-aches :)
typedef unsigned char uchar;
typedef unsigned short ushort;
typedef unsigned int uint;  
typedef unsigned long ulong;
