#pragma once

#include "libzhl.h"

typedef int lua_Integer;
typedef void* lua_State;

struct ANM2;
struct AchievementOverlay;
struct AchievementOverlay_Entry;
struct ActiveItemDesc;
struct Ambush;
struct AnimationData;
struct AnimationFrame;
struct AnimationLayer;
struct AnimationState;
struct Backdrop;
struct BackdropConfig;
struct BeamRenderer;
struct BitSet128;
struct BlendMode;
struct BossPool;
struct Camera;
struct Capsule;
struct ChallengeParam;
struct ColorMod;
struct ColorModState;
struct CompletionWidget;
struct Console;
struct Console_HistoryEntry;
struct CostumeSpriteDesc;
struct Cutscene;
struct DailyChallenge;
struct DebugRenderer;
struct DestinationQuad;
struct DrawStringEntry;
struct DrawStringScaledEntry;
struct Entity;
struct EntityConfig;
struct EntityConfig_Boss;
struct EntityConfig_Entity;
struct EntityConfig_Player;
struct EntityList;
struct EntityList_EL;
struct EntityRef;
struct EntitySaveState;
struct Entity_Bomb;
struct Entity_Effect;
struct Entity_Familiar;
struct Entity_Knife;
struct Entity_Laser;
struct Entity_NPC;
struct Entity_Pickup;
struct Entity_Player;
struct Entity_Projectile;
struct Entity_Slot;
struct Entity_Tear;
struct FXParams;
struct Font;
struct Game;
struct GameOver;
struct GameState;
struct GenericPopup;
struct GenericPrompt;
struct GlobalPost;
struct GridEntity;
struct GridEntityDesc;
struct GridEntity_Decoration;
struct GridEntity_Door;
struct GridEntity_Fire;
struct GridEntity_Gravity;
struct GridEntity_Lock;
struct GridEntity_Pit;
struct GridEntity_Poop;
struct GridEntity_PressurePlate;
struct GridEntity_Rock;
struct GridEntity_Spikes;
struct GridEntity_Stairs;
struct GridEntity_Statue;
struct GridEntity_TNT;
struct GridEntity_Teleporter;
struct GridEntity_TrapDoor;
struct GridEntity_Wall;
struct GridEntity_Web;
struct HUD;
struct History;
struct History_HistoryItem;
struct Isaac;
struct ItemConfig;
struct ItemConfig_Card;
struct ItemConfig_Costume;
struct ItemConfig_Item;
struct ItemConfig_Pill;
struct ItemConfig_PlayerForm;
struct ItemOverlay;
struct ItemPool;
struct ItemPool_Item;
struct KAGE;
struct KAGE_File;
struct KAGE_Graphics_Color;
struct KAGE_Graphics_ImageBase;
struct KAGE_Graphics_ImageBase_VertexAttributeDescriptor;
struct KAGE_Graphics_ImagePCX;
struct KAGE_Graphics_ImagePIC;
struct KAGE_Graphics_ImagePNG;
struct KAGE_Graphics_Manager;
struct KAGE_Graphics_Manager_GL;
struct KAGE_Graphics_RenderDescriptor;
struct KAGE_Graphics_Shader;
struct KAGE_Graphics_VertexAttributeDescriptor;
struct KAGE_Memory_MemoryPool;
struct KAGE_Memory_MemoryPoolDescriptor;
struct KAGE_SmartPointer_ImageBase;
struct KAGE_System_CriticalSection;
struct KAGE_System_Mutex;
struct KColor;
struct LayerData;
struct LayerState;
struct Leaderboard;
struct Level;
struct LevelGenerator;
struct LevelGenerator_Room;
struct LuaBridgeRef;
struct LuaCallbackCaller;
struct LuaCallbackCallerResult;
struct LuaEngine;
struct Manager;
struct MenuManager;
struct Menu_Bestiary;
struct Menu_Challenge;
struct Menu_Character;
struct Menu_Collection;
struct Menu_ControllerSelect;
struct Menu_CustomChallenge;
struct Menu_Cutscenes;
struct Menu_DailyChallenge;
struct Menu_Game;
struct Menu_KeyConfig;
struct Menu_Mods;
struct Menu_Options;
struct Menu_Save;
struct Menu_SpecialSeeds;
struct Menu_Stats;
struct Menu_Title;
struct Minimap;
struct ModEntry;
struct ModManager;
struct Music;
struct NPCAI_Pathfinder;
struct NightmareScene;
struct NullFrame;
struct OptionsConfig;
struct PauseScreen;
struct PersistentGameData;
struct PlayerCostumeMap;
struct PlayerHUD;
struct PlayerHUDActiveItem;
struct PlayerHUDHeart;
struct PlayerManager;
struct PocketItem;
struct Point;
struct PosVel;
struct ProceduralEffect;
struct ProceduralEffect_ActionData_AddTemproryEffect;
struct ProceduralEffect_ActionData_AreaDamage;
struct ProceduralEffect_ActionData_ConvertEntities;
struct ProceduralEffect_ActionData_Fart;
struct ProceduralEffect_ActionData_SpawnEntity;
struct ProceduralEffect_ActionData_UseActiveItem;
struct ProceduralEffect_ConditionData_EntitySpawn;
struct ProceduralItem;
struct ProceduralItemManager;
struct ProjectileParams;
struct RNG;
struct RailManager;
struct ReferenceCounter_ImageBase;
struct Rendering;
struct Room;
struct RoomConfig;
struct RoomConfigHolder;
struct RoomConfigs;
struct RoomDescriptor;
struct RoomEntry;
struct RoomSpawn;
struct RoomTransition;
struct RunCallbackRegistry;
struct SFXManager;
struct ScoreSheet;
struct Seeds;
struct Shape;
struct ShapeRenderer;
struct SoundEffects;
struct SourceQuad;
struct StageTransition;
struct StaticArray;
struct StringTable;
struct TearParams;
struct TemporaryEffect;
struct TemporaryEffects;
struct TrinketPoolItem;
struct UnknownGameStartStruct;
struct Vector;
struct Weapon;
struct Weapon_Brimstone;
struct Weapon_MonstrosLung;
struct Weapon_MultiShotParams;
struct WeightedOutcomePicker;
struct WeightedOutcomePicker_Outcome;
struct xmldocument_rep;
struct xmlnode_rep;
#include <windows.h>
#include <string>
#include <vector>
#include <set>
#include <map>
#include <functional>
#include <deque>
#include <cstdarg>
#include <unordered_map>
#include <cmath>
#include <queue>
#include <cstdint>
#include <bitset>
#include <rttidata.h>
#undef LoadImage


#ifndef M_PI
        #define M_PI 3.14159265358979323846
#endif

struct Console_HistoryEntry;
struct History_HistoryItem;
struct EntitySaveState;

struct EntityId {
    int type;
    int variant;
    int subtype;
};

struct IntPair {
    int pair[2];
};

// When adding typedefs, remember to define them in ExtraTypes!
typedef std::vector<Point> vector_Point;
typedef std::deque<Console_HistoryEntry> std_deque_console_historyentry;
typedef std::set<int> std_set_int;
typedef std::vector<TemporaryEffect> vector_TemporaryEffect;
typedef std::vector<LevelGenerator_Room> vector_LevelGenRoom;
typedef std::string std_string;
typedef std::vector<ModEntry*> vector_ModEntryPointer;
typedef std::deque<std::string> deque_string;
typedef std::vector<int> std_vector_int;
typedef std::vector<Vector> std_vector_vector2;
typedef std::vector<History_HistoryItem> std_vector_history_historyitem;
typedef std::vector<unsigned int> std_vector_uint;
typedef std::set<uint32_t> std_set_uint32t;
typedef std::vector<EntitySaveState> vector_EntitySaveState;
typedef std::vector<GridEntityDesc> vector_GridEntityDesc;
typedef std::map<int, int> std_map_int_int;
typedef std::vector<EntityId> vector_ErasedEntities;
typedef std::vector<Entity_Player**> vector_EntityPlayerPtr;
typedef std::vector<ItemConfig_Item*> vector_ItemPtr;
typedef std::vector<TrinketPoolItem> vector_TrinketPoolItem;
typedef std::vector<WeightedOutcomePicker_Outcome> vector_Outcome;

struct PoolItem {
	uint32_t _itemID;
	float _initialWeight;
	float _weight;
	float _decreaseBy;
	float _removeOn;
	char _pad[4];
	
	//std_string _itemName;
};

typedef std::vector<PoolItem> vector_PoolItem;
// Something goofy seemed to be happening with std::vector<bool> in zhl
// typedef std::vector<bool> vector_bool;

struct RoomConfig;
typedef std::vector<RoomConfig*> RoomConfigPtrVector;

struct SmeltedTrinketDesc {
	short _trinketNum;
	short _goldenTrinketNum;
};
typedef std::vector<SmeltedTrinketDesc> vector_SmeltedTrinketDesc;
typedef std::vector<CostumeSpriteDesc> vector_CostumeSpriteDesc;



enum CharacterLockedFlag
{
		LOCKED = 65536,
		UNLOCKED = 65792,
};

enum WeaponType
{
        WEAPON_NULL = 0x0,
        WEAPON_TEARS = 0x1,
        WEAPON_BRIMSTONE = 0x2,
        WEAPON_LASER = 0x3,
        WEAPON_KNIFE = 0x4,
        WEAPON_BOMBS = 0x5,
        WEAPON_ROCKETS = 0x6,
        WEAPON_MONSTROS_LUNGS = 0x7,
        WEAPON_LUDOVICO_TECHNIQUE = 0x8,
        WEAPON_TECH_X = 0x9,
        WEAPON_BONE = 0xA,
        WEAPON_NOTCHED_AXE = 0xB,
        WEAPON_URN_OF_SOULS = 0xC,
        WEAPON_SPIRIT_SWORD = 0xD,
        WEAPON_FETUS = 0xE,
        WEAPON_UMBILICAL_WHIP = 0xF,
        NUM_WEAPON_TYPES = 0x10,
};

enum GridEntityType {
        GRID_NULL = 0x0,
        GRID_DECORATION = 0x1,
        GRID_ROCK = 0x2,
        GRID_ROCKB = 0x3,	
        GRID_ROCKT = 0x4,	
        GRID_ROCK_BOMB = 0x5,	
        GRID_ROCK_ALT = 0x6,	
        GRID_PIT = 0x7,
        GRID_SPIKES = 0x8,
        GRID_SPIKES_ONOFF = 0x9,
        GRID_SPIDERWEB = 0xA,
        GRID_LOCK = 0xB,
        GRID_TNT = 0xC,
        GRID_FIREPLACE = 0xD,
        GRID_POOP = 0xE,
        GRID_WALL = 0xF,
        GRID_DOOR = 0x10,
        GRID_TRAPDOOR = 0x11,
        GRID_STAIRS = 0x12,
        GRID_GRAVITY = 0x13,
        GRID_PRESSURE_PLATE = 0x14,
        GRID_STATUE = 0x15,
        GRID_ROCK_SS = 0x16,
        GRID_TELEPORTER = 0x17,
        GRID_PILLAR = 0x18,
        GRID_ROCK_SPIKED = 0x19,
        GRID_ROCK_ALT2 = 0x1A,
        GRID_ROCK_GOLD = 0x1B,
};

enum Direction
{
        NO_DIRECTION = 0xFFFFFFFF,
        LEFT = 0x0,
        UP = 0x1,
        RIGHT = 0x2,
        DOWN = 0x3,
};

enum eRoomShape 
{
    ROOMSHAPE_1x1 = 1,
    ROOMSHAPE_IH, // Horizontal, narrow
    ROOMSHAPE_IV, // Vertical, narrow
    ROOMSHAPE_1x2, // Vertical, two high
    ROOMSHAPE_IIV, // Vertical, two high, narrow
    ROOMSHAPE_2x1, // Horizontal, two wide
    ROOMSHAPE_IIH, // Horizontal, two wide, narrow
    ROOMSHAPE_2x2,
    ROOMSHAPE_LTL, 
    ROOMSHAPE_LTR,
    ROOMSHAPE_LBL,
    ROOMSHAPE_LBR,
    MAX_ROOMSHAPES
};

enum eDoorSlots 
{
    DOOR_SLOT_LEFT0 = 0, // Left wall, top
    DOOR_SLOT_UP0, // Top wall, left
    DOOR_SLOT_RIGHT0, // Right wall, top
    DOOR_SLOT_DOWN0, // Down wall, left
    DOOR_SLOT_LEFT1, // Left wall, bottom
    DOOR_SLOT_UP1, // Top wall, right
    DOOR_SLOT_RIGHT1, // Right wall, bottom
    DOOR_SLOT_DOWN1, // Bottom wall, right
    MAX_DOOR_SLOTS
};

enum GridCollisionClass
{
        COLLISION_NONE = 0,
        COLLISION_PIT,
        COLLISION_OBJECT,
        COLLISION_SOLID,
        COLLISION_WALL,
        COLLISION_WALL_EXCEPT_PLAYER
};

enum CollectibleType
{
        COLLECTIBLE_NULL = 0,
        COLLECTIBLE_SAD_ONION = 1,
        COLLECTIBLE_INNER_EYE = 2,
        COLLECTIBLE_SPOON_BENDER = 3,
        COLLECTIBLE_CRICKETS_HEAD = 4,
        COLLECTIBLE_MY_REFLECTION = 5,
        COLLECTIBLE_NUMBER_ONE = 6,
        COLLECTIBLE_BLOOD_OF_THE_MARTYR = 7,
        COLLECTIBLE_BROTHER_BOBBY = 8,
        COLLECTIBLE_SKATOLE = 9,
        COLLECTIBLE_HALO_OF_FLIES = 10,
        COLLECTIBLE_1UP = 11,
        COLLECTIBLE_MAGIC_MUSHROOM = 12,
        COLLECTIBLE_VIRUS = 13,
        COLLECTIBLE_ROID_RAGE = 14,
        COLLECTIBLE_HEART = 15,
        COLLECTIBLE_RAW_LIVER = 16,
        COLLECTIBLE_SKELETON_KEY = 17,
        COLLECTIBLE_DOLLAR = 18,
        COLLECTIBLE_BOOM = 19,
        COLLECTIBLE_TRANSCENDENCE = 20,
        COLLECTIBLE_COMPASS = 21,
        COLLECTIBLE_LUNCH = 22,
        COLLECTIBLE_DINNER = 23,
        COLLECTIBLE_DESSERT = 24,
        COLLECTIBLE_BREAKFAST = 25,
        COLLECTIBLE_ROTTEN_MEAT = 26,
        COLLECTIBLE_WOODEN_SPOON = 27,
        COLLECTIBLE_BELT = 28,
        COLLECTIBLE_MOMS_UNDERWEAR = 29,
        COLLECTIBLE_MOMS_HEELS = 30,
        COLLECTIBLE_MOMS_LIPSTICK = 31,
        COLLECTIBLE_WIRE_COAT_HANGER = 32,
        COLLECTIBLE_BIBLE = 33,
        COLLECTIBLE_BOOK_OF_BELIAL = 34,
        COLLECTIBLE_NECRONOMICON = 35,
        COLLECTIBLE_POOP = 36,
        COLLECTIBLE_MR_BOOM = 37,
        COLLECTIBLE_TAMMYS_HEAD = 38,
        COLLECTIBLE_MOMS_BRA = 39,
        COLLECTIBLE_KAMIKAZE = 40,
        COLLECTIBLE_MOMS_PAD = 41,
        COLLECTIBLE_BOBS_ROTTEN_HEAD = 42,
        // 43
        COLLECTIBLE_TELEPORT = 44,
        COLLECTIBLE_YUM_HEART = 45,
        COLLECTIBLE_LUCKY_FOOT = 46,
        COLLECTIBLE_DOCTORS_REMOTE = 47,
        COLLECTIBLE_CUPIDS_ARROW = 48,
        COLLECTIBLE_SHOOP_DA_WHOOP = 49,
        COLLECTIBLE_STEVEN = 50,
        COLLECTIBLE_PENTAGRAM = 51,
        COLLECTIBLE_DR_FETUS = 52,
        COLLECTIBLE_MAGNETO = 53,
        COLLECTIBLE_TREASURE_MAP = 54,
        COLLECTIBLE_MOMS_EYE = 55,
        COLLECTIBLE_LEMON_MISHAP = 56,
        COLLECTIBLE_DISTANT_ADMIRATION = 57,
        COLLECTIBLE_BOOK_OF_SHADOWS = 58,
        COLLECTIBLE_BOOK_OF_BELIAL_PASSIVE = 59,
        COLLECTIBLE_LADDER = 60,
        // 61
        COLLECTIBLE_CHARM_VAMPIRE = 62,
        COLLECTIBLE_BATTERY = 63,
        COLLECTIBLE_STEAM_SALE = 64,
        COLLECTIBLE_ANARCHIST_COOKBOOK = 65,
        COLLECTIBLE_HOURGLASS = 66,
        COLLECTIBLE_SISTER_MAGGY = 67,
        COLLECTIBLE_TECHNOLOGY = 68,
        COLLECTIBLE_CHOCOLATE_MILK = 69,
        COLLECTIBLE_GROWTH_HORMONES = 70,
        COLLECTIBLE_MINI_MUSH = 71,
        COLLECTIBLE_ROSARY = 72,
        COLLECTIBLE_CUBE_OF_MEAT = 73,
        COLLECTIBLE_QUARTER = 74,
        COLLECTIBLE_PHD = 75,
        COLLECTIBLE_XRAY_VISION = 76,
        COLLECTIBLE_MY_LITTLE_UNICORN = 77,
        COLLECTIBLE_BOOK_OF_REVELATIONS = 78,
        COLLECTIBLE_MARK = 79,
        COLLECTIBLE_PACT = 80,
        COLLECTIBLE_DEAD_CAT = 81,
        COLLECTIBLE_LORD_OF_THE_PIT = 82,
        COLLECTIBLE_THE_NAIL = 83,
        COLLECTIBLE_WE_NEED_TO_GO_DEEPER = 84,
        COLLECTIBLE_DECK_OF_CARDS = 85,
        COLLECTIBLE_MONSTROS_TOOTH = 86,
        COLLECTIBLE_LOKIS_HORNS = 87,
        COLLECTIBLE_LITTLE_CHUBBY = 88,
        COLLECTIBLE_SPIDER_BITE = 89,
        COLLECTIBLE_SMALL_ROCK = 90,
        COLLECTIBLE_SPELUNKER_HAT = 91,
        COLLECTIBLE_SUPER_BANDAGE = 92,
        COLLECTIBLE_GAMEKID = 93,
        COLLECTIBLE_SACK_OF_PENNIES = 94,
        COLLECTIBLE_ROBO_BABY = 95,
        COLLECTIBLE_LITTLE_CHAD = 96,
        COLLECTIBLE_BOOK_OF_SIN = 97,
        COLLECTIBLE_RELIC = 98,
        COLLECTIBLE_LITTLE_GISH = 99,
        COLLECTIBLE_LITTLE_STEVEN = 100,
        COLLECTIBLE_HALO = 101,
        COLLECTIBLE_MOMS_BOTTLE_OF_PILLS = 102,
        COLLECTIBLE_COMMON_COLD = 103,
        COLLECTIBLE_PARASITE = 104,
        COLLECTIBLE_D6 = 105,
        COLLECTIBLE_MR_MEGA = 106,
        COLLECTIBLE_PINKING_SHEARS = 107,
        COLLECTIBLE_WAFER = 108,
        COLLECTIBLE_MONEY_EQUALS_POWER = 109,
        COLLECTIBLE_MOMS_CONTACTS = 110,
        COLLECTIBLE_BEAN = 111,
        COLLECTIBLE_GUARDIAN_ANGEL = 112,
        COLLECTIBLE_DEMON_BABY = 113,
        COLLECTIBLE_MOMS_KNIFE = 114,
        COLLECTIBLE_OUIJA_BOARD = 115,
        COLLECTIBLE_9_VOLT = 116,
        COLLECTIBLE_DEAD_BIRD = 117,
        COLLECTIBLE_BRIMSTONE = 118,
        COLLECTIBLE_BLOOD_BAG = 119,
        COLLECTIBLE_ODD_MUSHROOM_THIN = 120,
        COLLECTIBLE_ODD_MUSHROOM_LARGE = 121,
        COLLECTIBLE_WHORE_OF_BABYLON = 122,
        COLLECTIBLE_MONSTER_MANUAL = 123,
        COLLECTIBLE_DEAD_SEA_SCROLLS = 124,
        COLLECTIBLE_BOBBY_BOMB = 125,
        COLLECTIBLE_RAZOR_BLADE = 126,
        COLLECTIBLE_FORGET_ME_NOW = 127,
        COLLECTIBLE_FOREVER_ALONE = 128,
        COLLECTIBLE_BUCKET_OF_LARD = 129,
        COLLECTIBLE_PONY = 130,
        COLLECTIBLE_BOMB_BAG = 131,
        COLLECTIBLE_LUMP_OF_COAL = 132,
        COLLECTIBLE_GUPPYS_PAW = 133,
        COLLECTIBLE_GUPPYS_TAIL = 134,
        COLLECTIBLE_IV_BAG = 135,
        COLLECTIBLE_BEST_FRIEND = 136,
        COLLECTIBLE_REMOTE_DETONATOR = 137,
        COLLECTIBLE_STIGMATA = 138,
        COLLECTIBLE_MOMS_PURSE = 139,
        COLLECTIBLE_BOBS_CURSE = 140,
        COLLECTIBLE_PAGEANT_BOY = 141,
        COLLECTIBLE_SCAPULAR = 142,
        COLLECTIBLE_SPEED_BALL = 143,
        COLLECTIBLE_BUM_FRIEND = 144,
        COLLECTIBLE_GUPPYS_HEAD = 145,
        COLLECTIBLE_PRAYER_CARD = 146,
        COLLECTIBLE_NOTCHED_AXE = 147,
        COLLECTIBLE_INFESTATION = 148,
        COLLECTIBLE_IPECAC = 149,
        COLLECTIBLE_TOUGH_LOVE = 150,
        COLLECTIBLE_MULLIGAN = 151,
        COLLECTIBLE_TECHNOLOGY_2 = 152,
        COLLECTIBLE_MUTANT_SPIDER = 153,
        COLLECTIBLE_CHEMICAL_PEEL = 154,
        COLLECTIBLE_PEEPER = 155,
        COLLECTIBLE_HABIT = 156,
        COLLECTIBLE_BLOODY_LUST = 157,
        COLLECTIBLE_CRYSTAL_BALL = 158,
        COLLECTIBLE_SPIRIT_OF_THE_NIGHT = 159,
        COLLECTIBLE_CRACK_THE_SKY = 160,
        COLLECTIBLE_ANKH = 161,
        COLLECTIBLE_CELTIC_CROSS = 162,
        COLLECTIBLE_GHOST_BABY = 163,
        COLLECTIBLE_CANDLE = 164,
        COLLECTIBLE_CAT_O_NINE_TAILS = 165,
        COLLECTIBLE_D20 = 166,
        COLLECTIBLE_HARLEQUIN_BABY = 167,
        COLLECTIBLE_EPIC_FETUS = 168,
        COLLECTIBLE_POLYPHEMUS = 169,
        COLLECTIBLE_DADDY_LONGLEGS = 170,
        COLLECTIBLE_SPIDER_BUTT = 171,
        COLLECTIBLE_SACRIFICIAL_DAGGER = 172,
        COLLECTIBLE_MITRE = 173,
        COLLECTIBLE_RAINBOW_BABY = 174,
        COLLECTIBLE_DADS_KEY = 175,
        COLLECTIBLE_STEM_CELLS = 176,
        COLLECTIBLE_PORTABLE_SLOT = 177,
        COLLECTIBLE_HOLY_WATER = 178,
        COLLECTIBLE_FATE = 179,
        COLLECTIBLE_BLACK_BEAN = 180,
        COLLECTIBLE_WHITE_PONY = 181,
        COLLECTIBLE_SACRED_HEART = 182,
        COLLECTIBLE_TOOTH_PICKS = 183,
        COLLECTIBLE_HOLY_GRAIL = 184,
        COLLECTIBLE_DEAD_DOVE = 185,
        COLLECTIBLE_BLOOD_RIGHTS = 186,
        COLLECTIBLE_GUPPYS_HAIRBALL = 187,
        COLLECTIBLE_ABEL = 188,
        COLLECTIBLE_SMB_SUPER_FAN = 189,
        COLLECTIBLE_PYRO = 190,
        COLLECTIBLE_3_DOLLAR_BILL = 191,
        COLLECTIBLE_TELEPATHY_BOOK = 192,
        COLLECTIBLE_MEAT = 193,
        COLLECTIBLE_MAGIC_8_BALL = 194,
        COLLECTIBLE_MOMS_COIN_PURSE = 195,
        COLLECTIBLE_SQUEEZY = 196,
        COLLECTIBLE_JESUS_JUICE = 197,
        COLLECTIBLE_BOX = 198,
        COLLECTIBLE_MOMS_KEY = 199,
        COLLECTIBLE_MOMS_EYESHADOW = 200,
        COLLECTIBLE_IRON_BAR = 201,
        COLLECTIBLE_MIDAS_TOUCH = 202,
        COLLECTIBLE_HUMBLEING_BUNDLE = 203,
        COLLECTIBLE_FANNY_PACK = 204,
        COLLECTIBLE_SHARP_PLUG = 205,
        COLLECTIBLE_GUILLOTINE = 206,
        COLLECTIBLE_BALL_OF_BANDAGES = 207,
        COLLECTIBLE_CHAMPION_BELT = 208,
        COLLECTIBLE_BUTT_BOMBS = 209,
        COLLECTIBLE_GNAWED_LEAF = 210,
        COLLECTIBLE_SPIDERBABY = 211,
        COLLECTIBLE_GUPPYS_COLLAR = 212,
        COLLECTIBLE_LOST_CONTACT = 213,
        COLLECTIBLE_ANEMIC = 214,
        COLLECTIBLE_GOAT_HEAD = 215,
        COLLECTIBLE_CEREMONIAL_ROBES = 216,
        COLLECTIBLE_MOMS_WIG = 217,
        COLLECTIBLE_PLACENTA = 218,
        COLLECTIBLE_OLD_BANDAGE = 219,
        COLLECTIBLE_SAD_BOMBS = 220,
        COLLECTIBLE_RUBBER_CEMENT = 221,
        COLLECTIBLE_ANTI_GRAVITY = 222,
        COLLECTIBLE_PYROMANIAC = 223,
        COLLECTIBLE_CRICKETS_BODY = 224,
        COLLECTIBLE_GIMPY = 225,
        COLLECTIBLE_BLACK_LOTUS = 226,
        COLLECTIBLE_PIGGY_BANK = 227,
        COLLECTIBLE_MOMS_PERFUME = 228,
        COLLECTIBLE_MONSTROS_LUNG = 229,
        COLLECTIBLE_ABADDON = 230,
        COLLECTIBLE_BALL_OF_TAR = 231,
        COLLECTIBLE_STOP_WATCH = 232,
        COLLECTIBLE_TINY_PLANET = 233,
        COLLECTIBLE_INFESTATION_2 = 234,
        // 235
        COLLECTIBLE_E_COLI = 236,
        COLLECTIBLE_DEATHS_TOUCH = 237,
        COLLECTIBLE_KEY_PIECE_1 = 238,
        COLLECTIBLE_KEY_PIECE_2 = 239,
        COLLECTIBLE_EXPERIMENTAL_TREATMENT = 240,
        COLLECTIBLE_CONTRACT_FROM_BELOW = 241,
        COLLECTIBLE_INFAMY = 242,
        COLLECTIBLE_TRINITY_SHIELD = 243,
        COLLECTIBLE_TECH_5 = 244,
        COLLECTIBLE_20_20 = 245,
        COLLECTIBLE_BLUE_MAP = 246,
        COLLECTIBLE_BFFS = 247,
        COLLECTIBLE_HIVE_MIND = 248,
        COLLECTIBLE_THERES_OPTIONS = 249,
        COLLECTIBLE_BOGO_BOMBS = 250,
        COLLECTIBLE_STARTER_DECK = 251,
        COLLECTIBLE_LITTLE_BAGGY = 252,
        COLLECTIBLE_MAGIC_SCAB = 253,
        COLLECTIBLE_BLOOD_CLOT = 254,
        COLLECTIBLE_SCREW = 255,
        COLLECTIBLE_HOT_BOMBS = 256,
        COLLECTIBLE_FIRE_MIND = 257,
        COLLECTIBLE_MISSING_NO = 258,
        COLLECTIBLE_DARK_MATTER = 259,
        COLLECTIBLE_BLACK_CANDLE = 260,
        COLLECTIBLE_PROPTOSIS = 261,
        COLLECTIBLE_MISSING_PAGE_2 = 262,
        COLLECTIBLE_CLEAR_RUNE = 263,
        COLLECTIBLE_SMART_FLY = 264,
        COLLECTIBLE_DRY_BABY = 265,
        COLLECTIBLE_JUICY_SACK = 266,
        COLLECTIBLE_ROBO_BABY_2 = 267,
        COLLECTIBLE_ROTTEN_BABY = 268,
        COLLECTIBLE_HEADLESS_BABY = 269,
        COLLECTIBLE_LEECH = 270,
        COLLECTIBLE_MYSTERY_SACK = 271,
        COLLECTIBLE_BBF = 272,
        COLLECTIBLE_BOBS_BRAIN = 273,
        COLLECTIBLE_BEST_BUD = 274,
        COLLECTIBLE_LIL_BRIMSTONE = 275,
        COLLECTIBLE_ISAACS_HEART = 276,
        COLLECTIBLE_LIL_HAUNT = 277,
        COLLECTIBLE_DARK_BUM = 278,
        COLLECTIBLE_BIG_FAN = 279,
        COLLECTIBLE_SISSY_LONGLEGS = 280,
        COLLECTIBLE_PUNCHING_BAG = 281,
        COLLECTIBLE_HOW_TO_JUMP = 282,
        COLLECTIBLE_D100 = 283,
        COLLECTIBLE_D4 = 284,
        COLLECTIBLE_D10 = 285,
        COLLECTIBLE_BLANK_CARD = 286,
        COLLECTIBLE_BOOK_OF_SECRETS = 287,
        COLLECTIBLE_BOX_OF_SPIDERS = 288,
        COLLECTIBLE_RED_CANDLE = 289,
        COLLECTIBLE_THE_JAR = 290,
        COLLECTIBLE_FLUSH = 291,
        COLLECTIBLE_SATANIC_BIBLE = 292,
        COLLECTIBLE_HEAD_OF_KRAMPUS = 293,
        COLLECTIBLE_BUTTER_BEAN = 294,
        COLLECTIBLE_MAGIC_FINGERS = 295,
        COLLECTIBLE_CONVERTER = 296,
        COLLECTIBLE_BLUE_BOX = 297,
        COLLECTIBLE_UNICORN_STUMP = 298,
        COLLECTIBLE_TAURUS = 299,
        COLLECTIBLE_ARIES = 300,
        COLLECTIBLE_CANCER = 301,
        COLLECTIBLE_LEO = 302,
        COLLECTIBLE_VIRGO = 303,
        COLLECTIBLE_LIBRA = 304,
        COLLECTIBLE_SCORPIO = 305,
        COLLECTIBLE_SAGITTARIUS = 306,
        COLLECTIBLE_CAPRICORN = 307,
        COLLECTIBLE_AQUARIUS = 308,
        COLLECTIBLE_PISCES = 309,
        COLLECTIBLE_EVES_MASCARA = 310,
        COLLECTIBLE_JUDAS_SHADOW = 311,
        COLLECTIBLE_MAGGYS_BOW = 312,
        COLLECTIBLE_HOLY_MANTLE = 313,
        COLLECTIBLE_THUNDER_THIGHS = 314,
        COLLECTIBLE_STRANGE_ATTRACTOR = 315,
        COLLECTIBLE_CURSED_EYE = 316,
        COLLECTIBLE_MYSTERIOUS_LIQUID = 317,
        COLLECTIBLE_GEMINI = 318,
        COLLECTIBLE_CAINS_OTHER_EYE = 319,
        COLLECTIBLE_BLUE_BABYS_ONLY_FRIEND = 320,
        COLLECTIBLE_SAMSONS_CHAINS = 321,
        COLLECTIBLE_MONGO_BABY = 322,
        COLLECTIBLE_ISAACS_TEARS = 323,
        COLLECTIBLE_UNDEFINED = 324,
        COLLECTIBLE_SCISSORS = 325,
        COLLECTIBLE_BREATH_OF_LIFE = 326,
        COLLECTIBLE_POLAROID = 327,
        COLLECTIBLE_NEGATIVE = 328,
        COLLECTIBLE_LUDOVICO_TECHNIQUE = 329,
        COLLECTIBLE_SOY_MILK = 330,
        COLLECTIBLE_GODHEAD = 331,
        COLLECTIBLE_LAZARUS_RAGS = 332,
        COLLECTIBLE_MIND = 333,
        COLLECTIBLE_BODY = 334,
        COLLECTIBLE_SOUL = 335,
        COLLECTIBLE_DEAD_ONION = 336,
        COLLECTIBLE_BROKEN_WATCH = 337,
        COLLECTIBLE_BOOMERANG = 338,
        COLLECTIBLE_SAFETY_PIN = 339,
        COLLECTIBLE_CAFFEINE_PILL = 340,
        COLLECTIBLE_TORN_PHOTO = 341,
        COLLECTIBLE_BLUE_CAP = 342,
        COLLECTIBLE_LATCH_KEY = 343,
        COLLECTIBLE_MATCH_BOOK = 344,
        COLLECTIBLE_SYNTHOIL = 345,
        COLLECTIBLE_SNACK = 346,
        COLLECTIBLE_DIPLOPIA = 347,
        COLLECTIBLE_PLACEBO = 348,
        COLLECTIBLE_WOODEN_NICKEL = 349,
        COLLECTIBLE_TOXIC_SHOCK = 350,
        COLLECTIBLE_MEGA_BEAN = 351,
        COLLECTIBLE_GLASS_CANNON = 352,
        COLLECTIBLE_BOMBER_BOY = 353,
        COLLECTIBLE_CRACK_JACKS = 354,
        COLLECTIBLE_MOMS_PEARLS = 355,
        COLLECTIBLE_CAR_BATTERY = 356,
        COLLECTIBLE_BOX_OF_FRIENDS = 357,
        COLLECTIBLE_THE_WIZ = 358,
        COLLECTIBLE_8_INCH_NAILS = 359,
        COLLECTIBLE_INCUBUS = 360,
        COLLECTIBLE_FATES_REWARD = 361,
        COLLECTIBLE_LIL_CHEST = 362,
        COLLECTIBLE_SWORN_PROTECTOR = 363,
        COLLECTIBLE_FRIEND_ZONE = 364,
        COLLECTIBLE_LOST_FLY = 365,
        COLLECTIBLE_SCATTER_BOMBS = 366,
        COLLECTIBLE_STICKY_BOMBS = 367,
        COLLECTIBLE_EPIPHORA = 368,
        COLLECTIBLE_CONTINUUM = 369,
        COLLECTIBLE_MR_DOLLY = 370,
        COLLECTIBLE_CURSE_OF_THE_TOWER = 371,
        COLLECTIBLE_CHARGED_BABY = 372,
        COLLECTIBLE_DEAD_EYE = 373,
        COLLECTIBLE_HOLY_LIGHT = 374,
        COLLECTIBLE_HOST_HAT = 375,
        COLLECTIBLE_RESTOCK = 376,
        COLLECTIBLE_BURSTING_SACK = 377,
        COLLECTIBLE_NUMBER_TWO = 378,
        COLLECTIBLE_PUPULA_DUPLEX = 379,
        COLLECTIBLE_PAY_TO_PLAY = 380,
        COLLECTIBLE_EDENS_BLESSING = 381,
        COLLECTIBLE_FRIEND_BALL = 382,
        COLLECTIBLE_TEAR_DETONATOR = 383,
        COLLECTIBLE_LIL_GURDY = 384,
        COLLECTIBLE_BUMBO = 385,
        COLLECTIBLE_D12 = 386,
        COLLECTIBLE_CENSER = 387,
        COLLECTIBLE_KEY_BUM = 388,
        COLLECTIBLE_RUNE_BAG = 389,
        COLLECTIBLE_SERAPHIM = 390,
        COLLECTIBLE_BETRAYAL = 391,
        COLLECTIBLE_ZODIAC = 392,
        COLLECTIBLE_SERPENTS_KISS = 393,
        COLLECTIBLE_MARKED = 394,
        COLLECTIBLE_TECH_X = 395,
        COLLECTIBLE_VENTRICLE_RAZOR = 396,
        COLLECTIBLE_TRACTOR_BEAM = 397,
        COLLECTIBLE_GODS_FLESH = 398,
        COLLECTIBLE_MAW_OF_THE_VOID = 399,
        COLLECTIBLE_SPEAR_OF_DESTINY = 400,
        COLLECTIBLE_EXPLOSIVO = 401,
        COLLECTIBLE_CHAOS = 402,
        COLLECTIBLE_SPIDER_MOD = 403,
        COLLECTIBLE_FARTING_BABY = 404,
        COLLECTIBLE_GB_BUG = 405,
        COLLECTIBLE_D8 = 406,
        COLLECTIBLE_PURITY = 407,
        COLLECTIBLE_ATHAME = 408,
        COLLECTIBLE_EMPTY_VESSEL = 409,
        COLLECTIBLE_EVIL_EYE = 410,
        COLLECTIBLE_LUSTY_BLOOD = 411,
        COLLECTIBLE_CAMBION_CONCEPTION = 412,
        COLLECTIBLE_IMMACULATE_CONCEPTION = 413,
        COLLECTIBLE_MORE_OPTIONS = 414,
        COLLECTIBLE_CROWN_OF_LIGHT = 415,
        COLLECTIBLE_DEEP_POCKETS = 416,
        COLLECTIBLE_SUCCUBUS = 417,
        COLLECTIBLE_FRUIT_CAKE = 418,
        COLLECTIBLE_TELEPORT_2 = 419,
        COLLECTIBLE_BLACK_POWDER = 420,
        COLLECTIBLE_KIDNEY_BEAN = 421,
        COLLECTIBLE_GLOWING_HOUR_GLASS = 422,
        COLLECTIBLE_CIRCLE_OF_PROTECTION = 423,
        COLLECTIBLE_SACK_HEAD = 424,
        COLLECTIBLE_NIGHT_LIGHT = 425,
        COLLECTIBLE_OBSESSED_FAN = 426,
        COLLECTIBLE_MINE_CRAFTER = 427,
        COLLECTIBLE_PJS = 428,
        COLLECTIBLE_HEAD_OF_THE_KEEPER = 429,
        COLLECTIBLE_PAPA_FLY = 430,
        COLLECTIBLE_MULTIDIMENSIONAL_BABY = 431,
        COLLECTIBLE_GLITTER_BOMBS = 432,
        COLLECTIBLE_MY_SHADOW = 433,
        COLLECTIBLE_JAR_OF_FLIES = 434,
        COLLECTIBLE_LIL_LOKI = 435,
        COLLECTIBLE_MILK = 436,
        COLLECTIBLE_D7 = 437,
        COLLECTIBLE_BINKY = 438,
        COLLECTIBLE_MOMS_BOX = 439,
        COLLECTIBLE_KIDNEY_STONE = 440,
        COLLECTIBLE_MEGA_BLAST = 441,
        COLLECTIBLE_DARK_PRINCES_CROWN = 442,
        COLLECTIBLE_APPLE = 443,
        COLLECTIBLE_LEAD_PENCIL = 444,
        COLLECTIBLE_DOG_TOOTH = 445,
        COLLECTIBLE_DEAD_TOOTH = 446,
        COLLECTIBLE_LINGER_BEAN = 447,
        COLLECTIBLE_SHARD_OF_GLASS = 448,
        COLLECTIBLE_METAL_PLATE = 449,
        COLLECTIBLE_EYE_OF_GREED = 450,
        COLLECTIBLE_TAROT_CLOTH = 451,
        COLLECTIBLE_VARICOSE_VEINS = 452,
        COLLECTIBLE_COMPOUND_FRACTURE = 453,
        COLLECTIBLE_POLYDACTYLY = 454,
        COLLECTIBLE_DADS_LOST_COIN = 455,
        COLLECTIBLE_MIDNIGHT_SNACK = 456,
        COLLECTIBLE_CONE_HEAD = 457,
        COLLECTIBLE_BELLY_BUTTON = 458,
        COLLECTIBLE_SINUS_INFECTION = 459,
        COLLECTIBLE_GLAUCOMA = 460,
        COLLECTIBLE_PARASITOID = 461,
        COLLECTIBLE_EYE_OF_BELIAL = 462,
        COLLECTIBLE_SULFURIC_ACID = 463,
        COLLECTIBLE_GLYPH_OF_BALANCE = 464,
        COLLECTIBLE_ANALOG_STICK = 465,
        COLLECTIBLE_CONTAGION = 466,
        COLLECTIBLE_FINGER = 467,
        COLLECTIBLE_SHADE = 468,
        COLLECTIBLE_DEPRESSION = 469,
        COLLECTIBLE_HUSHY = 470,
        COLLECTIBLE_LIL_MONSTRO = 471,
        COLLECTIBLE_KING_BABY = 472,
        COLLECTIBLE_BIG_CHUBBY = 473,
        COLLECTIBLE_BROKEN_GLASS_CANNON = 474,
        COLLECTIBLE_PLAN_C = 475,
        COLLECTIBLE_D1 = 476,
        COLLECTIBLE_VOID = 477,
        COLLECTIBLE_PAUSE = 478,
        COLLECTIBLE_SMELTER = 479,
        COLLECTIBLE_COMPOST = 480,
        COLLECTIBLE_DATAMINER = 481,
        COLLECTIBLE_CLICKER = 482,
        COLLECTIBLE_MAMA_MEGA = 483,
        COLLECTIBLE_WAIT_WHAT = 484,
        COLLECTIBLE_CROOKED_PENNY = 485,
        COLLECTIBLE_DULL_RAZOR = 486,
        COLLECTIBLE_POTATO_PEELER = 487,
        COLLECTIBLE_METRONOME = 488,
        COLLECTIBLE_D_INFINITY = 489,
        COLLECTIBLE_EDENS_SOUL = 490,
        COLLECTIBLE_ACID_BABY = 491,
        COLLECTIBLE_YO_LISTEN = 492,
        COLLECTIBLE_ADRENALINE = 493,
        COLLECTIBLE_JACOBS_LADDER = 494,
        COLLECTIBLE_GHOST_PEPPER = 495,
        COLLECTIBLE_EUTHANASIA = 496,
        COLLECTIBLE_CAMO_UNDIES = 497,
        COLLECTIBLE_DUALITY = 498,
        COLLECTIBLE_EUCHARIST = 499,
        COLLECTIBLE_SACK_OF_SACKS = 500,
        COLLECTIBLE_GREEDS_GULLET = 501,
        COLLECTIBLE_LARGE_ZIT = 502,
        COLLECTIBLE_LITTLE_HORN = 503,
        COLLECTIBLE_BROWN_NUGGET = 504,
        COLLECTIBLE_POKE_GO = 505,
        COLLECTIBLE_BACKSTABBER = 506,
        COLLECTIBLE_SHARP_STRAW = 507,
        COLLECTIBLE_MOMS_RAZOR = 508,
        COLLECTIBLE_BLOODSHOT_EYE = 509,
        COLLECTIBLE_DELIRIOUS = 510,
        
        // Booster Pack #1
        COLLECTIBLE_ANGRY_FLY = 511,
        COLLECTIBLE_BLACK_HOLE = 512,
        COLLECTIBLE_BOZO = 513,
        COLLECTIBLE_BROKEN_MODEM = 514,
        COLLECTIBLE_MYSTERY_GIFT = 515,
        COLLECTIBLE_SPRINKLER = 516,
        COLLECTIBLE_FAST_BOMBS = 517,
        COLLECTIBLE_BUDDY_IN_A_BOX = 518,
        COLLECTIBLE_LIL_DELIRIUM = 519,

        // Booster Pack #2
        COLLECTIBLE_JUMPER_CABLES = 520,
        COLLECTIBLE_COUPON = 521,
        COLLECTIBLE_TELEKINESIS = 522,
        COLLECTIBLE_MOVING_BOX = 523,
        COLLECTIBLE_TECHNOLOGY_ZERO = 524,
        COLLECTIBLE_LEPROSY = 525,
        
        // Booster Pack #3
        COLLECTIBLE_7_SEALS = 526,
        COLLECTIBLE_MR_ME = 527,
        COLLECTIBLE_ANGELIC_PRISM = 528,
        COLLECTIBLE_POP = 529,

        // Booster Pack #4
        COLLECTIBLE_DEATHS_LIST = 530,
        COLLECTIBLE_HAEMOLACRIA = 531,
        COLLECTIBLE_LACHRYPHAGY = 532,
        COLLECTIBLE_TRISAGION = 533,
        COLLECTIBLE_SCHOOLBAG = 534,
        
        // Booster Pack #5
        COLLECTIBLE_BLANKET = 535,
        COLLECTIBLE_SACRIFICIAL_ALTAR = 536,
        COLLECTIBLE_LIL_SPEWER = 537,
        COLLECTIBLE_MARBLES = 538,
        COLLECTIBLE_MYSTERY_EGG = 539,
        COLLECTIBLE_FLAT_STONE = 540,

        COLLECTIBLE_MARROW = 541,
        COLLECTIBLE_SLIPPED_RIB = 542,
        COLLECTIBLE_HALLOWED_GROUND = 543,
        COLLECTIBLE_POINTY_RIB = 544,
        COLLECTIBLE_BOOK_OF_THE_DEAD = 545,
        COLLECTIBLE_DADS_RING = 546,
        COLLECTIBLE_DIVORCE_PAPERS = 547,
        COLLECTIBLE_JAW_BONE = 548,
        COLLECTIBLE_BRITTLE_BONES = 549,

        COLLECTIBLE_BROKEN_SHOVEL_1 = 550,
        COLLECTIBLE_BROKEN_SHOVEL_2 = 551,
        COLLECTIBLE_MOMS_SHOVEL = 552,

        //NUM_COLLECTIBLES = 553
        
        // Repentance
        COLLECTIBLE_MUCORMYCOSIS = 553,
        COLLECTIBLE_2SPOOKY = 554,
        COLLECTIBLE_GOLDEN_RAZOR = 555,
        COLLECTIBLE_SULFUR = 556,
        COLLECTIBLE_FORTUNE_COOKIE = 557,
        COLLECTIBLE_EYE_SORE = 558,
        COLLECTIBLE_120_VOLT = 559,
        COLLECTIBLE_IT_HURTS = 560,
        COLLECTIBLE_ALMOND_MILK = 561,
        COLLECTIBLE_ROCK_BOTTOM = 562,
        COLLECTIBLE_NANCY_BOMBS = 563,
        COLLECTIBLE_BAR_OF_SOAP = 564,
        COLLECTIBLE_BLOOD_PUPPY = 565,
        COLLECTIBLE_DREAM_CATCHER = 566,
        COLLECTIBLE_PASCHAL_CANDLE = 567,
        COLLECTIBLE_DIVINE_INTERVENTION = 568,
        COLLECTIBLE_BLOOD_OATH = 569,
        COLLECTIBLE_PLAYDOUGH_COOKIE = 570,
        COLLECTIBLE_SOCKS = 571,
        COLLECTIBLE_EYE_OF_THE_OCCULT = 572,
        COLLECTIBLE_IMMACULATE_HEART = 573,
        COLLECTIBLE_MONSTRANCE = 574,
        COLLECTIBLE_INTRUDER = 575,
        COLLECTIBLE_DIRTY_MIND = 576,
        COLLECTIBLE_DAMOCLES = 577,
        COLLECTIBLE_FREE_LEMONADE = 578,
        COLLECTIBLE_SPIRIT_SWORD = 579,
        COLLECTIBLE_RED_KEY = 580,
        COLLECTIBLE_PSY_FLY = 581,
        COLLECTIBLE_WAVY_CAP = 582,
        COLLECTIBLE_ROCKET_IN_A_JAR = 583,
        COLLECTIBLE_BOOK_OF_VIRTUES = 584,
        COLLECTIBLE_ALABASTER_BOX = 585,
        COLLECTIBLE_STAIRWAY = 586,
        // 587
        COLLECTIBLE_SOL = 588,
        COLLECTIBLE_LUNA = 589,
        COLLECTIBLE_MERCURIUS = 590,
        COLLECTIBLE_VENUS = 591,
        COLLECTIBLE_TERRA = 592,
        COLLECTIBLE_MARS = 593,
        COLLECTIBLE_JUPITER = 594,
        COLLECTIBLE_SATURNUS = 595,
        COLLECTIBLE_URANUS = 596,
        COLLECTIBLE_NEPTUNUS = 597,
        COLLECTIBLE_PLUTO = 598,
        COLLECTIBLE_VOODOO_HEAD = 599,
        COLLECTIBLE_EYE_DROPS = 600,
        COLLECTIBLE_ACT_OF_CONTRITION = 601,
        COLLECTIBLE_MEMBER_CARD = 602,
        COLLECTIBLE_BATTERY_PACK = 603,
        COLLECTIBLE_MOMS_BRACELET = 604,
        COLLECTIBLE_SCOOPER = 605,
        COLLECTIBLE_OCULAR_RIFT = 606,
        COLLECTIBLE_BOILED_BABY = 607,
        COLLECTIBLE_FREEZER_BABY = 608,
        COLLECTIBLE_ETERNAL_D6 = 609,
        COLLECTIBLE_BIRD_CAGE = 610,
        COLLECTIBLE_LARYNX = 611,
        COLLECTIBLE_LOST_SOUL = 612,
        // 613
        COLLECTIBLE_BLOOD_BOMBS = 614,
        COLLECTIBLE_LIL_DUMPY = 615,
        COLLECTIBLE_BIRDS_EYE = 616,
        COLLECTIBLE_LODESTONE = 617,
        COLLECTIBLE_ROTTEN_TOMATO = 618,
        COLLECTIBLE_BIRTHRIGHT = 619,
        // 620
        COLLECTIBLE_RED_STEW = 621,
        COLLECTIBLE_GENESIS = 622,
        COLLECTIBLE_SHARP_KEY = 623,
        COLLECTIBLE_BOOSTER_PACK = 624,
        COLLECTIBLE_MEGA_MUSH = 625,
        COLLECTIBLE_KNIFE_PIECE_1 = 626,
        COLLECTIBLE_KNIFE_PIECE_2 = 627,
        COLLECTIBLE_DEATH_CERTIFICATE = 628,
        COLLECTIBLE_BOT_FLY = 629,
        // 630
        COLLECTIBLE_MEAT_CLEAVER = 631,
        COLLECTIBLE_EVIL_CHARM = 632,
        COLLECTIBLE_DOGMA = 633,
        COLLECTIBLE_PURGATORY = 634,
        COLLECTIBLE_STITCHES = 635,
        COLLECTIBLE_R_KEY = 636,
        COLLECTIBLE_KNOCKOUT_DROPS = 637,
        COLLECTIBLE_ERASER = 638,
        COLLECTIBLE_YUCK_HEART = 639,
        COLLECTIBLE_URN_OF_SOULS = 640,
        COLLECTIBLE_AKELDAMA = 641,
        COLLECTIBLE_MAGIC_SKIN = 642,
        COLLECTIBLE_REVELATION = 643,
        COLLECTIBLE_CONSOLATION_PRIZE = 644,
        COLLECTIBLE_TINYTOMA = 645,
        COLLECTIBLE_BRIMSTONE_BOMBS = 646,
        COLLECTIBLE_4_5_VOLT = 647,
        // 648
        COLLECTIBLE_FRUITY_PLUM = 649,
        COLLECTIBLE_PLUM_FLUTE = 650,
        COLLECTIBLE_STAR_OF_BETHLEHEM = 651,
        COLLECTIBLE_CUBE_BABY = 652,
        COLLECTIBLE_VADE_RETRO = 653,
        COLLECTIBLE_FALSE_PHD = 654,
        COLLECTIBLE_SPIN_TO_WIN = 655,
        COLLECTIBLE_DAMOCLES_PASSIVE = 656,
        COLLECTIBLE_VASCULITIS = 657,
        COLLECTIBLE_GIANT_CELL = 658,
        COLLECTIBLE_TROPICAMIDE = 659,
        COLLECTIBLE_CARD_READING = 660,
        COLLECTIBLE_QUINTS = 661,
        // 662
        COLLECTIBLE_TOOTH_AND_NAIL = 663,
        COLLECTIBLE_BINGE_EATER = 664,
        COLLECTIBLE_GUPPYS_EYE = 665,
        // 666
        COLLECTIBLE_STRAW_MAN = 667,
        COLLECTIBLE_DADS_NOTE = 668,
        COLLECTIBLE_SAUSAGE = 669,
        COLLECTIBLE_OPTIONS = 670,
        COLLECTIBLE_CANDY_HEART = 671,
        COLLECTIBLE_POUND_OF_FLESH = 672,
        COLLECTIBLE_REDEMPTION = 673,
        COLLECTIBLE_SPIRIT_SHACKLES = 674,
        COLLECTIBLE_CRACKED_ORB = 675,
        COLLECTIBLE_EMPTY_HEART = 676,
        COLLECTIBLE_ASTRAL_PROJECTION = 677,
        COLLECTIBLE_C_SECTION = 678,
        COLLECTIBLE_LIL_ABADDON = 679,
        COLLECTIBLE_MONTEZUMAS_REVENGE = 680,
        COLLECTIBLE_LIL_PORTAL = 681,
        COLLECTIBLE_WORM_FRIEND = 682,
        COLLECTIBLE_BONE_SPURS = 683,
        COLLECTIBLE_HUNGRY_SOUL = 684,
        COLLECTIBLE_JAR_OF_WISPS = 685,
        COLLECTIBLE_SOUL_LOCKET = 686,
        COLLECTIBLE_FRIEND_FINDER = 687,
        COLLECTIBLE_INNER_CHILD = 688,
        COLLECTIBLE_GLITCHED_CROWN = 689,
        COLLECTIBLE_JELLY_BELLY = 690,
        COLLECTIBLE_SACRED_ORB = 691,
        COLLECTIBLE_SANGUINE_BOND = 692,
        COLLECTIBLE_SWARM = 693,
        COLLECTIBLE_HEARTBREAK = 694,
        COLLECTIBLE_BLOODY_GUST = 695,
        COLLECTIBLE_SALVATION = 696,
        COLLECTIBLE_VANISHING_TWIN = 697,
        COLLECTIBLE_TWISTED_PAIR = 698,
        COLLECTIBLE_AZAZELS_RAGE = 699,
        COLLECTIBLE_ECHO_CHAMBER = 700,
        COLLECTIBLE_ISAACS_TOMB = 701,
        COLLECTIBLE_VENGEFUL_SPIRIT = 702,
        COLLECTIBLE_ESAU_JR = 703,
        COLLECTIBLE_BERSERK = 704,
        COLLECTIBLE_DARK_ARTS = 705,
        COLLECTIBLE_ABYSS = 706,
        COLLECTIBLE_SUPPER = 707,
        COLLECTIBLE_STAPLER = 708,
        COLLECTIBLE_SUPLEX = 709,
        COLLECTIBLE_BAG_OF_CRAFTING = 710,
        COLLECTIBLE_FLIP = 711,
        COLLECTIBLE_LEMEGETON = 712,
        COLLECTIBLE_SUMPTORIUM = 713,
        COLLECTIBLE_RECALL = 714,
        COLLECTIBLE_HOLD = 715,
        COLLECTIBLE_KEEPERS_SACK = 716,
        COLLECTIBLE_KEEPERS_KIN = 717,
        // 718
        COLLECTIBLE_KEEPERS_BOX = 719,
        COLLECTIBLE_EVERYTHING_JAR = 720,
        COLLECTIBLE_TMTRAINER = 721,
        COLLECTIBLE_ANIMA_SOLA = 722,
        COLLECTIBLE_SPINDOWN_DICE = 723,
        COLLECTIBLE_HYPERCOAGULATION = 724,
        COLLECTIBLE_IBS = 725,
        COLLECTIBLE_HEMOPTYSIS = 726,
        COLLECTIBLE_GHOST_BOMBS = 727,
        COLLECTIBLE_GELLO = 728,
        COLLECTIBLE_DECAP_ATTACK = 729,
        COLLECTIBLE_GLASS_EYE = 730,
        COLLECTIBLE_STYE = 731,
        COLLECTIBLE_MOMS_RING = 732,
        
        NUM_COLLECTIBLES = 733
};
        
enum LevelStateFlag
{
        STATE_BUM_KILLED = 0,
        STATE_EVIL_BUM_KILLED = 1,
        STATE_REDHEART_DAMAGED = 2,
        STATE_BUM_LEFT = 3,
        STATE_EVIL_BUM_LEFT = 4,
        STATE_DAMAGED = 5,
        STATE_SHOPKEEPER_KILLED_LVL = 6,
        STATE_COMPASS_EFFECT = 7,
        STATE_MAP_EFFECT = 8,
        STATE_BLUE_MAP_EFFECT = 9,
        STATE_FULL_MAP_EFFECT = 10,
        STATE_GREED_LOST_PENALTY = 11,
        STATE_GREED_MONSTRO_SPAWNED = 12,
        STATE_ITEM_DUNGEON_FOUND = 13,
        STATE_MAMA_MEGA_USED = 14,
        //NUM_STATE_FLAGS = 15

        STATE_WOODEN_CROSS_REMOVED = 15,
        STATE_SHOVEL_QUEST_TRIGGERED = 16,
        STATE_SATANIC_BIBLE_USED = 17,
        STATE_SOL_EFFECT = 18,
        STATE_LEVEL_START_TRIGGERED = 19,
        STATE_LUNA_EFFECT = 20,
        STATE_VOID_DOOR_DISABLED = 21,
        STATE_MINESHAFT_ESCAPE = 22,
        STATE_MIRROR_BROKEN = 23,
        NUM_STATE_FLAGS = 24
};

enum TrinketType
{
        TRINKET_NULL = 0,
        TRINKET_SWALLOWED_PENNY = 1,
        TRINKET_PETRIFIED_POOP = 2,
        TRINKET_AAA_BATTERY = 3,
        TRINKET_BROKEN_REMOTE = 4,
        TRINKET_PURPLE_HEART = 5,
        TRINKET_BROKEN_MAGNET = 6,
        TRINKET_ROSARY_BEAD = 7,
        TRINKET_CARTRIDGE = 8,
        TRINKET_PULSE_WORM = 9,
        TRINKET_WIGGLE_WORM = 10,
        TRINKET_RING_WORM = 11,
        TRINKET_FLAT_WORM = 12,
        TRINKET_STORE_CREDIT = 13,
        TRINKET_CALLUS = 14,
        TRINKET_LUCKY_ROCK = 15,
        TRINKET_MOMS_TOENAIL = 16,
        TRINKET_BLACK_LIPSTICK = 17,
        TRINKET_BIBLE_TRACT = 18,
        TRINKET_PAPER_CLIP = 19,
        TRINKET_MONKEY_PAW = 20,
        TRINKET_MYSTERIOUS_PAPER = 21,
        TRINKET_DAEMONS_TAIL = 22,
        TRINKET_MISSING_POSTER = 23,
        TRINKET_BUTT_PENNY = 24,
        TRINKET_MYSTERIOUS_CANDY = 25,
        TRINKET_HOOK_WORM = 26,
        TRINKET_WHIP_WORM = 27,
        TRINKET_BROKEN_ANKH = 28,
        TRINKET_FISH_HEAD = 29,
        TRINKET_PINKY_EYE = 30,
        TRINKET_PUSH_PIN = 31,
        TRINKET_LIBERTY_CAP = 32,
        TRINKET_UMBILICAL_CORD = 33,
        TRINKET_CHILDS_HEART = 34,
        TRINKET_CURVED_HORN = 35,
        TRINKET_RUSTED_KEY = 36,
        TRINKET_GOAT_HOOF = 37,
        TRINKET_MOMS_PEARL = 38,
        TRINKET_CANCER = 39,
        TRINKET_RED_PATCH = 40,
        TRINKET_MATCH_STICK = 41,
        TRINKET_LUCKY_TOE = 42,
        TRINKET_CURSED_SKULL = 43,
        TRINKET_SAFETY_CAP = 44,
        TRINKET_ACE_SPADES = 45,
        TRINKET_ISAACS_FORK = 46,
        TRINKET_POLAROID_OBSOLETE = 47,
        TRINKET_MISSING_PAGE = 48,
        TRINKET_BLOODY_PENNY = 49,
        TRINKET_BURNT_PENNY = 50,
        TRINKET_FLAT_PENNY = 51,
        TRINKET_COUNTERFEIT_PENNY = 52,
        TRINKET_TICK = 53,
        TRINKET_ISAACS_HEAD = 54,
        TRINKET_MAGGYS_FAITH = 55,
        TRINKET_JUDAS_TONGUE = 56,
        TRINKET_SOUL = 57,
        TRINKET_SAMSONS_LOCK = 58,
        TRINKET_CAINS_EYE = 59,
        TRINKET_EVES_BIRD_FOOT = 60,
        TRINKET_LEFT_HAND = 61,
        TRINKET_SHINY_ROCK = 62,
        TRINKET_SAFETY_SCISSORS = 63,
        TRINKET_RAINBOW_WORM = 64,
        TRINKET_TAPE_WORM = 65,
        TRINKET_LAZY_WORM = 66,
        TRINKET_CRACKED_DICE = 67,
        TRINKET_SUPER_MAGNET = 68,
        TRINKET_FADED_POLAROID = 69,
        TRINKET_LOUSE = 70,
        TRINKET_BOBS_BLADDER = 71,
        TRINKET_WATCH_BATTERY = 72,
        TRINKET_BLASTING_CAP = 73,
        TRINKET_STUD_FINDER = 74,
        TRINKET_ERROR = 75,
        TRINKET_POKER_CHIP = 76,
        TRINKET_BLISTER = 77,
        TRINKET_SECOND_HAND = 78,
        TRINKET_ENDLESS_NAMELESS = 79,
        TRINKET_BLACK_FEATHER = 80,
        TRINKET_BLIND_RAGE = 81,
        TRINKET_GOLDEN_HORSE_SHOE = 82,
        TRINKET_STORE_KEY = 83,
        TRINKET_RIB_OF_GREED = 84,
        TRINKET_KARMA = 85,
        TRINKET_LIL_LARVA = 86,
        TRINKET_MOMS_LOCKET = 87,
        TRINKET_NO = 88,
        TRINKET_CHILD_LEASH = 89,
        TRINKET_BROWN_CAP = 90,
        TRINKET_MECONIUM = 91,
        TRINKET_CRACKED_CROWN = 92,
        TRINKET_USED_DIAPER = 93,
        TRINKET_FISH_TAIL = 94,
        TRINKET_BLACK_TOOTH = 95,
        TRINKET_OUROBOROS_WORM = 96,
        TRINKET_TONSIL = 97,
        TRINKET_NOSE_GOBLIN = 98,
        TRINKET_SUPER_BALL = 99,
        TRINKET_VIBRANT_BULB = 100,
        TRINKET_DIM_BULB = 101,
        TRINKET_FRAGMENTED_CARD = 102,
        TRINKET_EQUALITY = 103,
        TRINKET_WISH_BONE = 104,
        TRINKET_BAG_LUNCH = 105,
        TRINKET_LOST_CORK = 106,
        TRINKET_CROW_HEART = 107,
        TRINKET_WALNUT = 108,
        TRINKET_DUCT_TAPE = 109,
        TRINKET_SILVER_DOLLAR = 110,
        TRINKET_BLOODY_CROWN = 111,
        TRINKET_PAY_TO_WIN = 112,
        TRINKET_LOCUST_OF_WRATH = 113,
        TRINKET_LOCUST_OF_PESTILENCE = 114,
        TRINKET_LOCUST_OF_FAMINE = 115,
        TRINKET_LOCUST_OF_DEATH = 116,
        TRINKET_LOCUST_OF_CONQUEST = 117,
        TRINKET_BAT_WING = 118,
        TRINKET_STEM_CELL = 119,
        
        // Booster pack #1
        TRINKET_HAIRPIN = 120,
        TRINKET_WOODEN_CROSS = 121,
        TRINKET_BUTTER = 122,

        // Booster pack #2
        TRINKET_FILIGREE_FEATHERS = 123,
        
        // Booster pack #3
        TRINKET_DOOR_STOP = 124,
        
        // Booster pack #4
        TRINKET_EXTENSION_CORD = 125,
        
        // Booster pack #5
        TRINKET_ROTTEN_PENNY = 126,
        TRINKET_BABY_BENDER = 127,
        TRINKET_FINGER_BONE = 128,
        
        //NUM_TRINKETS = 129
        
        // Repentance
        TRINKET_JAW_BREAKER = 129,
        TRINKET_CHEWED_PEN = 130,
        TRINKET_BLESSED_PENNY = 131,
        TRINKET_BROKEN_SYRINGE = 132,
        TRINKET_SHORT_FUSE = 133,
        TRINKET_GIGANTE_BEAN = 134,
        TRINKET_LIGHTER = 135,
        TRINKET_BROKEN_PADLOCK = 136,
        TRINKET_MYOSOTIS = 137,
        TRINKET_M = 138,
        TRINKET_TEARDROP_CHARM = 139,
        TRINKET_APPLE_OF_SODOM = 140,
        TRINKET_FORGOTTEN_LULLABY = 141,
        TRINKET_BETHS_FAITH = 142,
        TRINKET_OLD_CAPACITOR = 143,
        TRINKET_BRAIN_WORM = 144,
        TRINKET_PERFECTION = 145,
        TRINKET_DEVILS_CROWN = 146,
        TRINKET_CHARGED_PENNY = 147,
        TRINKET_FRIENDSHIP_NECKLACE = 148,
        TRINKET_PANIC_BUTTON = 149,
        TRINKET_BLUE_KEY = 150,
        TRINKET_FLAT_FILE = 151,
        TRINKET_TELESCOPE_LENS = 152,
        TRINKET_MOMS_LOCK = 153,
        TRINKET_DICE_BAG = 154,
        TRINKET_HOLY_CROWN = 155,
        TRINKET_MOTHERS_KISS = 156,
        TRINKET_TORN_CARD = 157,
        TRINKET_TORN_POCKET = 158,
        TRINKET_GILDED_KEY = 159,
        TRINKET_LUCKY_SACK = 160,
        TRINKET_WICKED_CROWN = 161,
        TRINKET_AZAZELS_STUMP = 162,
        TRINKET_DINGLE_BERRY = 163,
        TRINKET_RING_CAP = 164,
        TRINKET_NUH_UH = 165,
        TRINKET_MODELING_CLAY = 166,
        TRINKET_POLISHED_BONE = 167,
        TRINKET_HOLLOW_HEART = 168,
        TRINKET_KIDS_DRAWING = 169,
        TRINKET_CRYSTAL_KEY = 170,
        TRINKET_KEEPERS_BARGAIN = 171,
        TRINKET_CURSED_PENNY = 172,
        TRINKET_YOUR_SOUL = 173,
        TRINKET_NUMBER_MAGNET = 174,
        TRINKET_STRANGE_KEY = 175,
        TRINKET_LIL_CLOT = 176,
        TRINKET_TEMPORARY_TATTOO = 177,
        TRINKET_SWALLOWED_M80 = 178,
        TRINKET_RC_REMOTE = 179,
        TRINKET_FOUND_SOUL = 180,
        TRINKET_EXPANSION_PACK = 181,
        TRINKET_BETHS_ESSENCE = 182,
        TRINKET_THE_TWINS = 183,
        TRINKET_ADOPTION_PAPERS = 184,
        TRINKET_CRICKET_LEG = 185,
        TRINKET_APOLLYONS_BEST_FRIEND = 186,
        TRINKET_BROKEN_GLASSES = 187,
        TRINKET_ICE_CUBE = 188,
        TRINKET_SIGIL_OF_BAPHOMET = 189,
        NUM_TRINKETS = 190,
        
        // Golden trinkets
        TRINKET_GOLDEN_FLAG = 0x8000,
        TRINKET_ID_MASK = 0x7fff
};

enum StageType
{
        STAGETYPE_ORIGINAL = 0,
        STAGETYPE_WOTL = 1,
        STAGETYPE_AFTERBIRTH = 2,
        STAGETYPE_GREEDMODE = 3, // deprecated, Greed Mode no longer has its own stages
        STAGETYPE_REPENTANCE = 4,
        STAGETYPE_REPENTANCE_B = 5,
};

enum LevelStage 
{
        STAGE_NULL = 0,
        STAGE1_1 = 1,
        STAGE1_2 = 2,
        STAGE2_1 = 3,
        STAGE2_2 = 4,
        STAGE3_1 = 5,
        STAGE3_2 = 6,
        STAGE4_1 = 7,
        STAGE4_2 = 8,
        STAGE4_3 = 9,
        STAGE5 = 10,
        STAGE6 = 11,
        STAGE7 = 12,
        STAGE8 = 13, // Home
        NUM_STAGES = 14,
        
        STAGE1_GREED = 1,
        STAGE2_GREED = 2,
        STAGE3_GREED = 3,
        STAGE4_GREED = 4,
        STAGE5_GREED = 5,
        STAGE6_GREED = 6,
        STAGE7_GREED = 7,
        
        NUM_BACKWARDS_STAGES = 7 // Save stages up to Mausoleum II for the Ascent (7 stages)
};

static DWORD GetBaseAddress()
{
        return (DWORD)GetModuleHandle(NULL);
}

enum BagOfCraftingPickup : uint8_t 
{
        BOC_NONE = 0,
        BOC_RED_HEART = 1,
        BOC_SOUL_HEART = 2,
        BOC_BLACK_HEART = 3,
        BOC_ETERNAL_HEART = 4,
        BOC_GOLD_HEART = 5,
        BOC_BONE_HEART = 6,
        BOC_ROTTEN_HEART = 7,
        BOC_PENNY = 8,
        BOC_NICKEL = 9,
        BOC_DIME = 10,
        BOC_LUCKY_PENNY = 11,
        BOC_KEY = 12,
        BOC_GOLD_KEY = 13,
        BOC_CHARGED_KEY = 14,
        BOC_BOMB = 15,
        BOC_GOLD_BOMB = 16,
        BOC_GIGA_BOMB = 17,
        BOC_MINI_BATTERY = 18,
        BOC_BATTERY = 19,
        BOC_MEGA_BATTERY = 20,
        BOC_CARD = 21,
        BOC_PILL = 22,
        BOC_RUNE = 23,
        BOC_DICE_SHARD = 24,
        BOC_CRACKED_KEY = 25,
        BOC_GOLD_PENNY = 26,
        BOC_GOLD_PILL = 27,
        BOC_GOLD_BATTERY = 28,
        BOC_POOP = 29,
        BOC_MAX = 30
};

enum RailType : uint8_t {
    RAIL_HORIZONTAL = 0,
    RAIL_VERTICAL = 1,
    RAIL_UP_RIGHT = 2,
    RAIL_DOWN_RIGHT = 3,
    RAIL_UP_LEFT = 4,
    RAIL_DOWN_LEFT = 5,
    RAIL_CROSSING = 6,
    RAIL_DOOR_LEFT = 144,
    RAIL_DOOR_BOTTOM = 145,
    RAIL_DOOR_RIGHT = 160,
    RAIL_DOOR_TOP = 161,
    RAIL_NONE = 255
};

enum ShaderType : uint8_t {
    SHADER_COLOR_OFFSET,
    SHADER_PIXELATION,
    SHADER_BLOOM,
    SHADER_COLOR_CORRECTION,
    SHADER_HQ4X,
    SHADER_SHOCKWAVE,
    SHADER_OLDTV,
    SHADER_WATER,
    SHADER_HALLUCINATION,
    SHADER_COLOR_MOD,
    SHADER_COLOR_OFFSET_CHAMPION,
    SHADER_WATER_V2,
    SHADER_BACKGROUND,
    SHADER_WATER_OVERLAY,
    SHADER_UNK,
    SHADER_COLOR_OFFSET_DOGMA,
    SHADER_COLOR_OFFSET_GOLD,
    SHADER_DIZZY,
    SHADER_HEAT_WAVE,
    SHADER_MIRROR,
    SHADER_MAX
};

enum eItemPoolType {
    POOL_NULL = -1,
    POOL_TREASURE = 0,
    POOL_SHOP = 1,
    POOL_BOSS = 2,
    POOL_DEVIL = 3,
    POOL_ANGEL = 4,
    POOL_SECRET = 5,
    POOL_LIBRARY = 6,
    POOL_SHELL_GAME = 7, // unused (for now)
    POOL_GOLDEN_CHEST = 8,
    POOL_RED_CHEST = 9,
    POOL_BEGGAR = 10,
    POOL_DEMON_BEGGAR = 11,
    POOL_CURSE = 12,
    POOL_KEY_MASTER = 13,
    POOL_BATTERY_BUM = 14,
    POOL_MOMS_CHEST = 15,
    POOL_GREED_TREASURE = 16,
    POOL_GREED_BOSS = 17,
    POOL_GREED_SHOP = 18,
    POOL_GREED_DEVIL = 19,
    POOL_GREED_ANGEL = 20,
    POOL_GREED_CURSE = 21,
    POOL_GREED_SECRET = 22,
    POOL_CRANE_GAME = 23,
    POOL_ULTRA_SECRET = 24,
    POOL_BOMB_BUM = 25,
    POOL_PLANETARIUM = 26,
    POOL_OLD_CHEST = 27,
    POOL_BABY_SHOP = 28,
    POOL_WOODEN_CHEST = 29,
    POOL_ROTTEN_BEGGAR = 30,
    NUM_ITEMPOOLS = 31
};


	// For address "literals" in LibZHL, it's best to define them here to avoid clashing with the parser more than needed
	static void* wglSwapBuffersAddr = GetProcAddress(GetModuleHandleA("opengl32.dll"), "wglSwapBuffers");
extern LIBZHL_API float* __ptr_g_WIDTH;
#define g_WIDTH (*__ptr_g_WIDTH)
extern LIBZHL_API float* __ptr_g_HEIGHT;
#define g_HEIGHT (*__ptr_g_HEIGHT)
extern LIBZHL_API float* __ptr_g_PointScale;
#define g_PointScale (*__ptr_g_PointScale)
extern LIBZHL_API float* __ptr_g_DisplayPixelsPerPoint;
#define g_DisplayPixelsPerPoint (*__ptr_g_DisplayPixelsPerPoint)
extern LIBZHL_API BeamRenderer ** __ptr_g_BeamRenderer;
#define g_BeamRenderer (*__ptr_g_BeamRenderer)
extern LIBZHL_API double* __ptr_g_colorDouble;
#define g_colorDouble (*__ptr_g_colorDouble)
extern LIBZHL_API void ** __ptr_EntityRTTI;
#define EntityRTTI (*__ptr_EntityRTTI)
extern LIBZHL_API void ** __ptr_EntityFamiliarRTTI;
#define EntityFamiliarRTTI (*__ptr_EntityFamiliarRTTI)
extern LIBZHL_API void ** __ptr_EntityNPCRTTI;
#define EntityNPCRTTI (*__ptr_EntityNPCRTTI)
extern LIBZHL_API void ** __ptr_EntityPlayerRTTI;
#define EntityPlayerRTTI (*__ptr_EntityPlayerRTTI)
extern LIBZHL_API void ** __ptr_EntityProjectileRTTI;
#define EntityProjectileRTTI (*__ptr_EntityProjectileRTTI)
extern LIBZHL_API Game ** __ptr_g_Game;
#define g_Game (*__ptr_g_Game)
extern LIBZHL_API char ** __ptr_g_KAGEInputController;
#define g_KAGEInputController (*__ptr_g_KAGEInputController)
extern LIBZHL_API KAGE_Graphics_ImageBase_VertexAttributeDescriptor* __ptr_g_VertexAttributeDescriptor_Position;
#define g_VertexAttributeDescriptor_Position (*__ptr_g_VertexAttributeDescriptor_Position)
extern LIBZHL_API KAGE_Graphics_Manager* __ptr_g_KAGE_Graphics_Manager;
#define g_KAGE_Graphics_Manager (*__ptr_g_KAGE_Graphics_Manager)
extern LIBZHL_API float* __ptr_g_OrthographicWidth;
#define g_OrthographicWidth (*__ptr_g_OrthographicWidth)
extern LIBZHL_API float* __ptr_g_OrthographicHeight;
#define g_OrthographicHeight (*__ptr_g_OrthographicHeight)
extern LIBZHL_API KAGE_Graphics_Shader ** __ptr_g_CurrentShader;
#define g_CurrentShader (*__ptr_g_CurrentShader)
extern LIBZHL_API KAGE_Graphics_Shader ** __ptr_g_AllShaders;
#define g_AllShaders (*__ptr_g_AllShaders)
extern LIBZHL_API LuaEngine ** __ptr_g_LuaEngine;
#define g_LuaEngine (*__ptr_g_LuaEngine)
extern LIBZHL_API std_string* __ptr_g_SaveDataPath;
#define g_SaveDataPath (*__ptr_g_SaveDataPath)
extern LIBZHL_API bool* __ptr_g_isfullscreenrendering;
#define g_isfullscreenrendering (*__ptr_g_isfullscreenrendering)
extern LIBZHL_API unsigned int* __ptr_g_WindowSizeX;
#define g_WindowSizeX (*__ptr_g_WindowSizeX)
extern LIBZHL_API unsigned int* __ptr_g_WindowSizeY;
#define g_WindowSizeY (*__ptr_g_WindowSizeY)
extern LIBZHL_API Manager ** __ptr_g_Manager;
#define g_Manager (*__ptr_g_Manager)
extern LIBZHL_API MenuManager ** __ptr_g_MenuManager;
#define g_MenuManager (*__ptr_g_MenuManager)
extern LIBZHL_API ShapeRenderer ** __ptr_g_ShapeRenderer;
#define g_ShapeRenderer (*__ptr_g_ShapeRenderer)
struct ColorMod {
	float _tint[4]; // 0x0
	float _colorize[4]; // 0x10
	float _offset[3]; // 0x20
		ColorMod() : _tint{1.0f, 1.0f, 1.0f, 1.0f}, _colorize{0.0f, 0.0f, 0.0f, 0.0f}, _offset{0.0f, 0.0f, 0.0f} {}

}; // 0x2c

struct Vector {
	float x; // 0x0
	float y; // 0x4
	Vector() : x(0.f), y(0.f) {}
	Vector(float _x, float _y) : x(_x), y(_y) {}
	
	Vector operator+(const Vector& other)
	{
		return Vector(x + other.x, y + other.y);
	}
	
	Vector operator-(const Vector& other)
	{		
		return Vector(x - other.x, y - other.y);
	}
	
	Vector operator/(float amount)
	{		
		return Vector(x / amount, y / amount);
	}
	
	Vector operator*(float amount)
	{		
		return Vector(x * amount, y * amount);
	}
	
	Vector& operator*=(float amount)
	{
		x *= amount;
		y *= amount;
		return *this;
	}
}; // 0x8

struct AnimationFrame {
	Vector crop; // 0x0
	float width; // 0x8
	float height; // 0xc
	Vector pos; // 0x10
	Vector scale; // 0x18
	Vector pivot; // 0x20
	int duration; // 0x28
	bool visible; // 0x2c
	char pad0[0x3]; // 0x2d
	ColorMod color; // 0x30
	float rotation; // 0x5c
	bool interpolated; // 0x60
	char pad1[0x3]; // 0x61
	int startFrame; // 0x64
	int endFrame; // 0x68
}; // 0x6c

struct AnimationLayer {
	int _layerID; // 0x0
	AnimationFrame * _animFrames; // 0x4
	int _numFrames; // 0x8
	bool _visible; // 0xc
	char pad0[0x3]; // 0xd
	LIBZHL_API void RenderFrame(Vector const & position, int unk, Vector const & topLeftClamp, Vector const & BottomRightClamp, ANM2 * animation);
	inline int GetLayerID() { return this->_layerID; }
	// Number of unique frames. Not the total length of the animation.
	// Note that interpolated frames have been split into multiple frames.
	// Should only be used internally, for accessing the array of AnimationFrames.
	inline int GetFrameCount() { return this->_numFrames; }
	inline AnimationFrame* GetFrame(const int frame) {
		if (this->_animFrames != nullptr && frame >= 0 && frame < this->GetFrameCount()) {
			return &this->_animFrames[frame];
		}
		return nullptr;
	}
	inline bool IsVisible() { return this->_visible; }
}; // 0x10

struct AnimationData {
	std_string _name; // 0x0
	AnimationLayer * _animLayers; // 0x18
	int _layerCount; // 0x1c
	char _nullLayersPtr[4]; // 0x20
	char pad0[0x4]; // 0x24
	int _nullLayerCount; // 0x28
	char pad1[0x4]; // 0x2c
	int _length; // 0x30
	bool _loop; // 0x34
	char pad2[0x3]; // 0x35
	int _layerMap[64]; // 0x38
	char pad3[0x4]; // 0x138
	inline std_string GetName() { return this->_name; };
	inline int GetLayerCount() { return this->_layerCount; };
	// Returns the Nth layer, from the bottom to the top.
	inline AnimationLayer* GetLayerByOrder(const int layer) {
		if (this->_animLayers != nullptr && layer >= 0 && layer < this->GetLayerCount()) {
			return &this->_animLayers[layer];
		}
		return nullptr;
	}
	// Given a layer ID, returns where in the layer order it sits.
	// IE, the very bottom layer is the 0th layer regardless of its ID.
	inline int GetLayerOrder(const int layerID) {
		if (this->_layerMap != nullptr && layerID >= 0 && layerID < 64) {
			return this->_layerMap[layerID];
		}
		return -1;
	}
	// Returns the layer with the provided ID, regardless of layer ordering.
	inline AnimationLayer* GetLayerById(const int layerID) {
		return this->GetLayerByOrder(this->GetLayerOrder(layerID));
	}
	inline int GetLength() { return this->_length; };
	inline bool IsLoopingAnimation() { return this->_loop; };
}; // 0x13c

struct AnimationState {
	ANM2 * _animation; // 0x0
	AnimationData * _animData; // 0x4
	int * _layerFrames; // 0x8
	int * _nullLayerFrames; // 0xc
	float _animFrame; // 0x10
	bool _isPlaying; // 0x14
	char pad0[0x3]; // 0x15
	int _currentlyTriggeredEvents; // 0x18
	int _previouslyTriggeredEvents; // 0x1c
	LIBZHL_API NullFrame * GetNullFrame(char const * nullLayerName);
	LIBZHL_API NullFrame * GetNullFrame(int nullLayerID);
	LIBZHL_API bool IsEventTriggered(char const * eventName);
	LIBZHL_API bool WasEventTriggered(char const * eventName);
	LIBZHL_API int NextEventTrigger(char const * eventName);
	LIBZHL_API void AdvancePosition(int amount);
	LIBZHL_API void Rewind();
	LIBZHL_API void Reset(AnimationState * right);
	LIBZHL_API void Render(Vector const & position, Vector const & topLeftClamp, Vector const & bottomRightClamp);
    inline AnimationData* GetAnimationData() { return this->_animData; }
    inline void SetFrame(const float frame) { this->_animFrame = frame; }
    inline bool IsPlaying() { return this->_isPlaying; }
    inline void Play() {
        if (this->_animData != nullptr) {
            if (this->_animFrame < 0) {
                this->Rewind();
            }
            this->_isPlaying = true;
        }
    }
    inline void Stop() { if (this->_animData != nullptr) this->_isPlaying = false; }
}; // 0x20

struct KColor {
	float _red; // 0x0
	float _green; // 0x4
	float _blue; // 0x8
	float _alpha; // 0xc
}; // 0x10

struct BlendMode {
	unsigned int flag1; // 0x0
	unsigned int flag2; // 0x4
	unsigned int flag3; // 0x8
	unsigned int flag4; // 0xc
	LIBZHL_API void SetMode(unsigned int mode);
	inline unsigned int* GetFlag1() { return &this->flag1; }
	inline unsigned int* GetFlag2() { return &this->flag2; }
	inline unsigned int* GetFlag3() { return &this->flag3; }
	inline unsigned int* GetFlag4() { return &this->flag4; }
}; // 0x10

struct LayerData {
	unsigned int ID; // 0x0
	unsigned int spritesheetID; // 0x4
	std_string name; // 0x8
	std_string defaultSpriteSheetPath; // 0x20
}; // 0x38

struct LayerState {
	LayerData * _layerData; // 0x0
	ANM2 * _animation; // 0x4
	std_string _spriteSheetPath; // 0x8
	unsigned int _minFilterMode; // 0x20
	unsigned int _magFilterMode; // 0x24
	unsigned int _wrapSMode; // 0x28
	unsigned int _wrapTMode; // 0x2c
	char pad0[0x4]; // 0x30
	Vector _size; // 0x34
	float _rotation; // 0x3c
	Vector _pos; // 0x40
	ColorMod _color; // 0x48
	bool _visible; // 0x74
	char pad1[0x3]; // 0x75
	BlendMode _blendMode; // 0x78
	unsigned int _bitflags; // 0x88
	Vector _cropOffset; // 0x8c
	KAGE_Graphics_ImageBase * _imageBasePtr; // 0x94
	void * _unkPtr; // 0x98
    inline int GetLayerID() { return this->_layerData->ID; }
    inline std_string GetName() { return this->_layerData->name; }
	inline std_string GetSpritesheetPath() { return this->_spriteSheetPath; }
    inline std_string GetDefaultSpritesheetPath() { return this->_layerData->defaultSpriteSheetPath; }
	inline Vector* GetSize() { return &this->_size; }
	inline float* GetRotation() { return &this->_rotation; }
	inline Vector* GetPos() { return &this->_pos; }
	inline ColorMod* GetColor() { return &this->_color; }
	inline bool* IsVisible() { return &this->_visible; }
	inline BlendMode* GetBlendMode() { return &this->_blendMode; }
	inline unsigned int* GetRenderFlags() { return &this->_bitflags; }
	inline Vector* GetCropOffset() { return &this->_cropOffset; } 
}; // 0x9c

struct ANM2 {
	std_string _filename; // 0x0
	std_string _animDefaultName; // 0x18
	AnimationState _animState; // 0x30
	AnimationState _overlayAnimState; // 0x50
	bool _overlayRenderFirst; // 0x70
	char pad0[0x3]; // 0x71
	AnimationData * _animData; // 0x74
	int _animCount; // 0x78
	LayerState * _layerState; // 0x7c
	unsigned int _layerCount; // 0x80
	std_string * _nullLayerNames; // 0x84
	unsigned int _numNullLayers; // 0x88
	std_string * _eventNames; // 0x8c
	unsigned int _numEvents; // 0x90
	Vector _offset; // 0x94
	Vector _scale; // 0x9c
	float _rotation; // 0xa4
	ColorMod _color; // 0xa8
	KColor _kColor; // 0xd4
	char pad1[0x1c]; // 0xe4
	bool _flipX; // 0x100
	bool _flipY; // 0x101
	char pad2[0x2]; // 0x102
	float _playbackSpeed; // 0x104
	char pad3[0x1]; // 0x108
	bool _loaded; // 0x109
	char pad4[0x6]; // 0x10a
	unsigned int _bitflags; // 0x110
	LIBZHL_API void Render(Vector * position, Vector * topleftclamp, Vector * bottomrightclamp);
	LIBZHL_API void Update();
	LIBZHL_API void SetLayerFrame(int layerid, int frame);
	LIBZHL_API void ReplaceSpritesheet(int LayerId, std_string & PngFilename);
	LIBZHL_API void LoadGraphics(bool unk);
	LIBZHL_API void Reset();
	LIBZHL_API LayerState * GetLayer(char const * layerName);
	LIBZHL_API LayerState * GetLayer(int layer);
	LIBZHL_API void RenderLayer(int param_1, Vector * param_2, Vector * param_3, Vector * param_4);
	LIBZHL_API bool IsPlaying(std_string * name);
	LIBZHL_API int GetFrame();
	LIBZHL_API int SetFrame(char const * anim, float frame);
	LIBZHL_API void Load(std_string & ANM2Path, bool loadgraphics);
	LIBZHL_API void Reload();
	LIBZHL_API bool SetAnimation(char const * anim, bool reset);
	LIBZHL_API bool SetOverlayAnimation(char const * anim, bool reset);
	LIBZHL_API void SetOverlayFrame(int frame);
	LIBZHL_API void SetOverlayFrame(char const * anim, int frame);
	LIBZHL_API void Play(char const * anim, bool reset);
	LIBZHL_API void Render_Wrapper(Vector * Position, Vector * topleftclamp, Vector * bottomrightclamp);
	LIBZHL_API void construct_from_copy(ANM2 * right);
	LIBZHL_API void destructor();
    inline AnimationState* GetAnimationState() { return &this->_animState; }
    inline AnimationState* GetOverlayAnimationState() { return &this->_overlayAnimState; }
    inline unsigned int GetAnimationCount() { return this->_animCount; }
    inline AnimationData* GetAnimationData(const int index) {
        if (this->_animData != nullptr && index >= 0 && index < this->_animCount) {
			return &this->_animData[index];
		}
		return nullptr;
    }
	inline NullFrame* GetNullFrame(const char * name) {return this->GetAnimationState()->GetNullFrame(name); }
	inline NullFrame* GetOverlayNullFrame(const char * name) {return this->GetOverlayAnimationState()->GetNullFrame(name); }
	inline unsigned int GetLayerCount() { return this->_layerCount; } 
    inline unsigned int* GetRenderFlags() { return &this->_bitflags; } 
	inline ColorMod* GetColor() { return &this->_color; } 
}; // 0x114

struct AchievementOverlay {
	char pad0[0x14]; // 0x0
	unsigned int displayedachievement; // 0x14
	unsigned int frame; // 0x18
	unsigned int status; // 0x1c
	ANM2 anm2; // 0x20
	char pad1[0x819c]; // 0x134
	LIBZHL_API void Update();
	inline ANM2* GetANM2() { return &anm2; }
}; // 0x82d0

struct AchievementOverlay_Entry {
	char pad0[0x34]; // 0x0
}; // 0x34

struct ActiveItemDesc {
	int _item; // 0x0
	int _charge; // 0x4
	int _batteryCharge; // 0x8
	int _subCharge; // 0xc
	int _timeRechargeCooldown; // 0x10
	int _partialCharge; // 0x14
	int _varData; // 0x18
}; // 0x1c

struct RNG {
	unsigned int _seed; // 0x0
	unsigned int _shift1; // 0x4
	unsigned int _shift2; // 0x8
	unsigned int _shift3; // 0xc
	LIBZHL_API void SetSeed(unsigned int Seed, unsigned int ShiftIdx);
	LIBZHL_API unsigned int RandomInt(unsigned int max);
	LIBZHL_API float RandomFloat();
	LIBZHL_API unsigned int Next();
	LIBZHL_API void game_constructor(unsigned int seed, unsigned int shiftidx);
}; // 0x10

struct Ambush {
	char pad0[0x18]; // 0x0
	int maxBossWaves; // 0x18
	int bossesPerWave; // 0x1c
	bool active; // 0x20
	char pad1[0x3]; // 0x21
	int currentWave; // 0x24
	char pad2[0x14]; // 0x28
	RNG rng; // 0x3c
	LIBZHL_API void StartChallenge();
	LIBZHL_API void SpawnBossrushWave();
	LIBZHL_API void SpawnWave();
	inline int* GetMaxBossrushWaves() {return (int*)((char*)this + 0x18); }
	inline int* GetNumBossesPerWave() {return (int*)((char*)this + 0x1C); }
	inline int* GetCurrentWave() {return (int*)((char*)this + 0x24); }
}; // 0x4c

struct ReferenceCounter_ImageBase {
	KAGE_Graphics_ImageBase * image; // 0x0
	KAGE_SmartPointer_ImageBase * counter; // 0x4
	LIBZHL_API ReferenceCounter_ImageBase & operator=(ReferenceCounter_ImageBase const & other);
	LIBZHL_API void DecrRef();
    ReferenceCounter_ImageBase() {
        image = nullptr;
        counter = nullptr;
    }
   
}; // 0x8

struct BackdropConfig {
	unsigned int backdropId; // 0x0
	std_string gfx; // 0x4
	std_string waterGfx; // 0x1c
	std_string lFloorGfx; // 0x34
	std_string nFloorGfx; // 0x4c
	unsigned int walls; // 0x64
	unsigned int wallVariants; // 0x68
	unsigned int floors; // 0x6c
	unsigned int floorVariants; // 0x70
	unsigned int unk1; // 0x74
	std_string props; // 0x78
	std_string rocks; // 0x90
	std_string pit; // 0xa8
	std_string waterPit; // 0xc0
	std_string bridge; // 0xd8
	std_string door; // 0xf0
	std_string holeInWall; // 0x108
	std_string spikes; // 0x120
	unsigned int waterPitsMode; // 0x138
}; // 0x13c

struct Backdrop {
	ReferenceCounter_ImageBase floorBuffer; // 0x0
	ReferenceCounter_ImageBase wallsBuffer; // 0x8
	char pad0[0x14]; // 0x10
	ReferenceCounter_ImageBase gfx; // 0x24
	ReferenceCounter_ImageBase waterGfx; // 0x2c
	ReferenceCounter_ImageBase nlfloorGfx; // 0x34
	char pad1[0x114]; // 0x3c
	unsigned int backdropId; // 0x150
	BackdropConfig configurations[61]; // 0x154
	char pad2[0x10]; // 0x4ca0
	RNG rng; // 0x4cb0
	LIBZHL_API void Init(unsigned int backdropId, bool LoadGraphics);
	LIBZHL_API void LoadConfig(char * xmlpath);
	LIBZHL_API void RenderWater(Vector const & offset);
	LIBZHL_API void RenderWalls(Vector const & renderOffset, ColorMod color);
	LIBZHL_API void RenderFloor(Vector const & renderOffset, ColorMod color);
	LIBZHL_API void pre_render_walls();
};

struct BeamRenderer {
	ANM2 _anm2; // 0x0
	unsigned int _layer; // 0x114
	bool _useOverlayData; // 0x118
	bool _unkBool; // 0x119
	char pad0[0x2]; // 0x11a
	vector_Point _points; // 0x11c
	LIBZHL_API static void __stdcall Begin(ANM2 * anm2, unsigned int layer, bool useOverlay, bool unk);
	LIBZHL_API static void __stdcall Add(Vector * point, ColorMod * color, float height, float width);
	LIBZHL_API static void __stdcall End();
		BeamRenderer(unsigned int layer, bool useOverlayData, bool unkBool) : _layer(layer), _useOverlayData(useOverlayData), _unkBool(unkBool) {}
	
		inline ANM2* GetANM2() { return &this->_anm2; }
		inline unsigned int* GetLayer() { return &this->_layer; }
		inline bool* GetUseOverlay() { return &this->_useOverlayData; }
		inline bool* GetUnkBool() { return &this->_unkBool; } 

}; // 0x128

struct BitSet128 {
	unsigned int ll; // 0x0
	unsigned int lh; // 0x4
	unsigned int hl; // 0x8
	unsigned int hh; // 0xc
	BitSet128() : ll(0), lh(0), hl(0), hh(0) {}
	BitSet128(unsigned int _ll, unsigned int _lh, unsigned int _hl, unsigned int _hh) : ll(_ll), lh(_lh), hl(_hl), hh(_hh) {}


}; // 0x10

struct BossPool {
	char pad0[0x8ac]; // 0x0
	LIBZHL_API int GetBossId(int leveltype, int levelvariant, RNG * rng);
}; // 0x8ac

struct EntityList_EL {
	bool _sublist; // 0x0
	char pad0[0x3]; // 0x1
	Entity * * _data; // 0x4
	unsigned int _capacity; // 0x8
	unsigned int _size; // 0xc
	LIBZHL_API void constructor(EntityList_EL * source);
	LIBZHL_API void Destroy();
	EntityList_EL(EntityList_EL *source) 
	{
		this->constructor(source);
	}
    
    EntityList_EL()
    {
    
    }
}; // 0x10

struct Entity {
	char pad0[0x20]; // 0x0
	unsigned int _index; // 0x20
	unsigned int _collisionIndex; // 0x24
	unsigned int _type; // 0x28
	unsigned int _variant; // 0x2c
	unsigned int _subtype; // 0x30
	char pad1[0x8]; // 0x34
	ANM2 _sprite; // 0x3c
	unsigned int _shadowSize; // 0x150
	char pad2[0xc]; // 0x154
	unsigned int _flags[2]; // 0x160
	bool _dead; // 0x168
	bool _visible; // 0x169
	char pad3[0x9e]; // 0x16a
	int _fireDamageCountdown; // 0x208
	int _damageCountdown; // 0x20c
	int _freezeCountdown; // 0x210
	int _poisonCountdown; // 0x214
	int _slowingCountdown; // 0x218
	int _charmedCountdown; // 0x21c
	int _confusionCountdown; // 0x220
	int _midasFreezeCountdown; // 0x224
	int _fearCountdown; // 0x228
	int _burnCountdown; // 0x22c
	int _bossStatusEffectCooldown; // 0x230
	int _shrinkCountdown; // 0x234
	int _poisonDamageTimer; // 0x238
	int _burnDamageTimer; // 0x23c
	int _bleedingCountdown; // 0x240
	char pad4[0x4]; // 0x244
	int _magnetizedCountdown; // 0x248
	int _baitedCountdown; // 0x24c
	int _knockbackCountdown; // 0x250
	int _weaknessCountdown; // 0x254
	int _iceCountdown; // 0x258
	int _brimstoneMarkCountdown; // 0x25c
	Vector _knockbackDirection; // 0x260
	char pad5[0x10]; // 0x268
	float _poisonDamage; // 0x278
	float _burnDamage; // 0x27c
	char pad6[0x30]; // 0x280
	float _depthOffset; // 0x2b0
	char pad7[0x2c]; // 0x2b4
	float _collisionDamage; // 0x2e0
	char pad8[0x10]; // 0x2e4
	float _speedMultiplier; // 0x2f4
	char pad9[0x14]; // 0x2f8
	float _shrinkStatus1; // 0x30c
	float _shrinkStatus2; // 0x310
	char pad10[0x4]; // 0x314
	Entity * _child; // 0x318
	char pad11[0x18]; // 0x31c
	RNG _dropRNG; // 0x334
	char pad12[0x1c]; // 0x344
	LIBZHL_API void constructor();
	LIBZHL_API void CopyStatusEffects();
	LIBZHL_API void AddBleeding(EntityRef const & ref, int duration);
	LIBZHL_API void AddShrink(EntityRef const & ref, int duration);
	LIBZHL_API void AddMagnetized(EntityRef const & ref, int duration);
	LIBZHL_API void AddBaited(EntityRef const & ref, int duration);
	LIBZHL_API void AddBrimstoneMark(EntityRef const & ref, int duration);
	LIBZHL_API void AddWeakness(EntityRef const & ref, int duration);
	LIBZHL_API void AddIce(EntityRef const & ref, int duration);
	LIBZHL_API void AddKnockback(EntityRef const & ref, Vector const & pushDirection, int duration, bool takeImpactDamage);
	LIBZHL_API unsigned int ComputeStatusEffectDuration(int initial, EntityRef * source);
	LIBZHL_API Vector GetNullOffset(char const * nullLayerName);
	LIBZHL_API Capsule GetNullCapsule(char const * nullLayerName);
	LIBZHL_API bool RenderShadowLayer(Vector * offset);
	LIBZHL_API static bool ForceCollide(Entity * boom, Entity * collider, bool low);
	LIBZHL_API Capsule GetCollisionCapsule(Vector * vec);
	LIBZHL_API unsigned int GetHitListIndex();
	LIBZHL_API static void __stdcall DoGroundImpactEffects(Vector * pos, Vector * velocity, float strength);
	LIBZHL_API void GetPredictedTargetPosition(Vector * buffer, Entity * target, float distanceStrength);
	LIBZHL_API bool IgnoreEffectFromFriendly(EntityRef * source);
	LIBZHL_API Entity_Effect * MakeBloodPoof(Vector * pos, ColorMod * color, float size);
	LIBZHL_API Entity_Effect * MakeGroundPoof(Vector * pos, ColorMod * color, float size);
	LIBZHL_API void TeleportToRandomPosition(bool unused);
	LIBZHL_API Entity_NPC * GiveMinecart(Vector * position, Vector * velocity);
	void virtual_unk0() { }
	LIBZHL_API void Init(unsigned int type, unsigned int variant, unsigned int subtype, unsigned int initSeed);
	LIBZHL_API void Original_Init(unsigned int type, unsigned int variant, unsigned int subtype, unsigned int initSeed);
	void virtual_unk1() { }
	LIBZHL_API void Update();
	LIBZHL_API void Original_Update();
	void virtual_unk2() { }
	void virtual_unk3() { }
	void virtual_unk4() { }
	void virtual_unk5() { }
	LIBZHL_API bool TakeDamage(float Damage, unsigned long long int DamageFlags, EntityRef * Source, int DamageCountdown);
	LIBZHL_API bool Original_TakeDamage(float Damage, unsigned long long int DamageFlags, EntityRef * Source, int DamageCountdown);
	void virtual_unk6() { }
	LIBZHL_API void Remove();
	LIBZHL_API void Original_Remove();
	void virtual_unk7() { }
	void virtual_unk8() { }
	void virtual_unk9() { }
	LIBZHL_API void SetColor(ColorMod * color, int Duration, int Priority, bool Fadeout, bool Shared);
	LIBZHL_API void Original_SetColor(ColorMod * color, int Duration, int Priority, bool Fadeout, bool Shared);
	void virtual_unk10() { }
	void virtual_unk11() { }
	void virtual_unk12() { }
	void virtual_unk13() { }
	void virtual_unk14() { }
	LIBZHL_API bool TryThrow(EntityRef const & Source, Vector * dir, float force);
	LIBZHL_API bool Original_TryThrow(EntityRef const & Source, Vector * dir, float force);
	void virtual_unk15() { }
	void virtual_unk16() { }
	void virtual_unk17() { }
	void virtual_unk18() { }
	inline int GetIndex() { return *(int*)((char*)this + 0x20); }
	inline unsigned int* GetType() { return (unsigned int*)((char*)this + 0x28); }
	inline unsigned int* GetVariant() { return (unsigned int*)((char*)this + 0x2c); }
	inline unsigned int* GetSubType() { return (unsigned int*)((char*)this + 0x30); }
	inline AnimationState* GetAnimationState() { return (AnimationState*)((char*)this + 0x6c); }
	inline bool IsAnimationExist() {
		int animSomething = *(int*)((char*)this + 0x70); //unknown type, so use int instead
		return animSomething != NULL;
	}
	inline AnimationState* GetOverlayAnimationState() { return (AnimationState*)((char*)this + 0x8c); }
	inline bool IsOverlayAnimationExist() {
		int overlayAnimSomething = *(int*)((char*)this + 0x90); //unknown type, so use int instead
		return overlayAnimSomething != NULL;
	}
	inline float* GetShadowSize() { return (float*)((char*)this + 0x150); }
	inline bool* GetVisible() { return (bool*)((char*)this + 0x169); }
	inline bool* IsDead() { return (bool*)((char*)this + 0x16b); }
	inline int* GetBossStatusEffectCooldown() { return (int*)((char*)this + 0x230); }
	inline int* GetPauseTime() { return (int*)((char*)this + 0x274); }
	inline Vector* GetPosition() { return (Vector*)((char*)this + 0x294); }
	inline bool* IsInvincible() { return (bool*)((char*)this + 0x308); }
	inline int* GetFireDamageCountdown() { return (int*)((char*)this + 0x208); }
	inline int* GetDamageCountdown() { return (int*)((char*)this + 0x20c); }

    template<typename T>
    inline T Downcast(void* target) {
        return (T)__RTDynamicCast(this, 0, (void*)__ptr_EntityRTTI, target, false); 
    }

    inline Entity_NPC* GetMinecart() { return *(Entity_NPC**)((char*)this + 0x32C); }
	
	inline LuaBridgeRef** GetLuaRef() { return (LuaBridgeRef**)((char*)this + 0x35C); }
	
    inline Entity_NPC* ToNPC() { return Downcast<Entity_NPC*>(__ptr_EntityNPCRTTI); } 
    inline Entity_Player* ToPlayer() { return Downcast<Entity_Player*>(__ptr_EntityPlayerRTTI); }
    inline Entity_Familiar* ToFamiliar() { return Downcast<Entity_Familiar*>(__ptr_EntityFamiliarRTTI); }
    inline Entity_Projectile* ToProjectile() { return Downcast<Entity_Projectile*>(__ptr_EntityProjectileRTTI); }
	
	Entity() 
	{
		this->constructor();
	}
}; // 0x360

struct EntityList {
	char pad0[0x580]; // 0x0
	LIBZHL_API void RenderShadows(Vector * offset);
	LIBZHL_API EntityList_EL * QueryType(EntityList_EL * result, int Type, int Variant, int Subtype, bool Cache, bool IgnoreFriendly);
	LIBZHL_API void QueryRadius(EntityList_EL * result, Vector * Position, float Radius, unsigned int Partitions);
	LIBZHL_API EntityList_EL * QueryCapsule(EntityList_EL * result, Capsule * Capsule, unsigned int Partitions);
    inline EntityList_EL* GetUpdateEL() { return (EntityList_EL*)((char*)this + 0x40); }
    inline EntityList_EL* GetTempEL() { return (EntityList_EL*)((char*)this + 0x70); }
	inline EntityList_EL* GetWispEL() { return (EntityList_EL*)((char*)this + 0x90); }
    inline EntityList_EL* GetPersistentEL() { return (EntityList_EL*)((char*)this + 0x30); }

	// This exists in the original source code as evidenced in the Switch decomp, but was inlined on PC.
	int CountWisps(unsigned int WispSubtype) {
	
		EntityList_EL* wisps = this->GetWispEL();
		unsigned int size = wisps->_size;
		unsigned int wispCount = 0;
		
		if (size) {
			Entity** data = wisps->_data;

			while (size) {
				Entity* wisp = *data;
				++data;
				if (wisp->_subtype == WispSubtype) // int WispSubtype
					wispCount++;
				--size;
			}
		}
		
		return wispCount;
	}
}; // 0x580

struct RoomConfig {
	int StageId; // 0x0
	int Mode; // 0x4
	int Type; // 0x8
	unsigned int Variant; // 0xc
	int Subtype; // 0x10
	std_string Name; // 0x14
	int Difficulty; // 0x2c
	float InitialWeight; // 0x30
	float Weight; // 0x34
	int Doors; // 0x38
	int unk7; // 0x3c
	RoomSpawn * Spawns; // 0x40
	unsigned short int SpawnCount; // 0x44
	char Width; // 0x46
	char Height; // 0x47
	int Shape; // 0x48
	int unk9; // 0x4c
	int unk10; // 0x50
	int unk11; // 0x54
	int unk12; // 0x58
	LIBZHL_API void LoadCurses(char * xmlpath, bool ismod);
	LIBZHL_API static unsigned int GetStageID(unsigned int LevelStage, unsigned int StageType, unsigned int Mode);
	LIBZHL_API void LoadStages(char * xmlpath);
	LIBZHL_API void DannyDeleto();
	LIBZHL_API void UnloadStage(int stageid);
	LIBZHL_API void LoadStageBinary(unsigned int Stage, unsigned int Mode);
    bool LIBZHL_API IsValidGridIndex(lua_Integer index, bool includeWalls = true) const;
   
}; // 0x5c

struct RoomDescriptor {
	int GridIndex; // 0x0
	int SafeGridIndex; // 0x4
	int ListIndex; // 0x8
	int unk0; // 0xc
	RoomConfig * Data; // 0x10
	RoomConfig * OverrideData; // 0x14
	int AllowedDoors; // 0x18
	int Doors[8]; // 0x1c
	int DisplayFlags; // 0x3c
	int VisitedCount; // 0x40
	int Flags; // 0x44
	short int unk9; // 0x48
	short int ClearCount; // 0x4a
	int unk10; // 0x4c
	int PoopCount; // 0x50
	int PitsCount; // 0x54
	int DecorationSeed; // 0x58
	int SpawnSeed; // 0x5c
	int AwardSeed; // 0x60
	char pad0[0x4]; // 0x64
	vector_GridEntityDesc SavedGridEntities; // 0x68
	vector_EntitySaveState SavedEntities; // 0x74
	std_set_int RestrictedGridIndexes; // 0x80
	vector_EntitySaveState SavedEntities2; // 0x88
	char pad1[0x18]; // 0x94
	short int ShopItemIdx; // 0xac
	short int ShopItemDiscountIdx; // 0xae
	int DeliriumDistance; // 0xb0
	int unk29; // 0xb4
}; // 0xb8

struct RailManager {
	Room * _room; // 0x0
	unsigned char _gridflags[447]; // 0x4
	char pad0[0x1]; // 0x1c3
	ANM2 _sprite; // 0x1c4
	
}; // 0x2d8

struct TemporaryEffects {
	char pad0[0x4]; // 0x0
	vector_TemporaryEffect _effects; // 0x4
	char pad1[0x4]; // 0x10
	int _disabled; // 0x14
	Entity_Player * _player; // 0x18
}; // 0x1c

struct Room {
	char pad0[0x4]; // 0x0
	RoomDescriptor * _descriptor; // 0x4
	unsigned int _roomType; // 0x8
	char pad1[0x18]; // 0xc
	GridEntity * _gridEntities[447]; // 0x24
	char pad2[0x4]; // 0x720
	GridEntity * _doors[8]; // 0x724
	unsigned int _doorGridPositions[8]; // 0x744
	char pad3[0xa88]; // 0x764
	int _roomClearDelay; // 0x11ec
	char pad4[0x8]; // 0x11f0
	Camera * _Camera; // 0x11f8
	char pad5[0x10]; // 0x11fc
	bool _redHeartDamage; // 0x120c
	char pad6[0xb]; // 0x120d
	EntityList _entityList; // 0x1218
	char pad7[0x5998]; // 0x1798
	int _greedWaveTimer; // 0x7130
	float _waterAmount; // 0x7134
	char pad8[0x4d]; // 0x7138
	bool _pacifist; // 0x7185
	char pad9[0x6e]; // 0x7186
	TemporaryEffects _temporaryEffects; // 0x71f4
	char pad10[0x13c]; // 0x7210
	RailManager _railManager; // 0x734c
	char pad11[0x158]; // 0x7624
	LIBZHL_API float GetDevilRoomChance();
	LIBZHL_API GridEntity * GetGridEntity(unsigned int idx);
	LIBZHL_API void ShopRestockFull();
	LIBZHL_API void ShopRestockPartial();
	LIBZHL_API int GetShopItemPrice(unsigned int entVariant, unsigned int entSubType, int shopItemID);
	LIBZHL_API bool SpawnGridEntity(int GridIndex, unsigned int Type, unsigned int Variant, unsigned int Seed, int VarData);
	LIBZHL_API bool SpawnGridEntityDesc(int GridIndex, GridEntityDesc * Desc);
	LIBZHL_API void RemoveGridEntityImmediate(int GridIndex, int PathTrail, bool KeepDecoration);
	LIBZHL_API void TriggerClear(bool playSound);
	LIBZHL_API bool CanSpawnObstacleAtPosition(int GridIndex, bool Force);
	LIBZHL_API float GetLightingAlpha();
	LIBZHL_API void PreRender();
	LIBZHL_API void RenderGridLight(GridEntity * grid, Vector & offset);
	LIBZHL_API void RenderEntityLight(Entity * ent, Vector & offset);
	LIBZHL_API bool CanPickupGridEntity(int GridIndex);
	LIBZHL_API bool PickupGridEntity(int GridIndex, GridEntityDesc * Desc, ANM2 * Sprite);
	LIBZHL_API Entity_Effect * PickupGridEntity(int GridIndex);
	LIBZHL_API int GetGridIndexByTile(int GridRow, int GridColumn);
	LIBZHL_API void Init(int param_1, RoomDescriptor * descriptor);
	LIBZHL_API void SetPauseTimer(int Duration);
	LIBZHL_API ColorModState ComputeColorModifier();
	LIBZHL_API int TryGetShopDiscount(int shopItemIdx, int price);
	LIBZHL_API bool IsPersistentRoomEntity(int type, int variant, int subtype);
	LIBZHL_API bool save_entity(Entity * entity, EntitySaveState * data, bool unk);
	LIBZHL_API void restore_entity(Entity * entity, EntitySaveState * data);
	inline Camera* GetCamera() { return *(Camera**)((char*)this + 0x11F8); }
	inline bool GetRedHeartDamage() { return *(bool*)((char*)this + 0x120C); }
	inline EntityList* GetEntityList() { return (EntityList*)((char*)this + 0x1218); }
	inline FXParams* GetFXParams() { return (FXParams*)((char*)this + 0x1c90); } // doing this the lazy way while FXLayers isn't exposed
	inline float* GetWaterAmount() { return &this->_waterAmount; }
	inline KColor* GetWaterColor() { return (KColor*)((char*)this + 0x7158 ); }
	inline KColor* GetWaterColorMultiplier() { return (KColor*)((char*)this + 0x7168 ); }
	
	// Initially, the base water color was erroneously defined as a Color and not a KColor occupying 0x7168. Color takes more bytes in memory.
	// Due to this, when setting the color, some arbitrary bytes ahead of the water color were being set.
	// While the true nature of these bytes aren't yet understood, the one at 0x7178 seems to control whether water color is rendered.
	inline int* GetUnknownWaterInt() { return (int*)((char*)this + 0x7178 ); }
	
	inline ColorMod* GetFloorColor() { return (ColorMod*)((char*)this + 0x7188 ); }
	inline TemporaryEffects* GetTemporaryEffects() {return (TemporaryEffects*)((char*)this + 0x71F4); }
    inline Backdrop* GetBackdrop() { return (Backdrop*)((char*)this + 0x1D34); }
	inline Vector* GetWaterCurrent() {return (Vector*)((char*)this + 0x7344); }
    inline RailType* GetRails() { return (RailType*)((char*)this + 0x7350); }
    inline RailType GetRailType(uint8_t gridIndex) { return GetRails()[gridIndex]; }
    inline void SetRailType(uint8_t gridIndex, RailType railType) { GetRails()[gridIndex] = railType; }
    static bool LIBZHL_API IsValidRailType(lua_Integer rail);
    inline bool IsValidGridIndex(lua_Integer index, bool includeWalls = true) const {
        return _descriptor->Data->IsValidGridIndex(index, includeWalls);
    }
    bool LIBZHL_API IsChampionBossSeed() const;
    float LIBZHL_API GetChampionBossChance() const;
}; // 0x777c

struct Camera {
	char pad0[0x94]; // 0x0
	LIBZHL_API void constructor(Room * room);
	LIBZHL_API void SetFocusPosition(Vector * pos);
	LIBZHL_API void DoUpdate(bool unk);
	LIBZHL_API void SnapToPosition(Vector const & pos);
	LIBZHL_API Vector * ClampedToRoom(Vector & pos);
	LIBZHL_API void UpdateDrag2();
	LIBZHL_API void UpdateUltrasmooth(bool unk);

	inline bool* ShouldOverride() { return (bool*)((char*)this + 0x8C); }
	
	Camera(Room* room)
	{
		this->constructor(room);
	}

}; // 0x94

struct Capsule {
	Vector _position; // 0x0
	Vector _vec2; // 0x8
	Vector _vec3; // 0x10
	Vector _direction; // 0x18
	float _unkFloat1; // 0x20
	float _unkFloat2; // 0x24
	LIBZHL_API void constructor(Vector * Position, Vector * Multiplier, float Rotation, float size);
	LIBZHL_API static bool Collide(Capsule * Cap1, Capsule * Cap2, Vector * retHitLocation);
	
	Capsule(Vector* pos, Vector* mult, float rot = 0.0f, float size = 0.0f) {
		this->constructor(pos, mult, rot, size);
	}
	
	inline Vector* GetPosition() { return &_position; }
	inline Vector* GetVec2() { return &_vec2; }
}; // 0x28

struct ChallengeParam {
	std_string _name; // 0x0
	std_set_int _roomset; // 0x18
	std_vector_int _collectibleList; // 0x20
	std_vector_int _trinketList; // 0x2c
	int _startingPill; // 0x38
	int _startingCard; // 0x3c
	int _endStage; // 0x40
	int _playerType; // 0x44
	std_vector_int _achievementList; // 0x48
	int _soulHearts; // 0x54
	int _blackHearts; // 0x58
	int _hearts; // 0x5c
	int _maxHearts; // 0x60
	int _coins; // 0x64
	float _addDamage; // 0x68
	bool _canShoot; // 0x6c
	bool _isAltPath; // 0x6d
	char pad0[0x2]; // 0x6e
	int _difficulty; // 0x70
	bool _isMegaSatan; // 0x74
	char pad1[0x3]; // 0x75
	float _minFireRate; // 0x78
	bool _maxDamage; // 0x7c
	bool _minShotSpeed; // 0x7d
	bool _bigRange; // 0x7e
	char pad2[0x1]; // 0x7f
	unsigned int _getCurse; // 0x80
	unsigned int _curseFilter; // 0x84
	bool _isSecretPath; // 0x88
	char pad3[0x3]; // 0x89
	std_vector_int _collectibleTwinList; // 0x8c
	char pad4[0xc]; // 0x98
}; // 0xa4

struct ColorModState {
	float r; // 0x0
	float g; // 0x4
	float b; // 0x8
	float a; // 0xc
	float brightness; // 0x10
	float contrast; // 0x14
	ColorModState() : r(1.0f), g(1.0f), b(1.0f), a(0.0f), brightness(0.0f), contrast(1.0f) {}
	ColorModState(float _r, float _g, float _b, float _a, float _brightness, float _contrast ) : r(_r), g(_g), b(_b), a(_a), brightness(_brightness), contrast(_contrast) {}

	ColorModState& operator=(ColorModState const& other) {
		r = other.r;
		g = other.g;
		b = other.b;
		a = other.a;
		brightness = other.brightness;
		contrast = other.contrast;
		return *this;
	}
	
	bool operator ==(ColorModState const& other) {
		return r == other.r && g == other.g && b == other.b && a == other.a && brightness == other.brightness && contrast == other.contrast;
	}	

	ColorModState& operator+=(ColorModState const& other) {
		r += other.r;
		g += other.g;
		b += other.b;
		a += other.a;
		brightness += other.brightness;
		contrast += other.contrast;
		return *this;
	}

	ColorModState operator+(ColorModState const& other) {
		return ColorModState(r + other.r, g + other.g, b + other.b, a + other.a, brightness + other.brightness, contrast + other.contrast);
	}
	
	ColorModState& operator-=(ColorModState const& other) {
		r -= other.r;
		g -= other.g;
		b -= other.b;
		a -= other.a;
		brightness -= other.brightness;
		contrast -= other.contrast;
		return *this;
	}

	ColorModState operator-(ColorModState const& other) {
		return ColorModState(r - other.r, g - other.g, b - other.b, a - other.a, brightness - other.brightness, contrast - other.contrast);
	}

	ColorModState& operator*=(float amount) {
		r *= amount;
		g *= amount;
		b *= amount;
		a *= amount;
		brightness *= amount;
		contrast *= amount;
		return *this;
	}
	
	ColorModState& operator*=(ColorModState const& other) {
		r *= other.r;
		g *= other.g;
		b *= other.b;
		a *= other.a;
		brightness *= other.brightness;
		contrast *= other.contrast;
		return *this;
	}	
	
	ColorModState operator*(float amount) {
		return ColorModState(r * amount, g * amount, b * amount, a * amount, brightness * amount, contrast * amount);
	}
	
	ColorModState operator*(ColorModState const& other) {
		return ColorModState(r * other.r, g * other.g, b * other.b, a * other.a, brightness * other.brightness, contrast * other.contrast);
	}
	
	ColorModState& operator/=(float amount) {
		r /= amount;
		g /= amount;
		b /= amount;
		a /= amount;
		brightness /= amount;
		contrast /= amount;
		return *this;
	}

	ColorModState operator/(float amount) {
		return ColorModState(r / amount, g / amount, b / amount, a / amount, brightness / amount, contrast / amount);
	}	

	inline float* GetR() { return &this->r; }
	inline float* GetG() { return &this->g; }
	inline float* GetB() { return &this->b; }
	inline float* GetA() { return &this->a; }
	inline float* GetBrightness() { return &this->brightness; }
	inline float* GetContrast() { return &this->contrast; }

};

struct CompletionWidget {
	int CharacterId; // 0x0
	ANM2 anm2; // 0x4
	char pad0[0x4]; // 0x118
	LIBZHL_API void Render(Vector * pos, Vector * scale);
	LIBZHL_API void Update();
	inline ANM2* GetANM2() { return &anm2; } 
}; // 0x11c

struct Console_HistoryEntry {
	std_string _text; // 0x0
	char pad0[0x10]; // 0x18
		inline int GetColorMap() {return *(int*)((char*)this + 0x1C); }

}; // 0x28

struct Console {
	char pad0[0x88]; // 0x0
	LIBZHL_API void PrintError(std_string const & err);
	LIBZHL_API void RunCommand(std_string & in, std_string * out, Entity_Player * player);
	LIBZHL_API void Print(std_string const & text, unsigned int color, unsigned int fadeTime);
	LIBZHL_API void FillOmnicomplete();
	LIBZHL_API void ProcessInput();
	LIBZHL_API void Render();
	LIBZHL_API std_deque_console_historyentry * RenderHistory(Font * font, float unk, float unk2, bool unk3);
	LIBZHL_API void SaveCommandHistory();
    inline int* GetState() { return (int*)((char*)this + 0x20); }
	
	inline std_deque_console_historyentry *GetHistory() { return (std_deque_console_historyentry*)((char*)this + 0x60); }
	inline deque_string *GetCommandHistory() { return (deque_string*)((char*)this + 0x74); }
	
	enum Color: unsigned int {WHITE = 0xFFD3D3D3};
}; // 0x88

struct ItemConfig_Costume {
	unsigned int id; // 0x0
	std_string anm2Path; // 0x4
	unsigned int priority; // 0x1c
	bool hasOverlay; // 0x20
	bool isFlying; // 0x21
	bool hasSkinAlt; // 0x22
	char pad0[0x1]; // 0x23
	unsigned int skinColor; // 0x24
	unsigned int overwriteColor; // 0x28
}; // 0x2c

struct ItemConfig_Item {
	int type; // 0x0
	int id; // 0x4
	std_string name; // 0x8
	std_string desc; // 0x20
	std_string gfxFilename; // 0x38
	int achievementId; // 0x50
	int cacheFlags; // 0x54
	int addMaxhearts; // 0x58
	int addHearts; // 0x5c
	int addSoulHearts; // 0x60
	int addBlackHearts; // 0x64
	int addBombs; // 0x68
	int addKeys; // 0x6c
	int addCoins; // 0x70
	unsigned int maxCharges; // 0x74
	unsigned int maxCooldown; // 0x78
	short int devilprice; // 0x7c
	short int shopPrice; // 0x7e
	ItemConfig_Costume costume; // 0x80
	unsigned int chargeType; // 0xac
	bool special; // 0xb0
	bool passiveCache; // 0xb1
	bool addCostumeOnPickup; // 0xb2
	bool hidden; // 0xb3
	bool persistentEffect; // 0xb4
	bool clearEffectsOnRemove; // 0xb5
	char pad0[0x2]; // 0xb6
	unsigned long long int tags; // 0xb8
	char pad1[0xc]; // 0xc0
	LIBZHL_API bool IsAvailableEx(unsigned int flags);
}; // 0xcc

struct CostumeSpriteDesc {
	ANM2 _sprite; // 0x0
	ItemConfig_Item * _item; // 0x114
	int _priority; // 0x118
	bool _itemAnimPlay; // 0x11c
	bool _isFlying; // 0x11d
	bool _hasOverlay; // 0x11e
	bool _hasSkinAlt; // 0x11f
	int _headColor; // 0x120
	int _bodyColor; // 0x124
	bool _overwriteColor; // 0x128
	bool _itemStateOnly; // 0x129
	char pad0[0x2]; // 0x12a
	int _playerType; // 0x12c
}; // 0x130

struct Cutscene {
	char pad0[0x7b0]; // 0x0
	LIBZHL_API void Init(char * xmlresourcespath);
	LIBZHL_API void Show(int cutsceneid);
}; // 0x7b0

struct DailyChallenge {
	unsigned int _id; // 0x0
	unsigned int _seed; // 0x4
	char pad0[0x8]; // 0x8
	ChallengeParam _params; // 0x10
	LIBZHL_API void Init(unsigned int dailyDate);
	inline ChallengeParam* GetChallengeParams() {return &_params; }
}; // 0xb4

struct DebugRenderer {
	LIBZHL_API Shape * Get(int Index, bool Unk);
};

struct DestinationQuad {
	Vector _topLeft; // 0x0
	Vector _topRight; // 0x8
	Vector _bottomLeft; // 0x10
	Vector _bottomRight; // 0x18
}; // 0x20

struct DrawStringEntry {
	char const * _text; // 0x0
	float _x; // 0x4
	float _y; // 0x8
	KColor _color; // 0xc
	int _boxWidth; // 0x1c
	bool _center; // 0x20
	char pad0[0x3]; // 0x21
}; // 0x24

struct DrawStringScaledEntry {
	char const * _text; // 0x0
	float _x; // 0x4
	float _y; // 0x8
	float _scaleX; // 0xc
	float _scaleY; // 0x10
	KColor _color; // 0x14
	int _boxWidth; // 0x24
	bool _center; // 0x28
	char pad0[0x3]; // 0x29
}; // 0x2c

struct EntityConfig_Player {
	int _id; // 0x0
	std_string _name; // 0x4
	std_string _skinPath; // 0x1c
	std_string _nameImagePath; // 0x34
	std_string _portraitPath; // 0x4c
	std_string _unkString; // 0x64
	std_string _extraPortraitPath; // 0x7c
	std_string _costumeSuffixName; // 0x94
	int _costumeID; // 0xac
	int _heart; // 0xb0
	int _armor; // 0xb4
	int _blackHeart; // 0xb8
	int _coins; // 0xbc
	int _bombs; // 0xc0
	int _keys; // 0xc4
	int _card; // 0xc8
	int _pill; // 0xcc
	bool _canShoot; // 0xd0
	char pad0[0x3]; // 0xd1
	std_vector_int _collectibles; // 0xd4
	int _trinket; // 0xe0
	int _skinColor; // 0xe4
	int _achievement; // 0xe8
	int _brokenHeart; // 0xec
	unsigned int _pocketActiveID; // 0xf0
	std_string _birthrightDescription; // 0xf4
	std_string _bSkinParentName; // 0x10c
	int _moddedTaintedPlayerID; // 0x124
	bool _hidden; // 0x128
	char pad1[0x3]; // 0x129
	ModEntry * _modEntry; // 0x12c
	char pad2[0x4]; // 0x130
	ANM2 * _moddedMenuBackgroundANM2; // 0x134
	ANM2 * _moddedMenuPortraitANM2; // 0x138
	ANM2 * _moddedGameOverANM2; // 0x13c
	ANM2 * _moddedCoopMenuANM2; // 0x140
	ANM2 * _moddedControlsANM2; // 0x144
	LIBZHL_API std_string GetDisplayName(void * ptr);
		inline int* GetAchievement() { return &this->_achievement; }
		inline ANM2** GetModdedMenuBackgroundANM2() { return (ANM2**)((char*)this + 0x134); }
		inline ANM2** GetModdedMenuPortraitANM2() { return (ANM2**)((char*)this + 0x138); }

}; // 0x148

struct EntityConfig_Boss {
	int bossID; // 0x0
	std_string name; // 0x4
	char pad0[0x48]; // 0x1c
}; // 0x64

struct ModEntry {
	LIBZHL_API void GetContentPath(char * * param_1, std_string * param_2);
	LIBZHL_API void WriteMetadata();
	inline std_string GetDir() { return *(std_string*)((char*)this + 0); }
	inline std_string GetName() { return *(std_string*)((char*)this + 0x18); }
	inline char* GetVersion() { return (char*)(this + 120); } //these last 2 are consistent
	inline char* GetId() { return (char*)(this + 144); } //these last 2 are consistent (this is the one I needed anyway)
	
	inline bool IsEnabled() { return *(bool*)((char*)this + 0xFC); }

	inline ANM2* GetDeathEnemiesAnm2() { return (ANM2*)((char*)this + 0xDF0); }
	
};

struct EntityConfig_Entity {
	int id; // 0x0
	int variant; // 0x4
	int subtype; // 0x8
	std_string name; // 0xc
	float shadowSize; // 0x24
	float collisionDamage; // 0x28
	bool isBoss; // 0x2c
	char pad0[0x3]; // 0x2d
	int bossID; // 0x30
	bool canBeChampion; // 0x34
	char pad1[0x3]; // 0x35
	float collisionRadius; // 0x38
	Vector collisionRadiusMulti; // 0x3c
	float mass; // 0x44
	unsigned int gridCollisionPoints; // 0x48
	float friction; // 0x4c
	float baseHP; // 0x50
	float stageHP; // 0x54
	bool shutDoors; // 0x58
	char pad2[0x3]; // 0x59
	unsigned int gibsAmount; // 0x5c
	unsigned int gibFlags; // 0x60
	int portrait; // 0x64
	char pad3[0xc]; // 0x68
	std_string anm2Path; // 0x74
	char pad4[0x28]; // 0x8c
	std_string gridCollisionClassString; // 0xb4
	bool reroll; // 0xcc
	bool hasFloorAlts; // 0xcd
	char pad5[0x2]; // 0xce
	unsigned int collisionInterval; // 0xd0
	char pad6[0x4]; // 0xd4
	unsigned int tags; // 0xd8
	char pad7[0x4]; // 0xdc
	float shieldStrength; // 0xe0
	char pad8[0x8]; // 0xe4
	Vector bestiaryOffset; // 0xec
	float bestiaryScale; // 0xf4
	std_string bestiaryAnm2Path; // 0xf8
	std_string bestiaryAnim; // 0x110
	std_string bestiaryOverlay; // 0x128
	std_string bestiaryFloorAlt; // 0x140
	char pad9[0x8]; // 0x158
	ModEntry * modEntry; // 0x160
	char pad10[0x34]; // 0x164
}; // 0x198

struct EntityConfig {
	char pad0[0x2c]; // 0x0
	LIBZHL_API void Load(char * xmlpath, ModEntry * param_2);
	LIBZHL_API void LoadPlayers(char * xmlpath, ModEntry * modentry);
	LIBZHL_API EntityConfig_Entity * GetEntity(int id, int variant, int subtype);
        inline std::vector<EntityConfig_Player>* GetPlayers() { return (std::vector<EntityConfig_Player>*)((char*)this + 0x8); }
        inline EntityConfig_Player* GetPlayer(const int ptype) {
            if (ptype < 0 || ptype >= (int)this->GetPlayers()->size()) {
		        return nullptr;
	        }
            return &this->GetPlayers()->at(ptype);
        }
        inline std::vector<EntityConfig_Boss>* GetBosses() { return (std::vector<EntityConfig_Boss>*)((char*)this + 0x20); }
   
}; // 0x2c

struct EntityRef {
	int _type; // 0x0
	int _variant; // 0x4
	int _spawnerType; // 0x8
	unsigned int _spawnerVariant; // 0xc
	Vector _position; // 0x10
	Vector _velocity; // 0x18
	unsigned int _flags; // 0x20
	Entity * _entity; // 0x24
}; // 0x28

struct EntitySaveState {
	int type; // 0x0
	int variant; // 0x4
	int subtype; // 0x8
	unsigned int intStorage1; // 0xc
	unsigned int intStorage2; // 0x10
	unsigned int intStorage3; // 0x14
	int intStorage4; // 0x18
	int intStorage5; // 0x1c
	short int gridSpawnIdx; // 0x20
	bool boolStorage1; // 0x22
	bool boolStorage2; // 0x23
	unsigned int intStorage6; // 0x24
	Vector targetPosition; // 0x28
	unsigned int _intStorage7; // 0x30
	unsigned int _initSeed; // 0x34
	unsigned int _dropSeed; // 0x38
	int spawnerType; // 0x3c
	int spawnerVariant; // 0x40
	float floatStorage1; // 0x44
	float floatStorage2; // 0x48
	unsigned int intStorage8; // 0x4c
	char byteStorage; // 0x50
	char pad0[0x17]; // 0x51
}; // 0x68

struct Entity_Bomb : public Entity {
	int _explosionCountdown1; // 0x360
	char pad0[0x8]; // 0x364
	float _height; // 0x36c
	float _fallingSpeed; // 0x370
	char pad1[0x10]; // 0x374
	float _scale; // 0x384
	char pad2[0x2b]; // 0x388
	bool _loadCostumes; // 0x3b3
	ANM2 _bombCostumesSprites[5]; // 0x3b4
	std_vector_uint _hitList; // 0x918
	char pad3[0x4]; // 0x924
	LIBZHL_API void Render(Vector * offset);
	LIBZHL_API bool HandleCollision(Entity * collider, bool low);
	LIBZHL_API void UpdateDirtColor();
	inline int* GetExplosionCountdown() { return &this->_explosionCountdown1; }
}; // 0x928

struct Entity_Effect : public Entity {
	char pad0[0x10]; // 0x360
	BitSet128 _varData; // 0x370
	char pad1[0x20]; // 0x380
	int _state; // 0x3a0
	char pad2[0x8]; // 0x3a4
	int _timeout; // 0x3ac
	int _lifespan; // 0x3b0
	char pad3[0x2c]; // 0x3b4
	LIBZHL_API void Render(Vector * offset);
	LIBZHL_API static Entity_Effect * CreateTimer(void * fn, unsigned int delay, unsigned int times, bool persistent);
	LIBZHL_API void Update();
	LIBZHL_API void Original_Update();
	void virtual_unk19() { }
	void virtual_unk20() { }
	void virtual_unk21() { }
	void virtual_unk22() { }
	void virtual_unk23() { }
	void virtual_unk24() { }
	void virtual_unk25() { }
	void virtual_unk26() { }
	void virtual_unk27() { }
	void virtual_unk28() { }
	void virtual_unk29() { }
	void virtual_unk30() { }
	void virtual_unk31() { }
	void virtual_unk32() { }
	void virtual_unk33() { }
	void virtual_unk34() { }
	void virtual_unk35() { }
	void virtual_unk36() { }
	void virtual_unk37() { }
	void virtual_unk38() { }
	void virtual_unk39() { }
	void virtual_unk40() { }
	void virtual_unk41() { }
	void virtual_unk42() { }
}; // 0x3e0

struct Entity_Familiar : public Entity {
	char pad0[0x974]; // 0x360
	int _state; // 0xcd4
	char pad1[0x150]; // 0xcd8
	ColorMod * _dirtColor; // 0xe28
	char pad2[0x44]; // 0xe2c
	LIBZHL_API int GetFollowerPriority();
	LIBZHL_API void Render(Vector * offset);
	LIBZHL_API bool HandleCollision(Entity * collider, bool low);
	LIBZHL_API void Shoot();
	LIBZHL_API bool TryAimAtMarkedTarget(Vector * AimDirection, int eDirection, Vector * Unk);
	LIBZHL_API void TriggerRoomClear();
	LIBZHL_API void UpdateDirtColor();
	LIBZHL_API Entity_Tear * FireProjectile(Vector const & AimDirection, bool Unk);
	LIBZHL_API Entity_Laser * FireBrimstone(Vector const & AimDirection, bool Unk);
	LIBZHL_API Entity_Laser * FireTechLaser(Vector const & AimDirection);
	LIBZHL_API bool CanBeDamagedByEnemy();
	LIBZHL_API bool CanBlockProjectiles();
	LIBZHL_API void Update();
	LIBZHL_API void Original_Update();
	void virtual_unk43() { }
	void virtual_unk44() { }
	void virtual_unk45() { }
	void virtual_unk46() { }
	void virtual_unk47() { }
	void virtual_unk48() { }
	void virtual_unk49() { }
	void virtual_unk50() { }
	void virtual_unk51() { }
	void virtual_unk52() { }
	void virtual_unk53() { }
	void virtual_unk54() { }
	void virtual_unk55() { }
	void virtual_unk56() { }
	void virtual_unk57() { }
	void virtual_unk58() { }
	void virtual_unk59() { }
	void virtual_unk60() { }
	void virtual_unk61() { }
	void virtual_unk62() { }
	void virtual_unk63() { }
	void virtual_unk64() { }
	void virtual_unk65() { }
	void virtual_unk66() { }
	inline Entity_Player** GetPlayer() { return (Entity_Player**)((char*)this + 0x360); }
	inline NPCAI_Pathfinder* GetPathFinder() {return (NPCAI_Pathfinder*)((char*)this + 0x54c); }
	inline Weapon** GetWeapon() { return (Weapon**)((char*)this + 0xcfc); }
}; // 0xe70

struct Entity_Knife : public Entity {
	char pad0[0xb10]; // 0x360
	LIBZHL_API void Render(Vector * offset);
	LIBZHL_API bool HandleCollision(Entity * collider, bool low);
	LIBZHL_API std_vector_uint * GetHitEntities();
}; // 0xe70

struct Entity_Laser : public Entity {
	char pad0[0x158]; // 0x360
	LIBZHL_API void ResetSpriteScale();
	LIBZHL_API void DoDamage(Entity * entity, float damage);
	LIBZHL_API bool CanDamageEntity(Entity * entity);
	LIBZHL_API void RotateToAngle(float angle, float speed);
	inline uint32_t* GetHomingType() { return (uint32_t*)((char*)this + 0x420); }
	inline float* GetScale() { return (float*)((char*)this + 0x430); }
	
	inline int* GetTimeout() { return (int*)((char*)this + 0x3a8); }
	inline bool* GetShrink() { return (bool*)((char*)this + 0x3ae); }
	inline bool* GetDisableFollowParent() { return (bool*)((char*)this + 0x434); }
	inline bool* GetOneHit() { return (bool*)((char*)this + 0x465); }
	inline std_vector_uint* GetHitList() { return (std_vector_uint*)((char*)this + 0x470); }
}; // 0x4b8

struct Entity_NPC : public Entity {
	int _stateFrame; // 0x360
	char pad0[0x750]; // 0x364
	int _state; // 0xab4
	char pad1[0x38]; // 0xab8
	int _projectileCooldown; // 0xaf0
	int _projectileDelay; // 0xaf4
	char pad2[0x8]; // 0xaf8
	Vector _v1; // 0xb00
	Vector _v2; // 0xb08
	int _i1; // 0xb10
	int _i2; // 0xb14
	char pad3[0x75]; // 0xb18
	bool _isBoss; // 0xb8d
	char pad4[0x322]; // 0xb8e
	LIBZHL_API void Morph(int EntityType, int Variant, int SubType, int Championid);
	LIBZHL_API void Render(Vector * offset);
	LIBZHL_API void UpdateDirtColor(bool unk);
	LIBZHL_API static bool Redirect(int * EntityType, int * Variant);
	LIBZHL_API bool TryForceTarget(Entity * Target, int Duration);
	LIBZHL_API bool HandleCollision(Entity * collider, bool low);
	LIBZHL_API void FireProjectiles(Vector * position, Vector * velocity, unsigned int mode, ProjectileParams * params);
	LIBZHL_API Entity_Projectile * FireBossProjectiles(int numProjectiles, Vector const & targetPos, float trajectoryModifier, ProjectileParams const & params);
	LIBZHL_API Entity_Projectile * FireGridEntity(ANM2 * anm2, GridEntityDesc * desc, Vector * velocity, unsigned int backdrop);
	LIBZHL_API void PlaySound(int id, float volume, int framedelay, bool loop, float pitch);
	LIBZHL_API Entity * GetPlayerTarget();
	LIBZHL_API bool CheckPlayerProximity(Vector * pos, float margin);
	LIBZHL_API void CreateBling();
	LIBZHL_API void CreateGoldParticles(unsigned int unused, unsigned int count);
	LIBZHL_API Entity_Effect * MakeBloodCloud(Vector * pos, ColorMod * color);
	LIBZHL_API void MakeBloodSplash();
	LIBZHL_API static Entity_NPC * ThrowMaggot(Vector * origin, Vector * velocity, float yOffset, float unk);
	LIBZHL_API static Entity_NPC * ThrowMaggotAtPos(Vector * pos, Vector * targetPos, float yOffset);
	LIBZHL_API static Entity_NPC * ShootMaggotProjectile(Vector * pos, Vector * dir, float velocity, float yOffset);
	LIBZHL_API static Entity_NPC * ThrowStrider(Vector * pos, Entity * spanwer, Vector * targetPos);
	LIBZHL_API static Entity_NPC * ThrowRockSpider(Vector * pos, Vector * targetPos, Entity * spanwer, int variant, float yPosOffset);
	LIBZHL_API static Entity_NPC * ThrowLeech(Vector * pos, Entity * spanwer, float yPosOffset, Vector * targetPos, bool big);
	LIBZHL_API bool TryThrow(EntityRef const & Source, Vector * pos, float unk);
	LIBZHL_API bool Original_TryThrow(EntityRef const & Source, Vector * pos, float unk);
	void virtual_unk67() { }
	void virtual_unk68() { }
	void virtual_unk69() { }
	void virtual_unk70() { }
	void virtual_unk71() { }
	void virtual_unk72() { }
	void virtual_unk73() { }
	void virtual_unk74() { }
	void virtual_unk75() { }
	void virtual_unk76() { }
	void virtual_unk77() { }
	void virtual_unk78() { }
	void virtual_unk79() { }
	void virtual_unk80() { }
	void virtual_unk81() { }
	void virtual_unk82() { }
	void virtual_unk83() { }
	void virtual_unk84() { }
	void virtual_unk85() { }
	void virtual_unk86() { }
	void virtual_unk87() { }
	void virtual_unk88() { }
	void virtual_unk89() { }
	void virtual_unk90() { }
	inline ColorMod* GetDirtColor() { return (ColorMod*)((char*)this + 0xBFC); }
    inline uint32_t* GetDeliriumBossType() { return (uint32_t*)((char*)this + 0xB18); }
    inline uint32_t* GetDeliriumBossVariant() { return (uint32_t*)((char*)this + 0xB1C); }
    inline uint16_t* GetDeliriumTransformationTimer() { return (uint16_t*)((char*)this + 0xB20); }
    inline uint8_t* GetDeliriumRemainingAttacks() { return (uint8_t*)((char*)this + 0xB22); }
    inline uint8_t* GetDeliriumState() { return (uint8_t*)((char*)this + 0xB23); }
    inline uint32_t* GetDeliriumAttackID() { return (uint32_t*)((char*)this + 0xB28); }
    inline uint8_t* GetDeliriumAttackAngle() { return (uint8_t*)((char*)this + 0xB2C); }
    inline uint32_t* GetDeliriumCycleID() { return (uint32_t*)((char*)this + 0xB30); }
	inline float* GetShieldStrength() { return (float*)((char*)this + 0xB90); }
	inline std_vector_uint GetHitList() { return *(std_vector_uint*)((char*)this + 0xE5C); }
	inline int32_t * GetControllerId() { return (int32_t *)((char*)this + 0xE6C); }
	inline void SetControllerId(int32_t  x) { *(int32_t *)((char*)this + 0xE6C) = x; }
}; // 0xeb0

struct Entity_Pickup : public Entity {
	ANM2 _priceANM2; // 0x360
	char pad0[0x78]; // 0x474
	unsigned int _cycleCollectibleList[8]; // 0x4ec
	unsigned int _cycleCollectibleCount; // 0x50c
	char pad1[0x128]; // 0x510
	LIBZHL_API void Morph(int EntityType, int Variant, int SubType, bool KeepPrice, bool KeepSeed, bool IgnoreModifiers);
	LIBZHL_API void TriggerShopPurchase(Entity_Player * player, int spentMoney);
	LIBZHL_API void Render(Vector * offset);
	LIBZHL_API void SetAlternatePedestal(int pedestalType);
	LIBZHL_API bool TryRemoveCollectible();
	LIBZHL_API void SetForceBlind(bool setBlind);
	LIBZHL_API int SetNewOptionsPickupIndex();
	LIBZHL_API bool HandleCollision(Entity * collider, bool low);
	LIBZHL_API bool TryInitOptionCycle(int numCycle);
	LIBZHL_API int GetCoinValue();
	LIBZHL_API bool CanReroll();
	LIBZHL_API void MakeShopItem(int shopId);
	LIBZHL_API bool TryFlip(Entity_Player * unusedPlayer, unsigned int unusedSeed);
	LIBZHL_API static Vector * GetRandomPickupVelocity(Vector const & buffer, Vector * position, RNG * rng, unsigned int ePickupVelType);
	LIBZHL_API int GetAlternatePedestal();
	LIBZHL_API void Remove();
	LIBZHL_API void Original_Remove();
	void virtual_unk91() { }
	void virtual_unk92() { }
	void virtual_unk93() { }
	void virtual_unk94() { }
	void virtual_unk95() { }
	void virtual_unk96() { }
	void virtual_unk97() { }
	void virtual_unk98() { }
	void virtual_unk99() { }
	void virtual_unk100() { }
	void virtual_unk101() { }
	void virtual_unk102() { }
	void virtual_unk103() { }
	void virtual_unk104() { }
	void virtual_unk105() { }
	void virtual_unk106() { }
	void virtual_unk107() { }
	void virtual_unk108() { }
	void virtual_unk109() { }
	void virtual_unk110() { }
	void virtual_unk111() { }
	void virtual_unk112() { }
	void virtual_unk113() { }
	void virtual_unk114() { }
	inline bool IsBlind() { return *(bool*)((char*)this + 0x47e); }
	inline int* GetDropDelay() { return (int*)((char*)this + 0x4a0); }
	inline int* GetVarData() { return (int*)((char*)this + 0x4e8); }
}; // 0x638

struct PlayerCostumeMap {
	int _index; // 0x0
	int _layerID; // 0x4
	int _priority; // 0x8
	bool _isBodyLayer; // 0xc
	char pad0[0x3]; // 0xd
}; // 0x10

struct Entity_Player : public Entity {
	char pad0[0xbe8]; // 0x360
	ANM2 _heldSprite; // 0xf48
	char pad1[0x114]; // 0x105c
	vector_CostumeSpriteDesc _costumeSpriteDescs; // 0x1170
	PlayerCostumeMap _playerCostumeMap[15]; // 0x117c
	char pad2[0x14c]; // 0x126c
	float _damage; // 0x13b8
	char pad3[0x50]; // 0x13bc
	ColorMod _laserColor; // 0x140c
	char pad4[0x30]; // 0x1438
	int _speedModifier; // 0x1468
	int _fireDelayModifier; // 0x146c
	int _damageModifier; // 0x1470
	int _tearRangeModifier; // 0x1474
	int _shotSpeedModifier; // 0x1478
	int _luckModifier; // 0x147c
	char pad5[0x38]; // 0x1480
	unsigned int _cacheFlags; // 0x14b8
	char pad6[0x1b4]; // 0x14bc
	vector_SmeltedTrinketDesc _smeltedTrinkets; // 0x1670
	char pad7[0x84]; // 0x167c
	int _playerForms[15]; // 0x1700
	char pad8[0x2c]; // 0x173c
	KColor _footprintColor1; // 0x1768
	char pad9[0x1c]; // 0x1778
	KColor _footprintColor2; // 0x1794
	char pad10[0x2c]; // 0x17a4
	unsigned int _deadEyeCharges; // 0x17d0
	unsigned int _deadEyeMisses; // 0x17d4
	char pad11[0x234]; // 0x17d8
	int _babySkin; // 0x1a0c
	char pad12[0x374]; // 0x1a10
	Entity_Player * _backupPlayer; // 0x1d84
	char pad13[0x70]; // 0x1d88
	int _maggySwingCooldown; // 0x1df8
	char pad14[0x48]; // 0x1dfc
	char _bagOfCraftingContent[8]; // 0x1e44
	char pad15[0x8]; // 0x1e4c
	char _poopSpellQueue[6]; // 0x1e54
	char pad16[0x1e]; // 0x1e5a
	int _eveSumptoriumCharge; // 0x1e78
	std_map_int_int _itemWispsList; // 0x1e7c
	char pad17[0x30]; // 0x1e84
	int _keepersSackBonus; // 0x1eb4
	char pad18[0xd0]; // 0x1eb8
	bool _isCoopGhost; // 0x1f88
	char pad19[0x5f7]; // 0x1f89
	LIBZHL_API void AddCollectible(int type, int charge, bool firsttime, int slot, int vardata);
	LIBZHL_API void AddBrokenHearts(int amount);
	LIBZHL_API void AddBombs(int amount);
	LIBZHL_API void AddKeys(int amount);
	LIBZHL_API void AddJarHearts(int amount);
	LIBZHL_API void AddJarFlies(int amount);
	LIBZHL_API void AddPrettyFly();
	LIBZHL_API void AddCoins(int amount);
	LIBZHL_API static PosVel GetMultiShotPositionVelocity(int loopIndex, WeaponType weaponType, Vector shotDirection, float shotSpeed, Weapon_MultiShotParams multiShotParams);
	LIBZHL_API Weapon_MultiShotParams * GetMultiShotParams(Weapon_MultiShotParams * params, int weaponType);
	LIBZHL_API Entity_Player * InitTwin(int playerType);
	LIBZHL_API Entity * ThrowHeldEntity(Vector * Velocity);
	LIBZHL_API void InitPostLevelInitStats();
	LIBZHL_API void TriggerRoomExit(bool unk);
	LIBZHL_API bool TriggerDeath(bool checkOnly);
	LIBZHL_API void Revive();
	LIBZHL_API void SetItemState(CollectibleType collectible);
	LIBZHL_API void UseCard(int cardType, unsigned int useFlag);
	LIBZHL_API void UsePill(int ePillEffect, int ePillColor, unsigned int useFlag);
	LIBZHL_API void Render(Vector * offset);
	LIBZHL_API int GetHealthType();
	LIBZHL_API void RenderHead(Vector * position);
	LIBZHL_API void RenderBody(Vector * position);
	LIBZHL_API void TriggerRoomClear();
	LIBZHL_API bool CanUseCollectible(CollectibleType collectible, int slot);
	LIBZHL_API bool HasCollectible(int type, bool ignoreModifiers);
	LIBZHL_API int GetCollectibleCount();
	LIBZHL_API void EvaluateItems();
	LIBZHL_API void CheckFamiliar(unsigned int FamiliarVariant, unsigned int TargetCount, RNG * rng, ItemConfig_Item * Item, int FamiliarSubType);
	LIBZHL_API void AddCacheFlags(int flags);
	LIBZHL_API int GetActiveItem(int slot);
	LIBZHL_API int GetActiveItemSlot(int id);
	LIBZHL_API int GetTotalActiveCharge(int slot);
	LIBZHL_API int GetActiveMaxCharge(int collectible, int vardata);
	LIBZHL_API int GetActiveMaxCharge(int slot);
	LIBZHL_API int GetActiveMinUsableCharge(int slot);
	LIBZHL_API void SetActiveVarData(int vardata, int slot);
	LIBZHL_API int AddActiveCharge(unsigned int charge, int slot, bool unk, bool overcharge, bool force);
	LIBZHL_API Entity_Pickup * DropCollectible(int collectible, Entity_Pickup * existingCollectible, bool removeFromPlayerForm);
	LIBZHL_API Entity_Pickup * DropCollectibleByHistoryIndex(int index, Entity_Pickup * existingCollectible);
	LIBZHL_API void AddHearts(int hearts, bool unk);
	LIBZHL_API int GetHealthLimit(bool keeper);
	LIBZHL_API void IncrementPlayerFormCounter(int ePlayerForm, int num);
	LIBZHL_API void TriggerNewRoom_TemporaryEffects();
	LIBZHL_API void TriggerNewStage(bool unk);
	LIBZHL_API bool TryPreventDeath();
	LIBZHL_API void RemoveCollectibleByHistoryIndex(int index, bool RemovedBool);
	LIBZHL_API void Teleport(Vector * position, bool doEffects, bool teleportTwinPlayers);
	LIBZHL_API bool TryFakeDeath();
	LIBZHL_API int GetCollectibleNum(int collectibleID, bool OnlyCountTrueItems);
	LIBZHL_API void TriggerCollectibleRemoved(unsigned int collectibleID);
	LIBZHL_API void TriggerTrinketAdded(unsigned int trinketID, bool firstTimePickingUp);
	LIBZHL_API void TriggerTrinketRemoved(unsigned int trinketID);
	LIBZHL_API int GetWeaponModifiers();
	LIBZHL_API void EnableWeaponType(WeaponType weaponType, bool Set);
	LIBZHL_API PocketItem * GetPocketItem(int SlotID);
	LIBZHL_API bool IsLocalPlayer();
	LIBZHL_API bool HandleCollision(Entity * collider, bool low);
	LIBZHL_API void InitPreLevelInitStats();
	LIBZHL_API void AddBlackHearts(unsigned int amount);
	LIBZHL_API void AddRottenHearts(unsigned int amount, bool unk);
	LIBZHL_API void AddGigaBombs(int amount);
	LIBZHL_API void ShuffleCostumes(int seed);
	LIBZHL_API void RemoveCollectible(unsigned int CollectibleType, bool IgnoreModifiers, unsigned int ActiveSlot, bool RemoveFromPlayerForm);
	LIBZHL_API void UpdateIsaacPregnancy(bool Cambion);
	LIBZHL_API int GetCambionPregnancyLevel();
	LIBZHL_API void CheckPoopSpellQueue();
	LIBZHL_API void AddCostume(ItemConfig_Item * collectibleID, bool itemStateOnly);
	LIBZHL_API void AddNullCostume(int costumeid);
	LIBZHL_API void ClearDeadEyeCharge();
	LIBZHL_API void SwapForgottenForm(bool unk1, bool unk2);
	LIBZHL_API TearParams * GetTearHitParams(TearParams * res, int WeaponType, float DamageScale, int TearDisplacement, Entity * Source);
	LIBZHL_API void PlayDelayedSFX(unsigned int soundEffectID, int soundDelay, int frameDelay, float volume);
	LIBZHL_API bool CanUsePill(int pillEffect);
	LIBZHL_API unsigned int InvalidateCoPlayerItems();
	LIBZHL_API bool TryRemoveSmeltedTrinket(unsigned int id);
	LIBZHL_API bool IsItemCostumeVisible(ItemConfig_Item * item, int playerSpriteLayerID);
	LIBZHL_API bool IsCollectibleCostumeVisible(CollectibleType collectible, int playerSpriteLayerID);
	LIBZHL_API bool IsNullItemCostumeVisible(int nullItemID, int playerSpriteLayerID);
	LIBZHL_API void PlayCollectibleAnim(CollectibleType collectible, bool checkBodyAnim, std_string & animName, int frameNum, bool unused);
	LIBZHL_API bool IsCollectibleAnimFinished(CollectibleType collectible, std_string & animName);
	LIBZHL_API void ClearCollectibleAnim(CollectibleType collectible);
	LIBZHL_API unsigned int GetMaxPocketItems();
	LIBZHL_API void AddPocketItem(unsigned int slot, unsigned int itemID);
	LIBZHL_API void AddBoneOrbital();
	LIBZHL_API unsigned int AddItemCard(unsigned int itemID);
	LIBZHL_API void AddLeprocy();
	LIBZHL_API void AddUrnSouls(unsigned int amount);
	LIBZHL_API bool CanAddCollectibleToInventory(int id);
	LIBZHL_API bool CanOverrideActiveItem(unsigned int slot);
	LIBZHL_API void ClearItemAnimCollectible(int id);
	LIBZHL_API void ClearItemAnimNullItems();
	LIBZHL_API Entity_Bomb * FireBomb(Vector * pos, Vector * vel, Entity * source);
	LIBZHL_API Entity_Knife * FireBoneClub(Entity * parent, unsigned int variant, bool unk, Weapon * weapon, float unk2);
	LIBZHL_API Entity_Effect * FireBrimstoneBall(Vector const & pos, Vector const & vel, Vector const & offset, unsigned int unk1, unsigned int unk2, Entity * unk3);
	LIBZHL_API Entity_Knife * FireKnife(Entity * parent, unsigned int variant, float rotationOffset, bool cantOverwrite, unsigned int subType);
	LIBZHL_API Entity_Laser * FireTechLaser(Vector const & pos, unsigned int offsetID, Vector const & dir, bool leftEye, bool oneHit, Entity * source, float damageScale);
	LIBZHL_API Entity_Laser * FireTechXLaser(Vector const & pos, Vector const & dir, float radius, Entity * source, float damageMultiplier);
	LIBZHL_API void GetBodyMoveDirection(Vector * buffer);
	LIBZHL_API char * GetDeathAnimName();
	LIBZHL_API unsigned int GetGlitchBabySubType();
	LIBZHL_API int GetGreedsGulletHearts();
	LIBZHL_API unsigned int GetSpecialGridCollision(Vector * pos);
	LIBZHL_API bool CanCrushRocks();
	LIBZHL_API void GetEnterPosition(Vector * buffer);
	LIBZHL_API Entity * GetFocusEntity();
	LIBZHL_API void GetGlyphOfBalanceDrop(int * variant, int * subtype);
	LIBZHL_API bool HasInstantDeathCurse();
	LIBZHL_API bool HasPoisonImmunity();
	LIBZHL_API bool IsEntityValidTarget(Entity * entity);
	LIBZHL_API bool IsInvisible();
	LIBZHL_API bool IsFootstepFrame(int eFoot);
	LIBZHL_API bool IsHeadless();
	LIBZHL_API bool IsHologram();
	LIBZHL_API void MorphToCoopGhost();
	LIBZHL_API void RemovePocketItem(int slot);
	LIBZHL_API void RerollAllCollectibles(RNG * rng, bool includeActives);
	LIBZHL_API void ResetPlayer();
	LIBZHL_API void RevivePlayerGhost();
	LIBZHL_API void SalvageCollectible(Vector * pos, int subtype, unsigned int seed, int poolType);
	LIBZHL_API void SetControllerIndex(unsigned int index);
	LIBZHL_API void SetFootprintColor(KColor * color, bool unk);
	LIBZHL_API void ShootBlueCandle(Vector * dir);
	LIBZHL_API void SpawnClot(Vector * pos, bool unk);
	LIBZHL_API unsigned int SpawnSaturnusTears();
	LIBZHL_API void SyncConsumableCounts(Entity_Player * player, int bitflags);
	LIBZHL_API void TryAddToBagOfCrafting(Entity_Pickup * pickup);
	LIBZHL_API void TryDecreaseGlowingHourglassUses(int unk1, bool unk2);
	LIBZHL_API bool TryForgottenThrow(Vector * dir);
	LIBZHL_API void UseRedKey();
	LIBZHL_API bool VoidHasCollectible(int id);
	LIBZHL_API RNG * GetCollectibleRNG(int id);
	LIBZHL_API void AttachMinecart(Entity_NPC * minecart);
	LIBZHL_API void Init(unsigned int type, unsigned int variant, unsigned int subtype, unsigned int initSeed);
	LIBZHL_API void Original_Init(unsigned int type, unsigned int variant, unsigned int subtype, unsigned int initSeed);
	LIBZHL_API void Update();
	LIBZHL_API void Original_Update();
	LIBZHL_API bool TakeDamage(float Damage, unsigned long long int DamageFlags, EntityRef * Source, int DamageCountdown);
	LIBZHL_API bool Original_TakeDamage(float Damage, unsigned long long int DamageFlags, EntityRef * Source, int DamageCountdown);
	LIBZHL_API bool TryThrow(EntityRef const & Source, Vector * pos, float unk);
	LIBZHL_API bool Original_TryThrow(EntityRef const & Source, Vector * pos, float unk);
	void virtual_unk115() { }
	void virtual_unk116() { }
	void virtual_unk117() { }
	void virtual_unk118() { }
	void virtual_unk119() { }
	void virtual_unk120() { }
	void virtual_unk121() { }
	void virtual_unk122() { }
	void virtual_unk123() { }
	void virtual_unk124() { }
	void virtual_unk125() { }
	void virtual_unk126() { }
	void virtual_unk127() { }
	void virtual_unk128() { }
	void virtual_unk129() { }
	void virtual_unk130() { }
	void virtual_unk131() { }
	void virtual_unk132() { }
	void virtual_unk133() { }
	void virtual_unk134() { }
	void virtual_unk135() { }
	inline RNG* GetDropRNG() {return (RNG*)((char*)this + 0x334); }
    inline int* GetMaxHearts() {return (int*)((char*)this + 0x1290); }
	inline int* GetRedHearts() {return (int*)((char*)this + 0x1294); }
	inline int* GetEternalHearts() {return (int*)((char*)this + 0x1298); }
	inline int* GetSoulHearts() {return (int*)((char*)this + 0x129C); }
	inline int* GetBlackHearts() {return (int*)((char*)this + 0x12A0); }
	inline int* GetMetronomeCollectibleID() { return (int*)((char*)this + 0x12d8); } 
	inline int GetPlayerType() { return *(int*)((char*)this + 0x130c); }
	inline int* GetPlayerTypeMutable() { return (int*)((char*)this + 0x130c); }
	inline Weapon** GetWeapon(int index) { return (Weapon**)((char*)this + index * 4 + 0x1328); }
	inline Entity_Effect* GetMarkedTarget() { return *(Entity_Effect**)((char*)this + 0x1354); }
	inline Entity** GetHeldEntity() { return (Entity**)((char*)this + 0x1358); }
	inline int* GetFireDelayModifier() { return &this->_fireDelayModifier; }
	inline int* GetDamageModifier() { return &this->_damageModifier; }
	inline float* GetEdenSpeed() { return (float*)((char*)this + 0x1490); }
	inline float* GetEdenFireDelay() { return (float*)((char*)this + 0x1494); }
	inline float* GetEdenDamage() { return (float*)((char*)this + 0x1498); }
	inline float* GetEdenRange() { return (float*)((char*)this + 0x149c); }
	inline float* GetEdenShotSpeed() { return (float*)((char*)this + 0x14a0); }
	inline float* GetEdenLuck() { return (float*)((char*)this + 0x14a4); }
	inline int* GetCanFly() { return (int*)((char*)this + 0x14b4); }
	inline std_vector_int GetCollectiblesList() { return *(std_vector_int*)((char*)this + 0x15f0); }
	inline vector_SmeltedTrinketDesc* GetSmeltedTrinket() { return &this->_smeltedTrinkets; }
	inline std_vector_int GetVoidedCollectiblesList() { return *(std_vector_int*)((char*)this + 0x167c); }
	inline int* GetPonyCharge() { return (int*)((char*)this + 0x17a8); } 
	inline int GetDeadEyeCharge() { return *(int*)((char*)this + 0x17D0); }
	inline int GetDeadEyeMisses() { return *(int*)((char*)this + 0x17D0); }
	inline bool* GetCanShoot() { return (bool*)((char*)this + 0x1745); }
	inline int* GetEpiphoraCharge() { return (int*)((char*)this + 0x17c4); }
	inline int* GetMegaBlastDuration() { return (int*)((char*)this + 0x1814); }
	inline int* GetPeeBurstCooldown() { return (int*)((char*)this + 0x1818); }
	inline int* GetMaxPeeBurstCooldown() { return (int*)((char*)this + 0x181c); }
	inline int* GetBladderCharge() { return (int*)((char*)this + 0x1820); }
	inline int* GetMaxBladderCharge() { return (int*)((char*)this + 0x1824); }
	inline bool* IsUrethraBlocked() { return (bool*)((char*)this + 0x1828); }
	inline int* GetNextUrethraBlockFrame() { return (int*)((char*)this + 0x182c); }
	inline int* GetPurityState() { return (int*)((char*)this + 0x184c); }
	inline int* GetImmaculateConceptionState() { return (int*)((char*)this + 0x1850); }
	inline int* GetCambionConceptionState() { return (int*)((char*)this + 0x1854); }
	inline float* GetD8DamageModifier() { return (float*)((char*)this + 0x185C); }
	inline float* GetD8SpeedModifier() { return (float*)((char*)this + 0x1860); }
	inline float* GetD8RangeModifier() { return (float*)((char*)this + 0x1864); }
	inline float* GetD8FireDelayModifier() { return (float*)((char*)this + 0x1868); }
	inline int* GetGoldenHearts() { return (int*)((char*)this + 0x186C); }
	inline int* GetBoneHearts() {return (int*)((char*)this + 0x1CA8); }
	inline int* GetBrokenHearts() {return (int*)((char*)this + 0x1CC0); }
	inline int* GetRottenHearts() {return (int*)((char*)this + 0x1CC4); }
	inline int* GetGigaBombs() {return (int*)((char*)this + 0x1CF4); }
	inline History* GetHistory() { return (History*)((char*)this + 0x1D0C); }
	inline float* GetTearPoisonDamage() { return (float*)((char*)this + 0x14c0); }
	inline ActiveItemDesc* GetActiveItemDesc(int index) { return (ActiveItemDesc*)((char*)this + index * 28 + 0x14c4); }
	inline ANM2* GetHeldSprite() { return &this->_heldSprite; }

    inline int* GetRedStewBonusDuration() { return (int*)((char*)this + 0x1d8c); }
    inline BagOfCraftingPickup* GetBagOfCraftingContent() { return (BagOfCraftingPickup*)((char*)this + 0x1e44); }
	inline std_map_int_int* GetItemWispsList() { return &this->_itemWispsList; }
    inline int* GetBagOfCraftingOutput() { return (int*)((char*)this + 0x1e4c); }
	inline uint8_t* GetWildCardItemType() { return (uint8_t*)((char*)this + 0x1f70); }
	inline int* GetWildCardItem() { return (int*)((char*)this + 0x1f74); }
	inline Entity_Player* GetBackupPlayer() { return *(Entity_Player**)((char*)this + 0x1d84); }
   
}; // 0x2580

struct Entity_Projectile : public Entity {
	char pad0[0x60]; // 0x360
	LIBZHL_API void Render(Vector * offset);
	LIBZHL_API bool HandleCollision(Entity * collider, bool low);
	LIBZHL_API void Reflect(Entity * unused, Vector * newVelocity);
}; // 0x3c0

struct Entity_Slot : public Entity {
	char pad0[0x130]; // 0x360
	LIBZHL_API void Render(Vector * offset);
	LIBZHL_API void CreateDropsFromExplosion();
	LIBZHL_API void SetPrizeCollectible(int CollectibleType);
	LIBZHL_API void Init(unsigned int Type, unsigned int Variant, unsigned int SubType, unsigned int Seed);
	LIBZHL_API void Original_Init(unsigned int Type, unsigned int Variant, unsigned int SubType, unsigned int Seed);
	LIBZHL_API void Update();
	LIBZHL_API void Original_Update();
	LIBZHL_API bool TakeDamage(float Damage, unsigned long long int DamageFlags, EntityRef * Source, int DamageCountdown);
	LIBZHL_API bool Original_TakeDamage(float Damage, unsigned long long int DamageFlags, EntityRef * Source, int DamageCountdown);
	void virtual_unk136() { }
	void virtual_unk137() { }
	void virtual_unk138() { }
	void virtual_unk139() { }
	void virtual_unk140() { }
	void virtual_unk141() { }
	void virtual_unk142() { }
	void virtual_unk143() { }
	void virtual_unk144() { }
	void virtual_unk145() { }
	void virtual_unk146() { }
	void virtual_unk147() { }
	void virtual_unk148() { }
	void virtual_unk149() { }
	void virtual_unk150() { }
	void virtual_unk151() { }
	void virtual_unk152() { }
	void virtual_unk153() { }
	void virtual_unk154() { }
	LIBZHL_API bool HandleCollision(Entity * Collider, bool Low);
	LIBZHL_API bool Original_HandleCollision(Entity * Collider, bool Low);
	void virtual_unk155() { }
	void virtual_unk156() { }
	inline RNG* GetSlotRNG() { return (RNG*)((char*)this + 0x334); }
	inline int* GetState() { return (int*)((char*)this + 0x360); }
	inline int* GetPrizeType() { return (int*)((char*)this + 0x364); }
	inline int* GetTimeout() { return (int*)((char*)this + 0x36a); }
	inline int* GetDonationValue() { return (int*)((char*)this + 0x36c); }
	inline unsigned short* GetTouch() { return (unsigned short*)((char*)this + 0x376); }
}; // 0x490

struct Entity_Tear : public Entity {
	char pad0[0x54]; // 0x360
	float _deadEyeIntensity; // 0x3b4
	char pad1[0x3c0]; // 0x3b8
	LIBZHL_API void Render(Vector * offset);
	LIBZHL_API bool HandleCollision(Entity * collider, bool low);
	LIBZHL_API Entity_Tear * MakeMultidimensionalCopy(Entity * spawner);
}; // 0x778

struct FXParams {
	ColorModState ColorModifier; // 0x0
	bool useWaterV2; // 0x18
	char pad0[0x3]; // 0x19
	KColor waterColor; // 0x1c
	KColor waterColorMultiplier; // 0x2c
	float shadowAlpha; // 0x3c
	KColor shadowColor; // 0x40
	KColor lightColor; // 0x50
	ColorMod waterEffectColor; // 0x60
	LIBZHL_API FXParams * Init();
	inline ColorModState* GetColorModifier() { return &this->ColorModifier; }
	inline bool* GetWaterV2() { return &this->useWaterV2; }
	inline KColor* GetWaterColor() { return &this->waterColor; }
	inline KColor* GetWaterColorMultiplier() { return &this->waterColorMultiplier; }
	inline float* GetShadowAlpha() { return &this->shadowAlpha; }
	inline KColor* GetShadowColor() { return &this->shadowColor; }
	inline KColor* GetLightColor() { return &this->lightColor; }
	inline ColorMod* GetWaterEffectColor() { return &this->waterEffectColor; }
}; // 0x8c

struct Font {
	char pad0[0x2003c]; // 0x0
	LIBZHL_API void DrawString(DrawStringEntry entry);
	LIBZHL_API void DrawStringUTF8(DrawStringEntry entry);
	LIBZHL_API void DrawStringScaled(DrawStringScaledEntry entry);
	LIBZHL_API void DrawStringScaledUTF8(DrawStringScaledEntry entry);
	LIBZHL_API int GetStringWidth(char const * str);
	LIBZHL_API int GetStringWidthUTF8(char const * str);
}; // 0x2003c

struct Seeds {
	bool _isCustomRun; // 0x0
	char pad0[0x3]; // 0x1
	unsigned int _gameStartSeed; // 0x4
	unsigned int _unkSeed; // 0x8
	char pad1[0xc]; // 0xc
	int _stageSeeds[14]; // 0x18
	unsigned int _playerInitSeed; // 0x50
	char pad2[0x4]; // 0x54
	int _seedEffectsCount; // 0x58
}; // 0x5c

struct GameState {
	char pad0[0x20294]; // 0x0
}; // 0x20294

struct PlayerManager {
	RNG _rng; // 0x0
	vector_EntityPlayerPtr _playerList; // 0x10
	char pad0[0x80]; // 0x1c
	Entity_Player * _esauJrState[4]; // 0x9c
	LIBZHL_API Entity_Player * SpawnCoPlayer(int unk);
	LIBZHL_API Entity_Player * SpawnCoPlayer2(int unk);
	LIBZHL_API Entity_Player * FirstCollectibleOwner(CollectibleType collectibleID, RNG * * rng, bool unk);
	LIBZHL_API bool IsCoopPlay();
	LIBZHL_API int GetNumCollectibles(CollectibleType type);
	LIBZHL_API Entity_Player * FirstTrinketOwner(TrinketType trinketType, RNG * * rng, bool unk);
	LIBZHL_API Entity_Player * FirstPlayerByType(unsigned int type);
	LIBZHL_API Entity_Player * FirstBirthrightOwner(unsigned int type);
	LIBZHL_API bool HasTemporaryEffect(ItemConfig_Item * item);
	LIBZHL_API int GetTrinketMultiplier(int TrinketID);
	LIBZHL_API Entity_Player * GetPlayer(int param1);
	LIBZHL_API void TriggerRoomClear();
	LIBZHL_API static bool __stdcall CoopBabiesOnly();
}; // 0xac

struct ItemOverlay {
	char pad0[0x4]; // 0x0
	int _overlayID; // 0x4
	ANM2 _sprite; // 0x8
	char pad1[0x1028]; // 0x11c
	int _delay; // 0x1144
	Entity_Player * _player; // 0x1148
	ANM2 _megaMushPlayerSprite; // 0x114c
	LIBZHL_API void Show(int eOverlayID, int delay, Entity_Player * player);
	LIBZHL_API void Update(bool unk);
	inline int* GetOverlayID() { return &_overlayID; } 
	inline ANM2* GetSprite() { return &_sprite; } 
	inline int* GetDelay() { return &_delay; } 
	inline Entity_Player* GetPlayer() { &_player; }
}; // 0x1260

struct ProceduralEffect_ActionData_UseActiveItem {
	int collectibleId; // 0x0
}; // 0x4

struct ProceduralEffect_ConditionData_EntitySpawn {
	char pad0[0x4]; // 0x0
	short int variant; // 0x4
	short int type; // 0x6
}; // 0x8

struct ProceduralEffect_ActionData_AddTemproryEffect {
	int collectibleId; // 0x0
}; // 0x4

struct ProceduralEffect_ActionData_SpawnEntity {
	short int variant; // 0x0
	short int type; // 0x2
}; // 0x4

struct ProceduralEffect_ActionData_ConvertEntities {
	short int fromVariant; // 0x0
	short int fromType; // 0x2
	short int toVariant; // 0x4
	short int toType; // 0x6
}; // 0x8

struct ProceduralEffect_ActionData_Fart {
	float fartScale; // 0x0
	char pad0[0x8]; // 0x4
	float radius; // 0xc
}; // 0x10

struct ProceduralEffect_ActionData_AreaDamage {
	char pad0[0x8]; // 0x0
	float radius; // 0x8
	float damage; // 0xc
	long long int flags1; // 0x10
	long long int flags2; // 0x18
}; // 0x20

struct ProceduralEffect {
	int effectConditionType; // 0x0
	int effectActionType; // 0x4
	char pad0[0x28]; // 0x8
	float triggerChance; // 0x30
	char pad1[0x2c]; // 0x34
    enum ConditionType{
        CONDITION_ACTIVE,
        CONDITION_TEAR_FIRE,
        CONDITION_ENEMY_HIT,
        CONDITION_ENEMY_KILL,
        CONDITION_DAMAGE_TAKEN,
        CONDITION_ROOM_CLEAR,
        CONDITION_ENTITY_SPAWN,
        CONDITION_PICKUP_COLLECTED,
        CONDITION_CHAIN,
    };

    enum ActionType{
        ACTION_USE_ACTIVE_ITEM,
        ACTION_ADD_TEMPRORY_EFFECT,
        ACTION_CONVERT_ENTITIES,
        ACTION_AREA_DAMAGE,
        ACTION_SPAWN_ENTITY,
        ACTION_FART,
    };

    union ConditionData{
        struct ProceduralEffect_ConditionData_EntitySpawn entitySpawn;
    };

    union ActionData{
        struct ProceduralEffect_ActionData_UseActiveItem useActiveItem;
        struct ProceduralEffect_ActionData_AddTemproryEffect addTempraryEffect;
        struct ProceduralEffect_ActionData_SpawnEntity spawnEntity;
        struct ProceduralEffect_ActionData_ConvertEntities convertEntities;
        struct ProceduralEffect_ActionData_AreaDamage areaDamage;
        struct ProceduralEffect_ActionData_Fart fart;
    };

    inline union ConditionData * GetConditionData(){
        return (union ConditionData*)((char*)this + 0x8);
    }
    inline union ActionData * GetActionData(){
        return (union ActionData*)((char*)this + 0x10);
    }
    
    // FIXME: ColorMod class
    // inline ColorMod* GetColor(){
    //     return (ColorMod*)((char *)this + 0x34);
    // }
}; // 0x60

struct ProceduralItem {
	ItemConfig_Item * item; // 0x0
	int _id; // 0x4
	char pad0[0x8]; // 0x8
	ItemConfig_Item * targetItem; // 0x10
	float damage; // 0x14
	float firedelay; // 0x18
	float speed; // 0x1c
	float range; // 0x20
	float shotspeed; // 0x24
	float luck; // 0x28
	char pad1[0xc]; // 0x2c
    inline std::vector<ProceduralEffect*>* GetEffects() { return (std::vector<ProceduralEffect*>*)((char*)this + 0x2c); }
}; // 0x38

struct ProceduralItemManager {
	char pad0[0x10]; // 0x0
	LIBZHL_API int CreateProceduralItem(unsigned int seed, unsigned int unk);
    inline std::vector<ProceduralItem*>* GetProceduralItems() { return (std::vector<ProceduralItem*>*)((char*)this + 0x0); }
}; // 0x10

struct Level {
	char pad0[0x1822c]; // 0x0
	unsigned int _levelStateFlag; // 0x1822c
	LIBZHL_API void SetStage(int stageid, int alt);
	LIBZHL_API void Init();
	LIBZHL_API void Update();
	LIBZHL_API void ChangeRoom(int targetRoomIDX, int dimension);
	LIBZHL_API bool TryInitializeExtraBossRoom(unsigned int seed);
	LIBZHL_API bool CanSpawnDoorOutline(int roomIDX, unsigned int doorSlot);
	LIBZHL_API bool HasAbandonedMineshaft();
	LIBZHL_API bool HasMirrorDimension();
	LIBZHL_API bool HasPhotoDoor();
	LIBZHL_API std_string GetName();
	LIBZHL_API void SetNextStage();
	LIBZHL_API static bool __stdcall IsStageAvailable(int LevelStage, int StageType);
	LIBZHL_API bool place_room(LevelGenerator_Room * slot, RoomConfig * data, unsigned int seed, unsigned int unk);
}; // 0x18230

struct RoomConfigs {
	unsigned int stageId; // 0x0
	std_string stageName; // 0x4
	std_string playerSpot; // 0x1c
	std_string bossSpot; // 0x34
	std_string suffix; // 0x4c
	std_string xmlFileName; // 0x64
	RoomConfig * configs; // 0x7c
	unsigned int nbRooms; // 0x80
	void * unk1; // 0x84
	unsigned int unk2; // 0x88
	unsigned char unk3; // 0x8c
	char pad0[0x3]; // 0x8d
	std_string greedModeXmlFileName; // 0x90
	char pad1[0x8]; // 0xa8
	void * unk6; // 0xb0
	char pad2[0x8]; // 0xb4
	unsigned int music; // 0xbc
	unsigned int backdrop; // 0xc0
}; // 0xc4

struct RoomConfigHolder {
	RoomConfigs configs[36]; // 0x0
	LIBZHL_API RoomConfig * GetRoomByStageTypeAndVariant(unsigned int stage, unsigned int type, unsigned int variant, int difficulty);
	LIBZHL_API RoomConfig * GetRandomRoom(unsigned int seed, bool reduceWeight, int stage, int roomType, int roomShape, unsigned int minVariant, int maxVariant, int minDifficulty, int maxDifficulty, unsigned int * requiredDoors, unsigned int roomSubtype, int mode);
	LIBZHL_API RoomConfigPtrVector GetRooms(int stage, int type, int shape, int minVariant, int maxVariant, int minDifficulty, int maxDifficulty, unsigned int * doors, unsigned int subtype, int mode);
}; // 0x1b90

struct RoomTransition {
	char pad0[0x344]; // 0x0
	LIBZHL_API void ChangeRoom();
	LIBZHL_API void StartBossIntro(unsigned int bossID1, unsigned int bossID2);
	inline int GetTransitionMode() { return *(int*)((char*)this); }
	inline ANM2* GetVersusScreenSprite() { return (ANM2*)((char*)this + 0x38); }
	inline bool IsRenderingBossIntro() {
		return GetTransitionMode() == 2;
	}
}; // 0x344

struct ScoreSheet {
	int _stageBonus; // 0x0
	int _schwagBonus; // 0x4
	int _blueBabyBonus; // 0x8
	int _lambBonus; // 0xc
	int _megaSatanBonus; // 0x10
	int _rushBonus; // 0x14
	int _explorationBonus; // 0x18
	int _damagePenalty; // 0x1c
	int _timePenalty; // 0x20
	int _itemPenalty; // 0x24
	int _totalScore; // 0x28
	int _runTimeLevel; // 0x2c
	int _runTimeLevelType; // 0x30
	unsigned int _runTime; // 0x34
	char pad0[0x8]; // 0x38
	int _runEnding; // 0x40
	char pad1[0x108]; // 0x44
	LIBZHL_API void Calculate();
		/*inline void AddFinishedStage(int stage, int stageType, uint32_t time) {
			if ((this->_runTimeLevel < stage) && g_Game->GetDailyChallenge()._id == 0) {
				this->_runTimeLevel = stage;
				this->_runTimeLevelStage = stageType;
				this->_runTime = time;
			}
			return;
		};
		*/

}; // 0x14c

struct ItemPool_Item {
	char pad0[0x4]; // 0x0
	vector_PoolItem _poolList; // 0x4
	RNG _rng1; // 0x10
	RNG _rng2; // 0x20
	int _bibleUpgrade; // 0x30
}; // 0x34

struct ItemPool {
	char pad0[0x4]; // 0x0
	ItemPool_Item _pools[31]; // 0x4
	char pad1[0x13c]; // 0x650
	vector_TrinketPoolItem _trinketPoolItems; // 0x78c
	int _numAvailableTrinkets; // 0x798
	int _pillEffects[15]; // 0x79c
	bool _idendifiedPillEffects[15]; // 0x7d8
	char pad2[0x41]; // 0x7e7
	LIBZHL_API static int __stdcall GetCardEx(int Seed, int SpecialChance, int RuneChance, int SuitChance, bool AllowNonCards);
	LIBZHL_API void load_pools(char * xmlpath, bool ismod);
	LIBZHL_API int GetCollectibleFromList(int const * list, unsigned int length, unsigned int seed, unsigned int defaultItem, bool addToBlacklist, bool excludeLockedItems);
	LIBZHL_API ItemPool_Item * GetPool(int itemPoolType);
		inline std::vector<bool>* GetRemovedCollectibles() { return (std::vector<bool>*)((char*)this + 0x67c); }
		inline std::vector<bool>* GetRoomBlacklistedCollectibles() { return (std::vector<bool>*)((char*)this + 0x68c); }

}; // 0x828

struct GameOver {
	char pad0[0x8]; // 0x0
	ANM2 anm2; // 0x8
	ANM2 exitSprite; // 0x11c
	ANM2 restartSprite; // 0x230
	char pad1[0x20040]; // 0x344
	ANM2 maybeControllerDisconnectPopup; // 0x20384
	EntityConfig_Entity * modEntityConfig; // 0x20498
	LIBZHL_API void Show();
}; // 0x2049c

struct Game {
	unsigned int _stage; // 0x0
	unsigned int _stageType; // 0x4
	bool _bossChallenge; // 0x8
	bool _devilRoomDisabled; // 0x9
	char pad0[0x2]; // 0xa
	unsigned int _curses; // 0xc
	char pad1[0x4]; // 0x10
	RoomDescriptor _gridRooms[507]; // 0x14
	RoomDescriptor _negativeGridRooms[18]; // 0x16c7c
	unsigned int _roomOffset[507]; // 0x1796c
	char pad2[0x4]; // 0x18158
	unsigned int _nbRooms; // 0x1815c
	unsigned int _startingRoomIdx; // 0x18160
	char pad3[0x2c]; // 0x18164
	Room * _room; // 0x18190
	unsigned int _currentRoomIdx; // 0x18194
	unsigned int _lastRoomIdx; // 0x18198
	unsigned int _currentDimensionIdx; // 0x1819c
	unsigned int _lastRoomDimensionIdx; // 0x181a0
	unsigned int _lastBossRoomListIdx; // 0x181a4
	unsigned int _leaveDoor; // 0x181a8
	unsigned int _enterDoor; // 0x181ac
	char pad4[0x14]; // 0x181b0
	unsigned int _greedModeWave; // 0x181c4
	char pad5[0x38]; // 0x181c8
	unsigned int _greedModeTreasureRoomIdx; // 0x18200
	char pad6[0x28]; // 0x18204
	unsigned int _stateFlags; // 0x1822c
	char pad7[0x56c]; // 0x18230
	RoomConfigHolder _roomConfigs; // 0x1879c
	char pad8[0x2a0]; // 0x1a32c
	ItemPool _itemPool; // 0x1a5cc
	char pad9[0xc4c]; // 0x1adf4
	PlayerManager _playerManager; // 0x1ba40
	char pad10[0x74]; // 0x1baec
	Console _console; // 0x1bb60
	char pad11[0xd8]; // 0x1bbe8
	ItemOverlay _itemOverlay; // 0x1bcc0
	char pad12[0x1861bc]; // 0x1cf20
	int _frameCount; // 0x1a30dc
	char pad13[0x20074]; // 0x1a30e0
	bool _triggerWindowResize; // 0x1c3154
	char pad14[0x23]; // 0x1c3155
	int _treasureRoomsVisited; // 0x1c3178
	int _planetariumsVisited; // 0x1c317c
	char pad15[0x20]; // 0x1c3180
	bool _isRerun; // 0x1c31a0
	bool _isDebug; // 0x1c31a1
	char pad16[0x16]; // 0x1c31a2
	Ambush _ambush; // 0x1c31b8
	char pad17[0xb4]; // 0x1c3204
	ScoreSheet _scoreSheet; // 0x1c32b8
	char pad18[0x80220]; // 0x1c3404
	unsigned int _difficulty; // 0x243624
	char pad19[0x40558]; // 0x243628
	bool _shouldLerpColorModState; // 0x283b80
	char pad20[0x93]; // 0x283b81
	vector_ErasedEntities _erasedEntities; // 0x283c14
	ProceduralItemManager _proceduralItemManager; // 0x283c20
	char pad21[0x1608]; // 0x283c30
	LIBZHL_API void constructor();
	LIBZHL_API bool IsPaused();
	LIBZHL_API static bool __stdcall IsHardMode();
	LIBZHL_API Entity * Spawn(unsigned int type, unsigned int variant, Vector const & position, Vector const & velocity, Entity * spawner, unsigned int subtype, unsigned int seed, unsigned int unk);
	LIBZHL_API void ShakeScreen(int timeout);
	LIBZHL_API void MakeShockwave(Vector const & pos, float amplitude, float speed, int duration);
	LIBZHL_API Entity_Player * GetPlayer(unsigned int Index);
	LIBZHL_API int GetNumPlayers();
	LIBZHL_API void Update();
	LIBZHL_API bool AchievementUnlocksDisallowed();
	LIBZHL_API bool PlaceRoom(LevelGenerator_Room * room, RoomConfig * data, unsigned int Seed, int dimension);
	LIBZHL_API void UpdateVisibility();
	LIBZHL_API unsigned int * GetRoomDescriptorsOffsetsArrayForDimension(unsigned int dimension);
	LIBZHL_API RoomDescriptor * GetRoomByIdx(unsigned int idx, int dimension);
	LIBZHL_API float GetPlanetariumChance();
	LIBZHL_API void StartStageTransition(bool SameStage, int param_2, Entity_Player * param_3);
	LIBZHL_API void Render();
	LIBZHL_API void ToggleDebugFlag(unsigned int flag);
	LIBZHL_API bool GetDebugFlag(unsigned int flag);
	LIBZHL_API Entity * SpawnBombCrater(Vector * Pos, float Scale);
	LIBZHL_API static void __stdcall DevolveEnemy(Entity * ent);
	LIBZHL_API void NetStart(void * unk, int challenge, Seeds seed, unsigned int difficulty, GameState * state);
	LIBZHL_API static void __stdcall ProcessInput();
	LIBZHL_API void Start(int playertype, int challenge, Seeds seeds, unsigned int difficulty);
	LIBZHL_API void SetColorModifier(ColorModState * color, bool lerp, float rate);
	LIBZHL_API ChallengeParam * GetChallengeParams();
	LIBZHL_API static bool __stdcall IsGreedBoss();
	LIBZHL_API static bool __stdcall IsGreedFinalBoss();
	LIBZHL_API bool IsGreedMode();
	Game()
	{
		this->constructor();
	}
    
    uint32_t GetNbRooms() const 
    { 
        return *(uint32_t*)((char*)this + 0x1815C); 
    }
    
	inline Console* GetConsole() { return (Console*)((char*)this + 0x1BB60); } // Cast to appropriate type
	
	inline ItemOverlay* GetItemOverlay() { return (ItemOverlay*)((char*)this + 0x1BCC0) ; }
	
	inline Ambush* GetAmbush() { return (Ambush*)((char*)this + 0x1c31b8); }
	
	inline Room** GetCurrentRoom() { return (Room**)((char*)this + 0x18190); }
		
	inline int GetCurrentRoomIdx() {return *(int*)((char*)this + 0x18194); }

    inline int GetDimension() {return *(int*)((char*)this + 0x1819C);}
	
	inline int GetLastBossRoomListIdx() {return *(int*)((char*)this + 0x181A4); }
	
	inline int GetGreedModeWave() { return *(int*)((char*)this + 0x181C4); }
	
	inline const unsigned int* GetLevelStateFlags() { return (const unsigned int*)((char*)this + 0x1822C); }
		
	inline RoomConfigHolder* GetRoomConfigHolder() { return (RoomConfigHolder*)((char*)this + 0x1879C); }
	
	inline RoomConfig* GetRoomConfig() { return (RoomConfig*)((char*)this + 0x1879C); }
	
	inline PlayerManager* GetPlayerManager() { return (PlayerManager*)((char*)this + 0x1BA40); }
	
	inline int GetLastDevilRoomStage() { return *(int*)((char*)this + 0x1C3174); }
	
	inline int GetLastLevelWithDamage() { return *(int*)((char*)this + 0x243628); }
	
	inline int GetLastLevelWithoutHalfHp() { return *(int*)((char*)this + 0x24361c); }

	inline int GetTreasureRoomsVisited() { return *(int*)((char*)this + 0x1C3178); }
	
	inline int GetPlanetariumsVisited() { return *(int*)((char*)this + 0x1C317C); }
	
	inline int IsPauseMenuOpen() { return (bool)*(int*)((char*)this + 0x10203C); } //in reality this gets the pause menu itself, but the first att is if its opened or not
	
	inline PauseScreen* GetPauseMenu() { return (PauseScreen*)((char*)this + 0x10203C); } 
	
	inline DailyChallenge GetDailyChallenge() { return *(DailyChallenge*)((char*)this + 0x1C3204); }
	
	inline unsigned int GetChallenge() { return *(unsigned int*)((char*)this + 0x1C319C); }
	
	inline bool* IsDebug() { return &this->_isDebug; }
	
	inline unsigned int* GetDebugFlags() { return (unsigned int*)((char*)this + 0X1C3164); }
	
	inline ScoreSheet* GetScoreSheet() { return (ScoreSheet*)((char*)this + 0x1c32b8); }
	
	inline int GetDifficulty() {return *(int*)((char*) this + 0x243624); }
	
	inline ProceduralItemManager* GetProceduralItemManager() {return (ProceduralItemManager*)((char*) this + 0x283c20); }
    
	inline HUD* GetHUD() { return (HUD*)((char*)this + 0x3DA4C); }

	inline PlayerHUD* GetPlayerHUD(uint32_t playerId) { return (PlayerHUD*)((char*)this + 0x3DA4C + playerId * 0x6B0); }
	
	inline Minimap* GetMinimap() { return (Minimap*)((char*)this + 0x1a2ab0); }
	
	inline RoomTransition* GetRoomTransition() { return (RoomTransition*)((char*)this + 0x1b6c0); }

    inline StageTransition* GetStageTransition() { return (StageTransition*)((char*)this + 0x1ba0c); }
	
	inline DebugRenderer* GetDebugRenderer() { return (DebugRenderer*)((char*)this + 0x283bf8); }

	inline GameOver* GetGameOver() { return (GameOver*)((char*)this + 0x1d154); }
	
	
	// Wack
	inline ColorModState* GetCurrentColorModifier() { return (ColorModState*)((char*)this + 0x283b84); }
	inline ColorModState* GetTargetColorModifier() { return (ColorModState*)((char*)this + 0x283b9c); }
	inline ColorModState* GetLerpColorModifier() { return (ColorModState*)((char*)this + 0x283bb4); }
	
    RoomDescriptor* GetRoomDescriptorsForDimension(uint32_t dimension) 
    { 
        return (RoomDescriptor*)((char*)this + 0x14 + dimension * sizeof(RoomDescriptor) * 169); 
    }

    bool LIBZHL_API IsErased(int type, int variant, int subtype);
}; // 0x285238

struct GenericPopup {
	char pad0[0x120]; // 0x0
}; // 0x120

struct GenericPrompt {
	char pad0[0x80218]; // 0x0
}; // 0x80218

struct GlobalPost {

};

struct GridEntityDesc {
	int _type; // 0x0
	int _variant; // 0x4
	int _state; // 0x8
	int _spawnCount; // 0xc
	unsigned int _spawnSeed; // 0x10
	int _varData; // 0x14
	bool _initialized; // 0x18
	char pad0[0x3]; // 0x19
	unsigned int _variableSeed; // 0x1c
}; // 0x20

struct GridEntity {
	char pad0[0x154]; // 0x0
	LIBZHL_API void Init(unsigned int Seed);
	LIBZHL_API void hurt_func(Entity * ent, int Damage, int DamageFlags, float unk3, bool unk4);
	LIBZHL_API void hurt_surroundings(int Damage, unsigned long long int DamageFlags, float unk3, bool unk4);
	LIBZHL_API Vector * GetRenderPosition(Vector * buffer);
	LIBZHL_API bool IsBreakableRock();
	void virtual_unk157() { }
	void virtual_unk158() { }
	void virtual_unk159() { }
	LIBZHL_API void Render(Vector & Offset);
	LIBZHL_API void Original_Render(Vector & Offset);
	void virtual_unk160() { }
	LIBZHL_API bool Destroy(bool Immediate);
	LIBZHL_API bool Original_Destroy(bool Immediate);
	void virtual_unk161() { }
	void virtual_unk162() { }
	void virtual_unk163() { }
	void virtual_unk164() { }
	void virtual_unk165() { }
	inline GridEntityDesc* GetDesc() {return (GridEntityDesc*)((char*)this + 0x4); }
	inline int GetType() {return *(int*)((char*)this + 0x4); }
	inline GridCollisionClass* GetCollisionClass() { return (GridCollisionClass*)((char*)this + 0x3C); }
	inline unsigned int* GetGridIndex() { return (unsigned int*)((char*)this + 0x24); }
}; // 0x154

struct GridEntity_Decoration : public GridEntity {
	LIBZHL_API void Render(Vector & Offset);
	LIBZHL_API void Original_Render(Vector & Offset);
	void virtual_unk166() { }
	void virtual_unk167() { }
	LIBZHL_API void Update();
	LIBZHL_API void Original_Update();
	void virtual_unk168() { }
	void virtual_unk169() { }
	void virtual_unk170() { }
	void virtual_unk171() { }
	void virtual_unk172() { }
	void virtual_unk173() { }
	void virtual_unk174() { }
}; // 0x154

struct GridEntity_Door : public GridEntity {
	char pad0[0x10]; // 0x154
	ANM2 _extraSprite; // 0x164
	char pad1[0x74]; // 0x278
	LIBZHL_API void Render(Vector & Offset);
	LIBZHL_API void Original_Render(Vector & Offset);
	void virtual_unk175() { }
	void virtual_unk176() { }
	LIBZHL_API void Update();
	LIBZHL_API void Original_Update();
	void virtual_unk177() { }
	void virtual_unk178() { }
	void virtual_unk179() { }
	void virtual_unk180() { }
	void virtual_unk181() { }
	void virtual_unk182() { }
	void virtual_unk183() { }
}; // 0x2ec

struct GridEntity_Fire : public GridEntity {
	LIBZHL_API void Render(Vector & Offset);
	LIBZHL_API void Original_Render(Vector & Offset);
	void virtual_unk184() { }
	void virtual_unk185() { }
	LIBZHL_API void Update();
	LIBZHL_API void Original_Update();
	void virtual_unk186() { }
	void virtual_unk187() { }
	void virtual_unk188() { }
	void virtual_unk189() { }
	void virtual_unk190() { }
	void virtual_unk191() { }
	void virtual_unk192() { }
}; // 0x154

struct GridEntity_Gravity : public GridEntity {
	void virtual_unk193() { }
	void virtual_unk194() { }
	LIBZHL_API void Update();
	LIBZHL_API void Original_Update();
	void virtual_unk195() { }
	void virtual_unk196() { }
	void virtual_unk197() { }
	void virtual_unk198() { }
	void virtual_unk199() { }
	void virtual_unk200() { }
	void virtual_unk201() { }
	void virtual_unk202() { }
}; // 0x154

struct GridEntity_Lock : public GridEntity {
	char pad0[0x4]; // 0x154
	LIBZHL_API void Render(Vector & Offset);
	LIBZHL_API void Original_Render(Vector & Offset);
	void virtual_unk203() { }
	void virtual_unk204() { }
	LIBZHL_API void Update();
	LIBZHL_API void Original_Update();
	void virtual_unk205() { }
	void virtual_unk206() { }
	void virtual_unk207() { }
	void virtual_unk208() { }
	void virtual_unk209() { }
	void virtual_unk210() { }
	void virtual_unk211() { }
}; // 0x158

struct GridEntity_Pit : public GridEntity {
	char pad0[0x4]; // 0x154
	LIBZHL_API void Render(Vector & Offset);
	LIBZHL_API void Original_Render(Vector & Offset);
	void virtual_unk212() { }
	void virtual_unk213() { }
	LIBZHL_API void Update();
	LIBZHL_API void Original_Update();
	void virtual_unk214() { }
	void virtual_unk215() { }
	void virtual_unk216() { }
	void virtual_unk217() { }
	void virtual_unk218() { }
	void virtual_unk219() { }
	void virtual_unk220() { }
}; // 0x158

struct GridEntity_Poop : public GridEntity {
	char pad0[0x20]; // 0x154
	LIBZHL_API void Render(Vector & Offset);
	LIBZHL_API void Original_Render(Vector & Offset);
	void virtual_unk221() { }
	void virtual_unk222() { }
	LIBZHL_API void Update();
	LIBZHL_API void Original_Update();
	void virtual_unk223() { }
	void virtual_unk224() { }
	void virtual_unk225() { }
	void virtual_unk226() { }
	void virtual_unk227() { }
	void virtual_unk228() { }
	void virtual_unk229() { }
}; // 0x174

struct GridEntity_PressurePlate : public GridEntity {
	char pad0[0x128]; // 0x154
	LIBZHL_API void Render(Vector & Offset);
	LIBZHL_API void Original_Render(Vector & Offset);
	void virtual_unk230() { }
	void virtual_unk231() { }
	LIBZHL_API void Update();
	LIBZHL_API void Original_Update();
	void virtual_unk232() { }
	void virtual_unk233() { }
	void virtual_unk234() { }
	void virtual_unk235() { }
	void virtual_unk236() { }
	void virtual_unk237() { }
	void virtual_unk238() { }
}; // 0x27c

struct GridEntity_Rock : public GridEntity {
	char pad0[0x44]; // 0x154
	LIBZHL_API static void SpawnDrops(Vector const & pos, int GridEntityType, int GridEntityVariant, unsigned int Seed, bool Unk, int BackdropType);
	LIBZHL_API void RenderTop(Vector const & pos);
	LIBZHL_API void TrySpawnWorms();
	LIBZHL_API void TrySpawnLadder();
	LIBZHL_API void UpdateNeighbors();
	LIBZHL_API static void PlayBreakSound(int GridEntityType, int BackdropType);
	LIBZHL_API static int GetAltRockType(int BackdropType);
	LIBZHL_API static void RegisterRockDestroyed(int GridEntityType);
	LIBZHL_API void update_collision();
	LIBZHL_API void Render(Vector & offset);
	LIBZHL_API void Original_Render(Vector & offset);
	LIBZHL_API bool Destroy(bool Immediate);
	LIBZHL_API bool Original_Destroy(bool Immediate);
	void virtual_unk239() { }
	void virtual_unk240() { }
	LIBZHL_API void Update();
	LIBZHL_API void Original_Update();
	void virtual_unk241() { }
	void virtual_unk242() { }
	void virtual_unk243() { }
	void virtual_unk244() { }
	void virtual_unk245() { }
	void virtual_unk246() { }
}; // 0x198

struct GridEntity_Spikes : public GridEntity {
	char pad0[0x4]; // 0x154
	void virtual_unk247() { }
	void virtual_unk248() { }
	LIBZHL_API void Update();
	LIBZHL_API void Original_Update();
	void virtual_unk249() { }
	void virtual_unk250() { }
	void virtual_unk251() { }
	void virtual_unk252() { }
	void virtual_unk253() { }
	void virtual_unk254() { }
	void virtual_unk255() { }
	void virtual_unk256() { }
}; // 0x158

struct GridEntity_Stairs : public GridEntity {
	void virtual_unk257() { }
	void virtual_unk258() { }
	LIBZHL_API void Update();
	LIBZHL_API void Original_Update();
	void virtual_unk259() { }
	void virtual_unk260() { }
	void virtual_unk261() { }
	void virtual_unk262() { }
	void virtual_unk263() { }
	void virtual_unk264() { }
	void virtual_unk265() { }
	void virtual_unk266() { }
}; // 0x154

struct GridEntity_Statue : public GridEntity {
	char pad0[0x4]; // 0x154
	void virtual_unk267() { }
	void virtual_unk268() { }
	LIBZHL_API void Update();
	LIBZHL_API void Original_Update();
	void virtual_unk269() { }
	void virtual_unk270() { }
	void virtual_unk271() { }
	void virtual_unk272() { }
	void virtual_unk273() { }
	void virtual_unk274() { }
	void virtual_unk275() { }
	void virtual_unk276() { }
}; // 0x158

struct GridEntity_TNT : public GridEntity {
	char pad0[0x4]; // 0x154
	void virtual_unk277() { }
	void virtual_unk278() { }
	LIBZHL_API void Update();
	LIBZHL_API void Original_Update();
	void virtual_unk279() { }
	void virtual_unk280() { }
	void virtual_unk281() { }
	void virtual_unk282() { }
	void virtual_unk283() { }
	void virtual_unk284() { }
	void virtual_unk285() { }
	void virtual_unk286() { }
}; // 0x158

struct GridEntity_Teleporter : public GridEntity {
	LIBZHL_API void Render(Vector & Offset);
	LIBZHL_API void Original_Render(Vector & Offset);
	void virtual_unk287() { }
	void virtual_unk288() { }
	LIBZHL_API void Update();
	LIBZHL_API void Original_Update();
	void virtual_unk289() { }
	void virtual_unk290() { }
	void virtual_unk291() { }
	void virtual_unk292() { }
	void virtual_unk293() { }
	void virtual_unk294() { }
	void virtual_unk295() { }
}; // 0x154

struct GridEntity_TrapDoor : public GridEntity {
	void virtual_unk296() { }
	void virtual_unk297() { }
	LIBZHL_API void Update();
	LIBZHL_API void Original_Update();
	void virtual_unk298() { }
	void virtual_unk299() { }
	void virtual_unk300() { }
	void virtual_unk301() { }
	void virtual_unk302() { }
	void virtual_unk303() { }
	void virtual_unk304() { }
	void virtual_unk305() { }
}; // 0x154

struct GridEntity_Wall : public GridEntity {
	LIBZHL_API void Render(Vector & Offset);
	LIBZHL_API void Original_Render(Vector & Offset);
	void virtual_unk306() { }
	void virtual_unk307() { }
	void virtual_unk308() { }
	void virtual_unk309() { }
	void virtual_unk310() { }
	void virtual_unk311() { }
	void virtual_unk312() { }
	void virtual_unk313() { }
	void virtual_unk314() { }
	void virtual_unk315() { }
}; // 0x154

struct GridEntity_Web : public GridEntity {
	void virtual_unk316() { }
	void virtual_unk317() { }
	LIBZHL_API void Update();
	LIBZHL_API void Original_Update();
	void virtual_unk318() { }
	void virtual_unk319() { }
	void virtual_unk320() { }
	void virtual_unk321() { }
	void virtual_unk322() { }
	void virtual_unk323() { }
	void virtual_unk324() { }
	void virtual_unk325() { }
}; // 0x154

struct PlayerHUDHeart {
	short int _visibility; // 0x0
	short int _goldenHeartVisibility; // 0x2
	int _flashType; // 0x4
	char const * _spriteAnim; // 0x8
	char const * _spriteOverlayAnim; // 0xc
}; // 0x10

struct PlayerHUD {
	Entity_Player * _player; // 0x0
	HUD * _HUD; // 0x4
	char pad0[0x8]; // 0x8
	PlayerHUDHeart _heart[24]; // 0x10
	char pad1[0x520]; // 0x190
	LIBZHL_API void Update();
	LIBZHL_API void RenderActiveItem(unsigned int slot, Vector const & pos, float alpha, float unk);
	LIBZHL_API void RenderHearts(Vector * unk1, ANM2 * sprite, Vector const & unk2, float unk3);
	LIBZHL_API void UpdateHearts(PlayerHUDHeart * heart, int unkInt, Entity_Player * player);
	LIBZHL_API void RenderTrinket(unsigned int TrinketSlot, Vector * pos, float scale);
	inline Entity_Player* GetPlayer() { return this->_player; }
}; // 0x6b0

struct HUD {
	PlayerHUD _playerHUD[8]; // 0x0
	char pad0[0xc1070]; // 0x3580
	LIBZHL_API void Render();
	LIBZHL_API void Update();
	LIBZHL_API void PostUpdate();
	LIBZHL_API void LoadGraphics();
	LIBZHL_API void FlashRedHearts(Entity_Player * player);
	LIBZHL_API void ShowItemText(char * param_1, char * param_2, bool iscurse, bool idk);
	//inline PlayerHUD GetPlayerHUD(int index) { return _playerHUD[index]; } 
	inline PlayerHUD* GetPlayerHUD(int index) { return (PlayerHUD*)((char*)this + index * 1712); }
	inline ANM2* GetChargeBarSprite() { return (ANM2*)((char*)this + 0xc36e8); }
	inline ANM2* GetPickupsHUDSprite() { return (ANM2*)((char*)this + 0xc3910); }
}; // 0xc45f0

struct History {
	std_vector_history_historyitem _historyItems; // 0x0
	char pad0[0x24]; // 0xc
	LIBZHL_API bool RemoveHistoryItemByIndex(int index);
	LIBZHL_API void AddHistoryItem(History_HistoryItem * historyItem);
}; // 0x30

struct History_HistoryItem {
	int _time; // 0x0
	bool _isTrinket; // 0x4
	char pad0[0x3]; // 0x5
	int _itemID; // 0x8
	int _levelStage; // 0xc
	int _stageType; // 0x10
	int _roomType; // 0x14
	int _itemPoolType; // 0x18
	
	History_HistoryItem(TrinketType itemID, int levelStage, int stageType, int roomType, int itemPoolType, int time = -1)
	{
		_itemID = itemID;
		_levelStage = levelStage;
		_stageType = stageType;
		_roomType = roomType;
		_isTrinket = true;
		_time = time;
		_itemPoolType = itemPoolType;
		
		if (time < 0) {
			_time = g_Game->_frameCount;
		}
	}
}; // 0x1c

struct Isaac {
	LIBZHL_API static GridEntity * __fastcall CreateGridEntity(int Type, unsigned int Index);
	LIBZHL_API static int __fastcall Random(int Max);
	LIBZHL_API static char const * __stdcall GetString(StringTable * table, char const * key);
	LIBZHL_API static void * __cdecl GetRoomEntities(void * unk);
	LIBZHL_API static void __cdecl SetBuiltInCallbackState(int callbackid, bool enabled);
	LIBZHL_API static void __cdecl free(void * block);
	LIBZHL_API static void * __cdecl operator_new(unsigned int size);
	LIBZHL_API static Weapon * CreateWeapon(WeaponType type, Entity * ent);
	LIBZHL_API static void DestoryWeapon(Weapon * * wep);
	LIBZHL_API static void SpawnLocust(Entity_Player * player, int collectibleType, Vector * pos);
	LIBZHL_API static unsigned int __stdcall genrand_int32();
	LIBZHL_API static Vector  RandomUnitVector(unsigned int seed);
	LIBZHL_API static void __cdecl Shutdown();
	LIBZHL_API static Vector  GetRenderPosition(Vector * source, bool scale);
	LIBZHL_API static void __stdcall ClearBossHazards(bool includeNPCs);
	LIBZHL_API static void __fastcall GetRandomPickupVelocity(Vector * buffer, Vector * position, unsigned int ePickupVelType, RNG * rng);
	LIBZHL_API static Vector  GetCollectibleSpawnPosition(Vector * target);
    LIBZHL_API static bool IsInGame();
   
}; // 0x0

struct ItemConfig_Pill {
	int id; // 0x0
	int achievementId; // 0x4
	std_string name; // 0x8
	std_string desc; // 0x20
	bool greedModeAllowed; // 0x38
	char pad0[0x3]; // 0x39
	unsigned int announcerVoice; // 0x3c
	unsigned int announcerVoiceSuper; // 0x40
	unsigned int announcerVoiceDelay; // 0x44
	unsigned int mimicCharge; // 0x48
	unsigned char effectClass; // 0x4c
	unsigned char effectSubClass; // 0x4d
	char pad1[0x2]; // 0x4e
}; // 0x50

struct ItemConfig_PlayerForm {
	int id; // 0x0
	char pad0[0x4]; // 0x4
	unsigned long long int tags; // 0x8
	std_string name; // 0x10
	int costume; // 0x28
	unsigned int cache; // 0x2c
}; // 0x30

struct ItemConfig_Card {
	int id; // 0x0
	int achievementId; // 0x4
	std_string name; // 0x8
	std_string desc; // 0x20
	std_string hudAnim; // 0x38
	bool greedModeAllowed; // 0x50
	char pad0[0x3]; // 0x51
	unsigned int pickupSubtype; // 0x54
	unsigned int cardType; // 0x58
	unsigned int announcerVoice; // 0x5c
	unsigned int announcerDelay; // 0x60
	unsigned int mimicCharge; // 0x64
}; // 0x68

struct ItemConfig {
	char pad0[0x50]; // 0x0
	LIBZHL_API ItemConfig_Item * GetCollectible(int id);
	LIBZHL_API void LoadCostumes(char * xmlpath, ModEntry * modentry);
	LIBZHL_API void LoadMetadata(char * xmlpath, ModEntry * modentry);
	LIBZHL_API void LoadWispConfig(char * xmlpath, ModEntry * modentry);
	LIBZHL_API void LoadLocustConfig(char * xmlpath, ModEntry * modentry);
	LIBZHL_API void LoadCraftingRecipes(char * xmlpath, ModEntry * modentry);
	LIBZHL_API void LoadBombConfigRules(char * xmlpath, bool ismod);
	LIBZHL_API void LoadPocketItems(char * xmlpath, ModEntry * modentry);
	LIBZHL_API void Load(char * xmlpath, ModEntry * modentry);
	LIBZHL_API ItemConfig_Item * GetTrinket(unsigned int TrinketType);
	LIBZHL_API vector_ItemPtr & GetTaggedItems(unsigned int tags);
		inline std::vector<ItemConfig_Item*>* GetCollectibles() { return (std::vector<ItemConfig_Item*>*)((char*)this + 0x00); }
		inline std::vector<ItemConfig_Item*>* GetTrinkets() { return (std::vector<ItemConfig_Item*>*)((char*)this + 0x0C); }
		inline std::vector<ItemConfig_Item*>* GetNullItems() { return (std::vector<ItemConfig_Item*>*)((char*)this + 0x18); }
		inline std::vector<ItemConfig_Card*>* GetCards() { return (std::vector<ItemConfig_Card*>*)((char*)this + 0x24); }
		inline std::vector<ItemConfig_Pill*>* GetPillEffects() { return (std::vector<ItemConfig_Pill*>*)((char*)this + 0x30); }
		inline std::vector<ItemConfig_PlayerForm*>* GetPlayerForms() { return (std::vector<ItemConfig_PlayerForm*>*)((char*)this + 0x44); }

		inline ItemConfig_Item* GetNullItem(const unsigned int id) {
			const auto* nullItems = this->GetNullItems();
			if (id < nullItems->size()) {
				return nullItems->at(id);
			}
			return nullptr;
		}
		
		static bool LIBZHL_API IsValidTrinket(unsigned int TrinketType);

}; // 0x50

struct KAGE {
	LIBZHL_API static void LogMessage(int flag, char const * string);
    LIBZHL_API static void _LogMessage(int flag, const char* fmt, ...);
   
}; // 0x0

struct KAGE_File {
	void * vtable; // 0x0
	char pad0[0x4]; // 0x4
	FILE * f; // 0x8
	char pad1[0x4]; // 0xc
	LIBZHL_API bool OpenFileRB(char const * name);
}; // 0x10

struct KAGE_Graphics_Color {
	float r; // 0x0
	float g; // 0x4
	float b; // 0x8
	float a; // 0xc
    KAGE_Graphics_Color() {
        r = g = b = a = 0;
    }

    KAGE_Graphics_Color(KColor const& other) {
        r = other._red;
        g = other._green;
        b = other._blue;
        a = other._alpha;
    }

    KAGE_Graphics_Color& operator=(KColor const& other) {
        r = other._red;
        g = other._green;
        b = other._blue;
        a = other._alpha;
        return *this;
    }
   
}; // 0x10

struct SourceQuad {
	Vector _topLeft; // 0x0
	Vector _topRight; // 0x8
	Vector _bottomLeft; // 0x10
	Vector _bottomRight; // 0x18
	int __coordinateSpaceEnum; // 0x20
}; // 0x24

struct KAGE_Graphics_ImageBase {
	void virtual_unk326() { }
	void virtual_unk327() { }
	void virtual_unk328() { }
	LIBZHL_API void Render(SourceQuad & source, DestinationQuad & dest, KAGE_Graphics_Color & color);
	LIBZHL_API void Original_Render(SourceQuad & source, DestinationQuad & dest, KAGE_Graphics_Color & color);
	LIBZHL_API void Render(SourceQuad & source, DestinationQuad & dest, KAGE_Graphics_Color & col1, KAGE_Graphics_Color & col2, KAGE_Graphics_Color & col3, KAGE_Graphics_Color & col4);
	LIBZHL_API void Original_Render(SourceQuad & source, DestinationQuad & dest, KAGE_Graphics_Color & col1, KAGE_Graphics_Color & col2, KAGE_Graphics_Color & col3, KAGE_Graphics_Color & col4);
	void virtual_unk329() { }
	void virtual_unk330() { }
	void virtual_unk331() { }
	void virtual_unk332() { }
	void virtual_unk333() { }
	void virtual_unk334() { }
	void virtual_unk335() { }
	void virtual_unk336() { }
	void virtual_unk337() { }
	void virtual_unk338() { }
	void virtual_unk339() { }
	void virtual_unk340() { }
	void virtual_unk341() { }
	void virtual_unk342() { }
	void virtual_unk343() { }
	void virtual_unk344() { }
	void virtual_unk345() { }
	void virtual_unk346() { }
	void virtual_unk347() { }
	void virtual_unk348() { }
	void virtual_unk349() { }
	void virtual_unk350() { }
	void virtual_unk351() { }
	void virtual_unk352() { }
	void virtual_unk353() { }
	void virtual_unk354() { }
	void virtual_unk355() { }
	void virtual_unk356() { }
	void virtual_unk357() { }
	void virtual_unk358() { }
	void virtual_unk359() { }
	void virtual_unk360() { }
	void virtual_unk361() { }
}; // 0x0

struct KAGE_Graphics_ImageBase_VertexAttributeDescriptor {
	char const * const * name; // 0x0
	unsigned int param; // 0x4
}; // 0x8

struct KAGE_Graphics_ImagePCX : public KAGE_Graphics_ImageBase {
};

struct KAGE_Graphics_ImagePIC : public KAGE_Graphics_ImageBase {
};

struct KAGE_Graphics_ImagePNG : public KAGE_Graphics_ImageBase {
};

struct KAGE_Graphics_Manager {
	char pad0[0x18]; // 0x0
	KAGE_Graphics_ImageBase * currentRenderTarget; // 0x18
	bool unk; // 0x1c
	char pad1[0xab]; // 0x1d
	unsigned int openGLFramebufferID; // 0xc8
	LIBZHL_API void SetCurrentRenderTarget(KAGE_Graphics_ImageBase * target, bool unk);
	LIBZHL_API void Clear();
	LIBZHL_API void Present();
};

struct KAGE_Graphics_VertexAttributeDescriptor {
};

struct KAGE_Graphics_Shader {
        inline int GetShaderId() { return *(int*)((char*)this + 0x28); }
   
};

struct KAGE_Graphics_Manager_GL {
	LIBZHL_API static void LoadShader(KAGE_Graphics_Shader * shader, KAGE_Graphics_VertexAttributeDescriptor * descriptor, char const * shaderPath);
};

struct KAGE_Memory_MemoryPoolDescriptor {
	KAGE_Memory_MemoryPool * container; // 0x0
	unsigned int offset; // 0x4
	unsigned int elementSize; // 0x8
	LIBZHL_API void * Allocate(unsigned int n);
    inline void* GetBase() {
        return (void*)(elementSize * (uintptr_t)*(void**)((offset << 4) + (char*)container + 0xC) + (uintptr_t)*(void**)((offset << 4) + (char*)container));
    }
   
}; // 0xc

struct KAGE_Graphics_RenderDescriptor {
	char pad0[0x10]; // 0x0
	KAGE_Graphics_Shader * shader; // 0x10
	char pad1[0xc]; // 0x14
	KAGE_Memory_MemoryPoolDescriptor vertices; // 0x20
	KAGE_Memory_MemoryPoolDescriptor elements; // 0x2c
}; // 0x38

struct KAGE_Memory_MemoryPool {
	void * data; // 0x0
	unsigned int size; // 0x4
	unsigned int capacity; // 0x8
	char pad0[0x4]; // 0xc
}; // 0x10

struct KAGE_System_Mutex {
	void * vtable; // 0x0
	bool initialized; // 0x4
	char pad0[0x3]; // 0x5
	KAGE_System_CriticalSection * cs; // 0x8
}; // 0xc

struct KAGE_SmartPointer_ImageBase {
	void * vtable; // 0x0
	unsigned short int strong; // 0x4
	unsigned short int weak; // 0x6
	KAGE_System_Mutex mutex; // 0x8
	KAGE_Graphics_ImageBase * image; // 0x14
}; // 0x18

struct KAGE_System_CriticalSection {
	CRITICAL_SECTION criticalSection; // 0x0
	bool locked; // 0x18
	char pad0[0x3]; // 0x19
}; // 0x1c

struct Leaderboard {
	int _selectedDate; // 0x0
	int _currentDate; // 0x4
	DailyChallenge _dailyChallenge; // 0x8
	char _scoreSheet[332]; // 0xbc
	char pad0[0x4]; // 0x208
	int _pageEntryStartID; // 0x20c
	int _isLeaderboardClosing; // 0x210
	char pad1[0x4]; // 0x214
	int _displayState; // 0x218
	int _scoreOrTimeRankingListState; // 0x21c
	int _listTypeSelection; // 0x220
	char pad2[0x8]; // 0x224
	int _numDisplayedEntries; // 0x22c
	char pad3[0x4]; // 0x230
	ANM2 _scoreMenuSprite; // 0x234
	ANM2 _leaderboardMenuSprite; // 0x348

}; // 0x45c

struct LevelGenerator_Room {
	bool _unk1; // 0x0
	char pad0[0x3]; // 0x1
	unsigned int _generationIndex; // 0x4
	unsigned int _gridColIdx; // 0x8
	unsigned int _gridLineIdx; // 0xc
	unsigned int _horizontalSize; // 0x10
	unsigned int _verticalSize; // 0x14
	unsigned int _shape; // 0x18
	unsigned int _doors; // 0x1c
	int _originNeighborConnectDir; // 0x20
	int _originNeighborConnectDirAdjust; // 0x24
	int _linkColIdx; // 0x28
	int _linkLineIdx; // 0x2c
	std_set_int _neighbors; // 0x30
	unsigned int _setExtraField; // 0x38
	bool _deadEnd; // 0x3c
	char pad1[0x3]; // 0x3d
	unsigned int _distanceFromStart; // 0x40
	bool _unk8; // 0x44
	char pad2[0x3]; // 0x45
}; // 0x48

struct LevelGenerator {
	LIBZHL_API bool place_room(LevelGenerator_Room * room);
	LIBZHL_API LevelGenerator_Room * CreateRoom(int x, int y, int shape, int connectX, int connectY, Direction connectDir);
	LIBZHL_API void Generate(int unk, bool unk2, bool unk3, bool unk4, unsigned int const & allowedShapes, unsigned int numDeadEnds, LevelGenerator_Room * startRoom);
	LIBZHL_API LevelGenerator_Room * GetNewEndRoom(int roomShape, unsigned int const & possibleDoors);
	LIBZHL_API void DetermineBossRoom(int shape, unsigned int const & possibleDoors);
	LIBZHL_API void get_neighbor_candidates(vector_LevelGenRoom * neighbors, unsigned int generationIndex, bool unk);
	LIBZHL_API void calc_required_doors();
	LIBZHL_API bool is_placement_valid(unsigned int * position, unsigned int shape);
	LIBZHL_API void mark_dead_ends();
    inline int* GetNumBossRooms() { return (int*)((char*)this + 0x38C); }
    inline std::vector<LevelGenerator_Room>* GetAllRooms() { return (std::vector<LevelGenerator_Room>*)((char*)this + 0x364); }
    inline std::vector<int>* GetDeadEnds() { return (std::vector<int>*)((char*)this + 0x370); }
    inline std::vector<int>* GetNonDeadEnds() { return (std::vector<int>*)((char*)this + 0x37C); }
};

struct LuaBridgeRef {
	lua_State * _state; // 0x0
	int _ref; // 0x4
		LuaBridgeRef() {

		}

}; // 0x8

struct LuaCallbackCallerResult {
	lua_State * state; // 0x0
	int ref; // 0x4
}; // 0x8

struct LuaCallbackCaller {
	lua_State * state; // 0x0
	int callbackId; // 0x4
	int optionalArg; // 0x8
	char pad0[0x4]; // 0xc
	LIBZHL_API LuaCallbackCallerResult CallInputAction(LuaEngine * engine, Entity * entity, int hook, int action);
}; // 0x10

struct RunCallbackRegistry {
	lua_State * state; // 0x0
	int key; // 0x4
}; // 0x8

struct LuaEngine {
	char pad0[0x10]; // 0x0
	RunCallbackRegistry * runCallbackRegistry; // 0x10
	char pad1[0x4]; // 0x14
	lua_State * _state; // 0x18
	int _runCallbackRegistryKey; // 0x1c
	LIBZHL_API void Init(bool Debug);
	LIBZHL_API void RegisterClasses();
	LIBZHL_API bool RunBundledScript(char const * path);
	LIBZHL_API static void __stdcall PostGameStart(unsigned int state);
	LIBZHL_API void RunScript(char const * path);
	LIBZHL_API void destroy();
	LIBZHL_API bool EntityTakeDamage(Entity * entity, float damage, unsigned long long int damageFlags, EntityRef * source, int damageCountdown);
	LIBZHL_API void EvaluateItems(Entity_Player * player, int cacheFlag);
	LIBZHL_API static void __stdcall Isaac_WorldToScreen(Vector * buffer, Vector * pos);
	
		inline bool GetLuaDebug() {return *(bool*)((char*)this + 0xC); }


};

struct UnknownGameStartStruct {
	char pad0[0x5c]; // 0x0
}; // 0x5c

struct StringTable {
	unsigned int language; // 0x0
	char pad0[0x14]; // 0x4
	LIBZHL_API char * GetString(char const * category, int language, char const * key, void * unk);
}; // 0x18

struct ModManager {
	vector_ModEntryPointer _mods; // 0x0
	char pad0[0x20250]; // 0xc
	LIBZHL_API void UpdateWorkshopMods();
	LIBZHL_API static void __stdcall RenderCustomCharacterMenu(int CharacterId, Vector * RenderPos, ANM2 * DefaultSprite);
	LIBZHL_API void RenderCustomCharacterPortraits(int id, Vector * pos, ColorMod * color, Vector * scale);
	LIBZHL_API void ListMods();
	LIBZHL_API void LoadConfigs();
	LIBZHL_API void UpdateRooms(int id, int mode);
	LIBZHL_API void Reset();
	LIBZHL_API void TriggerResize();
}; // 0x2025c

struct OptionsConfig {
	std_string _optionsIniFilePath; // 0x0
	float _musicVolume; // 0x18
	float _sfxVolume; // 0x1c
	float _mapOpacity; // 0x20
	bool _isFullscreen; // 0x24
	bool _filterEnabled; // 0x25
	bool field6_0x26; // 0x26
	bool field7_0x27; // 0x27
	float _gamma; // 0x28
	float _exposure; // 0x2c
	float _brightness; // 0x30
	float _contrast; // 0x34
	bool _controlHotplugEnabled; // 0x38
	bool _popupsEnabled; // 0x39
	bool _enableFoundHUD; // 0x3a
	bool field15_0x3b; // 0x3b
	int _cameraStyle; // 0x3c
	int _historyHudMode; // 0x40
	float _hudOffset; // 0x44
	bool _tryImportSave; // 0x48
	bool _enableMods; // 0x49
	bool _enableRumble; // 0x4a
	bool _enableChargeBars; // 0x4b
	bool _enableBulletVisibility; // 0x4c
	bool _enableAimLock; // 0x4d
	bool field25_0x4e; // 0x4e
	bool field26_0x4f; // 0x4f
	int _touchMode; // 0x50
	bool _enableDebugConsole; // 0x54
	bool _enableVSync; // 0x55
	bool _enableSteamCloud; // 0x56
	bool _enablePauseOnFocusLost; // 0x57
	bool _enableMouseControl; // 0x58
	bool field33_0x59; // 0x59
	bool field34_0x5a; // 0x5a
	bool field35_0x5b; // 0x5b
	int _maxScale; // 0x5c
	int _maxRenderScale; // 0x60
	int _windowWidth; // 0x64
	int _windowHeight; // 0x68
	int _windowPosX; // 0x6c
	int _windowPosY; // 0x70
	int _consoleFont; // 0x74
	bool _enableFadedConsoleDisplay; // 0x78
	bool _enableSaveCommandHistory; // 0x79
	bool _enableBorderlessFullscreen; // 0x7a
	bool _enableInterpolation; // 0x7b
	bool _enableColorCorrection; // 0x7c
	bool _enableLighting; // 0x7d
	bool _enableShockwave; // 0x7e
	bool _enableCaustics; // 0x7f
	bool _enableFilter; // 0x80
	bool _enablePixelation; // 0x81
	bool _enableBloom; // 0x82
	bool _enableWaterSurface; // 0x83
	bool _getsSetToEnableWaterSurface; // 0x84
	bool _enableColorModifier; // 0x85
	bool _bossHpOnBottom; // 0x86
	bool field58_0x87; // 0x87
	int _announcerVoiceMode; // 0x88
	char pad0[0x1]; // 0x8c
	LIBZHL_API void Save();
	LIBZHL_API void SetFullScreen(bool Value);
	inline bool ModsEnabled() { return _enableMods; }
	inline bool PopUpsEnabled() { return _popupsEnabled; }
}; // 0x8d

struct NightmareScene {
	char pad0[0x5ec]; // 0x0
	LIBZHL_API void LoadConfig(char * xmlpath);
	LIBZHL_API void Render();
	LIBZHL_API void Show(bool unk);
	inline ANM2* GetBackgroundSprite() { return (ANM2*)((char*)this + 0x20); }
	inline ANM2* GetBubbleSprite() { return (ANM2*)((char*)this + 0x134); }
	inline ANM2* GetProgressBarSprite() { return (ANM2*)((char*)this + 0x248); }
	inline int* GetProgressBarMap() { return (int*)((char*)this + 0x36c); }
	inline bool* IsDogmaNightmare() { return (bool*)((char*)this + 0x5e8); }
}; // 0x5ec

struct PersistentGameData {
	char pad0[0x38]; // 0x0
	bool achievements[638]; // 0x38
	char pad1[0xc6a]; // 0x2b6
	LIBZHL_API bool TryUnlock(int achievementID);
	LIBZHL_API void IncreaseEventCounter(int eEventCounters, int num);
	LIBZHL_API bool Unlocked(int achievementID);
	LIBZHL_API void AddToCollection(int collectibleID);
	LIBZHL_API void Load(char const * filepath);
	LIBZHL_API int GetBestiaryDeathCount(int EntityType, int EntityVariant);
	LIBZHL_API int GetBestiaryKillCount(int EntityType, int EntityVariant);
	LIBZHL_API int GetBestiaryEncounterCount(int EntityType, int EntityVariant);
	LIBZHL_API void UnlockSteamAchievement(int achievementID);
	inline int GetEventCounter(int eventCounter) {return *(int*)((char*)this + eventCounter * 4 + 0x2b8); }
	inline bool IsItemInCollection (int collectibleID) {
		bool savedata = *(bool*)((char*)this + collectibleID * 0x1 + 0xa78);
		return savedata != false; 
	}
	inline bool IsChallengeCompleted (int challengeID) {
		bool savedata = *(bool*)((char*)this + challengeID * 0x1 + 0xdff);
		return savedata != false; 
	}
}; // 0xf20

struct SoundEffects {
	char pad0[0x18]; // 0x0
	LIBZHL_API void ClearVolumeModifier();
	LIBZHL_API void Play(int ID, float Volume, int FrameDelay, bool Loop, float Pitch, float Pan);
}; // 0x18

struct Manager {
	char pad0[0x14]; // 0x0
	PersistentGameData _persistentGameData; // 0x14
	char pad1[0x28eac]; // 0xf34
	SoundEffects _sfxManager; // 0x29de0
	char pad2[0x8c]; // 0x29df8
	ItemConfig _itemConfig; // 0x29e84
	char pad3[0xb4]; // 0x29ed4
	EntityConfig _entityConfig; // 0x29f88
	char pad4[0x20280]; // 0x29fb4
	StringTable _stringTable; // 0x4a234
	char pad5[0x1a05f4]; // 0x4a24c
	ANM2 _cursorSprite; // 0x1ea840
	char pad6[0x20084]; // 0x1ea954
	LIBZHL_API static void __stdcall Update();
	LIBZHL_API static void __stdcall RecordPlayerCompletion(int eCompletionEvent);
	LIBZHL_API void LoadGameState(int saveslot);
	LIBZHL_API void LoadConfigs();
	LIBZHL_API void LoadChallenges(char * xmlpath, bool ismod);
	LIBZHL_API ChallengeParam * GetChallengeParams(int challengeID);
	LIBZHL_API void StartNewGame(int playerType, int challenge, UnknownGameStartStruct unk, int difficulty);
	LIBZHL_API bool AchievementUnlocksDisallowed(bool unk);
	LIBZHL_API void ExecuteStartGame();
	LIBZHL_API static void __stdcall RestartGame();
	LIBZHL_API void cleanup_current_state();
	LIBZHL_API static ReferenceCounter_ImageBase * __stdcall LoadImage(ReferenceCounter_ImageBase * result, char const * path, KAGE_Graphics_ImageBase_VertexAttributeDescriptor * descriptor, bool unk);
	LIBZHL_API void Render();
	LIBZHL_API void ResizeWindow(int windowWidth, int windowHeight);
	LIBZHL_API void ResizeWindowCallback(int windowWidth, int windowHeight);
	LIBZHL_API void SetFullscreenRendering(bool value);
	LIBZHL_API void SetSaveSlot(unsigned int slot);
	inline int GetState() { return *(int*)((char*)this + 0x8); }
	inline int* GetTestState() { return (int*)((char*)this + 0x8); }
	inline PersistentGameData* GetPersistentGameData() { return (PersistentGameData*)((char*)this + 0x14); }
	inline NightmareScene* GetNightmareScene() { return (NightmareScene*)((char*)this + 0x211BC); }
	inline bool GetDebugConsoleEnabled() { return *(bool*)((char*)this + 0x29E4C); }
	inline int GetMaxRenderScale() { return *(int*)((char*)this + 0x29E58); }
	inline ModManager* GetModManager() { return (ModManager*)((char*)this + 0x29FD8); }
	inline DailyChallenge* GetDailyChallenge() { return (DailyChallenge*)((char*)this + 0x1ea750); } 
	inline StringTable* GetStringTable() { return (StringTable*)((char*)this + 0x4a234); }
	inline bool GetNetStart() { return *(bool*)((char*)this + 0x1ea804); }
	inline Cutscene* GetCutscene() { return (Cutscene*)((char*)this + 0x20A00); }
	inline OptionsConfig* GetOptions() { return (OptionsConfig*)((char*)this + 0x29DF8); }
	inline AchievementOverlay* GetAchievementOverlay() { return (AchievementOverlay*)((char*)this + 0x217a8); }
	inline ItemConfig* GetItemConfig() { return &this->_itemConfig; }
	inline EntityConfig* GetEntityConfig() { return &this->_entityConfig; }
	inline std::vector<EntityConfig_Player>* GetPlayerConfig() { return this->GetEntityConfig()->GetPlayers(); }
}; // 0x20a9d8

struct Menu_Bestiary {
	float PositionX; // 0x0
	float PositionY; // 0x4
	ANM2 BestiaryMenuSprite; // 0x8
	ANM2 DeathScreenSprite; // 0x11c
	ANM2 EnemySprite; // 0x230
	int CurrentPage; // 0x344
	int SelectedElement; // 0x348
	int LastEnemyPageID; // 0x34c
	char pad0[0xc]; // 0x350
	int unk1; // 0x35c
	int unk2; // 0x360
	char pad1[0x4]; // 0x364
	int _holdLeftArrowCounter; // 0x368
	int _holdUpArrowCounter; // 0x36c
	int _holdRightArrowCounter; // 0x370
	int _holdDownArrowCounter; // 0x374
	LIBZHL_API void LoadPreview();
	inline ANM2* GetBestiaryMenuSprite() { return &this->BestiaryMenuSprite; }
	inline ANM2* GetDeathScreenSprite() { return &this->DeathScreenSprite; }
	inline ANM2* GetEnemySprite() { return &this->EnemySprite; }
}; // 0x378

struct Menu_Challenge {
	char pad0[0x4]; // 0x0
	int SelectedChallengeID; // 0x4
	int HoldInputTimer; // 0x8
	float PositionX; // 0xc
	float PositionY; // 0x10
	ANM2 ChallengeMenuSprite; // 0x14
	char _unkImageBase[8]; // 0x128
	inline ANM2* GetChallengeMenuSprite() { return &this->ChallengeMenuSprite; }
}; // 0x130

struct Menu_Character {
	int Status; // 0x0
	char pad0[0x1]; // 0x4
	bool IsCharacterUnlocked; // 0x5
	bool IsInputPossible; // 0x6
	char pad1[0x1]; // 0x7
	int Difficulty; // 0x8
	int CooldownWhenHoldDirection; // 0xc
	int SelectedCharacterID; // 0x10
	int _chosenRandomCharacter; // 0x14
	float _randomRotationVelocity; // 0x18
	char pad2[0x4]; // 0x1c
	int _randomRotationAmount; // 0x20
	float _characterWheelDepth; // 0x24
	float _scrollSpeed; // 0x28
	float _characterWheelWidth; // 0x2c
	float MenuBlackColorizeIntensity; // 0x30
	float MenuYellowColorizeIntensity; // 0x34
	float _PositionX; // 0x38
	float _PositionY; // 0x3c
	ANM2 _BigCharPageSprite; // 0x40
	ANM2 _DifficultyOverlaySprite; // 0x154
	ANM2 _GreedDecoOverlaySprite; // 0x268
	ANM2 _CharacterMenuBGSprite; // 0x37c
	CompletionWidget _completionWidget; // 0x490
	ANM2 _DifficultyPageSprite; // 0x5ac
	ANM2 _SeedPageSprite; // 0x6c0
	ANM2 _WinStreakPageSprite; // 0x7d4
	ANM2 _EastereggPageSprite; // 0x8e8
	ANM2 _SeedUnlockPageSprite; // 0x9fc
	int _numCharacters; // 0xb10
	int _numCharacters_MINUS_SelectedEntry; // 0xb14
	ANM2 _CharacterPortraitsSprite; // 0xb18
	char pad3[0x1c]; // 0xc2c
	ANM2 _SeedEntrySprite; // 0xc48
	char pad4[0x50]; // 0xd5c
	int _characterMenuShown; // 0xdac
	ANM2 _PageSwapWidgetSprite; // 0xdb0
	ANM2 _TaintedMenuBGDecoSprite; // 0xec4
	char pad5[0x14]; // 0xfd8
	LIBZHL_API void Update();
	LIBZHL_API void Render();
	LIBZHL_API void Init(Vector * unk);
	LIBZHL_API void SelectRandomChar();
	inline CompletionWidget* GetCompletionWidget() { return (CompletionWidget*)((char*)this + 1168); } 
	inline ANM2* GetBigCharPageSprite() { return &this->_BigCharPageSprite; }
	inline ANM2* GetDifficultyOverlaySprite() { return &this->_DifficultyOverlaySprite; }
	inline ANM2* GetGreedDecoSprite() { return &this->_GreedDecoOverlaySprite; }
	inline ANM2* GetBGSprite() { return &this->_CharacterMenuBGSprite; }
	inline ANM2* GetDifficultyPageSprite() { return &this->_DifficultyPageSprite; }
	inline ANM2* GetSeedPageSprite() { return &this->_SeedPageSprite; }
	inline ANM2* GetWinStreakPageSprite() { return &this->_WinStreakPageSprite; }
	inline ANM2* GetEastereggPageSprite() { return &this->_EastereggPageSprite; }
	inline ANM2* GetSeedUnlockPageSprite() { return &this->_SeedUnlockPageSprite; }
	inline ANM2* GetCharacterPortraitSprite() { return &this->_CharacterPortraitsSprite; }
	inline ANM2* GetSeedEntrySprite() { return &this->_SeedEntrySprite; }
	inline ANM2* GetPageSwapWidgetSprite() { return &this->_PageSwapWidgetSprite; }
	inline ANM2* GetTaintedBGDecoSprite() { return &this->_TaintedMenuBGDecoSprite; }
    
    inline int GetNumCharacters() { return this->_numCharacters; }
	inline int GetSelectedCharacterMenu() { return this->_characterMenuShown; }
}; // 0xfec

struct Menu_Collection {
	int HoldInputTimer; // 0x0
	int SelectedPage; // 0x4
	float PositionX; // 0x8
	float PositionY; // 0xc
	int SelectedElement; // 0x10
	ANM2 CollectionMenuSprite; // 0x14
	ANM2 DeathScreenSprite; // 0x128
	char pad0[0xc]; // 0x23c
	float MoveXAxisDirection; // 0x248
	float MoveYAxisDirection; // 0x24c
	char pad1[0xc]; // 0x250
	int NumItems; // 0x25c
	inline ANM2* GetCollectionMenuSprite() { return &this->CollectionMenuSprite; }
	inline ANM2* GetDeathScreenSprite() { return &this->DeathScreenSprite; }
}; // 0x260

struct Menu_ControllerSelect {
	int HoldInputTimer; // 0x0
	int SelectedElement; // 0x4
	float PositionX; // 0x8
	float PositionY; // 0xc
	ANM2 ControllerSelectSprite; // 0x10
	char pad0[0xc]; // 0x124
	inline ANM2* GetControllerSelectSprite() { return &this->ControllerSelectSprite; }
}; // 0x130

struct Menu_CustomChallenge {
	int SelectedElement; // 0x0
	int HoldInputTimer; // 0x4
	float PositionX; // 0x8
	float PositionY; // 0xc
	ANM2 CustomChallengeSprite; // 0x10
	inline ANM2* GetCustomChallengeSprite() { return &this->CustomChallengeSprite; }
}; // 0x124

struct Menu_Cutscenes {
	int HoldInputTimer; // 0x0
	int SelectedElement; // 0x4
	float PositionX; // 0x8
	float PositionY; // 0xc
	ANM2 CutscenesMenuSprite; // 0x10
	inline ANM2* GetCutscenesMenuSprite() { return &this->CutscenesMenuSprite; }
}; // 0x124

struct Menu_Stats {
	int _countTotalAchievements; // 0x0
	int _countItemsInCollection; // 0x4
	int _countDeaths; // 0x8
	int _countMomKills; // 0xc
	int _statsMenuCurrentSelection; // 0x10
	float _PositionX; // 0x14
	float _PositionY; // 0x18
	ANM2 _StatsMenuSprite; // 0x1c
	int _isAchievementScreenVisible; // 0x130
	float _achievementScrollInPosition; // 0x134
	float _achievementScrollThruListPosition; // 0x138
	int _selectedAchievmentId; // 0x13c
	int _IconIDtoUseForAchievementID[638]; // 0x140
	ANM2 _achievementsSprite; // 0xb38
	ANM2 _achievementMiniSprite1; // 0xc4c
	ANM2 _achievementMiniSprite2; // 0xd60
	ANM2 _achievementMiniSprite3; // 0xe74
	ANM2 _achievementMiniSprite4; // 0xf88
	ANM2 _achievementMiniSprite5; // 0x109c
	ANM2 _achievementMiniSprite6; // 0x11b0
	ANM2 _achievementMiniSprite7; // 0x12c4
	ANM2 _achievementMiniSprite8; // 0x13d8
	ANM2 _achievementMiniSprite9; // 0x14ec
	ANM2 _cursorLeftSprite; // 0x1600
	ANM2 _cursorRightSprite; // 0x1714
	AchievementOverlay_Entry _achievementOverlayEntries[638]; // 0x1828
	int _achievementIDList[638]; // 0x99c0
	int _maxAchievementID; // 0xa3b8
	int _holdInputTimer; // 0xa3bc
	float _scrollSpeed; // 0xa3c0

}; // 0xa3c4

struct Menu_Mods {
	int SelectedElement; // 0x0
	int HoldInputTimer; // 0x4
	float PositionX; // 0x8
	float PositionY; // 0xc
	ANM2 ModsMenuSprite; // 0x10
	int State; // 0x124
	void * _pointerToSelectedMod; // 0x128
	char pad0[0x80]; // 0x12c
	float _scrollPositionX; // 0x1ac
	float _scrollPositionY; // 0x1b0
         inline ANM2* GetModsMenuSprite() { return &this->ModsMenuSprite; }
    
}; // 0x1b4

struct Menu_KeyConfig {
	int State; // 0x0
	int SelectedElement; // 0x4
	int SelectedColumn; // 0x8
	float PositionX; // 0xc
	float PositionY; // 0x10
	ANM2 KeyConfigSprite; // 0x14
	inline ANM2* GetKeyConfigSprite() { return &this->KeyConfigSprite; }
}; // 0x128

struct Menu_Title {
	float PositionX; // 0x0
	float PositionY; // 0x4
	ANM2 TitleScreenSprite; // 0x8
	int unusedVariable; // 0x11c
	LIBZHL_API void Update();
	LIBZHL_API void Render();
	inline ANM2* GetTitleScreenSprite() { return &this->TitleScreenSprite; }
}; // 0x120

struct Menu_Save {
	int State; // 0x0
	int SelectedSave; // 0x4
	char pad0[0x4]; // 0x8
	int HoldInputTimer; // 0xc
	float PositionX; // 0x10
	float PositionY; // 0x14
	ANM2 SaveSelectMenuSprite; // 0x18
	ANM2 Save1DrawingSprite; // 0x12c
	ANM2 Save2DrawingSprite; // 0x240
	ANM2 Save3DrawingSprite; // 0x354
	char pad1[0x4]; // 0x468
	ANM2 DeleteButtonSprite; // 0x46c
	ANM2 DeletePopupSprite; // 0x580
         inline ANM2* GetSaveSelectMenuSprite() { return &this->SaveSelectMenuSprite; }
         inline ANM2* GetDeleteButtonSprite() { return &this->DeleteButtonSprite; }
         inline ANM2* GetDeletePopupSprite() { return &this->DeletePopupSprite; }
         inline ANM2* GetSave1DrawingSprite() { return &this->Save1DrawingSprite; }
         inline ANM2* GetSave2DrawingSprite() { return &this->Save2DrawingSprite; }
         inline ANM2* GetSave3DrawingSprite() { return &this->Save3DrawingSprite; }
    
}; // 0x694

struct Menu_SpecialSeeds {
	int State; // 0x0
	int SelectedElement; // 0x4
	int HoldInputTimer; // 0x8
	float PositionX; // 0xc
	float PositionY; // 0x10
	ANM2 SpecialSeedsSprite; // 0x14
	std_string _seedUnlockedString; // 0x128
	std_string _seedEnabledString; // 0x140
	char pad0[0xc]; // 0x158
         inline ANM2* GetSpecialSeedsSprite() { return &this->SpecialSeedsSprite; }
    
}; // 0x164

struct Menu_Game {
	int KeyDownTimer; // 0x0
	int SelectedElement; // 0x4
	float PositionX; // 0x8
	float PositionY; // 0xc
	ANM2 GameMenuSprite; // 0x10
	ANM2 ContinueWidgetSprite; // 0x124
	char pad0[0x128]; // 0x238
	LIBZHL_API void Update();
	LIBZHL_API void Render();
	LIBZHL_API void PreRenderContinueImg();
	inline ANM2* GetGameMenuSprite() { return &this->GameMenuSprite; }
	inline ANM2* GetContinueWidgetSprite() { return &this->ContinueWidgetSprite; }
}; // 0x360

struct Menu_Options {
	char pad0[0x4]; // 0x0
	int SelectedElement; // 0x4
	float PositionX_duplicate; // 0x8
	float PositionY_duplicate; // 0xc
	float PositionX; // 0x10
	float PositionY; // 0x14
	char pad1[0x8]; // 0x18
	ANM2 OptionsSprite; // 0x20
	ANM2 GammaMenuSprite; // 0x134
	int HoldLeftCounter; // 0x248
	int HoldRightCounter; // 0x24c
	int HoldUpDownCounter; // 0x250
	char pad2[0x4]; // 0x254
	int _someState; // 0x258
	unsigned int _somethingLanguageRelated; // 0x25c
	char pad3[0xc]; // 0x260
         inline ANM2* GetOptionsSprite() { return &this->OptionsSprite; }
         inline ANM2* GetGammaMenuSprite() { return &this->GammaMenuSprite; }
    
}; // 0x26c

struct Menu_DailyChallenge {
	int State; // 0x0
	int _holdInputTimer; // 0x4
	int SelectedElement; // 0x8
	float _positionX; // 0xc
	float _positionY; // 0x10
	ANM2 _DailyRunSprite; // 0x14
	std_string _steamUsername; // 0x128
	int lastRunScore; // 0x140
	Leaderboard _leaderboard; // 0x144
	int _timeDaysLeftUNUSED; // 0x5a0
	int _timeHoursLeft; // 0x5a4
	int _timeMinutesLeft; // 0x5a8
	int _timeSecondsLeft; // 0x5ac
	AnimationState * _leaderboardAnmState; // 0x5b0
	GenericPopup GenericPopup_genericPopup; // 0x5b4
	GenericPrompt GenericPrompt_genericPrompt; // 0x6d4
	char pad0[0x8]; // 0x808ec
	
}; // 0x808f4

struct MenuManager {
	int _state; // 0x0
	float _fadeOutProgress; // 0x4
	int _fadeInActive; // 0x8
	float _fadeInProgress; // 0xc
	KAGE_Graphics_Color _fadeInColor; // 0x10
	int _returnState; // 0x20
	int _unrecognizedControllerPopupVisible; // 0x24
	float _vingnetteIntensity; // 0x28
	float _backWidgetPositionOffsetY; // 0x2c
	float _selectWidgetPositionOffsetY; // 0x30
	int _controllerIndex; // 0x34
	int _selectedMenuID; // 0x38
	Vector _ViewPosition; // 0x3c
	ANM2 _MenuShadowSprite; // 0x44
	ANM2 _BackWidgetSprite; // 0x158
	ANM2 _SelectWidgetSprite; // 0x26c
	GenericPopup GenericPopup_unrecognizedControllerPopup; // 0x380
	char ImageBase_EmptyScreenImage[8]; // 0x4a0
	char ImageBase_MenuOverlayImage[8]; // 0x4a8
	char ImageBase_UNUSED4b0[8]; // 0x4b0
	Seeds _seedsObject; // 0x4b8
	Menu_Title _menuTitle; // 0x514
	Menu_Save _menuSave; // 0x634
	GenericPrompt GenericPopup_genericPrompt; // 0xcc8
	char _UNUSED80ee0[204]; // 0x80ee0
	Menu_Game _menuGame; // 0x80fac
	Menu_DailyChallenge _menuDailyChallenge; // 0x8130c
	Menu_Character _menuCharacter; // 0x101c00
	Menu_SpecialSeeds _menuSpecialSeeds; // 0x102bec
	Menu_Challenge _menuChallenge; // 0x102d50
	Menu_Collection _menuCollection; // 0x102e80
	Menu_Stats _menuStats; // 0x1030e0
	Menu_Options _menuOptions; // 0x10d4a4
	Menu_ControllerSelect _menuControllerSelect; // 0x10d710
	Menu_KeyConfig _menuKeyConfig; // 0x10d840
	Menu_Cutscenes _menuCutscenes; // 0x10d968
	Menu_Bestiary _menuBestiary; // 0x10da8c
	Menu_CustomChallenge _menuCustomChallenge; // 0x10de04
	Menu_Mods _menuMods; // 0x10df28
	bool _shouldLerpColorModState; // 0x10e0dc
	char pad0[0x3]; // 0x10e0dd
	ColorModState _currentColorModState; // 0x10e0e0
	ColorModState _targetColorModState; // 0x10e0f8
	ColorModState _lerpColorModState; // 0x10e110
	char pad1[0x10]; // 0x10e128
	ANM2 _flySprite; // 0x10e138
	LIBZHL_API void constructor();
	LIBZHL_API void Init();
	LIBZHL_API void Render();
	LIBZHL_API void RenderButtonLayout();
	LIBZHL_API void SetState(int estate);
	MenuManager()
	{
		this->constructor();
	}
	
	inline Menu_Game* GetMenuGame() {return &this->_menuGame; }
	inline Menu_Character* GetMenuCharacter() {return &this->_menuCharacter; }

	inline Menu_Title* GetMenuTitle() {return &this->_menuTitle; }
	inline Menu_Save* GetMenuSave() {return &this->_menuSave; }
	inline Menu_Challenge* GetMenuChallenge() {return &this->_menuChallenge; }
	inline Menu_DailyChallenge* GetMenuDailyChallenge() {return &this->_menuDailyChallenge; }
	inline Menu_Collection* GetMenuCollection() {return &this->_menuCollection; }
	inline Menu_Bestiary* GetMenuBestiary() {return &this->_menuBestiary; }
	inline Menu_Stats* GetMenuStats() {return &this->_menuStats; }
	inline Menu_Options* GetMenuOptions() {return &this->_menuOptions; }
	inline Menu_SpecialSeeds* GetMenuSpecialSeeds() {return &this->_menuSpecialSeeds; }
	inline Menu_ControllerSelect* GetMenuControllerSelect() {return &this->_menuControllerSelect; }
	inline Menu_KeyConfig* GetMenuKeyConfig() {return &this->_menuKeyConfig; }
	inline Menu_Cutscenes* GetMenuCutscenes() {return &this->_menuCutscenes; }
	inline Menu_CustomChallenge* GetMenuCustomChallenge() {return &this->_menuCustomChallenge; }
	inline Menu_Mods* GetMenuMods() {return &this->_menuMods; }
	inline ColorModState* GetCurrentColorModifier() { return &this->_currentColorModState; }
	inline ColorModState* GetTargetColorModifier() { return &this->_targetColorModState; }
	inline ColorModState* GetLerpColorModifier() { return &this->_lerpColorModState; }
}; // 0x10e24c

struct Minimap {
	char pad0[0x628]; // 0x0
	LIBZHL_API void Update();
	LIBZHL_API void Render();
	LIBZHL_API Vector * GetDisplayedSize(Vector & buffer);
}; // 0x628

struct Music {
	char pad0[0x368]; // 0x0
	LIBZHL_API void Play(int musicid, float volume);
	LIBZHL_API void Crossfade(int musicid, float faderate);
	LIBZHL_API void PlayJingle(int musicid, int unusedInt, bool unusedBool);
	LIBZHL_API void Fadein(unsigned int Id, float Volume, float FadeRate);
	LIBZHL_API void LoadConfig(char * xmlpath, bool ismod);
	LIBZHL_API void DisableLayer(int id);
	LIBZHL_API void EnableLayer(int id, bool instant);
	inline void StopJingle() {
		*(int*)((char*)this + 0x348) = 0;
		*(int*)((char*)this + 0x364) = -99;
	};
}; // 0x368

struct NPCAI_Pathfinder {
	char pad0[0x750]; // 0x0
}; // 0x750

struct NullFrame {
	char pad0[0x48]; // 0x0
	inline Vector* GetPos() {return (Vector*)((char*)this); }
	inline bool* IsVisible() {return (bool*)((char*)this + 0xC); }
	inline Vector* GetScale() {return (Vector*)((char*)this + 0x10); }
	inline ColorMod* GetColor() {return (ColorMod*)((char*)this + 0x18); }
	inline float* GetRotation() {return (float*)((char*)this + 0x44); }
}; // 0x48

struct PauseScreen {
	int status; // 0x0
	char pad0[0x80a34]; // 0x4
	LIBZHL_API void Render();
	inline CompletionWidget* GetCompletionWidget() { return (CompletionWidget*)((char*)this + 526620); } 
	inline ANM2* GetANM2() { return (ANM2*)((char*)this + 44); }
	//inline ANM2* GetANM22() { return (ANM2*)((char*)this + 92); } // ?? another sprite, it can be rendered but I suspect its the same one loaded at a different offset?
	inline ANM2* GetStatsANM2() { return (ANM2*)((char*)this + 368); }	
}; // 0x80a38

struct PlayerHUDActiveItem {
	int id; // 0x0
	LIBZHL_API void RenderGfx(SourceQuad * sourceQuad, DestinationQuad * destQuad, ColorMod const & color);
}; // 0x4

struct PocketItem {
	int _slot; // 0x0
	int _type; // 0x4
}; // 0x8

struct Point {
	Vector _pos; // 0x0
	float _height; // 0x8
	float _width; // 0xc
	ColorMod _color; // 0x10
	LIBZHL_API void UpdateNormal(Vector * unk);
		Point() : _pos(Vector()), _height(100.f), _width(1.f), _color(ColorMod()) {}
		Point(Vector const& pos, float height, float width, ColorMod const& color) : _pos(pos), _height(height), _width(width), _color(color) {}

}; // 0x3c

struct PosVel {
	Vector pos; // 0x0
	Vector vel; // 0x8
	PosVel() : pos(Vector()), vel(Vector()) {}
	PosVel(Vector _pos, Vector _vel) : pos(_pos), vel(_vel) {}

	PosVel operator+(const PosVel& other)
	{
		return PosVel(pos + other.pos, vel + other.vel);
	}
	
	PosVel operator-(const PosVel& other)
	{		
		return PosVel(pos - other.pos, vel - other.vel);
	}
	
	PosVel operator/(float amount)
	{		
		return PosVel(pos / amount, vel / amount);
	}
	
	PosVel operator*(float amount)
	{		
		return PosVel(pos * amount, vel * amount);
	}

}; // 0x10

struct ProjectileParams {
	bool GridCollision; // 0x0
	char pad0[0x3]; // 0x1
	float HeightModifier; // 0x4
	float FallingSpeedModifier; // 0x8
	float FallingAccelModifier; // 0xc
	float VelocityMulti; // 0x10
	float Scale; // 0x14
	float CircleAngle; // 0x18
	float HomingStrength; // 0x1c
	float CurvingStrength; // 0x20
	float Acceleration; // 0x24
	float Spread; // 0x28
	ColorMod Color; // 0x2c
	unsigned long long int BulletFlags; // 0x58
	Vector PositionOffset; // 0x60
	Vector TargetPosition; // 0x68
	Vector FireDirectionLimit; // 0x70
	float DotProductLimit; // 0x78
	int WiggleFrameOffset; // 0x7c
	unsigned long long int ChangeFlags; // 0x80
	float ChangeVelocity; // 0x88
	unsigned int ChangeTimeout; // 0x8c
	float DepthOffset; // 0x90
	unsigned int Variant; // 0x94
	char pad1[0x4]; // 0x98
	float Damage; // 0x9c
	char pad2[0x8]; // 0xa0
}; // 0xa8

struct Rendering {
	LIBZHL_API static void __stdcall PushCurrentRenderTarget();
	LIBZHL_API static void __stdcall RestorePreviousRenderTarget();
}; // 0x0

struct RoomEntry {
	unsigned int type; // 0x0
	unsigned short int variant; // 0x4
	unsigned short int subtype; // 0x6
	float weight; // 0x8
}; // 0xc

struct RoomSpawn {
	unsigned short int X; // 0x0
	unsigned short int Y; // 0x2
	RoomEntry * Entries; // 0x4
	unsigned short int CountEntries; // 0x8
	char pad0[0x2]; // 0xa
	float SumWeights; // 0xc
}; // 0x10

struct SFXManager {
	LIBZHL_API void Play(int ID, float Volume, int FrameDelay, bool Loop, float Pitch, float Pan);
	LIBZHL_API void LoadConfig(char * xmlpath, bool ismod);
}; // 0x0

struct Shape {
	char pad0[0x8]; // 0x0
	LIBZHL_API void Capsula(Capsule * Thing);
	inline int* GetTimeout() { return (int*)((char*)this + 0x4); }
}; // 0x8

struct ShapeRenderer {
	LIBZHL_API int RenderLine(Vector * pos1, Vector * pos2, KColor * col1, KColor * col2, float const & thickness);
	int OutlineQuad(DestinationQuad* quad, KColor* col, float thickness) 
	{ // LOOK, OUR FLOAT IS NOT A POINTER! ISN'T THAT A CONCEPT??????? WHAT????????
		int ret = this->RenderLine(&quad->_topLeft, &quad->_topRight, col, col, thickness);
		this->RenderLine(&quad->_topRight, &quad->_bottomRight, col, col, thickness);
		this->RenderLine(&quad->_bottomRight, &quad->_bottomLeft, col, col, thickness);
		this->RenderLine(&quad->_bottomLeft, &quad->_topLeft, col, col, thickness);
		return ret;
	}
};

struct StageTransition {
	char pad0[0x10]; // 0x0
	bool _sameStage; // 0x10
	char pad1[0x3]; // 0x11
}; // 0x14

struct StaticArray {
	void * data; // 0x0
	unsigned short int size; // 0x4
}; // 0x6

struct TearParams {
	unsigned int _tearVariant; // 0x0
	unsigned int _bombVariant; // 0x4
	ColorMod _tearColor; // 0x8
	char pad0[0x4]; // 0x34
	BitSet128 _flags; // 0x38
	float _tearDamage; // 0x48
	float _tearScale; // 0x4c
	float _tearHeight; // 0x50
	char pad1[0x14]; // 0x54
	LIBZHL_API void constructor();
	TearParams() 
	{
		this->constructor();
	}
}; // 0x68

struct TemporaryEffect {
	ItemConfig_Item * _item; // 0x0
	int _count; // 0x4
	int _cooldown; // 0x8
}; // 0xc

struct TrinketPoolItem {
	unsigned int _ID; // 0x0
	bool _inPool; // 0x4
	bool _isAvailable; // 0x5
	char pad0[0x2]; // 0x6
}; // 0x8

struct Weapon {
	char pad0[0x40]; // 0x0
	LIBZHL_API void PlayItemAnim(unsigned int collectibleID, int itemAnim, Vector const & pos, float Charge);
	LIBZHL_API void SetBlinkTime(int Delay);
	LIBZHL_API void TriggerTearFired(Vector const & pos, int FireAmount);
	LIBZHL_API bool IsAxisAligned();
	LIBZHL_API bool IsItemAnimFinished(unsigned int collectibleID);
	LIBZHL_API void ClearItemAnim(unsigned int collectibleID);
	LIBZHL_API void SetHeadLockTime(int Time);
	LIBZHL_API static Entity_Laser * FireBrimstone(Entity * entity, Vector const & position, Vector const & direction, float damageMult, float unk1, unsigned int unk2);
	LIBZHL_API Entity_Knife * FireSword(Entity * param_1, unsigned int param_2, float param_3, bool param_4, bool param_5, unsigned int param_6, Entity * param_7);
	void virtual_unk362() { }
	void virtual_unk363() { }
	void virtual_unk364() { }
	LIBZHL_API void Fire(Vector const & pos, bool IsShooting, bool IsInterpolated);
	LIBZHL_API void Original_Fire(Vector const & pos, bool IsShooting, bool IsInterpolated);
	void virtual_unk365() { }
	void virtual_unk366() { }
	void virtual_unk367() { }
	void virtual_unk368() { }
	void virtual_unk369() { }
	void virtual_unk370() { }
	void virtual_unk371() { }
	void virtual_unk372() { }
	void virtual_unk373() { }
	void virtual_unk374() { }
	void virtual_unk375() { }
	void virtual_unk376() { }
	void virtual_unk377() { }
	inline Entity* GetOwner() { return *(Entity**)((char*)this + 0x4); }
	inline float* GetFireDelay() { return (float*)((char*)this + 0xC); }
	inline float GetMaxFireDelay() { return *(float*)((char*)this + 0x10); }
	inline float* GetCharge() { return (float*)((char*)this + 0x14); }
	inline Vector* GetDirection() {return (Vector*)((char*)this + 0x1c); }
	inline int GetWeaponType() { return *(int*)((char*)this + 0x2c); }
	inline int GetModifiers() { return *(int*)((char*)this + 0x30); }
	inline int GetNumFired() { return *(int*)((char*)this + 0x34); }
}; // 0x40

struct Weapon_Brimstone : public Weapon {
	char pad0[0x8]; // 0x40
	LIBZHL_API void Fire(Vector const & shootPos, bool IsShooting, bool IsInterpolated);
	LIBZHL_API void Original_Fire(Vector const & shootPos, bool IsShooting, bool IsInterpolated);
	void virtual_unk378() { }
	void virtual_unk379() { }
	void virtual_unk380() { }
	void virtual_unk381() { }
	void virtual_unk382() { }
	void virtual_unk383() { }
	void virtual_unk384() { }
	void virtual_unk385() { }
	void virtual_unk386() { }
	void virtual_unk387() { }
	void virtual_unk388() { }
	void virtual_unk389() { }
	void virtual_unk390() { }
	void virtual_unk391() { }
	void virtual_unk392() { }
	void virtual_unk393() { }

}; // 0x48

struct Weapon_MonstrosLung : public Weapon {
	LIBZHL_API void Fire(Vector const & shootPos, bool IsShooting, bool IsInterpolated);
	LIBZHL_API void Original_Fire(Vector const & shootPos, bool IsShooting, bool IsInterpolated);
	void virtual_unk394() { }
	void virtual_unk395() { }
	void virtual_unk396() { }
	void virtual_unk397() { }
	void virtual_unk398() { }
	void virtual_unk399() { }
	void virtual_unk400() { }
	void virtual_unk401() { }
	void virtual_unk402() { }
	void virtual_unk403() { }
	void virtual_unk404() { }
	void virtual_unk405() { }
	void virtual_unk406() { }
	void virtual_unk407() { }
	void virtual_unk408() { }
	void virtual_unk409() { }

}; // 0x40

struct Weapon_MultiShotParams {
	short int numTears; // 0x0
	short int numLanesPerEye; // 0x2
	float spreadAngleTears; // 0x4
	float spreadAngleLaser; // 0x8
	float speadAngleTechX; // 0xc
	float spreadAngleKnife; // 0x10
	int numEyesActive; // 0x14
	float multiEyeAngle; // 0x18
	bool isCrossEyed; // 0x1c
	bool isShootingBackwards; // 0x1d
	bool isShootingSideways; // 0x1e
	char pad0[0x1]; // 0x1f
	short int numRandomDirTears; // 0x20
	char pad1[0x2]; // 0x22
}; // 0x24

struct WeightedOutcomePicker_Outcome {
	unsigned int _value; // 0x0
	unsigned int _weight; // 0x4
}; // 0x8

struct WeightedOutcomePicker {
	vector_Outcome _outcomes; // 0x0
	LIBZHL_API unsigned int PickOutcome(RNG rng);
	LIBZHL_API void AddOutcomeWeight(WeightedOutcomePicker_Outcome outcome, bool unk);
	LIBZHL_API void * InsertOutcomeToVec(WeightedOutcomePicker_Outcome * unk, WeightedOutcomePicker_Outcome * outcome);
    inline vector_Outcome* GetOutcomes() { return (vector_Outcome*)this; }
}; // 0xc

struct xmldocument_rep {
	LIBZHL_API void parse(char * xmldata);

};

LIBZHL_API char * * __stdcall GetXMLNode(char * thi, int unk, char * name);
LIBZHL_API void RepCaughtException(int x);
LIBZHL_API GridEntity * __fastcall CreateGridEntity(GridEntityType type, unsigned int seed);
LIBZHL_API bool __stdcall CanRerollCollectible(int id);
LIBZHL_API void GetLevelName(std_string * result, unsigned int levelStage, unsigned int stageType, unsigned int curseMask, unsigned int unk, unsigned int unk2, bool unk3);
LIBZHL_API unsigned int __stdcall Random();

namespace OpenGL {
	bool __stdcall wglSwapBuffers(HDC hdc);
}
namespace VCRuntime {
	void __stdcall _CxxThrowException(void * except, ThrowInfo * info);
#ifdef DEBUG
	void __stdcall _CxxThrowExceptionD(void * except, ThrowInfo * info);
#endif
}