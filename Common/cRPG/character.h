
typedef struct sDamageMinMax
{
 int MinDamage;
 int MaxDamage;
}sDamageMinMax;

typedef struct sCharacterDefinition
{
  //Misc Data
  char Name[32]; // Name of the character
  long Money;  //Amount of money

  //Stats
  int Strength;
  int Perception;
  int Endurance;
  int Charisma;
  int Inteligence;
  int Agility;
  int Luck;

  //Attributes
  int HitPoints;
  int Mana;
  int HitDrain;
  int ManaDrain;
  int ArmorRating;

  //Damage
  sDamageMinMax UnArmedDamage;
  sDamageMinMax ArmedDamage;
  sDamageMinMax RangedDamage;
  sDamageMinMax SpellDamage;


  //Primary Skills
  int UnarmedMelee;
  int ArmedMelee;
  int RangedMelee;
  int Magery;

  //Secondary Skills
  int LockPick;
  int Stealth;



} sCharacterDefinition;
