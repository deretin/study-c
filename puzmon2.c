/*=== puzmon2: 敵モンスター関連処理の実装 ===*/
/*** インクルード宣言 ***/

#include <stdio.h>

/*** 列挙型宣言 ***/

// (a)属性
typedef enum Element {FIRE, WATER, WIND, EARTH, LIFE, EMPTY} Element;

/*** グローバル定数の宣言 ***/

// (b)属性別の記号
const char ELEMENT_SYMBOLS[EMPTY+1] = {'$','~','@','#','&', ' '};

// (c)属性別のカラーコード（ディスプレイ制御シーケンス用）
const char ELEMENT_COLORS[EMPTY+1] = {1,6,2,3,5,0};

/*** 構造体型宣言 ***/

// (f) モンスター
typedef struct MONSTER {
  char* name;
  Element element;
  int maxhp;
  int hp;
  int attack;
  int defense;
} Monster;

// (g)ダンジョン
typedef struct DUNGEON {
  Monster* monsters;
  const int numMonsters;
} Dungeon;


/*** プロトタイプ宣言 ***/

int goDungeon(char* playerName, Dungeon* pDungeon);
int doBattle(char* playerName, Monster* pEnemy);

// ユーティリティ関数
void printMonsterName(Monster* monster);

/*** 関数宣言 ***/

// (1)ゲーム開始から終了までの流れ
int main(int argc, char** argv)
{
  if(argc != 2) {
    printf("エラー: プレイヤー名を指定して起動してください\n");
    return 1;
  }

  printf("*** Puzzle & Monsters ***\n");

  // ダンジョンの準備
  Monster dungeonMonsters[] = {
    {"スライム",    WATER, 100, 100, 10,  5},
    {"ゴブリン",    EARTH, 200, 200, 20, 15},
    {"オオコウモリ", WIND,  300, 300, 30, 25},
    {"ウェアウルフ", WIND,  400, 400, 40, 30},
    {"ドラゴン",    FIRE,  800, 800, 50, 40}
  };
  Dungeon dungeon = {dungeonMonsters, 5};

  // いざ、ダンジョンへ
  int winCount = goDungeon(argv[1], &dungeon);

  // 冒険終了後
  if(winCount == dungeon.numMonsters) {
    printf("***GAME CLEAR!***\n");
  }  else {
    printf("***GAME OVER***\n");
  }
  printf("倒したモンスター数＝%d\n", winCount);
  return 0;
}

// (2)ダンジョン開始から終了までの流れ
int goDungeon(char* playerName, Dungeon* pDungeon)
{
  printf("%sはダンジョンに到着した\n", playerName);

  // そのダンジョンでバトルを繰り返す
  int winCount = 0;
  for(int i = 0; i < pDungeon->numMonsters; i++) {
    winCount += doBattle(playerName, &(pDungeon->monsters[i]));
  }

  printf("%sはダンジョンを制覇した！\n", playerName);
  return winCount;
}

// (3)バトル開始から終了までの流れ
int doBattle(char* playerName, Monster* pEnemy)
{
  printMonsterName(pEnemy);
  printf("が現れた！\n");

  // ダミーのため速攻倒す
  printMonsterName(pEnemy);
  printf("を倒した！\n");
  return 1;
}

/*** ユーティリティ関数宣言 ***/

// (A)モンスター名のカラー表示
void printMonsterName(Monster* pMonster)
{
  char symbol = ELEMENT_SYMBOLS[pMonster->element];

  printf("\x1b[3%dm", ELEMENT_COLORS[pMonster->element]);
  printf("%c%s%c", symbol, pMonster->name, symbol);
  printf("\x1b[0m");
}
