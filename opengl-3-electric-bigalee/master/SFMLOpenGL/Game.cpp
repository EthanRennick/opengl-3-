#include <Game.h>

static bool flip;

Game::Game() : window(VideoMode(800, 600), "OpenGL Cube VBO")
{
}

Game::~Game() {}

void Game::run()
{

	initialize();

	Event event;

	while (isRunning) {

		cout << "Game running..." << endl;

		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
			{
				isRunning = false;
			}
		}
		update();
		render();
	}

}

typedef struct
{
	float coordinate[3];
	float color[3];
} Vertex;

Vertex vertex[8];
GLubyte triangles[36]; //triangle points

/* Variable to hold the VBO identifier */
GLuint vbo[1];
GLuint index;

vector<gpp::Vector3> cube;

void Game::initialize()
{
	isRunning = true;
	cube.push_back(gpp::Vector3(1.0f, -1.0f, -5.0f)); //3 - 0
	cube.push_back(gpp::Vector3(-1.0f, -1.0f, -5.0f)); //2 - 1
	cube.push_back(gpp::Vector3(-1.0f, 1.0f, -5.0f)); //1 - 2
	cube.push_back(gpp::Vector3(1.0f, 1.0f, -5.0f)); //4 - 3
	cube.push_back(gpp::Vector3(1.0f, -1.0f, -10.0f)); //7 - 4
	cube.push_back(gpp::Vector3(1.0f, 1.0f, -10.0f)); //8 - 5
	cube.push_back(gpp::Vector3(-1.0f, -1.0f, -10.0f)); //6 - 6
	cube.push_back(gpp::Vector3(-1.0f, 1.0f, -10.0f)); //5 - 7
	glewInit();

	// Vertices for one Triangle
	float vertices[] = { 1.0f, 1.0f, -5.0f, //1
	-1.0f, 1.0f, -5.0f, //2
	-1.0f, -1.0f, -5.0f,  //3
	1.0f, -1.0f, -5.0f, //4
	-1.0f, 1.0f, -10.0f, //5
	-1.0f, -1.0f, -10.0f, //6
	1.0f, -1.0f, -10.0f, //7
	1.0f, 1.0f, -10.0f //8
	};
	
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glTranslatef(0, 0, -8);
	glMatrixMode(GL_PROJECTION); //small, far away
	glLoadIdentity();
	gluPerspective(45.0, window.getSize().x / window.getSize().y, 1.0, 500.0);
	glMatrixMode(GL_MODELVIEW); //object moves, not us, not our view of it. its mass doesnt change

	/* Vertices counter-clockwise winding */
	triangles[0] = (cube.at(0).x); 
	triangles[1] = (cube.at(0).y); 
	triangles[2] = (cube.at(0).z); 

	triangles[3] = (cube.at(1).x);
	triangles[4] = (cube.at(1).y);
	triangles[5] = (cube.at(1).z);

	triangles[6] = (cube.at(2).x);
	triangles[7] = (cube.at(2).y);
	triangles[8] = (cube.at(2).z);

	triangles[9] = (cube.at(3).x);
	triangles[10] = (cube.at(3).y);
	triangles[11] = (cube.at(3).z);

	triangles[12] = (cube.at(2).x);
	triangles[12] = (cube.at(2).y);
	triangles[14] = (cube.at(2).z);

	triangles[15] = (cube.at(0).x);
	triangles[16] = (cube.at(0).y);
	triangles[17] = (cube.at(0).z);


	triangles[18] = (cube.at(4).x);
	triangles[19] = (cube.at(4).y);
	triangles[20] = (cube.at(4).z);

	triangles[21] = (cube.at(5).x);
	triangles[22] = (cube.at(5).y);
	triangles[23] = (cube.at(5).z);

	triangles[24] = (cube.at(6).x);
	triangles[25] = (cube.at(6).y);
	triangles[26] = (cube.at(6).z);

	triangles[27] = (cube.at(7).x);
	triangles[28] = (cube.at(7).y);
	triangles[29] = (cube.at(7).z);

	triangles[30] = (cube.at(0).x);
	triangles[31] = (cube.at(0).y);
	triangles[32] = (cube.at(0).z);

	triangles[33] = (cube.at(5).x);
	triangles[34] = (cube.at(5).y);
	triangles[35] = (cube.at(5).z);


	vertex[0].coordinate[0] = (cube.at(0).x); //3
	vertex[0].coordinate[1] = (cube.at(0).y); //3
	vertex[0].coordinate[2] = (cube.at(0).z); //3

	vertex[1].coordinate[0] = (cube.at(1).x); //1
	vertex[1].coordinate[1] = (cube.at(1).y); //1
	vertex[1].coordinate[2] = (cube.at(1).z); //1

	vertex[2].coordinate[0] = (cube.at(2).x); //2
	vertex[2].coordinate[1] = (cube.at(2).y); //2
	vertex[2].coordinate[2] = (cube.at(2).z); //2

	vertex[3].coordinate[0] = (cube.at(3).x); //3
	vertex[3].coordinate[1] = (cube.at(3).y); //3
	vertex[3].coordinate[2] = (cube.at(3).z); //3

	vertex[4].coordinate[0] = (cube.at(4).x); //1
	vertex[4].coordinate[1] = (cube.at(4).y); //1
	vertex[4].coordinate[2] = (cube.at(4).z); //1

	vertex[5].coordinate[0] = (cube.at(5).x); //2
	vertex[5].coordinate[1] = (cube.at(5).y); //2
	vertex[5].coordinate[2] = (cube.at(5).z); //2

	vertex[6].coordinate[0] = (cube.at(6).x); //1
	vertex[6].coordinate[1] = (cube.at(6).y); //1
	vertex[6].coordinate[2] = (cube.at(6).z); //1

	vertex[7].coordinate[0] = (cube.at(7).x); //2
	vertex[7].coordinate[1] = (cube.at(7).y); //2
	vertex[7].coordinate[2] = (cube.at(7).z); //2

	vertex[0].color[0] = 0.1f;
	vertex[0].color[1] = 1.0f;
	vertex[0].color[2] = 0.0f;

	vertex[1].color[0] = 0.2f;
	vertex[1].color[1] = 1.0f;
	vertex[1].color[2] = 0.0f;

	vertex[2].color[0] = 0.3f;
	vertex[2].color[1] = 1.0f;
	vertex[2].color[2] = 0.0f;

	vertex[3].color[0] = 0.4f;
	vertex[3].color[1] = 1.0f;
	vertex[3].color[2] = 0.0f;

	vertex[4].color[0] = 0.5f;
	vertex[4].color[1] = 1.0f;
	vertex[4].color[2] = 0.0f;

	vertex[5].color[0] = 0.6f;
	vertex[5].color[1] = 1.0f;
	vertex[5].color[2] = 0.0f;

	vertex[6].color[0] = 0.1f;
	vertex[6].color[1] = 1.0f;
	vertex[6].color[2] = 0.0f;

	vertex[7].color[0] = 0.2f;
	vertex[7].color[1] = 1.0f;
	vertex[7].color[2] = 0.0f;

	triangles[0] = 3;   triangles[1] = 0;   triangles[2] = 1;
	triangles[3] = 1;   triangles[4] = 0;   triangles[5] = 2;

	/* Create a new VBO using VBO id */
	glGenBuffers(1, vbo);

	/* Bind the VBO */
	glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);

	/* Upload vertex data to GPU */
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * 36, vertex, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glGenBuffers(1, &index);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, index);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLubyte) * 36, triangles, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void Game::update()
{
	elapsed = clock.getElapsedTime();

	if (elapsed.asSeconds() >= 1.0f)

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		for (int i = 0; i < 8; i++)
		{
			cube[i] = Matrix3::RotationY(-.1) * cube[i];

		}
		vertex[0].coordinate[0] = (cube.at(0).x); //3
		vertex[0].coordinate[1] = (cube.at(0).y); //3
		vertex[0].coordinate[2] = (cube.at(0).z); //3

		vertex[1].coordinate[0] = (cube.at(1).x); //1
		vertex[1].coordinate[1] = (cube.at(1).y); //1
		vertex[1].coordinate[2] = (cube.at(1).z); //1

		vertex[2].coordinate[0] = (cube.at(2).x); //2
		vertex[2].coordinate[1] = (cube.at(2).y); //2
		vertex[2].coordinate[2] = (cube.at(2).z); //2

		vertex[3].coordinate[0] = (cube.at(3).x); //3
		vertex[3].coordinate[1] = (cube.at(3).y); //3
		vertex[3].coordinate[2] = (cube.at(3).z); //3

		vertex[4].coordinate[0] = (cube.at(4).x); //1
		vertex[4].coordinate[1] = (cube.at(4).y); //1
		vertex[4].coordinate[2] = (cube.at(4).z); //1

		vertex[5].coordinate[0] = (cube.at(5).x); //2
		vertex[5].coordinate[1] = (cube.at(5).y); //2
		vertex[5].coordinate[2] = (cube.at(5).z); //2

		vertex[6].coordinate[0] = (cube.at(6).x); //1
		vertex[6].coordinate[1] = (cube.at(6).y); //1
		vertex[6].coordinate[2] = (cube.at(6).z); //1

		vertex[7].coordinate[0] = (cube.at(7).x); //2
		vertex[7].coordinate[1] = (cube.at(7).y); //2
		vertex[7].coordinate[2] = (cube.at(7).z); //2
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		for (int i = 0; i < 8; i++)
		{
			cube[i] = Matrix3::RotationY(.1) * cube[i];

		}

		vertex[0].coordinate[0] = (cube.at(0).x); //3
		vertex[0].coordinate[1] = (cube.at(0).y); //3
		vertex[0].coordinate[2] = (cube.at(0).z); //3

		vertex[1].coordinate[0] = (cube.at(1).x); //1
		vertex[1].coordinate[1] = (cube.at(1).y); //1
		vertex[1].coordinate[2] = (cube.at(1).z); //1

		vertex[2].coordinate[0] = (cube.at(2).x); //2
		vertex[2].coordinate[1] = (cube.at(2).y); //2
		vertex[2].coordinate[2] = (cube.at(2).z); //2

		vertex[3].coordinate[0] = (cube.at(3).x); //3
		vertex[3].coordinate[1] = (cube.at(3).y); //3
		vertex[3].coordinate[2] = (cube.at(3).z); //3

		vertex[4].coordinate[0] = (cube.at(4).x); //1
		vertex[4].coordinate[1] = (cube.at(4).y); //1
		vertex[4].coordinate[2] = (cube.at(4).z); //1

		vertex[5].coordinate[0] = (cube.at(5).x); //2
		vertex[5].coordinate[1] = (cube.at(5).y); //2
		vertex[5].coordinate[2] = (cube.at(5).z); //2

		vertex[6].coordinate[0] = (cube.at(6).x); //1
		vertex[6].coordinate[1] = (cube.at(6).y); //1
		vertex[6].coordinate[2] = (cube.at(6).z); //1

		vertex[7].coordinate[0] = (cube.at(7).x); //2
		vertex[7].coordinate[1] = (cube.at(7).y); //2
		vertex[7].coordinate[2] = (cube.at(7).z); //2
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{
		for (int i = 0; i < 8; i++)
		{
			cube[i] = Matrix3::RotationX(-.1) * cube[i];

		}

		vertex[0].coordinate[0] = (cube.at(0).x); //3
		vertex[0].coordinate[1] = (cube.at(0).y); //3
		vertex[0].coordinate[2] = (cube.at(0).z); //3

		vertex[1].coordinate[0] = (cube.at(1).x); //1
		vertex[1].coordinate[1] = (cube.at(1).y); //1
		vertex[1].coordinate[2] = (cube.at(1).z); //1

		vertex[2].coordinate[0] = (cube.at(2).x); //2
		vertex[2].coordinate[1] = (cube.at(2).y); //2
		vertex[2].coordinate[2] = (cube.at(2).z); //2

		vertex[3].coordinate[0] = (cube.at(3).x); //3
		vertex[3].coordinate[1] = (cube.at(3).y); //3
		vertex[3].coordinate[2] = (cube.at(3).z); //3

		vertex[4].coordinate[0] = (cube.at(4).x); //1
		vertex[4].coordinate[1] = (cube.at(4).y); //1
		vertex[4].coordinate[2] = (cube.at(4).z); //1

		vertex[5].coordinate[0] = (cube.at(5).x); //2
		vertex[5].coordinate[1] = (cube.at(5).y); //2
		vertex[5].coordinate[2] = (cube.at(5).z); //2

		vertex[6].coordinate[0] = (cube.at(6).x); //1
		vertex[6].coordinate[1] = (cube.at(6).y); //1
		vertex[6].coordinate[2] = (cube.at(6).z); //1

		vertex[7].coordinate[0] = (cube.at(7).x); //2
		vertex[7].coordinate[1] = (cube.at(7).y); //2
		vertex[7].coordinate[2] = (cube.at(7).z); //2

	}


	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
		for (int i = 0; i < 8; i++)
		{
			cube[i] = Matrix3::RotationX(.1) * cube[i];

		}
		vertex[0].coordinate[0] = (cube.at(0).x); //3
		vertex[0].coordinate[1] = (cube.at(0).y); //3
		vertex[0].coordinate[2] = (cube.at(0).z); //3

		vertex[1].coordinate[0] = (cube.at(1).x); //1
		vertex[1].coordinate[1] = (cube.at(1).y); //1
		vertex[1].coordinate[2] = (cube.at(1).z); //1

		vertex[2].coordinate[0] = (cube.at(2).x); //2
		vertex[2].coordinate[1] = (cube.at(2).y); //2
		vertex[2].coordinate[2] = (cube.at(2).z); //2

		vertex[3].coordinate[0] = (cube.at(3).x); //3
		vertex[3].coordinate[1] = (cube.at(3).y); //3
		vertex[3].coordinate[2] = (cube.at(3).z); //3

		vertex[4].coordinate[0] = (cube.at(4).x); //1
		vertex[4].coordinate[1] = (cube.at(4).y); //1
		vertex[4].coordinate[2] = (cube.at(4).z); //1

		vertex[5].coordinate[0] = (cube.at(5).x); //2
		vertex[5].coordinate[1] = (cube.at(5).y); //2
		vertex[5].coordinate[2] = (cube.at(5).z); //2

		vertex[6].coordinate[0] = (cube.at(6).x); //1
		vertex[6].coordinate[1] = (cube.at(6).y); //1
		vertex[6].coordinate[2] = (cube.at(6).z); //1

		vertex[7].coordinate[0] = (cube.at(7).x); //2
		vertex[7].coordinate[1] = (cube.at(7).y); //2
		vertex[7].coordinate[2] = (cube.at(7).z); //2
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		std::cout << "Translate attempt forward" << std::endl;

		for (int i = 0; i < 8; i++)
		{
			cube[i] = Matrix3::Translate(-.01, 0) * cube[i];
		}
		vertex[0].coordinate[0] = (cube.at(0).x); //3
		vertex[0].coordinate[1] = (cube.at(0).y); //3
		vertex[0].coordinate[2] = (cube.at(0).z); //3

		vertex[1].coordinate[0] = (cube.at(1).x); //1
		vertex[1].coordinate[1] = (cube.at(1).y); //1
		vertex[1].coordinate[2] = (cube.at(1).z); //1

		vertex[2].coordinate[0] = (cube.at(2).x); //2
		vertex[2].coordinate[1] = (cube.at(2).y); //2
		vertex[2].coordinate[2] = (cube.at(2).z); //2

		vertex[3].coordinate[0] = (cube.at(3).x); //3
		vertex[3].coordinate[1] = (cube.at(3).y); //3
		vertex[3].coordinate[2] = (cube.at(3).z); //3

		vertex[4].coordinate[0] = (cube.at(4).x); //1
		vertex[4].coordinate[1] = (cube.at(4).y); //1
		vertex[4].coordinate[2] = (cube.at(4).z); //1

		vertex[5].coordinate[0] = (cube.at(5).x); //2
		vertex[5].coordinate[1] = (cube.at(5).y); //2
		vertex[5].coordinate[2] = (cube.at(5).z); //2

		vertex[6].coordinate[0] = (cube.at(6).x); //1
		vertex[6].coordinate[1] = (cube.at(6).y); //1
		vertex[6].coordinate[2] = (cube.at(6).z); //1

		vertex[7].coordinate[0] = (cube.at(7).x); //2
		vertex[7].coordinate[1] = (cube.at(7).y); //2
		vertex[7].coordinate[2] = (cube.at(7).z); //2
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		std::cout << "Translate attempt back" << std::endl;

		for (int i = 0; i < 8; i++)
		{
			cube[i] = Matrix3::Translate(.01, 0) * cube[i];

		}
		vertex[0].coordinate[0] = (cube.at(0).x); //3
		vertex[0].coordinate[1] = (cube.at(0).y); //3
		vertex[0].coordinate[2] = (cube.at(0).z); //3

		vertex[1].coordinate[0] = (cube.at(1).x); //1
		vertex[1].coordinate[1] = (cube.at(1).y); //1
		vertex[1].coordinate[2] = (cube.at(1).z); //1

		vertex[2].coordinate[0] = (cube.at(2).x); //2
		vertex[2].coordinate[1] = (cube.at(2).y); //2
		vertex[2].coordinate[2] = (cube.at(2).z); //2

		vertex[3].coordinate[0] = (cube.at(3).x); //3
		vertex[3].coordinate[1] = (cube.at(3).y); //3
		vertex[3].coordinate[2] = (cube.at(3).z); //3

		vertex[4].coordinate[0] = (cube.at(4).x); //1
		vertex[4].coordinate[1] = (cube.at(4).y); //1
		vertex[4].coordinate[2] = (cube.at(4).z); //1

		vertex[5].coordinate[0] = (cube.at(5).x); //2
		vertex[5].coordinate[1] = (cube.at(5).y); //2
		vertex[5].coordinate[2] = (cube.at(5).z); //2

		vertex[6].coordinate[0] = (cube.at(6).x); //1
		vertex[6].coordinate[1] = (cube.at(6).y); //1
		vertex[6].coordinate[2] = (cube.at(6).z); //1

		vertex[7].coordinate[0] = (cube.at(7).x); //2
		vertex[7].coordinate[1] = (cube.at(7).y); //2
		vertex[7].coordinate[2] = (cube.at(7).z); //2
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	{
		std::cout << "Scale attempt smol" << std::endl;

		for (int i = 0; i < 8; i++)
		{
			cube[i] = Matrix3::Scale(99, 99) * cube[i];

		}
		vertex[0].coordinate[0] = (cube.at(0).x); //3
		vertex[0].coordinate[1] = (cube.at(0).y); //3
		vertex[0].coordinate[2] = (cube.at(0).z); //3

		vertex[1].coordinate[0] = (cube.at(1).x); //1
		vertex[1].coordinate[1] = (cube.at(1).y); //1
		vertex[1].coordinate[2] = (cube.at(1).z); //1

		vertex[2].coordinate[0] = (cube.at(2).x); //2
		vertex[2].coordinate[1] = (cube.at(2).y); //2
		vertex[2].coordinate[2] = (cube.at(2).z); //2

		vertex[3].coordinate[0] = (cube.at(3).x); //3
		vertex[3].coordinate[1] = (cube.at(3).y); //3
		vertex[3].coordinate[2] = (cube.at(3).z); //3

		vertex[4].coordinate[0] = (cube.at(4).x); //1
		vertex[4].coordinate[1] = (cube.at(4).y); //1
		vertex[4].coordinate[2] = (cube.at(4).z); //1

		vertex[5].coordinate[0] = (cube.at(5).x); //2
		vertex[5].coordinate[1] = (cube.at(5).y); //2
		vertex[5].coordinate[2] = (cube.at(5).z); //2

		vertex[6].coordinate[0] = (cube.at(6).x); //1
		vertex[6].coordinate[1] = (cube.at(6).y); //1
		vertex[6].coordinate[2] = (cube.at(6).z); //1

		vertex[7].coordinate[0] = (cube.at(7).x); //2
		vertex[7].coordinate[1] = (cube.at(7).y); //2
		vertex[7].coordinate[2] = (cube.at(7).z); //2
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
		std::cout << "Scale attempt big" << std::endl;

		for (int i = 0; i < 8; i++)
		{
			cube[i] = Matrix3::Scale(101, 101) * cube[i];

		}
		vertex[0].coordinate[0] = (cube.at(0).x); //3
		vertex[0].coordinate[1] = (cube.at(0).y); //3
		vertex[0].coordinate[2] = (cube.at(0).z); //3

		vertex[1].coordinate[0] = (cube.at(1).x); //1
		vertex[1].coordinate[1] = (cube.at(1).y); //1
		vertex[1].coordinate[2] = (cube.at(1).z); //1

		vertex[2].coordinate[0] = (cube.at(2).x); //2
		vertex[2].coordinate[1] = (cube.at(2).y); //2
		vertex[2].coordinate[2] = (cube.at(2).z); //2

		vertex[3].coordinate[0] = (cube.at(3).x); //3
		vertex[3].coordinate[1] = (cube.at(3).y); //3
		vertex[3].coordinate[2] = (cube.at(3).z); //3

		vertex[4].coordinate[0] = (cube.at(4).x); //1
		vertex[4].coordinate[1] = (cube.at(4).y); //1
		vertex[4].coordinate[2] = (cube.at(4).z); //1

		vertex[5].coordinate[0] = (cube.at(5).x); //2
		vertex[5].coordinate[1] = (cube.at(5).y); //2
		vertex[5].coordinate[2] = (cube.at(5).z); //2

		vertex[6].coordinate[0] = (cube.at(6).x); //1
		vertex[6].coordinate[1] = (cube.at(6).y); //1
		vertex[6].coordinate[2] = (cube.at(6).z); //1

		vertex[7].coordinate[0] = (cube.at(7).x); //2
		vertex[7].coordinate[1] = (cube.at(7).y); //2
		vertex[7].coordinate[2] = (cube.at(7).z); //2
	}

	//cout << "Update up" << endl;

}

void Game::render()
{
	//cout << "Drawing" << endl;

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

	glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, index);

	/*	As the data positions will be updated by the this program on the
		CPU bind the updated data to the GPU for drawing	*/
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * 36, vertex, GL_STATIC_DRAW);

	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_COLOR_ARRAY);


	glColorPointer(3, GL_FLOAT, sizeof(Vertex), (char*)NULL + 12);

	/*	Draw Triangle from VBO	(set where to start from as VBO can contain 
		model compoents that are and are not to be drawn )	*/
	glVertexPointer(3, GL_FLOAT, sizeof(Vertex), (char*)NULL + 0);
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_BYTE, (char*)NULL + 0);

	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_COLOR_ARRAY);

	window.display();

}

void Game::unload()
{
	//cout << "Cleaning up" << endl;

	glDeleteBuffers(1, vbo);
}

