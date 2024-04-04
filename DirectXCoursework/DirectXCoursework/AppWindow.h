
#pragma once
#include "Window.h"
#include "GraphicsEngine.h"
#include "SwapChain.h"
#include "DeviceContext.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "ConstantBuffer.h"
#include "VertexShader.h"
#include "PixelShader.h"
#include "Point.h"
#include "InputListener.h"
#include "InputSystem.h"
#include "Matrix4x4.h"
#include "Vector2D.h"
#include "Vector3D.h"
#include "Vector4D.h"
#include "Prerequisites.h"
class AppWindow : public Window,public InputListener
{
public:
	AppWindow();
	~AppWindow();

	void update();
	void updateCamera();
	void updateModel(Vector3D position, const MaterialPtr& material);
	void updateSkybox();
	void drawMesh(const MeshPtr& mesh, const MaterialPtr& material);
	void render();
	void updateLight();

	// Inherited via Window
	virtual void onCreate() override;
	virtual void onUpdate() override;
	virtual void onDestroy() override;
	virtual void onFocus() override;
	virtual void onKillFocus() override;
	virtual void onSize() override;


	//Inherited via InputListener
	virtual void onKeyDown(int key) override;
	virtual void onKeyUp(int key) override;
	virtual void onMouseMove(const Point& mouse_pos) override;
	virtual void onLeftMouseDown(const Point& mouse_pos) override;
	virtual void onLeftMouseUp(const Point& mouse_pos) override;
	virtual void onRightMouseDown(const Point& mouse_pos) override;
	virtual void onRightMouseUp(const Point& mouse_pos) override;
private:
	SwapChainPtr m_swap_chain;
	VertexBufferPtr m_vb;
	VertexShaderPtr m_vs,m_pointLight_vs;
	PixelShaderPtr m_ps,m_sky_ps, m_pointLight_ps;
	ConstantBufferPtr m_cb,m_sky_cb;
	IndexBufferPtr m_ib;


	TexturePtr m_wood_tex;
	TexturePtr m_sky_tex;
	TexturePtr m_earth_color_tex;
	TexturePtr m_earth_spec_tex;
	TexturePtr m_clouds_tex;
	TexturePtr m_earth_night_tex;
	TexturePtr m_wall_tex;
	TexturePtr m_bricks_tex;

	MeshPtr m_mesh,m_scene_mesh;
	MeshPtr m_sky_mesh;

	MeshPtr m_torus_mesh;
	MeshPtr m_suzanne_mesh;
	MeshPtr m_plane_mesh;

	MaterialPtr m_mat,m_sky_mat, m_earth_mat,m_bricks_mat;

private:
	long m_old_delta;
	long m_new_delta;
	float m_delta_time;

	float m_delta_pos;
	float m_delta_scale;
	float m_delta_rot;

	float m_rot_x = 0.0f;
	float m_rot_y = 0.0f;

	float m_light_rot_y = 0.0f;

	float m_scale_cube = 1;
	float m_forward = 0.0f;
	float m_rightward = 0.0f;
	
	bool cull = true;
	Matrix4x4 m_world_cam;
	Matrix4x4 m_view_cam;
	Matrix4x4 m_proj_cam;


	RECT size_screen;

	bool m_play_state = false;

	bool m_full_screen_state = false;

	float m_time = 0.0f;


	float m_light_radius = 4.0f;
	float m_attenuation = 2.0f;
	bool m_anim = false;


	Vector4D m_light_position;
};


