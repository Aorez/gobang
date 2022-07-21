
/*
	五子棋人工智能操作
*/


//棋局声明在dim.h中
#if !defined(AFX_WZQ_H__211A6397_25EF_4A1B_8835_A743267879B1__INCLUDED_)
#define AFX_WZQ_H__211A6397_25EF_4A1B_8835_A743267879B1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif 
#include "CDC2.h"

/*
	保存是否获胜的结构
*/
struct wzwin
{
	int		winner;	//0 没有获胜 1 白 2 黑
	int		nx1;	//五连的X坐标开始((第几行第几列))
	int		nx2;	//五连的X坐标结束((第几行第几列))
	int		ny1;	//五连的Y坐标开始((第几行第几列))
	int		ny2;	//五连的Y坐标开始((第几行第几列))
};

/*
	保存下棋记录的结构
*/
struct wzsave
{
	bool	used;	//是否使用
	bool	color;	//颜色(false-白子;true-黑子)
	int		ix;		//x坐标(第几行第几列)
	int		iy;		//y坐标(第几行第几列)
};

class wzq  
{
public:
	
	wzq(CDC2 *tqp,CDC2 *tqzh,CDC2 *tqzb,CDC2 *tmask,CDC2 *dead,CDC* dc,CDC2 *tqzhl,CDC2 *tqzbl);
	wzq();
	virtual ~wzq();
	void NewGame();//新游戏
	bool downzi(int nx,int ny);//外部调用此函数下子
	bool bewinner2(bool style,int nx,int ny);//判断胜败

	/*
		下棋记录和悔棋函数
	*/
	bool goback();//悔棋
	void setback(int nx,int ny,bool style);//记录
	bool getbackble(){return nowd2<=0?false:true;}//是否可以悔棋

	/*
		操作
	*/
	CPoint AiGo(bool color);//人工智能外部控制

	/*
		初始化
	*/
	void DrawQZ(int nx,int ny,bool style,bool drawMode);//画棋子
	void SetDc(CDC2*tqp,CDC2*tqzh,CDC2*tqzb,CDC2*tmask,CDC2*dead,CDC*dc,CDC2 *tqzhl,CDC2 *tqzbl);//设置DC
	void draw();						//重画整个棋盘

	/*
		下棋函数
	*/
private:
	bool userAd(int nx,int ny);//黑色下子
	bool userBd(int nx,int ny);//白色下子

//------------------------------AI人工智能内部函数------------------------------////
/**/private:																	/**/																
/**/	void fillin(bool color,bool player,bool type);							/**/
/**/	void setqx(int nx ,int ny,bool style,bool player,int st,bool type);		/**/
/**/	void setall();															/**/
/**/	void clear(bool style);													/**/
/**/	void checkgo(int x,int y,bool color,int nu,int inx,int iny);//预测函数	/**/
/**/	bool bejs(int nx, int ny);	/*++此处添加禁手控制++*/					/**/
/**/	bool bj2(int x1,int y1,int x2,int y2,bool style);						/**/
/**/	char ntoc(char num,bool type,bool style);								/**/
/**/	CPoint getmax(bool color);												/**/
/**/	CPoint getbg(bool style);												/**/
/**/	int getaitype();														/**/
//AI								//请参见"五子棋算法"						/**/
///-----------------------------------------------------------------------------////


public:
			bool	firstgo;	//false:人true:机
			bool	secondgo;	//false:人true:机
			int		nturn;		//表示当前下子的顺序(只有在使用模式为2(两人对弈时才有效)
								//1-白子下,2-黑子下,0-不知道谁下)
			wzwin	twinner;	//判断是否有一方已经获胜的结构成员
			int		AItype;		//智能等级:0低预测6步 1中预测10步 2高预测16步
			int		Model;		//模式0人->机 1机->人 2对翌
			bool	backable ;	//是否允许悔棋 0=N 1=Y
			char map[15][15];				//储存棋盘地图(0-某点空,1-白子,2-黑子)
											//表示棋盘上某一个交叉点是否已经下过子
			//以下参数用于保存下棋历史记录
			int nowd2;						//表示当前已经下了多少子的计数器
			wzsave wzs[225];				//对应棋盘的15行*15列
protected:

private:
			CDC2 *	qp;			//棋盘dc
			CDC2 *	qzh;		//黑子dc
			CDC2 *	qzhl;		//黑子dc(带圆圈)
			CDC2 *	qzb;		//白子dc
			CDC2 *	qzbl;		//白子dc(带圆圈)
			CDC2 *	mask;		//屏蔽dc
			CDC2 *	dead;		//红子
			CDC *	dc;			//窗口dc


			//以下参数和预测相关
			unsigned char user[15][15][4];	//储存棋局的棋型数据
			unsigned char pc[15][15][4];	//储存棋局的棋型数据

			unsigned char nicest2[15][15];	//在预测过程中记录某一点落子后的结果
			char trygo[15][15];				//在预测前备份当前棋型数据(map)
			bool dcseted;					//?
			int aitype2;					//预测步数


};

#endif // !defined(AFX_WZQ_H__211A6397_25EF_4A1B_8835_A743267879B1__INCLUDED_)
