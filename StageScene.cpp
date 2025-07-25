#include "StageScene.h"
#include <Novice.h>

fourpoint StageScene::FourPointProcessing(const Vector2& object, float radians) {
	fourpoint pos;
	const float leftupX = -32.0f;
	const float leftupY = -32.0f;
	const float rightupX = 32.0f;
	const float rightupY = -32.0f;
	const float leftdownX = -32.0f;
	const float leftdownY = 32.0f;
	const float rightdownX = 32.0f;
	const float rightdownY = 32.0f;

	pos.leftup.x = leftupX * cosf(radians) - leftupY * sinf(radians) + object.x;
	pos.leftup.y = leftupX * sinf(radians) + leftupY * cosf(radians) + object.y;

	pos.rightup.x = rightupX * cosf(radians) - rightupY * sinf(radians) + object.x;
	pos.rightup.y = rightupX * sinf(radians) + rightupY * cosf(radians) + object.y;

	pos.leftdown.x = leftdownX * cosf(radians) - leftdownY * sinf(radians) + object.x;
	pos.leftdown.y = leftdownX * sinf(radians) + leftdownY * cosf(radians) + object.y;

	pos.rightdown.x = rightdownX * cosf(radians) - rightdownY * sinf(radians) + object.x;
	pos.rightdown.y = rightdownX * sinf(radians) + rightdownY * cosf(radians) + object.y;
	return pos;
};
void StageScene::BulletMoving(Vector2& object, const Vector2& direction, float speed) {
	object.x += direction.x * speed;
	object.y += direction.y * speed;
};
void StageScene::LockonMoving(Vector2& object, const Vector2& target, float speed) {
	Vector2 direction;
	direction.x = target.x - object.x;
	direction.y = target.y - object.y;
	float length = sqrt(direction.x * direction.x + direction.y * direction.y);
	if (length != 0) {
		direction.x /= length;
		direction.y /= length;
	}
	object.x += direction.x * speed;
	object.y += direction.y * speed;
};
Vector2 StageScene::enemyRandomPosition(int WindowWidth, int WindowHeight) {
	Vector2 pos = {0.0f, 0.0f};
	int edge = rand() % 4;
	switch (edge) {
	case 0: // 上
		pos = {static_cast<float>(rand() % WindowWidth), 0.0f};
		break;
	case 1: // 下
		pos = {static_cast<float>(rand() % WindowWidth), static_cast<float>(WindowHeight)};
		break;
	case 2: // 左
		pos = {0.0f, static_cast<float>(rand() % WindowHeight)};
		break;
	case 3: // 右
		pos = {static_cast<float>(WindowWidth), static_cast<float>(rand() % WindowHeight)};
		break;
	}
	return pos;
};



void StageScene::Initialize() {
	// 初始化随机种子
	srand(static_cast<unsigned int>(time(0)));

	// 初始化玩家
	player.pos.x = 1280.0f / 2.0f;
	player.pos.y = 720.0f / 2.0f + 150.0f;
	player.radius = 16.0f;
	player.speed = 4.0f;
	player.boltnumber = 10;
	player.shootcooltime = 0;
	player.hp = 10;
	player.gethurtcooltime = 60;
	player.killcounter = 0;

	// 初始化子弹
	for (int i = 0; i < 10; i++) {
		bullet[i].pos.x = -128.0f;
		bullet[i].pos.y = -128.0f;
		bullet[i].lockonpos.x = -128.0f;
		bullet[i].lockonpos.y = -128.0f;
		bullet[i].radius = 4.0f;
		bullet[i].speed = 12.0f;
		bullet[i].isShoot = false;
		bullet[i].bullettype = -1;
		bullet[i].killcounter = 0;
	}

	// 初始化敌人
	for (int i = 0; i < 150; i++) {
		enemy[i].pos = enemyRandomPosition(1280, 720);
		enemy[i].hp = 1;
		enemy[i].radius = 8.0f;
		enemy[i].speed = 0.50f;
		enemy[i].respowntime = 120;
		enemy[i].isAlive = true;
		enemyhoumenn[i] = left;
	}
	// boss初始化
	for (int i = 150; i < 160; i++) {
		enemy[i].pos = enemyRandomPosition(1280, 720);
		enemy[i].hp = 100;
		enemy[i].radius = 45.0f;
		enemy[i].speed = 1.0f;
		enemy[i].respowntime = 120;
		enemy[i].isAlive = false;
	}

	// 初始化物品
	for (int i = 0; i < 160; i++) {
		point[i].pos = {-1000.0f, -1000.0f};
		point[i].isalive = false;
	}

	// 初始化状态
	bladestorm = false;
	bladestormtime = 120;
	playerhoumenn = left;
	flame = 0;
	bladeflame = 0;
	deadboss = 0;

	// 加载资源
	LoadResources();
}

void StageScene::LoadResources() {
	// 数字
	numgraph[0] = Novice::LoadTexture("./images/num/num1.png");
	numgraph[1] = Novice::LoadTexture("./images/num/num2.png");
	numgraph[2] = Novice::LoadTexture("./images/num/num3.png");
	numgraph[3] = Novice::LoadTexture("./images/num/num4.png");
	numgraph[4] = Novice::LoadTexture("./images/num/num5.png");
	numgraph[5] = Novice::LoadTexture("./images/num/num6.png");
	numgraph[6] = Novice::LoadTexture("./images/num/num7.png");
	numgraph[7] = Novice::LoadTexture("./images/num/num8.png");
	numgraph[8] = Novice::LoadTexture("./images/num/num9.png");
	numgraph[9] = Novice::LoadTexture("./images/num/num10.png");

	// 弹夹
	boltimage = Novice::LoadTexture("./images/ui/bolt.png");
	holderupimage = Novice::LoadTexture("./images/ui/holderup.png");
	holderunderimage = Novice::LoadTexture("./images/ui/holderunder.png");

	// 鸟卜仪
	monitaimage = Novice::LoadTexture("./images/ui/monita.png");

	// 血条
	hpcounter = Novice::LoadTexture("./images/ui/hpcounter.png");
	hpblock = Novice::LoadTexture("./images/ui/hp.png");

	// 子弹
	bulletimage = Novice::LoadTexture("./images/player/bullet.png");
	flybladeimage = Novice::LoadTexture("./images/player/flyblade.png");

	// 玩家
	playergraphL[0] = Novice::LoadTexture("./images/player/UMARINEL1.png");
	playergraphL[1] = Novice::LoadTexture("./images/player/UMARINEL2.png");
	playergraphL[2] = Novice::LoadTexture("./images/player/UMARINEL3.png");
	playergraphL[3] = Novice::LoadTexture("./images/player/UMARINEL4.png");
	playergraphR[0] = Novice::LoadTexture("./images/player/UMARINER1.png");
	playergraphR[1] = Novice::LoadTexture("./images/player/UMARINER2.png");
	playergraphR[2] = Novice::LoadTexture("./images/player/UMARINER3.png");
	playergraphR[3] = Novice::LoadTexture("./images/player/UMARINER4.png");

	// 链锯剑
	bladestormgraph[0] = Novice::LoadTexture("./images/player/bladestorm1.png");
	bladestormgraph[1] = Novice::LoadTexture("./images/player/bladestorm2.png");
	bladestormgraph[2] = Novice::LoadTexture("./images/player/bladestorm3.png");
	bladestormgraph[3] = Novice::LoadTexture("./images/player/bladestorm4.png");

	// 小怪
	enemygraphL[0] = Novice::LoadTexture("./images/enemy/NGLINGL1.png");
	enemygraphL[1] = Novice::LoadTexture("./images/enemy/NGLINGL2.png");
	enemygraphL[2] = Novice::LoadTexture("./images/enemy/NGLINGL3.png");
	enemygraphL[3] = Novice::LoadTexture("./images/enemy/NGLINGL4.png");
	enemygraphR[0] = Novice::LoadTexture("./images/enemy/NGLINGR1.png");
	enemygraphR[1] = Novice::LoadTexture("./images/enemy/NGLINGR2.png");
	enemygraphR[2] = Novice::LoadTexture("./images/enemy/NGLINGR3.png");
	enemygraphR[3] = Novice::LoadTexture("./images/enemy/NGLINGR4.png");

	// 小怪死亡
	enemydeathgraph[3] = Novice::LoadTexture("./images/enemy/death1.png");
	enemydeathgraph[2] = Novice::LoadTexture("./images/enemy/death2.png");
	enemydeathgraph[1] = Novice::LoadTexture("./images/enemy/death3.png");
	enemydeathgraph[0] = Novice::LoadTexture("./images/enemy/death4.png");

	// boss
	bossgraph[0] = Novice::LoadTexture("./images/enemy/BOOS1.png");
	bossgraph[1] = Novice::LoadTexture("./images/enemy/BOOS2.png");
	bossgraph[2] = Novice::LoadTexture("./images/enemy/BOOS3.png");
	bossgraph[3] = Novice::LoadTexture("./images/enemy/BOOS4.png");

	// boss爆炸
	bossexp[14] = Novice::LoadTexture("./images/enemy/Explosion1.png");
	bossexp[13] = Novice::LoadTexture("./images/enemy/Explosion2.png");
	bossexp[12] = Novice::LoadTexture("./images/enemy/Explosion3.png");
	bossexp[11] = Novice::LoadTexture("./images/enemy/Explosion4.png");
	bossexp[10] = Novice::LoadTexture("./images/enemy/Explosion5.png");
	bossexp[9] = Novice::LoadTexture("./images/enemy/Explosion6.png");
	bossexp[8] = Novice::LoadTexture("./images/enemy/Explosion7.png");
	bossexp[7] = Novice::LoadTexture("./images/enemy/Explosion8.png");
	bossexp[6] = Novice::LoadTexture("./images/enemy/Explosion9.png");
	bossexp[5] = Novice::LoadTexture("./images/enemy/Explosion10.png");
	bossexp[4] = Novice::LoadTexture("./images/enemy/Explosion11.png");
	bossexp[3] = Novice::LoadTexture("./images/enemy/Explosion12.png");
	bossexp[2] = Novice::LoadTexture("./images/enemy/Explosion13.png");
	bossexp[1] = Novice::LoadTexture("./images/enemy/Explosion14.png");
	bossexp[0] = Novice::LoadTexture("./images/enemy/Explosion15.png");

	// 点数宝石
	pointgraph = Novice::LoadTexture("./images/enemy/point.png");

	// 地图
	maograph = Novice::LoadTexture("./images/ui/room.png");

	// 界面
	gameovergraph = Novice::LoadTexture("./images/ui/gameover.png");
	gamecleargraph = Novice::LoadTexture("./images/ui/gameclear.png");

	// 音乐
	bgmgraph = Novice::LoadAudio("./Sounds/bgm.wav");
	playhandle = -1;

	// 枪声
	gungraph = Novice::LoadAudio("./Sounds/9mm2.mp3");
	gunplayhandle = -1;

	// 装弹音效
	reloadgraph = Novice::LoadAudio("./Sounds/reload.mp3");
	reloadhandle = -1;
}


void StageScene::Update(char* keys, char* preKeys) {
	flame = ++flame % 60;
	bladeflame = ++bladeflame % 20;
	int closestEnemyNumber = -1;
	float miniDis = 10000.0f;
	// 播放背景音乐
	if (!Novice::IsPlayingAudio(playhandle) || playhandle == -1) {
		playhandle = Novice::PlayAudio(bgmgraph, true, 1.0f);
	}

	// 移动控制
	if (keys[DIK_W]) {
		if (player.pos.y > 0 + 48.0f + player.radius + 48.0f / 2.0f) {
			player.pos.y -= player.speed;
		}
	}

	if (keys[DIK_S]) {
		if (player.pos.y < 720.0f - 90.0f - player.radius / 2.0f) {
			player.pos.y += player.speed;
		}
	}

	if (keys[DIK_A]) {
		playerhoumenn = left;
		if (player.pos.x > 0 + 64.0f + player.radius / 2.0f) {
			player.pos.x -= player.speed;
		}
	}

	if (keys[DIK_D]) {
		playerhoumenn = right;
		if (player.pos.x < 1280.0f - 64.0f - player.radius / 2.0f) {
			player.pos.x += player.speed;
		}
	}

	// 索敌

	for (int i = 0; i < wave1num; i++) {
		if (!enemy[i].isAlive) {
			continue; // 跳过已经死亡的敌人
		}

		Vector2 direction;
		direction.x = player.pos.x - enemy[i].pos.x;
		direction.y = player.pos.y - enemy[i].pos.y;
		float length = sqrt(direction.x * direction.x + direction.y * direction.y);

		if (length < miniDis) {
			miniDis = length;       // 更新最小距离
			closestEnemyNumber = i; // 更新最近敌人的索引
		}
	}

	// 发射子弹0
	if ((keys[DIK_SPACE]) && !preKeys[DIK_SPACE] && (player.shootcooltime <= 0) && (player.boltnumber > 0)) {

		// 枪声
		if (!Novice::IsPlayingAudio(gunplayhandle) || gunplayhandle == -1) {
			gunplayhandle = Novice::PlayAudio(gungraph, false, 1.0f);
		}
		int bulletIndex = 10 - player.boltnumber;
		if (!bullet[bulletIndex].isShoot) {
			bullet[bulletIndex].isShoot = true;
			bullet[bulletIndex].pos = player.pos;
			bullet[bulletIndex].bullettype = 0;
			player.boltnumber--;
			player.shootcooltime = 10; // 设置一个适当的冷却时间

			// 获取锁定的敌人的位置并计算方向
			if (closestEnemyNumber != -1) {
				Vector2 direction;
				direction.x = enemy[closestEnemyNumber].pos.x - player.pos.x;
				direction.y = enemy[closestEnemyNumber].pos.y - player.pos.y;
				float length = sqrt(direction.x * direction.x + direction.y * direction.y);
				if (length != 0) {
					direction.x /= length;
					direction.y /= length;
					bullet[bulletIndex].lockonpos = direction;
				}
			}
		}
	}
	// 发射子弹1
	if ((keys[DIK_RSHIFT]) && !preKeys[DIK_RSHIFT] && (player.shootcooltime <= 0) && (player.boltnumber > 0) && player.killcounter >= 2000) {
		int bulletIndex = 10 - player.boltnumber;
		if (!bullet[bulletIndex].isShoot) {
			bullet[bulletIndex].isShoot = true;
			bullet[bulletIndex].pos = player.pos;
			bullet[bulletIndex].bullettype = 1;
			player.boltnumber--;
			player.shootcooltime = 10; // 设置一个适当的冷却时间

			// 获取锁定的敌人的位置并计算方向
			if (closestEnemyNumber != -1) {
				Vector2 direction;
				direction.x = enemy[closestEnemyNumber].pos.x - player.pos.x;
				direction.y = enemy[closestEnemyNumber].pos.y - player.pos.y;
				float length = sqrt(direction.x * direction.x + direction.y * direction.y);
				if (length != 0) {
					direction.x /= length;
					direction.y /= length;
					bullet[bulletIndex].lockonpos = direction;
				}
			}
		}
	}

	// 子弹移动
	for (int i = 0; i < 10; i++) {
		if (bullet[i].isShoot && bullet[i].bullettype == 0) {
			BulletMoving(bullet[i].pos, bullet[i].lockonpos, bullet[i].speed);
		} else if (bullet[i].isShoot && bullet[i].bullettype == 1) {
			LockonMoving(bullet[i].pos, enemy[closestEnemyNumber].pos, bullet[i].speed);
		}
	}

	// 冷却时间
	if (player.shootcooltime > 0) {
		player.shootcooltime--;
	}
	// 手动装弹
	if (keys[DIK_R]) {
		if (!Novice::IsPlayingAudio(reloadhandle) || reloadhandle == -1) {
			reloadhandle = Novice::PlayAudio(reloadgraph, false, 1.0f);
		}
		player.boltnumber = 10;
		for (int i = 0; i < 10; i++) {
			bullet[i].isShoot = false;
			bullet[i].bullettype = -1;
			bullet[i].killcounter = 0;
		}
	}

	// 射击击中判定
	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 160; j++) {
			if (!bullet[i].isShoot || !enemy[j].isAlive) {
				continue;
			}

			Vector2 direction;
			direction.x = bullet[i].pos.x - enemy[j].pos.x;
			direction.y = bullet[i].pos.y - enemy[j].pos.y;
			float length = sqrt(direction.x * direction.x + direction.y * direction.y);

			if (length < enemy[j].radius + bullet[i].radius + 30.0f) {
				enemy[j].hp--;
				if (bullet[i].bullettype == 1) {
					bullet[i].killcounter++;
				}
				break;
			}
		}
	}

	// 对玩家攻击
	if (player.hp > 0) {
		player.gethurtcooltime--;
		for (int j = 0; j < wave1num; j++) {
			if (player.hp < 0 || !enemy[j].isAlive) {
				continue;
			}

			Vector2 direction;
			direction.x = player.pos.x - enemy[j].pos.x;
			direction.y = player.pos.y - enemy[j].pos.y;
			float length = sqrt(direction.x * direction.x + direction.y * direction.y);

			if (length < enemy[j].radius + player.radius && player.gethurtcooltime <= 0) {
				player.hp--;
				player.gethurtcooltime = 60;
				break;
			}
		}
	}

	if (player.hp <= 0) {
		TransitionTo(CLEAR);
	}
	// 子弹自毁 超出视距

	for (int i = 0; i < 10; i++) {
		if (bullet[i].bullettype == 0) {
			if (bullet[i].pos.x < 0.0f || bullet[i].pos.x > 1280.0f || bullet[i].pos.y < 0.0f || bullet[i].pos.y > 720.0f) {
				bullet[i].pos = {-128, -128};
			}
		} else if (bullet[i].bullettype == 1 && bullet[i].killcounter >= 10) {
			bullet[i].pos = {-128, -128};
		}
	}

	// 近战攻击
	if ((keys[DIK_RETURN]) && !preKeys[DIK_RETURN] && player.killcounter >= 4000) {
		bladestorm = true;
	}

	// 近战攻击计时器

	if (bladestorm == true && bladestormtime > 0) {
		bladestormtime--;
		for (int i = 0; i < 160; i++) {
			if (enemy[i].isAlive == false) {
				continue;
			}
			Vector2 direction;
			direction.x = enemy[i].pos.x - player.pos.x;
			direction.y = enemy[i].pos.y - player.pos.y;
			float length = sqrt(direction.x * direction.x + direction.y * direction.y);
			if (length < 80 + enemy[i].radius) {
				enemy[i].hp--;
			}
		}
	} else if (bladestormtime <= 0) {
		bladestorm = false;
		bladestormtime = 120;
	}
	// 死亡监测
	for (int j = 0; j < 160; j++) {
		if (enemy[j].hp <= 0) {
			enemy[j].isAlive = false;
			point[j].isalive = true;
			point[j].pos = enemy[j].pos;
			if (j >= 150) {
				deadboss++;
				point[j].isalive = true;
			}
		}
	}
	// 敌人位置更新
	for (int i = 0; i < 150; i++) {
		if (enemy[i].isAlive == true) {
			LockonMoving(enemy[i].pos, player.pos, enemy[i].speed);
		} else {
			enemy[i].respowntime--;
		}
	}

	for (int i = 150; i < 160; i++) {
		LockonMoving(enemy[i].pos, player.pos, enemy[i].speed);
		if (enemy[i].hp <= 0) {
			enemy[i].respowntime--;
		}
	}

	// 确定敌人移动是左还是右
	for (int i = 0; i < 150; i++) {
		if (player.pos.x - enemy[i].pos.x >= 0) {
			enemyhoumenn[i] = left;
		} else {
			enemyhoumenn[i] = right;
		}
	}
	// 复活并刷新至四个边框
	for (int i = 0; i < 150; i++) {
		if (enemy[i].respowntime <= 0) {
			enemy[i].isAlive = true;
			enemy[i].hp = 1;
			enemy[i].respowntime = 120;
			enemy[i].pos = enemyRandomPosition(1280, 720);
		}
	}
	// boss刷新
	for (int i = 150; i < 160; i++) {
		if (player.killcounter > 6000 && enemy[i].isAlive == false && enemy[i].hp == 100) {
			enemy[i].isAlive = true;
			enemy[i].pos = enemyRandomPosition(1280, 720);
		}
	}
	
	// 拾取豆子

	if (player.hp > 0) {
		for (int j = 0; j < 160; j++) {
			if (player.hp < 0 || !point[j].isalive) {
				continue;
			}

			Vector2 direction;
			direction.x = player.pos.x - point[j].pos.x;
			direction.y = player.pos.y - point[j].pos.y;
			float length = sqrt(direction.x * direction.x + direction.y * direction.y);

			if (length < player.radius + 50.0f) {
				point[j].isalive = false;
				player.killcounter = player.killcounter + 2;
				break;
			}
		}
	}
	// 分数计算
	numberarray[0] = player.killcounter / 10000;
	numberarraysaver = player.killcounter % 10000;

	numberarray[1] = numberarraysaver / 1000;
	numberarraysaver %= 1000;

	numberarray[2] = numberarraysaver / 100;
	numberarraysaver %= 100;

	numberarray[3] = numberarraysaver / 10;
	numberarraysaver %= 10;

	numberarray[4] = numberarraysaver;

	// 计时器 六十内循环
	flame = ++flame % 60;
	bladeflame = ++bladeflame % 20;
	////子弹飞行角度
	for (int i = 0; i < 10; i++) {
		shotangle[i] = atan2(bullet[i].lockonpos.y, bullet[i].lockonpos.x);
	}
	//
}

void StageScene::Draw() {

		// 地图
	Novice::DrawSprite(0, 0, maograph, 1.0f, 1.0f, 0.0f, WHITE);
	// 豆子
	for (int i = 0; i < wave1num; i++) {
		if (point[i].isalive == true) {
			Novice::DrawSprite(static_cast<int>(point[i].pos.x) - 32, static_cast<int>(point[i].pos.y) - 32, pointgraph, 1.0f, 1.0f, 0.0f, WHITE);
		}
	}

	// 敌人死亡
	for (int i = 0; i < 150; i++) {
		if (enemy[i].isAlive == false && (enemy[i].respowntime < 120 && enemy[i].respowntime >= 60)) {
			Novice::DrawSprite(static_cast<int>(enemy[i].pos.x) - 32, static_cast<int>(enemy[i].pos.y) - 32, enemydeathgraph[(enemy[i].respowntime - 61) / 15], 1.0f, 1.0f, 0.0f, WHITE);
		}
	}
	/// 敌人

	for (int i = 0; i < 150; i++) {
		if (enemy[i].isAlive == true) {
			switch (enemyhoumenn[i]) {
			case left:
				Novice::DrawSprite(static_cast<int>(enemy[i].pos.x) - 32, static_cast<int>(enemy[i].pos.y) - 32, enemygraphR[flame / 15], 1.0f, 1.0f, 0.0f, WHITE);
				break;
			case right:
				Novice::DrawSprite(static_cast<int>(enemy[i].pos.x) - 32, static_cast<int>(enemy[i].pos.y) - 32, enemygraphL[flame / 15], 1.0f, 1.0f, 0.0f, WHITE);
				break;
			}
		}
	}

	// boss
	for (int i = 150; i < 160; i++) {
		if (enemy[i].isAlive == true) {
			Novice::DrawSprite(static_cast<int>(enemy[i].pos.x) - 64, static_cast<int>(enemy[i].pos.y) - 64, bossgraph[flame / 15], 1.0f, 1.0f, 0.0f, WHITE);
		}
	}

	// boss死亡
	for (int i = 150; i < 160; i++) {
		if (enemy[i].hp == 0 && enemy[i].respowntime < 120 && enemy[i].respowntime >= 60) {
			Novice::DrawSprite(static_cast<int>(enemy[i].pos.x) - 64, static_cast<int>(enemy[i].pos.y) - 64, bossexp[(enemy[i].respowntime - 61) / 4], 1.0f, 1.0f, 0.0f, WHITE);
		}
	}
	// 子弹
	for (int i = 0; i < 10; i++) {

		if (bullet[i].isShoot == true) {
			modfourpos[i] = FourPointProcessing(bullet[i].pos, shotangle[i]);
			if (bullet[i].bullettype == 0) {
				Novice::DrawQuad(
				    static_cast<int>(modfourpos[i].leftup.x), static_cast<int>(modfourpos[i].leftup.y), static_cast<int>(modfourpos[i].rightup.x), static_cast<int>(modfourpos[i].rightup.y),
				    static_cast<int>(modfourpos[i].leftdown.x), static_cast<int>(modfourpos[i].leftdown.y), static_cast<int>(modfourpos[i].rightdown.x), static_cast<int>(modfourpos[i].rightdown.y), 0,
				    0, 64, 64, bulletimage, WHITE);
			} else if (bullet[i].bullettype == 1) {
				Novice::DrawQuad(
				    static_cast<int>(modfourpos[i].leftup.x), static_cast<int>(modfourpos[i].leftup.y), static_cast<int>(modfourpos[i].rightup.x), static_cast<int>(modfourpos[i].rightup.y),
				    static_cast<int>(modfourpos[i].leftdown.x), static_cast<int>(modfourpos[i].leftdown.y), static_cast<int>(modfourpos[i].rightdown.x), static_cast<int>(modfourpos[i].rightdown.y), 0,
				    0, 64, 64, flybladeimage, WHITE);
			}
		}
	}

	// 近战特效
	if (bladestorm == true && bladestormtime > 0) {
		Novice::DrawSprite(static_cast<int>(player.pos.x) - 64, static_cast<int>(player.pos.y) - 64, bladestormgraph[bladeflame / 5], 1.0f, 1.0f, 0.0f, WHITE);
	}
	// 主角
	switch (playerhoumenn) {
	case left:
		Novice::DrawSprite(static_cast<int>(player.pos.x) - 32, static_cast<int>(player.pos.y) - 32, playergraphL[flame / 15], 1.0f, 1.0f, 0.0f, WHITE);
		break;
	case right:
		Novice::DrawSprite(static_cast<int>(player.pos.x) - 32, static_cast<int>(player.pos.y) - 32, playergraphR[flame / 15], 1.0f, 1.0f, 0.0f, WHITE);
		break;
	}

	// 弹药量
	Novice::DrawSprite(1200 - 82, 200 - 82, holderunderimage, 1.5f, 1.5f, 0.0f, WHITE);
	for (int i = 0; i < 10; i++) {
		if (bullet[i].isShoot == false) {
			Novice::DrawSprite(1200 - 20, 150 + i * 48, boltimage, 1.5f, 1.5f, 0.0f, WHITE);
		}
	}
	Novice::DrawSprite(1200 - 82, 200 - 82, holderupimage, 1.5f, 1.5f, 0.0f, WHITE);
	// 鸟卜仪
	Novice::DrawSprite(1280 / 2 - 200, 5, monitaimage, 1.0f, 1.0f, 0.0f, WHITE);
	////分数
	for (int i = 0; i < 5; i++) {
		Novice::DrawSprite(465 + i * 70, 29, numgraph[numberarray[i]], 1.0f, 1.0f, 0.0f, WHITE);
	}
	// 血量显示
	Novice::DrawSprite(400, 550, hpcounter, 1.0f, 1.0f, 0.0f, WHITE);
	// 血量格子
	if (player.hp > 0) {
		for (int i = 0; i < player.hp; i++) {
			Novice::DrawSprite(460 + i * 32, 550 + 32, hpblock, 1.0f, 1.0f, 0.0f, WHITE);
		}
	}
}