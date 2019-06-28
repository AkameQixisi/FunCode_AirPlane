//-----------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------
#include "CommonClass.h"
#include "LessonX.h"

///////////////////////////////////////////////////////////////////////////////////////////
//
// 主函数入口
//
//////////////////////////////////////////////////////////////////////////////////////////
int PASCAL WinMain(HINSTANCE hInstance,
                   HINSTANCE hPrevInstance,
                   LPSTR     lpCmdLine,
                   int       nCmdShow)
{
	// 初始化游戏引擎
	if( !CSystem::InitGameEngine( hInstance, lpCmdLine ) )
		return 0;

	// To do : 在此使用API更改窗口标题
	CSystem::SetWindowTitle("LessonX");

	// 引擎主循环，处理屏幕图像刷新等工作
	while( CSystem::EngineMainLoop() )
	{
		// 获取两次调用之间的时间差，传递给游戏逻辑处理
		float	fTimeDelta	=	CSystem::GetTimeDelta();

		// 执行游戏主循环
		g_GameMain.GameMainLoop( fTimeDelta );
	};

	// 关闭游戏引擎
	CSystem::ShutdownGameEngine();
	return 0;
}

//==========================================================================
//
// 引擎捕捉鼠标移动消息后，将调用到本函数
void CSystem::OnMouseMove( const float fMouseX, const float fMouseY )
{
	// 可以在此添加游戏需要的响应函数

}
//==========================================================================
//
// 引擎捕捉鼠标点击消息后，将调用到本函数
void CSystem::OnMouseClick( const int iMouseType, const float fMouseX, const float fMouseY )
{
	// 可以在此添加游戏需要的响应函数

}
//==========================================================================
//
// 引擎捕捉鼠标弹起消息后，将调用到本函数
void CSystem::OnMouseUp( const int iMouseType, const float fMouseX, const float fMouseY )
{
	// 可以在此添加游戏需要的响应函数

}
//==========================================================================
//
// 引擎捕捉键盘按下消息后，将调用到本函数
// bAltPress bShiftPress bCtrlPress 分别为判断Shift，Alt，Ctrl当前是否也处于按下状态。比如可以判断Ctrl+E组合键
void CSystem::OnKeyDown( const int iKey, const bool bAltPress, const bool bShiftPress, const bool bCtrlPress )
{
	// 可以在此添加游戏需要的响应函数
	g_GameMain.OnKeyDown(iKey, bAltPress, bShiftPress, bCtrlPress);

}
//==========================================================================
//
// 引擎捕捉键盘弹起消息后，将调用到本函数
void CSystem::OnKeyUp( const int iKey )
{
	// 可以在此添加游戏需要的响应函数
	g_GameMain.OnKeyUp(iKey);

}

//===========================================================================
//
// 引擎捕捉到精灵与精灵碰撞之后，调用此函数
void CSystem::OnSpriteColSprite( const char *szSrcName, const char *szTarName )
{
}

//===========================================================================
//
// 引擎捕捉到精灵与世界边界碰撞之后，调用此函数.
// iColSide : 0 左边，1 右边，2 上边，3 下边
void CSystem::OnSpriteColWorldLimit( const char *szName, const int iColSide )
{

}

