/////////////////////////////////////////////////////////////////////////////////
//
//
//
//
/////////////////////////////////////////////////////////////////////////////////
#include <Stdio.h>
#include "CommonClass.h"
#include "LessonX.h"
#include <fstream>
////////////////////////////////////////////////////////////////////////////////
//
//
CGameMain		g_GameMain;

CSprite* beginWords = new CSprite("GameBegin");  //“空格开始”

bool checkBulletIsOverScreen(auto& bullets) {
    for (auto b = std::begin(bullets); b != std::end(bullets); ++b) {
        if ((*b)->isOverScreen()) {
            (*b)->DeleteSprite();
            bullets.erase(b);
            return true;
        }
    }
    return false;
}

bool checkMyBulletIsDoen(auto& myBullets, auto& target) {
    for (auto mb = std::begin(myBullets); mb != std::end(myBullets); ++mb) {
        for (auto t = std::begin(target); t != std::end(target); ++t) {
            if ( (*t)->IsPointInSprite((*mb)->GetSpritePositionX(), (*mb)->GetSpritePositionY()) ) {
                (*mb)->DeleteSprite();
                myBullets.erase(mb);
                (*t)->setHp((*t)->getHp() - 1);
                if ((*t)->getHp() <= 0) {
                    (*t)->beenDown(); /// ok
                    (*t)->DeleteSprite();
                    target.erase(t);
                    return true;
                }
                return false;
            }
        }
    }
    return false;
}

bool checkPlayerIsDoen(auto& player, auto& target) {
    for (auto t = std::begin(target); t != std::end(target); ++t) {
        if (player->IsPointInSprite((*t)->GetSpritePositionX(), (*t)->GetSpritePositionY())) {
            player->setHp(player->getHp() - 1);
            (*t)->beenDown();
            (*t)->DeleteSprite();
            target.erase(t);
            return true;
        }
    }
    return false;
}


//==============================================================================
//
// 大体的程序流程为：GameMainLoop函数为主循环函数，在引擎每帧刷新屏幕图像之后，都会被调用一次。

//==============================================================================
//
// 构造函数
CGameMain::CGameMain()
{
	m_iGameState			=	0;
	player = nullptr;
	myBullets = std::list<std::shared_ptr<Bullet>>();
	enemyBullets = std::list<std::shared_ptr<Bullet>>();
    playerScore = std::shared_ptr<CTextSprite>();
    playerHp = std::shared_ptr<CTextSprite>();
}
//==============================================================================
//
// 析构函数
CGameMain::~CGameMain()
{
}

//==============================================================================
//
// 游戏主循环，此函数将被不停的调用，引擎每刷新一次屏幕，此函数即被调用一次
// 用以处理游戏的开始、进行中、结束等各种状态.
// 函数参数fDeltaTime : 上次调用本函数到此次调用本函数的时间间隔，单位：秒
void CGameMain::GameMainLoop( float	fDeltaTime )
{
	switch( GetGameState() )
	{
		// 初始化游戏，清空上一局相关数据
	case 1:
		{
			GameInit();
			SetGameState(2); // 初始化之后，将游戏状态设置为进行中
		}
		break;

		// 游戏进行中，处理各种游戏逻辑
	case 2:
		{
			// TODO 修改此处游戏循环条件，完成正确游戏逻辑
			if( player->getHp() > 0 )
			{
				GameRun( fDeltaTime );
			}
			else // 游戏结束。调用游戏结算函数，并把游戏状态修改为结束状态
			{
				SetGameState(0);
				GameEnd();
			}
		}
		break;

		// 游戏结束/等待按空格键开始
	case 0:
	default:
		break;
	};
}
//=============================================================================
//
// 每局开始前进行初始化，清空上一局相关数据
void CGameMain::GameInit()
{
    beginWords->SetSpriteVisible(false);
    player = std::make_shared<MyCraft>("ControlSprite");
    player->SetSpriteVisible(true);
    playerScore = std::make_shared<CTextSprite>("playerScore");
    playerHp = std::make_shared<CTextSprite>("playerHp");
}
//=============================================================================
//
// 每局游戏进行中
void CGameMain::GameRun( float fDeltaTime )
{
    onLoop();
    auto mB = player->onFire(fDeltaTime);
    if (mB != nullptr) {
        myBullets.push_back(mB);
    }

    enemysCtrl.creatEnemy(fDeltaTime);
    enemysCtrl.onLooop(fDeltaTime);

    for (auto enemy = std::begin(enemysCtrl.enemys); enemy != std::end(enemysCtrl.enemys); ++enemy) {
        auto eB = (*enemy)->onFire(fDeltaTime);
        if (eB != nullptr)
            enemyBullets.push_back(eB);
    }
}
//=============================================================================
//
// 本局游戏结束
void CGameMain::GameEnd()
{
    player->beenDown();
    player->SetSpriteVisible(false);
    playerHp->SetTextValue(0);
    beginWords->SetSpriteVisible(true);
    std::ofstream fout("PlayerScore.txt", std::ios::out | std::ios::app);
    fout << "Player's score is : " << player->getScore() << std::endl;
}

void CGameMain::OnKeyDown( const int iKey, const int iAltPress, const int iShiftPress, const int iCtrlPress )
{
    if( KEY_SPACE == iKey && 0 == GetGameState() )
        SetGameState( 1 );
    //当游戏状态为2时
    if( 2 == GetGameState() ) {
        player->onMove(true, iKey);
        if (iKey == KEY_SPACE)
            player->setFire(true);
    }
}
void CGameMain::OnKeyUp( const int iKey )
{
    if( 2 == GetGameState() ) {
        player->onMove(false, iKey);
        if (iKey == KEY_SPACE)
            player->setFire(false);
    }
}

void CGameMain::onLoop() {
    playerScore->SetTextValue(player->getScore());
    playerHp->SetTextValue(player->getHp());
    checkBulletIsOverScreen(myBullets);
    checkBulletIsOverScreen(enemyBullets);
    if (checkMyBulletIsDoen(myBullets, enemysCtrl.enemys)) player->setScore(player->getScore() + 10);
    checkMyBulletIsDoen(myBullets, enemyBullets);
    checkPlayerIsDoen(player, enemyBullets);
    checkPlayerIsDoen(player, enemysCtrl.enemys);
}

