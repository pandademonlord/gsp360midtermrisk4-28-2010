#pragma once

//general screen & window info
#define SCREEN_WIDTH				1230
#define SCREEN_HEIGHT				630
#define SCREEN_MAX_X				SCREEN_WIDTH
#define SCREEN_MAX_Y				SCREEN_HEIGHT
#define SCREEN_MIN_X				0
#define SCREEN_MIN_Y				0
#define DASH_SIZE					.5
#define INIT_WINDOW_X				10
#define INIT_WINDOW_Y				50
#define TIMER_VALUE					20
#define BUFFER_SIZE					150

//mouse button states
#define	STATE_MOUSE_BUTTON_DN		0
#define STATE_MOUSE_BUTTON_UP		1

//state machine
#define STATE_INIT_PLACEMENT_CLAIM	0
#define STATE_INIT_PLACEMENT_PLACE	1
#define STATE_GET_TROOPS_TERRITORY	2
#define STATE_GET_TROOPS_CARDS		3
#define STATE_PLACE_BONUS_TROOPS	4
#define STATE_ATTACK_FROM			5
#define STATE_ATTACK_TO				6
#define STATE_ATTACK_BATTLE			7
#define STATE_CAPTURE_TERRITORY		8
#define STATE_ELIMINATE_ENEMY		9
#define STATE_CHECK_IF_WON			10
#define STATE_EXCESS_CARDS			11
#define STATE_PLACE_EXCESS_TROOPS	12
#define STATE_AFTER_ATK_B4_FORTIFY	13
#define STATE_FORTIFY_FROM			14
#define STATE_FORTIFY_TO			15
#define STATE_FORTIFY_TROOPS		16
	//go this state ONLY if current player owns all 42 territories
#define STATE_WIN					17

//flags (array of "short" numbers, either used as "short" or "bool" value)
	//#defined numbers represent that flag's element in the array
//# of total flags within array
#define FLAGS_NUM					14
//(bool) determine if hover is within a territory
#define FLAG_WITHIN_AREA			0
//(short) index of which territory was clicked on
#define FLAG_CLICKED_TER			1
//(short) which index to use for 1st territory
#define FLAG_PARAM_TER_ONE			2
//(short) which index to use for 2nd territory
#define FLAG_PARAM_TER_TWO			3
//(short) stores #territories b4 atk, & later, how many troops to move/fortify
#define FLAG_PARAM_NUM				4
//(bool) are all needed parameters set?
#define FLAG_PARAMS_SET				5
//(short) game's current state
#define FLAG_GAME_STATE				6
//(bool) should the state change?
#define FLAG_UPDATE_GAME_STATE		7
//(short) number of players @ start of game
#define FLAG_PLAYERS				8
//(short) ID of current player
#define FLAG_CURRENT_PLAYER			9
//(bool) should the player change?
#define FLAG_UPDATE_PLAYER			10
//(bool) should the player be allowed to draw a card for capturing territory
#define FLAG_DRAW_CARD				11
//(short) # of card sets that have been turned in
#define FLAG_CARD_SET				12
//(bool) is this the 1st set turned in this turn?
#define FLAG_FIRST_SET_IN_TURN		13

//input
#define CLICK_TWO_TERRITORIES		2
#define CLICK_TERRITORY_ONE			0
#define CLICK_TERRITORY_TWO			1

//colors
#define COLOR_DARK_VALUE			150
#define COLOR_MAX_VALUE				255
#define COLOR_ORANGE_RATIO			.75
#define	COLOR_ALPHA					1.0
#define COLOR_GREY					.5,.5,.5

	//regular colors
#define COLOR_BLUE					0,0,COLOR_MAX_VALUE
#define COLOR_CYAN					0,COLOR_MAX_VALUE,COLOR_MAX_VALUE
#define COLOR_GREEN					0,COLOR_MAX_VALUE,0
#define COLOR_ORANGE				COLOR_MAX_VALUE,(COLOR_MAX_VALUE*COLOR_ORANGE_RATIO),0
#define COLOR_PURPLE				COLOR_MAX_VALUE,0,COLOR_MAX_VALUE
#define COLOR_RED					COLOR_MAX_VALUE,0,0
#define COLOR_WHITE					COLOR_MAX_VALUE,COLOR_MAX_VALUE,COLOR_MAX_VALUE
#define COLOR_YELLOW				COLOR_MAX_VALUE,COLOR_MAX_VALUE,0

	//darker variants of above colors
#define COLOR_BLUE_DARK				0,0,COLOR_DARK_VALUE
#define COLOR_GREEN_DARK			0,COLOR_DARK_VALUE,0
#define COLOR_ORANGE_DARK			COLOR_DARK_VALUE,(COLOR_DARK_VALUE*COLOR_ORANGE_RATIO),0
#define COLOR_PURPLE_DARK			COLOR_DARK_VALUE,0,COLOR_DARK_VALUE
#define COLOR_RED_DARK				COLOR_DARK_VALUE,0,0
#define COLOR_YELLOW_DARK			COLOR_DARK_VALUE,COLOR_DARK_VALUE,0

//which colors to use
	//for hovering & continents
#define HIGHLIGHT_COLOR				COLOR_WHITE
#define CONTINENT_COLOR_NA			COLOR_YELLOW_DARK
#define CONTINENT_COLOR_SA			COLOR_RED_DARK
#define CONTINENT_COLOR_EU			COLOR_BLUE_DARK
#define CONTINENT_COLOR_AF			COLOR_ORANGE_DARK
#define CONTINENT_COLOR_AS			COLOR_GREEN_DARK
#define CONTINENT_COLOR_OC			COLOR_PURPLE_DARK
	//for players
#define PLAYER_ONE_COLOR			COLOR_YELLOW
#define PLAYER_TWO_COLOR			COLOR_RED
#define PLAYER_THREE_COLOR			COLOR_CYAN//COLOR_BLUE	
#define PLAYER_FOUR_COLOR			COLOR_ORANGE
#define PLAYER_FIVE_COLOR			COLOR_GREEN
#define PLAYER_SIX_COLOR			COLOR_PURPLE

//continent ID's
#define CONTINENT_ID_N_AMERICA		0
#define CONTINENT_ID_S_AMERICA		1
#define CONTINENT_ID_EUROPE			2
#define CONTINENT_ID_AFRICA			3
#define CONTINENT_ID_ASIA			4
#define CONTINENT_ID_OCEANIA		5

//owner ID's
#define OWNER_NONE					-1
#define PLAYER_ONE					0
#define PLAYER_TWO					1
#define PLAYER_THREE				2
#define PLAYER_FOUR					3
#define PLAYER_FIVE					4
#define PLAYER_SIX					5
#define PLAYERS_MIN					2
#define PLAYERS_MAX					6

//number of territories in specified continent
#define TERRITORIES_N_AMERICA		9
#define TERRITORIES_S_AMERICA		4
#define TERRITORIES_EUROPE			7
#define TERRITORIES_AFRICA			6
#define TERRITORIES_ASIA			12
#define TERRITORIES_OCEANIA			4
//total number of territories (42)
#define TERRITORIES_TOTAL			(TERRITORIES_N_AMERICA + TERRITORIES_S_AMERICA + TERRITORIES_EUROPE + TERRITORIES_AFRICA + TERRITORIES_ASIA + TERRITORIES_OCEANIA)

//bonus troops for owning continents
#define BONUS_NA					5
#define BONUS_SA					2
#define BONUS_EU					5
#define BONUS_AF					3
#define BONUS_AS					7
#define BONUS_OC					2

//the element at which the territories for the specified continent start
#define TERRITORIES_ST_N_AMERICA	0
#define TERRITORIES_ST_S_AMERICA	(TERRITORIES_ST_N_AMERICA + TERRITORIES_N_AMERICA)
#define TERRITORIES_ST_EUROPE		(TERRITORIES_ST_S_AMERICA + TERRITORIES_S_AMERICA)
#define TERRITORIES_ST_AFRICA		(TERRITORIES_ST_EUROPE + TERRITORIES_EUROPE)
#define TERRITORIES_ST_ASIA			(TERRITORIES_ST_AFRICA + TERRITORIES_AFRICA)
#define TERRITORIES_ST_OCEANIA		(TERRITORIES_ST_ASIA + TERRITORIES_ASIA)

//define all territory ID's
//NORTH AMERICA
#define ID_ALASKA					(TERRITORIES_ST_N_AMERICA + 0)
#define ID_ALBERTA					(TERRITORIES_ST_N_AMERICA + 1)
#define ID_C_AMERICA				(TERRITORIES_ST_N_AMERICA + 2)
#define ID_E_US						(TERRITORIES_ST_N_AMERICA + 3)
#define ID_GREENLAND				(TERRITORIES_ST_N_AMERICA + 4)
#define ID_NW_TERRITORY				(TERRITORIES_ST_N_AMERICA + 5)
#define ID_ONTARIO					(TERRITORIES_ST_N_AMERICA + 6)
#define ID_QUEBEC					(TERRITORIES_ST_N_AMERICA + 7)
#define ID_W_US						(TERRITORIES_ST_N_AMERICA + 8)
//SOUTH AMERICA
#define ID_ARGENTINA				(TERRITORIES_ST_S_AMERICA + 0)
#define ID_BRAZIL					(TERRITORIES_ST_S_AMERICA + 1)
#define ID_PERU						(TERRITORIES_ST_S_AMERICA + 2)
#define ID_VENEZUELA				(TERRITORIES_ST_S_AMERICA + 3)
//EUROPE
#define ID_GREAT_BRITIAN			(TERRITORIES_ST_EUROPE + 0)
#define ID_ICELAND					(TERRITORIES_ST_EUROPE + 1)
#define ID_N_EUROPE					(TERRITORIES_ST_EUROPE + 2)
#define ID_SCANDINAVIA				(TERRITORIES_ST_EUROPE + 3)
#define ID_S_EUROPE					(TERRITORIES_ST_EUROPE + 4)
#define ID_RUSSIA					(TERRITORIES_ST_EUROPE + 5)
#define ID_W_EUROPE					(TERRITORIES_ST_EUROPE + 6)
//AFRICA
#define ID_CONGO					(TERRITORIES_ST_AFRICA + 0)
#define ID_E_AFRICA					(TERRITORIES_ST_AFRICA + 1)
#define ID_EGYPT					(TERRITORIES_ST_AFRICA + 2)
#define ID_MADAGASCAR				(TERRITORIES_ST_AFRICA + 3)
#define ID_N_AFRICA					(TERRITORIES_ST_AFRICA + 4)
#define ID_S_AFRICA					(TERRITORIES_ST_AFRICA + 5)
//ASIA
#define ID_AFGHANISTAN				(TERRITORIES_ST_ASIA + 0)
#define ID_CHINA					(TERRITORIES_ST_ASIA + 1)
#define ID_INDIA					(TERRITORIES_ST_ASIA + 2)
#define ID_IRKUTSK					(TERRITORIES_ST_ASIA + 3)
#define ID_JAPAN					(TERRITORIES_ST_ASIA + 4)
#define ID_KAMCHATKA				(TERRITORIES_ST_ASIA + 5)
#define ID_MIDDLE_EAST				(TERRITORIES_ST_ASIA + 6)
#define ID_MONGOLIA					(TERRITORIES_ST_ASIA + 7)
#define ID_SIAM						(TERRITORIES_ST_ASIA + 8)
#define ID_SIBERIA					(TERRITORIES_ST_ASIA + 9)
#define ID_URAL						(TERRITORIES_ST_ASIA + 10)
#define ID_YAKUTSK					(TERRITORIES_ST_ASIA + 11)
//OCEANIA
#define ID_E_AUSTRALIA				(TERRITORIES_ST_OCEANIA + 0)
#define ID_INDONESIA				(TERRITORIES_ST_OCEANIA + 1)
#define ID_N_GUINEA					(TERRITORIES_ST_OCEANIA + 2)
#define ID_W_AUSTRALIA				(TERRITORIES_ST_OCEANIA + 3)
//card stuff
#define CARD_ID_SOLDIER				0
#define CARD_ID_HORSEMAN			1
#define CARD_ID_CANNON				2
#define CARD_ID_WILD				3
#define CARD_TERRITORY_NONE			OWNER_NONE
#define CARD_DISCARDED				-1
#define CARD_NUM_IN_SET				3
#define CARD_MAX_HAND				(CARD_NUM_IN_SET+2)
#define CARD_MAX_FR_OPPONENT		(CARD_MAX_HAND+1)
#define CARD_MIN_FR_OPPONENT		(CARD_MAX_HAND-1)
#define CARD_NUM_IN_DECK			44
#define CARD_NUM_IN_DECK_WO_WILD	(CARD_NUM_IN_DECK-2)
//set numbers
#define CARD_SET_ONE				1
#define CARD_SET_TWO				2
#define CARD_SET_THREE				3
#define CARD_SET_FOUR				4
#define CARD_SET_FIVE				5
#define CARD_SET_SIX				6
//troop bonuses from #set turned-in
#define BONUS_SET_ONE				4
#define BONUS_SET_TWO				6
#define BONUS_SET_THREE				8
#define BONUS_SET_FOUR				10
#define BONUS_SET_FIVE				12
#define BONUS_SET_SIX				15
#define BONUS_SET_AFTER_SIX			5
//battle stuff
#define dicesides					6
#define epicfail					1
#define minArmys					3
#define minTerri					11
#define ATK_MIN_TROOPS				2
#define ATK_LEAVE_TROOPS			1
//player stuff
#define TROOPS_PLAYERS_TWO			40
#define TROOPS_PLAYERS_THREE		35
#define TROOPS_PLAYERS_FOUR			30
#define TROOPS_PLAYERS_FIVE			25
#define TROOPS_PLAYERS_SIX			20
#define NUM_PLAYERS_TWO				2
#define NUM_PLAYERS_THREE			3
#define NUM_PLAYERS_FOUR			4
#define NUM_PLAYERS_FIVE			5
#define NUM_PLAYERS_SIX				6