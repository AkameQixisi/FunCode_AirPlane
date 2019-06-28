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

CSprite* beginWords = new CSprite("GameBegin");  //���ո�ʼ��

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
// ����ĳ�������Ϊ��GameMainLoop����Ϊ��ѭ��������������ÿ֡ˢ����Ļͼ��֮�󣬶��ᱻ����һ�Ρ�

//==============================================================================
//
// ���캯��
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
// ��������
CGameMain::~CGameMain()
{
}

//==============================================================================
//
// ��Ϸ��ѭ�����˺���������ͣ�ĵ��ã�����ÿˢ��һ����Ļ���˺�����������һ��
// ���Դ�����Ϸ�Ŀ�ʼ�������С������ȸ���״̬.
// ��������fDeltaTime : �ϴε��ñ��������˴ε��ñ�������ʱ��������λ����
void CGameMain::GameMainLoop( float	fDeltaTime )
{
	switch( GetGameState() )
	{
		// ��ʼ����Ϸ�������һ���������
	case 1:
		{
			GameInit();
			SetGameState(2); // ��ʼ��֮�󣬽���Ϸ״̬����Ϊ������
		}
		break;

		// ��Ϸ�����У����������Ϸ�߼�
	case 2:
		{
			// TODO �޸Ĵ˴���Ϸѭ�������������ȷ��Ϸ�߼�
			if( player->getHp() > 0 )
			{
				GameRun( fDeltaTime );
			}
			else // ��Ϸ������������Ϸ���㺯����������Ϸ״̬�޸�Ϊ����״̬
			{
				SetGameState(0);
				GameEnd();
			}
		}
		break;

		// ��Ϸ����/�ȴ����ո����ʼ
	case 0:
	default:
		break;
	};
}
//=============================================================================
//
// ÿ�ֿ�ʼǰ���г�ʼ���������һ���������
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
// ÿ����Ϸ������
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
// ������Ϸ����
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
    //����Ϸ״̬Ϊ2ʱ
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

