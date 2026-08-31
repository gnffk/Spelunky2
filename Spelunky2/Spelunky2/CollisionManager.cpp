#include "pch.h"

#include "CollisionManager.h"
#include "CameraManager.h"
#include "Tile.h"
#include "Player.h"
#include "Boss.h"
#include "CBomb.h"
#include "Snake.h"
#include "ShopMan.h"
#include "UI.h"
#include "BombPackage.h"
#include "RopePackage.h"
#include "ShotGun.h"
#include "Particle.h"
#include "SoundManager.h"

void CCollisionManager::Collision_Rect(list<CObj*> _Dst, list<CObj*> _Src)
{

	RECT	rc{};

	for (auto& Dst : _Dst)
	{
		for (auto& Src : _Src)
		{
			if (IntersectRect(&rc, Dst->Get_Rect(), Src->Get_Rect()))
			{
			
			}
		}
	}
		
}

void CCollisionManager::Collision_RectEx(list<CObj*> _Dst, list<CObj*> _Src)
{
	float	fWidth(0.f), fHeight(0.f);

	for (auto& Dst : _Dst)
	{
		for (auto& Src : _Src)
		{
			if (Check_Rect(Dst, Src, &fWidth, &fHeight))
			{
				// 상 하 충돌
				if (fWidth > fHeight)
				{
					// 상 충돌
					if (Dst->Get_Info()->fY < Src->Get_Info()->fY)
					{
						
						Dst->Set_PosY(-fHeight);
						
					}
					// 하 충돌
					else
					{
						Dst->Set_PosY(fHeight);
					}
				}

				// 좌 우 충돌
				else
				{
					// 좌 충돌
					if (Dst->Get_Info()->fX < Src->Get_Info()->fX)
					{
						Dst->Set_PosX(-fWidth);
					}
					// 우 충돌
					else
					{
						Dst->Set_PosX(fWidth);
					}
				}
			}
		}
	}
}

void CCollisionManager::Collision_RectEx_Player(CObj* Dst, vector<CObj*> _Src)
{
	float	fWidth(0.f), fHeight(0.f);

		for (auto& Src : _Src)
		{

			if (static_cast<CTile*>(Src)->Get_Collision() == CollisionType::FLOOR) {
				if (!static_cast<CPlayer*>(Dst)->Get_Hurt() ) {
					if (Check_Rect(Dst, Src, &fWidth, &fHeight))
					{
						// 상 하 충돌
						if (fWidth > fHeight)
						{
							// 상 충돌
							if (Dst->Get_Info()->fY < Src->Get_Info()->fY)
							{
								dynamic_cast<CPlayer*>(Dst)->SetCurrentState(CPlayer::IDLE);
								dynamic_cast<CPlayer*>(Dst)->SetFalling(true);
								Dst->Set_PosY(-fHeight);
							}

							else
							{
								dynamic_cast<CPlayer*>(Dst)->SetCurrentState(CPlayer::IDLE);
								dynamic_cast<CPlayer*>(Dst)->SetFalling(true);
								Dst->Set_PosY(-fHeight + 10);
							}

						}

						// 좌 우 충돌
						else
						{
							// 좌 충돌
							if (Dst->Get_Info()->fX < Src->Get_Info()->fX)
							{

								Dst->Set_PosX(-fWidth);


							}
							// 우 충돌
							else
							{
								Dst->Set_PosX(fWidth);


							}
						}
					}
					else {
						dynamic_cast<CPlayer*>(Dst)->SetFalling(false);

					}
				}
				else if(static_cast<CPlayer*>(Dst)->Get_Hurt() && 
					static_cast<CPlayer*>(Dst)->GetCurHurtState() != CPlayer::HITIDLE) {
				
					if (Check_Rect(Dst, Src, &fWidth, &fHeight)) {
					
						
			
						if (fWidth > fHeight)
							{
								// 상 충돌
								if (Dst->Get_Info()->fY < Src->Get_Info()->fY)
								{
									if (static_cast<CTile*>(Src)->Get_up()) {
										static_cast<CPlayer*>(Dst)->Set_Collision(true);
										static_cast<CPlayer*>(Dst)->Set_PosY(-fHeight);
									}
									
						
								}

								else if(Dst->Get_Info()->fY > Src->Get_Info()->fY)
								{
									if (static_cast<CTile*>(Src)->Get_down()) {

										static_cast<CPlayer*>(Dst)->Set_Collision(true);
										static_cast<CPlayer*>(Dst)->Set_PosY(fHeight+20);
									}
									
								}

							}

							// 좌 우 충돌
						else
							{
								// 좌 충돌
								if (Dst->Get_Info()->fX < Src->Get_Info()->fX )
								{
									if (static_cast<CTile*>(Src)->Get_left()) {
										static_cast<CPlayer*>(Dst)->Set_Collision(true);
										static_cast<CPlayer*>(Dst)->SetJumpXSpeed(-1);
										static_cast<CPlayer*>(Dst)->Set_PosY(fWidth);

									}
								

								}
								// 우 충돌
								else if(Dst->Get_Info()->fX  > Src->Get_Info()->fX )
								{
									if (static_cast<CTile*>(Src)->Get_right()) {

										static_cast<CPlayer*>(Dst)->Set_Collision(true);
										static_cast<CPlayer*>(Dst)->SetJumpXSpeed(1);
										static_cast<CPlayer*>(Dst)->Set_PosY(-fWidth);
									}


								}
							}

						

					}
						
				}
						
				else if (static_cast<CPlayer*>(Dst)->Get_Hurt() &&
					static_cast<CPlayer*>(Dst)->GetCurHurtState() == CPlayer::HITIDLE) {
					if (Check_Rect(Dst, Src, &fWidth, &fHeight)) {
				
							if (fWidth > fHeight)
							{
								// 상 충돌
								if (Dst->Get_Info()->fY < Src->Get_Info()->fY)
								{
									if (static_cast<CTile*>(Src)->Get_up()) {
										static_cast<CPlayer*>(Dst)->Set_Collision(true);
										Dst->Set_PosY(-fHeight);
									}
							
								}

								else
								{
									if (static_cast<CTile*>(Src)->Get_down()) {
										Dst->Set_PosY(-fHeight + 10);
									}

								
								}

							}

							// 좌 우 충돌
							else
							{
								// 좌 충돌
								if (Dst->Get_Info()->fX < Src->Get_Info()->fX)
								{
									if (static_cast<CTile*>(Src)->Get_right()) {
										Dst->Set_PosX(-fWidth);
									}
									
								}
								// 우 충돌
								else
								{
									if (static_cast<CTile*>(Src)->Get_left()) {
										Dst->Set_PosX(fWidth);
									}
					

								}
							}

					}

				}
			
				
			}
			
			if ((Src)->Get_Collision() == CollisionType::PITFALL) {
				if (Check_Rect(Dst, Src, &fWidth, &fHeight))
				{
					
					dynamic_cast<CPlayer*>(Dst)->SetDead();
				}
			
			}

			if ((Src)->Get_Collision() == CollisionType::LADDER) {
				if (Check_Rect(Dst, Src, &fWidth, &fHeight))
				{
					if (fWidth > fHeight) {
						if (Dst->Get_Info()->fY < Src->Get_Info()->fY -60) {
							if (static_cast<CTile*>(Src)->Get_Ladder()) {
								dynamic_cast<CPlayer*>(Dst)->SetCurrentState(CPlayer::IDLE);
								dynamic_cast<CPlayer*>(Dst)->SetFalling(true);
								Dst->Set_PosY(-fHeight);
						
								static_cast<CTile*>(Src)->Set_PlayerIn(false);
								dynamic_cast<CPlayer*>(Dst)->SetLadder(false);
							}
						
						}
					}
					else {
						dynamic_cast<CPlayer*>(Dst)->SetLadder(true);
						static_cast<CTile*>(Src)->Set_PlayerIn(true);
					}
					
				}
				else {
					if (static_cast<CTile*>(Src)->Get_PlayerIn()) {
						static_cast<CTile*>(Src)->Set_PlayerIn(false);
						dynamic_cast<CPlayer*>(Dst)->SetLadder(false);
					}
		
				}
				
			}

			if ((Src)->Get_Collision() == CollisionType::NEXTSTAGE) {

				if (Check_Rect(Dst, Src, &fWidth, &fHeight))
				{

					(Src)->Set_PlayerIn(true);
					dynamic_cast<CPlayer*>(Dst)->SetNext(true);
				}
				else {
					if ((Src)->Get_PlayerIn()) {

						(Src)->Set_PlayerIn(false);
						dynamic_cast<CPlayer*>(Dst)->SetNext(false);
					}
				}
				
				
			}

		}

}
void CCollisionManager::Collision_RectEx_Player_Item(CObj* Dst, list<CObj*> _Src) {
	float	fWidth(0.f), fHeight(0.f);


	for (auto& Src : _Src)
	{

		if ((Src)->Get_Collision() == CollisionType::LADDER) {
			if (Check_Ladder_Rect(Dst, Src, &fWidth, &fHeight))
			{
				
				// 상 하 충돌
				if (fWidth > fHeight)
				{
					// 상 충돌
					if (Dst->Get_Info()->fY < Src->Get_Info()->fY)
					{
						dynamic_cast<CPlayer*>(Dst)->SetCurrentState(CPlayer::IDLE);
						dynamic_cast<CPlayer*>(Dst)->SetFalling(true);
						
					}

					

				}
				else {
					dynamic_cast<CPlayer*>(Dst)->SetLadder(true);
					(Src)->Set_PlayerIn(true);

				}

					
				
			}
			else {
				if ((Src)->Get_PlayerIn()) {
					
					(Src)->Set_PlayerIn(false);
					dynamic_cast<CPlayer*>(Dst)->SetLadder(false);
				}

			}

		}

		if ((Src)->Get_ItemType() == ITEM_GOLD) {
			if (Check_Rect(Dst, Src, &fWidth, &fHeight)) {
				dynamic_cast<CPlayer*>(Dst)->SetGold(1000);
				Src->Set_Dead(true);
			}
		}

		if ((Src)->Get_ItemType() == ITEM_KEY) {
			if (Check_Rect(Dst, Src, &fWidth, &fHeight)) {
				dynamic_cast<CPlayer*>(Dst)->SetKey(1);
				
				if (dynamic_cast<CPlayer*>(Dst)->Get_Key() == 2) {
					CSoundManager::Get_Instance()->PlaySound(L"journal_page.wav", SOUND_EFFECT, 1.f);
				}
				Src->Set_Dead(true);
			}
		}


		if ((Src)->Get_ItemType() == ITEM_BOMB_PACKAGE && !Src->Get_Store()) {
			if (Check_Rect(Dst, Src, &fWidth, &fHeight)) {
				dynamic_cast<CPlayer*>(Dst)->SetBomb(5);
				Src->Set_Dead(true);
			}
		}
		else if ((Src)->Get_ItemType() == ITEM_BOMB_PACKAGE && Src->Get_Store()) {
			if (static_cast<CBombPackage*>(Src)->GetUI()) {
				if (Check_Rect(Dst, Src, &fWidth, &fHeight)) {
					static_cast<CBombPackage*>(Src)->GetUI()->Set_In(true);
				}
				else {
					static_cast<CBombPackage*>(Src)->GetUI()->Set_In(false);
				}
				
			}
		

		}


		if ((Src)->Get_ItemType() == ITEM_ROPE_PACKAGE && !Src->Get_Store()) {
			if (Check_Rect(Dst, Src, &fWidth, &fHeight)) {
				dynamic_cast<CPlayer*>(Dst)->SetRope(5);
				Src->Set_Dead(true);
			}
		}
		else if ((Src)->Get_ItemType() == ITEM_ROPE_PACKAGE && Src->Get_Store()) {
			if (static_cast<CRopePackage*>(Src)->GetUI()) {
				if (Check_Rect(Dst, Src, &fWidth, &fHeight)) {
					static_cast<CRopePackage*>(Src)->GetUI()->Set_In(true);
				}
				else {
					static_cast<CRopePackage*>(Src)->GetUI()->Set_In(false);
				}

			}
		}

		if ((Src)->Get_ItemType() == ITEM_SHOTGUN && Src->Get_Store()) {
			if (static_cast<CShotGun*>(Src)->GetUI()) {
				if (Check_Rect(Dst, Src, &fWidth, &fHeight)) {
					static_cast<CShotGun*>(Src)->GetUI()->Set_In(true);
				}
				else {
					static_cast<CShotGun*>(Src)->GetUI()->Set_In(false);
				}

			}
		}
	}

}

void CCollisionManager::Collision_RectEx_Player_Item_Hand(CObj* Dst, list<CObj*> _Src, CObj*& m_Hand) {
	float	fWidth(0.f), fHeight(0.f);


	for (auto& Src : _Src)
	{

		if ((Src)->Get_ItemType() == ITEM_SHOTGUN) {
			if (Check_Rect(Dst, Src, &fWidth, &fHeight))
			{
				if (!Src->Get_Store()) {
					m_Hand = Src;
				}
				
				if(Src->Get_Store()){
					if (dynamic_cast<CPlayer*>(Dst)->GetOwn().m_iMoney >= 5000) {
						dynamic_cast<CPlayer*>(Dst)->SetGold(-5000);
						Src->Set_Store(false);
						CSoundManager::Get_Instance()->PlaySound(L"shop_buy.wav", SOUND_EFFECT, 1.f);
				
					}

				}
			}

		}

		if ((Src)->Get_ItemType() == ITEM_BOMB_PACKAGE) {
			if (Check_Rect(Dst, Src, &fWidth, &fHeight))
			{
				if (!Src->Get_Store()) {
					m_Hand = Src;
				}

				if (Src->Get_Store()) {
					if (dynamic_cast<CPlayer*>(Dst)->GetOwn().m_iMoney >= 1000) {
						dynamic_cast<CPlayer*>(Dst)->SetGold(-1000);
						Src->Set_Store(false);
					}

				}
			}

		}

		if ((Src)->Get_ItemType() == ITEM_ROPE_PACKAGE) {
			if (Check_Rect(Dst, Src, &fWidth, &fHeight))
			{
				if (!Src->Get_Store()) {
					m_Hand = Src;
				}

				if (Src->Get_Store()) {
					if (dynamic_cast<CPlayer*>(Dst)->GetOwn().m_iMoney >= 1000) {
						dynamic_cast<CPlayer*>(Dst)->SetGold(-1000);
						Src->Set_Store(false);
					}

				}
			}

		}

		if ((Src)->Get_EnemyType() == ENEMY_SHOPMAN) {
			if (Check_Rect(Dst, Src, &fWidth, &fHeight))
			{
			
				if (Src->Get_Store()) {
					if (dynamic_cast<CPlayer*>(Dst)->GetOwn().m_iMoney >= 5000) {
						dynamic_cast<CPlayer*>(Dst)->SetGold(-5000);
						dynamic_cast<CShopMan*>(Src)->Set_time(GetTickCount());
						dynamic_cast<CShopMan*>(Src)->Set_State(CShopMan::ANSWER);
					}

				}
			}

		}

	}
}

void CCollisionManager::Collision_RectEx_Boss(CObj* Dst, vector<CObj*>& _Src)
{
	float	fWidth(0.f), fHeight(0.f);


	for (auto iter = _Src.begin(); iter != _Src.end(); )
	{

		if (static_cast<CTile*>((*iter))->Get_Collision() == CollisionType::FLOOR) {
			if (Check_Rect(Dst, (*iter), &fWidth, &fHeight))
			{
			
			
				if (Dst->Get_Info()->fY < (*iter)->Get_Info()->fY)
				{

					Dst->Set_PosY(-fHeight);
					if (static_cast<CBoss*>(Dst)->GetBossState() == CBoss::BossState::ATTACK) {
						(*iter)->Set_Dead(true);
						++iter;
						static_cast<CBoss*>(Dst)->SetBroke(true);
					}
				}


				
				if(static_cast<CBoss*>(Dst)->GetBossState() != CBoss::BossState::ATTACK) {
					++iter;
				}
			}
			else {
				++iter;
			}
		}
		else if(static_cast<CTile*>((*iter))->Get_Collision() != CollisionType::FLOOR){
			++iter;
		}
		
	
		if (static_cast<CBoss*>(Dst)->GetBossState() == CBoss::BossState::ATTACKDONE) {
				static_cast<CBoss*>(Dst)->SetBossState(CBoss::BossState::ATTACKDONE);
		}
		
	}


}

void CCollisionManager::Collision_RectEx_Item(list<CObj*> _Dst, vector<CObj*> _Src)
{
	float	fWidth(0.f), fHeight(0.f);

	for (auto& Dst : _Dst)
	{
		for (auto& Src : _Src)
		{
			if ((Src)->Get_Collision() == CollisionType::FLOOR) {
			
				if (Check_Rect(Dst, Src, &fWidth, &fHeight))
				{
					if (Dst->Get_Collision() == CollisionType::C_BOMB) {
					

							// 상 하 충돌
							if (fWidth > fHeight)
							{
								// 상 충돌
								if (Dst->Get_Info()->fY < Src->Get_Info()->fY)
								{

									Dst->Set_PosY(-fHeight);
									Dst->Set_Collision();
									Dst->Set_invincibility(GetTickCount());
								}
								// 하 충돌
								else
								{
									if (Dst->Get_invincibility() + 10 < GetTickCount()) {
									
									}
									Dst->Set_PosY(fHeight + 20);
									Dst->Set_Collision();
									Dst->Set_invincibility(GetTickCount());
									//static_cast<CBomb*>(Dst)->Set_State(CBomb::FALLING);
								}
							}

							// 좌 우 충돌
							else
							{
								if (Dst->Get_invincibility() + 10 < GetTickCount()) {
								
									if (Dst->Get_Info()->fX - 10  < Src->Get_Info()->fX)
									{

										//Dst->Set_PosX(-fWidth-20);
										Dst->Set_Direction(DIR_LEFT);
										Dst->Set_invincibility(GetTickCount());



									}
						
									else if(Dst->Get_Info()->fX + 10 > Src->Get_Info()->fX)
									{

										//Dst->Set_PosX(fWidth + 20);
										Dst->Set_Direction(DIR_RIGHT);
										Dst->Set_invincibility(GetTickCount());

									}
								}
							}
						
					}
						
					if (Dst->Get_Collision() == CollisionType::LADDER) {
					 

							// 상 하 충돌
							if (fWidth > fHeight)
							{
								// 상 충돌
								if (Dst->Get_Info()->fY < Src->Get_Info()->fY)
								{

									Dst->Set_PosY(-fHeight);
									Dst->Set_Collision();
								
								}
								// 하 충돌
								else
								{
									Dst->Set_PosY(fHeight);
									Dst->Set_Collision();
						
								}
							}

						
					}

					if (Dst->Get_Collision() == CollisionType::C_ITEM) {


						// 상 하 충돌
						if (fWidth > fHeight)
						{
							// 상 충돌
							if (Dst->Get_Info()->fY < Src->Get_Info()->fY)
							{

								Dst->Set_PosY(-fHeight);
								Dst->Set_Collision();

							}
						
						}
						else
						{
						

								if (Dst->Get_Info()->fX  < Src->Get_Info()->fX)
								{

									Dst->Set_PosX(-fWidth);
								
									Dst->Set_invincibility(GetTickCount());



								}

								else if (Dst->Get_Info()->fX  > Src->Get_Info()->fX)
								{

									Dst->Set_PosX(fWidth);
					
									Dst->Set_invincibility(GetTickCount());

								}
							
						}

					}

				}
			}
		
		}
	}
}

void CCollisionManager::Collision_RectEx_Player_Boss(CObj* Dst, CObj* Src) {
	float	fWidth(0.f), fHeight(0.f);
	if (Check_Rect(Dst, Src, &fWidth, &fHeight))
	{
		// 상 하 충돌
		if (fWidth > fHeight)
		{
			// 상 충돌
			if (Dst->Get_Info()->fY < Src->Get_Info()->fY)
			{
				dynamic_cast<CPlayer*>(Dst)->SetCurrentState(CPlayer::IDLE);
				dynamic_cast<CPlayer*>(Dst)->SetFalling(true);
				Dst->Set_PosY(-fHeight);

			}
			// 하 충돌
			else
			{
				Dst->Set_PosY(fHeight);
				Dst->Set_Dead(true);
			}
		}

		// 좌 우 충돌
		else
		{
			// 좌 충돌
			if (Dst->Get_Info()->fX < Src->Get_Info()->fX)
			{
				Dst->Set_PosX(-fWidth);
			}
			// 우 충돌
			else
			{
				Dst->Set_PosX(fWidth);
			}
		}
	}
}

void CCollisionManager::Collision_RectEx_Enemy(list<CObj*> _Dst, vector<CObj*> _Src)
{
	for (auto& Dst : _Dst)
	{
		for (auto& Src : _Src)
		{
			float	fWidth(0.f), fHeight(0.f);
			if ((Src)->Get_Collision() == CollisionType::FLOOR) {
				if (Dst->Get_EnemyType() == ENEMY_BAT) {
					if (Check_Rect(Dst, Src, &fWidth, &fHeight))
					{
						// 상 하 충돌
						if (fWidth > fHeight)
						{
							// 상 충돌
							if (Dst->Get_Info()->fY < Src->Get_Info()->fY)
							{

								Dst->Set_PosY(-fHeight);

							}
							// 하 충돌
							else
							{
								Dst->Set_PosY(fHeight);
							}
						}

						// 좌 우 충돌
						else
						{
							// 좌 충돌
							if (Dst->Get_Info()->fX < Src->Get_Info()->fX)
							{
								Dst->Set_PosX(-fWidth);
							}
							// 우 충돌
							else
							{
								Dst->Set_PosX(fWidth);
							}
						}

					}
				}
		

				if (Dst->Get_EnemyType() == ENEMY_SNAKE) {
					if (Check_Rect(Dst, Src, &fWidth, &fHeight))
					{
						if (Dst->Get_StopCollision() + 4000 < GetTickCount()) {
							if (fWidth > fHeight)
							{

							}
							else {
								dynamic_cast<CSnake*>(Dst)->Set_State(CSnake::CHANGE);
							}
							Dst->Set_StopCollision(GetTickCount());
						}
						
					}
					
				}

				if (Dst->Get_EnemyType() == ENEMY_SHOPMAN) {
					if (Check_Rect(Dst, Src, &fWidth, &fHeight))
					{
						if (fWidth > fHeight) {
							if (Dst->Get_Info()->fY < Src->Get_Info()->fY)
							{

								Dst->Set_PosY(-fHeight);

							}
							// 하 충돌
							else
							{
								Dst->Set_PosY(fHeight + 10);
							}
						}
						else {
							if (Dst->Get_StopCollision()+ 1000< GetTickCount()) {
								if (Dst->Get_Info()->fX < Src->Get_Info()->fX)
								{
									Dst->Set_PosX(-fWidth - 20);
									Dst->Set_Direction(DIR_RIGHT);
									//static_cast<CShopMan*>(Dst)->Set_dir(1);
								}
								// 우 충돌
								else
								{
									Dst->Set_PosX(fWidth + 20);
									//static_cast<CShopMan*>(Dst)->Set_dir(-1);
									Dst->Set_Direction(DIR_LEFT);
								}
								Dst->Set_StopCollision(GetTickCount());
							}
							
						}
					

					}

				}

			}

		}
	}

}

void CCollisionManager::Collision_RectEx_Player_Enemy(CObj* Dst, list<CObj*> _Src)
{

	for (auto& Src : _Src)
	{
		float	fWidth(0.f), fHeight(0.f);
	
			if (Src->Get_EnemyType() == ENEMY_BAT) {
				if (Check_Rect(Dst, Src, &fWidth, &fHeight))
				{
					if (Dst->Get_StopCollision() + 3000 < GetTickCount()) {
						if (fWidth > fHeight)
						{
							// 상 충돌
							if (Dst->Get_Info()->fY < Src->Get_Info()->fY)
							{

								Src->Set_Dead(true);
								dynamic_cast<CPlayer*>(Dst)->RemoteJump();

							}
							// 하 충돌
							else
							{
								Dst->Set_PosY(fHeight);
							}
						}

						// 좌 우 충돌
						else
						{
							// 좌 충돌
							if (Dst->Get_Info()->fX < Src->Get_Info()->fX)
							{
								Dst->Set_PosX(-fWidth);
								dynamic_cast<CPlayer*>(Dst)->Hurt(-1);
							}
							// 우 충돌
							else
							{
								Dst->Set_PosX(fWidth);
								dynamic_cast<CPlayer*>(Dst)->Hurt(+1);
							}
						}
						static_cast<CPlayer*>(Dst)->Set_Collision(false);
						static_cast<CPlayer*>(Dst)->SetHp(1);
						Dst->Set_StopCollision(GetTickCount());
					}
			
				}
			}
			if (Src->Get_EnemyType() == ENEMY_SNAKE) {
				if (Check_Rect(Dst, Src, &fWidth, &fHeight))
				{

					if (fWidth > fHeight)
					{
						// 상 충돌
						if (Dst->Get_Info()->fY < Src->Get_Info()->fY)
						{

							Src->Set_Dead(true);
							dynamic_cast<CPlayer*>(Dst)->RemoteJump();

						}
					}

		
					else
					{
					
						if (Dst->Get_Info()->fX < Src->Get_Info()->fX)
						{
							
							dynamic_cast<CPlayer*>(Dst)->Hurt(-1);
						}
						// 우 충돌
						else
						{
							dynamic_cast<CPlayer*>(Dst)->Hurt(1);
						}
					}

				}
			}
			if (Src->Get_EnemyType() == ENEMY_SHOPMAN) {
				if (Check_Rect(Dst, Src, &fWidth, &fHeight)) {
					if (static_cast<CShopMan*>(Src)->GetUI()) {

						static_cast<CShopMan*>(Src)->GetUI()->Set_In(true);
						if (static_cast<CShopMan*>(Src)->Get_State() != CShopMan::CHASE) {
							CSoundManager::Get_Instance()->PlaySound_IfNotPlaying(L"npc_shopkeeper_all_natural.wav", SOUND_TALK, 1.f);
						}
					
					}
				}
				else {
					if (static_cast<CShopMan*>(Src)->GetUI()) {
						static_cast<CShopMan*>(Src)->GetUI()->Set_In(false);
						CSoundManager::Get_Instance()->StopSound(SOUND_TALK);
					}
					
				}
			}
	}

	


}

void CCollisionManager::Collision_RectEx_Weapon_Enemy(CObj* Dst, list<CObj*> _Src) {
	for (auto& Src : _Src)
	{
		float	fWidth(0.f), fHeight(0.f);

		if (Src->Get_EnemyType() == ENEMY_BAT) {
			if (Check_Rect(Dst, Src, &fWidth, &fHeight))
			{

				Src->Set_Dead(true);
			}
		}
		if (Src->Get_EnemyType() == ENEMY_SNAKE) {
			if (Check_Rect(Dst, Src, &fWidth, &fHeight))
			{

				Src->Set_Dead(true);

			}
		}
		if (Src->Get_EnemyType() == ENEMY_SHOPMAN) {
			if (Check_Rect(Dst, Src, &fWidth, &fHeight))
			{
				
				if (!Src->Get_invincibility()) {
					static_cast<CShopMan*>(Src)->Set_Hp(1);
					static_cast<CShopMan*>(Src)->Set_State(CShopMan::HIT);
					if(fWidth < fHeight)
				{
					// 좌 충돌
					if (Dst->Get_Info()->fX < Src->Get_Info()->fX)
					{
						static_cast<CShopMan*>(Src)->Set_dir(1);
					}
					// 우 충돌
					else
					{
						static_cast<CShopMan*>(Src)->Set_dir(-1);
					}
				}
					
					Src->Set_invincibility(true);
					Src->Set_StopCollision(GetTickCount());
					
				}

				
			}
		}
	}
}

void CCollisionManager::Collision_RectEx_Bomb(CObj* Dst, vector<CObj*> _Src) {
	for (auto& Src : _Src) {
		if (Check_Bomb(Dst, Src)) {
			if (static_cast<CTile*>(Src)->Get_Bomb()) {
				Src->Set_Dead(true);
			}
		}
	}

}

void CCollisionManager::Collision_RectEx_Particle(vector<CObj*> _Dst, vector<CObj*> _Src) {
	float	fWidth(0.f), fHeight(0.f);

	for (auto& Dst : _Dst)
	{
		for (auto& Src : _Src)
		{
			if ((Src)->Get_Collision() == CollisionType::FLOOR) {

				if (Check_Rect(Dst, Src, &fWidth, &fHeight))
				{
					if (Dst->Get_invincibility() + 100 < GetTickCount()) {
						static_cast<CParticle*>(Dst)->SetSplit();
					}
					

				}
			}

		}
	}
}

void CCollisionManager::Collision_RectEx_Bullet_ENEMY(list<CObj*> _Dst, list<CObj*> _Src) {
	float	fWidth(0.f), fHeight(0.f);

	for (auto& Dst : _Dst)
	{
		for (auto& Src : _Src)
		{
			if (Check_Rect(Dst, Src, &fWidth, &fHeight))
			{
				if (Src->Get_EnemyType() != ENEMY_SHOPMAN) {
					Dst->Set_Dead(true);
					Src->Set_Dead(true);
				}
			}
		}
	}
}
void CCollisionManager::TileCheck(CObj* _Dst, vector<CObj*> _Src)
{
	float	fWidth(0.f), fHeight(0.f);

	int Count = static_cast<CTile*>(_Dst)->Get_Count();
	bool up(false);
	bool down(false);
	bool right(false);
	bool left(false);

	if (Count >=101 && Count <= 2400) {
	
		if (_Src[Count + 50]->Get_Collision() == END) {
			up = true;
		}
		if (_Src[ Count -  50]->Get_Collision() == END) {
			down = true;
		}
		CollisionType a = _Src[Count - 1]->Get_Collision();
	
		if (_Src[Count - 1]->Get_Collision() == END) {
			left = true;
		}
		if (_Src[Count + 1]->Get_Collision() == END) {
			right = true;
		}
		

	}
	
		
	static_cast<CTile*>(_Dst)->SetTileFloor(up, down, right, left);

}

bool CCollisionManager::Check_Rect(CObj* pDst, CObj* pSrc, float* pX, float* pY)
{
	float		fWidth = fabsf(pDst->Get_Info()->fX - pSrc->Get_Info()->fX);
	float		fHeight = fabsf(pDst->Get_Info()->fY - pSrc->Get_Info()->fY);

	float		fRadiusX = (pDst->Get_RealSize().x + pSrc->Get_Info()->fCX) * 0.5f;
	float		fRadiusY = (pDst->Get_RealSize().y + pSrc->Get_Info()->fCY) * 0.5f;


	if (fRadiusX >= fWidth && fRadiusY >= fHeight)
	{
		*pX = fRadiusX - fWidth;
		*pY = fRadiusY - fHeight;

		return true;
	}

	return false;
}
bool CCollisionManager::Check_Ladder_Rect(CObj* pDst, CObj* pSrc, float* pX, float* pY)
{
	float		fWidth = fabsf(pDst->Get_Info()->fX - pSrc->Get_Info()->fX);
	float		fHeight = fabsf(pDst->Get_Info()->fY  - pSrc->Get_Info()->fY  - pSrc->Get_RealSize().y/2);

	float		fRadiusX = (pDst->Get_RealSize().x-30 + pSrc->Get_RealSize().x- 30) * 0.5f;
	float		fRadiusY = (pDst->Get_RealSize().y + pSrc->Get_RealSize().y) * 0.5f;


	if (fRadiusX >= fWidth && fRadiusY >= fHeight)
	{
		*pX = fRadiusX - fWidth;
		*pY = fRadiusY - fHeight;

		return true;
	}

	return false;
}

bool CCollisionManager::Check_Circle(CObj* pDst, CObj* pSrc)
{
	float	fRadius = (pDst->Get_Info()->fCX + pSrc->Get_Info()->fCX) * 0.5f;

	float	fWidth = fabsf(pDst->Get_Info()->fX - pSrc->Get_Info()->fX);
	float	fHeight = fabsf(pDst->Get_Info()->fY - pSrc->Get_Info()->fY);

	float	fDiagonal = sqrtf(fWidth * fWidth + fHeight * fHeight);

	return fRadius >= fDiagonal;
}

void CCollisionManager::Collision_Circle(list<CObj*> _Dst, list<CObj*> _Src)
{
	for (auto& Dst : _Dst)
	{
		for (auto& Src : _Src)
		{
			if (Check_Circle(Dst, Src))
			{
			
			}
		}
	}
}

bool CCollisionManager::Check_Bomb(CObj* pDst, CObj* pSrc) {
	float	fRadius = (static_cast<CBomb*>(pDst)->Get_BombSize().x + pSrc->Get_Info()->fCX) * 0.5f;

	float	fWidth = fabsf(pDst->Get_Info()->fX - pSrc->Get_Info()->fX);
	float	fHeight = fabsf(pDst->Get_Info()->fY - pSrc->Get_Info()->fY);

	float	fDiagonal = sqrtf(fWidth * fWidth + fHeight * fHeight);

	return fRadius >= fDiagonal;
}