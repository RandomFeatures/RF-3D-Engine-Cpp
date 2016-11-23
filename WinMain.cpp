/**************************************************
RF3d_WinMain.cpp
Random Features 3D RPG Main Window

by Allen Halsted (12 June 2002)

Required libraries:

**************************************************/

#include "RF3d_Global.h"

#include "xml.h"
#include <ini.h>
#include <mmsystem.h>


// Local includes
#include "Window.h"
#include "Frustum.h"
#include "NodeTree.h"
#include "SkyBox.h"
#include "WinMain.h"

//for testing
const char* gpcText = 
    "If there's anything more important than my ego around,\n"
	"I want it hunted and killed now!\n"
    "\n"
    "\n"
    "Only the good die young. That is why immortality is\n" 
	"reserved for the greatest of evils.\n"
    "\n"
    "\n"
	"The two rules for success in life are:\n"
	"1) Never tell them everything you know\n"
    "\n"
    "\n"
	"What if the Hokey Pokey is really what it's all about?";


// Global names of character meshes
char *g_CharMeshNames[] = 
{
    { "Resources\\characters\\Warrior.x" },   // Mesh # 0
    { "Resources\\characters\\Yodan.x"   }    // Mesh # 1
};


//Global Ref to the Application
cApp  *g_Game;

//---------------------------------------------------------------
cApp::cApp()
{ 

  char strBuffer[256];

  //get the current path and find the ini file
  GetCurrentDirectory(256,strBuffer);
  strcat(strBuffer, "\\rf3d.ini");
  strcpy(m_path, strBuffer);	

  m_inifile.Create(strBuffer); //create the inifile
  
  
  m_logfile.Create("RF3d.Log"); //create the log file

  //? Full screen | windowed
  m_bFullScreen = m_inifile.ReadBool("settings","fullscreen");
  
  
  //get the screen size and setup the window
  if (m_bFullScreen)
  {
	m_Width = m_inifile.ReadInteger("fullscreen","width",800);
	m_Height = m_inifile.ReadInteger("fullscreen","height",600);
    m_Style  = WS_DLGFRAME;
	m_logfile.Log("FullScreen Mode");
  }
  else
  {
	m_Width = m_inifile.ReadInteger("window","width",400);
	m_Height = m_inifile.ReadInteger("window","height",320);
    m_Style  = WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX;
	m_logfile.Log("Window Mode");
  }
  	
  strcpy(m_Class, "RF3dRPG");
  strcpy(m_Caption, "Random Features 3D RPG Engine");
  
  

  //check the ini for frame rate control
  EnableFrameRate(m_inifile.ReadBool("settings","lockframerate"));
  SetMaxFrameRate(m_inifile.ReadInteger("settings","framerate",30)); // cap the frame rate at 30fps
  
  //Set The Global
 g_Game = (cApp*)this;

} 

BOOL cApp::Init()
{
	std::string tmpBuffer;
	char cursor[256];
	char strBuffer[256];

	cRFApp::Init(); //inherited

	ShowMouse(FALSE);
    m_logfile.Log("Hide Cursor");
	
    m_bShutDown = FALSE;
    //get the current path and find the ini file
    GetCurrentDirectory(256,strBuffer);
	//Start The Python Engine
//	if(m_PyScript.Initialize(strBuffer))
//	{
//		m_logfile.Log("Python Init");
//		m_logfile.Log("Python Path", Py_GetPath());
//	}
//		m_logfile.Log("MyPath", m_PyScript.MyPath);

	// Create a font
    m_Font.Create(&m_Graphics, "Arial", 12, TRUE);
	m_logfile.Log("Default Font Created");

	//get the resource data from the ini file
	m_BasePath = m_inifile.ReadString("settings","basepath");
	m_logfile.Log("BasePath",m_BasePath);

	//texture path
	m_TexturePath = m_BasePath + m_inifile.ReadString("settings","textures");
	m_logfile.Log("TexturePath",m_TexturePath);

	//Mesh path
	m_MeshPath = m_BasePath + m_inifile.ReadString("settings","meshes");
	m_logfile.Log("MeshPath",m_MeshPath);
	
	
	strcpy(cursor, m_BasePath.c_str());
	strcat(cursor, "gui\\cursor.bmp");
    m_Cursor.Load(&m_Graphics, cursor, D3DCOLOR_RGBA(0,0,0,255),D3DFMT_A1R5G5B5);
	m_logfile.Log(cursor);

	strcpy(cursor, m_BasePath.c_str());
	strcat(cursor, "gui\\crosshair.bmp");
    m_CrossHair.Load(&m_Graphics, cursor, D3DCOLOR_RGBA(0,0,0,255),D3DFMT_A1R5G5B5);
//	m_CrossHair.Create(&m_Graphics, "gui\\crosshair.bmp", m_BasePath.c_str());
	m_logfile.Log(cursor);

	m_MenuOptions = 0;
	//push the main menu onto the stack
    m_StateManager.Push(MainMenuFrame, this);

	m_logfile.Log("CurrentState", "MenuFrame");
    
	return TRUE;
}

BOOL cApp::Shutdown()
{
//    m_CharController.Free();

  //  m_PyScript.Free(); //shut down Python

//	m_ConsoleList.Clear();

	m_DebugWindow.Free();

	m_DataPackage.Free();

	m_Cursor.Free();

	m_CrossHair.Free();

//    m_GameObjCntrler.Free();

    m_Font.Free();

	m_logfile.Close();

	cRFApp::Shutdown(); //inherited
 
	// clean up state manager
    m_StateManager.PopAll(this);
    

  return TRUE;
}

BOOL cApp::Frame()
{

  static DWORD UpdateCounter = timeGetTime();


  if(m_bCapFrameRate)
  {
	  // Lock to 30 fps
	  if(timeGetTime() < UpdateCounter + m_iMaxFrameRate)
		return TRUE;
	  UpdateCounter = timeGetTime();
  }

	
  CaptureInput(); //see what the user wants

  if (m_bShutDown)
	m_StateManager.PopAll(this);
  

  int LastState = m_StateManager.Process(this); // if no states are left then exit;

  // Process state, returning result
  return LastState;
}

void cApp::ParseLevelFile()
{
	
	TiXmlElement* worldElement = 0;
	TiXmlElement* meshElement = 0;
	TiXmlElement* skyboxElement = 0;
	TiXmlElement* lightElement = 0;
	TiXmlElement* startElement = 0;

	
	//Establish the WorldBlock
	worldElement = GetXMLElement(&m_LevelFile, "World");
	if (worldElement == NULL){ m_logfile.Log("Error : No World Tag in XML file");}
    
	lightElement = GetXMLElement(worldElement, "Light");
	if (lightElement == NULL){ m_logfile.Log("Error : No Light Tag in XML file");}

	m_LevelFileData.UseLighting = StrIsTrue(GetXMLDataStr(lightElement, "Enabled"));
    m_LevelFileData.AmbientRed = GetXMLDataInt(lightElement,"Red");
	m_LevelFileData.AmbientGreen = GetXMLDataInt(lightElement,"Green");
	m_LevelFileData.AmbientBlue = GetXMLDataInt(lightElement,"Blue");

	//Get the mesh file name
	meshElement = GetXMLElement(worldElement,"Mesh");
	if (meshElement == NULL){ m_logfile.Log("Error : No Mesh Tag in XML file");}

	m_LevelFileData.LevelXFile = m_MeshPath + GetXMLDataStr(meshElement,NULL);

	//Get the player start postion
	startElement = GetXMLElement(worldElement,"PlayerStart");
	if (startElement == NULL){ m_logfile.Log("Error : No Start Tag in XML file");}

	m_LevelFileData.StartX = GetXMLDataFloat(startElement, "XPos");
	m_LevelFileData.StartY = GetXMLDataFloat(startElement, "YPos");
	m_LevelFileData.StartZ = GetXMLDataFloat(startElement, "ZPos");


	skyboxElement = GetXMLElement(worldElement,"SkyBox");
	if (skyboxElement == NULL){ m_logfile.Log("Error : No SkyBox Tag in XML file");}

	m_LevelFileData.SkyTop = m_TexturePath + GetXMLDataStr(skyboxElement,"Top") ;
	m_LevelFileData.SkyBottom = m_TexturePath + GetXMLDataStr(skyboxElement,"Bottom");
    m_LevelFileData.SkyLeft = m_TexturePath + GetXMLDataStr(skyboxElement,"Left");
	m_LevelFileData.SkyRight = m_TexturePath + GetXMLDataStr(skyboxElement,"Right");
	m_LevelFileData.SkyFront = m_TexturePath + GetXMLDataStr(skyboxElement,"Front");
	m_LevelFileData.SkyBack = m_TexturePath + GetXMLDataStr(skyboxElement, "Back");

}

BOOL cApp::SetupCamera()
{
	//TODO -- Setup the camera
    cRFApp::SetupCamera();

	//set perspective D3DX_PI/4,1.25f,1.0f,650.0f
    m_Graphics.SetPerspective(D3DX_PI/4,1.25f,1.0f,10000.0f);

//	m_Graphics.SetPerspective(D3DX_PI/4, 1.3333f, 1.0f, 20000.0f);

	// Position view at origin
    m_XPos = m_YPos = m_ZPos = 0.0f;
//	m_XPos = -800.0f;
//  m_YPos = 0.0f;
//  m_ZPos = -800.0f;

    return true;
}



BOOL cApp::CreateScene()
{
	cRFApp::CreateScene();

	char tmpStr[256];


	ParseLevelFile();
	m_StatusWindow.SetPercent(40);
	RenderStatusWindow();

	// Enable lighting and setup light
	if (m_LevelFileData.UseLighting)
	{
        
		m_logfile.Log("UseLighting = true");
   		m_Graphics.EnableLighting(m_LevelFileData.UseLighting);
		m_Graphics.SetAmbientLight(m_LevelFileData.AmbientRed,   \
								   m_LevelFileData.AmbientGreen, \
								   m_LevelFileData.AmbientBlue);

		sprintf(tmpStr, "R %d  G %d  B %d", \
          m_LevelFileData.AmbientRed,       \
		  m_LevelFileData.AmbientGreen,     \
		  m_LevelFileData.AmbientBlue);
		m_logfile.Log("Ambient Light", tmpStr);

		//m_Graphics.SetLight(0, &m_Light);
//		m_Graphics.EnableLight(0, TRUE);
//		m_Light.SetAttenuation0(0.5f);
//		m_Light.SetRange(1000.0f);
	}
	else 
	{
        m_logfile.Log("UseLighting = false");
		m_Graphics.EnableLighting(m_LevelFileData.UseLighting);
	}


	// Set light data, color, position, and range
//	ZeroMemory(&Light, sizeof(Light));
//	Light.Type = D3DLIGHT_POINT;
//	Light.Diffuse.r = Light.Ambient.r = 5.5f;
//	Light.Diffuse.g = Light.Ambient.g = 0.5f;
//	Light.Diffuse.b = Light.Ambient.b = 2.0f;
//	Light.Diffuse.a = Light.Ambient.a = 3.0f;
//	Light.Range = 500.0f;
//	Light.Attenuation0 = 0.5f;
//	Light.Position.x = -800.0f;
//	Light.Position.y = 25.0f;
//	Light.Position.z = -550.0f;

	// Set and enable the light


//	m_Graphics.SetLight(0, &Light);
//	m_Graphics.EnableLight(0, TRUE);
	m_StatusWindow.SetPercent(50);
	RenderStatusWindow();


	//Get the mesh file name
	// Load the mesh and create an NodeTree mesh from it
	m_Mesh.Load(&m_Graphics, m_LevelFileData.LevelXFile.c_str(), m_TexturePath.c_str());
	m_NodeTreeMesh.Create(&m_Graphics, &m_Mesh, QUADTREE);
    m_logfile.Log("mesh filename",m_LevelFileData.LevelXFile.c_str());
	m_StatusWindow.SetPercent(60);
	RenderStatusWindow();
	
	//set the player start
	m_XPos = m_LevelFileData.StartX;
	m_YPos = m_LevelFileData.StartY;
	m_ZPos = m_LevelFileData.StartZ;
	sprintf(tmpStr, "X %d : Y %d : Z %d", \
		    m_XPos, m_YPos, m_ZPos);
	m_logfile.Log("PlayerStart", tmpStr);

	// Setup the sky box
	m_SkyBox.Create(&m_Graphics);

	m_SkyBox.LoadTexture(0, m_LevelFileData.SkyTop.c_str());
	m_SkyBox.LoadTexture(1, m_LevelFileData.SkyBottom.c_str());
	m_SkyBox.LoadTexture(2, m_LevelFileData.SkyLeft.c_str());
	m_SkyBox.LoadTexture(3, m_LevelFileData.SkyRight.c_str());
	m_SkyBox.LoadTexture(4, m_LevelFileData.SkyFront.c_str());
	m_SkyBox.LoadTexture(5, m_LevelFileData.SkyBack.c_str());
	m_logfile.Log("Create SkyBox");

	m_StatusWindow.SetPercent(70);
	RenderStatusWindow();
	

	m_DebugWindow.Create(&m_Graphics, "gui\\Border.bmp", m_BasePath.c_str());
	m_DebugWindow.Move(2,2,270,75,D3DCOLOR_RGBA(0,64,128,255));
	m_StatusWindow.SetPercent(75);
	RenderStatusWindow();

	
	char tmpMeshPath[256];
	char tmpTexturePath[256];
	strcpy(tmpMeshPath, m_MeshPath.c_str());
	strcpy(tmpTexturePath, m_TexturePath.c_str());
	// This should come from the lvl file
	strcat(tmpMeshPath, "warrior.x");

	  // Initialize the character controller
	m_logfile.Log("GameObjCntrler Init");
//	m_GameObjCntrler.Create(&m_Graphics,tmpTexturePath, this);
	m_logfile.Log("GameObjCntrler Created");


	// This should come from the lvl file
//	m_GameObjCntrler.AddGameObj(3,tmpMeshPath,-800,0,-550,3.0f);

	strcpy(tmpMeshPath, m_MeshPath.c_str());
	strcpy(tmpTexturePath, m_TexturePath.c_str());
	// This should come from the lvl file
	strcat(tmpMeshPath, "grey.x");

//	m_GameObjCntrler.AddGameObj(2,tmpMeshPath,-850,0,-500,3.0f);

    return true;
}


void cApp::EnableLighting(BOOL active)
{
	if (active)
	{
  		m_Graphics.EnableLighting(TRUE); 
		m_Graphics.SetAmbientLight(m_LevelFileData.AmbientRed,   \
								   m_LevelFileData.AmbientGreen, \
								   m_LevelFileData.AmbientBlue);

		// Set light data, color, position, and range
		ZeroMemory(&Light, sizeof(Light));
		Light.Type = D3DLIGHT_POINT;
		Light.Diffuse.r = Light.Ambient.r = 5.5f;
		Light.Diffuse.g = Light.Ambient.g = 0.5f;
		Light.Diffuse.b = Light.Ambient.b = 2.0f;
		Light.Diffuse.a = Light.Ambient.a = 3.0f;
		Light.Range = 500.0f;
		Light.Attenuation0 = 0.5f;
		Light.Position.x = -800.0f;
		Light.Position.y = 25.0f;
		Light.Position.z = -550.0f;
//		m_Graphics.SetLight(0, &Light);
		m_Graphics.EnableLight(0, TRUE);
	}
	else
	{
		m_Graphics.EnableLighting(FALSE); 
//  		m_Graphics.SetAmbientLight(255,255,255);
	}
}



void cApp::TakeScreenShot(IDirect3DDevice8* device, char* file_name, int screenx, int screeny)
{
   IDirect3DSurface8* frontbuf; //this is our pointer to the memory location containing our copy of the
                                //front buffer

   //now we create the image that our screen shot will be copied into
   //NOTE: Surface format of the front buffer is D3DFMT_A8R8G8B8 when it is returned
   device->CreateImageSurface(screenx, screeny, D3DFMT_A8R8G8B8, &frontbuf);

   //now we copy the front buffer into our surface
   HRESULT hr = device->GetFrontBuffer(frontbuf);

   //error checking
   if(hr != D3D_OK)
   {
      m_logfile.Log("ERROR");
	  //do error handling etc...
      frontbuf->Release(); //release the surface so there is no memory leak
      return;
   }

   //now write our screen shot to a bitmap file
   //the last 2 params are NULL because we want the entire front buffer and no palette
   D3DXSaveSurfaceToFile(file_name, D3DXIFF_BMP, frontbuf, NULL, NULL);

   //release the surface so there is no memory leak
   frontbuf->Release();
}

void cApp::NewGameObject(int ObjectType, char *MeshFile, float X, float Y, float Z, float Dir)
{
/*****Local Variables Start*****/
	char tmpMeshPath[256];
/*****Local Variables End*******/
	strcpy(tmpMeshPath, m_MeshPath.c_str());
	strcat(tmpMeshPath, MeshFile);

//  m_GameObjCntrler.AddGameObj(ObjectType,tmpMeshPath,X,Y,Z,Dir);
}

void cApp::LoadScriptDLL()
{
//	PyNewGame();
}

void cApp::AddLogEntry()
{
   m_logfile.Log("Python Works");
}


int PASCAL WinMain(HINSTANCE hInst, HINSTANCE hPrev, LPSTR szCmdLine, int nCmdShow)
{
  cApp App;
  return App.Run();
}

