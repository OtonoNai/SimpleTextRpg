#include "Battle.h"
#include <iostream>

int CalculateDamage(int AttakerAtk, int DamageDivisor, int TargetDef)
{
	int Damage = (AttakerAtk / DamageDivisor) - TargetDef;

	if (Damage < 1)
	{
		Damage = 1;
	}

	return Damage;
}

EBattleResult RunBattle(FPlayer& Player, FMonster& Monster)
{
	std::cout << "[ 전투 시작! ] " << Player.GetName() << " vs " << Monster.GetDisplayName() << std::endl;
	std::cout << std::endl << "계속하려면 Enter" << std::endl;
	std::cin.get();

	while (Player.IsAlive() && Monster.IsAlive())
	{
		std::cout << std::endl << "--- 플레이어 턴 ---" << std::endl;
		std::cout << Player.Attack() << std::endl;

		for (int i = 0; i < Player.GetHitCount(); ++i)
		{
			int Damage = CalculateDamage(Player.GetAtk(), Player.GetDamageDivisor(), Monster.GetDef());
			Monster.TakeDamage(Damage);
			std::cout << Monster.GetDisplayName() << "에게 " << Damage << " 데미지!" << std::endl;

			if (!Monster.IsAlive())
			{
				break;
			}
		}

		std::cout << Monster.GetDisplayName() << " HP : " << Monster.GetHp() << std::endl;

		if (!Monster.IsAlive())
		{
			break;
		}

		std::cout << std::endl << "계속하려면 Enter" << std::endl;
		std::cin.get();

		std::cout << std::endl << "--- 몬스터 턴 ---" << std::endl;

		int MonsterDamage = CalculateDamage(Monster.GetAtk(), 1, Player.GetDef());
		Player.TakeDamage(MonsterDamage);
		std::cout << Monster.GetDisplayName() << "이(가) " << Player.GetName() << "에게 " << MonsterDamage << " 데미지!" << std::endl;
		std::cout << Player.GetName() << " HP : " << Player.GetHp() << std::endl;
	}

	if (Player.IsAlive())
	{
		std::cout << std::endl << "★ 전투 승리!" << std::endl;
		return EBattleResult::Victory;
	}
	else
	{

		std::cout << std::endl << "패배" << std::endl;
		return EBattleResult::Defeat;
	}
}