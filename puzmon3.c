/*=== puzmon3: 味方パーティ関連処理の実装 ===*/
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

// (h)パーティ
typedef struct PARTY {
  char* playerName;
  Monster* monsters;
  const int numMonsters;
  const int maxHp;
  int hp;
  const int defense;
} Party;

/*** プロトタイプ宣言 ***/

int goDungeon(Party* pParty, Dungeon* pDungeon);
int doBattle(Party* pParty, Monster* pEnemy);
Party organizeParty(char* playerName, Monster* monsters, int numMonsters);
void showParty(Party* pParty);

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

  // パーティの準備
  Monster partyMonsters[] = {
    {"朱雀", FIRE,  150, 150, 25, 10},
    {"青龍", WIND,  150, 150, 15, 10},
    {"白虎", EARTH, 150, 150, 20,  5},
    {"玄武", WATER, 150, 150, 20, 15}
  };
  Party party = organizeParty(argv[1], partyMonsters, 4);

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
  int winCount = goDungeon(&party, &dungeon);

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
int goDungeon(Party* pParty, Dungeon* pDungeon)
{
  // プレイヤーHP/最大HPの算出とメッセージ表示
  printf("%sのパーティ(HP=%d)はダンジョンに到着した\n",pParty->playerName, pParty->hp);
  showParty(pParty);

  // そのダンジョンでバトルを繰り返す
  int winCount = 0;
  for(int i = 0; i < pDungeon->numMonsters; i++) {
    winCount += doBattle(pParty, &(pDungeon->monsters[i]));
    if(pParty->hp <= 0) {
      printf("%sはダンジョンから逃げ出した...\n", pParty->playerName);
      break;
    } else {
      printf("%sはさらに奥へと進んだ\n\n", pParty->playerName);
      printf("================\n\n");
    }
  }

  printf("%sはダンジョンを制覇した！\n", pParty->playerName);
  return winCount;
}

// (3)バトル開始から終了までの流れ
int doBattle(Party* pParty, Monster* pEnemy)
{
  printMonsterName(pEnemy);
  printf("が現れた！\n");

  // ダミーのため速攻倒す
  printMonsterName(pEnemy);
  printf("を倒した！\n");
  return 1;
}

// (4)パーティ編成処理
Party organizeParty(char* playerName, Monster* monsters, int numMonsters)
{
  int sumHp = 0;
  int sumDefense = 0;
  for(int i = 0; i < numMonsters; i++) {
    sumHp += monsters[i].hp;
    sumDefense += monsters[i].defense;
  }
  int avgDefense = sumDefense / numMonsters;

  Party p = {playerName, monsters, numMonsters, sumHp, sumHp, avgDefense};
  return p;
}

// (5)パーティ情報の表示
void showParty(Party* pParty)
{
  printf("＜パーティ編成＞----------\n");
  for(int i = 0; i < pParty->numMonsters; i++) {
    printMonsterName(&(pParty->monsters[i]));
    printf("  HP=%4d 攻撃=%3d 防御=%3d\n",
      pParty->monsters[i].hp,
      pParty->monsters[i].attack,
      pParty->monsters[i].defense
    );
  }
  printf("------------------------\n\n");
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
