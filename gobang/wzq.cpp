/*
	五子棋人工智能操作-实现程序
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
	构造函数
*/
wzq::wzq(CDC2*tqp,CDC2*tqzh,CDC2*tqzb,CDC2*tmask,CDC2*dead,CDC*dc,CDC2 *tqzhl,CDC2 *tqzbl)
{
	SetDc(tqp,tqzh,tqzb,tmask,dead,dc,tqzhl,tqzbl);
}
/*
	析构函数
*/
wzq::~wzq(){}

/*
	默认构造函数
*/
wzq::wzq()
{	
	wzq::dcseted=false; 
}


/*
	画棋子的函数.
	参数：
		int nx		棋子x坐标(几行几列,不包括边界)
		int ny		棋子y坐标(几行几列,不包括边界)
		bool style	在屏幕上画出黑棋还是白棋。
					true -画黑棋
					flase-画白棋
		boolean		drawModel		是draw函数调用还是UserAd,UserBd函数
					true		draw函数调用

	存在问题:机先人后时,第一个子(黑子)的形状不能正确变更

	使用到的函数API(MFC函数解析)
	(1) BOOL BitBlt(int x, int y, int nWidth, int nHeight, CDC* pSrcDC,
		int xSrc, int ySrc, DWORD dwRop);
		该函数的各个参数的含义还没有说明
	函数功能：该函数对指定的源或设备环境区域中的像进行位块(bit_block)转换，以传送到目标设备环境。
		参数：
		x：指定目标矩形区域克上角的X轴逻辑坐标。
		y：指定目标矩形区域左上角的Y轴逻辑坐标。
		nWidth：指定源和目标矩形区域的逻辑宽度。
		nHeight：指定源和目标矩形区域的逻辑高度。
		pSrcDC：指向源设备环境句柄。
		xSrc：指定源矩形区域左上角的X轴逻辑坐标。
		ySrc：指定源矩形区域左上角的Y轴逻辑坐标。
		dwRop：指定光栅操作代码。这些代码将定义源矩形区域的颜色数据，如何与目标矩形区域的颜色数据组合以完成最后的颜色。

*/
void wzq::DrawQZ(int nx,int ny,bool style,bool drawModel=false)
{
	CDC2 * lcdc_qzh;
	CDC2 *lcdc_qzb;
	if (wzq::dcseted==false)return;
	if (nx>15||ny>15) return;		

	if (drawModel==true) {
		//如果是draw函数调用,这使用不带圈的棋子
		lcdc_qzh = qzh;
		lcdc_qzb = qzb;
	}
	else {
		//如果是非draw函数调用,这使用带圈的棋子
		lcdc_qzh = qzhl;
		lcdc_qzb = qzbl;

	}

	if (style==false )		//白子
	{
		//先使用背景颜色擦除
		dc->BitBlt(nx*29+7,ny*29+7,28,28,mask,0,0,MERGEPAINT);
		//画出白子(实际坐标是行列*29+7,28是棋子的高度和宽度)
		dc->BitBlt(nx*29+7,ny*29+7,28,28,lcdc_qzb,0,0,SRCAND);
	}
	else		//黑子
	{
		//先使用背景颜色擦除
		dc->BitBlt(nx*29+7,ny*29+7,28,28,mask,0,0,MERGEPAINT);
		//画出黑子(实际坐标是行列*29+7,28是棋子的高度和宽度)
		dc->BitBlt(nx*29+7,ny*29+7,28,28,lcdc_qzh,0,0,SRCAND);
	}

	//设置上一下的棋子为正常颜色
	int li_LastXY = wzq::nowd2-1;
	if (li_LastXY>=0 && !(drawModel==true)) {
		int li_LastX = wzq::wzs[li_LastXY].ix;
		int li_LastY = wzq::wzs[li_LastXY].iy;
		if (wzq::wzs[li_LastXY].color == false) {		//上一子是白子
			//先使用背景颜色擦除
			dc->BitBlt(li_LastX*29+7,li_LastY*29+7,28,28,mask,0,0,MERGEPAINT);
			//画出白子(实际坐标是行列*29+7,28是棋子的高度和宽度)
			dc->BitBlt(li_LastX*29+7,li_LastY*29+7,28,28,qzb,0,0,SRCAND);
		}
		else if (wzq::wzs[li_LastXY].color == true) {	//上一子是黑子
			//先使用背景颜色擦除
			dc->BitBlt(li_LastX*29+7,li_LastY*29+7,28,28,mask,0,0,MERGEPAINT);
			//画出白子(实际坐标是行列*29+7,28是棋子的高度和宽度)
			dc->BitBlt(li_LastX*29+7,li_LastY*29+7,28,28,qzh,0,0,SRCAND);
		}
	}

}

/*
	设置DC,具体的DC由一个指针参数传递
*/
void wzq::SetDc(CDC2 * tqp,CDC2 * tqzh,CDC2 * tqzb,CDC2 * tmask,CDC2 * dead,CDC * dc,CDC2 * tqzhl,CDC2 * tqzbl)//设置DC
{
	wzq::mask =tmask;	//掩码DC
	wzq::qp =tqp;		//棋盘DC
	wzq::qzb =tqzb;		//白棋子DC
	wzq::qzbl = tqzbl;	//白棋子DC(带圆圈)
	wzq::qzh =tqzh;		//黑棋子DC
	wzq::qzhl =tqzhl;		//黑棋子DC(带圆圈)
	wzq::dc =dc;		//窗口DC
	wzq::dead=dead;		//红颜色棋子的DC
	wzq::dcseted=true; 
}

/*
	开始新游戏的函数
*/
void wzq::NewGame()
{

	if (wzq::dcseted==false)	return;

	/*
		据初始工作，主要包括：
		(1) 存储棋局的三维数组user设置为""(255)
		(2) 存储棋局的三维数组pc设置为""(255)
		(3) 保存棋盘上每个点是否下过棋子的二维数组wzs清空
		(4) 保存储存棋盘地图的二维数组map设置为''(255)
	*/
	for(int i1=0 ; i1<=14;i1++)
	{
		for(int i2=0 ; i2<=14;i2++)
		{
			//初始化(4)
			map[i1][i2]=0;
			for(int i3=0 ; i3<=3;i3++)
			{
				//初始化(1)
				user[i1][i2][i3]=255;
				//初始化(2)
				pc[i1][i2][i3]=255;

			}
		}
	}

	//初始化(3)
	for (int ix=0;ix<225;ix++)
	{
		wzq::wzs[ix].used=false; 
	}

	/*
		画棋盘
	*/
	//取棋盘DC的尺寸,主要是获取棋盘DC的高度和宽度
	CSize x=qp->GetSize();
	//调用窗口DC的BitBlt函数画出棋盘DC
	dc->BitBlt(0, 0,x.cx,x.cy,qp,0,0,SRCCOPY);//画棋盘
	//设置成员变量表示没有那一方获胜，这个成员变量在每次下子后均需要重新判断
	wzq::twinner.winner=0;  
	//
	wzq::nturn=0; 
	//设置是否可以悔棋
	wzq::nowd2 =0;

	/*
		先下的用黑子
		如果是操作模式是机器先下，这程序自动下一个黑子,位置是在第7行第7列(不包含边界上的那一列)
	*/
	if (wzq::Model==1)
	{
		userBd(7,7);
	} 
}


/*
	重画整个棋局(棋盘和已经下的黑子和白子)的函数
	说明:
		在函数中还需要判断5连是朝那个方向，其实可以在bewinner2函数中保存5连的方向即可.
		这样可以简化函数
*/
void wzq::draw()//重画
{
	//未设置窗口DC，退出	
	if (wzq::dcseted==false)return;

	//画棋盘(从棋盘DC中得到棋盘的高度和宽度)
	CSize x=qp->GetSize() ;
	dc->BitBlt(0, 0,x.cx,x.cy,qp,0,0,SRCCOPY);

	//画棋子
	for(int i1=0 ; i1<15;i1++)
	{
		for(int i2=0 ; i2<15;i2++)
		{
			//如果某一交叉点已经下了白子，这该棋盘上该点处画白子
			if (map[i1][i2]==1){this->DrawQZ(i1,i2,false,true);}
			//如果某一交叉点已经下了黑子，这该棋盘上该点处画黑子
			if (map[i1][i2]==2){this->DrawQZ(i1,i2,true,true);}	
		}
	}
	
	/*
		检查棋局是否已经有一方赢了,如果已经有一方赢了，这
		使用红子代替原来位置的棋子(不管黑子)
	*/
	if (wzq::twinner.winner!=0)		//1-白胜;2-黑胜
	{
		/*
			检查胜的一方棋子的排列方式，总共的方向有8种：
				y不变,x增加		棋子在0度方向连成一线
				x增加,y增加		棋子在45度方向连成一线
				x不变,y增加		棋子在90度方向连成一线
				x增加,y减少		棋子在135度方向连成一线
				y不变,x减小		棋子在180度方向连成一线
				x减小,y减小		棋子在225度方向连成一线
				x不变,y减小		棋子在270度方向连成一线
				x减少,y增加		棋子在315度方向连成一线
		*/
		int x1=wzq::twinner.nx1;	//5连的开始坐标(x)
		int y1=wzq::twinner.ny1;	//5连的开始坐标(y)
		int xj;						//5连的x坐标增加方向
		int yj;						//5连的y坐标增加方向

		//判断5连的x坐标增加方向
		if(wzq::twinner.nx2-wzq::twinner.nx1>0)
			{
				xj=1;				//X坐标增加
			}
		else {
				if (wzq::twinner.nx2-wzq::twinner.nx1==0)
					{
						xj=0;		//X坐标不变
					}
				else
					{
						xj=-1;		//X坐标减小
					}

			}

		//判断5连的y坐标增加方向
		if(wzq::twinner.ny2-wzq::twinner.ny1>0)
			{
				yj=1;				//Y坐标增加
			}
		else
			{
				if (wzq::twinner.ny2-wzq::twinner.ny1==0)
					{
						yj=0;		//Y坐标不变
					}
				else
					{
						yj=-1;		//Y坐标减小
					}

			}

		/*
			在有5连的地方用红子代替原来位置的棋子(不管黑子)
			为了统一，也可以修改DrawQZ函数在该函数中画红子,这里调用该函数
		*/
		for (int ii=1; ii<=5 ; ii++)		//ii是循环变量，没有什么用处
			{

				//先擦除原来的棋子
				dc->BitBlt(x1*29+7,y1*29+7,28,28,mask,0,0,MERGEPAINT);
				//画出红子
				dc->BitBlt(x1*29+7,y1*29+7,28,28,dead,0,0,SRCAND);
				//5连的x坐标变化
				x1+=xj;
				//5连的y坐标变化
				y1+=yj;
			}
		//画红子结束
	}
	
}  

/*
	(private函数)白色下子,参数:
		nx-下子的x坐标(几行几列)
		ny-下子的y坐标(几行几列)
	需要该坐标处下过其他子，才能落子
*/
bool wzq::userAd(int nx,int ny)
{
	//未设置窗口DC，退出	
	if (wzq::dcseted==false)return false;

	if (map[nx][ny]==0)			//该点没有下过子
		{
			map[nx][ny]=1;		//设置该点下过的子是白子
			DrawQZ(nx,ny,false);//在该坐标处画白子
			return true;
		}
	else		//该点已经落子了
		{
			return false;
		}
}

/*
	(private函数)黑色下子，参数:
		nx-下子的x坐标(几行几列)
		ny-下子的y坐标(几行几列)
	需要该坐标处下过其他子，才能落子
*/
bool wzq::userBd(int nx,int ny)
{
	//未设置窗口DC，退出	
	if (wzq::dcseted==false)return false;

	if (map[nx][ny]==0)			//该点没有下过子
		{
			map[nx][ny]=2;		//设置该点下过的子是黑子
			DrawQZ(nx,ny,true); //在该坐标处画黑子
			return true;
		}
	else
	{
		return false;
	}
}

/*
	判断胜败,判断棋盘上是否有5连或者>5连,参数:
		style
			false		检查是否白子胜
			true		检查是否黑子胜
		nx,ny	当前点的坐标(几行几列)，从当前点开始,从8个方向判断棋盘上是否有5连或者>5连
			棋子在0方向连成一线
			棋子在45度方向连成一线
			棋子在90度方向连成一线
			棋子在135度方向连成一线
			棋子在180度方向连成一线
			棋子在225度方向连成一线
			棋子在270度方向连成一线
			棋子在315度方向连成一线
	返回值:
		false		没有5连
		true		有5连
	存在问题:
		只能够判断5连,不能判断6连甚至7连.....
*/		
bool wzq::bewinner2(bool style,int nx,int ny)
{
	int tx1=0,tx2=0,ty1=0,ty2=0;
	int yx1=0,yx2=0,yy1=0,yy2=0;

	//st=1 表示白子		st=2表示黑子
	int st=(int)style+1;

	/*
		从当前点出发，检查是否超过5个以上的子是指定的颜色(白子或者黑子)
			nx-5~nx+5	y不变			检查延x方向是否有5个以上的子连在一起
			ny-5~ny+5	x不变			检查延x方向是否有5个以上的子连在一起
			ny-5~ny+5	ny-5~ny+5(x,y同时增加和减小)		
				检查延45度(225)方向是否有5个以上的子连在一起
			ny-5~ny+5	ny-5~ny+5(x,y相反增加和减小)		
				检查延135度(315)方向是否有5个以上的子连在一起

	*/

	for (int x1=-5 ; x1<= 5 ; x1++)	//以当前点为中心点，检查前后5个点
	{
		//检查x方向
		if (map[nx+x1][ny]==st)		
		{
			//表示x方向相同颜色的计数器+1
			tx1++;
			if (tx1==1)	yx1=x1;		//5子相连的开始X坐标(y坐标相同)

			if (tx1>=5)				//在x方向有5个子连在一起
			{
				twinner.winner =st;

				//设置5子在x方向相连的开始坐标
				twinner.nx1= nx+yx1;
				twinner.ny1 =ny;
				//设置5子在x方向相连的结束坐标
				twinner.nx2 =nx+yx1+5;
				twinner.ny2 =ny;
				return true;
			}
		}
		else 
		{
			//在该方向上有一个子的颜色和要判断子的颜色不一样时tx1这个计数器重新计数
			tx1=0;
		}

		//检查Y方向
		if (map[nx][ny+x1]==st)
		{
			//表示y方向相同颜色的计数器+1
			ty1++;
			if (ty1==1)	yy1=x1;		//5子相连的开始y坐标(x坐标相同)

			if (ty1>=5)				//在x方向有5个子连在一起
				{
					twinner.winner =st;
					//设置5子在y方向相连的开始坐标
					twinner.nx1= nx;
					twinner.ny1 =ny+yy1;
					//设置5子在y方向相连的结束坐标
					twinner.nx2 =nx;
					twinner.ny2 =ny+yy1+5;
					return true;
				}

		}
		else 
		{
			//在该方向上有一个子的颜色和要判断子的颜色不一样时ty1这个计数器重新计数
			ty1=0;
		}

		//检查45度方向
		if (map[nx+x1][ny+x1]==st)
		{
			//表示45度方向相同颜色的计数器+1
			tx2++;

			if (tx2==1)	yx2=x1;		//5子相连的开始坐标
			if (tx2>=5)				//在45度方向有5个子连在一起
			{
				twinner.winner =st;
				//设置5子在45度方向相连的开始坐标
				twinner.nx1= nx+yx2;
				twinner.ny1 =ny+yx2;
				//设置5子在45度方向相连的结束坐标
				twinner.nx2 =nx+yx2+5;
				twinner.ny2 =ny+yx2+5;
				return true;
			}
		}
		else
		{
			//在该方向上有一个子的颜色和要判断子的颜色不一样时tx2这个计数器重新计数
			tx2=0;
		}

		//检查135度方向
		if (map[nx+x1][ny-x1]==st)
		{
			//表示135度方向相同颜色的计数器+1
			ty2++;
			if (ty2==1)	yy2=x1;
			if (ty2>=5)				//在135度方向有5个子连在一起
			{
				twinner.winner =st;
				//设置5子在135度方向相连的开始坐标
				twinner.nx1= nx+yy2;
				twinner.ny1 =ny-yy2;
				//设置5子在135度方向相连的结束坐标
				twinner.nx2 =nx+yy2+5;
				twinner.ny2 =ny-yy2-5;
				return true;
			}
		}
		else 
		{
			//在该方向上有一个子的颜色和要判断子的颜色不一样时ty1这个计数器重新计数
			ty2=0;
		}
	}
	return false;
}

/*
	提供给其他类调用的下子函数。参数：
		nx-下子的x坐标(几行几列)
		ny-下子的y坐标(几行几列)
	返回值:下子是否成功

	说明：
		每落一个子后，均需要执行一下操作:
			(1) 判断是否获胜
				bewinner2(标志(false-白子,true-黑子),x坐标,y坐标)
			(2) 记录下棋记录
				setback(x坐标,y坐标,标志(false-白子,true-黑子) )
*/
bool wzq::downzi(int nx,int ny)
{
	bool turnback;

	//下子的坐标点范围是在0-14范围内
	if (nx<0||nx>14||ny<0||nx>14) return false;
	if (wzq::nturn==-1)return false;

	/*
		下棋的是否根据不同的使用模式进行不同的处理
			两人对弈		两方按照顺序轮流下子(不涉及到人工智能)
			机先人后		人下白子，下完后机器自动响应应该在那里下黑子
			人先机后		人下黑子，下完后机器自动响应应该在那里下白子
	*/

	//使用模式是两人对弈
	if (wzq::Model==2 )
	{
		if (wzq::nturn==1)				//当前应该是白子下
		{
			turnback=userAd(nx,ny);		//在指定点下一个白子

			//在指定点落一个白子后检查是否白子胜。
			if (bewinner2(false,nx,ny)==true)
				wzq::nturn=-1; 
			wzq::nturn =turnback?0:1;
			//记录落子历史
			setback(nx,ny,false);
		}
		else							//当前应该是黑子下
		{
			turnback=userBd(nx,ny);		//在指定点下一个黑子

			//在指定点落一个黑子后检查是否黑子胜。
			if(bewinner2(true,nx,ny)==true)wzq::nturn =-1;

			wzq::nturn =turnback?1:0;
			//记录落子历史
			setback(nx,ny,true);
		}
	}
	else if (wzq::Model==1)
	//使用模式是机先人后(机器黑子,下棋的一方白子)
	{
		//白方在指定的坐标处下一白子
		if (userAd(nx,ny)==false)	return false;

		//在指定点落一个白子后检查是否白子胜。
		if(bewinner2(false,nx,ny)==true)wzq::nturn =-1;
		//记录落子历史
		setback(nx,ny,false);

		/*
			以下程序是机器的自动响应(机器黑子)
		*/
		CPoint aigo=wzq::AiGo(true);		//返回值是应该在那个坐标落子(几行几列)
		//在机器响应的坐标位置落黑子
		userBd(aigo.x,aigo.y);
		//记录落子历史
		setback(aigo.x,aigo.y,true);

		//在指定点落一个黑子后检查是否黑子胜。
		if(bewinner2(true,aigo.x,aigo.y)==true) wzq::nturn =-1;
	}
	else if (wzq::Model==0)
	//使用模式是人先机后(机器白子,下棋的一方黑子)
	{
		//黑方在指定的坐标处下一黑子
		if (userBd(nx,ny)==false)return false;

		//在指定点落一个黑子后检查是否黑子胜。
		if(bewinner2(true,nx,ny)==true)wzq::nturn =-1;
		//记录落子历史
		setback(nx,ny,true);

		/*
			以下程序是机器的自动响应(机器白子)
		*/

		CPoint aigo=wzq::AiGo(false);	;		//返回值是应该在那个坐标落子(几行几列)
		//在机器响应的坐标位置落白子
		userAd(aigo.x,aigo.y);
		//记录落子历史
		setback(aigo.x,aigo.y,false);

		//在指定点落一个白子后检查是否白子胜。
		if(bewinner2(false,aigo.x,aigo.y)==true)wzq::nturn =-1;
	}

	//MessageBox(GetActiveWindow(),wzq::nowd2,"提示",MB_OK);
	
	return turnback;
}

/*
	悔棋函数.
	返回值:悔棋是否成功

*/
bool wzq::goback()
{	
	//当前不允许悔棋,返回
	if (wzq::getbackble==false) return false; 

	/*
		表示已经下了多少子的计数器减1,这个计数器在setback函数中已经加1了
		所以要先减回来，才表示要悔的那一步棋
	*/
	wzq::nowd2--;

	/*
		如果是两个人对弈，这悔棋悔一步
		如果是人和机器对弈，这人悔棋的同时，机器也自动会退一步
	*/
	if (wzq::Model==2)		//两个人对弈
	{
		//在该坐标点在map数组中表示已经下过子数据清空
		map[wzq::wzs[nowd2].ix][wzq::wzs[nowd2].iy]=0;

		//?(好像不能正确表示顺序)
		wzq::nturn= wzq::wzs[nowd2].color ;

		wzq::wzs[nowd2].used=false;		//清除该点在下棋历史记录中的数据

		/*
			从棋盘DC中的取出一块区域覆盖目前的棋局中指定位置的棋子
			也可以考虑使用掩码DC擦除该棋子
		*/
		wzq::dc->BitBlt(wzq::wzs[nowd2].ix*29+7,wzq::wzs[nowd2].iy*29+7,28,28,
			wzq::qp,wzq::wzs[nowd2].ix*29+7,wzq::wzs[nowd2].iy*29+7,SRCCOPY);
	}
	else
	{
		//在该坐标点在map数组中表示已经下过子数据清空
		map[wzq::wzs[nowd2].ix][wzq::wzs[nowd2].iy]=0;
		wzq::wzs[nowd2].used=false;
		//从棋盘DC中的取出一块区域覆盖目前的棋局中指定位置的棋子
		wzq::dc->BitBlt(wzq::wzs[nowd2].ix*29+7,wzq::wzs[nowd2].iy*29+7,28,28,
			wzq::qp,wzq::wzs[nowd2].ix*29+7,wzq::wzs[nowd2].iy*29+7,SRCCOPY);

		/*悔机器下的一子*/
		wzq::nowd2--;				//表示下棋记录的计数器减1
		map[wzq::wzs[nowd2].ix][wzq::wzs[nowd2].iy]=0;
		wzq::wzs[nowd2].used=false;
		wzq::dc->BitBlt(wzq::wzs[nowd2].ix*29+7,wzq::wzs[nowd2].iy*29+7,28,28,
			wzq::qp,wzq::wzs[nowd2].ix*29+7,wzq::wzs[nowd2].iy*29+7,SRCCOPY);
	}

	//如果已经判断当前又某一方已经赢了，则悔棋后的赢的条件不成立了
	if (wzq::twinner.winner!=0) 
	{
		wzq::twinner.winner =0;		//没有那一方赢
		/*
			重新画棋盘(因为如果又那一方已经赢了话,棋盘上又一部分
				子已经变成了红子，所以要重新画棋盘
				或者将红子部分重新变成白子或者黑子.
		*/
		wzq::draw();		//将全部点变成不带圆圈的形状
	}

	//
	if (wzq::nturn ==-1) wzq::nturn=0;
	return false;
}


/*
	禁手控制函数,暂时没有设置禁手
*/
bool wzq::bejs(int nx,int ny)
{
	return false;
}


/*
	根据当前的棋局填写棋型数据(
		机器使用的写在pc这个三维数组中
		人方写在user这个三维数组中)
	参数说明:
		color		黑子还是白子
		player		机器方还是人方(false-机器方;true-人方)
		type		?(调用时有true和false两种值)
	说明：
		所谓棋型数据就 如果在棋盘上未下子的地方下子，该子在各个方向上对棋局的影响值
		(影响值参见dim.h，数值越小越重要)	
*/
void wzq::fillin(bool color,bool player,bool type)
{
	int ix,iy;
	for (ix=0 ;ix<=14;ix++)
	{
		for (iy=0 ;iy<=14;iy++)
		{
			if (map[ix][iy]==0)				//只有棋盘上未下子的地方才进行计算。
			{
			
				/*
					分别计算在某一个位置(nx,ny)处落一子后,在4个方向上对棋局的影响,则4个方向分别为:
							im=0	x方向(在setqx函数中如果左右扩展为0度和180度两个方向)
							im=1	y方向(在setqx函数中如果左右扩展为90度和270度两个方向)
							im=2	45度方向(在setqx函数中如果左右扩展为45度和225度两个方向)
							im=3	135度方向(在setqx函数中如果左右扩展为135度和315度两个方向)
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
	函数功能:		计算某一点在棋型数据中的值(当前棋局中的重要程序(优先级别))
	参数说明:
		nx,ny		计算点的坐标(该点是未落过子的点才计算棋型数据,否则不计算)
		style		黑子还是白子
		player		?(计算机器还是人这一方的棋型数据)
		st			预测方向,具体含义为:
					0	x方向(在setqx函数中如果左右扩展为0度和180度两个方向)
					1	y方向(在setqx函数中如果左右扩展为90度和270度两个方向)
					2	45度方向(在setqx函数中如果左右扩展为45度和225度两个方向)
					3	135度方向(在setqx函数中如果左右扩展为135度和315度两个方向)

		type		?(调用时有true和false两种值)
	返回值: 无

*/
void wzq::setqx(int nx ,int ny,bool style,bool player,int st,bool type)
{
	bool ok=true;
	int ia,ib;
	int ix,iy;
	int i2,i2j;		//x方向和y方向的增加子
	int tem1,tem2;
	int x;
	int i3;
	int m1,m3;
	int i;
	int wx=nx,wy=ny,tem3=0;


	switch (st)
	{
		case 0:					//x方向(行方向)
			i2=1,i2j=0;break;		
		case 1:					//y方向(列方向)
			i2=0,i2j=1;break;
		case 2:					//45度方向
			i2=1,i2j=1;break;
		case 3:					//135度方向
			i2=1,i2j=-1;break;
	}

	unsigned char temp3[15]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
	unsigned char temp4[15]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};

begin:
	if (map[wx][wy]!=0)	return;		//如果该点已经落过子了，则返回
	i3=0;
	ix=i2;			//x方向
	iy=i2j;			//y方向
	ia=1,ib=1;

	/*
		在计算棋型数据时,以X方向(st=0)为例说明,其他方向类似
	*/
	/*
	if (nx==6 && ny==8 && st==1) {
		AfxMessageBox("123");
	}
	*/


	//计算当前点的左边(以当前点为中心,x坐标减少，y坐标减少)有多少个和要计算的子颜色一样的子//
	x=map[wx-ix][wy-iy];
	while(!(x!=(int)style+1||wx-ix<0||wy-iy<0))
	{
		ia++;
		ix+=i2;
		iy+=i2j;
		x=map[wx-ix][wy-iy];

	} 

	//x方向和y方向的增加子重新赋值
	ix=i2,iy=i2j;

	//计算当前点的左边(以当前点为中心,x坐标增加，y坐标增加)有多少个和要计算的子颜色一样的子//
	x=map[wx+ix][wy+iy];
	while(!(x!=(int)style+1||wx+ix>14||wy+iy>14))
	{
		ix+=i2;
		iy+=i2j;
		ib++;	
		x=map[wx+ix][wy+iy];
	} 


	/*
		当前点周围没有颜色相同的子,则将当前点分别左、右移一格后检查
	*/
	if (ib==1&&ia==1)		
	{
		
		if (tem3==0)		//判断当前点右边子的情况
		{
			wx+=i2,wy+=i2j;	
			tem3=1;
			//MessageBox(GetActiveWindow(),"当前情况是H0H","提示",MB_OK);
			goto begin;
		}
		else				//判断当前点左边子的情况
		{
			if (tem3==1)	
			{
				wx-=i2*2,wy-=i2j*2;
				tem3=2;
				goto begin;
			}
			else		//如果当前点左右两边均是空或者没有和判断点颜色相同的子,则不展开该点的预测数据(退出)
			{
				if (tem3==2) return;
			}
		}
		
	}

	ix=0,iy=0;


	//分不同方向进行判断在判断点落子后棋局的状态
	switch (st)
	{
		case 0:			//x方向
			{
				m1=(ia!=1&&ib==1);	//m1表示当前点左边有相同颜色的子>1个,右边没有相同颜色的子
				m3=(ib!=1&&ia==1);	//m3表示当前点右边有相同颜色的子>1个,左边没有相同颜色的子

				/*
					计算当前子左边和右边的情况，并保存在temp3和temp4数组中，分为几种情况:
						(1) 如果ia和ib均大于1,则在判断点左边取ia位,右边取ib位,temp3和temp4数组中内容相同
							例如ia=2;ib=2，则temp3=temp4 = #H*H#(#表示除H外的任意数字,*表示判断点)
						(2) 如果ia>1,ib=1，则在
							判断点左边取ia+1位,右边不取,放到数组temp3中
							判断点左边取ia位,右边取1位,放到数组temp4中

							例如ia=3,ib=1,则temp3=##HH*(#表示除H外的任意数字,*表示判断点)
											temp4=#HH*#(#表示除H外的任意数字,*表示判断点)
						(3) 如果ia=1,ib>1，则在
							判断点左边取1位,右边取ib位,放到数组temp3中
							判断点左边不取,右边取ib+1位,放到数组temp4中

							例如ia=1,ib=3,则temp3=#*HH#(#表示除H外的任意数字,*表示判断点)
											temp4=*HH##(#表示除H外的任意数字,*表示判断点)
							
				*/

				//取左边子的状态放到temp3数组中(子的格式为ia+ib+1个(包括判断点))
				for(i=0; i<1+ia+ib;i++)
				{
					tem1=wx-ia+ix-m1;
					if (tem1<0||tem1>14)	//超过边界行列,不进行后面的处理
					{	ix+=1;
						continue;
					}

					x=map[tem1][wy];				//取该点子的状态
					temp3[i3]=ntoc(x,type,style);	//取该点子的状态(0或1)转换为H或B	

					ix+=1;
					i3++;
				}

				//取右边子的状态放到temp4数组中(子的格式为ia+ib+1个(包括判断点))
				ix=0,i3=0;
				for (i=0 ; i<1+ia+ib;i++)
				{
					tem1=wx+ib-ix+m3;
					if (tem1<0||tem1>14)	//超过边界行列,不进行后面的处理	
					{	ix+=1;
						continue;
					}

					x=map[tem1][wy];				//取该点子的状态	
					temp4[i3]=ntoc(x,type,style);	//取该点子的状态(0或1)转换为H或B
					
					ix+=1;
					i3++;
				}

				break;
			}

		//y方向的判断同x方向
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

		//45度方向的判断同x方向
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

		//135度方向的判断同x方向
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
		以下根据判断点落子后棋局的状态判断该点在当前棋局状态的重要程度(优先级),判断的方法是和预先
			定义好的棋局状态(保存在wds(dim.h)这个变量)进行比较，该点的棋型值为该点状态在棋局中的
			序号，序号越小,优先级越高
	*/
	if ( (strcmp("00H0",(const char *)&temp3[1])==0 || strcmp("00H0",(const char *)&temp4[1])==0 || strcmp("00H0",(const char *)&temp3[0])==0 || strcmp("00H0",(const char *)&temp4[0])==0)&&tem3!=0)return;
	if ( (strcmp("00B0",(const char *)&temp3[1])==0 || strcmp("00B0",(const char *)&temp4[1])==0 || strcmp("00B0",(const char *)&temp3[0])==0 || strcmp("00B0",(const char *)&temp4[0])==0)&&tem3!=0)return;
	if ( (strcmp("00HHHB",(const char *)&temp3[1])==0 || strcmp("00HHHB",(const char *)&temp4[1])==0 || strcmp("00HHHB",(const char *)&temp3[0])==0 || strcmp("00HHHB",(const char *)&temp4[0])==0)&&tem3!=0)return;

	/*++此处添加更多的屏蔽++*/
	if (tem3==0)	{
		//for (i=0 ; i<=27 ; i++)		//测试添加的,原始是下面这条语句
		for (i=0 ; i<=61 ; i++)
			{
				if (strcmp(wds[i],(const char *)&temp3[1])==0||strcmp(wds[i],(const char *)&temp4[1])==0||strcmp(wds[i],(const char *)&temp3[0])==0||strcmp(wds[i],(const char *)&temp4[0])==0)
				{
					if (player==false)
					{
						//写机器使用的棋型数据

						/*
						if (pc[nx][ny][st]!=255) {
							MessageBox(GetActiveWindow(),"覆盖原始的棋型数据","提示",MB_OK);
						}
						*/
						pc[nx][ny][st]=i;
						return;
					}	
					else
					{
						//写人这一方使用的棋型数据
						user[nx][ny][st]=i;
						return;
					}
				}
			}
	}
	else	{
		//for (i=0 ; i<=27 ; i++)		//测试添加的,原始是下面这条语句
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
	AIGO:五子棋人工智能的主函数。参数
		color
			false		白子
			true		黑子
	返回值：应该在第几行几列落子。
	存在的问题:
		(1) 不稳定,存在优先级计算不正确的情况,活3、冲5等均不处理的情况
*/
CPoint wzq::AiGo(bool color)
{
	//初始化返回点的坐标为-1,-1
	CPoint turnback(-1,-1);

	//清空机器使用的棋型数据
	clear(false);

	/*
		根据目前的棋局设置机器使用的棋型数据
	*/
	fillin(color,false,true);			//机器使用的棋型数据(己方占据该点的棋型)
	fillin(!color,false,false);			//机器使用的棋型数据(对方占据该点的棋型)

	//计算预测步数
	wzq::aitype2 =getaitype();
	unsigned char found=255;

	/*
		在所有棋型数据中，找优先级最小的那个点(数据越小表示优先级越高)
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
		计算应该走那一步
		(1) 如果返回点的优先级<23(参见dim.h)，表示该步是机器必须要响应的棋局(唯一必走棋,否则就5连了)
			所以没有最优，机器必须走该唯一必走棋
		(2) 如果可以选择，则调用getmax函数计算走哪一步最优.
	*/
	if (found<=23) 
	{
		//MessageBox(GetActiveWindow(),"唯一必走棋盘","提示",MB_OK);
		return turnback;
	}
	else
		return getmax(color);
}

/*
	将nicest2数组中的所有元素设置为0
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
	将黑子和白子(0,1或者true和false)转换为表示黑子字符(H)和白子的字符(B)
*/
char wzq::ntoc(char num,bool type,bool style)
{
	if (num==0)
		return '0';
	else if (type==true)		//在type参数为true的情况下,0表示黑子,1表示白子
	{
		if (num==(int)style+1)
			return 'H';
		else 
			return 'B';
	}
	else						//在type参数为false的情况下,0表示黑子,1表示白子
	{
		if (num!=(int)style+1)
			return 'H';
		else 
			return 'B';
	}
}

/*
	预测下几步的走法，该函数是一个递归函数。递归终止条件是：
		(1) 预测步数已经达到设置的步数(初级-6;中级-10;高级-20)
		(2) 有一方已经获胜
	参数含义:
		int x,y		预测点的坐标(在函数调用过程中不断变化)
		color		落子的颜色
		nu			预测步数
		inx inx,iny	原始预测点的坐标
	返回值:
		函数本身并没有返回值，返回值通过nicest2[inx][iny]这个数组元素来传递,该数组元素的含义为:
			1		已方输
			2		已方赢
			3		不能判断胜负

	存在问题(?):
		预测得不准确，先处理完保存和加载功能后在来处理

*/
void wzq::checkgo(int x,int y,bool color,int nu,int inx,int iny)//预测函数 
{
	//模拟落子
	//wzq::trygo[x][y]=(char)color+1;
	wzq::map[x][y]=(char)color+1;

	//清除人方使用的棋型数据
	clear(true);


	//根据当前的棋局计算人方使用的棋型数据()
	fillin(color,true,true);		//人方使用的棋型数据(落子颜色)-己方
	fillin(!color,true,false);		//人方使用的棋型数据(另外一方的响应棋型)-对方


	//从棋型数据中返回优先级最小的点(该点是预测的响应点)
	CPoint temp=getbg(true);


	bool four1=false,four2=false,three1=false,three2=false;
	bool four3=false,four4=false,three3=false,three4=false;

	/*
		检查要预测的点落子后,检查棋局的状态( 参见IDB_STATUS)
		在4个方向分别检查是否已经分出胜负,是否有4连,3连等等....
	*/

	for (int i=0 ; i<=3 ; i++)
	{
		//"0BBBBB0",	"0BBBBBH",	"HBBBBBH",		对方已经5连,输了
		if (user[temp.x][temp.y][i]>=3&&user[temp.x][temp.y][i]<=5)
		{
			wzq::nicest2[inx][iny]=2;//lose 
			return;
		}
		else
		{
			//"0HHHHH0",	"0HHHHHB",	"BHHHHHB", 己方已经5连，赢了
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
						己方已经4连了
					*/

					if(four1==true)	four2=true;
					else four1=true;
				}
				else
				{
					/*
						15,16,17,18,19 "0BBBB0",	"0BBBBH",	"0BB0BB0",	"0BB0BBH","HBB0BBH",\
						20,21,22,23    "0B0BBB0",	"HB0BBB0",	"0B0BBBH",	"HB0BBBH",\
						对方已经4连了
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
								//对方已经3连了
								if(three1==true)three2=true;else three1=true;
						}
						else
						{
							if (user[temp.x][temp.y][i]==26||user[temp.x][temp.y][i]==27)
							{	
								//己方已经3连了
								if(three3==true)three4=true;else three3=true;
							}
						}
					}
				}
			}
		}
	}


	/*
		根据棋局状态进行胜负判断(未进行禁手判断)。判断规则是
			(1) 两个活3			胜
			(2) 两个活4			胜
			(2) 1个活3+1个活4	胜
		可以增加更多的规则

	*/
	if (three1+three2+four1+four2>=2)		//用户响应后形成后活3+活4数量>2,则用户方胜
	{
		wzq::nicest2[inx][iny]=1;		//己方输
		return;
	}
	else
	{
		if (three3+three4+four3+four4>=2)	//用户响应后己方形成的活3+活4数量>2,则己方胜
		{
			wzq::nicest2[inx][iny]=2;	//己方赢
			return;
		}
	}

	//判断是否预测步数已经达到指定的步数
	if (nu>=wzq::aitype2)
	{
		//已经达到还没有判断出胜负
		wzq::nicest2[inx][iny]=3;
		return;
	}
	else {
		//继续调用该递归函数,注意是用!color调用的。
		int xxx=nu+1;

		checkgo(temp.x,temp.y,!color,xxx,inx,iny);
	}
}

/*
	从棋型数据中,返回重要程度最大的一点,主要是两种情况:
		(1) 不考虑预测的情况,选择优先级最小的一点(数据越小,优先击级越高,越重要)
		(2) 考虑预测的情况,则需要考虑人方如何应对的情况，在人方应对的情况下，再考虑机器如何走.....
				直到分出胜负或者达到预测步数为止
	存在问题(?)
		在棋盘上下的点越多，该函数内的循环次数就越多
*/
CPoint wzq::getmax(bool color)
{
	//初始化返回数值点的坐标
	CPoint turnback(0,0);
	setall();		//将nicest2数组中的所有元素设置为0
	bool lb_backupFlag=false;		//当前棋型数据的备份标志(true-已备份,false-未备份)
	
	int li_count=0;		//调试增加

	//将当前的棋盘数据备份到trygo这个数组中
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

	//在所有没有调用过checkgo函数的节点中,查找优先级最小的节点,保存在坐标fx和fy中
	for (ix=0 ;ix<=14;ix++)
		{
			for (int iy=0;iy<=14;iy++)
			{
				if (wzq::nicest2[ix][iy]==0)			//该点没有调用过checkgo函数
				{
					if (bj2(ix,iy,fx,fy,false)==true) {
						fx=ix;		//将最小点的x坐标保存在fx中
						fy=iy;		//将最小点的x坐标保存在fy中
						x=1;
					}
				}
			}	
		}

	//如果没有找到
	if (x==0) {	
		x=0;
		for (int ix=0 ;ix<=14;ix++)
		{
			for (int iy=0 ;iy<=14;iy++)
			{
				if (wzq::nicest2[ix][iy]!=1)		//在所有保证不输的节点中查找优先级的最小的点
				{
					if (bj2(ix,iy,turnback.x,turnback.y,false)==true) {
						turnback.x=ix;
						turnback.y=iy;
						x=1;}
				}
			}
		}
		
		//在不输的节点中没有找到比(0,1)节点优先级更小的点，则在所有的节点中查找优先级最小的节点
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

		//在所有的节点中查找优先级最小的节点,则棋子下在中心点
		if (x==0) turnback.x =7,turnback.y =7;

		//恢复正常的棋型数据
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

	//调用checkgo函数进行预测(下完该点后,棋局的状态是什么?)
	wzq::checkgo(fx,fy, color,1,fx,fy);

	//判断函数的返回值,通过nicest2[fx][fy]这个数组元素返回
	if (nicest2[fx][fy]==2)			//赢了
	{
		turnback.x=fx,turnback.y=fy;
		//恢复正常的棋型数据
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
		goto begin;				//重来一次
	}
	
}

/*
	函数功能:在棋盘的所有点上，取棋型数据最小的点坐标.
	参数：
		style这个参数实际上是没有用的。
*/
CPoint wzq::getbg(bool style )
{
	CPoint turnback;
	int ix1=0,iy1=0;
	for (int ix=0 ;ix<=14;ix++)
	{
		for (int iy=0 ;iy<=14;iy++)
		{
			//调用函数比较两个点的预测值的大小
			if (bj2(ix,iy,ix1,iy1,style)==true)
			{
				ix1=ix,iy1=iy;
			}
		}
	}

	//返回预测值最小的点的坐标
	turnback.x=ix1;
	turnback.y=iy1;
	return turnback;
}

/*
	函数功能:(?)比较两个点的棋型数据的大小
	参数:
		int x1,int y1		第1个点的坐标
		int x2,int y2		第2个点的坐标
		style				表示是取机器数据还是个人下的数据
	返回值：
		如果第1个点小，则返回true;否则返回false.
*/
bool wzq::bj2(int x1,int y1,int x2,int y2,bool style)
{
	unsigned char a[4];
	unsigned char b[4];
	unsigned char temp1;
	int i;


	if (style==false)			//取机器数据,将第一个点的数据放在数组a，第2个点的数据放在数组b中
	{
		for (i=0 ; i<=3 ;i++)
		{
			a[i]=1;
			a[i]=pc[x1][y1][i];
			b[i]=pc[x2][y2][i];
		}
	}
	else						//取个人下的数据,将第一个点的数据放在数组a，第2个点的数据放在数组b中
	{
		for (i=0 ; i<=3 ;i++)
		{a[i]=1;
		a[i]=user[x1][y1][i];
		b[i]=user[x2][y2][i];
		}
	}

	//冒泡排序，分别对两个数组a和b进行排序
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
		返回结果:
			如果在第1点数据中有小于第2个点的数据，则返回true，否则返回false.
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
	清除棋型数据,机器用的数据放置在pc这个三维数组中，
		人使用的数据放置在user这个三纬数组中,
	参数:style
			false		清除机器用的数据
			true		清除人用的数据
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
	根据设置的智能等级计算应该预测几步的函数
*/
int wzq::getaitype()
{
	if (wzq::AItype==0)
		return 6;		//低智能，预测6步
	else if (wzq::AItype==1)
		return 10;		//中智能，预测10步
	else if (wzq::AItype==2 )
		return 20;		//高智能，预测20步
	else
		return 10;		//默认为中智能，预测10步
}

/*
	保存下棋记录的函数。参数含义
		nx,ny		下棋点的坐标(几行几列)
		style
			false	该点下的是白子
			true	该点下的是黑子
*/
void wzq::setback(int nx,int ny,bool style)
{
	wzq::wzs[wzq::nowd2].used=true;
	wzq::wzs[wzq::nowd2].color=style;
	wzq::wzs[wzq::nowd2].ix =nx;
	wzq::wzs[wzq::nowd2].iy =ny;
	wzq::nowd2++; 
}
