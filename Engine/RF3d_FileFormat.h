#ifndef _RF3D_FILEFORMAT_H_
#define _RF3D_FILEFORMAT_H_


typedef struct sCharacterDefinition
{
  // Misc data
  char  Name[32];           // Name of character
  char  Title[32];          // Title of character
  long  Class;              // Class # of character
  long  Gold;               // Amount of money
  float Speed;              // Movement speed
  long  MagicSpells[2];     // Bit flags to mark known spells
  long  MeshNum;            // Mesh/anim # to load

  // Abilities
  long  Strength;           // Strenght ability
  long  Perception;         // Perceptiom ability
  long  Endurance;          // Endurance ability
  long  Charisma;           // Charisma ability
  long  Intelligence;       // Intelligence ability
  long  Agility;            // Agility ability

  long  Attack;             // Attack ability
  long  Defense;            // Defend ability
  long  Resistance;         // Magic resistance ability
  long  ToHit;              // Chance to hit

  // Attributes
  long  BaseHitPoints;      // # hit points (maximum)
  long  BaseMana;           // # mana points (maximum)
  long  HitDrain;			// Current # hit points
  long  ManaDrain;			// Current # mana points
  long  Level;              // Experience level
  long  Experience;         // Experience points

  // Inventory
  char  ItemFilename[MAX_PATH]; // CharICS filename 
  long  Weapon;             // Equipped Weapon
  long  Armor;              // Equipped Armor
  long  Shield;             // Equipped Shield
  long  Accessory;          // Equipped Accessory

  // Dropping item data
  long  DropChance;         // % of dropping item when killed
  long  DropItem;           // Item # to drop when killed
  
  // Attack/Magic chances and effects
  float Range;              // Attack range
  long  ToAttack;           // Percent to attack
  long  ToMagic;            // Percent to use magic
  long  EffectChance;       // Chance of attack effect occuring
  long  Effects;            // Bit flags of attack effects
} sCharacterDefinition;


typedef struct sMapFileFormat
{
  char  MeshFilename[16];    // .X mesh filename
  char	SkyBox[16];  // .bmp skybox image
  float StartXPos;
  float StartYPos;
  float StartZPos;
  float Direction;
  bool  AmbentLight;
  int	rLight;
  int	gLight;
  int	bLight;
 

} sMapFileFormat;

#endif