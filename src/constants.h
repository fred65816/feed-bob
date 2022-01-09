// Constantes de niveau
#define LEVEL_FILENAME "../assets/level.lvl"
#define WALL_CHAR 'X'
#define BG_CHAR 'O'
#define TILE_BG "../assets/tile_background.png"
#define TILE_WALL "../assets/tile_wall.png"
#define TILE_WIDTH 16
#define TILE_HEIGHT 16
#define LEVEL_NUM_ROWS 49
#define LEVEL_NUM_COLS 64
#define LEVEL_WIDTH (LEVEL_NUM_COLS * TILE_WIDTH)
#define LEVEL_HEIGHT (LEVEL_NUM_ROWS * TILE_HEIGHT)
#define LEVEL_INIT_X 30
#define LEVEL_INIT_Y 660

// Constantes de menu
#define TITLE_FILENAME "../assets/title.png"
#define TITLE_WIDTH 744
#define TITLE_X ((LEVEL_WIDTH - TITLE_WIDTH) / 2)
#define TITLE_Y 10
#define PLAY_YES_FILENAME "../assets/play_yes.png"
#define PLAY_NO_FILENAME "../assets/play_no.png"
#define PLAY_WIDTH 400
#define PLAY_X ((LEVEL_WIDTH - PLAY_WIDTH) / 2)
#define PLAY_Y 400
#define QUIT_YES_FILENAME "../assets/quit_yes.png"
#define QUIT_NO_FILENAME "../assets/quit_no.png"
#define QUIT_WIDTH 400
#define QUIT_X ((LEVEL_WIDTH - QUIT_WIDTH) / 2)
#define QUIT_Y 500



// Constantes de beignes
#define DONUT_FILENAME "../assets/donut.png"
#define DONUT_NUM_MOVES 1
#define DONUT_NUM_FRAMES 32
#define DONUT_TOTAL_FRAMES (DONUT_NUM_MOVES * DONUT_NUM_FRAMES)
#define DONUT_MOVE_DURATION 1200
#define DONUT_BETWEEN_FRAME (DONUT_MOVE_DURATION / DONUT_NUM_FRAMES)
#define DONUT_AMOUNT 5
#define DONUT_ZONE_X 14
#define DONUT_ZONE_Y 38
#define DONUT_ZONE_WIDTH 100
#define DONUT_ZONE_HEIGHT 60
#define DONUT_SCALE 0.70
#define DONUT_SCALE_WIDTH (DONUT_ZONE_WIDTH * DONUT_SCALE)
#define DONUT_SCALE_HEIGHT (DONUT_ZONE_HEIGHT * DONUT_SCALE)
#define DONUT1_X 30
#define DONUT1_Y 92
#define DONUT2_X 30
#define DONUT2_Y 572
#define DONUT3_X 910
#define DONUT3_Y 62
#define DONUT4_X 910
#define DONUT4_Y 350
#define DONUT5_X 910
#define DONUT5_Y 702

// Constantes de joeur
#define PLAYER_FILENAME "../assets/player.png"
#define PLAYER_NUM_MOVES 6
#define PLAYER_NUM_FRAMES 32
#define PLAYER_TOTAL_FRAMES (PLAYER_NUM_MOVES * PLAYER_NUM_FRAMES)
#define PLAYER_MOVE_DURATION 480
#define PLAYER_BETWEEN_FRAME (PLAYER_MOVE_DURATION / PLAYER_NUM_FRAMES)
#define PLAYER_SPEED 5
#define PLAYER_JUMP_VELOCITY 15
#define PLAYER_SCALE 0.70
#define PLAYER_SPRITE_WIDTH 128
#define PLAYER_SPRITE_HEIGTH 128
#define PLAYER_ZONE_WIDTH 44
#define PLAYER_ZONE_HEIGHT 112
#define PLAYER_ZONE_X ((PLAYER_SPRITE_WIDTH / 2) - (PLAYER_ZONE_WIDTH / 2))
#define PLAYER_ZONE_Y (PLAYER_SPRITE_HEIGTH - PLAYER_ZONE_HEIGHT)

// Constantes de jeu
#define GAME_GRAVITY 0.45

// Constantes audio et Font
#define DONUT_SFX "../assets/donut.ogg"
#define LOST_SFX "../assets/lose.ogg"
#define FINAL_SONG "../assets/final.ogg"
#define AUDIO_BUFFER 4096
#define SAMPLE_RATE 22050
#define CHANNELS 2
#define AUDIO_TYPE AUDIO_S16SYS
#define FONT "../assets/font.ttf"

// Constante de timer
#define TIMER_FONT_SIZE 26