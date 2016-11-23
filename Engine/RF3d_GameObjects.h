#ifndef RF3D_GAMEOBJECTS_H
#define RF3D_GAMEOBJECTS_H

#include "Frustum.h"
#include "RF3d_FileFormat.h"

// Action/Animation types
#define CHAR_IDLE        0
#define CHAR_MOVE        1
#define CHAR_ATTACK      2
#define CHAR_SPELL       3
#define CHAR_ITEM        4
#define CHAR_HURT        5
#define CHAR_DIE         6
#define CHAR_TALK        7

#define GAMEOBJECT		 0		
#define LIVEOBJECT		 1		
#define AIOBJECT		 2		
#define MOBALOBJECT		 3		
#define CHAROBJECT		 4		


// Animation info
typedef struct 
{
  char Name[32];    // Name of animation
  BOOL Loop;        // To loop flag
} sAnimationInfo;

// A mesh list
typedef struct sGameObjectMeshList 
{
  char       Filename[MAX_PATH];  // Filename of mesh/anim
  long       Count;               // # characters using mesh
  cMesh      Mesh;                // Mesh object
  cAnimation Animation;           // Animation object

  sGameObjectMeshList()  { Count = 0; }
  ~sGameObjectMeshList() { Mesh.Free(); Animation.Free(); }
} sGameObjectMeshList;

class cApp;

class cGameObject
{


private:
	// 3-D meshes and objects
    cMesh           *m_Meshes;
    cObject         m_Object;
    cAnimation      m_Animations;
	cGraphics		*m_Graphics;
	long			m_NumAnimations; 
	sAnimationInfo  *m_ActionList;

    float MinX, MinY, MinZ;   // Min bounding coordinates
    float MaxX, MaxY, MaxZ;   // Max bounding coordiantes

public:
	//cGameObject *Prev, *Next; // Linked list of GameObject
	cApp			*m_App;
	BOOL  Enabled;
	BOOL  Blended;
    long  m_Action;             // Current action
    float XPos, YPos, ZPos;   // Current coordinates
    float Direction;          // Angle character is facing

	long  LastAnim;           // Last animation
	long  LastAnimTime;       // Last animation time

	BOOL  Locked;             // Specific action lock
	long  ActionTimer;        // Lock action countdown timer
	BOOL SetData(cApp *App);

	virtual BOOL Render(long Elapsed, cFrustum *Frustum, float ZDistance = 0.0f);
	virtual BOOL Free();
//	virtual BOOL Init(cGraphics *Graphics, char *MeshFile, char *TexturePath,  \
//		      long NumAnimations, sAnimationInfo *Anims);
	virtual	BOOL Init(cGraphics *Graphics, char *MeshFile, cMesh *Mesh,   \
		      long NumAnimations, sAnimationInfo *Anims);

	virtual BOOL Update(long Elapsed);

    // Finish movement by setting direction, animation, etc
    virtual BOOL ProcessUpdate(float XMove, float YMove, float ZMove);
	
	//After the artwork and mesh is loaded
	virtual BOOL OnInitalize();
	virtual void DoAction(int action);
};


class cLiveObject :public cGameObject
{

private:
	int	m_HitPoints;
	int	m_Damage;
	BOOL m_Dead;

public:
	//cLiveObject *Prev, *Next; // Linked list of LiveObject

	cLiveObject() {m_HitPoints = 1; m_Damage = 0; m_Dead = FALSE;}

	int GetHitPoints() {return m_HitPoints;}
	int GetDamage() {return m_Damage;}
	BOOL IsDead() {return m_Dead;}
	virtual BOOL SetHitPoints(int HitPoints);
	virtual BOOL TakeDamage(int damage);
	virtual BOOL OnDeath();

};


class cAIObject :public cLiveObject
{
private:
	FILE *fp;
	char AIFile[256];

public:
   	virtual BOOL Update(long Elapsed);
	void InitAI();
	void LoadAIFile(char *FileName);
	void ExecuteAI();

};

class cMobalObject :public cAIObject
{
private:
	float m_Speed;

public:
	cMobalObject() { m_Speed = 50;Distance = 0.0f;}
	
	float Distance;           // Follow/Evade distance

	int GetSpeed(){return 50;}
   	virtual BOOL Update(long Elapsed);
	void Meander(long Elapsed, float *XMove, float *YMove, float *ZMove);
	BOOL CheckMove(float *XMove, float *YMove, float *ZMove);
	BOOL ValidateMove(float *XMove, float *YMove, float *ZMove);
};


//class cGameObjectController
//{
//
//private:
//	cGraphics		*m_Graphics;
//	char			m_TexturePath[256];
//	cApp			*m_App;
//
//	List <cMesh>		m_cMeshList;
//	List <cGameObject>	m_GameObjectList;	
//	List <cLiveObject>	m_LiveObjectList;	
//	List <cAIObject>	m_AIObjectList;	
//	List <cMobalObject> m_MobalObjectList;
//	
//	
//public:
//	
//	int AddGameObj(int ObjectType, char *MeshFile, float X, float Y, float Z, float Dir);
//	void Free();
//	BOOL Render(long Elapsed, cFrustum *Frustum, float ZDistance = 0.0f);
//	BOOL Update(long Elapsed);
//	void Create(cGraphics *Graphics, char *TexturePath, cApp *App);
//	void Blended(int ObjectType, int indx);
//};

#endif
