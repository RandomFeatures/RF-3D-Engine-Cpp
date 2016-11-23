#ifndef _WINMAIN_H_
#define _WINMAIN_H_

#include "ini.h"

class cApp : public cRFApp
{
  protected:

	long            m_MenuOptions;
	float           m_fAngle;
	char            m_path[256];

	cIniFile        m_inifile;
	cTexture		m_Cursor;
	cTexture		m_CrossHair;
//	cSimplePolyGUIWindow	m_CrossHair;
	D3DLIGHT8		Light;
	cStateManager   m_StateManager;
	cMessageGUI		m_DebugWindow;
	cStatusBar  	m_StatusWindow;
//	List <std::string> m_ConsoleList;	
//	cPython			m_PyScript;
	void ParseLevelFile();
	void LoadScriptDLL();
	void EnableLighting(BOOL active);

  public:

//	cGameObjectController m_GameObjCntrler;
	BOOL m_bShutDown;
	/***** Overwrite from RF3d_RFApp.h ****/  
	virtual BOOL Init();
    virtual BOOL Shutdown();
    virtual BOOL Frame();
    virtual BOOL SetupCamera(); 
    virtual BOOL CreateScene(); 

	//For Python
	void TakeScreenShot(IDirect3DDevice8* device, char* file_name, int screenx, int screeny);
    void NewGameObject(int ObjectType, char *MeshFile, float X, float Y, float Z, float Dir);
	void AddLogEntry();

	/**** Local Constructor ****/
	cApp();

  protected:
	/***** See GameWindow.cpp *****/
	void static MainGameFrame(void *Ptr, long Purpose);
	void CaptureGameInput(float &XMove, float &ZMove, unsigned long Elapsed);
	void RenderInGameGUI();
	void ControlPlayerMovement();
	void RenderStatusWindow();


	/***** See MainMenu.cpp *****/
	void static MainMenuFrame(void *Ptr, long Purpose);
	BOOL CaptureMenuInput();
  public:
	void NewGame();
	void ReturnToGame();
	void ExitGame();

  protected:
	/***** See ConsoleWindo.cpp *****/
    void static ConsoleFrame(void *Ptr, long Purpose);
	BOOL CaptureConsoleInput();
  public:
	void DisplayLogInConsole();


};

extern cApp *g_Game;


#endif
