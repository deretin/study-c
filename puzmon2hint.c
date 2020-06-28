/*=== puzmon2hint: 敵モンスター関連処理の実装 ===*/
/*** インクルード宣言 ***/

#include <stdio.h>

/*** 列挙型宣言 ***/

// (a)属性
// HINT: FIRE, WATERなどを含む列挙型Elementを定義する

/*** グローバル定数の宣言 ***/

// (b)属性別の記号
// HINT: '$'や'~'を含む配列ELEMENT_SYMBOLSを定義する

// (c)属性別のカラーコード（ディスプレイ制御シーケンス用）
const char ELEMENT_COLORS[EMPTY+1] = {1,6,2,3,5,0};

/*** 構造体型宣言 ***/

// (f) モンスター
// HINT: 各種のメンバを持つMonster型配列を定義する

// (g)ダンジョン
typedef struct DUNGEON {
  // HINT: ダンジョンでの登場モンスターを格納した配列の先頭アドレスを格納するメンバの宣言
  // HINT: 登場モンスターを格納した配列の要素数を格納するメンバ（不変）の宣言
} Dungeon;


/*** プロトタイプ宣言 ***/

int goDungeon(char* playerName, Dungeon* pDungeon);
int doBattle(char* playerName, Monster* pEnemy);

// ユーティリティ関数
// HINT: printMonsterName関数のプロトタイプ宣言

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

  // HINT: 要素数5のモンスター配列dungeonMonstersを宣言すると同時に、
  //       "スライム",    WATER, 100, 100, 10,  5
  //       などで中身を初期化。

  // HINT: Dungeon型の変数を宣言し、上記配列の先頭アドレスと要素数で初期化。

  // いざ、ダンジョンへ
  int winCount = goDungeon(argv[1], /* HINT: ダンジョンのアドレス */);

  // 冒険終了後
  if(winCount == /* HINT: ダンジョンのモンスター数 */) {
    printf("***GAME CLEAR!***\n");
  }  else {
    printf("***GAME OVER***\n");
  }
  printf("倒したモンスター数＝%d\n", winCount);
  return 0;
}

// (2)ダンジョン開始から終了までの流れ
int goDungeon(char* playerName, /* ダンジョンのアドレス */)
{
  printf("%sはダンジョンに到着した\n", playerName);

  // そのダンジョンでバトルを繰り返す
  int winCount = 0;
  // HINT: ダンジョンにいる全モンスターについて繰り返し {
  // HINT:     i番目のモンスターとdoBattle関数で戦い、結果の勝利数をwinCountに加える
  // HINT: }

  printf("%sはダンジョンを制覇した！\n", playerName);
  return winCount;
}

// (3)バトル開始から終了までの流れ
int doBattle(char* playerName, /* 戦う敵モンスターのアドレス */)
{
  // HINT: モンスター名を表示する関数を呼び出す;
  printf("が現れた！\n");

  // ダミーのため速攻倒す

  // HINT: モンスター名を表示する関数を呼び出す;
  printf("を倒した！\n");
  return 1;
}

/*** ユーティリティ関数宣言 ***/

// (A)モンスター名のカラー表示
void printMonsterName(/* モンスターのアドレス */)
{
  // HINT: char型変数symbolを宣言し、引数で指定されたモンスターの
  //       属性記号($や#など）を取得する。
  //       （ELEMENT_SYMBOLS配列から取り出す）

  // HINT: char型変数colorを宣言し、引数で指定されたモンスターの
  //       カラーコード(1や6など）を取得する。
  //       （ELEMENT_COLORS配列から取り出す）

  // HINT: ディスプレイ制御シーケンスを使い、文字色を変更
  // HINT: 「属性記号 モンスター名 属性記号」と表示
  // HINT: ディスプレイ制御シーケンスを使い、文字色を戻す
}
