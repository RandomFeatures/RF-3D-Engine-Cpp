#ifndef _RFAPP_H_
#define _RFAPP_H_

// Local includes
#include "Frustum.h"
#include "NodeTree.h"
#include "SkyBox.h"
#include "Window.h"
#include "tinyxml.h"
#include "RF3d_LogFile.h"
//#include "RF3d_Character.h"


typedef struct 
{
  BOOL			UseLighting;
  int			AmbientRed;
  int			AmbientBlue;
  int			AmbientGreen;
  std::string	TexturePath;
  std::string   LevelXFile;
  float			StartX;
  float			StartY;
  float			StartZ;
  std::string	SkyTop;
  std::string	SkyBottom;
  std::string	SkyLeft;
  std::string	SkyRight;
  std::string	SkyFront;
  std::string	SkyBack;

} sLevelFileInfo;


class cRFApp : public cApplication
{

  protected:

    cGraphics       m_Graphics;
    cCamera         m_Camera;
    cLight          m_Light;
	cFont           m_Font;
//    cSound          m_Sound;
//    cSoundChannel   m_SndChannel[3];

    cSkyBox         m_SkyBox;
    cMesh           m_Mesh;
	cDataPackage    m_DataPackage;
	TiXmlDocument	m_LevelFile;
	sLevelFileInfo	m_LevelFileData;

//	sMapFileFormat *m_LevelFile;
    float           m_XPos, m_YPos, m_ZPos;

  
    //Input device
	cInput          m_Input;     // cInput object
    cInputDevice    m_Keyboard;  // Keyboard input object
    cInputDevice    m_Mouse;     // Mouse input object

	unsigned int	m_iMaxFrameRate; // max frame rate
	BOOL			m_bCapFrameRate; // apply max frame rate
//	BOOL			m_bFullScreen;

	//paths
	std::string		m_BasePath;
	std::string		m_TexturePath;
	std::string		m_LevelFileName;

//    cCharacterController m_CharController;


  public:

	std::string		m_MeshPath;
	cLogFile        m_logfile;
    cNodeTreeMesh   m_NodeTreeMesh;

    void CaptureInput();
 
    //Control frame rate
	void EnableFrameRate(BOOL bEnable);
    int GetMaxFrameRate();
    void SetMaxFrameRate(int iMax);

	cRFApp();
    virtual BOOL Init();
    virtual BOOL Shutdown();
	void setMouseClipping();
	void ClearMouseClipping();




protected:
    virtual BOOL SetupCamera(); 
    virtual BOOL CreateRenderer();
    virtual BOOL CreateScene();  

};


#endif
