#include "Head.h"
#include <conio.h>
#include <ConsoleEngine/EngineCore.h>
#include "BodyManager.h"
#include "Body.h"

void Head::Move()
{
	int BodyCount = TailBody.size();
	if (BodyCount == 0)
	{
		return;
	}
	else
	{
		int2 PosDir = GetPos();
		int2 NextDir = TailBody[0]->GetPos();
		TailBody[0]->SetPos(PosDir);

		if (BodyCount >= 2)
		{
			for (size_t i = 1; i < BodyCount; i++)
			{
				PosDir = NextDir;
				NextDir = TailBody[i]->GetPos();
				TailBody[i]->SetPos(PosDir);
			}
		}
	}
}

void Head::BodyCollisionCheck()
{
	int TailSize = TailBody.size();
	int2 HeadPos = GetPos();

	for (int i = 0; i < TailSize; i++)
	{
		int2 TailPos = TailBody[i]->GetPos();

		if (TailPos == HeadPos)
		{
			GetCore()->EngineEnd();
		}
	}
}

void Head::WallCollisionCheck()
{
	int2 HeadPos = GetPos();

	int ScreenX = GetCore()->Screen.GetScreenX();
	int ScreenY = GetCore()->Screen.GetScreenY();

	if (0 > HeadPos.Y || HeadPos.Y >= ScreenY)
	{
		GetCore()->EngineEnd();
	}
	if (0 > HeadPos.X || HeadPos.X >= ScreenX)
	{
		GetCore()->EngineEnd();
	}
}

void Head::Update()
{
	int InputCount = _kbhit();
	int Select = 0;
	while (0 < InputCount)
	{
		Select = _getch();
		InputCount = _kbhit();
	}


	int2 CurDir = { 0, 0 };

	switch (Select)
	{
	case 'A':
	case 'a':
		CurDir = Left;
		break;
	case 'S':
	case 's':
		CurDir = Down;
		break;
	case 'W':
	case 'w':
		CurDir = Up;
		break;
	case 'D':
	case 'd':
		CurDir = Right;
		break;
	case '1':
		GetCore()->EngineEnd();
		break;
	default:
		break;
	}

	if (int2{ 0,0 } == CurDir)
	{
		CurDir = PrevDir;
	}

	int2 MoveDir = { 0, 0 };
	if (TailBody.size() != 0)
	{
		MoveDir = TailBody[TailBody.size() - 1]->GetPos();
	}

	if (CurDir != PrevDir * -1)
	{
		Move();
		AddPos(CurDir);
		WallCollisionCheck();
		BodyCollisionCheck();
		PrevDir = CurDir;
	}

	if (nullptr == BodyManager::GetCurBody())
	{
		MsgBoxAssert("먹을수 있는 바디가 존재하지 않습니다.");
		return;
	}

	Body* CurBody = BodyManager::GetCurBody();


	if (CurBody->GetPos() == GetPos())
	{
		if (TailBody.size() == 0)
		{
			CurBody->SetPos(GetPos() - CurDir);
		}
		else
		{
			CurBody->SetPos(MoveDir);
		}
		TailBody.push_back(CurBody);
		CurBody->SetRenderChar('@');
		BodyManager::ResetBody();

		int a = 0;
	}
}

