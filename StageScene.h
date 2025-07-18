#pragma once
#include "IScene.h"
#include <Novice.h>
#include <cmath>
#include <time.h>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

typedef struct Vector2 {
	float x;
	float y;
} Vector2;

typedef struct Player {
	Vector2 pos;
	float radius;
	float speed;
	int boltnumber;
	int shootcooltime;
	int hp;
	int gethurtcooltime;
	int killcounter;
} Player;

// 子弹数据
typedef struct Bullet {
	Vector2 pos;
	Vector2 lockonpos;
	float radius;
	float speed;
	bool isShoot;
	int bullettype;
	int killcounter;
} Bullet;

// 敌人数据
typedef struct Enemy {
	Vector2 pos;
	int hp;
	float radius;
	float speed;
	int respowntime;
	bool isAlive;
} Enemy;

// 物品数据
typedef struct Item {
	Vector2 pos;
	float radius;
	bool isalive;
} Item;

typedef struct fourpoint {
	Vector2 leftup;
	Vector2 rightup;
	Vector2 leftdown;
	Vector2 rightdown;
} fourpoint;

enum Houmenn { left, right };

class StageScene : public IScene {
public:
	void Initialize() override;
	void Update(char* keys, char* preKeys) override;
	void Draw() override;

private:
	// 玩家数据

	Player player;
	Bullet bullet[10];
	Enemy enemy[160];
	Item point[160];

	 // 游戏状态
	bool bladestorm;
	int bladestormtime;
	Houmenn playerhoumenn;
	Houmenn enemyhoumenn[150];
	int flame;
	int bladeflame;
	int deadboss;
	int wave1num = 160;

	// 数字显示
	int numberarray[5] = {0, 0, 0, 0, 0};
	int numberarraysaver = 0;

	// 图形资源
	int numgraph[10];
	int boltimage;
	int holderupimage;
	int holderunderimage;
	int monitaimage;
	int hpcounter;
	int hpblock;
	int bulletimage;
	float shotangle[10];
	fourpoint modfourpos[10];
	int flybladeimage;
	int playergraphL[4];
	int playergraphR[4];
	int bladestormgraph[4];
	int enemygraphL[4];
	int enemygraphR[4];
	int enemydeathgraph[4];
	int bossgraph[4];
	int bossexp[15];
	int pointgraph;
	int maograph;
	int gameovergraph;
	int gamecleargraph;

	// 音频资源
	int bgmgraph;
	int playhandle;
	int gungraph;
	int gunplayhandle;
	int reloadgraph;
	int reloadhandle;
	// 辅助函数
	fourpoint FourPointProcessing(const Vector2& object, float radians);
	void BulletMoving(Vector2& object, const Vector2& direction, float speed);
	void LockonMoving(Vector2& object, const Vector2& target, float speed);
	Vector2 enemyRandomPosition(int WindowWidth, int WindowHeight);
	void LoadResources();
};