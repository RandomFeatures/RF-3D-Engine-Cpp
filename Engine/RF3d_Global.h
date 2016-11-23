/**************************************************
RF3d_Global.h
Random Features 3D RPG Component

by Allen Halsted (10 June 2002)
**************************************************/

#ifndef _RF3D_GLOBAL_H_
#define _RF3D_GLOBAL_H_

//new requirment in DX8
#define DIRECTINPUT_VERSION  0x0800

// Windows includes
#include <windows.h>

// Standard ANSI-C includes
#include <stdio.h>

// DirectX includes
#include "d3d8.h"
#include "d3dx8.h"
#include "dmusici.h"
#include "dsound.h"
#include "dplay8.h"
#include "dpaddr.h"
#include "dinput.h"


//MyStuff
#include "strfunctions.h"

//Common Included
//#include "ListControl.h"
#include "tinyxml.h"



// Core includes
#include "System.h"
#include "Graphics.h"
#include "RF3d_FileFormat.h"
#include "RF3d_Input.h"
#include "RF3d_RFApp.h"
#include "RF3d_LogFile.h"
//#include "RF3d_Character.h"
#include "RF3d_GameObjects.h"
#include "RF3d_GUIControl.h"
//#include "NiScreenText.h"

//#include "RF3d_Sound.h"
//#include "RF3d_Network.h"

///////////////////////////////////////////////////////////
// Global declarations
///////////////////////////////////////////////////////////
#define MENU_BACK   1
#define MENU_LOAD   2
#define MENU_SAVE   4

#endif
