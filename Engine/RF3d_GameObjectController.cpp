//#include "RF3d_Global.h"
//#include "Frustum.h"
//
////#include "MCL.h"
////#include "MIL.h"
////#include "MSL.h"
//#include "RF3d_GameObjects.h"
//#include "..\\WinMain.h"
//
//
//sAnimationInfo g_CharAnimations[] = 
//{
//    { "Idle",  TRUE  },
//    { "Walk",  TRUE  },
//    { "Swing", FALSE },
//    { "Spell", FALSE },
//    { "Swing", FALSE },
//    { "Hurt",  FALSE },
//    { "Die",   FALSE },
//    { "AnimationSet0",  TRUE  }
//	
//};
//
//
//void cGameObjectController::Free()
//{
///*****Local Variables Start*****/
//	int iLoop;
///*****Local Variables End*****/
//
////	m_cMeshList;
////	m_GameObjectList;	
////	m_LiveObjectList;	
////	m_AIObjectList;	
////	m_MobalObjectList;
//
//  for (iLoop = 0; iLoop < (m_cMeshList.Length()); iLoop ++)
//  {
//     m_cMeshList[iLoop].Free();
//  }
//
//  for (iLoop = 0; iLoop < (m_GameObjectList.Length()); iLoop ++)
//  {
//     m_GameObjectList[iLoop].Free();
//  }
//
//  for (iLoop = 0; iLoop < (m_LiveObjectList.Length()); iLoop ++)
//  {
//     m_LiveObjectList[iLoop].Free();
//  }
//
//  for (iLoop = 0; iLoop < (m_AIObjectList.Length()); iLoop ++)
//  {
//     m_AIObjectList[iLoop].Free();
//  }
//  
//  for (iLoop = 0; iLoop < (m_MobalObjectList.Length()); iLoop ++)
//  {
//     m_MobalObjectList[iLoop].Free();
//  }
//
//}
//
//void cGameObjectController::Blended(int ObjectType, int indx)
//{
//	switch (ObjectType)
//	{
//	case GAMEOBJECT:
//		m_GameObjectList[indx].Blended = !m_GameObjectList[indx].Blended;
//		break;
//	case LIVEOBJECT:
//		m_LiveObjectList[indx].Blended = !m_LiveObjectList[indx].Blended;
//		break;
//	case AIOBJECT:
//		m_AIObjectList[indx].Blended = !m_AIObjectList[indx].Blended;
//		break;
//	case MOBALOBJECT:
//		m_MobalObjectList[indx].Blended = !m_MobalObjectList[indx].Blended;
//		break;
//	case CHAROBJECT:
//
//		break;
//	}
//
//	m_AIObjectList[indx].Blended = !m_AIObjectList[indx].Blended;
//}
//
//BOOL cGameObjectController::Render(long Elapsed, cFrustum *Frustum, float ZDistance)
//{
///*****Local Variables Start*****/
//	int iLoop;
///*****Local Variables End*****/
//
//  for (iLoop = 0; iLoop < (m_GameObjectList.Length()); iLoop ++)
//  {
//     m_GameObjectList[iLoop].Render(Elapsed, Frustum, ZDistance);
//  }
//
//  for (iLoop = 0; iLoop < (m_LiveObjectList.Length()); iLoop ++)
//  {
//     m_LiveObjectList[iLoop].Render(Elapsed, Frustum, ZDistance);
//  }
//
//  for (iLoop = 0; iLoop < (m_AIObjectList.Length()); iLoop ++)
//  {
//     m_AIObjectList[iLoop].Render(Elapsed, Frustum, ZDistance);
//  }
//  
//  for (iLoop = 0; iLoop < (m_MobalObjectList.Length()); iLoop ++)
//  {
//     m_MobalObjectList[iLoop].Render(Elapsed, Frustum, ZDistance);
//  }
//
//  return TRUE;
//}
//	
//
//BOOL cGameObjectController::Update(long Elapsed)
//{
///*****Local Variables Start*****/
//	int iLoop;
///*****Local Variables End*****/
//
//  for (iLoop = 0; iLoop < (m_GameObjectList.Length()); iLoop ++)
//  {
//     m_GameObjectList[iLoop].Update(Elapsed);
//  }
//
//  for (iLoop = 0; iLoop < (m_LiveObjectList.Length()); iLoop ++)
//  {
//     m_LiveObjectList[iLoop].Update(Elapsed);
//  }
//
//  for (iLoop = 0; iLoop < (m_AIObjectList.Length()); iLoop ++)
//  {
//     m_AIObjectList[iLoop].Update(Elapsed);
//  }
//  
//  for (iLoop = 0; iLoop < (m_MobalObjectList.Length()); iLoop ++)
//  {
//     m_MobalObjectList[iLoop].Update(Elapsed);
//  }
//
//  return TRUE;
//}
//
//void cGameObjectController::Create(cGraphics *Graphics, char *TexturePath, cApp *App)
//{
//	m_Graphics = Graphics;
//	m_App = App;
//	strcpy(m_TexturePath, TexturePath);
//}
//
//int cGameObjectController::AddGameObj(int ObjectType, char *MeshFile, float X, float Y, float Z, float Dir)
//{
///*****Local Variables Start*****/
//	int				MeshIndex = -1;
//	int				ObjIndx = -1;
//	char					sMeshFile[256];
///*****Local Variables End*****/
//
//// GAMEOBJECT		 0		
//// LIVEOBJECT		 1		
//// AIOBJECT			 2	
//// MOBALOBJECT		 3		
//// CHAROBJECT		 4
//	 
//	MeshIndex =	m_cMeshList.Add();
//
//    m_App->m_logfile.Log("Add Mesh to MeshList", MeshIndex);
//
//    m_cMeshList[MeshIndex].Load(m_Graphics, MeshFile, m_TexturePath);
//	m_App->m_logfile.Log("Load Mesh", MeshFile);
//	strcpy(sMeshFile, MeshFile);
//
//	switch (ObjectType)
//	{
//	case GAMEOBJECT:
//		 m_App->m_logfile.Log("Create GameObject");
// 		 
//		 ObjIndx = m_GameObjectList.Add();	
//
//		 m_GameObjectList[ObjIndx].Init(m_Graphics, sMeshFile, &m_cMeshList[MeshIndex],    \
//				sizeof(g_CharAnimations) / sizeof(sAnimationInfo),     \
//				(sAnimationInfo*)&g_CharAnimations);
// 		 m_App->m_logfile.Log("Add GameObject to List", ObjIndx);
//		 m_GameObjectList[ObjIndx].SetData(m_App);
//		 m_GameObjectList[ObjIndx].XPos = X;
//		 m_GameObjectList[ObjIndx].YPos = Y;
//		 m_GameObjectList[ObjIndx].ZPos = Z;
//		 m_GameObjectList[ObjIndx].Direction = Dir;
//		break;
//	case LIVEOBJECT:
//		 m_App->m_logfile.Log("Create LiveObject");
//		 	ObjIndx = m_LiveObjectList.Add();	
//		 m_LiveObjectList[ObjIndx].Init(m_Graphics, sMeshFile, &m_cMeshList[MeshIndex],    \
//				sizeof(g_CharAnimations) / sizeof(sAnimationInfo),     \
//				(sAnimationInfo*)&g_CharAnimations);
// 		 m_App->m_logfile.Log("Add LiveObject to List", ObjIndx);
//		 m_LiveObjectList[ObjIndx].SetData(m_App);
//		 m_LiveObjectList[ObjIndx].XPos = X;
//		 m_LiveObjectList[ObjIndx].YPos = Y;
//		 m_LiveObjectList[ObjIndx].ZPos = Z;
//		 m_LiveObjectList[ObjIndx].Direction = Dir;
//		break;
//	case AIOBJECT:
//
//		 m_App->m_logfile.Log("Create AIObject");
//			ObjIndx = m_AIObjectList.Add();	
//		 m_AIObjectList[ObjIndx].Init(m_Graphics, sMeshFile, &m_cMeshList[MeshIndex],    \
//				sizeof(g_CharAnimations) / sizeof(sAnimationInfo),     \
//				(sAnimationInfo*)&g_CharAnimations);
// 		 m_App->m_logfile.Log("Add AIObject to List", ObjIndx);
//		 m_AIObjectList[ObjIndx].SetData(m_App);
//		 m_AIObjectList[ObjIndx].XPos = X;
//		 m_AIObjectList[ObjIndx].YPos = Y;
//		 m_AIObjectList[ObjIndx].ZPos = Z;
//		 m_AIObjectList[ObjIndx].Direction = Dir;
//		break;
//	case MOBALOBJECT:
//		 m_App->m_logfile.Log("Create MobalObject");
//			ObjIndx = m_MobalObjectList.Add();	
//		 m_MobalObjectList[ObjIndx].Init(m_Graphics, sMeshFile, &m_cMeshList[MeshIndex],    \
//				sizeof(g_CharAnimations) / sizeof(sAnimationInfo),     \
//				(sAnimationInfo*)&g_CharAnimations);
// 		 m_App->m_logfile.Log("Add MobalObject to List", ObjIndx);
//		 m_MobalObjectList[ObjIndx].SetData(m_App);
//		 m_MobalObjectList[ObjIndx].XPos = X;
//		 m_MobalObjectList[ObjIndx].YPos = Y;
//		 m_MobalObjectList[ObjIndx].ZPos = Z;
//		 m_MobalObjectList[ObjIndx].Direction = Dir;
//		break;
//	case CHAROBJECT:
//
//		break;
//	}
//return ObjIndx;
//}
//
//
