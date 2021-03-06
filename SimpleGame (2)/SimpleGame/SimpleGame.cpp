/*
Copyright 2017 Lee Taek Hee (Korea Polytech University)

This program is free software: you can redistribute it and/or modify
it under the terms of the What The Hell License. Do it plz.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY.
*/

#include "stdafx.h"
#include <iostream>
#include "Dependencies\glew.h"
#include "Dependencies\freeglut.h"
#include "Object.h"
#include "Renderer.h"
#include "SceneMgr.h"
#include "Sound.h"

//Renderer *g_Renderer = NULL;
SceneMgr *g_SceneMgr = NULL;


DWORD m_fStartTime = 0;
DWORD mouse_StartTime = 0;
bool mouse_click = false;


DWORD A_fStartTime = 0;
DWORD mouseA_StartTime = 0;
bool mouseA_click = false;
void RenderScene(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	
	DWORD currTime = timeGetTime();
	DWORD elapsedTime = currTime - m_fStartTime;
	m_fStartTime = currTime;

	g_SceneMgr->update((float)elapsedTime);
	g_SceneMgr->draw();
	
	glutSwapBuffers();

}

void Idle(void)
{
	RenderScene();
}

void MouseInput(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		mouse_click = true;
		if (mouse_StartTime == 0.f)
		{
			mouse_StartTime = timeGetTime();
			g_SceneMgr->add(x - 250, 400 - y, OBJECT_CHARACTER, TEAM_2);
		}
	}
	if (button == GLUT_LEFT_BUTTON && state == GLUT_UP)
	{
		DWORD m_currTime = timeGetTime();
		DWORD m_elapsedTime = m_currTime - mouse_StartTime;
	
		if (mouse_click && m_elapsedTime > 7000.f)
		{
			mouse_click = false;
			mouse_StartTime = 0.f;
		}
	}
	/// 근접공격 유닛 부르기
	if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
	{
		mouse_click = true;
		if (mouseA_StartTime == 0.f)
		{
			mouseA_StartTime = timeGetTime();
			g_SceneMgr->add(x - 250, 400 - y, OBJECT_MELEEATTACK, TEAM_2);
		}
	}
	if (button == GLUT_RIGHT_BUTTON && state == GLUT_UP)
	{
		DWORD m_currTime = timeGetTime();
		DWORD m_elapsedTime = m_currTime - mouseA_StartTime;

		if (mouse_click && m_elapsedTime > 3000.f)
		{
			mouseA_click = false;
			mouseA_StartTime = 0.f;
		}
	}
	RenderScene();
}

void KeyInput(unsigned char key, int x, int y)
{
	RenderScene();
}

void SpecialKeyInput(int key, int x, int y)
{
	RenderScene();
}

int main(int argc, char **argv)
{
	float m_fStartTime = (float)timeGetTime();
	// Initialize GL things
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(0, 0);
	glutInitWindowSize(500, 800);
	glutCreateWindow("Game Software Engineering KPU");
	glewInit();
	if (glewIsSupported("GL_VERSION_3_0"))
	{
		std::cout << " GLEW Version is 3.0\n ";
	}
	else
	{
		std::cout << "GLEW 3.0 not supported\n ";
	}

	// Initialize Renderer
	//g_Renderer = new Renderer(500, 500);
	/*if (!g_Renderer->IsInitialized())
	{
		std::cout << "Renderer could not be initialized.. \n";
	}*/
	
	glutDisplayFunc(RenderScene);
	glutIdleFunc(Idle);
	glutKeyboardFunc(KeyInput);
	glutMouseFunc(MouseInput);
	glutSpecialFunc(SpecialKeyInput);

	g_SceneMgr = new SceneMgr(500, 800);


	g_SceneMgr->add(-180, 250 , OBJECT_BUILDING, TEAM_1);
	g_SceneMgr->add(0, 300, OBJECT_BUILDING, TEAM_1);
	g_SceneMgr->add(180, 250, OBJECT_BUILDING, TEAM_1);

	g_SceneMgr->add(-180, -250, OBJECT_BUILDING, TEAM_2);
	g_SceneMgr->add(0, -300, OBJECT_BUILDING, TEAM_2);
	g_SceneMgr->add(180, -250, OBJECT_BUILDING, TEAM_2);

	m_fStartTime = timeGetTime();
	
	glutMainLoop();

	
	delete g_SceneMgr;
	
	return 0;
}

