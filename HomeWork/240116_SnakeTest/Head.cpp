#include "Head.h"
#include <conio.h>
#include <ConsoleEngine/EngineCore.h>
#include "BodyManager.h"
#include "Body.h"

// 2. ���� �̵��� �ؼ� CurBody�� ȹ���ߴٸ� �� �������� �� �ٵ�� ���� ����;� �Ѵ�.

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

void Head::Update()
{
	int InputCount = _kbhit();
	if (0 == InputCount)
	{
		return;
	}

	int Select = _getch();
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
	int2 MoveDir = { 0, 0 };
	if (TailBody.size() != 0)
	{
		MoveDir = TailBody[TailBody.size() - 1]->GetPos();
	}
	if (CurDir != PrevDir * -1)
	{
		Move();
		AddPos(CurDir);
		PrevDir = CurDir;
	}

	if (nullptr == BodyManager::GetCurBody())
	{
		MsgBoxAssert("������ �ִ� �ٵ� �������� �ʽ��ϴ�.");
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