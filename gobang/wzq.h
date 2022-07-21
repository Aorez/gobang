
/*
	�������˹����ܲ���
*/


//���������dim.h��
#if !defined(AFX_WZQ_H__211A6397_25EF_4A1B_8835_A743267879B1__INCLUDED_)
#define AFX_WZQ_H__211A6397_25EF_4A1B_8835_A743267879B1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif 
#include "CDC2.h"

/*
	�����Ƿ��ʤ�Ľṹ
*/
struct wzwin
{
	int		winner;	//0 û�л�ʤ 1 �� 2 ��
	int		nx1;	//������X���꿪ʼ((�ڼ��еڼ���))
	int		nx2;	//������X�������((�ڼ��еڼ���))
	int		ny1;	//������Y���꿪ʼ((�ڼ��еڼ���))
	int		ny2;	//������Y���꿪ʼ((�ڼ��еڼ���))
};

/*
	���������¼�Ľṹ
*/
struct wzsave
{
	bool	used;	//�Ƿ�ʹ��
	bool	color;	//��ɫ(false-����;true-����)
	int		ix;		//x����(�ڼ��еڼ���)
	int		iy;		//y����(�ڼ��еڼ���)
};

class wzq  
{
public:
	
	wzq(CDC2 *tqp,CDC2 *tqzh,CDC2 *tqzb,CDC2 *tmask,CDC2 *dead,CDC* dc,CDC2 *tqzhl,CDC2 *tqzbl);
	wzq();
	virtual ~wzq();
	void NewGame();//����Ϸ
	bool downzi(int nx,int ny);//�ⲿ���ô˺�������
	bool bewinner2(bool style,int nx,int ny);//�ж�ʤ��

	/*
		�����¼�ͻ��庯��
	*/
	bool goback();//����
	void setback(int nx,int ny,bool style);//��¼
	bool getbackble(){return nowd2<=0?false:true;}//�Ƿ���Ի���

	/*
		����
	*/
	CPoint AiGo(bool color);//�˹������ⲿ����

	/*
		��ʼ��
	*/
	void DrawQZ(int nx,int ny,bool style,bool drawMode);//������
	void SetDc(CDC2*tqp,CDC2*tqzh,CDC2*tqzb,CDC2*tmask,CDC2*dead,CDC*dc,CDC2 *tqzhl,CDC2 *tqzbl);//����DC
	void draw();						//�ػ���������

	/*
		���庯��
	*/
private:
	bool userAd(int nx,int ny);//��ɫ����
	bool userBd(int nx,int ny);//��ɫ����

//------------------------------AI�˹������ڲ�����------------------------------////
/**/private:																	/**/																
/**/	void fillin(bool color,bool player,bool type);							/**/
/**/	void setqx(int nx ,int ny,bool style,bool player,int st,bool type);		/**/
/**/	void setall();															/**/
/**/	void clear(bool style);													/**/
/**/	void checkgo(int x,int y,bool color,int nu,int inx,int iny);//Ԥ�⺯��	/**/
/**/	bool bejs(int nx, int ny);	/*++�˴���ӽ��ֿ���++*/					/**/
/**/	bool bj2(int x1,int y1,int x2,int y2,bool style);						/**/
/**/	char ntoc(char num,bool type,bool style);								/**/
/**/	CPoint getmax(bool color);												/**/
/**/	CPoint getbg(bool style);												/**/
/**/	int getaitype();														/**/
//AI								//��μ�"�������㷨"						/**/
///-----------------------------------------------------------------------------////


public:
			bool	firstgo;	//false:��true:��
			bool	secondgo;	//false:��true:��
			int		nturn;		//��ʾ��ǰ���ӵ�˳��(ֻ����ʹ��ģʽΪ2(���˶���ʱ����Ч)
								//1-������,2-������,0-��֪��˭��)
			wzwin	twinner;	//�ж��Ƿ���һ���Ѿ���ʤ�Ľṹ��Ա
			int		AItype;		//���ܵȼ�:0��Ԥ��6�� 1��Ԥ��10�� 2��Ԥ��16��
			int		Model;		//ģʽ0��->�� 1��->�� 2����
			bool	backable ;	//�Ƿ�������� 0=N 1=Y
			char map[15][15];				//�������̵�ͼ(0-ĳ���,1-����,2-����)
											//��ʾ������ĳһ��������Ƿ��Ѿ��¹���
			//���²������ڱ���������ʷ��¼
			int nowd2;						//��ʾ��ǰ�Ѿ����˶����ӵļ�����
			wzsave wzs[225];				//��Ӧ���̵�15��*15��
protected:

private:
			CDC2 *	qp;			//����dc
			CDC2 *	qzh;		//����dc
			CDC2 *	qzhl;		//����dc(��ԲȦ)
			CDC2 *	qzb;		//����dc
			CDC2 *	qzbl;		//����dc(��ԲȦ)
			CDC2 *	mask;		//����dc
			CDC2 *	dead;		//����
			CDC *	dc;			//����dc


			//���²�����Ԥ�����
			unsigned char user[15][15][4];	//������ֵ���������
			unsigned char pc[15][15][4];	//������ֵ���������

			unsigned char nicest2[15][15];	//��Ԥ������м�¼ĳһ�����Ӻ�Ľ��
			char trygo[15][15];				//��Ԥ��ǰ���ݵ�ǰ��������(map)
			bool dcseted;					//?
			int aitype2;					//Ԥ�ⲽ��


};

#endif // !defined(AFX_WZQ_H__211A6397_25EF_4A1B_8835_A743267879B1__INCLUDED_)
