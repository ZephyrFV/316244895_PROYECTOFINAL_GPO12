#include <iostream>
#include <cmath>

// GLEW
#include <GL/glew.h>

// GLFW
#include <GLFW/glfw3.h>

// Other Libs
#include "stb_image.h"

// GLM Mathematics
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

//Load Models
#include "SOIL2/SOIL2.h"


// Other includes
#include "Shader.h"
#include "Camera.h"
#include "Model.h"

// Function prototypes
void KeyCallback(GLFWwindow *window, int key, int scancode, int action, int mode);
void MouseCallback(GLFWwindow *window, double xPos, double yPos);
void DoMovement();
void movimientos();
void animacionCarro();
void animacionBalon();

// Window dimensions
const GLuint WIDTH = 800, HEIGHT = 600;
int SCREEN_WIDTH, SCREEN_HEIGHT;

// Camera
Camera  camera(glm::vec3(00.0f, 2.0f, 0.0f));
GLfloat lastX = WIDTH / 2.0;
GLfloat lastY = HEIGHT / 2.0;
bool keys[1024];
bool firstMouse = true;
float range = 0.0f;
float rot = 0.0f;
// Light attributes
glm::vec3 lightPos(0.0f, 0.0f, 0.0f);
glm::vec3 PosIni(-95.0f, 0.0f, -45.0f);
bool active;

// Positions of the point lights
glm::vec3 pointLightPositions[] = {
	glm::vec3(0.7f,  200.2f,  2.0f),
	glm::vec3(2.3f,  200.0f, -4.0f),
	glm::vec3(-4.0f,  200.0f, -12.0f),
	glm::vec3(0.0f,  200.0f, -3.0f)
};

glm::vec3 LightP1;

//VARIABLES PARA LOS MOVIMIENTOS DE LAS ANIMACIONES
float movCajonesArriba = 0; //variable para movimiento de cajon de arriba
float movCajonesAbajo = 0; //variable para movimiento de cajon de abajo
float movSilla = 0; //variable para movimiento de la silla
float rotCaja = 0; //variable para la rotacion de la tapa de la caja de juguetes
float rotPuertaRopero = 0; //variable para rotacion de las puertas del ropero
float movCarroX = 61.784; //variable para movimiento del carro sobre eje X
float movCarroZ = 6.896;
float movCarroY = 0; //variable para movimiento del carro sobre eje Z
float rotCarroY = 90;
float rotCarroZ = 0;//variable para rotacion de carro sobre eje Y y simular movimiento
float movBalonY = 0; //variable para movimiento del balon sobre eje Y y hacer que rebote
float rotBalonZ =0;  //variable para rotacion del balon y simular que gira

//BANDERAS PARA ACTIVAR LAS ANIMACIONES
bool muebles = true; //Bandera para activar el control de los muebles ()
bool cajonesArriba = false; //Bandera para accionar la animacion del cajon de arriba
bool cajonesAbajo = false; //Bandera para accionar la animacion del cajon de abajo
bool cajonesArribaCerrados = true; //Bandera saber si los cajones de arriba estan cerrados
bool cajonesArribaAbiertos = false; //Bandera saber si los cajones de arriba estan abiertos
bool cajonesAbajoCerrados = true; //Bandera saber si los cajones de abajo estan cerrados
bool cajonesAbajoAbiertos = false; //Bandera saber si los cajones de abajo estan abiertos
bool silla = false; //Bandera para accionar la animacion de la silla
bool sillaSinMover = true; //Bandera para saber si la silla ya se movio o no
bool cajaJuguetes = false; //Bandera para activar la animacion de la caja de juguetes
bool cajaJuguetesCerrada = true; //bandera para saber si la caja de juguetes ya se abrio
bool ropero = false; //Bandera para accionar la animacion del ropero
bool roperoCerrado = true; //Bandera pasa saber si el ropero esta cerrado
bool recorridoCarro = false; //Bandera para accionar el recorrido del carro
bool recorridoCarro1 = true; //Bandera para cordinar el recorrido 1 del carro
bool recorridoCarro2 = false; //Bandera para cordinar el recorrido 2 del carro
bool recorridoCarro3 = false; //Bandera para cordinar el recorrido 3 del carro
bool recorridoCarro4 = false; //Bandera para cordinar el recorrido 4 del carro
bool recorridoCarro5 = false; //Bandera para cordinar el recorrido 5 del carro
bool recorridoCarro6 = false; //Bandera para cordinar el recorrido 6 del carro
bool recorridoCarro7 = false; //Bandera para cordinar el recorrido 1 del carro
bool recorridoCarro8 = false; //Bandera para cordinar el recorrido 2 del carro
bool recorridoCarro9 = false; //Bandera para cordinar el recorrido 3 del carro
bool recorridoCarro10 = false; //Bandera para cordinar el recorrido 4 del carro
bool recorridoCarro11 = false; //Bandera para cordinar el recorrido 5 del carro
bool recorridoCarro12 = false; //Bandera para cordinar el recorrido 6 del carro
bool recorridoCarro13 = false; //Bandera para cordinar el recorrido 4 del carro
bool recorridoCarro14 = false; //Bandera para cordinar el recorrido 5 del carro
bool recorridoCarro15 = false; //Bandera para cordinar el recorrido 6 del carro
bool recorridoCarro16 = false; //Bandera para cordinar el recorrido 4 del carro
bool recorridoCarro17 = false; //Bandera para cordinar el recorrido 5 del carro
bool recorridoCarro18 = false; //Bandera para cordinar el recorrido 6 del carro
bool recorridoCarro19 = false; //Bandera para cordinar el recorrido 4 del carro
bool recorridoCarro20 = false; //Bandera para cordinar el recorrido 5 del carro
bool recorridoCarro21 = false; //Bandera para cordinar el recorrido 6 del carro
bool recorridoCarro22 = false; //Bandera para cordinar el recorrido 5 del carro
bool recorridoCarro23 = false; //Bandera para cordinar el recorrido 6 del carro
bool recorridoCarro24 = false; //Bandera para cordinar el recorrido 5 del carro
bool recorridoCarro25 = false; //Bandera para cordinar el recorrido 6 del carro
bool recorridoCarro26 = false; //Bandera para cordinar el recorrido 5 del carro
bool recorridoCarro27 = false; //Bandera para cordinar el recorrido 6 del carro
bool recorridoCarro28 = false; //Bandera para cordinar el recorrido 6 del carro
bool recorridoCarro29 = false; //Bandera para cordinar el recorrido 5 del carro
bool recorridoCarro30 = false; //Bandera para cordinar el recorrido 6 del carro
bool recorridoCarro31 = false; //Bandera para cordinar el recorrido 6 del carro
bool recorridoCarro32 = false; //Bandera para cordinar el recorrido 6 del carro
bool recorridoCarro33 = false; //Bandera para cordinar el recorrido 6 del carro
bool recorridoCarro34 = false; //Bandera para cordinar el recorrido 6 del carro
bool recorridoCarro35 = false; //Bandera para cordinar el recorrido 6 del carro
bool recorridoCarro36 = false; //Bandera para cordinar el recorrido 6 del carro
bool recorridoCarro37 = false; //Bandera para cordinar el recorrido 6 del carro




bool recorridoBalon = false; //Bandera para activar el movimiento del balon
bool recorridoBalon1 = true; //Bandera para cordinar el recorrido 1 del balon
bool recorridoBalon2 = false;//Bandera para cordinar el recorrido 2 del balon
bool recorridoBalon3 = false;//Bandera para cordinar el recorrido 3 del balon
bool recorridoBalon4 = false;//Bandera para cordinar el recorrido 4 del balon
bool recorridoBalon5 = false;//Bandera para cordinar el recorrido 5 del balon
bool recorridoBalon6 = false;//Bandera para cordinar el recorrido 6 del balon


// Deltatime
GLfloat deltaTime = 0.0f;	// Time between current frame and last frame
GLfloat lastFrame = 0.0f;  	// Time of last frame

int main()
{
	// Init GLFW
	glfwInit();
	// Set all the required options for GLFW
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

	// Create a GLFWwindow object that we can use for GLFW's functions
	GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "Proyecto Final", nullptr, nullptr);

	if (nullptr == window)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();

		return EXIT_FAILURE;
	}

	glfwMakeContextCurrent(window);

	glfwGetFramebufferSize(window, &SCREEN_WIDTH, &SCREEN_HEIGHT);

	// Set the required callback functions
	glfwSetKeyCallback(window, KeyCallback);
	glfwSetCursorPosCallback(window, MouseCallback);
	printf("%f", glfwGetTime());

	// GLFW Options
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	// Set this to true so GLEW knows to use a modern approach to retrieving function pointers and extensions
	glewExperimental = GL_TRUE;
	// Initialize GLEW to setup the OpenGL Function pointers
	if (GLEW_OK != glewInit())
	{
		std::cout << "Failed to initialize GLEW" << std::endl;
		return EXIT_FAILURE;
	}

	// Define the viewport dimensions
	glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);

	// OpenGL options
	glEnable(GL_DEPTH_TEST);

	//CARGA DE OBJETOS A MODELAR
	Shader lightingShader("Shaders/lighting.vs", "Shaders/lighting.frag");
	Shader lampShader("Shaders/lamp.vs", "Shaders/lamp.frag");
	Model Casa((char*)"Models/Casa/Casa.obj");
	Model Bed((char*)"Models/Bed/Bed.obj");
	Model Mesa((char*)"Models/Mesa/Mesa.obj");
	Model Silla((char*)"Models/Silla/Silla.obj");
	Model CajaJuguetesTapa((char*)"Models/CajaJuguetes/CajaJuguetesTapa2.obj");
	Model CajaJuguetesCuerpo((char*)"Models/CajaJuguetes/CajaJuguetesCuerpo.obj");
	Model MuebleCajon((char*)"Models/Cajon/Mueble.obj");
	Model CajonArriba((char*)"Models/Cajon/Cajon_Arriba.obj");
	Model CajonAbajo((char*)"Models/Cajon/Cajon_Abajo.obj");
	Model Lampara((char*)"Models/Lampara/Lampara.obj");
	Model Carro((char*)"Models/Car/Carro2.obj");
	Model RoperoMueble((char*)"Models/Ropero/RoperoMueble.obj");
	Model RoperoPuertaIzquierda((char*)"Models/Ropero/RoperoPuertaIzquierda2.obj");
	Model RoperoPuertaDerecha((char*)"Models/Ropero/RoperoPuertaDerecha2.obj");
	Model Balon((char*)"Models/Balon/Balon.obj");
	Model Pista((char*)"Models/Pista/Race_Track.obj");
	Model CarroPista((char*)"Models/Pista/Carro2.obj");


	// Build and compile our shader program


	// Set up vertex data (and buffer(s)) and attribute pointers
	GLfloat vertices[] =
	{
		// Positions            // Normals              // Texture Coords
		-0.5f, -0.5f, -0.5f,    0.0f,  0.0f, -1.0f,     0.0f,  0.0f,
		0.5f, -0.5f, -0.5f,     0.0f,  0.0f, -1.0f,     1.0f,  0.0f,
		0.5f,  0.5f, -0.5f,     0.0f,  0.0f, -1.0f,     1.0f,  1.0f,
		0.5f,  0.5f, -0.5f,     0.0f,  0.0f, -1.0f,     1.0f,  1.0f,
		-0.5f,  0.5f, -0.5f,    0.0f,  0.0f, -1.0f,     0.0f,  1.0f,
		-0.5f, -0.5f, -0.5f,    0.0f,  0.0f, -1.0f,     0.0f,  0.0f,

		-0.5f, -0.5f,  0.5f,    0.0f,  0.0f,  1.0f,     0.0f,  0.0f,
		0.5f, -0.5f,  0.5f,     0.0f,  0.0f,  1.0f,     1.0f,  0.0f,
		0.5f,  0.5f,  0.5f,     0.0f,  0.0f,  1.0f,     1.0f,  1.0f,
		0.5f,  0.5f,  0.5f,     0.0f,  0.0f,  1.0f,  	1.0f,  1.0f,
		-0.5f,  0.5f,  0.5f,    0.0f,  0.0f,  1.0f,     0.0f,  1.0f,
		-0.5f, -0.5f,  0.5f,    0.0f,  0.0f,  1.0f,     0.0f,  0.0f,

		-0.5f,  0.5f,  0.5f,    -1.0f,  0.0f,  0.0f,    1.0f,  0.0f,
		-0.5f,  0.5f, -0.5f,    -1.0f,  0.0f,  0.0f,    1.0f,  1.0f,
		-0.5f, -0.5f, -0.5f,    -1.0f,  0.0f,  0.0f,    0.0f,  1.0f,
		-0.5f, -0.5f, -0.5f,    -1.0f,  0.0f,  0.0f,    0.0f,  1.0f,
		-0.5f, -0.5f,  0.5f,    -1.0f,  0.0f,  0.0f,    0.0f,  0.0f,
		-0.5f,  0.5f,  0.5f,    -1.0f,  0.0f,  0.0f,    1.0f,  0.0f,

		0.5f,  0.5f,  0.5f,     1.0f,  0.0f,  0.0f,     1.0f,  0.0f,
		0.5f,  0.5f, -0.5f,     1.0f,  0.0f,  0.0f,     1.0f,  1.0f,
		0.5f, -0.5f, -0.5f,     1.0f,  0.0f,  0.0f,     0.0f,  1.0f,
		0.5f, -0.5f, -0.5f,     1.0f,  0.0f,  0.0f,     0.0f,  1.0f,
		0.5f, -0.5f,  0.5f,     1.0f,  0.0f,  0.0f,     0.0f,  0.0f,
		0.5f,  0.5f,  0.5f,     1.0f,  0.0f,  0.0f,     1.0f,  0.0f,

		-0.5f, -0.5f, -0.5f,    0.0f, -1.0f,  0.0f,     0.0f,  1.0f,
		0.5f, -0.5f, -0.5f,     0.0f, -1.0f,  0.0f,     1.0f,  1.0f,
		0.5f, -0.5f,  0.5f,     0.0f, -1.0f,  0.0f,     1.0f,  0.0f,
		0.5f, -0.5f,  0.5f,     0.0f, -1.0f,  0.0f,     1.0f,  0.0f,
		-0.5f, -0.5f,  0.5f,    0.0f, -1.0f,  0.0f,     0.0f,  0.0f,
		-0.5f, -0.5f, -0.5f,    0.0f, -1.0f,  0.0f,     0.0f,  1.0f,

		-0.5f,  0.5f, -0.5f,    0.0f,  1.0f,  0.0f,     0.0f,  1.0f,
		0.5f,  0.5f, -0.5f,     0.0f,  1.0f,  0.0f,     1.0f,  1.0f,
		0.5f,  0.5f,  0.5f,     0.0f,  1.0f,  0.0f,     1.0f,  0.0f,
		0.5f,  0.5f,  0.5f,     0.0f,  1.0f,  0.0f,     1.0f,  0.0f,
		-0.5f,  0.5f,  0.5f,    0.0f,  1.0f,  0.0f,     0.0f,  0.0f,
		-0.5f,  0.5f, -0.5f,    0.0f,  1.0f,  0.0f,     0.0f,  1.0f
	};

	GLuint indices[] =
	{  // Note that we start from 0!
		0,1,2,3,
		4,5,6,7,
		8,9,10,11,
		12,13,14,15,
		16,17,18,19,
		20,21,22,23,
		24,25,26,27,
		28,29,30,31,
		32,33,34,35
	};

	// Positions all containers
	glm::vec3 cubePositions[] = {
		glm::vec3(0.0f,  0.0f,  0.0f),
		glm::vec3(2.0f,  5.0f, -15.0f),
		glm::vec3(-1.5f, -2.2f, -2.5f),
		glm::vec3(-3.8f, -2.0f, -12.3f),
		glm::vec3(2.4f, -0.4f, -3.5f),
		glm::vec3(-1.7f,  3.0f, -7.5f),
		glm::vec3(1.3f, -2.0f, -2.5f),
		glm::vec3(1.5f,  2.0f, -2.5f),
		glm::vec3(1.5f,  0.2f, -1.5f),
		glm::vec3(-1.3f,  1.0f, -1.5f)
	};


	// First, set the container's VAO (and VBO)
	GLuint VBO, VAO, EBO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// Position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid *)0);
	glEnableVertexAttribArray(0);
	// Normals attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid *)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);
	// Texture Coordinate attribute
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid *)(6 * sizeof(GLfloat)));
	glEnableVertexAttribArray(2);
	glBindVertexArray(0);

	// Then, we set the light's VAO (VBO stays the same. After all, the vertices are the same for the light object (also a 3D cube))
	GLuint lightVAO;
	glGenVertexArrays(1, &lightVAO);
	glBindVertexArray(lightVAO);
	// We only need to bind to the VBO (to link it with glVertexAttribPointer), no need to fill it; the VBO's data already contains all we need.
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	// Set the vertex attributes (only position data for the lamp))
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid *)0); // Note that we skip over the other data in our buffer object (we don't need the normals/textures, only positions).
	glEnableVertexAttribArray(0);
	glBindVertexArray(0);

	// Load textures
	GLuint texture1, texture2;
	glGenTextures(1, &texture1);
	glGenTextures(1, &texture2);

	int textureWidth, textureHeight, nrChannels;
	stbi_set_flip_vertically_on_load(true);
	unsigned char *image;
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST_MIPMAP_NEAREST);
	// Diffuse map
	image = stbi_load("images/TexturesCom_GravelCobble0019_7_S.jpg", &textureWidth, &textureHeight, &nrChannels, 0);
	glBindTexture(GL_TEXTURE_2D, texture1);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, textureWidth, textureHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
	glGenerateMipmap(GL_TEXTURE_2D);
	if (image)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, textureWidth, textureHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "Failed to load texture" << std::endl;
	}
	stbi_image_free(image);

	// Specular map
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST_MIPMAP_NEAREST);
	image = stbi_load("images/piso.jpg", &textureWidth, &textureHeight, &nrChannels, 0);
	glBindTexture(GL_TEXTURE_2D, texture2);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, textureWidth, textureHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
	glGenerateMipmap(GL_TEXTURE_2D);
	if (image)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, textureWidth, textureHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "Failed to load texture" << std::endl;
	}
	stbi_image_free(image);

	glBindTexture(GL_TEXTURE_2D, 0);

	// Set texture units
	lightingShader.Use();
	glUniform1i(glGetUniformLocation(lightingShader.Program, "material.diffuse"), 0);
	glUniform1i(glGetUniformLocation(lightingShader.Program, "material.specular"), 1);

	glm::mat4 projection = glm::perspective(camera.GetZoom(), (GLfloat)SCREEN_WIDTH / (GLfloat)SCREEN_HEIGHT, 0.1f, 1000.0f);

	// Game loop
	while (!glfwWindowShouldClose(window))
	{

		// Calculate deltatime of current frame
		GLfloat currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		// Check if any events have been activiated (key pressed, mouse moved etc.) and call corresponding response functions
		glfwPollEvents();
		DoMovement();
		movimientos();
		animacionCarro();
		animacionBalon();


		// Clear the colorbuffer
		glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		//Load Model


		// Use cooresponding shader when setting uniforms/drawing objects
		lightingShader.Use();
		GLint viewPosLoc = glGetUniformLocation(lightingShader.Program, "viewPos");
		glUniform3f(viewPosLoc, camera.GetPosition().x, camera.GetPosition().y, camera.GetPosition().z);
		// Set material properties
		glUniform1f(glGetUniformLocation(lightingShader.Program, "material.shininess"), 32.0f);
		// == ==========================
		// Here we set all the uniforms for the 5/6 types of lights we have. We have to set them manually and index
		// the proper PointLight struct in the array to set each uniform variable. This can be done more code-friendly
		// by defining light types as classes and set their values in there, or by using a more efficient uniform approach
		// by using 'Uniform buffer objects', but that is something we discuss in the 'Advanced GLSL' tutorial.
		// == ==========================
		// Directional light
		glUniform3f(glGetUniformLocation(lightingShader.Program, "dirLight.direction"), -0.2f, -1.0f, -0.3f);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "dirLight.ambient"), 0.5f, 0.5f, 0.5f);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "dirLight.diffuse"), 0.4f, 0.4f, 0.4f);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "dirLight.specular"), 0.4f, 0.4f, 0.4f);


		// Point light 1
		glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[0].position"), pointLightPositions[0].x, pointLightPositions[0].y, pointLightPositions[0].z);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[0].ambient"), 0.05f, 0.05f, 0.05f);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[0].diffuse"), LightP1.x, LightP1.y, LightP1.z);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[0].specular"), LightP1.x, LightP1.y, LightP1.z);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[0].constant"), 1.0f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[0].linear"), 0.09f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[0].quadratic"), 0.032f);



		// Point light 2
		glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[1].position"), pointLightPositions[1].x, pointLightPositions[1].y, pointLightPositions[1].z);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[1].ambient"), 0.05f, 0.05f, 0.05f);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[1].diffuse"), 1.0f, 1.0f, 0.0f);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[1].specular"), 1.0f, 1.0f, 0.0f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[1].constant"), 1.0f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[1].linear"), 0.09f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[1].quadratic"), 0.032f);

		// Point light 3
		glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[2].position"), pointLightPositions[2].x, pointLightPositions[2].y, pointLightPositions[2].z);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[2].ambient"), 0.05f, 0.05f, 0.05f);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[2].diffuse"), 0.0f, 1.0f, 1.0f);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[2].specular"), 0.0f, 1.0f, 1.0f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[2].constant"), 1.0f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[2].linear"), 0.09f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[2].quadratic"), 0.032f);

		// Point light 4
		glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[3].position"), pointLightPositions[3].x, pointLightPositions[3].y, pointLightPositions[3].z);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[3].ambient"), 0.05f, 0.05f, 0.05f);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[3].diffuse"), 1.0f, 0.0f, 1.0f);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[3].specular"), 1.0f, 0.0f, 1.0f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[3].constant"), 1.0f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[3].linear"), 0.09f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[3].quadratic"), 0.032f);

		// SpotLight
		glUniform3f(glGetUniformLocation(lightingShader.Program, "spotLight.position"), camera.GetPosition().x, camera.GetPosition().y, camera.GetPosition().z);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "spotLight.direction"), camera.GetFront().x, camera.GetFront().y, camera.GetFront().z);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "spotLight.ambient"), 0.0f, 0.0f, 0.0f);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "spotLight.diffuse"), 0.0f, 0.0f, 0.0f);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "spotLight.specular"), 0.0f, 0.0f, 0.0f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "spotLight.constant"), 1.0f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "spotLight.linear"), 0.09f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "spotLight.quadratic"), 0.032f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "spotLight.cutOff"), glm::cos(glm::radians(12.5f)));
		glUniform1f(glGetUniformLocation(lightingShader.Program, "spotLight.outerCutOff"), glm::cos(glm::radians(15.0f)));

		// Set material properties
		glUniform1f(glGetUniformLocation(lightingShader.Program, "material.shininess"), 16.0f);

		// Create camera transformations
		glm::mat4 view;
		view = camera.GetViewMatrix();

		// Get the uniform locations
		GLint modelLoc = glGetUniformLocation(lightingShader.Program, "model");
		GLint viewLoc = glGetUniformLocation(lightingShader.Program, "view");
		GLint projLoc = glGetUniformLocation(lightingShader.Program, "projection");

		// Pass the matrices to the shader
		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
		glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));

		glBindVertexArray(VAO);
		glm::mat4 model(1);
		
		//DIBUJO DE OBJETOS
		//CASA
		view = camera.GetViewMatrix();
		model = glm::mat4(1);
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		//Casa.Draw(lightingShader);

		//CAMA
		view = camera.GetViewMatrix();
		model = glm::mat4(1);
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		//Bed.Draw(lightingShader);

		//MESA
		view = camera.GetViewMatrix();
		model = glm::mat4(1);
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		//Mesa.Draw(lightingShader);

		//SILLA
		view = camera.GetViewMatrix();
		model = glm::mat4(1);
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, movSilla));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		//Silla.Draw(lightingShader);

		//TAPA DE CAJA DE JUGUETES
		view = camera.GetViewMatrix();
		model = glm::mat4(1);
		model = glm::translate(model, glm::vec3(-2.074f, 2.683f, 0.949));
		model = glm::rotate(model, glm::radians(rotCaja), glm::vec3(0.0f, 0.0f, 1.0));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		//CajaJuguetesTapa.Draw(lightingShader);

		//CAJA DE JUGUETES
		view = camera.GetViewMatrix();
		model = glm::mat4(1);
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		//CajaJuguetesCuerpo.Draw(lightingShader);

		//MUEBLE DE LOS CAJONES
		view = camera.GetViewMatrix();
		model = glm::mat4(1);
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		//MuebleCajon.Draw(lightingShader);

		//CAJONES DE ARRIBA
		view = camera.GetViewMatrix();
		model = glm::mat4(1);
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, -movCajonesArriba));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		//CajonArriba.Draw(lightingShader);

		//CAJONES DE ABAJO
		view = camera.GetViewMatrix();
		model = glm::mat4(1);
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, -movCajonesAbajo));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		//CajonAbajo.Draw(lightingShader);

		//LAMPARA
		view = camera.GetViewMatrix();
		model = glm::mat4(1);
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		//Lampara.Draw(lightingShader);

		//CARRO
		view = camera.GetViewMatrix();
		model = glm::mat4(1);
		model = glm::translate(model, glm::vec3(8.816, 0.0f, -4.332f));
		model = glm::translate(model, glm::vec3(movCarroX, 0.0f, movCarroZ));
		model = glm::rotate(model, glm::radians(-rotCarroY), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		//Carro.Draw(lightingShader);

		//MUEBLE DE ROPERO
		view = camera.GetViewMatrix();
		model = glm::mat4(1);
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		//RoperoMueble.Draw(lightingShader);

		//PUERTA IZQUIERDA DE ROPERO
		view = camera.GetViewMatrix();
		model = glm::mat4(1);
		model = glm::translate(model, glm::vec3(-0.592f, 3.224f, 1.864));
		model = glm::rotate(model, glm::radians(-rotPuertaRopero), glm::vec3(0.0f, 1.0f, 0.0));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		//RoperoPuertaIzquierda.Draw(lightingShader);

		//PUERTA DERECHA DE ROPERO
		view = camera.GetViewMatrix();
		model = glm::mat4(1);
		model = glm::translate(model, glm::vec3(-1.396f, 3.016f, 1.87));
		model = glm::rotate(model, glm::radians(rotPuertaRopero), glm::vec3(0.0f, 1.0f, 0.0));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		//RoperoPuertaDerecha.Draw(lightingShader);

		//BALON
		view = camera.GetViewMatrix();
		model = glm::mat4(1);
		model = glm::translate(model, glm::vec3(-0.976f, 2.57f, -1.331f));
		model = glm::translate(model, glm::vec3(0.0f, movBalonY, 0.0f));
		model = glm::rotate(model, glm::radians(rotBalonZ), glm::vec3(0.0f, 0.0f, 1.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		//Balon.Draw(lightingShader);

		//CARRO
		view = camera.GetViewMatrix();
		model = glm::mat4(1);
		//CORDENADAS BASE
		//model = glm::translate(model, glm::vec3(61.784f, 0.0f, 6.896f));
		//model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::translate(model, glm::vec3(movCarroX, movCarroY, movCarroZ));
		model = glm::rotate(model, glm::radians(-rotCarroY), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::rotate(model, glm::radians(-rotCarroZ), glm::vec3(0.0f, 0.0f, 0.1f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		CarroPista.Draw(lightingShader);

		view = camera.GetViewMatrix();
		model = glm::mat4(1);
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		Pista.Draw(lightingShader);

				
		glBindVertexArray(0);


		// Also draw the lamp object, again binding the appropriate shader
		lampShader.Use();
		// Get location objects for the matrices on the lamp shader (these could be different on a different shader)
		modelLoc = glGetUniformLocation(lampShader.Program, "model");
		viewLoc = glGetUniformLocation(lampShader.Program, "view");
		projLoc = glGetUniformLocation(lampShader.Program, "projection");

		// Set matrices
		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
		glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));
		model = glm::mat4(1);
		model = glm::translate(model, lightPos);
		//model = glm::scale(model, glm::vec3(0.2f)); // Make it a smaller cube
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		// Draw the light object (using light's vertex attributes)
		glBindVertexArray(lightVAO);
		for (GLuint i = 0; i < 4; i++)
		{
			model = glm::mat4(1);
			model = glm::translate(model, pointLightPositions[i]);
			model = glm::scale(model, glm::vec3(0.2f)); // Make it a smaller cube
			glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
			glDrawArrays(GL_TRIANGLES, 0, 36);
		}
		glBindVertexArray(0);



		// Swap the screen buffers
		glfwSwapBuffers(window);
	}




	glDeleteVertexArrays(1, &VAO);
	glDeleteVertexArrays(1, &lightVAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);
	// Terminate GLFW, clearing any resources allocated by GLFW.
	glfwTerminate();




	return 0;
}

// Moves/alters the camera positions based on user input
void DoMovement()
{
	if (keys[GLFW_KEY_1]) //Mueve cajones de arriba
	{
		cajonesArriba = true ;
	}

	if (keys[GLFW_KEY_2]) //Mueve Cajones de abajo
	{
		cajonesAbajo = true;
	}

	if (keys[GLFW_KEY_3]) //Mueve la silla
	{
		silla = true;
	}

	if (keys[GLFW_KEY_4]) //Abre la caja de juguetes
	{
		cajaJuguetes = true;
	}

	if (keys[GLFW_KEY_5]) //Abre el ropero
	{
		ropero = true;
	}

	if (keys[GLFW_KEY_6]) //Mueve el carro
	{
		recorridoCarro = true;
	}

	if (keys[GLFW_KEY_7]) //Mueve el balon
	{
		recorridoBalon = true;
	}

	// Camera controls
	if (keys[GLFW_KEY_W] || keys[GLFW_KEY_UP])
	{
		camera.ProcessKeyboard(FORWARD, deltaTime);

	}

	if (keys[GLFW_KEY_S] || keys[GLFW_KEY_DOWN])
	{
		camera.ProcessKeyboard(BACKWARD, deltaTime);


	}

	if (keys[GLFW_KEY_A] || keys[GLFW_KEY_LEFT])
	{
		camera.ProcessKeyboard(LEFT, deltaTime);


	}

	if (keys[GLFW_KEY_D] || keys[GLFW_KEY_RIGHT])
	{
		camera.ProcessKeyboard(RIGHT, deltaTime);
	}

}
//Animacion para todos los objetos
void movimientos()
{
	if (muebles)
	{
		//Codigo implementado para mover los cajones de arriba
		if (cajonesArriba) //si se apreta tecla para usar cajones
		{
			if (cajonesArribaCerrados && cajonesArriba) //si los cajones estan cerrados entran a este if (cajonesCerrados = true)
			{
				movCajonesArriba += 0.001f;
				if (movCajonesArriba > 0.1 )
				{
					cajonesArribaCerrados = false; //se quitan la bandera de cajones cerrados indicando que estan abiertos
					cajonesArribaAbiertos = true; //se activa la bandera de cajones abiertos indicando que estan abiertos
					cajonesArriba = false; //se quita la bandera de interaccion con cajones para que se tenga que pulsar nuevamente la tecla
				}
			}


			if (cajonesArribaAbiertos && cajonesArriba) //si los cajones estan abiertos entran a este if (cajonesAbiertos = true)
			{
				movCajonesArriba -= 0.001f;
				if (movCajonesArriba < 0)
				{
					cajonesArribaCerrados = true; //se activa la bandera de cajones cerrados indicando que ya se cerraron
					cajonesArribaAbiertos = false; //se quita la bandera de cajones abiertos indicando que se cerraron
					cajonesArriba = false; //se quita la bandera de interaccion con cajones para que se tenga que pulsar nuevamente la tecla
				}
			}
		}


		//Codigo Implementado para mover los cajones de abajo
		if (cajonesAbajo) //si se apreta tecla para usar cajones
		{
			if (cajonesAbajoCerrados && cajonesAbajo) //si los cajones estan cerrados entran a este if (cajonesAbajoCerrados = true)
			{
				movCajonesAbajo += 0.001f;
				if (movCajonesAbajo > 0.1)
				{
					cajonesAbajoCerrados = false; //se quitan la bandera de cajones cerrados indicando que estan abiertos
					cajonesAbajoAbiertos = true; //se activa la bandera de cajones abiertos indicando que estan abiertos
					cajonesAbajo = false; //se quita la bandera de interaccion con cajones para que se tenga que pulsar nuevamente la tecla
				}
			}


			if (cajonesAbajoAbiertos && cajonesAbajo) //si los cajones estan abiertos entran a este if (cajonesAbajoAbiertos = true)
			{
				movCajonesAbajo -= 0.001f;
				if (movCajonesAbajo < 0)
				{
					cajonesAbajoCerrados = true; //se activa la bandera de cajones cerrados indicando que ya se cerraron
					cajonesAbajoAbiertos = false; //se quita la bandera de cajones abiertos indicando que se cerraron
					cajonesAbajo = false; //se quita la bandera de interaccion con cajones para que se tenga que pulsar nuevamente la tecla
				}
			}
		}


		if (silla) //si se apreta tecla para usar la silla
		{
			if (sillaSinMover) //si la silla aun no se ha movido (sillaSinMover = true)
			{
				movSilla += 0.001f;
				if (movSilla > 0.3f)
				{
					sillaSinMover = false; //se quita la bandera de "sillaSinMover" indicando que ya se movio 
					silla = false; //se quita la bandera de interaccion con la silla para que se tenga que pulsar nuevamente la tecla 3
				}
			}
			else
			{
				movSilla -= 0.001f;
				if (movSilla < 0)
				{
					sillaSinMover = true; //se pone la bandera de "sillaSinMover" indicando que ya se regreso a su estado original
					silla = false; //se quita la bandera de interaccion con la silla para que se tenga que pulsar nuevamente la tecla 3
				}
			}
		}




		if (cajaJuguetes) //si se apreta tecla para abrir la caja (cajaJuguetes=True)
		{
			if (cajaJuguetesCerrada) //si la caja esta cerrada entonces entra a este ciclo (cajaJuguetesCerrada)
			{
				rotCaja += 0.2f;
				if (rotCaja > 90)
				{
					cajaJuguetesCerrada = false; //se quita la bandera de cajaJugeutesCerrada indicando que ya no esta cerrada "cajaJuguetesCerrada=false;
					cajaJuguetes = false; //se quita la bandera de interaccion con la caja para que se tenga que pulsar nuevamente la tecla 4
				}
			}
			else
			{
				rotCaja -= 0.2f;
				if (rotCaja < 0)
				{
					cajaJuguetesCerrada = true; //se pone la bandera en tru (cajaJuguetesCerrada= true) para indicar que ya se cerro
					cajaJuguetes = false; //se quita la bandera de interaccion con la caja para que se tenga que pulsar nuevamente la tecla 4
				}
			}
		}

		if (ropero) //si se apreta tecla para abrir las puertas del ropero (ropero=true)
		{
			if (roperoCerrado) //si el ropero esta cerrado entonces entra a este ciclo (roperoCerrado=true)
			{
				rotPuertaRopero += 0.2f;
				if (rotPuertaRopero > 90)
				{
					roperoCerrado = false; //se quita la bandera de roperoCerradp indicando que ya no esta cerrada roperoCerrado=false;
					ropero = false; //se quita la bandera de interaccion con el ropero para que se tenga que pulsar nuevamente la tecla 5
				}
			}
			else
			{
				rotPuertaRopero -= 0.2f;
				if (rotPuertaRopero < 0)
				{
					roperoCerrado = true; //se pone la bandera de roperoCerradp indicando que ya esta cerrada roperoCerrado=True;
					ropero = false; //se quita la bandera de interaccion con el ropero para que se tenga que pulsar nuevamente la tecla 5
				}
			}
		}


	}
}

//Animacion compleja para carro
void animacionCarro()
{
	if (recorridoCarro)
	{
		if (recorridoCarro1)
		{
			movCarroZ += 0.02;
			if (movCarroZ > 42)
			{
				recorridoCarro1 = false;
				recorridoCarro2 = true;
			}
		}

		if (recorridoCarro2)
		{
			movCarroX -= 0.02;
			movCarroZ += 0.02;
			rotCarroY += 0.3;
			if (rotCarroY >180 )
			{
				recorridoCarro2 = false;
				recorridoCarro3 = true;
			}
		}

		if (recorridoCarro3)
		{
			movCarroX -= 0.02;
			if (movCarroX < 6)
			{
				recorridoCarro3 = false;
				recorridoCarro4 = true;
			}
		}

		if (recorridoCarro4)
		{
			movCarroX -= 0.02;
			movCarroY += 0.01;
			rotCarroZ -= 0.2;
			if (rotCarroZ < -34)
			{
				recorridoCarro4 = false;
				recorridoCarro5 = true;
				
			}
		}

		if (recorridoCarro5)
		{
			movCarroX -= 0.02;
			movCarroY += 0.01;
			if (movCarroX < -8)
			{
				recorridoCarro5 = false;
				recorridoCarro6 = true;
			}
		}


		if (recorridoCarro6)
		{
			movCarroX -= 0.02;
			movCarroY -= 0.01;
			rotCarroZ += 0.2;
			if (rotCarroZ >34 )
			{
				recorridoCarro6 = false;
				recorridoCarro7 = true;
			}
		}

		if (recorridoCarro7)
		{
			movCarroX -= 0.02;
			movCarroY -= 0.01;
			rotCarroZ -= 0.2;
			if (rotCarroZ < 0)
			{
				recorridoCarro7 = false;
				recorridoCarro8 = true;
			}
		}

		if (recorridoCarro8)
		{
			movCarroX -= 0.02;
			movCarroY -= 0.01;
			if (movCarroY < 0)
			{
				recorridoCarro8 = false;
				recorridoCarro9 = true;
			}
		}
		if (recorridoCarro9)
		{
			movCarroX -= 0.02;
			if (movCarroX < -38)
			{
				recorridoCarro9 = false;
				recorridoCarro10 = true;
			}
		}
		if (recorridoCarro10)
		{
			movCarroX -= 0.02;
			movCarroZ += 0.02;
			rotCarroY -= 0.18;
			if (rotCarroY < 90)
			{
				recorridoCarro10 = false;
				recorridoCarro11 = true;
			}
		}

		if (recorridoCarro11)
		{
			movCarroX += 0.02;
			movCarroZ += 0.02;
			rotCarroY -= 0.18;
			if (rotCarroY < 0)
			{
				recorridoCarro11 = false;
				recorridoCarro12 = true;
			}
		}

		if (recorridoCarro12)
		{
			movCarroX += 0.02;
			if (movCarroX > -17)
			{
				recorridoCarro12 = false;
				recorridoCarro13 = true;
			}
		}

		if (recorridoCarro13)
		{
			movCarroX += 0.02;
			movCarroZ -= 0.02;
			rotCarroY -= 0.18;
			if (rotCarroY < -90)
			{
				recorridoCarro13 = false;
				recorridoCarro14 = true;
			}
		}

		if (recorridoCarro14)
		{
			movCarroZ -= 0.02;
			if (movCarroZ < 5)
			{
				recorridoCarro14 = false;
				recorridoCarro15 = true;
			}
		}

		if (recorridoCarro15)
		{
			movCarroX += 0.02;
			movCarroZ -= 0.02;
			rotCarroY += 0.2;
			if (rotCarroY > 0)
			{
				recorridoCarro15 = false;
				recorridoCarro16 = true;
			}
		}

		if (recorridoCarro16)
		{
			movCarroX += 0.02;
			if (movCarroX > 17)
			{
				recorridoCarro16 = false;
				recorridoCarro17 = true;
			}
		}

		if (recorridoCarro17)
		{
			movCarroX += 0.02;
			movCarroZ += 0.02;
			rotCarroY += 0.18;
			if (rotCarroY > 90)
			{
				recorridoCarro17 = false;
				recorridoCarro18 = true;
			}
		}

		if (recorridoCarro18)
		{
			movCarroX -= 0.02;
			movCarroZ += 0.02;
			rotCarroY += 0.18;
			if (rotCarroY > 180)
			{
				recorridoCarro18 = false;
				recorridoCarro19 = true;
			}
		}
		if (recorridoCarro19)
		{
			movCarroX -= 0.02;
			movCarroY += 0.004;
			rotCarroZ -= 0.08;
			if (rotCarroZ < -34)
			{
				recorridoCarro19 = false;
				recorridoCarro20 = true;

			}
		}

		if (recorridoCarro20)
		{
			movCarroX -= 0.02;
			movCarroY += 0.012;
			rotCarroZ += 0.04;
			if (rotCarroZ > 0)
			{
				recorridoCarro20 = false;
				recorridoCarro21 = true;

			}
		}

		if (recorridoCarro21)
		{
			movCarroX -= 0.02;
			movCarroY -= 0.011;
			rotCarroZ += 0.04;
			if (rotCarroZ > 34)
			{
				recorridoCarro21 = false;
				recorridoCarro22 = true;

			}
		}

		if (recorridoCarro22)
		{
			movCarroX -= 0.02;
			movCarroY -= 0.0052;
			rotCarroZ -= 0.08;
			if (rotCarroZ < 0)
			{
				recorridoCarro22 = false;
				recorridoCarro23 = true;

			}
		}

		if (recorridoCarro23)
		{
			movCarroX -= 0.02;
			movCarroY = 0;
			if (movCarroX < -70)
			{
				recorridoCarro23 = false;
				recorridoCarro24 = true;

			}
		}

		if (recorridoCarro24)
		{
			movCarroX -= 0.02;
			movCarroZ -= 0.02;
			rotCarroY += 0.18;
			if (rotCarroY > 270)
			{
				recorridoCarro24 = false;
				recorridoCarro25 = true;
			}
		}

		if (recorridoCarro25)
		{
			movCarroZ -= 0.02;
			if (movCarroZ < -40)
			{
				recorridoCarro25 = false;
				recorridoCarro26 = true;
			}
		}

		if (recorridoCarro26)
		{
			movCarroX += 0.02;
			movCarroZ -= 0.02;
			rotCarroY += 0.18;
			if (rotCarroY > 360)
			{
				recorridoCarro26 = false;
				recorridoCarro27 = true;
			}
		}

		if (recorridoCarro27)
		{
			movCarroX += 0.02;
			if (movCarroX > -6)
			{
				recorridoCarro27 = false;
				recorridoCarro28 = true;
				rotCarroY = 0;
			}
		}

		if (recorridoCarro28)
		{
			movCarroX += 0.02;
			movCarroZ -= 0.02;
			rotCarroY -= 0.18;
			if (rotCarroY < -90)
			{
				recorridoCarro28 = false;
				recorridoCarro29 = true;
			}
		}


		if (recorridoCarro29)
		{
			movCarroX += 0.02;
			movCarroZ -= 0.02;
			rotCarroY += 0.18;
			if (rotCarroY > 0)
			{
				recorridoCarro29 = false;
				recorridoCarro30 = true;
			}
		}

		if (recorridoCarro30)
		{
			movCarroX += 0.02;
			if (movCarroX > 70)
			{
				recorridoCarro30 = false;
				recorridoCarro31 = true;
			}
		}

		if (recorridoCarro31)
		{
			movCarroX += 0.02;
			movCarroZ += 0.02;
			rotCarroY += 0.18;
			if (rotCarroY > 90)
			{
				recorridoCarro31 = false;
				recorridoCarro32 = true;
			}
		}

		if (recorridoCarro32)
		{
			movCarroZ += 0.02;
			if (movCarroZ > -45)
			{
				recorridoCarro32 = false;
				recorridoCarro33 = true;
			}
		}
		if (recorridoCarro33)
		{
			movCarroX -= 0.02;
			movCarroZ += 0.02;
			rotCarroY += 0.22;
			if (rotCarroY > 180)
			{
				recorridoCarro33 = false;
				recorridoCarro34 = true;
			}
		}

		if (recorridoCarro34)
		{
			movCarroX -= 0.02;
			movCarroZ += 0.02;
			rotCarroY -= 0.18;
			if (rotCarroY < 90)
			{
				recorridoCarro34 = false;
				recorridoCarro35 = true;
			}
		}

		if (recorridoCarro35)
		{	
			movCarroX = 61.784;
			movCarroZ += 0.02;
			if (movCarroZ > 6.896)
			{
				recorridoCarro35 = false;
				recorridoCarro1 = true;
			}
		}
	}
}

//Animacion compleja para el balon
void animacionBalon()
{
	if (recorridoBalon)
	{
		if (recorridoBalon1)
		{
			movBalonY += 0.0035;
			rotBalonZ += 1;
			if (movBalonY > 0.8)
			{
				recorridoBalon1 = false;
				recorridoBalon2 = true;
			}
		}
	

		if (recorridoBalon2)
		{
			movBalonY -= 0.005;
			rotBalonZ += 1;
			if (movBalonY < 0)
			{
				recorridoBalon2 = false;
				recorridoBalon3 = true;
			}
		}

		if (recorridoBalon3)
		{
			movBalonY += 0.002;
			rotBalonZ += 1;
			if (movBalonY > 0.6)
			{
				recorridoBalon3 = false;
				recorridoBalon4 = true;
			}
		}


		if (recorridoBalon4)
		{
			movBalonY -= 0.005;
			rotBalonZ += 1;
			if (movBalonY < 0)
			{
				recorridoBalon4 = false;
				recorridoBalon5 = true;
			}
		}

		if (recorridoBalon5)
		{
			movBalonY += 0.001;
			rotBalonZ += 1;
			if (movBalonY > 0.2)
			{
				recorridoBalon5 = false;
				recorridoBalon6 = true;
			}
		}


		if (recorridoBalon6)
		{
			movBalonY -= 0.002;
			rotBalonZ += 1;
			if (movBalonY < 0)
			{
				recorridoBalon6 = false;
				recorridoBalon1 = true;
				recorridoBalon = false;
			}
		}
	}
}


// Is called whenever a key is pressed/released via GLFW
void KeyCallback(GLFWwindow *window, int key, int scancode, int action, int mode)
{



	if (GLFW_KEY_ESCAPE == key && GLFW_PRESS == action)
	{
		glfwSetWindowShouldClose(window, GL_TRUE);
	}

	if (key >= 0 && key < 1024)
	{
		if (action == GLFW_PRESS)
		{
			keys[key] = true;
		}
		else if (action == GLFW_RELEASE)
		{
			keys[key] = false;
		}
	}

	if (keys[GLFW_KEY_SPACE])
	{
		active = !active;
		if (active)
			LightP1 = glm::vec3(1.0f, 0.0f, 0.0f);
		else
			LightP1 = glm::vec3(0.0f, 0.0f, 0.0f);
	}


}

void MouseCallback(GLFWwindow *window, double xPos, double yPos)
{

	if (firstMouse)
	{
		lastX = xPos;
		lastY = yPos;
		firstMouse = false;
	}

	GLfloat xOffset = xPos - lastX;
	GLfloat yOffset = lastY - yPos;  // Reversed since y-coordinates go from bottom to left

	lastX = xPos;
	lastY = yPos;

	camera.ProcessMouseMovement(xOffset, yOffset);
}

