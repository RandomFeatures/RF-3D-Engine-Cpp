#ifndef RF3D_GUI_H
#define RF3D_GUI_H


typedef struct 
{
  long XPos;
  long YPos;
  long Width;
  long Height;
  
} sFramePiece;

class cSimplePolyGUIWindow
{
protected:

    typedef struct sVertex {  // Custom vertex 
      float    x, y, z;  // Coordinates in screen space
      float    rhw;      // RHW value
      D3DCOLOR Diffuse;  // Diffuse color
    } sVertex;
	#define WINDOWFVF2 (D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1)
    cGraphics     *m_Graphics;  // Parent cGraphics object
    cFont          m_Font;      // Font object
    cVertexBuffer  m_WindowVB;  // Vertex buffer for window

//    char          *m_Text;        // Text to display
//    D3DCOLOR       m_TextColor;   // Color to draw text 
    long           m_XPos, m_YPos;     // Window coordinates
    long           m_Width, m_Height;  // Window dimensions
	D3DCOLOR       m_BackColor;
	cTexture	   m_Texture;

public:

	bool		   m_Visible;


	virtual void Create(cGraphics *Graphics, char *Filename, const char *BasePath);
	virtual void Free();
	virtual BOOL Move(long XPos, long YPos, long Width, long Height=0, D3DCOLOR BackColor = D3DCOLOR_RGBA(0,64,128,255));
	virtual BOOL Render(char *Text = "", BOOL Blended = TRUE, D3DCOLOR Color = D3DCOLOR_RGBA(255,255,255,255));
	void SetVertex();
};


class cBaseGUIWindow
{
protected:

    typedef struct sVertex {  // Custom vertex 
      float    x, y, z;  // Coordinates in screen space
      float    rhw;      // RHW value
      D3DCOLOR Diffuse;  // Diffuse color
    } sVertex;

    cGraphics     *m_Graphics;  // Parent cGraphics object
    cFont          m_Font;      // Font object
    cVertexBuffer  m_WindowVB;  // Vertex buffer for window

//    char          *m_Text;        // Text to display
//    D3DCOLOR       m_TextColor;   // Color to draw text 
    long           m_XPos, m_YPos;     // Window coordinates
    long           m_Width, m_Height;  // Window dimensions
	int			   m_WidthOffSet;
	int			   m_HeightOffSet;
	D3DCOLOR       m_BackColor;
	
	sFramePiece srcTopLeft;
	sFramePiece srcTopCenter;
	sFramePiece srcTopRight;
	sFramePiece srcLeftSide;
	sFramePiece srcRightSide;
	sFramePiece srcBottomLeft;
	sFramePiece srcBottomRight;
	sFramePiece srcBottomCenter;
	
	sFramePiece destTopLeft;
	sFramePiece destTopCenter;
	sFramePiece destTopRight;
	sFramePiece destLeftSide;
	sFramePiece destRightSide;
	sFramePiece destBottomLeft;
	sFramePiece destBottomRight;
	sFramePiece destBottomCenter;

	cTexture m_Texture;

public:

	bool		   m_Visible;


	virtual void Create(cGraphics *Graphics, char *Filename, const char *BasePath);
	virtual void Free();
	virtual BOOL Move(long XPos, long YPos, long Width, long Height=0, D3DCOLOR BackColor = D3DCOLOR_RGBA(0,64,128,255));
	virtual BOOL Render(char *Text = "", BOOL Blended = TRUE, D3DCOLOR Color = D3DCOLOR_RGBA(255,255,255,255));
	void CaclDest();
	void SetVertex();
};

class cMessageGUI : cBaseGUIWindow
{
private:
	int			   m_FixedX;
	int			   m_FixedY;
	bool		   m_Showing;
	bool		   m_Hiding;

public:
//    cMessageGUI();
//	~cMessageGUI();
	bool		   m_Visible;
	void Create(cGraphics *Graphics, char *Filename, const char *BasePath);
	BOOL Render(char *Text = "", BOOL Blended  = TRUE, D3DCOLOR Color = D3DCOLOR_RGBA(255,255,255,255));
	BOOL Move(long XPos, long YPos, long Width, long Height=0, D3DCOLOR BackColor = D3DCOLOR_RGBA(0,64,128,255));
	void Free();
	void ShowConsole();
	void HideConsole();
};


class cStatusBar : cBaseGUIWindow
{
protected:
	cTexture	m_StatusBar;
	int			m_Percent;
	int			m_sbRight;

public:
	bool		   m_Visible;

	void SetPercent(int per);
	int GetPercent();
	void IncPrecent(int per);
	virtual void Create(cGraphics *Graphics, char *Filename, const char *BasePath);
	virtual void Free();
	virtual BOOL Move(long XPos, long YPos, long Width, long Height=0, D3DCOLOR BackColor = D3DCOLOR_RGBA(0,64,128,255));
	virtual BOOL Render(char *Text = "", BOOL Blended = TRUE, D3DCOLOR Color = D3DCOLOR_RGBA(255,255,255,255));
};



#endif