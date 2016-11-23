#include "RF3d_Global.h"
#include "Frustum.h"

//#include "MCL.h"
//#include "MIL.h"
//#include "MSL.h"
#include "RF3d_GameObjects.h"
#include "..\\WinMain.h"

BOOL cGameObject::Init(cGraphics *Graphics, char *MeshFile, cMesh *Mesh,   \
		               long NumAnimations, sAnimationInfo *Anims)
{
/*****Local Variables Start*****/
int i;
/*****Local Variables End*******/

  Free();

  Enabled = TRUE;
  Blended = FALSE;
  m_Action = 0;
  m_NumAnimations     = 0;     // Clear animation data
  m_ActionList        = NULL;
  m_Graphics = Graphics;
  m_Meshes = Mesh;
  
  //load the animation
  m_Animations.Load(MeshFile, m_Meshes);
  
  //create the game object
  m_Object.Create(Graphics, m_Meshes);
  
  // Clear bounding box (for limiting movement)
  MinX = MinY = MinZ = MaxX = MaxY = MaxZ = 0.0f;

  // Get animation data and build the action list
  if((m_NumAnimations = NumAnimations)) 
  {
    m_ActionList = new  sAnimationInfo[m_NumAnimations]();
    for(i=0;i<m_NumAnimations;i++) 
	{
      memcpy(&m_ActionList[i], &Anims[i], sizeof(sAnimationInfo));
    }
  }

  //Set the Action list to the animation data
  if(m_NumAnimations) 
  {
    for(i=0;i<m_NumAnimations;i++)
    m_Animations.SetLoop(m_ActionList[i].Loop, m_ActionList[i].Name);
  }

  DoAction(m_Action);
  OnInitalize();

  return TRUE;	
}


BOOL cGameObject::OnInitalize()
{
	return true;
}

BOOL cGameObject::Render(long Elapsed, cFrustum *Frustum, float ZDistance)
{
/*****Local Variables Start*****/
  float        Radius;       // Bounding radius
  DWORD        Time;
/*****Local Variables End*******/

  // Get time to update animations (30fps) if
  // elapsed value passed == -1
  if(Elapsed == -1)
    Time = timeGetTime() / 30;
 
  // Loop through each character and draw
  // Update animation based on elapsed time passed
  if(Elapsed != -1) 
  {
      LastAnimTime += (Elapsed/30);
      Time = LastAnimTime;
  }

  // Update object animations
  m_Object.UpdateAnimation(Time, TRUE);
  
  m_Object.GetBounds(NULL,NULL,NULL,NULL,NULL,NULL,&Radius);
  if(Frustum->CheckSphere(m_Object.GetXPos(), m_Object.GetYPos(), m_Object.GetZPos(), Radius) == TRUE) 
  {
  	if (Blended)
	{
		// Render using alphablending
		m_Graphics->EnableAlphaBlending(TRUE, D3DBLEND_SRCCOLOR, D3DBLEND_DESTCOLOR);
	}

        m_Object.Render();

    if (Blended)
	{
		// Display alpha blending to render pointer
		m_Graphics->EnableAlphaBlending(FALSE);
	}

  }

  return TRUE;	
}

BOOL cGameObject::Free()
{
//  m_Meshes.Free();
  m_Object.Free();
  m_Animations.Free();

  m_NumAnimations = 0;
  delete [] m_ActionList;
  m_ActionList = NULL;
  return TRUE;
}

BOOL cGameObject::Update(long Elapsed)
{
/*****Local Variables Start*****/
  float XMove, YMove, ZMove;
/*****Local Variables End*******/

	// Clear movement
  XMove = YMove = ZMove = 0.0f;

  // TODO -- do the AI, Move around ect.
  
  // Process movement of character
  ProcessUpdate(XMove, YMove, ZMove);


  return TRUE;	

}


BOOL cGameObject::ProcessUpdate(float XMove, float YMove, float ZMove)
{
  // Move character
  XPos += XMove;
  YPos += YMove;
  ZPos += ZMove;

  // Move object and point in direction
  m_Object.Move(XPos, YPos, ZPos);                   
  m_Object.Rotate(0.0f, Direction, 0.0f);

	// Set new animation
  if(LastAnim != m_Action) 
  {
    LastAnim = m_Action;
//	m_Action = action;

    if(m_NumAnimations && m_ActionList != NULL) 
	{
		LastAnimTime = timeGetTime() / 30;
		m_Object.SetAnimation(&m_Animations,m_ActionList[m_Action].Name, LastAnimTime);
	}
  }

  return TRUE;
}

BOOL cGameObject::SetData(cApp *App)
{
  if((m_App = App) == FALSE)
    return FALSE;
  return TRUE;
}

void cGameObject::DoAction(int action)
{
	m_Action = action;
/*
	// Set new animation
  if(LastAnim != m_Action) 
  {
    LastAnim = m_Action;
	m_Action = action;

    if(m_NumAnimations && m_ActionList != NULL) 
	{
		LastAnimTime = timeGetTime() / 30;
		m_Object.SetAnimation(&m_Animations,m_ActionList[m_Action].Name, LastAnimTime);
	}
  }
*/
}


BOOL cLiveObject::TakeDamage(int damage)
{
	m_Damage += damage;

	if (m_Damage >= m_HitPoints)
	{
		m_Dead = true;
		OnDeath();
	}

	return true;
}

BOOL cLiveObject::OnDeath()
{
	DoAction(6);
	return true;
}

BOOL cLiveObject::SetHitPoints(int HitPoints)
{
	m_HitPoints = HitPoints;
	return true;
}


void cAIObject::LoadAIFile(char *FileName)
{
	strcpy(AIFile, FileName);
	fp = fopen(FileName,"r");
}

void cAIObject::InitAI()
{
//	PyRun_SimpleFile(fp,AIFile);
}

void cAIObject::ExecuteAI()
{
//	PyRun_SimpleFile(fp,AIFile);
	DoAction(7);
}

BOOL cAIObject::Update(long Elapsed)
{
/*****Local Variables Start*****/
  float XMove, YMove, ZMove;
/*****Local Variables End*******/

  // Clear movement
  XMove = YMove = ZMove = 0.0f;

  // TODO -- do the AI, Move around ect.
  if (!IsDead())
	ExecuteAI();

  // Process movement of character
  ProcessUpdate(XMove, YMove, ZMove);


  return TRUE;	

}


void cMobalObject::Meander(long Elapsed, float *XMove, float *YMove, float *ZMove)
{
/*****Local Variables Start*****/
  float MoveX, MoveY, MoveZ, Speed;
//  float XDiff, YDiff, ZDiff, Dist, Radius;
/*****Local Variables End*******/

    // Clear movements and action
  MoveX = MoveY = MoveZ = 0.0f;

  // Calculate movement speed
  Speed = (float)Elapsed / 1000.0f * GetSpeed();

  // Calculate new distance and direction if needed
  Distance -= Elapsed;

  if(Distance <= 0.0f) 
  {

    // Calculate a new distance to travel
    Distance = (float)(rand() % 2000) + 2000.0f;

    // Calculate a new direction
    Direction = (float)(rand()%360)*0.01744444f;
  }

  // Process walk or stand still
  if(Distance > 1000.0f) 
  {
    MoveX = (float)sin(Direction) * Speed;
    MoveZ = (float)cos(Direction) * Speed;
    DoAction(CHAR_MOVE);
  } 
  else 
  {
    // Stand still for one second
    DoAction(CHAR_IDLE);
  }

    // Store movement and return
  *XMove = MoveX;
  *YMove = MoveY;
  *ZMove = MoveZ;

}

BOOL cMobalObject::CheckMove(float *XMove, float *YMove, float *ZMove)
{
 //TODO -- check for collision with other character and the player
	
  // Call overloaded check custom collisions (maps, etc)
  if(ValidateMove(XMove, YMove, ZMove) == FALSE)
    return FALSE;  // Don't allow movement

  return TRUE;

}

BOOL cMobalObject::ValidateMove(float *XMove, float *YMove, float *ZMove)
{
/*****Local Variables Start*****/
 float Dist;
/*****Local Variables End*******/

	// Check against terrain mesh for collision
  if(m_App != NULL) 
  {
      if(m_App->m_NodeTreeMesh.CheckIntersect(                                 \
         XPos,                                     \
         YPos+2.0f,                                \
         ZPos,                                     \
         *XMove + XPos,                            \
         *YMove + YPos + 2.0f,                     \
         *ZMove + ZPos, &Dist) == TRUE) 
      return FALSE;
  }

  return TRUE;

}

BOOL cMobalObject::Update(long Elapsed)
{
/*****Local Variables Start*****/
  float XMove, YMove, ZMove;
/*****Local Variables End*******/

  // Clear movement
  XMove = YMove = ZMove = 0.0f;

  // TODO -- do the AI, Move around ect.
  if (!IsDead())
  Meander(Elapsed, &XMove, &YMove, &ZMove);

  if(CheckMove(&XMove,&YMove,&ZMove)==FALSE) 
  {
	XMove = YMove = ZMove = 0.0f;
    DoAction(CHAR_IDLE);
  }

  // Process movement of character
  ProcessUpdate(XMove, YMove, ZMove);


  return TRUE;	

}
