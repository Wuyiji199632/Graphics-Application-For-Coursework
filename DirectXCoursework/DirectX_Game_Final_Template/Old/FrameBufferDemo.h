/*MIT License

C++ 3D Game Tutorial Series (https://github.com/PardCode/CPP-3D-Game-Tutorial-Series)

Copyright (c) 2019-2022, PardCode

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.*/


#pragma once
#include <DX3D/Window/Window.h>
#include <DX3D/Graphics/GraphicsEngine.h>
#include <DX3D/Graphics/SwapChain.h>
#include <DX3D/Graphics/DeviceContext.h>
#include <DX3D/Graphics/VertexBuffer.h>
#include <DX3D/Graphics/IndexBuffer.h>
#include <DX3D/Graphics/ConstantBuffer.h>
#include <DX3D/Graphics/VertexShader.h>
#include <DX3D/Graphics/PixelShader.h>
#include "InputListener.h"
#include "Matrix4x4.h"
#include "MiniGame.h"


class FrameBufferDemo : public Window, public InputListener
{
public:
	FrameBufferDemo();
	~FrameBufferDemo();

	// Inherited via Window
	virtual void onCreate() override;
	virtual void onUpdate() override;
	virtual void onDestroy() override;
	virtual void onFocus() override;
	virtual void onKillFocus() override;
	virtual void onSize() override;

	// Inherited via InputListener
	virtual void onKeyDown(int key) override;
	virtual void onKeyUp(int key) override;
	virtual void onMouseMove(const Point& mouse_pos) override;

	virtual void onLeftMouseDown(const Point& mouse_pos) override;
	virtual void onLeftMouseUp(const Point& mouse_pos) override;
	virtual void onRightMouseDown(const Point& mouse_pos) override;
	virtual void onRightMouseUp(const Point& mouse_pos) override;
public:
	void render();
	void update();
	void updateModel(Vector3D position, Vector3D rotation, Vector3D scale, const std::vector<MaterialPtr>& list_materials);
	void updateThirdPersonCamera();
	void updateSkyBox();
	void updateLight();
	void drawMesh(const MeshPtr& mesh, const std::vector<MaterialPtr>& list_materials/* MaterialPtr* list_materials, unsigned int size_list_materials*/);
	void updateViewportProjection();
private:
	SwapChainPtr m_swap_chain;

	MeshPtr m_sphere_mesh;
	TexturePtr m_brick_tex;
	TexturePtr m_brick_normal_tex;
	MaterialPtr m_brick_mat;


	MaterialPtr m_screen_monitor;
	MaterialPtr m_case_monitor;



	TexturePtr m_sky_tex;
	MeshPtr m_sky_mesh;
	MaterialPtr m_sky_mat;
	MaterialPtr m_base_mat;
private:
	long m_old_delta;
	long m_new_delta;
	float m_delta_time;

	float m_current_cam_distance;
	float m_cam_distance = 2.4f;
	Vector3D m_current_cam_rot;
	Vector3D m_cam_rot;
	Vector3D m_cam_pos;

	float m_delta_mouse_x = 0.0f, m_delta_mouse_y = 0.0f;

	Matrix4x4 m_world_cam;
	Matrix4x4 m_view_cam;
	Matrix4x4 m_proj_cam;

	float m_time = 0.0f;

	Matrix4x4 m_light_rot_matrix;
	bool m_play_state = false;
	bool m_fullscreen_state = false;
	std::vector<MaterialPtr> m_list_materials;



	MiniGame m_mini_game;
};

