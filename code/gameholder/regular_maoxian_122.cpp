#include "gameholder_pch.h"
#include "regular_maoxian_122.h"
#include "scene.h"
#include "checkpoint.h"
#include "event_define.h"
#include "point_monster.h"
#include "point_touch.h"
#include "point_treasure.h"
#include "point_barrel.h"
#include "point_trigger.h"
#include "monster.h"
#include "spawn.h"
#include "point_barrel.h"
#include "rog_regular_event_player_dead.h"
#include "rog_regular_event_monster_clear.h"  //怪物清空
#include "rog_regular_event_timer.h"
#include "rog_regular_event_combo_kill.h"
// 关卡类的构造函数
RegularMaoXian_122::RegularMaoXian_122(RegularDoc* pDoc) :
RegularMaoXianBase(pDoc)
{

}
// 关卡类的析构函数
RegularMaoXian_122::~RegularMaoXian_122()
{

}
// 关卡开始时的,关卡内容配置
void RegularMaoXian_122::FirstUpdate()
{
	RegularMaoXianBase::FirstUpdate();

	PointMonster* pPointMonster  = NULL;            // 出怪点
	PointTreasure* pPointTreasure = NULL;           // 宝箱
	PointBarrel* pPointBarrel = NULL;               // 木桶
	PointTouch* pPointTouch = NULL;                 // 采集点
	PointTrigger* pPointTrigger = NULL;             // 触摸石

	/////////////////////////////////////////////////////////////////////////////////
	// 关卡配置
	SetMapLevel(22);

	SetLifeCount(0); // 设置命数

	// 胜利条件
	ROGRegularEvent_MonsterClear* pEventMonsterClear = CnNew ROGRegularEvent_MonsterClear(this);
	AddSucceedEvent(pEventMonsterClear); // 清空全部怪

	// 失败条件
	ROGRegularEvent_PlayerDead* pEventPlayerDead = CnNew ROGRegularEvent_PlayerDead(this);
	AddFailedEvent(pEventPlayerDead); // 玩家死亡

	ROGRegularEvent_Timer* pEventFailed_Timer = CnNew ROGRegularEvent_Timer(this);
	pEventFailed_Timer->SetTime(1000*300);            // n秒限时
	AddFailedEvent(pEventFailed_Timer);

	// 评价条件
	ROGRegularEvent_Timer* pEventScore_Timer = CnNew ROGRegularEvent_Timer(this, true);
	pEventScore_Timer->SetTime(1000*200);            // n秒通关获得一星
	AddScoreEvent(pEventScore_Timer);

	ROGRegularEvent_ComboKill* pEventScore_ComboKill = CnNew ROGRegularEvent_ComboKill(this);
	pEventScore_ComboKill->SetComboKill(5);         // n连杀
	AddScoreEvent(pEventScore_ComboKill);
	////////////////////////////////////////////////////////////////////////////
	pPointMonster = CnNew PointMonster(this, 11);
	pPointMonster->SetRadius(0);
	pPointMonster->SetMonster(3002, 1);         // 1个精英狼人

	pPointMonster = CnNew PointMonster(this, 12);
	pPointMonster->SetRadius(200);
	pPointMonster->SetMonster(3002, 1);
	pPointMonster->SetDefaultMovie();           // 出场演绎
	//pPointMonster->SetDelayTime(500);           // 触发后延时500ms出怪
	//pPointMonster->SetSpawnSpeed(300);          // 出怪间隔300ms
	pPointMonster->SetTriggerID(13);             // trigger 13 触发

	pPointMonster = CnNew PointMonster(this, 13);
	pPointMonster->SetRadius(200);
	pPointMonster->SetMonster(3001, 2);
	pPointMonster->SetDefaultMovie();
	//pPointMonster->SetDelayTime(1000);
	pPointMonster->SetSpawnSpeed(300);
	pPointMonster->SetTriggerID(13);

	pPointBarrel = CnNew PointBarrel(this, 15);     // 木桶
	pPointBarrel->SetRadius(150);
	pPointBarrel->SetNumber(3);                     // 3个


	////////////////////////////////////////////////////////////////////////////

	pPointMonster = CnNew PointMonster(this, 20);
	pPointMonster->SetRadius(400);
	pPointMonster->SetMonster(3009, 1);
	//pPointMonster->SetDefaultMovie();
	pPointMonster->SetQuality(QUALITY_GREEN);
	pPointMonster->SetTriggerID(17);

	pPointTouch = CnNew PointTouch(this, 21);      // 采集点
	pPointTouch->SetShowID(4004);
	pPointTouch->SetTouchTime(2000);

	////////////////////////////////////////////////////////////////////////////

	pPointBarrel = CnNew PointBarrel(this, 32);
	pPointBarrel->SetRadius(200);
	pPointBarrel->SetNumber(3);



	pPointMonster = CnNew PointMonster(this, 34);
	pPointMonster->SetRadius(300);
	pPointMonster->SetMonster(3002, 3);
	pPointMonster->SetDefaultMovie();

	pPointTrigger = CnNew PointTrigger(this, 31);           // 触摸石
	pPointTrigger->SetShowID(4002);
	pPointTrigger->LinkTrigger(pPointMonster);

	if (Crown::RandomPercent(50))
	{   

		pPointMonster = CnNew PointMonster(this, 35);
		pPointMonster->SetRadius(300);
		pPointMonster->SetMonster(Crown::RandomOneNumber(2, 3029, 3009), 1);
		pPointMonster->LinkTrigger(pPointTrigger);


		pPointMonster = CnNew PointMonster(this, 36);
		pPointMonster->SetRadius(300);
		pPointMonster->SetMonster(Crown::RandomOneNumber(2, 3001, 3002), 3);
		pPointMonster->LinkTrigger(pPointTrigger);

	}
	else
	{
		// 出宝箱
		pPointTreasure = CnNew PointTreasure(this,35);
		pPointTreasure->SetShowID(4001);
		pPointTreasure->LinkTrigger(pPointTrigger);

	}

	////////////////////////////////////////////////////////////////////////////

	pPointMonster = CnNew PointMonster(this, 41);
	pPointMonster->SetRadius(300);
	pPointMonster->SetMonster(3012, 1);
	pPointMonster->SetQuality(QUALITY_GREEN);

	pPointMonster = CnNew PointMonster(this, 41);
	pPointMonster->SetRadius(300);
	pPointMonster->SetMonster(3001, 1);

	pPointMonster = CnNew PointMonster(this, 42);
	pPointMonster->SetRadius(100);
	pPointMonster->SetMonster(3001, 1);

	pPointMonster = CnNew PointMonster(this, 42);
	pPointMonster->SetRadius(100);
	pPointMonster->SetMonster(3001, 1);

	pPointBarrel = CnNew PointBarrel(this, 43);       //木桶
	pPointBarrel->SetRadius(200);
	pPointBarrel->SetNumber(3);

	////////////////////////////////////////////////////////////////////////////



	pPointMonster = CnNew PointMonster(this, 55);
	pPointMonster->SetRadius(0);
	pPointMonster->SetMonster(3009, 1);


	pPointMonster = CnNew PointMonster(this, 52);
	pPointMonster->SetRadius(200);
	pPointMonster->SetMonster(3001, 3);


	pPointMonster = CnNew PointMonster(this, 53);
	pPointMonster->SetRadius(300);
	pPointMonster->SetMonster(3001, 2);
	//pPointMonster->SetDefaultMovie();
	//pPointMonster->SetDelayTime(200);
	//pPointMonster->SetSpawnSpeed(300);


	pPointMonster = CnNew PointMonster(this, 54);
	pPointMonster->SetRadius(0);
	pPointMonster->SetMonster(3002, 1);
	pPointMonster->SetDefaultMovie();
	pPointMonster->SetDelayTime(100);
	pPointMonster->SetSpawnSpeed(200);


	pPointTreasure = CnNew PointTreasure(this, 56);         // 宝箱
	pPointTreasure->SetShowID(4001);

	////////////////////////////////////////////////////////////////////////////

	pPointMonster = CnNew PointMonster(this, 61);
	pPointMonster->SetRadius(200);
	pPointMonster->SetMonster(3031, 1);
	pPointMonster->SetQuality(QUALITY_GREEN);

	pPointMonster = CnNew PointMonster(this, 61);
	pPointMonster->SetRadius(200);
	pPointMonster->SetMonster(3018, 2);

	////////////////////////////////////////////////////////////////////////////
	// boss
	pPointMonster = CnNew PointMonster(this, 70);
	pPointMonster->SetRadius(0);
	pPointMonster->SetMonster(3030, 1);
	pPointMonster->SetQuality(QUALITY_GREEN);
	//pPointMonster->SetDefaultMovie();
	pPointMonster->SetTriggerID(10);

	pPointTreasure = CnNew PointTreasure(this,74);
	pPointTreasure->SetShowID(4001);
	pPointTreasure->LinkTrigger(pPointMonster);

	pPointMonster = CnNew PointMonster(this, 71);
	pPointMonster->SetRadius(100);
	pPointMonster->SetMonster(3012, 2);
	//pPointMonster->SetMax(1);                   // 一次1个，共4个
	//pPointMonster->SetDefaultMovie();
	//pPointMonster->SetDelayTime(100);
	//pPointMonster->SetSpawnSpeed(200);
	//pPointMonster->SetTriggerID(10);

	pPointMonster = CnNew PointMonster(this, 72);
	pPointMonster->SetRadius(200);
	pPointMonster->SetMonster(3001, 2);
	pPointMonster->SetMax(1);                   // 一次1个，共4个
	pPointMonster->SetDefaultMovie();
	pPointMonster->SetDelayTime(200);
	pPointMonster->SetSpawnSpeed(200);
	pPointMonster->SetTriggerID(10);

	pPointMonster = CnNew PointMonster(this, 73);
	pPointMonster->SetRadius(200);
	pPointMonster->SetMonster(3002, 2);
	pPointMonster->SetMax(1);                   // 一次1个，共4个
	pPointMonster->SetDefaultMovie();
	pPointMonster->SetDelayTime(300);
	pPointMonster->SetSpawnSpeed(200);
	pPointMonster->SetTriggerID(10);
}
