/**************************************************
RF3d_NiApp.cpp
Random Features 3D RPG Main Window

by Allen Halsted (29 June 2002)

Required libraries:

**************************************************/

#include "RF3d_Global.h"

//#include "Window.h"
#include <mmsystem.h>

///////////////////////////////////////////////////////////
// Overloaded application class functions
//////////////////////////////////////////////////////////
cRFApp::cRFApp()
{ 
} 

BOOL cRFApp::Init()
{
    m_bCapFrameRate = true;
    m_iMaxFrameRate = 30; // cap the frame rate at 30fps

	m_logfile.Log("Max Frame Rate = 33");

	// Initialize input and input devices
	m_Input.Init(GethWnd(), GethInst());
	m_Keyboard.Create(&m_Input, KEYBOARD);
	m_Mouse.Create(&m_Input, MOUSE, TRUE);
	m_logfile.Log("Init DirectInput");


    if (!CreateRenderer()) //DirectX
        return false;

    if (!SetupCamera()) 
        return false;

//    if (!CreateScene())//load the level... do the lighting
//        return false;


	return TRUE;
}

BOOL cRFApp::Shutdown()
{

  
  
  // Free meshes
  m_NodeTreeMesh.Free();
  m_Mesh.Free();
  
  m_SkyBox.Free();

 // Shutdown input
  m_Keyboard.Free();
  m_Mouse.Free();
  m_Input.Shutdown();

  // Shutdown graphics
  m_Graphics.Shutdown();

  ClearMouseClipping();

  return TRUE;
}

void cRFApp::EnableFrameRate(BOOL bEnable)
{
	m_bCapFrameRate = bEnable;
}

int cRFApp::GetMaxFrameRate()
{
	return m_iMaxFrameRate;
}

void cRFApp::SetMaxFrameRate(int iMax)
{
	m_iMaxFrameRate = iMax;
}


BOOL cRFApp::SetupCamera()
{

   return true;
}

BOOL cRFApp::CreateRenderer()
{
 // Initialize the graphics device and set display mode
  m_logfile.Log("CreateRenderer()");

  m_Graphics.Init();
  m_Graphics.SetMode(GethWnd(), !m_bFullScreen, TRUE, m_Width, m_Height, 32);
  m_logfile.Log("D3D Init");

	return true;
}


BOOL cRFApp::CreateScene()
{
   // TODO -- Make a level file!
   // TODO -- load the first level here

   return true;
}



void cRFApp::CaptureInput()
{
  // Read in input
  m_Keyboard.Acquire(TRUE);
  m_Keyboard.Read();
  m_Mouse.Acquire(TRUE);
  m_Mouse.Read();
}

//--------------------------------------
void cRFApp::setMouseClipping()
{
	  ClipCursor(NULL);
	//  if (getWindowActive())
	  {
		  RECT r;
		  GetWindowRect(GethWnd(), &r);

			 POINT p;
			 GetCursorPos(&p);
			 //lastCursorPos.set(p.x - r.left, p.y - r.top);

			 ClipCursor(&r);

			 int centerX = (r.right + r.left) >> 1;
			 int centerY = (r.bottom + r.top) >> 1;
			 SetCursorPos(centerX, centerY);
	  }
}

//--------------------------------------
void cRFApp::ClearMouseClipping()
{
	  ClipCursor(NULL);
}

