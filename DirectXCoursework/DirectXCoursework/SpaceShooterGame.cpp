
#include "SpaceShooterGame.h"
#include <Windows.h>
#include <xmemory>
#include <time.h>
#include "MathUtility.h"
struct vec3
{
	float x, y, z;
};

struct vertex
{
	Vector3D position;
	Vector2D texcoord;
};


__declspec(align(16))
struct constant //Specify the position and rotation or any other constant behavioural movements of scene objects, further work needs to create seperation for all the scene objects correspondingly
{
	Matrix4x4 m_world;
	Matrix4x4 m_view;
	Matrix4x4 m_proj;
	Vector4D m_light_direction;
	Vector4D m_camera_position;
	Vector4D m_light_position = Vector4D(0, 1, 0, 0);
	float m_light_radius = 40.0f;
	float m_time = 0.0f;
};



SpaceShooterGame::SpaceShooterGame()
{
}


SpaceShooterGame::~SpaceShooterGame()
{
}
void SpaceShooterGame::onCreate()
{
	Window::onCreate();

	InputSystem::get()->addListener(this);

	m_play_state = true;
	InputSystem::get()->showCursor(false);

	

	RECT rc = this->getClientWindowRect();
	m_swap_chain = GraphicsEngine::get()->getRenderSystem()->createSwapChain(this->m_hwnd, rc.right - rc.left, rc.bottom - rc.top);

	srand((unsigned int)time(NULL));

	//Initialise the asteroid meshes
	for (unsigned int i = 0; i < 200; i++) {

		m_asteroids_pos[i] = Vector3D(rand()%4000 - 2000, rand() % 4000 - 2000, rand() % 4000 - 2000);

		m_asteroids_rot[i] = Vector3D((rand() % 628)/100.f - 2000, (rand() % 628)/100.f - 2000, (rand() % 628) - 2000);

		float scale = rand() % 10 + 6;
		m_asteroids_scale[i] = Vector3D(scale, scale, scale);
	}


	m_sky_tex = GraphicsEngine::get()->getTextureManager()->createTextureFromFile(L"Assets\\Textures\\stars_map.jpg");
	m_sky_mesh = GraphicsEngine::get()->getMeshManager()->createMeshFromFile(L"Assets\\Meshes\\sphere.obj");


	m_spaceship_tex = GraphicsEngine::get()->getTextureManager()->createTextureFromFile(L"Assets\\Textures\\spaceship.jpg");
	m_spaceship_mesh = GraphicsEngine::get()->getMeshManager()->createMeshFromFile(L"Assets\\Meshes\\spaceship.obj");

	m_asteroid_tex = GraphicsEngine::get()->getTextureManager()->createTextureFromFile(L"Assets\\Textures\\asteroid.jpg");
	m_asteroid_mesh = GraphicsEngine::get()->getMeshManager()->createMeshFromFile(L"Assets\\Meshes\\asteroid.obj");

	m_planet_normal_map = GraphicsEngine::get()->getTextureManager()->createTextureFromFile(L"Assets\\Meshes\\brick_n.jpg");
	m_planet_tex = GraphicsEngine::get()->getTextureManager()->createTextureFromFile(L"Assets\\Meshes\\brick_d.jpg");
	m_planet_mesh_for_test = GraphicsEngine::get()->getMeshManager()->createMeshFromFile(L"Assets\\Meshes\\sphere_hq.obj");



	m_base_mat = GraphicsEngine::get()->createMaterial(L"DirectionalLightVertexShader.hlsl", L"DirectionalLightPixelShader.hlsl");
	m_base_mat->setCullMode(CULL_MODE_BACK);

	m_spaceship_mat = GraphicsEngine::get()->createMaterial(m_base_mat);
	m_spaceship_mat->addTexture(m_spaceship_tex);
	m_spaceship_mat->setCullMode(CULL_MODE_BACK);

	m_asteroid_mat = GraphicsEngine::get()->createMaterial(L"DirectionalLightVertexShader.hlsl", L"DirectionalLightPixelShader.hlsl");
	m_asteroid_mat->addTexture(m_asteroid_tex);
	m_asteroid_mat->setCullMode(CULL_MODE_BACK);

	m_planet_mat = GraphicsEngine::get()->createMaterial(L"BumpyVS.hlsl", L"BumpyPS.hlsl");
	m_planet_mat->addTexture(m_planet_tex);
	m_planet_mat->addTexture(m_planet_normal_map);
	m_planet_mat->setCullMode(CULL_MODE_BACK);

	m_sky_mat = GraphicsEngine::get()->createMaterial(L"SkyBoxVertexShader.hlsl", L"SkyBoxPixelShader.hlsl");
	m_sky_mat->addTexture(m_sky_tex);
	m_sky_mat->setCullMode(CULL_MODE_FRONT);

	m_world_cam.setTranslation(Vector3D(0, 0, -2));

	m_list_materials.reserve(200);
}
void SpaceShooterGame::update()
{
	updateSpaceShipMovement();
	updateThirdPersonCamera();
	updateLight();
	updateSkybox();
	
}

void SpaceShooterGame::updateCamera()
{
	Matrix4x4 world_cam, temp;
	world_cam.setIdentity();

	m_cam_rot.m_x += m_delta_mouse_y * m_delta_time * 0.1f;
	m_cam_rot.m_y += m_delta_mouse_x * m_delta_time * 0.1f;


	m_current_cam_rot = Vector3D::lerp(m_current_cam_rot, m_cam_rot, 3.5f * m_delta_time);

	temp.setIdentity();
	temp.setRotationX(m_current_cam_rot.m_x);
	world_cam *= temp;

	temp.setIdentity();
	temp.setRotationY(m_current_cam_rot.m_y);
	world_cam *= temp;

	Vector3D new_pos = m_world_cam.getTranslation() + world_cam.getZDirection() * (m_forward * 0.05f);

	new_pos = new_pos + world_cam.getXDirection() * (m_rightward * 0.05f);

	world_cam.setTranslation(new_pos);

	m_world_cam = world_cam;

	world_cam.inverse();

	m_view_cam = world_cam;

	int width = (this->getClientWindowRect().right - this->getClientWindowRect().left);
	int height = (this->getClientWindowRect().bottom - this->getClientWindowRect().top);

	m_proj_cam.setPerspectiveFovLH(1.57f, ((float)width / (float)height), 0.1f, 6000.f);
}

void SpaceShooterGame::updateModel(Vector3D position, Vector3D rotation, Vector3D scale, const std::vector<MaterialPtr>& list_materials)
{
	constant cc;

	Matrix4x4 temp;
	cc.m_world.setIdentity();

	temp.setIdentity();
	temp.setScale(scale);
	cc.m_world *= temp;


	temp.setIdentity();
	temp.setRotationX(rotation.m_x);
	cc.m_world *= temp;

	temp.setIdentity();
	temp.setRotationY(rotation.m_y);
	cc.m_world *= temp;

	temp.setIdentity();
	temp.setRotationZ(rotation.m_z);
	cc.m_world *= temp;


	temp.setIdentity();
	temp.setTranslation(position);
	cc.m_world *= temp;


	cc.m_view = m_view_cam;
	cc.m_proj = m_proj_cam;
	cc.m_camera_position = m_world_cam.getTranslation();

	cc.m_light_position = m_light_position;
	cc.m_light_radius = 0.0f;
	cc.m_light_direction = m_light_rot_matrix.getZDirection();
	cc.m_time = m_time;

	for (unsigned int m = 0; m < list_materials.size(); m++)
	{
		list_materials[m]->setData(&cc, sizeof(constant));
	}
}

void SpaceShooterGame::updateSkybox()
{
	constant cc;

	cc.m_world.setIdentity();
	cc.m_world.setScale(Vector3D(4000.f, 4000.f, 4000.f));
	cc.m_world.setTranslation(m_world_cam.getTranslation());
	cc.m_view = m_view_cam;
	cc.m_proj = m_proj_cam;

	m_sky_mat->setData(&cc, sizeof(constant));
}

void SpaceShooterGame::drawMesh(const MeshPtr& mesh, const std::vector<MaterialPtr>& list_materials)
{
	//SET THE VERTICES OF THE TRIANGLE TO DRAW
	GraphicsEngine::get()->getRenderSystem()->getImmediateDeviceContext()->setVertexBuffer(mesh->getVertexBuffer());
	//SET THE INDICES OF THE TRIANGLE TO DRAW
	GraphicsEngine::get()->getRenderSystem()->getImmediateDeviceContext()->setIndexBuffer(mesh->getIndexBuffer());

	for (size_t m = 0; m < mesh->getNumMaterialSlots(); m++) {

		if (m >= list_materials.size()) break;

		MaterialSlot mat = mesh->getMaterialSlot(m);

		GraphicsEngine::get()->setMaterial(list_materials[m]);


		// FINALLY DRAW THE TRIANGLE
		GraphicsEngine::get()->getRenderSystem()->getImmediateDeviceContext()->drawIndexedTriangleList((UINT)mat.num_indices, 0, (UINT)mat.start_index);
	}


}

void SpaceShooterGame::drawNormalMappedMesh(const MeshPtr& mesh, const std::vector<MaterialPtr>& list_materials)
{
	for (unsigned int m = 0; m < list_materials.size(); m++)
	{
		if (m == list_materials.size()) break;

		MaterialSlot mat = mesh->getMaterialSlot(m);

		GraphicsEngine::get()->setMaterial(list_materials[m]);
		//SET THE VERTICES OF THE TRIANGLE TO DRAW
		GraphicsEngine::get()->getRenderSystem()->getImmediateDeviceContext()->setVertexBuffer(mesh->getVertexBuffer());
		//SET THE INDICES OF THE TRIANGLE TO DRAW
		GraphicsEngine::get()->getRenderSystem()->getImmediateDeviceContext()->setIndexBuffer(mesh->getIndexBuffer());
		// FINALLY DRAW THE TRIANGLE
		GraphicsEngine::get()->getRenderSystem()->getImmediateDeviceContext()->drawIndexedTriangleList((UINT)mat.num_indices, 0, (UINT)mat.start_index);
	}
}

void SpaceShooterGame::render()
{
	//CLEAR THE RENDER TARGET 
	GraphicsEngine::get()->getRenderSystem()->getImmediateDeviceContext()->clearRenderTargetColor(this->m_swap_chain,0, 0.3f, 0.4f, 1);
	//SET VIEWPORT OF RENDER TARGET IN WHICH WE HAVE TO DRAW
	RECT rc = this->getClientWindowRect();
	GraphicsEngine::get()->getRenderSystem()->getImmediateDeviceContext()->setViewportSize(rc.right - rc.left, rc.bottom - rc.top);

	//RENDER SPACESHIP
	m_list_materials.clear();
	m_list_materials.push_back(m_spaceship_mat);
	updateModel(m_current_spaceship_pos, m_current_spaceship_rot, Vector3D(1, 1, 1), m_list_materials);
	drawMesh(m_spaceship_mesh, m_list_materials);


	//DRAW THE TEST PLANET
	/*m_list_materials.clear();
	m_list_materials.push_back(m_planet_mat);
	updateModel(Vector3D(0, 0, 0), Vector3D(), Vector3D(1, 1, 1), m_list_materials);
	drawNormalMappedMesh(m_planet_mesh_for_test, m_list_materials);*/



	
	//RENDER ASTEROIDS
	m_list_materials.clear();
	m_list_materials.push_back(m_asteroid_mat);	
	for (unsigned int i = 0; i < 200; i++) {

		
		updateModel(m_asteroids_pos[i], m_asteroids_rot[i], m_asteroids_scale[i], m_list_materials);
		drawMesh(m_asteroid_mesh, m_list_materials);
	}



	//RENDER SKYBOX/SPHERE
	m_list_materials.clear();
	m_list_materials.push_back(m_sky_mat);
	drawMesh(m_sky_mesh, m_list_materials);

	GraphicsEngine::get()->getRenderSystem()->getImmediateDeviceContext()->clearDepthStencil(this->m_swap_chain);


	m_swap_chain->present(true);


	m_old_delta = m_new_delta;
	m_new_delta = ::GetTickCount64();

	//m_delta_time = (m_old_delta) ? ((m_new_delta - m_old_delta) / 1000.0f) : 0;

	m_delta_time = 1.0f / 60.0f;
	m_time += m_delta_time;
}

void SpaceShooterGame::updateLight()
{
	Matrix4x4 temp;
	m_light_rot_matrix.setIdentity();

	temp.setIdentity();
	temp.setRotationX(-0.707f);
	m_light_rot_matrix *= temp;

	temp.setIdentity();
	temp.setRotationY(0.707f);
	m_light_rot_matrix *= temp;
}

void SpaceShooterGame::updateSpaceShipMovement()
{
	Matrix4x4 world_model_spaceShip, temp;
	world_model_spaceShip.setIdentity();

	m_spaceship_rot.m_x += m_delta_mouse_y * m_delta_time * 0.1f;
	m_spaceship_rot.m_y += m_delta_mouse_x * m_delta_time * 0.1f;


	if (m_spaceship_rot.m_x >= 1.57f)
		m_spaceship_rot.m_x = 1.57f;
	else if (m_spaceship_rot.m_x <= -1.57f)
		m_spaceship_rot.m_x = -1.57f;

	m_current_cam_rot = Vector3D::lerp(m_current_cam_rot, m_cam_rot, 3.5f * m_delta_time);

	temp.setIdentity();
	temp.setRotationX(m_current_cam_rot.m_x);
	world_model_spaceShip *= temp;

	temp.setIdentity();
	temp.setRotationY(m_current_cam_rot.m_y);
	world_model_spaceShip *= temp;

	

	if (m_turbo_mode)
		m_spaceship_speed = 350.0f;
	else
		m_spaceship_speed = 125.0f;

	

	m_current_spaceship_rot = Vector3D::lerp(m_current_spaceship_rot, m_spaceship_rot,4.5f*m_delta_time);

	m_spaceship_pos = m_spaceship_pos + world_model_spaceShip.getZDirection() * (m_forward) * m_spaceship_speed * m_delta_time+ world_model_spaceShip.getXDirection() * (m_rightward) *m_spaceship_speed * m_delta_time;

	m_current_spaceship_pos = Vector3D::lerp(m_current_spaceship_pos, m_spaceship_pos, 3.0f * m_delta_time);
}

void SpaceShooterGame::updateThirdPersonCamera()
{
	Matrix4x4 world_cam, temp;
	world_cam.setIdentity();

	m_cam_rot.m_x += m_delta_mouse_y * m_delta_time * 0.1f;
	m_cam_rot.m_y += m_delta_mouse_x * m_delta_time * 0.1f;


	if (m_cam_rot.m_x >= 1.57f)
		m_cam_rot.m_x = 1.57f;
	else if (m_cam_rot.m_x <= -1.57f)
		m_cam_rot.m_x = -1.57f;

	m_current_cam_rot = Vector3D::lerp(m_current_cam_rot, m_cam_rot, 3.5f * m_delta_time);

	temp.setIdentity();
	temp.setRotationX(m_current_cam_rot.m_x);
	world_cam *= temp;

	temp.setIdentity();
	temp.setRotationY(m_current_cam_rot.m_y);
	world_cam *= temp;


	if (m_forward) {



		if (m_turbo_mode) {

			if (m_forward > 0) {

				m_cam_distance = 25.0f;
			}
			else {

				m_cam_distance = 5.0f;
			}
		}
		else {

			if (m_forward > 0) {

				m_cam_distance = 16.0f;
			}
			else {

				m_cam_distance = 9.0f;
			}
		}

		
	}
	else {

		m_cam_distance = 14.0f;
	}

	m_current_cam_distance = lerp(m_current_cam_distance, m_cam_distance, 2.4f * m_delta_time);



	m_cam_pos = m_current_spaceship_pos;

	Vector3D new_pos = m_cam_pos + world_cam.getZDirection() * (-m_current_cam_distance);
	new_pos = new_pos + world_cam.getYDirection() * (5.0f);

	world_cam.setTranslation(new_pos);

	m_world_cam = world_cam;

	world_cam.inverse();

	m_view_cam = world_cam;

	int width = (this->getClientWindowRect().right - this->getClientWindowRect().left);
	int height = (this->getClientWindowRect().bottom - this->getClientWindowRect().top);

	m_proj_cam.setPerspectiveFovLH(1.57f, ((float)width / (float)height), 0.1f, 5000.0f);
}



void SpaceShooterGame::onUpdate()
{
	Window::onUpdate();
	InputSystem::get()->update();
	//COMPUTE TRANSFORM MATRICES
	this->update();
	this->render();

	m_delta_mouse_x = 0;
	m_delta_mouse_y = 0;
}


void SpaceShooterGame::onDestroy()
{
	Window::onDestroy();
	m_swap_chain->setFullScreen(false, 1, 1);

}

void SpaceShooterGame::onFocus()
{
	InputSystem::get()->addListener(this);
}

void SpaceShooterGame::onKillFocus()
{
	InputSystem::get()->removeListener(this);
}

void SpaceShooterGame::onSize()
{
	RECT rc = this->getClientWindowRect();
	m_swap_chain->resize(rc.right-rc.left, rc.bottom-rc.top);
	this->update();
}

void SpaceShooterGame::onKeyDown(int key)
{
	if (key == 'W')
	{
		//m_rot_x += 3.14f*m_delta_time;
		m_forward = 1.0f;
	}
	else if (key == 'S')
	{
		//m_rot_x -= 3.14f*m_delta_time;
		m_forward = -1.0f;
	}
	else if (key == 'A')
	{
		//m_rot_y += 3.14f*m_delta_time;
		m_rightward = -1.0f;
	}
	else if (key == 'D')
	{
		//m_rot_y -= 3.14f*m_delta_time;
		m_rightward = 1.0f;
	}
	else if (key == VK_SHIFT)
	{
		m_turbo_mode = true;
	}
}

void SpaceShooterGame::onKeyUp(int key)
{
	m_forward = 0.0f;
	m_rightward = 0.0f;

	if (key == VK_ESCAPE)
	{
		if (m_play_state)
		{
			m_play_state = false;
			InputSystem::get()->showCursor(!m_play_state);
		}
	}
	else if (key == 'F')
	{
		m_fullscreen_state = (m_fullscreen_state) ? false : true;
		RECT size_screen = this->getScreenSize();

		m_swap_chain->setFullScreen(m_fullscreen_state, size_screen.right, size_screen.bottom);
	}
	else if (key == VK_SHIFT)
	{
		m_turbo_mode = false;
	}
}

void SpaceShooterGame::onMouseMove(const Point& mouse_pos)
{
	if (!m_play_state) return;

	RECT win_size = this->getClientWindowRect();

	int width = (win_size.right - win_size.left);
	int height = (win_size.bottom - win_size.top);

	m_delta_mouse_x = (float)(mouse_pos.m_x - (int)(win_size.left + (width / 2.0f)));
	m_delta_mouse_y = (float)(mouse_pos.m_y - (int)(win_size.top + (height / 2.0f)));

	InputSystem::get()->setCursorPosition(Point(win_size.left + (int)(width / 2.0f), win_size.top + (int)(height / 2.0f)));
}
void SpaceShooterGame::onLeftMouseDown(const Point& mouse_pos)
{
	if (!m_play_state) {
		m_play_state = true;
		InputSystem::get()->showCursor(!m_play_state);
	}
}

void SpaceShooterGame::onLeftMouseUp(const Point& mouse_pos)
{
	
}

void SpaceShooterGame::onRightMouseDown(const Point& mouse_pos)
{
	
}

void SpaceShooterGame::onRightMouseUp(const Point& mouse_pos)
{
	
}



