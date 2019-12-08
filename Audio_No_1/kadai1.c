/***************************************************************************
○ ファイル名：kadai1.c
○ プログラム内容：読み込んだRAWファイルを時間反転して出力するプログラム

【注意】
	このプログラムは未完成である。
	各自で必要な部分を追記し本プログラムを完成させること

【ヒント】
	※ 追記しなければいけない箇所
	（１）入力信号の時間反転
	（２）gnuplotを用いて時間波形をグラフ表示するためのテキストファイル出力

○ コンパイル方法：ターミナル上で右のコマンドを入力「gcc -o kadai1 kadai1.c -lm」
○ 実行方法：「./kadai1 入力ファイル名 出力ファイル名」
○ 実行例：「./kadai1 music.vc music.inv」
	（ ※ music.vcの時間反転した結果をmusic.invに格納 ）

Copyright @ ASPL all rights reserved.
***************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include "lib.h"

int main( int argc, char **argv ){

	int i;         // ループカウンタ
	int dtSize;    // 入力音源のサンプル数

	short *dt_in;  // 入力音源格納用ポインタ
	short *dt_out; // 出力音源格納用ポインタ

	double *time;  // 時間情報格納用ポインタ


	/***************************入力データの読み込み***************************/
	//                                                                        //
	//  「入力音源：argv[ 1 ]」の中身が「dt_in」に格納される                  //
	//   入力ファイルのサンプル数が「dtSize」に格納される                     //
	//                                                                        //
	/**************************************************************************/
	dt_in = Read_Raw_File_Short( argv[ 1 ], &dtSize );

	// 出力音源の中身を格納するshort型配列のメモリを確保
	//( 2byte( short型 ) * 入力ファイルのサンプル数( dtSize ) )
	dt_out = Memory_Short( dtSize );

	/************* (課題) 入力信号の時間反転 **************/
	//                                                    //
	//         この部分のプログラムを各自で作成           //
	//                                                    //
	/******************************************************/
	for(i = 0; i < dtSize; i++)
		dt_out[i] = dt_in[dtSize - 1 - i];

	/***************************出力再生データの作成***************************/
	//                                                                        //
	//        「出力ファイル：argv[ 2 ]」に「dt_out」の中身が格納             //
	//                                                                        //
	/**************************************************************************/
	Write_Raw_File_Short( dt_out, argv[ 2 ], dtSize );

	// グラフ表示のための時間情報を格納するdouble型配列のメモリ確保
	time = Memory_Double( dtSize );
	for(int i = 0; i < dtSize; i++)
		time[i] = (double)i*(1.0 / 16000);

	/* (課題) gnuplotを用いた時間波形表示プログラムの作成 */
	//                                                    //
	//          この部分のプログラムを各自で作成          //
	//        ※ 横軸：時間(time), 縦軸：振幅(dt_out)     //
	//                                                    //
	/******************************************************/
	FILE *fpout;
	fpout = fopen("kadai1.dat", "w");
	if(fpout == NULL){
		fprintf(stderr, "FILE Open ERROR\n");
		exit(-1);
	}

	for(i = 0; i < dtSize; i++)
		fprintf(fpout, "%lf %d \n", time[i], dt_out[i]);
	fclose(fpout);

	// メモリ開放
	free( dt_in );
	free( dt_out );
	free( time );

	return( 0 );
}
