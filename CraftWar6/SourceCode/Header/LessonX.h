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
// ��Ϸ�ܹ��ࡣ��������Ϸ��ѭ������Ϸ��ʼ���������ȹ���
class	CGameMain
{
private:
	int				m_iGameState;				// ��Ϸ״̬��0���������ߵȴ���ʼ��1����ʼ����2����Ϸ������
	std::shared_ptr<MyCraft>   player;
	EnemysTool                 enemysCtrl;
    std::list<std::shared_ptr<Bullet>> myBullets;
    std::list<std::shared_ptr<Bullet>> enemyBullets;
    std::shared_ptr<CTextSprite> playerScore;
    std::shared_ptr<CTextSprite> playerHp;

public:
	CGameMain();            //���캯��
	~CGameMain();           //��������

	// Get����
	int				GetGameState()											{ return m_iGameState; }

	// Set����
	void			SetGameState( const int iState )				{ m_iGameState	=	iState; }

	// ��Ϸ��ѭ����
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
