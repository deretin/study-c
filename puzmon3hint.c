/*=== puzmon3hint: 味方パーティ関連処理の実装 ===*/
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
  // HINT: プレイヤー名を格納するメンバ
  // HINT: 味方モンスター配列の先頭アドレスを格納するメンバ
  // HINT: 味方モンスター数を格納するメンバ
  // HINT: 最大HP（不変）を格納するメンバ
  // HINT: HPを格納するメンバ
  // HINT: 防御力（不変）を格納するメンバ
} Party;

/*** プロトタイプ宣言 ***/

int goDungeon(Party* pParty, Dungeon* pDungeon);
int doBattle(Party* pParty, Monster* pEnemy);
// HINT: organizePartyのプロトタイプ宣言
// HINT: showPartyのプロトタイプ宣言

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
  // HINT: 味方モンスターを格納する要素数4のMonster配列 partyMonstersを定義し、
  //       "朱雀", FIRE,  150, 150, 25, 10
  //       などで初期化する。

  // HINT: organizeParty関数を呼び出し、結果のパーティ構造体を
  //       Party型変数partyで受け取る

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
  int winCount = goDungeon(/* パーティのアドレス */, &dungeon);

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
int goDungeon(/* パーティのアドレス */, Dungeon* pDungeon)
{
  // プレイヤーHP/最大HPの算出とメッセージ表示
  // HINT: 「○○のパーティ(HP=▲▲)はダンジョンに登場した」と表示する
  // HINT: showParty関数を呼び出し、パーティ情報を表示

  // そのダンジョンでバトルを繰り返す
  int winCount = 0;
  for(int i = 0; i < pDungeon->numMonsters; i++) {
    winCount += doBattle(/* パーティのアドレス */, &(pDungeon->monsters[i]));
    // HINT: もしパーティのHPが0以下なら... {
    // HINT:    「○○はダンジョンから逃げ出した」と表示してforループを途中脱出
    // HINT: } そうでなければ {
    // HINT:    「○○はさらに奥へと進んだ」と表示する
    // HINT: }
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
Party organizeParty(/* HINT: プレイヤー名 */, /* HINT: 味方モンスター配列の先頭アドレス */, /* HINT: 味方モンスターの数 */)
{
  // HINT: HPと防御力を集計していくための変数を初期値0で準備
  // HINT: 味方モンスターについて繰り返し {
  // HINT:     HP集計変数にi番目のモンスターのHPを追加
  // HINT:     防御力集計変数にi番目のモンスターの防御力を追加
  // HINT: }
  // HINT: 防御力集計をモンスター数で割って、平均防御力を算出

  // HINT: Party型変数を宣言し、プレイヤー名、味方モンスター配列の先頭アドレス、
  //       味方モンスター数、合計HP、合計HP、平均防御力で初期化する
  return /* HINT: モンスター型変数 */;
}

// (5)パーティ情報の表示
void showParty(/* パーティのアドレス*/)
{
  printf("＜パーティ編成＞----------\n");
  // HINT: 味方モンスターの数だけ繰り返す {
  // HINT:      i番目のモンスターの名前を表示
  // HINT:      i番目のモンスターのHP、攻撃、防御を表示
  // HINT: }
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
