#include "RF3d_Global.h"


// Local includes
#include "Window.h"
#include "Frustum.h"
#include "NodeTree.h"
#include "WinMain.h"


void cApp::MainGameFrame(void *Ptr, long Purpose)
{
/*****Local Variables Start*****/
  cApp *g_Game = (cApp*)Ptr;
  cFrustum      Frustum;
  static long   CrossX;
  static long   CrossY;


/*****Local Variables End*****/

  // Initialize 
  if(Purpose == INITPURPOSE) 
  {
	  
	  CrossX = ((g_Game->m_Width / 2) - (16)) + 1;
	  CrossY = ((g_Game->m_Height / 2) - (16)) - 9;
//	  g_Game->m_CrossHair.Move(CrossX,CrossY,32,32);
	  //0xFFFFFFFF
//	 g_Game->ShowMouse(FALSE);
  }

  if(Purpose == SHUTDOWNPURPOSE) 
  {
	  g_Game->ClearMouseClipping();
  }

  // Only process frame states
  if(Purpose != FRAMEPURPOSE)
    return;


  g_Game->ControlPlayerMovement();
 
   // Set camera and calculate frustum
  g_Game->m_Graphics.SetCamera(&g_Game->m_Camera);
  Frustum.Construct(&g_Game->m_Graphics);

  // Update characters and call their AI
//  g_Game->m_GameObjCntrler.Update(33);
  
  // keep the mouse inside the window	
  g_Game->setMouseClipping();

  // Render everything
  g_Game->m_Graphics.ClearZBuffer(1.0f);
  if(g_Game->m_Graphics.BeginScene() == TRUE) 
  {


    g_Game->m_Graphics.EnableZBuffer(FALSE);
    g_Game->m_Graphics.EnableLighting(FALSE);

	//Render the Sky
	g_Game->m_SkyBox.Render(&g_Game->m_Camera);

    g_Game->m_Graphics.EnableZBuffer(TRUE);
    g_Game->m_Graphics.EnableLighting(TRUE);
	//Render the world
    g_Game->m_NodeTreeMesh.Render(&Frustum);

    // Render all characters
//	g_Game->m_GameObjCntrler.Render(30, &Frustum);

    // Render the GUI
	g_Game->RenderInGameGUI();
    g_Game->m_CrossHair.Blit(CrossX,CrossY);
//    g_Game->m_CrossHair.Render("+",FALSE);
									   
	//done rendering
	g_Game->m_Graphics.EndScene();
  
  }
  //flip to the screen
  g_Game->m_Graphics.Display();

}


void cApp::ControlPlayerMovement()
{
/*****Local Variables Start*****/
  static DWORD  Timer = timeGetTime();
  unsigned long Elapsed;
  float         XMove, ZMove, Height, Diff, Dist;
  D3DXVECTOR2   vecDir;
//  cLight        Light;
/*****Local Variables End*****/


  // Calculate elapsed time (plus speed boost)
  Elapsed = (timeGetTime() - Timer);
  Timer = timeGetTime();

	  // Process movement
  XMove = ZMove = 0.0f;

  CaptureGameInput(XMove, ZMove, Elapsed);

  
   // Check for height changes (can step up to 64 units)
  Height = m_NodeTreeMesh.GetHeightBelow(m_XPos, m_YPos + 64.0f, m_ZPos);
  if(m_YPos > Height) {
    // Dropping
    if((m_YPos -= (float)Elapsed) < Height)
      m_YPos = Height;
    else
      XMove = ZMove = 0.0f;
  } else {
    // Climbing
    m_YPos = Height;
  }

  // Check for movement collisions -
  // can't walk past anything blocking path
  if(m_NodeTreeMesh.CheckIntersect(m_XPos,m_YPos + 64.0f, m_ZPos,
                                 m_XPos + XMove, m_YPos + 64.0f, m_ZPos + ZMove,
                                 &Dist) == TRUE) {
    // Adjust coordinates to be exactly 2.5 units away from target
    Diff = Dist - 3.5f;
    D3DXVec2Normalize(&vecDir, &D3DXVECTOR2(XMove, ZMove));
    vecDir *= Diff;
    XMove = vecDir.x;
    ZMove = vecDir.y;
  }

  // Update view coordinates
  m_XPos += XMove;
  m_ZPos += ZMove;

  // Position camera  
  //  g_Game->m_YPos + 65.0f  sets the height of the player.
  m_Camera.Move(m_XPos + XMove, m_YPos + 65.0f, m_ZPos + ZMove);
  m_Camera.RotateRel((float)m_Mouse.GetYDelta() / 200.0f, 
                     (float)m_Mouse.GetXDelta() / 200.0f, 0.0f);

  Light.Position.x = m_XPos;
  Light.Position.y = m_YPos +80.0f;
  Light.Position.z = m_ZPos;
//  m_Graphics.SetLight(0, &Light);

  // Position light
//  m_Light.Move(m_XPos, m_YPos+80.0f, m_ZPos);
//  m_Graphics.SetLight(0, &m_Light);


}

void cApp::RenderInGameGUI()
{
/*****Local Variables Start*****/
/*****Local Variables End*****/

  
  if (m_DebugWindow.m_Visible)
  {
	  char Text[512];
	  	
	  sprintf(Text, "X %d : Y %d : Z %d\n", \
			  m_XPos, m_YPos, m_ZPos);

	  
//	  strcat(Text,m_logfile.m_strList[m_logfile.m_strList.Length()-3].c_str());
//	  strcat(Text,m_logfile.m_strList[m_logfile.m_strList.Length()-2].c_str());
//	  strcat(Text,m_logfile.m_strList[m_logfile.m_strList.Length()-1].c_str());

	  //The little window in the top left
	  m_DebugWindow.Render(Text);
	  
  }
}

void cApp::CaptureGameInput(float &XMove, float &ZMove, unsigned long Elapsed)
{
/*****Local Variables Start*****/
/*****Local Variables End*****/
   
	//Keyboard and mouse code!
    if(m_Keyboard.GetKeyState(KEY_SPACE) == TRUE) 
	{
  	  m_Keyboard.SetLock(KEY_SPACE, TRUE);
	  //Just test code
  	  //TODO - Remove this code
//	  m_GameObjCntrler.Blended(2, 1);
//	  m_Warrior.Blended = !m_Warrior.Blended;
//	  m_logfile.Log("GUID: ??  Blend Mode", BoolToStr(m_Warrior.Blended));

	}
	
	if(m_Keyboard.GetKeyState(KEY_D) == TRUE) 
	{
		XMove = (float)sin(m_Camera.GetYRotation() + 1.57f) * Elapsed;
		ZMove = (float)cos(m_Camera.GetYRotation() + 1.57f) * Elapsed;
	}

	if(m_Keyboard.GetKeyState(KEY_A) == TRUE) 
	{
		XMove = (float)sin(m_Camera.GetYRotation() - 1.57f) * Elapsed;
		ZMove = (float)cos(m_Camera.GetYRotation() - 1.57f) * Elapsed;
	}

	if(m_Keyboard.GetKeyState(KEY_W) == TRUE) 
	{
		XMove = (float)sin(m_Camera.GetYRotation()) * Elapsed;
        ZMove = (float)cos(m_Camera.GetYRotation()) * Elapsed;
	}

	if(m_Keyboard.GetKeyState(KEY_S) == TRUE) 
	{
		XMove = -(float)sin(m_Camera.GetYRotation()) * Elapsed;
		ZMove = -(float)cos(m_Camera.GetYRotation()) * Elapsed;
	}

		    // Exit game and go back to the main menu
	if(m_Keyboard.GetKeyState(KEY_ESC) == TRUE) 
	{
		m_Keyboard.SetLock(KEY_ESC);  
		m_StateManager.Pop(this);
		m_MenuOptions = MENU_BACK;
		// Push menu frame state
		m_StateManager.Push(MainMenuFrame, this);
	}

	if(m_Keyboard.GetKeyState(KEY_TILDE) == TRUE) 
	{  //Bring up the console window
		m_Keyboard.SetLock(KEY_TILDE);
		m_StateManager.Pop(this);
		// Push console frame state
		m_StateManager.Push(ConsoleFrame, this);
		m_Graphics.EnableLighting(FALSE);

	}
	
	if(m_Keyboard.GetKeyState(KEY_H) == TRUE) 
	{
	  m_Keyboard.SetLock(KEY_H);
	  if (m_DebugWindow.m_Visible)
	  {
		m_DebugWindow.HideConsole();
	  }
	  else
	  {
   		m_DebugWindow.ShowConsole();
	  }

	}

	if(m_Keyboard.GetKeyState(KEY_L) == TRUE) 
	{
	  m_Keyboard.SetLock(KEY_L);
	  EnableLighting(!m_LevelFileData.UseLighting);
	  m_LevelFileData.UseLighting = !m_LevelFileData.UseLighting;
	}

	if(m_Keyboard.GetKeyState(KEY_SUBTRACT) == TRUE) 
	{
	    m_Keyboard.SetLock(KEY_SUBTRACT, TRUE);
		TakeScreenShot(m_Graphics.GetDeviceCOM(),"d:\\temp\\test.bmp",100,100);
	}

		
	if(m_Mouse.GetButtonState(MOUSE_RBUTTON) == TRUE) 
	{
		m_Mouse.SetLock(MOUSE_RBUTTON, TRUE);
        m_Mouse.SetButtonState(MOUSE_RBUTTON, FALSE);

		//Just test code
		//TODO - Remove this code
//		if (!m_Warrior.IsDead())
//		{
//			m_Warrior.TakeDamage(1);	  
//			m_logfile.Log("GUID: ??  Takes 1 point of damage" );
//			m_logfile.Log("GUID: ??  Dies" );
//		}
	}
	  
	// Get selected character if left button pressed
	if(m_Mouse.GetButtonState(MOUSE_LBUTTON) == TRUE) 
	{
	}

	


}
