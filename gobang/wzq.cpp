/*
	�������˹����ܲ���-ʵ�ֳ���
*/

#include "stdafx.h"
#include "CMyApp.h"
#include "wzq.h"
#include "dim.h"
#include "iostream.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

/*
	���캯��
*/
wzq::wzq(CDC2*tqp,CDC2*tqzh,CDC2*tqzb,CDC2*tmask,CDC2*dead,CDC*dc,CDC2 *tqzhl,CDC2 *tqzbl)
{
	SetDc(tqp,tqzh,tqzb,tmask,dead,dc,tqzhl,tqzbl);
}
/*
	��������
*/
wzq::~wzq(){}

/*
	Ĭ�Ϲ��캯��
*/
wzq::wzq()
{	
	wzq::dcseted=false; 
}


/*
	�����ӵĺ���.
	������
		int nx		����x����(���м���,�������߽�)
		int ny		����y����(���м���,�������߽�)
		bool style	����Ļ�ϻ������廹�ǰ��塣
					true -������
					flase-������
		boolean		drawModel		��draw�������û���UserAd,UserBd����
					true		draw��������

	��������:�����˺�ʱ,��һ����(����)����״������ȷ���

	ʹ�õ��ĺ���API(MFC��������)
	(1) BOOL BitBlt(int x, int y, int nWidth, int nHeight, CDC* pSrcDC,
		int xSrc, int ySrc, DWORD dwRop);
		�ú����ĸ��������ĺ��廹û��˵��
	�������ܣ��ú�����ָ����Դ���豸���������е������λ��(bit_block)ת�����Դ��͵�Ŀ���豸������
		������
		x��ָ��Ŀ�����������Ͻǵ�X���߼����ꡣ
		y��ָ��Ŀ������������Ͻǵ�Y���߼����ꡣ
		nWidth��ָ��Դ��Ŀ�����������߼���ȡ�
		nHeight��ָ��Դ��Ŀ�����������߼��߶ȡ�
		pSrcDC��ָ��Դ�豸���������
		xSrc��ָ��Դ�����������Ͻǵ�X���߼����ꡣ
		ySrc��ָ��Դ�����������Ͻǵ�Y���߼����ꡣ
		dwRop��ָ����դ�������롣��Щ���뽫����Դ�����������ɫ���ݣ������Ŀ������������ɫ������������������ɫ��

*/
void wzq::DrawQZ(int nx,int ny,bool style,bool drawModel=false)
{
	CDC2 * lcdc_qzh;
	CDC2 *lcdc_qzb;
	if (wzq::dcseted==false)return;
	if (nx>15||ny>15) return;		

	if (drawModel==true) {
		//�����draw��������,��ʹ�ò���Ȧ������
		lcdc_qzh = qzh;
		lcdc_qzb = qzb;
	}
	else {
		//����Ƿ�draw��������,��ʹ�ô�Ȧ������
		lcdc_qzh = qzhl;
		lcdc_qzb = qzbl;

	}

	if (style==false )		//����
	{
		//��ʹ�ñ�����ɫ����
		dc->BitBlt(nx*29+7,ny*29+7,28,28,mask,0,0,MERGEPAINT);
		//��������(ʵ������������*29+7,28�����ӵĸ߶ȺͿ��)
		dc->BitBlt(nx*29+7,ny*29+7,28,28,lcdc_qzb,0,0,SRCAND);
	}
	else		//����
	{
		//��ʹ�ñ�����ɫ����
		dc->BitBlt(nx*29+7,ny*29+7,28,28,mask,0,0,MERGEPAINT);
		//��������(ʵ������������*29+7,28�����ӵĸ߶ȺͿ��)
		dc->BitBlt(nx*29+7,ny*29+7,28,28,lcdc_qzh,0,0,SRCAND);
	}

	//������һ�µ�����Ϊ������ɫ
	int li_LastXY = wzq::nowd2-1;
	if (li_LastXY>=0 && !(drawModel==true)) {
		int li_LastX = wzq::wzs[li_LastXY].ix;
		int li_LastY = wzq::wzs[li_LastXY].iy;
		if (wzq::wzs[li_LastXY].color == false) {		//��һ���ǰ���
			//��ʹ�ñ�����ɫ����
			dc->BitBlt(li_LastX*29+7,li_LastY*29+7,28,28,mask,0,0,MERGEPAINT);
			//��������(ʵ������������*29+7,28�����ӵĸ߶ȺͿ��)
			dc->BitBlt(li_LastX*29+7,li_LastY*29+7,28,28,qzb,0,0,SRCAND);
		}
		else if (wzq::wzs[li_LastXY].color == true) {	//��һ���Ǻ���
			//��ʹ�ñ�����ɫ����
			dc->BitBlt(li_LastX*29+7,li_LastY*29+7,28,28,mask,0,0,MERGEPAINT);
			//��������(ʵ������������*29+7,28�����ӵĸ߶ȺͿ��)
			dc->BitBlt(li_LastX*29+7,li_LastY*29+7,28,28,qzh,0,0,SRCAND);
		}
	}

}

/*
	����DC,�����DC��һ��ָ���������
*/
void wzq::SetDc(CDC2 * tqp,CDC2 * tqzh,CDC2 * tqzb,CDC2 * tmask,CDC2 * dead,CDC * dc,CDC2 * tqzhl,CDC2 * tqzbl)//����DC
{
	wzq::mask =tmask;	//����DC
	wzq::qp =tqp;		//����DC
	wzq::qzb =tqzb;		//������DC
	wzq::qzbl = tqzbl;	//������DC(��ԲȦ)
	wzq::qzh =tqzh;		//������DC
	wzq::qzhl =tqzhl;		//������DC(��ԲȦ)
	wzq::dc =dc;		//����DC
	wzq::dead=dead;		//����ɫ���ӵ�DC
	wzq::dcseted=true; 
}

/*
	��ʼ����Ϸ�ĺ���
*/
void wzq::NewGame()
{

	if (wzq::dcseted==false)	return;

	/*
		�ݳ�ʼ��������Ҫ������
		(1) �洢��ֵ���ά����user����Ϊ""(255)
		(2) �洢��ֵ���ά����pc����Ϊ""(255)
		(3) ����������ÿ�����Ƿ��¹����ӵĶ�ά����wzs���
		(4) ���洢�����̵�ͼ�Ķ�ά����map����Ϊ''(255)
	*/
	for(int i1=0 ; i1<=14;i1++)
	{
		for(int i2=0 ; i2<=14;i2++)
		{
			//��ʼ��(4)
			map[i1][i2]=0;
			for(int i3=0 ; i3<=3;i3++)
			{
				//��ʼ��(1)
				user[i1][i2][i3]=255;
				//��ʼ��(2)
				pc[i1][i2][i3]=255;

			}
		}
	}

	//��ʼ��(3)
	for (int ix=0;ix<225;ix++)
	{
		wzq::wzs[ix].used=false; 
	}

	/*
		������
	*/
	//ȡ����DC�ĳߴ�,��Ҫ�ǻ�ȡ����DC�ĸ߶ȺͿ��
	CSize x=qp->GetSize();
	//���ô���DC��BitBlt������������DC
	dc->BitBlt(0, 0,x.cx,x.cy,qp,0,0,SRCCOPY);//������
	//���ó�Ա������ʾû����һ����ʤ�������Ա������ÿ�����Ӻ����Ҫ�����ж�
	wzq::twinner.winner=0;  
	//
	wzq::nturn=0; 
	//�����Ƿ���Ի���
	wzq::nowd2 =0;

	/*
		���µ��ú���
		����ǲ���ģʽ�ǻ������£�������Զ���һ������,λ�����ڵ�7�е�7��(�������߽��ϵ���һ��)
	*/
	if (wzq::Model==1)
	{
		userBd(7,7);
	} 
}


/*
	�ػ��������(���̺��Ѿ��µĺ��ӺͰ���)�ĺ���
	˵��:
		�ں����л���Ҫ�ж�5���ǳ��Ǹ�������ʵ������bewinner2�����б���5���ķ��򼴿�.
		�������Լ򻯺���
*/
void wzq::draw()//�ػ�
{
	//δ���ô���DC���˳�	
	if (wzq::dcseted==false)return;

	//������(������DC�еõ����̵ĸ߶ȺͿ��)
	CSize x=qp->GetSize() ;
	dc->BitBlt(0, 0,x.cx,x.cy,qp,0,0,SRCCOPY);

	//������
	for(int i1=0 ; i1<15;i1++)
	{
		for(int i2=0 ; i2<15;i2++)
		{
			//���ĳһ������Ѿ����˰��ӣ���������ϸõ㴦������
			if (map[i1][i2]==1){this->DrawQZ(i1,i2,false,true);}
			//���ĳһ������Ѿ����˺��ӣ���������ϸõ㴦������
			if (map[i1][i2]==2){this->DrawQZ(i1,i2,true,true);}	
		}
	}
	
	/*
		�������Ƿ��Ѿ���һ��Ӯ��,����Ѿ���һ��Ӯ�ˣ���
		ʹ�ú��Ӵ���ԭ��λ�õ�����(���ܺ���)
	*/
	if (wzq::twinner.winner!=0)		//1-��ʤ;2-��ʤ
	{
		/*
			���ʤ��һ�����ӵ����з�ʽ���ܹ��ķ�����8�֣�
				y����,x����		������0�ȷ�������һ��
				x����,y����		������45�ȷ�������һ��
				x����,y����		������90�ȷ�������һ��
				x����,y����		������135�ȷ�������һ��
				y����,x��С		������180�ȷ�������һ��
				x��С,y��С		������225�ȷ�������һ��
				x����,y��С		������270�ȷ�������һ��
				x����,y����		������315�ȷ�������һ��
		*/
		int x1=wzq::twinner.nx1;	//5���Ŀ�ʼ����(x)
		int y1=wzq::twinner.ny1;	//5���Ŀ�ʼ����(y)
		int xj;						//5����x�������ӷ���
		int yj;						//5����y�������ӷ���

		//�ж�5����x�������ӷ���
		if(wzq::twinner.nx2-wzq::twinner.nx1>0)
			{
				xj=1;				//X��������
			}
		else {
				if (wzq::twinner.nx2-wzq::twinner.nx1==0)
					{
						xj=0;		//X���겻��
					}
				else
					{
						xj=-1;		//X�����С
					}

			}

		//�ж�5����y�������ӷ���
		if(wzq::twinner.ny2-wzq::twinner.ny1>0)
			{
				yj=1;				//Y��������
			}
		else
			{
				if (wzq::twinner.ny2-wzq::twinner.ny1==0)
					{
						yj=0;		//Y���겻��
					}
				else
					{
						yj=-1;		//Y�����С
					}

			}

		/*
			����5���ĵط��ú��Ӵ���ԭ��λ�õ�����(���ܺ���)
			Ϊ��ͳһ��Ҳ�����޸�DrawQZ�����ڸú����л�����,������øú���
		*/
		for (int ii=1; ii<=5 ; ii++)		//ii��ѭ��������û��ʲô�ô�
			{

				//�Ȳ���ԭ��������
				dc->BitBlt(x1*29+7,y1*29+7,28,28,mask,0,0,MERGEPAINT);
				//��������
				dc->BitBlt(x1*29+7,y1*29+7,28,28,dead,0,0,SRCAND);
				//5����x����仯
				x1+=xj;
				//5����y����仯
				y1+=yj;
			}
		//�����ӽ���
	}
	
}  

/*
	(private����)��ɫ����,����:
		nx-���ӵ�x����(���м���)
		ny-���ӵ�y����(���м���)
	��Ҫ�����괦�¹������ӣ���������
*/
bool wzq::userAd(int nx,int ny)
{
	//δ���ô���DC���˳�	
	if (wzq::dcseted==false)return false;

	if (map[nx][ny]==0)			//�õ�û���¹���
		{
			map[nx][ny]=1;		//���øõ��¹������ǰ���
			DrawQZ(nx,ny,false);//�ڸ����괦������
			return true;
		}
	else		//�õ��Ѿ�������
		{
			return false;
		}
}

/*
	(private����)��ɫ���ӣ�����:
		nx-���ӵ�x����(���м���)
		ny-���ӵ�y����(���м���)
	��Ҫ�����괦�¹������ӣ���������
*/
bool wzq::userBd(int nx,int ny)
{
	//δ���ô���DC���˳�	
	if (wzq::dcseted==false)return false;

	if (map[nx][ny]==0)			//�õ�û���¹���
		{
			map[nx][ny]=2;		//���øõ��¹������Ǻ���
			DrawQZ(nx,ny,true); //�ڸ����괦������
			return true;
		}
	else
	{
		return false;
	}
}

/*
	�ж�ʤ��,�ж��������Ƿ���5������>5��,����:
		style
			false		����Ƿ����ʤ
			true		����Ƿ����ʤ
		nx,ny	��ǰ�������(���м���)���ӵ�ǰ�㿪ʼ,��8�������ж��������Ƿ���5������>5��
			������0��������һ��
			������45�ȷ�������һ��
			������90�ȷ�������һ��
			������135�ȷ�������һ��
			������180�ȷ�������һ��
			������225�ȷ�������һ��
			������270�ȷ�������һ��
			������315�ȷ�������һ��
	����ֵ:
		false		û��5��
		true		��5��
	��������:
		ֻ�ܹ��ж�5��,�����ж�6������7��.....
*/		
bool wzq::bewinner2(bool style,int nx,int ny)
{
	int tx1=0,tx2=0,ty1=0,ty2=0;
	int yx1=0,yx2=0,yy1=0,yy2=0;

	//st=1 ��ʾ����		st=2��ʾ����
	int st=(int)style+1;

	/*
		�ӵ�ǰ�����������Ƿ񳬹�5�����ϵ�����ָ������ɫ(���ӻ��ߺ���)
			nx-5~nx+5	y����			�����x�����Ƿ���5�����ϵ�������һ��
			ny-5~ny+5	x����			�����x�����Ƿ���5�����ϵ�������һ��
			ny-5~ny+5	ny-5~ny+5(x,yͬʱ���Ӻͼ�С)		
				�����45��(225)�����Ƿ���5�����ϵ�������һ��
			ny-5~ny+5	ny-5~ny+5(x,y�෴���Ӻͼ�С)		
				�����135��(315)�����Ƿ���5�����ϵ�������һ��

	*/

	for (int x1=-5 ; x1<= 5 ; x1++)	//�Ե�ǰ��Ϊ���ĵ㣬���ǰ��5����
	{
		//���x����
		if (map[nx+x1][ny]==st)		
		{
			//��ʾx������ͬ��ɫ�ļ�����+1
			tx1++;
			if (tx1==1)	yx1=x1;		//5�������Ŀ�ʼX����(y������ͬ)

			if (tx1>=5)				//��x������5��������һ��
			{
				twinner.winner =st;

				//����5����x���������Ŀ�ʼ����
				twinner.nx1= nx+yx1;
				twinner.ny1 =ny;
				//����5����x���������Ľ�������
				twinner.nx2 =nx+yx1+5;
				twinner.ny2 =ny;
				return true;
			}
		}
		else 
		{
			//�ڸ÷�������һ���ӵ���ɫ��Ҫ�ж��ӵ���ɫ��һ��ʱtx1������������¼���
			tx1=0;
		}

		//���Y����
		if (map[nx][ny+x1]==st)
		{
			//��ʾy������ͬ��ɫ�ļ�����+1
			ty1++;
			if (ty1==1)	yy1=x1;		//5�������Ŀ�ʼy����(x������ͬ)

			if (ty1>=5)				//��x������5��������һ��
				{
					twinner.winner =st;
					//����5����y���������Ŀ�ʼ����
					twinner.nx1= nx;
					twinner.ny1 =ny+yy1;
					//����5����y���������Ľ�������
					twinner.nx2 =nx;
					twinner.ny2 =ny+yy1+5;
					return true;
				}

		}
		else 
		{
			//�ڸ÷�������һ���ӵ���ɫ��Ҫ�ж��ӵ���ɫ��һ��ʱty1������������¼���
			ty1=0;
		}

		//���45�ȷ���
		if (map[nx+x1][ny+x1]==st)
		{
			//��ʾ45�ȷ�����ͬ��ɫ�ļ�����+1
			tx2++;

			if (tx2==1)	yx2=x1;		//5�������Ŀ�ʼ����
			if (tx2>=5)				//��45�ȷ�����5��������һ��
			{
				twinner.winner =st;
				//����5����45�ȷ��������Ŀ�ʼ����
				twinner.nx1= nx+yx2;
				twinner.ny1 =ny+yx2;
				//����5����45�ȷ��������Ľ�������
				twinner.nx2 =nx+yx2+5;
				twinner.ny2 =ny+yx2+5;
				return true;
			}
		}
		else
		{
			//�ڸ÷�������һ���ӵ���ɫ��Ҫ�ж��ӵ���ɫ��һ��ʱtx2������������¼���
			tx2=0;
		}

		//���135�ȷ���
		if (map[nx+x1][ny-x1]==st)
		{
			//��ʾ135�ȷ�����ͬ��ɫ�ļ�����+1
			ty2++;
			if (ty2==1)	yy2=x1;
			if (ty2>=5)				//��135�ȷ�����5��������һ��
			{
				twinner.winner =st;
				//����5����135�ȷ��������Ŀ�ʼ����
				twinner.nx1= nx+yy2;
				twinner.ny1 =ny-yy2;
				//����5����135�ȷ��������Ľ�������
				twinner.nx2 =nx+yy2+5;
				twinner.ny2 =ny-yy2-5;
				return true;
			}
		}
		else 
		{
			//�ڸ÷�������һ���ӵ���ɫ��Ҫ�ж��ӵ���ɫ��һ��ʱty1������������¼���
			ty2=0;
		}
	}
	return false;
}

/*
	�ṩ����������õ����Ӻ�����������
		nx-���ӵ�x����(���м���)
		ny-���ӵ�y����(���м���)
	����ֵ:�����Ƿ�ɹ�

	˵����
		ÿ��һ���Ӻ󣬾���Ҫִ��һ�²���:
			(1) �ж��Ƿ��ʤ
				bewinner2(��־(false-����,true-����),x����,y����)
			(2) ��¼�����¼
				setback(x����,y����,��־(false-����,true-����) )
*/
bool wzq::downzi(int nx,int ny)
{
	bool turnback;

	//���ӵ�����㷶Χ����0-14��Χ��
	if (nx<0||nx>14||ny<0||nx>14) return false;
	if (wzq::nturn==-1)return false;

	/*
		������Ƿ���ݲ�ͬ��ʹ��ģʽ���в�ͬ�Ĵ���
			���˶���		��������˳����������(���漰���˹�����)
			�����˺�		���°��ӣ����������Զ���ӦӦ���������º���
			���Ȼ���		���º��ӣ����������Զ���ӦӦ���������°���
	*/

	//ʹ��ģʽ�����˶���
	if (wzq::Model==2 )
	{
		if (wzq::nturn==1)				//��ǰӦ���ǰ�����
		{
			turnback=userAd(nx,ny);		//��ָ������һ������

			//��ָ������һ�����Ӻ����Ƿ����ʤ��
			if (bewinner2(false,nx,ny)==true)
				wzq::nturn=-1; 
			wzq::nturn =turnback?0:1;
			//��¼������ʷ
			setback(nx,ny,false);
		}
		else							//��ǰӦ���Ǻ�����
		{
			turnback=userBd(nx,ny);		//��ָ������һ������

			//��ָ������һ�����Ӻ����Ƿ����ʤ��
			if(bewinner2(true,nx,ny)==true)wzq::nturn =-1;

			wzq::nturn =turnback?1:0;
			//��¼������ʷ
			setback(nx,ny,true);
		}
	}
	else if (wzq::Model==1)
	//ʹ��ģʽ�ǻ����˺�(��������,�����һ������)
	{
		//�׷���ָ�������괦��һ����
		if (userAd(nx,ny)==false)	return false;

		//��ָ������һ�����Ӻ����Ƿ����ʤ��
		if(bewinner2(false,nx,ny)==true)wzq::nturn =-1;
		//��¼������ʷ
		setback(nx,ny,false);

		/*
			���³����ǻ������Զ���Ӧ(��������)
		*/
		CPoint aigo=wzq::AiGo(true);		//����ֵ��Ӧ�����Ǹ���������(���м���)
		//�ڻ�����Ӧ������λ�������
		userBd(aigo.x,aigo.y);
		//��¼������ʷ
		setback(aigo.x,aigo.y,true);

		//��ָ������һ�����Ӻ����Ƿ����ʤ��
		if(bewinner2(true,aigo.x,aigo.y)==true) wzq::nturn =-1;
	}
	else if (wzq::Model==0)
	//ʹ��ģʽ�����Ȼ���(��������,�����һ������)
	{
		//�ڷ���ָ�������괦��һ����
		if (userBd(nx,ny)==false)return false;

		//��ָ������һ�����Ӻ����Ƿ����ʤ��
		if(bewinner2(true,nx,ny)==true)wzq::nturn =-1;
		//��¼������ʷ
		setback(nx,ny,true);

		/*
			���³����ǻ������Զ���Ӧ(��������)
		*/

		CPoint aigo=wzq::AiGo(false);	;		//����ֵ��Ӧ�����Ǹ���������(���м���)
		//�ڻ�����Ӧ������λ�������
		userAd(aigo.x,aigo.y);
		//��¼������ʷ
		setback(aigo.x,aigo.y,false);

		//��ָ������һ�����Ӻ����Ƿ����ʤ��
		if(bewinner2(false,aigo.x,aigo.y)==true)wzq::nturn =-1;
	}

	//MessageBox(GetActiveWindow(),wzq::nowd2,"��ʾ",MB_OK);
	
	return turnback;
}

/*
	���庯��.
	����ֵ:�����Ƿ�ɹ�

*/
bool wzq::goback()
{	
	//��ǰ���������,����
	if (wzq::getbackble==false) return false; 

	/*
		��ʾ�Ѿ����˶����ӵļ�������1,�����������setback�������Ѿ���1��
		����Ҫ�ȼ��������ű�ʾҪ�ڵ���һ����
	*/
	wzq::nowd2--;

	/*
		����������˶��ģ�������һ��
		������˺ͻ������ģ����˻����ͬʱ������Ҳ�Զ�����һ��
	*/
	if (wzq::Model==2)		//�����˶���
	{
		//�ڸ��������map�����б�ʾ�Ѿ��¹����������
		map[wzq::wzs[nowd2].ix][wzq::wzs[nowd2].iy]=0;

		//?(��������ȷ��ʾ˳��)
		wzq::nturn= wzq::wzs[nowd2].color ;

		wzq::wzs[nowd2].used=false;		//����õ���������ʷ��¼�е�����

		/*
			������DC�е�ȡ��һ�����򸲸�Ŀǰ�������ָ��λ�õ�����
			Ҳ���Կ���ʹ������DC����������
		*/
		wzq::dc->BitBlt(wzq::wzs[nowd2].ix*29+7,wzq::wzs[nowd2].iy*29+7,28,28,
			wzq::qp,wzq::wzs[nowd2].ix*29+7,wzq::wzs[nowd2].iy*29+7,SRCCOPY);
	}
	else
	{
		//�ڸ��������map�����б�ʾ�Ѿ��¹����������
		map[wzq::wzs[nowd2].ix][wzq::wzs[nowd2].iy]=0;
		wzq::wzs[nowd2].used=false;
		//������DC�е�ȡ��һ�����򸲸�Ŀǰ�������ָ��λ�õ�����
		wzq::dc->BitBlt(wzq::wzs[nowd2].ix*29+7,wzq::wzs[nowd2].iy*29+7,28,28,
			wzq::qp,wzq::wzs[nowd2].ix*29+7,wzq::wzs[nowd2].iy*29+7,SRCCOPY);

		/*�ڻ����µ�һ��*/
		wzq::nowd2--;				//��ʾ�����¼�ļ�������1
		map[wzq::wzs[nowd2].ix][wzq::wzs[nowd2].iy]=0;
		wzq::wzs[nowd2].used=false;
		wzq::dc->BitBlt(wzq::wzs[nowd2].ix*29+7,wzq::wzs[nowd2].iy*29+7,28,28,
			wzq::qp,wzq::wzs[nowd2].ix*29+7,wzq::wzs[nowd2].iy*29+7,SRCCOPY);
	}

	//����Ѿ��жϵ�ǰ��ĳһ���Ѿ�Ӯ�ˣ��������Ӯ��������������
	if (wzq::twinner.winner!=0) 
	{
		wzq::twinner.winner =0;		//û����һ��Ӯ
		/*
			���»�����(��Ϊ�������һ���Ѿ�Ӯ�˻�,��������һ����
				���Ѿ�����˺��ӣ�����Ҫ���»�����
				���߽����Ӳ������±�ɰ��ӻ��ߺ���.
		*/
		wzq::draw();		//��ȫ�����ɲ���ԲȦ����״
	}

	//
	if (wzq::nturn ==-1) wzq::nturn=0;
	return false;
}


/*
	���ֿ��ƺ���,��ʱû�����ý���
*/
bool wzq::bejs(int nx,int ny)
{
	return false;
}


/*
	���ݵ�ǰ�������д��������(
		����ʹ�õ�д��pc�����ά������
		�˷�д��user�����ά������)
	����˵��:
		color		���ӻ��ǰ���
		player		�����������˷�(false-������;true-�˷�)
		type		?(����ʱ��true��false����ֵ)
	˵����
		��ν�������ݾ� �����������δ���ӵĵط����ӣ������ڸ��������϶���ֵ�Ӱ��ֵ
		(Ӱ��ֵ�μ�dim.h����ֵԽСԽ��Ҫ)	
*/
void wzq::fillin(bool color,bool player,bool type)
{
	int ix,iy;
	for (ix=0 ;ix<=14;ix++)
	{
		for (iy=0 ;iy<=14;iy++)
		{
			if (map[ix][iy]==0)				//ֻ��������δ���ӵĵط��Ž��м��㡣
			{
			
				/*
					�ֱ������ĳһ��λ��(nx,ny)����һ�Ӻ�,��4�������϶���ֵ�Ӱ��,��4������ֱ�Ϊ:
							im=0	x����(��setqx���������������չΪ0�Ⱥ�180����������)
							im=1	y����(��setqx���������������չΪ90�Ⱥ�270����������)
							im=2	45�ȷ���(��setqx���������������չΪ45�Ⱥ�225����������)
							im=3	135�ȷ���(��setqx���������������չΪ135�Ⱥ�315����������)
				*/
				for (int im=0 ; im<=3 ; im++)
				{
					setqx(ix,iy,color,player,im,type);
				}
			}
		}
	}
}

/*
	��������:		����ĳһ�������������е�ֵ(��ǰ����е���Ҫ����(���ȼ���))
	����˵��:
		nx,ny		����������(�õ���δ����ӵĵ�ż�����������,���򲻼���)
		style		���ӻ��ǰ���
		player		?(���������������һ������������)
		st			Ԥ�ⷽ��,���庬��Ϊ:
					0	x����(��setqx���������������չΪ0�Ⱥ�180����������)
					1	y����(��setqx���������������չΪ90�Ⱥ�270����������)
					2	45�ȷ���(��setqx���������������չΪ45�Ⱥ�225����������)
					3	135�ȷ���(��setqx���������������չΪ135�Ⱥ�315����������)

		type		?(����ʱ��true��false����ֵ)
	����ֵ: ��

*/
void wzq::setqx(int nx ,int ny,bool style,bool player,int st,bool type)
{
	bool ok=true;
	int ia,ib;
	int ix,iy;
	int i2,i2j;		//x�����y�����������
	int tem1,tem2;
	int x;
	int i3;
	int m1,m3;
	int i;
	int wx=nx,wy=ny,tem3=0;


	switch (st)
	{
		case 0:					//x����(�з���)
			i2=1,i2j=0;break;		
		case 1:					//y����(�з���)
			i2=0,i2j=1;break;
		case 2:					//45�ȷ���
			i2=1,i2j=1;break;
		case 3:					//135�ȷ���
			i2=1,i2j=-1;break;
	}

	unsigned char temp3[15]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
	unsigned char temp4[15]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};

begin:
	if (map[wx][wy]!=0)	return;		//����õ��Ѿ�������ˣ��򷵻�
	i3=0;
	ix=i2;			//x����
	iy=i2j;			//y����
	ia=1,ib=1;

	/*
		�ڼ�����������ʱ,��X����(st=0)Ϊ��˵��,������������
	*/
	/*
	if (nx==6 && ny==8 && st==1) {
		AfxMessageBox("123");
	}
	*/


	//���㵱ǰ������(�Ե�ǰ��Ϊ����,x������٣�y�������)�ж��ٸ���Ҫ���������ɫһ������//
	x=map[wx-ix][wy-iy];
	while(!(x!=(int)style+1||wx-ix<0||wy-iy<0))
	{
		ia++;
		ix+=i2;
		iy+=i2j;
		x=map[wx-ix][wy-iy];

	} 

	//x�����y��������������¸�ֵ
	ix=i2,iy=i2j;

	//���㵱ǰ������(�Ե�ǰ��Ϊ����,x�������ӣ�y��������)�ж��ٸ���Ҫ���������ɫһ������//
	x=map[wx+ix][wy+iy];
	while(!(x!=(int)style+1||wx+ix>14||wy+iy>14))
	{
		ix+=i2;
		iy+=i2j;
		ib++;	
		x=map[wx+ix][wy+iy];
	} 


	/*
		��ǰ����Χû����ɫ��ͬ����,�򽫵�ǰ��ֱ�������һ�����
	*/
	if (ib==1&&ia==1)		
	{
		
		if (tem3==0)		//�жϵ�ǰ���ұ��ӵ����
		{
			wx+=i2,wy+=i2j;	
			tem3=1;
			//MessageBox(GetActiveWindow(),"��ǰ�����H0H","��ʾ",MB_OK);
			goto begin;
		}
		else				//�жϵ�ǰ������ӵ����
		{
			if (tem3==1)	
			{
				wx-=i2*2,wy-=i2j*2;
				tem3=2;
				goto begin;
			}
			else		//�����ǰ���������߾��ǿջ���û�к��жϵ���ɫ��ͬ����,��չ���õ��Ԥ������(�˳�)
			{
				if (tem3==2) return;
			}
		}
		
	}

	ix=0,iy=0;


	//�ֲ�ͬ��������ж����жϵ����Ӻ���ֵ�״̬
	switch (st)
	{
		case 0:			//x����
			{
				m1=(ia!=1&&ib==1);	//m1��ʾ��ǰ���������ͬ��ɫ����>1��,�ұ�û����ͬ��ɫ����
				m3=(ib!=1&&ia==1);	//m3��ʾ��ǰ���ұ�����ͬ��ɫ����>1��,���û����ͬ��ɫ����

				/*
					���㵱ǰ����ߺ��ұߵ��������������temp3��temp4�����У���Ϊ�������:
						(1) ���ia��ib������1,�����жϵ����ȡiaλ,�ұ�ȡibλ,temp3��temp4������������ͬ
							����ia=2;ib=2����temp3=temp4 = #H*H#(#��ʾ��H�����������,*��ʾ�жϵ�)
						(2) ���ia>1,ib=1������
							�жϵ����ȡia+1λ,�ұ߲�ȡ,�ŵ�����temp3��
							�жϵ����ȡiaλ,�ұ�ȡ1λ,�ŵ�����temp4��

							����ia=3,ib=1,��temp3=##HH*(#��ʾ��H�����������,*��ʾ�жϵ�)
											temp4=#HH*#(#��ʾ��H�����������,*��ʾ�жϵ�)
						(3) ���ia=1,ib>1������
							�жϵ����ȡ1λ,�ұ�ȡibλ,�ŵ�����temp3��
							�жϵ���߲�ȡ,�ұ�ȡib+1λ,�ŵ�����temp4��

							����ia=1,ib=3,��temp3=#*HH#(#��ʾ��H�����������,*��ʾ�жϵ�)
											temp4=*HH##(#��ʾ��H�����������,*��ʾ�жϵ�)
							
				*/

				//ȡ����ӵ�״̬�ŵ�temp3������(�ӵĸ�ʽΪia+ib+1��(�����жϵ�))
				for(i=0; i<1+ia+ib;i++)
				{
					tem1=wx-ia+ix-m1;
					if (tem1<0||tem1>14)	//�����߽�����,�����к���Ĵ���
					{	ix+=1;
						continue;
					}

					x=map[tem1][wy];				//ȡ�õ��ӵ�״̬
					temp3[i3]=ntoc(x,type,style);	//ȡ�õ��ӵ�״̬(0��1)ת��ΪH��B	

					ix+=1;
					i3++;
				}

				//ȡ�ұ��ӵ�״̬�ŵ�temp4������(�ӵĸ�ʽΪia+ib+1��(�����жϵ�))
				ix=0,i3=0;
				for (i=0 ; i<1+ia+ib;i++)
				{
					tem1=wx+ib-ix+m3;
					if (tem1<0||tem1>14)	//�����߽�����,�����к���Ĵ���	
					{	ix+=1;
						continue;
					}

					x=map[tem1][wy];				//ȡ�õ��ӵ�״̬	
					temp4[i3]=ntoc(x,type,style);	//ȡ�õ��ӵ�״̬(0��1)ת��ΪH��B
					
					ix+=1;
					i3++;
				}

				break;
			}

		//y������ж�ͬx����
		case 1:
			{
				m1=(ia!=1&&ib==1),m3=(ib!=1&&ia==1);
				for(i=0; i<1+ia+ib;i++)
				{
					tem1=wy-ia+iy-m1;
					if (tem1<0||tem1>14){iy+=1;continue;}
					x=map[wx][tem1];
					temp3[i3]=ntoc(x,type,style);
					iy+=1;
					i3++;
				}
				iy=0,i3=0;
				for (i=0 ; i<1+ia+ib;i++)
				{
					tem1=wy+ib-iy+m3;
					if (tem1<0||tem1>14){iy+=1;continue;}
					x=map[wx][tem1];
					temp4[i3]=ntoc(x,type,style);
					iy+=1;
					i3++;
				}
				break;
			}

		//45�ȷ�����ж�ͬx����
		case 2:
			{
				m1=(ia!=1&&ib==1),m3=(ib!=1&&ia==1);
				for (i=0 ; i<1+ia+ib ; i++)
				{
					tem1=wx-ia+ix-m1;
					tem2=wy-ia+iy-m1;
					if (tem1<0||tem1>14||tem2<0||tem2>14){ix+=1,iy+=1;continue;}
					x=map[tem1][tem2];
					temp3[i3]=ntoc(x,type,style);
					iy+=1;
					ix+=1;
					i3++;
				}
				iy=0,ix=0,i3=0;
				for (i=0 ; i<1+ia+ib ; i++)
				{
					tem1=wx+ib-ix+m3;
					tem2=wy+ib-iy+m3;
					if (tem1<0||tem1>14||tem2<0||tem2>14){ix+=1,iy+=1;continue;}
					x=map[tem1][tem2];
					temp4[i3]=ntoc(x,type,style);
					iy+=1;
					ix+=1;
					i3++;
				}
				
				break;
			}

		//135�ȷ�����ж�ͬx����
		case 3:
			{
				m1=(ia!=1&&ib==1),m3=(ib!=1&&ia==1);
				for (i=0 ; i<1+ia+ib ; i++)
				{
					tem1=wx-ia+ix-m1;
					tem2=wy+ia+iy+m1;
					if (tem1<0||tem1>14||tem2<0||tem2>14){ix+=1,iy-=1;continue;}
					x=map[tem1][tem2];
					temp3[i3]=ntoc(x,type,style);
					iy-=1;
					ix+=1;
					i3++;
				}
				iy=0,ix=0,i3=0;
				for (i=0 ; i<1+ia+ib ; i++)
				{
					tem1=wx+ib-ix+m3;
					tem2=wy-ib-iy-m3;
					if (tem1<0||tem1>14||tem2<0||tem2>14){ix+=1,iy+=1;continue;}
					x=map[tem1][tem2];
					temp4[i3]=ntoc(x,type,style);
					iy-=1;
					ix+=1;
					i3++;
				}
				break;
			}
	};

	/*
		���¸����жϵ����Ӻ���ֵ�״̬�жϸõ��ڵ�ǰ���״̬����Ҫ�̶�(���ȼ�),�жϵķ����Ǻ�Ԥ��
			����õ����״̬(������wds(dim.h)�������)���бȽϣ��õ������ֵΪ�õ�״̬������е�
			��ţ����ԽС,���ȼ�Խ��
	*/
	if ( (strcmp("00H0",(const char *)&temp3[1])==0 || strcmp("00H0",(const char *)&temp4[1])==0 || strcmp("00H0",(const char *)&temp3[0])==0 || strcmp("00H0",(const char *)&temp4[0])==0)&&tem3!=0)return;
	if ( (strcmp("00B0",(const char *)&temp3[1])==0 || strcmp("00B0",(const char *)&temp4[1])==0 || strcmp("00B0",(const char *)&temp3[0])==0 || strcmp("00B0",(const char *)&temp4[0])==0)&&tem3!=0)return;
	if ( (strcmp("00HHHB",(const char *)&temp3[1])==0 || strcmp("00HHHB",(const char *)&temp4[1])==0 || strcmp("00HHHB",(const char *)&temp3[0])==0 || strcmp("00HHHB",(const char *)&temp4[0])==0)&&tem3!=0)return;

	/*++�˴���Ӹ��������++*/
	if (tem3==0)	{
		//for (i=0 ; i<=27 ; i++)		//������ӵ�,ԭʼ�������������
		for (i=0 ; i<=61 ; i++)
			{
				if (strcmp(wds[i],(const char *)&temp3[1])==0||strcmp(wds[i],(const char *)&temp4[1])==0||strcmp(wds[i],(const char *)&temp3[0])==0||strcmp(wds[i],(const char *)&temp4[0])==0)
				{
					if (player==false)
					{
						//д����ʹ�õ���������

						/*
						if (pc[nx][ny][st]!=255) {
							MessageBox(GetActiveWindow(),"����ԭʼ����������","��ʾ",MB_OK);
						}
						*/
						pc[nx][ny][st]=i;
						return;
					}	
					else
					{
						//д����һ��ʹ�õ���������
						user[nx][ny][st]=i;
						return;
					}
				}
			}
	}
	else	{
		//for (i=0 ; i<=27 ; i++)		//������ӵ�,ԭʼ�������������
		for (i=0 ; i<=61 ; i++)
			{
				if (strcmp(wds[i],(const char *)&temp3[0])==0||strcmp(wds[i],(const char *)&temp4[0])==0)
				{
					if (player==false)
					{
						pc[nx][ny][st]=i;
						return;
					}	
					else
					{
						user[nx][ny][st]=i;
						return;
					}
				}
			}
	}

}

/*
	AIGO:�������˹����ܵ�������������
		color
			false		����
			true		����
	����ֵ��Ӧ���ڵڼ��м������ӡ�
	���ڵ�����:
		(1) ���ȶ�,�������ȼ����㲻��ȷ�����,��3����5�Ⱦ�����������
*/
CPoint wzq::AiGo(bool color)
{
	//��ʼ�����ص������Ϊ-1,-1
	CPoint turnback(-1,-1);

	//��ջ���ʹ�õ���������
	clear(false);

	/*
		����Ŀǰ��������û���ʹ�õ���������
	*/
	fillin(color,false,true);			//����ʹ�õ���������(����ռ�ݸõ������)
	fillin(!color,false,false);			//����ʹ�õ���������(�Է�ռ�ݸõ������)

	//����Ԥ�ⲽ��
	wzq::aitype2 =getaitype();
	unsigned char found=255;

	/*
		���������������У������ȼ���С���Ǹ���(����ԽС��ʾ���ȼ�Խ��)
	*/
	for (int ix=0 ;ix<=14;ix++)
	{
		for (int iy=0 ;iy<=14;iy++)
		{
			for (int im=0 ; im<=3 ; im++)
			{
				if (pc[ix][iy][im]<=found)
				{
					found=pc[ix][iy][im];
					turnback.x=ix,turnback.y=iy;
				}
			}
		}
	}

	/*
		����Ӧ������һ��
		(1) ������ص�����ȼ�<23(�μ�dim.h)����ʾ�ò��ǻ�������Ҫ��Ӧ�����(Ψһ������,�����5����)
			����û�����ţ����������߸�Ψһ������
		(2) �������ѡ�������getmax������������һ������.
	*/
	if (found<=23) 
	{
		//MessageBox(GetActiveWindow(),"Ψһ��������","��ʾ",MB_OK);
		return turnback;
	}
	else
		return getmax(color);
}

/*
	��nicest2�����е�����Ԫ������Ϊ0
*/
void wzq::setall()
{
	for (int ix=0 ;ix<=14;ix++)
	{
		for (int iy=0 ;iy<=14;iy++)
		{
			wzq::nicest2[ix][iy]=0; 
		}
	}
}

/*
	�����ӺͰ���(0,1����true��false)ת��Ϊ��ʾ�����ַ�(H)�Ͱ��ӵ��ַ�(B)
*/
char wzq::ntoc(char num,bool type,bool style)
{
	if (num==0)
		return '0';
	else if (type==true)		//��type����Ϊtrue�������,0��ʾ����,1��ʾ����
	{
		if (num==(int)style+1)
			return 'H';
		else 
			return 'B';
	}
	else						//��type����Ϊfalse�������,0��ʾ����,1��ʾ����
	{
		if (num!=(int)style+1)
			return 'H';
		else 
			return 'B';
	}
}

/*
	Ԥ���¼������߷����ú�����һ���ݹ麯�����ݹ���ֹ�����ǣ�
		(1) Ԥ�ⲽ���Ѿ��ﵽ���õĲ���(����-6;�м�-10;�߼�-20)
		(2) ��һ���Ѿ���ʤ
	��������:
		int x,y		Ԥ��������(�ں������ù����в��ϱ仯)
		color		���ӵ���ɫ
		nu			Ԥ�ⲽ��
		inx inx,iny	ԭʼԤ��������
	����ֵ:
		��������û�з���ֵ������ֵͨ��nicest2[inx][iny]�������Ԫ��������,������Ԫ�صĺ���Ϊ:
			1		�ѷ���
			2		�ѷ�Ӯ
			3		�����ж�ʤ��

	��������(?):
		Ԥ��ò�׼ȷ���ȴ����걣��ͼ��ع��ܺ���������

*/
void wzq::checkgo(int x,int y,bool color,int nu,int inx,int iny)//Ԥ�⺯�� 
{
	//ģ������
	//wzq::trygo[x][y]=(char)color+1;
	wzq::map[x][y]=(char)color+1;

	//����˷�ʹ�õ���������
	clear(true);


	//���ݵ�ǰ����ּ����˷�ʹ�õ���������()
	fillin(color,true,true);		//�˷�ʹ�õ���������(������ɫ)-����
	fillin(!color,true,false);		//�˷�ʹ�õ���������(����һ������Ӧ����)-�Է�


	//�����������з������ȼ���С�ĵ�(�õ���Ԥ�����Ӧ��)
	CPoint temp=getbg(true);


	bool four1=false,four2=false,three1=false,three2=false;
	bool four3=false,four4=false,three3=false,three4=false;

	/*
		���ҪԤ��ĵ����Ӻ�,�����ֵ�״̬( �μ�IDB_STATUS)
		��4������ֱ����Ƿ��Ѿ��ֳ�ʤ��,�Ƿ���4��,3���ȵ�....
	*/

	for (int i=0 ; i<=3 ; i++)
	{
		//"0BBBBB0",	"0BBBBBH",	"HBBBBBH",		�Է��Ѿ�5��,����
		if (user[temp.x][temp.y][i]>=3&&user[temp.x][temp.y][i]<=5)
		{
			wzq::nicest2[inx][iny]=2;//lose 
			return;
		}
		else
		{
			//"0HHHHH0",	"0HHHHHB",	"BHHHHHB", �����Ѿ�5����Ӯ��
			if (user[temp.x][temp.y][i]<3)//win
			{
				wzq::nicest2[inx][iny]=1;
				return;
			}
			else
			{
				if (user[temp.x][temp.y][i]>=6&&user[temp.x][temp.y][i]<=14)
				{
					/*
						6,7,8,9,10     "0HHHH0",	"0HHHHB",	"0HH0HH0",	"0HH0HHB","BHH0HHB",
						11,12,13,14    "0H0HHH0",	"BH0HHH0",	"0H0HHHB",	"BH0HHHB",\
						�����Ѿ�4����
					*/

					if(four1==true)	four2=true;
					else four1=true;
				}
				else
				{
					/*
						15,16,17,18,19 "0BBBB0",	"0BBBBH",	"0BB0BB0",	"0BB0BBH","HBB0BBH",\
						20,21,22,23    "0B0BBB0",	"HB0BBB0",	"0B0BBBH",	"HB0BBBH",\
						�Է��Ѿ�4����
					*/
					if (user[temp.x][temp.y][i]>=15&&user[temp.x][temp.y][i]<=23)
					{
							if(four3==true)four4=true;
							else four3=true;
					}
					else
					{
						/*
							24,25	"0H0HH0",	"0HHH0",
							26,27	"0B0BB0",	"0BBB0",
						*/
						if (user[temp.x][temp.y][i]==24||user[temp.x][temp.y][i]==25)
						{
								//�Է��Ѿ�3����
								if(three1==true)three2=true;else three1=true;
						}
						else
						{
							if (user[temp.x][temp.y][i]==26||user[temp.x][temp.y][i]==27)
							{	
								//�����Ѿ�3����
								if(three3==true)three4=true;else three3=true;
							}
						}
					}
				}
			}
		}
	}


	/*
		�������״̬����ʤ���ж�(δ���н����ж�)���жϹ�����
			(1) ������3			ʤ
			(2) ������4			ʤ
			(2) 1����3+1����4	ʤ
		�������Ӹ���Ĺ���

	*/
	if (three1+three2+four1+four2>=2)		//�û���Ӧ���γɺ��3+��4����>2,���û���ʤ
	{
		wzq::nicest2[inx][iny]=1;		//������
		return;
	}
	else
	{
		if (three3+three4+four3+four4>=2)	//�û���Ӧ�󼺷��γɵĻ�3+��4����>2,�򼺷�ʤ
		{
			wzq::nicest2[inx][iny]=2;	//����Ӯ
			return;
		}
	}

	//�ж��Ƿ�Ԥ�ⲽ���Ѿ��ﵽָ���Ĳ���
	if (nu>=wzq::aitype2)
	{
		//�Ѿ��ﵽ��û���жϳ�ʤ��
		wzq::nicest2[inx][iny]=3;
		return;
	}
	else {
		//�������øõݹ麯��,ע������!color���õġ�
		int xxx=nu+1;

		checkgo(temp.x,temp.y,!color,xxx,inx,iny);
	}
}

/*
	������������,������Ҫ�̶�����һ��,��Ҫ���������:
		(1) ������Ԥ������,ѡ�����ȼ���С��һ��(����ԽС,���Ȼ���Խ��,Խ��Ҫ)
		(2) ����Ԥ������,����Ҫ�����˷����Ӧ�Ե���������˷�Ӧ�Ե�����£��ٿ��ǻ��������.....
				ֱ���ֳ�ʤ�����ߴﵽԤ�ⲽ��Ϊֹ
	��������(?)
		���������µĵ�Խ�࣬�ú����ڵ�ѭ��������Խ��
*/
CPoint wzq::getmax(bool color)
{
	//��ʼ��������ֵ�������
	CPoint turnback(0,0);
	setall();		//��nicest2�����е�����Ԫ������Ϊ0
	bool lb_backupFlag=false;		//��ǰ�������ݵı��ݱ�־(true-�ѱ���,false-δ����)
	
	int li_count=0;		//��������

	//����ǰ���������ݱ��ݵ�trygo���������
	for (int ix=0;ix<=14;ix++)
		{
			for (int iy=0 ;iy<=14;iy++)
			{
				wzq::trygo[ix][iy]=wzq::map[ix][iy];
			}
		}
	lb_backupFlag=true;

begin:
	bool x=0;
	int fx=0,fy=1;

	li_count++;

	//������û�е��ù�checkgo�����Ľڵ���,�������ȼ���С�Ľڵ�,����������fx��fy��
	for (ix=0 ;ix<=14;ix++)
		{
			for (int iy=0;iy<=14;iy++)
			{
				if (wzq::nicest2[ix][iy]==0)			//�õ�û�е��ù�checkgo����
				{
					if (bj2(ix,iy,fx,fy,false)==true) {
						fx=ix;		//����С���x���걣����fx��
						fy=iy;		//����С���x���걣����fy��
						x=1;
					}
				}
			}	
		}

	//���û���ҵ�
	if (x==0) {	
		x=0;
		for (int ix=0 ;ix<=14;ix++)
		{
			for (int iy=0 ;iy<=14;iy++)
			{
				if (wzq::nicest2[ix][iy]!=1)		//�����б�֤����Ľڵ��в������ȼ�����С�ĵ�
				{
					if (bj2(ix,iy,turnback.x,turnback.y,false)==true) {
						turnback.x=ix;
						turnback.y=iy;
						x=1;}
				}
			}
		}
		
		//�ڲ���Ľڵ���û���ҵ���(0,1)�ڵ����ȼ���С�ĵ㣬�������еĽڵ��в������ȼ���С�Ľڵ�
		if (x==0)	{
			x=0;
			for (int ix=0 ;ix<=14;ix++)
			{
				for (int iy=0 ;iy<=14;iy++)
				{
					if (bj2(ix,iy,turnback.x,turnback.y,false)==true) {
						turnback.x=ix;
						turnback.y=iy;
						x=1;}
				}
			}
		}

		//�����еĽڵ��в������ȼ���С�Ľڵ�,�������������ĵ�
		if (x==0) turnback.x =7,turnback.y =7;

		//�ָ���������������
		if (lb_backupFlag==true) {
			for (int ix=0 ;ix<=14;ix++)
				{
					for (int iy=0 ;iy<=14;iy++)
					{
						wzq::map[ix][iy]=wzq::trygo[ix][iy];
					}
				}
		}
		return turnback;
	}

	//����checkgo��������Ԥ��(����õ��,��ֵ�״̬��ʲô?)
	wzq::checkgo(fx,fy, color,1,fx,fy);

	//�жϺ����ķ���ֵ,ͨ��nicest2[fx][fy]�������Ԫ�ط���
	if (nicest2[fx][fy]==2)			//Ӯ��
	{
		turnback.x=fx,turnback.y=fy;
		//�ָ���������������
		if (lb_backupFlag==true) {
			for (int ix=0 ;ix<=14;ix++)
				{
					for (int iy=0 ;iy<=14;iy++)
					{
						wzq::map[ix][iy]=wzq::trygo[ix][iy];
					}
				}
		}

		return turnback;
	}
	else
	{
		goto begin;				//����һ��
	}
	
}

/*
	��������:�����̵����е��ϣ�ȡ����������С�ĵ�����.
	������
		style�������ʵ������û���õġ�
*/
CPoint wzq::getbg(bool style )
{
	CPoint turnback;
	int ix1=0,iy1=0;
	for (int ix=0 ;ix<=14;ix++)
	{
		for (int iy=0 ;iy<=14;iy++)
		{
			//���ú����Ƚ��������Ԥ��ֵ�Ĵ�С
			if (bj2(ix,iy,ix1,iy1,style)==true)
			{
				ix1=ix,iy1=iy;
			}
		}
	}

	//����Ԥ��ֵ��С�ĵ������
	turnback.x=ix1;
	turnback.y=iy1;
	return turnback;
}

/*
	��������:(?)�Ƚ���������������ݵĴ�С
	����:
		int x1,int y1		��1���������
		int x2,int y2		��2���������
		style				��ʾ��ȡ�������ݻ��Ǹ����µ�����
	����ֵ��
		�����1����С���򷵻�true;���򷵻�false.
*/
bool wzq::bj2(int x1,int y1,int x2,int y2,bool style)
{
	unsigned char a[4];
	unsigned char b[4];
	unsigned char temp1;
	int i;


	if (style==false)			//ȡ��������,����һ��������ݷ�������a����2��������ݷ�������b��
	{
		for (i=0 ; i<=3 ;i++)
		{
			a[i]=1;
			a[i]=pc[x1][y1][i];
			b[i]=pc[x2][y2][i];
		}
	}
	else						//ȡ�����µ�����,����һ��������ݷ�������a����2��������ݷ�������b��
	{
		for (i=0 ; i<=3 ;i++)
		{a[i]=1;
		a[i]=user[x1][y1][i];
		b[i]=user[x2][y2][i];
		}
	}

	//ð�����򣬷ֱ����������a��b��������
	for (i=0 ; i<=3 ; i++)
	{
		for (int i2=0 ; i2<=2-i; i2++)
		{
			if (a[i2]>a[i2+1])
			{
				temp1=a[i2];
				a[i2]=a[i2+1];
				a[i2+1]=temp1;
			}
			if (b[i2]>b[i2+1])
			{
				temp1=b[i2];
				b[i2]=b[i2+1];
				b[i2+1]=temp1;
			}
		}
	}


	/*
		���ؽ��:
			����ڵ�1����������С�ڵ�2��������ݣ��򷵻�true�����򷵻�false.
	*/
	for (i=0 ; i<=3 ; i++)
	{
		if (a[i]<b[i])
		{
			return true;
		}
		else
		{
			if (a[i]>b[i])
			{
			return false;
			}
		}
	}
	return false;
}

/*
	�����������,�����õ����ݷ�����pc�����ά�����У�
		��ʹ�õ����ݷ�����user�����γ������,
	����:style
			false		��������õ�����
			true		������õ�����
*/
void wzq::clear(bool style)
{
	int ix,iy;

	if (style==false) 
	{
		for ( ix=0 ;ix<=14;ix++)
		{
			for (iy=0 ;iy<=14;iy++)
			{
				for (int im=0 ; im<=3 ; im++)
				{
					wzq::pc[ix][iy][im]=255; 
				}
			}
		}
	}

	else
	{
		for (ix=0 ;ix<=14;ix++)
		{
			for (iy=0 ;iy<=14;iy++)
			{
				for (int im=0 ; im<=3 ; im++)
					{
						wzq::user[ix][iy][im]=255; 
					}
			}
		}
	}
	//
}

/*
	�������õ����ܵȼ�����Ӧ��Ԥ�⼸���ĺ���
*/
int wzq::getaitype()
{
	if (wzq::AItype==0)
		return 6;		//�����ܣ�Ԥ��6��
	else if (wzq::AItype==1)
		return 10;		//�����ܣ�Ԥ��10��
	else if (wzq::AItype==2 )
		return 20;		//�����ܣ�Ԥ��20��
	else
		return 10;		//Ĭ��Ϊ�����ܣ�Ԥ��10��
}

/*
	���������¼�ĺ�������������
		nx,ny		����������(���м���)
		style
			false	�õ��µ��ǰ���
			true	�õ��µ��Ǻ���
*/
void wzq::setback(int nx,int ny,bool style)
{
	wzq::wzs[wzq::nowd2].used=true;
	wzq::wzs[wzq::nowd2].color=style;
	wzq::wzs[wzq::nowd2].ix =nx;
	wzq::wzs[wzq::nowd2].iy =ny;
	wzq::nowd2++; 
}
