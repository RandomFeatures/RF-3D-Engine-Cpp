#include "RF3d_Global.h"

#include "RF3d_GUIControl.h"


void cSimplePolyGUIWindow::Create(cGraphics *Graphics, char *Filename, const char *BasePath)
{

    // Error checking
    m_Graphics = Graphics;

	char strTmp[256];
//	strcpy(strTmp, BasePath);
//	strcat(strTmp, Filename);
//  m_Texture.Load(m_Graphics, strTmp, D3DCOLOR_RGBA(0,0,0,255),D3DFMT_A1R5G5B5);

	strcpy(strTmp, BasePath);
	strcat(strTmp, "gui\\crosshair.bmp");
    m_Texture.Load(m_Graphics, strTmp, D3DCOLOR_RGBA(0,0,0,255),D3DFMT_A1R5G5B5);

	m_Font.Create(m_Graphics, "MS Sans Serif", 8);

    // Create new vertex buffer
	
    m_WindowVB.Create(m_Graphics, 4, WINDOWFVF2, sizeof(sVertex));
}


void cSimplePolyGUIWindow::Free()
{
	m_Font.Free();
	m_Texture.Free();
    m_WindowVB.Free();  // Free vertex buffer

}

BOOL cSimplePolyGUIWindow::Render(char *Text, BOOL Blended, D3DCOLOR Color)
{

    if (!m_Visible) 
		return true;

	if (Blended)
	{
		// Render using alphablending
		m_Graphics->EnableAlphaBlending(TRUE, D3DBLEND_SRCCOLOR, D3DBLEND_DESTCOLOR);
	}
	
	// Set rendering states
	
	m_Graphics->EnableZBuffer(FALSE);
	if (!m_Graphics->SetTexture(0, &m_Texture)) 
		strcpy(Text, "-");

    //m_Graphics->EnableAlphaTesting(TRUE);

	//Render the background
    m_WindowVB.Render(0,2,D3DPT_TRIANGLESTRIP);
//	m_WindowVB.Render(4,2,D3DPT_TRIANGLESTRIP);

  //  m_Graphics->EnableAlphaTesting(FALSE);
    if (Blended)
	{
		// Display alpha blending to render pointer
		m_Graphics->EnableAlphaBlending(FALSE);
	}

    m_Graphics->EnableZBuffer(TRUE);
    //write the text
	m_Font.Print(Text, m_XPos+10, m_YPos+10,               \
                          m_Width-12,m_Height-12,          \
                          Color, DT_WORD_ELLIPSIS);

	m_Graphics->SetTexture(0, NULL); 
	return true;
}


BOOL cSimplePolyGUIWindow::Move(long XPos, long YPos,                      \
                   long Width, long Height,                   \
                   D3DCOLOR BackColor)
{
	// Save the coordinates and calculate height if needed
	m_XPos  = XPos;
	m_YPos  = YPos;
	m_Width = Width;
	m_Height = Height;
	m_BackColor = BackColor;

	SetVertex();
 
    return TRUE;
}

void cSimplePolyGUIWindow::SetVertex()
{
  sVertex Verts[4];
  long i;

  // Clear the vertex data
  for(i=0;i<4;i++) 
  {
    Verts[i].z = 0.0f;
    Verts[i].rhw = 1.0f;
    Verts[i].Diffuse = 0xFFFFFFFF;
  }

  // Setup the text window
  Verts[0].x = (float)m_XPos+2.0f;
  Verts[0].y = (float)m_YPos+2.0f;
  Verts[0].Diffuse = m_BackColor;
  Verts[1].x = (float)(m_XPos+m_Width)-2.0f;
  Verts[1].y = (float)m_YPos+2.0f;
  Verts[1].Diffuse = m_BackColor;
  Verts[2].x = (float)m_XPos+2.0f;
  Verts[2].y = (float)(m_YPos+m_Height)-2.0f;
  Verts[2].Diffuse = m_BackColor;
  Verts[3].x = (float)(m_XPos+m_Width)-2.0f;
  Verts[3].y = (float)(m_YPos+m_Height)-2.0f;
  Verts[3].Diffuse = m_BackColor;

  m_WindowVB.Set(0,4,&Verts);  // Set the vertices

}


//----------------------------------------------------------------


void cBaseGUIWindow::Create(cGraphics *Graphics, char *Filename, const char *BasePath)
{

    // Error checking
    m_Graphics = Graphics;

	char strTmp[256];
	strcpy(strTmp, BasePath);
	strcat(strTmp, Filename);
    m_Texture.Load(m_Graphics, strTmp, D3DCOLOR_RGBA(0,0,0,255),D3DFMT_A1R5G5B5);

	m_Font.Create(m_Graphics, "MS Sans Serif", 8);

    // Create new vertex buffer
    m_WindowVB.Create(m_Graphics, 4, WINDOWFVF, sizeof(sVertex));
	
	srcTopLeft.XPos = 0;
	srcTopLeft.YPos = 0;
	srcTopLeft.Height = 16;
	srcTopLeft.Width = 16;
	
	srcTopCenter.XPos = 79;
	srcTopCenter.YPos = 0;
	srcTopCenter.Height = 9;
	srcTopCenter.Width = 73;

	srcTopRight.XPos = 57;
	srcTopRight.YPos = 0;
	srcTopRight.Height = 16;
	srcTopRight.Width = 16;

	srcLeftSide.XPos = 26;
	srcLeftSide.YPos = 0;
	srcLeftSide.Height = 32;
	srcLeftSide.Width = 7;

	srcRightSide.XPos = 40;
	srcRightSide.YPos = 0;
	srcRightSide.Height = 32;
	srcRightSide.Width = 9;

	srcBottomLeft.XPos = 0;
	srcBottomLeft.YPos = 25;
	srcBottomLeft.Height = 16;
	srcBottomLeft.Width = 16;

	srcBottomRight.XPos = 57;
	srcBottomRight.YPos = 25;
	srcBottomRight.Height = 16;
	srcBottomRight.Width = 16;

	srcBottomCenter.XPos = 79;
	srcBottomCenter.YPos = 14;
	srcBottomCenter.Height = 8;
	srcBottomCenter.Width = 73;
	
}


void cBaseGUIWindow::Free()
{
	m_Font.Free();
	m_Texture.Free();
    m_WindowVB.Free();  // Free vertex buffer

}

BOOL cBaseGUIWindow::Render(char *Text, BOOL Blended, D3DCOLOR Color)
{

    if (!m_Visible) 
		return true;

	if (Blended)
	{
		// Render using alphablending
		m_Graphics->EnableAlphaBlending(TRUE, D3DBLEND_SRCCOLOR, D3DBLEND_DESTCOLOR);
	}
	
	// Set rendering states
	m_Graphics->SetTexture(0, NULL); // empty backgound... could add an image in later
	m_Graphics->EnableZBuffer(FALSE);

	//Render the background
    m_WindowVB.Render(0,2,D3DPT_TRIANGLESTRIP);
	m_WindowVB.Render(4,2,D3DPT_TRIANGLESTRIP);

    if (Blended)
	{
		// Display alpha blending to render pointer
		m_Graphics->EnableAlphaBlending(FALSE);
	}

    //write the text
	m_Font.Print(Text, m_XPos+10, m_YPos+10,               \
                          m_Width-12,m_Height-12,          \
                          Color, DT_WORD_ELLIPSIS);


	//Draw the border
	int iLoop;

	for (iLoop = 0; iLoop < m_WidthOffSet; iLoop ++) 
	{
		
		if (destTopCenter.XPos + (srcTopCenter.Width * iLoop) + srcTopCenter.Width > (m_XPos + m_Width))
		{
			int i = (destTopCenter.XPos + (srcTopCenter.Width * iLoop) + srcTopCenter.Width) - (m_XPos + m_Width);
  			//Top Center
			m_Texture.Blit(destTopCenter.XPos + (srcTopCenter.Width * iLoop),destTopCenter.YPos,srcTopCenter.XPos,srcTopCenter.YPos,srcTopCenter.Width - i,srcTopCenter.Height);	
			//bottom Center
  			m_Texture.Blit(destBottomCenter.XPos + (srcBottomCenter.Width * iLoop),destBottomCenter.YPos,srcBottomCenter.XPos,srcBottomCenter.YPos,srcBottomCenter.Width - i,srcBottomCenter.Height);
		}
		else
		{
    		//Top Center
			m_Texture.Blit(destTopCenter.XPos + (srcTopCenter.Width * iLoop),destTopCenter.YPos,srcTopCenter.XPos,srcTopCenter.YPos,srcTopCenter.Width,srcTopCenter.Height);

			//bottom Center
			m_Texture.Blit(destBottomCenter.XPos + (srcBottomCenter.Width * iLoop),destBottomCenter.YPos,srcBottomCenter.XPos,srcBottomCenter.YPos,srcBottomCenter.Width,srcBottomCenter.Height);
		}

	}

	for (iLoop = 0; iLoop < m_HeightOffSet; iLoop ++) 
	{
		
		if (destLeftSide.YPos+(srcLeftSide.Height * iLoop) + srcLeftSide.Height > (m_YPos + m_Height))
		{
			int i = (destLeftSide.YPos+(srcLeftSide.Height * iLoop) + srcLeftSide.Height) - (m_YPos + m_Height);
			//Left Side
			m_Texture.Blit(destLeftSide.XPos,destLeftSide.YPos+(srcLeftSide.Height * iLoop),srcLeftSide.XPos,srcLeftSide.YPos,srcLeftSide.Width,srcLeftSide.Height -i);

			//Right Side
			m_Texture.Blit(destRightSide.XPos,destRightSide.YPos+(srcRightSide.Height * iLoop),srcRightSide.XPos,srcRightSide.YPos,srcRightSide.Width,srcRightSide.Height - i);
		}
		else
		{
			//Left Side
			m_Texture.Blit(destLeftSide.XPos,destLeftSide.YPos+(srcLeftSide.Height * iLoop),srcLeftSide.XPos,srcLeftSide.YPos,srcLeftSide.Width,srcLeftSide.Height);

			//Right Side
			m_Texture.Blit(destRightSide.XPos,destRightSide.YPos+(srcRightSide.Height * iLoop),srcRightSide.XPos,srcRightSide.YPos,srcRightSide.Width,srcRightSide.Height);
		}
	}


	//Top Left
	m_Texture.Blit(destTopLeft.XPos,destTopLeft.YPos,srcTopLeft.XPos,srcTopLeft.YPos,srcTopLeft.Width,srcTopLeft.Height);

	//bottom Left
	m_Texture.Blit(destBottomLeft.XPos,destBottomLeft.YPos,srcBottomLeft.XPos,srcBottomLeft.YPos,srcBottomLeft.Width,srcBottomLeft.Height);

	//Top Right
	m_Texture.Blit(destTopRight.XPos,destTopRight.YPos,srcTopRight.XPos,srcTopRight.YPos,srcTopRight.Width,srcTopRight.Height);

	//Bottom Right
	m_Texture.Blit(destBottomRight.XPos,destBottomRight.YPos,srcBottomRight.XPos,srcBottomRight.YPos,srcBottomRight.Width,srcBottomRight.Height);
	
	return true;
}


BOOL cBaseGUIWindow::Move(long XPos, long YPos,                      \
                   long Width, long Height,                   \
                   D3DCOLOR BackColor)
{
	// Save the coordinates and calculate height if needed
	m_XPos  = XPos;
	m_YPos  = YPos;
	m_Width = Width;
	m_Height = Height;
	m_BackColor = BackColor;

	m_HeightOffSet = (Height / srcLeftSide.Height) + 1;

	m_WidthOffSet = (Width / srcTopCenter.Width) + 1;


	SetVertex();
 
    CaclDest();

    return TRUE;
}

void cBaseGUIWindow::SetVertex()
{
  sVertex Verts[4];
  long i;

  // Clear the vertex data
  for(i=0;i<4;i++) 
  {
    Verts[i].z = 0.0f;
    Verts[i].rhw = 1.0f;
    Verts[i].Diffuse = 0xFFFFFFFF;
  }

  // Setup the text window
  Verts[0].x = (float)m_XPos+2.0f;
  Verts[0].y = (float)m_YPos+2.0f;
  Verts[0].Diffuse = m_BackColor;
  Verts[1].x = (float)(m_XPos+m_Width)-2.0f;
  Verts[1].y = (float)m_YPos+2.0f;
  Verts[1].Diffuse = m_BackColor;
  Verts[2].x = (float)m_XPos+2.0f;
  Verts[2].y = (float)(m_YPos+m_Height)-2.0f;
  Verts[2].Diffuse = m_BackColor;
  Verts[3].x = (float)(m_XPos+m_Width)-2.0f;
  Verts[3].y = (float)(m_YPos+m_Height)-2.0f;
  Verts[3].Diffuse = m_BackColor;

  m_WindowVB.Set(0,4,&Verts);  // Set the vertices

}

void cBaseGUIWindow::CaclDest()
{
  
	
	destTopLeft.XPos = m_XPos;
	destTopLeft.YPos = m_YPos;

	destTopCenter.XPos = m_XPos;
	destTopCenter.YPos = m_YPos;

	destTopRight.XPos = (m_XPos + m_Width) - srcTopRight.Width;
	destTopRight.YPos = m_YPos;

	destLeftSide.XPos = m_XPos;
	destLeftSide.YPos = m_YPos;

	destRightSide.XPos = (m_XPos + m_Width) - srcRightSide.Width; 
	destRightSide.YPos = m_YPos;

	destBottomLeft.XPos = m_XPos;
	destBottomLeft.YPos = (m_YPos + m_Height) - srcBottomLeft.Height;

	destBottomCenter.XPos = m_XPos; 
    destBottomCenter.YPos = (m_YPos + m_Height) - srcBottomCenter.Height;

	destBottomRight.XPos = (m_XPos + m_Width) - srcBottomRight.Width;
	destBottomRight.YPos = (m_YPos + m_Height) - srcBottomRight.Height;

}

//----------------------------------------------------------------

void cMessageGUI::Create(cGraphics *Graphics, char *Filename, const char *BasePath)
{

	m_FixedX = -1;
	m_FixedY = -1;
	m_Visible = false;
	cBaseGUIWindow::m_Visible = false;
	m_Showing = false;
	m_Hiding = false;

	cBaseGUIWindow::Create(Graphics, Filename, BasePath);
}


void cMessageGUI::ShowConsole()
{
	m_Showing = true;
	m_Hiding = false;
	m_Visible = true;
	cBaseGUIWindow::m_Visible = true;

}

void cMessageGUI::HideConsole()
{
	m_Showing = false;
	m_Hiding = true;
}


BOOL cMessageGUI::Render(char *Text, BOOL Blended, D3DCOLOR Color)
{

    if (!m_Visible) 
		return true;

	if (m_Showing) //move the window onto the screen
	{
		if (m_YPos < m_FixedY)
		{
			m_YPos = m_YPos ++;
			CaclDest();
		}
		else
		{
			m_Showing = false;
		}
	}

	if (m_Hiding) //move the window off the screen
	{
		if (m_YPos > (0 - m_Height))
		{
   			m_YPos = m_YPos --;
			CaclDest();
		}
		else
		{
			m_Hiding = false;
			m_Visible = false;
			cBaseGUIWindow::m_Visible = false;
			return true;
		}

	}
    
	SetVertex(); //this will make the backgound move with 
				// the border

	cBaseGUIWindow::Render(Text, Blended, Color);


	return true;
}


BOOL cMessageGUI::Move(long XPos, long YPos,                      \
                   long Width, long Height,                   \
                   D3DCOLOR BackColor)
{

  m_BackColor = BackColor;
  //  Frist Pos
  if (m_FixedY == -1)
  {
	  m_XPos  = XPos;
	  m_FixedX = XPos;
	  m_YPos = (0 - Height);
	  m_FixedY = YPos;

	  // Save the coordinates and calculate height if needed
	  m_Width = Width;
	  m_Height = Height;

	  m_HeightOffSet = (Height / srcLeftSide.Height) + 1;

	  m_WidthOffSet = (Width / srcTopCenter.Width) + 1;

  }
  else
  {
	m_XPos  = XPos;
	m_YPos  = YPos;
  }


  SetVertex();


  CaclDest();

  
  return TRUE;
}


void cMessageGUI::Free()
{
	cBaseGUIWindow::Free();
}

//--------------------------------------------

BOOL cStatusBar::Render(char *Text, BOOL Blended, D3DCOLOR Color)
{

    if (!m_Visible) 
		return true;

	cBaseGUIWindow::Render(Text, Blended, Color);

	m_sbRight = (m_Percent * 0.01f) * 256;
	//gold bar
	m_StatusBar.Blit(m_XPos + 20,m_YPos+25,0,16,256,16);
	//status bar
	m_StatusBar.Blit(m_XPos+21,m_YPos +26,1,1,m_sbRight,14);

	return true;
}

void cStatusBar::SetPercent(int per)
{
	m_Percent = per;
	if (m_Percent > 100)
		m_Percent = 100;
	if (m_Percent < 0)
		m_Percent = 0;
}

int cStatusBar::GetPercent()
{
	return m_Percent;
}

void cStatusBar::IncPrecent(int per)
{
	m_Percent += per;
	if (m_Percent > 100)
		m_Percent = 100;
}

void cStatusBar::Create(cGraphics *Graphics, char *Filename, const char *BasePath)
{
	cBaseGUIWindow::Create(Graphics, Filename, BasePath);
	m_Percent = 1;
	m_sbRight = 1;
	m_Visible = TRUE;
	cBaseGUIWindow::m_Visible = TRUE;
	char strTmp[256];

	strcpy(strTmp, BasePath);
	strcat(strTmp, "gui\\statusbar.bmp");
    m_StatusBar.Load(m_Graphics, strTmp, D3DCOLOR_RGBA(0,0,0,255),D3DFMT_A1R5G5B5);

}

void cStatusBar::Free()
{
	m_StatusBar.Free();
	cBaseGUIWindow::Free();
}

BOOL cStatusBar::Move(long XPos, long YPos,                      \
                   long Width, long Height,                   \
                   D3DCOLOR BackColor)
{

  m_BackColor = BackColor;
  m_XPos  = XPos;
  m_YPos  = YPos;
  // Save the coordinates and calculate height if needed
  m_Width = Width;
  m_Height = Height;

  m_HeightOffSet = (Height / srcLeftSide.Height) + 1;
  m_WidthOffSet = (Width / srcTopCenter.Width) + 1;

  SetVertex();

  CaclDest();

  
  return TRUE;
}
