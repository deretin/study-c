/*=== puzmon5: バトルフィールドの実装 ===*/
/*** インクルード宣言 ***/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

/*** 列挙型宣言 ***/

// (a)属性
typedef enum Element {FIRE, WATER, WIND, EARTH, LIFE, EMPTY} Element;

/*** グローバル定数の宣言 ***/

// (b)属性別の記号
const char ELEMENT_SYMBOLS[EMPTY+1] = {'$','~','@','#','&', ' '};

// (c)属性別のカラーコード（ディスプレイ制御シーケンス用）
const char ELEMENT_COLORS[EMPTY+1] = {1,6,2,3,5,0};

// (d)バトルフィールドに並ぶ宝石の数
enum {MAX_GEMS = 14};

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

// (i)バトルフィールド
typedef struct BATTLE_FIELD {
  Party* pParty;
  Monster* pEnemy;
  Element gems[MAX_GEMS];
} BattleField;

/*** プロトタイプ宣言 ***/

int goDungeon(Party* pParty, Dungeon* pDungeon);
int doBattle(Party* pParty, Monster* pEnemy);
Party organizeParty(char* playerName, Monster* monsters, int numMonsters);
void showParty(Party* pParty);
void onPlayerTurn(BattleField* pField);
void doAttack(BattleField* pField);
void onEnemyTurn(BattleField* pField);
void doEnemyAttack(BattleField* pField);
void showBattleField(BattleField* pField);

// ユーティリティ関数
void printMonsterName(Monster* monster);
void fillGems(Element* gems);
void printGems(Element* gems);
void printGem(Element element);

/*** 関数宣言 ***/

// (1)ゲーム開始から終了までの流れ
int main(int argc, char** argv)
{
  srand((unsigned)time(NULL));

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

  // バトルフィールドの宝石スロットの準備と初期化
  BattleField field = {pParty, pEnemy};
  fillGems(field.gems);

  while(true) {
    onPlayerTurn(&field);
    if(pEnemy->hp <= 0) {           // 撃破判定
      printMonsterName(pEnemy);
      printf("を倒した！\n");
      return 1;
    }
    onEnemyTurn(&field);
    if(pParty->hp <= 0) {           // 敗北判定
      printf("%sは倒れた...\n", pParty->playerName);
      return 0;
    }
  }
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

// (6)プレイヤーターン
void onPlayerTurn(BattleField* pField)
{
  printf("\n【%sのターン】\n", pField->pParty->playerName);
  showBattleField(pField);
  doAttack(pField);
}

// (7)パーティの攻撃
void doAttack(BattleField* pField)
{
  pField->pEnemy->hp -= 80;
  printf("ダミー攻撃で80のダメージを与えた\n");
}

// (8)敵モンスターターン
void onEnemyTurn(BattleField* pField)
{
  printf("\n【%sのターン】\n", pField->pEnemy->name);
  doEnemyAttack(pField);
}

// (9)敵モンスターの攻撃
void doEnemyAttack(BattleField* pField)
{
  // ダミーのダメージ計算
  pField->pParty->hp -= 20;
  printf("20のダメージを受けた\n");
}

// (10)バトルフィールド情報の表示
void showBattleField(BattleField *pField)
{
  printf("------------------------------\n\n");
  printf("          ");
  printMonsterName(pField->pEnemy);
  printf("\n       HP= %4d / %4d\n", pField->pEnemy->hp, pField->pEnemy->maxhp);
  printf("\n\n");
  for(int i = 0; i < pField->pParty->numMonsters; i++) {
    printMonsterName(&(pField->pParty->monsters[i]));
    printf("  ");
  }
  printf("\n");
  printf("       HP= %4d / %4d\n", pField->pParty->hp, pField->pParty->maxHp);
  printf("------------------------------\n");
  printf(" ");
  for(int i = 0; i < MAX_GEMS; i++ ){
    printf("%c ", 'A'+i);
  }
  printf("\n");
  printGems(pField->gems);
  printf("------------------------------\n");
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

// (B)スロットをランダムな宝石で埋める
void fillGems(Element* gems)
{
  for(int i = 0; i < MAX_GEMS; i++) {
    gems[i] = rand() % EMPTY;
  }
}

// (C)スロットに並ぶ宝石を表示する
void printGems(Element* gems)
{
  for(int i = 0; i < MAX_GEMS; i++) {
    printf(" ");
    printGem(gems[i]);
  }
  printf("\n");
}

// (D)1個の宝石の表示
void printGem(Element e)
{
  printf("\x1b[30m");       // 黒文字
  printf("\x1b[4%dm", ELEMENT_COLORS[e]); // 属性色背景
  printf("%c", ELEMENT_SYMBOLS[e]);
  printf("\x1b[0m");        // 色指定解除
}
