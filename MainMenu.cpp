#include "RF3d_Global.h"


// Local includes
#include "Window.h"
#include "Frustum.h"
#include "NodeTree.h"
#include "WinMain.h"

void cApp::MainMenuFrame(void *Ptr, long Purpose)
{
  typedef struct 
	{
		float x, y, z;//screen coordinates
		float u, v;  //Texture coordinates
	} sMenuVertex;

  sMenuVertex Verts[4] = 
  {
    { -100.0f,  100.0f, 1.0f, 0.0f, 0.0f },
    {  100.0f,  100.0f, 1.0f, 1.0f, 0.0f },
    { -100.0f, -100.0f, 1.0f, 0.0f, 1.0f },
    {  100.0f, -100.0f, 1.0f, 1.0f, 1.0f }
  };

/*****Local Variables Start*****/
  cApp *g_Game = (cApp*)Ptr;

  long MenuFVF = (D3DFVF_XYZ | D3DFVF_TEX1);
  
  static cVertexBuffer  MenuVB;
  static cTexture       MenuTexture;
  static cTexture       MenuSelect;
  static cTexture       MenuLogo;
  static cCamera        MenuCam;
  static cWorldPosition MenuPos;
  static long			LogoX;
  static long			SelectX;
  static long			StatusX;
//  static cFont          MenuFont;
  long                  Num;
/*****Local Variables End*****/

  // Initialize menu related data
  if(Purpose == INITPURPOSE) 
  {
	char MenuBG[256]; //I only need this in the init
	g_Game->m_Graphics.EnableLighting(FALSE); 
    // Create and set the menu vertices
    MenuVB.Create(&g_Game->m_Graphics, 4, MenuFVF,               \
                  sizeof(sMenuVertex));
    MenuVB.Set(0,4,Verts);

    // Load textures
	strcpy(MenuBG, g_Game->m_BasePath.c_str());
	strcat(MenuBG, "gui\\select.bmp");
    MenuSelect.Load(&g_Game->m_Graphics, MenuBG, D3DCOLOR_RGBA(0,0,0,255),D3DFMT_A1R5G5B5);

	strcpy(MenuBG, g_Game->m_BasePath.c_str());
	strcat(MenuBG, "gui\\menubd.bmp");
    MenuTexture.Load(&g_Game->m_Graphics, MenuBG);
	
	strcpy(MenuBG, g_Game->m_BasePath.c_str());
	strcat(MenuBG, "gui\\logo.bmp");
    MenuLogo.Load(&g_Game->m_Graphics, MenuBG, D3DCOLOR_RGBA(0,0,0,255),D3DFMT_A1R5G5B5);


  	LogoX = (g_Game->m_Width / 2) - (MenuLogo.GetWidth() / 2);
    SelectX = (g_Game->m_Width / 2) - (MenuSelect.GetWidth() / 2);
	StatusX = (g_Game->m_Width / 2) - 150;
    // Setup the menu camera
    MenuCam.Point(0.0f, 0.0f, -150.0f, 0.0f, 0.0f, 0.0f);

	g_Game->m_StatusWindow.Create(&g_Game->m_Graphics, "gui\\Border.bmp", g_Game->m_BasePath.c_str());
	g_Game->m_StatusWindow.Move(StatusX,300,300,50,D3DCOLOR_RGBA(0,64,128,255));
	g_Game->m_StatusWindow.m_Visible = false;

    return;

  }

  // Shutdown resources used in menu
  if(Purpose == SHUTDOWNPURPOSE) 
  {
    MenuVB.Free();
    MenuTexture.Free();
    MenuSelect.Free();
//    MenuFont.Free();
	MenuLogo.Free();
    return;
  }

  // Process a frame of menu
   if (!g_Game->CaptureMenuInput())
	   return;

  // Set the menu camera
  g_Game->m_Graphics.SetCamera(&MenuCam);

 // Rotate backdrop vertex buffer world position
 //  MenuPos.Rotate(0.0f, 0.0f, (float)timeGetTime() / 4000.0f);

  // Render the frame's graphics
  if(g_Game->m_Graphics.BeginScene() == TRUE) 
  {

    // Render backdrop (turning off Z-Buffering first)
    g_Game->m_Graphics.EnableZBuffer(FALSE);
    g_Game->m_Graphics.SetWorldPosition(&MenuPos);
    g_Game->m_Graphics.SetTexture(0, &MenuTexture);
    MenuVB.Render(0, 2, D3DPT_TRIANGLESTRIP);

    // Draw the game's title
    // MenuFont.Print("RF3D RPG Engine",0,16,640,0,0xFFFFFFFF,DT_CENTER);
    MenuLogo.Blit(LogoX,25);

    // Select option based on mouse position
    Num = g_Game->m_Mouse.GetYPos() - 126;
    if(Num >= 0) {
      Num /= 64;

      if(!Num || 
         (Num==1 && (g_Game->m_MenuOptions & MENU_BACK)) ||
         (Num==2 && (g_Game->m_MenuOptions & MENU_LOAD)) ||
         (Num==3 && (g_Game->m_MenuOptions & MENU_SAVE)) ||
         (Num == 4))
        MenuSelect.Blit(SelectX,Num*64+143);
    }
	
    // Draw enabled options
    g_Game->m_Font.Print("New Game", 0,150,g_Game->m_Width,0, 0xFFFFFFFF,DT_CENTER);

    if(g_Game->m_MenuOptions & MENU_BACK)
      g_Game->m_Font.Print("Back to Game",0,214,g_Game->m_Width,0, 0xFFFFFFFF,DT_CENTER);

    if(g_Game->m_MenuOptions & MENU_LOAD)
      g_Game->m_Font.Print("Load Game",0,278,g_Game->m_Width,0, 0xFFFFFFFF,DT_CENTER);

    if(g_Game->m_MenuOptions & MENU_SAVE)
      g_Game->m_Font.Print("Save Game",0,342,g_Game->m_Width,0, 0xFFFFFFFF,DT_CENTER);

    g_Game->m_Font.Print("Quit",0,406,g_Game->m_Width,0,0xFFFFFFFF,DT_CENTER);

	//blit cursor
    g_Game->m_Cursor.Blit(g_Game->m_Mouse.GetXPos(),g_Game->m_Mouse.GetYPos());

	g_Game->m_Graphics.EndScene();
  }
  g_Game->m_Graphics.Display();

}

void cApp::RenderStatusWindow()
{
	  // Render the frame's graphics
  if(m_Graphics.BeginScene() == TRUE) 
  {
	m_StatusWindow.Render("   Loading...");
	m_Graphics.EndScene();
  }
  m_Graphics.Display();

}

BOOL cApp::CaptureMenuInput()
{
/*****Local Variables Start*****/
	long                  Num;
/*****Local Variables End*****/


  // Exit game or return to game if ESC pressed
  if(m_Keyboard.GetKeyState(KEY_ESC) == TRUE) 
  {
    m_StateManager.Pop(this);
    return FALSE;
  }

  // See which option was selected if mouse button pressed
  if(m_Mouse.GetButtonState(MOUSE_LBUTTON) == TRUE) 
  {
    // Lock the mouse button and clear button state
    m_Mouse.SetLock(MOUSE_LBUTTON, TRUE);
    m_Mouse.SetButtonState(MOUSE_LBUTTON, FALSE);

    // Determine which, if any selection
    Num = m_Mouse.GetYPos() - 126;
    if(Num >= 0) 
	{
      Num /= 64;

      // Make sure option enabled 
      if(Num==1 && !(m_MenuOptions & MENU_BACK))
        return FALSE;
      if(Num==2 && !(m_MenuOptions & MENU_LOAD))
        return FALSE;
      if(Num==3 && !(m_MenuOptions & MENU_SAVE))
        return FALSE;

      // Pop the menu state
      m_StateManager.Pop(this);

      // Determine what to do based on selection
      switch(Num) 
	  {
        case 0: // New game
			NewGame();
			break;

        case 1: // Return to game
			ReturnToGame();
			break;

        case 2: // Load game
          // Prepare game data for loading game
  		    
			//temp only
			m_LevelFileName = m_inifile.ReadString("settings","levelfile");
			m_logfile.Log("LevelFile", m_LevelFileName);

			CreateScene();

			// Pop all states
			m_StateManager.PopAll(this);

			// Push game frame state
			m_StateManager.Push(MainGameFrame, this);

			break;

        case 3: // Save game
	        break;

        case 4: // Quit game
			ExitGame();
			break;
      }

      return FALSE;
    }
  }
	return TRUE;
}

void cApp::ExitGame()
{
	m_StateManager.PopAll();
}

void cApp::NewGame() 
{
/*****Local Variables Start*****/
	// Prepare game data for new game
	char tmpLvlFile[256];
/*****Local Variables End*****/

	m_StatusWindow.SetPercent(1);
	m_StatusWindow.m_Visible = true;	

	//start file
	m_LevelFileName = m_inifile.ReadString("settings","levelfile");
	m_logfile.Log("LevelFileName", m_LevelFileName);
	strcpy(tmpLvlFile, m_BasePath.c_str());
	strcat(tmpLvlFile, m_LevelFileName.c_str());
	m_LevelFile.LoadFile(tmpLvlFile);
    m_StatusWindow.SetPercent(10);
	RenderStatusWindow();

	CreateScene();

    m_StatusWindow.SetPercent(90);
	RenderStatusWindow();
	// Pop all states
	m_StateManager.PopAll(this);

	m_StatusWindow.SetPercent(95);
	RenderStatusWindow();
	// Push game frame state
	m_StateManager.Push(MainGameFrame, this);

}


void cApp::ReturnToGame()
{
	m_Graphics.EnableLighting(m_LevelFileData.UseLighting);
	// Pop all states
	m_StateManager.PopAll(this);
	m_StateManager.Push(MainGameFrame, this);
}

