/////////////////////////////////////////////////////////////////////////////////
//
//
//
//
/////////////////////////////////////////////////////////////////////////////////
#ifndef _LESSON_X_H_
#define _LESSON_X_H_
//
#include <Windows.h>
#include "mycraft.h"
#include "enemystool.h"
#include "bullet.h"

/////////////////////////////////////////////////////////////////////////////////
//
// 游戏总管类。负责处理游戏主循环、游戏初始化、结束等工作
class	CGameMain
{
private:
	int				m_iGameState;				// 游戏状态，0：结束或者等待开始；1：初始化；2：游戏进行中
	std::shared_ptr<MyCraft>   player;
	EnemysTool                 enemysCtrl;
    std::list<std::shared_ptr<Bullet>> myBullets;
    std::list<std::shared_ptr<Bullet>> enemyBullets;
    std::shared_ptr<CTextSprite> playerScore;
    std::shared_ptr<CTextSprite> playerHp;

public:
	CGameMain();            //构造函数
	~CGameMain();           //析构函数

	// Get方法
	int				GetGameState()											{ return m_iGameState; }

	// Set方法
	void			SetGameState( const int iState )				{ m_iGameState	=	iState; }

	// 游戏主循环等
	void			GameMainLoop( float	fDeltaTime );
	void			GameInit();
	void			GameRun( float fDeltaTime );
	void			GameEnd();
    void  OnKeyDown( const int iKey, const int iAltPress, const int iShiftPress, const int iCtrlPress );
	void  OnKeyUp( const int iKey );
	void  onLoop();
};

/////////////////////////////////////////////////////////////////////////////////
//
extern CGameMain	g_GameMain;

#endif // _LESSON_X_H_
