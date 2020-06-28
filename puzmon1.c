/*=== puzmon1: ゲーム全体の流れの実装 ===*/
/*** インクルード宣言 ***/

#include <stdio.h>

/*** 列挙型宣言 ***/

/*** グローバル定数の宣言 ***/

/*** 構造体型宣言 ***/

/*** プロトタイプ宣言 ***/

int goDungeon(char* playerName);
int doBattle(char* playerName, char* enemyName);

/*** 関数宣言 ***/

// (1)ゲーム開始から終了までの流れ
int main(int argc, char** argv)
{
  if(argc != 2) {
    printf("エラー: プレイヤー名を指定して起動してください\n");
    return 1;
  }

  printf("*** Puzzle & Monsters ***\n");

  // いざ、ダンジョンへ
  int winCount = goDungeon(argv[1]);

  // 冒険終了後
  if(winCount == 5) {
    printf("***GAME CLEAR!***\n");
  }  else {
    printf("***GAME OVER***\n");
  }
  printf("倒したモンスター数＝%d\n", winCount);
  return 0;
}

// (2)ダンジョン開始から終了までの流れ
int goDungeon(char* playerName)
{
  printf("%sはダンジョンに到着した\n", playerName);

  int winCount = 0;
  winCount += doBattle(playerName, "スライム");
  winCount += doBattle(playerName, "ゴブリン");
  winCount += doBattle(playerName, "オオコウモリ");
  winCount += doBattle(playerName, "ウェアウルフ");
  winCount += doBattle(playerName, "ドラゴン");
  printf("%sはダンジョンを制覇した！\n", playerName);
  return winCount;
}

// (3)バトル開始から終了までの流れ
int doBattle(char* playerName, char* enemyName)
{
  printf("%sが現れた！\n", enemyName);
  // ダミーのため速攻倒す
  printf("%sを倒した！\n", enemyName);
  return 1;
}

/*** ユーティリティ関数宣言 ***/
