#pragma once
#include "Objcet.h"
#include <iostream>

#define MAX_OBJECTS_COUNT 100


#define	OBJECT_BUILDING 0
#define	OBJECT_CHARACTER 1
#define	OBJECT_BULLET 2
#define	OBJECT_ARROW 3


class SceneMgr
{
	int m_num;
public:
	SceneMgr(int width, int height);
	~SceneMgr();

	
	void add(int x, int y, int t);
	

	void draw();
	void update(DWORD time);
	void release();
	void collision();
	void bulletmake();
	bool BoxBoxCollisionTest(float minX, float minY, float maxX, float maxY, float minX1, float minY1, float maxX1, float maxY1);

	Renderer *m_renderer;
	Objcet* m_objects[MAX_OBJECTS_COUNT];
	int m_windowWidth;
	int m_windowHeight;
};
