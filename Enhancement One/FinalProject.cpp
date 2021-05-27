/*
 * FinalProject.cpp
 *
 * 
 * 
 */


#include <iostream>			// Includes C++ I/O stream
#include <GL/glew.h>		// Includes glew header
#include <GL/freeglut.h>	// Includes freeglut header
#include "SOIL2/SOIL2.h"

/* GLM Math Header Inclusions */
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

using namespace std; 		// Uses standard namespace

#define WINDOW_TITLE "Final Project" // Macro for window title

// Vertex and Fragment Shader Source Macro
#ifndef GLSL
#define GLSL(Version, Source) "#version " #Version "\n" #Source
#endif

/* Variable declarations */
GLint pyramidShaderProgram, WindowWidth = 800, WindowHeight = 600;
GLuint VBO, EBO, texture, PyramidVAO, LightVAO;

/* Object Parameters */
glm::vec3 pyramidPosition(0.0f, 0.0f, 0.f);
glm::vec3 pyramidScale(2.0f);
glm::vec3 objectColor(1.0f, 1.0f, 1.0f);

/* Key Light Parameters */
glm::vec3 keyLightColor(1.0f, 1.0f, 1.0f);
glm::vec3 keyLightPosition(-5.0f, 4.0f, -5.0f);
glm::vec3 keyLightScale(1.0f);

/* Fill Light Parameters */
glm::vec3 fillLightColor(0.5f, 0.5f, 0.7f);
glm::vec3 fillLightPosition(5.0f, 2.0f, 5.0f);
glm::vec3 fillLightScale(0.1f);

/* Camera Control */
GLchar currentKey;
GLfloat cameraSpeed = 0.050f;
GLfloat zoomSpeed = 0.100f;
GLfloat lastMouseX = 400, lastMouseY = 300;
GLfloat mouseXOffset, mouseYOffset, yaw = 0.0f, pitch = 0.0f;
GLfloat sensitivity = 0.005f;
bool mouseDetected = true;
bool orbit = false;
bool zoom = false;
bool perspective = false;

/* Global vector Declarations */
glm::vec3 cameraPosition = glm::vec3(0.5f, 2.0f, -10.0f);
glm::vec3 CameraUpY = glm::vec3(0.0f, 1.0f, 0.0f);
glm::vec3 CameraForwardZ = glm::vec3(0.0f, 0.0f, -1.0f);
glm::vec3 front = glm::vec3(0.0f, -2.0f, 10.0f);

/* Function prototypes */
void UResizeWindow(int, int);
void URenderGraphics(void);
void UCreateShader(void);
void UCreateBuffers(void);

/* Camera Controls */
void UKeyboard(unsigned char key, int x, int y);
void UKeyReleased(unsigned char ey, int x, int y);
void UMouseClick(int button, int state, int x, int y);
void UMousePressedMove(int x, int y);

/* Texturing */
void UGenerateTexture(void);

/* Vertex Shader Program Source Code */
const GLchar * pyramidVertexShaderSource = GLSL(330,
	in layout(location=0) vec3 position; 			// Vertex Coordinates
	in layout(location=1) vec3 normal;				// Normal Coordinates
	in layout(location=2) vec2 textureCoordinates;	// Texture Coordinates

	out vec3 Normal;					// Transfers data to fragment shader
	out vec3 FragmentPos;
	out vec2 mobileTextureCoordinate;

	uniform mat4 model;					// Matrices used to transform vertex data
	uniform mat4 view;
	uniform mat4 projection;

		void main() {
			// Transforms vertex data
			gl_Position = projection * view * model * vec4(position, 1.0f);
			// Gets fragment / pixel position in world space
			FragmentPos = vec3(model * vec4(position, 1.0f));
			// Get normal vectors in world space only
			Normal = mat3(transpose(inverse(model))) * normal;
			// Combine texture coordinates into one vector
			mobileTextureCoordinate = vec2(textureCoordinates.x, 1.0f - textureCoordinates.y);
		}
);

/* Fragment Shader Program Source Code */
const GLchar * pyramidFragmentShaderSource = GLSL(330,
		// Receive values from Vertex Shader
		in vec3 Normal;
		in vec3 FragmentPos;
		in vec2 mobileTextureCoordinate;

		out vec4 pyramidColor;	// Sends data to GPU

		uniform sampler2D uTexture; // For textures

		// For object and lighting
		uniform vec3 objectColor;
		uniform vec3 keyLightColor;
		uniform vec3 keyLightPos;
		uniform vec3 viewPosition;
		uniform vec3 fillLightColor;
		uniform vec3 fillLightPos;

		void main(){
			/* Key Light Calculations */
			/* Calculate Ambient Lighting */
			float keyAmbientStrength = 0.0f;
			vec3 keyAmbient = keyAmbientStrength * keyLightColor;

			/* Calculate Diffuse Lighting */
			vec3 norm = normalize(Normal);
			vec3 keyLightDirection = normalize(keyLightPos - FragmentPos);
			float keyImpact = max(dot(norm, keyLightDirection), 0.0);
			vec3 keyDiffuse = keyImpact * keyLightColor;

			/* Calculate Specular Lighting */
			float keySpecularIntensity = 0.1f;
			float keyHighlightSize = 0.0f;
			vec3 viewDir = normalize(viewPosition - FragmentPos);
			vec3 reflectDir = reflect(-keyLightDirection, norm);

			float keySpecularComponent = pow(max(dot(viewDir, reflectDir), 0.0), keyHighlightSize);
			vec3 keySpecular = keySpecularIntensity * keySpecularComponent * keyLightColor;

			// Create Key Light Phong
			vec3 keyPhong = (keyAmbient + keyDiffuse + keySpecular) * objectColor;

			/* Fill Light Calculations */
			/* Calculate Ambient Lighting */
			float fillAmbientStrength = 0.5f;
			vec3 fillAmbient = fillAmbientStrength * keyLightColor;

			/* Calculate Diffuse Lighting */
			vec3 norm2 = normalize(Normal);
			vec3 fillLightDirection = normalize(fillLightPos - FragmentPos);
			float fillImpact = max(dot(norm2, fillLightDirection), 0.0);
			vec3 fillDiffuse = fillImpact * fillLightColor;

			/* Calculate Specular Lighting */
			float fillSpecularIntensity = 0.0f;
			float fillHighlightSize = 0.0f;
			vec3 viewDir2 = normalize(viewPosition - FragmentPos);
			vec3 reflectDir2 = reflect(-fillLightDirection, norm2);

			float fillSpecularComponent = pow(max(dot(viewDir2, reflectDir2), 0.0), fillHighlightSize);
			vec3 fillSpecular = fillSpecularIntensity * fillSpecularComponent * fillLightColor;

			// Create Fill Light Phong
			vec3 fillPhong = (fillAmbient + fillDiffuse + fillSpecular) * objectColor;

			// Merge phongs with texture and send data to GPU
			pyramidColor =
					(vec4(keyPhong, 1.0f) * texture(uTexture, mobileTextureCoordinate)) +
					(vec4(fillPhong, 1.0f) * texture(uTexture, mobileTextureCoordinate));

		}
);

/* Main Function; Entry point to OpenGL program */
int main(int argc, char* argv[]){

	glutInit(&argc, argv);	// Initialize the OpenGL program
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA); // Memory buffer setup for display
	glutInitWindowSize(WindowWidth, WindowHeight); // Sets window size
	glutCreateWindow(WINDOW_TITLE); // Creates a window with macro title

	glutReshapeFunc(UResizeWindow); // Called when window is resized

	glewExperimental = GL_TRUE;
			if (glewInit() != GLEW_OK){
				cout << "Failed to initialize GLEW" << endl;
				return -1;
			}

	UCreateShader();	// Calls the function to create the Shader Program

	UCreateBuffers();	// Calls the function to create Buffers

	UGenerateTexture();	// Calls the function to generate textures

	glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // Sets background color to black

	glutDisplayFunc(URenderGraphics); // Renders graphics on the screen

	glutKeyboardFunc(UKeyboard);		// Calls the function to handle key presses
	glutKeyboardUpFunc(UKeyReleased);	// Calls the function to handle key releases
	glutMouseFunc(UMouseClick);			// Calls the function to handle mouse clicks
	glutMotionFunc(UMousePressedMove);	// Calls the function to handle mouse button pressed movement

	glutMainLoop();	// Starts the OpenGL loop in the background

	// Destroys buffer objects after use
	glDeleteVertexArrays(1, &PyramidVAO);
	glDeleteVertexArrays(1, &LightVAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);

	return 0;

}

/* Implements UResizeWindow Function */
void UResizeWindow(int width, int height){

	glViewport(0, 0, width, height); // Sets the viewport

}

/* Implements URenderGraphics Function */
void URenderGraphics(void){

	glEnable(GL_DEPTH_TEST); // Enables z depth

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Clears screen

	// Variable declaration
	GLint modelLoc, viewLoc, projLoc, objectColorLoc, keyLightColorLoc, keyLightPositionLoc, viewPositionLoc;
	GLint fillLightColorLoc, fillLightPositionLoc;

	glBindTexture(GL_TEXTURE_2D, texture); // Bind texture

	CameraForwardZ = front; // Replaces camera forward vector with Radians normalized as a unit vector

	// Handles User Perspective Selection
	if(currentKey == 'p'){
		if(perspective == false){
			perspective = true;
			Sleep(200); // Used to prevent the input from reading every frame
		}
		else{
			perspective = false;
			Sleep(200);
		}
	}

	// Handles Camera Reset
	if(currentKey == 'r'){
		cameraPosition = glm::vec3(0.5f, 2.0f, -10.0f);
		front = glm::vec3(0.0f, -2.0f, 10.0f);
	}

	// Handles WASD Camera Control
	if(currentKey == 'w'){
		cameraPosition += cameraSpeed * CameraForwardZ * zoomSpeed;
	}
	if(currentKey == 'a'){
		cameraPosition -= glm::normalize(glm::cross(CameraForwardZ, CameraUpY)) * cameraSpeed;
	}
	if(currentKey == 's'){
		cameraPosition -= cameraSpeed * CameraForwardZ * zoomSpeed;
	}
	if(currentKey == 'd'){
		cameraPosition += glm::normalize(glm::cross(CameraForwardZ, CameraUpY)) * cameraSpeed;
	}
	if(currentKey == 'q'){
		yaw -= sensitivity;
		front.x = 10.0f * cos(yaw);
		front.z = sin(yaw) * cos(pitch) * 10.0f;
	}
	if(currentKey == 'e'){
		yaw += sensitivity;
		front.x = 10.0f * cos(yaw);
		front.z = sin(yaw) * cos(pitch) * 10.0f;
	}
	if(currentKey == ' '){
		cameraPosition += cameraSpeed * CameraUpY;
	}
	if(currentKey == 'z'){
		cameraPosition -= cameraSpeed * CameraUpY;
	}

	// Create matrices
	glm::mat4 model;
	glm::mat4 view;
	glm::mat4 projection;

	// Activate object shader and VAO
	glUseProgram(pyramidShaderProgram);
	glBindVertexArray(PyramidVAO);

	// Transforms the object
	model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f));
	model = glm::rotate(model, 0.0f, glm::vec3(0.0f, 1.0f, 0.0f));
	model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));

	// Transforms the camera
	view = glm::lookAt(cameraPosition, cameraPosition+CameraForwardZ, CameraUpY);

	// Creates a perspective or orthogonal projection based on user input
	if(perspective){
		projection = glm::ortho(-5.0f, 5.0f, -5.0f, 5.0f, 0.1f, 100.0f);
	}
	else{
		projection = glm::perspective(45.0f, (GLfloat)WindowWidth / (GLfloat)WindowHeight, 0.1f, 200.0f);
	}

	// Retrieves and then passes transform matrices to the Shader Program
	modelLoc = glGetUniformLocation(pyramidShaderProgram, "model");
	viewLoc = glGetUniformLocation(pyramidShaderProgram, "view");
	projLoc = glGetUniformLocation(pyramidShaderProgram, "projection");

	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
	glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
	glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));

	// References matrix uniforms from shader program
	objectColorLoc = glGetUniformLocation(pyramidShaderProgram, "objectColor");
	keyLightColorLoc = glGetUniformLocation(pyramidShaderProgram, "keyLightColor");
	keyLightPositionLoc = glGetUniformLocation(pyramidShaderProgram, "keyLightPos");
	viewPositionLoc = glGetUniformLocation(pyramidShaderProgram, "viewPosition");
	fillLightColorLoc = glGetUniformLocation(pyramidShaderProgram, "fillLightColor");
	fillLightPositionLoc = glGetUniformLocation(pyramidShaderProgram, "fillLightPos");

	// Passes the data to the shader program's uniforms
	glUniform3f(objectColorLoc, objectColor.r, objectColor.g, objectColor.b);
	glUniform3f(keyLightColorLoc, keyLightColor.r, keyLightColor.g, keyLightColor.b);
	glUniform3f(keyLightPositionLoc, keyLightPosition.x, keyLightPosition.y, keyLightPosition.z);
	glUniform3f(viewPositionLoc, cameraPosition.x, cameraPosition.y, cameraPosition.z);
	glUniform3f(fillLightColorLoc, fillLightColor.r, fillLightColor.g, fillLightColor.b);
	glUniform3f(fillLightPositionLoc, fillLightPosition.x, fillLightPosition.y, fillLightPosition.z);

	glutPostRedisplay();

	// Draw Triangles
	glDrawElements(GL_TRIANGLES, 1200, GL_UNSIGNED_INT, 0);

	glBindVertexArray(0);	// Deactivate VAO

	glutSwapBuffers(); // Flips back buffer with front buffer every frame

}

/* Implements UCreateShader Function */
void UCreateShader(void) {

	/* Pyramid Vertex Shader */
	GLint pyramidVertexShader = glCreateShader(GL_VERTEX_SHADER);		// Create shader
	glShaderSource(pyramidVertexShader, 1, &pyramidVertexShaderSource, NULL);	// Attach source code
	glCompileShader(pyramidVertexShader);								// Compile

	/* Pyramid Fragment Shader */
	GLint pyramidFragmentShader = glCreateShader(GL_FRAGMENT_SHADER);		// Create shader
	glShaderSource(pyramidFragmentShader, 1, &pyramidFragmentShaderSource, NULL);	// Attach source code
	glCompileShader(pyramidFragmentShader);								// Compile

	/* Pyramid Shader Program */
	pyramidShaderProgram = glCreateProgram();				// Create Shader Progarm
	glAttachShader(pyramidShaderProgram, pyramidVertexShader);	// Attach vertex shader
	glAttachShader(pyramidShaderProgram, pyramidFragmentShader);	// Attach fragment shader
	glLinkProgram(pyramidShaderProgram);					// Links vertex/fragment shaders to Shader Program

	/* Deletes shaders once linked */
	glDeleteShader(pyramidVertexShader);
	glDeleteShader(pyramidFragmentShader);

}

/* Implements UCreateBuffers Function */
void UCreateBuffers() {

	GLfloat vertices[] = {

			/* Vertices for the Cup */

			// Exterior Top of the Cup, Points around a Unit Circle (x3); 24 Vertices
			 3.00f,  3.0f,  0.00f,    1.00f, 1.0f,  0.00f,   0.5f,  0.50f, //   0 degrees
			 2.89f,  3.0f,  0.77f,    0.83f, 1.0f,  0.16f,   0.5f,  0.58f, //
			 2.59f,  3.0f,  1.50f,    0.66f, 1.0f,  0.33f,   0.5f,  0.66f, //  30 degrees
			 2.12f,  3.0f,  2.12f,    0.50f, 1.0f,  0.50f,   0.5f,  0.75f, //
			 1.50f,  3.0f,  2.59f,    0.33f, 1.0f,  0.66f,   0.5f,  0.83f, //  60 degrees
			 0.77f,  3.0f,  2.89f,    0.16f, 1.0f,  0.83f,   0.5f,  0.92f, //
			 0.00f,  3.0f,  3.00f,    0.00f, 1.0f,  1.00f,   0.5f,  1.00f, //  90 degrees
			-0.77f,  3.0f,  2.89f,   -0.16f, 1.0f,  0.83f,   0.5f,  0.92f, //
			-1.50f,  3.0f,  2.59f,   -0.33f, 1.0f,  0.66f,   0.5f,  0.83f, // 120 degrees
			-2.12f,  3.0f,  2.12f,   -0.50f, 1.0f,  0.50f,   0.5f,  0.75f, //
			-2.59f,  3.0f,  1.50f,   -0.66f, 1.0f,  0.33f,   0.5f,  0.66f, // 150 degrees
			-2.89f,  3.0f,  0.77f,   -0.83f, 1.0f,  0.16f,   0.5f,  0.58f, //
			-3.00f,  3.0f,  0.00f,   -1.00f, 1.0f,  0.00f,   0.5f,  0.50f, // 180 degrees
			-2.89f,  3.0f, -0.77f,   -0.83f, 1.0f, -0.16f,   0.5f,  0.58f, //
			-2.59f,  3.0f, -1.50f,   -0.66f, 1.0f, -0.33f,   0.5f,  0.66f, // 210 degrees
			-2.12f,  3.0f, -2.12f,   -0.50f, 1.0f, -0.50f,   0.5f,  0.75f, //
			-1.50f,  3.0f, -2.59f,   -0.33f, 1.0f, -0.66f,   0.5f,  0.83f, // 240 degrees
			-0.77f,  3.0f, -2.89f,   -0.16f, 1.0f, -0.83f,   0.5f,  0.92f, //
			 0.00f,  3.0f, -3.00f,    0.00f, 1.0f, -1.00f,   0.5f,  1.00f, // 270 degrees
			 0.77f,  3.0f, -2.89f,    0.16f, 1.0f, -0.83f,   0.5f,  0.92f, //
			 1.50f,  3.0f, -2.59f,    0.33f, 1.0f, -0.66f,   0.5f,  0.83f, // 300 degrees
			 2.12f,  3.0f, -2.12f,    0.50f, 1.0f, -0.50f,   0.5f,  0.75f, //
			 2.59f,  3.0f, -1.50f,    0.66f, 1.0f, -0.33f,   0.5f,  0.66f, // 330 degrees
			 2.89f,  3.0f, -0.77f,    0.83f, 1.0f, -0.16f,   0.5f,  0.58f, //

			 // Exterior Bottom of the Cup, Points around a Unit Circle (x3); 24 Vertices
			 3.00f, -3.0f,  0.00f,    1.00f, 0.2f,  0.00f,   0.0f,  0.50f, //   0 degrees
			 2.89f, -3.0f,  0.77f,    0.83f, 0.2f,  0.16f,   0.0f,  0.58f, //
			 2.59f, -3.0f,  1.50f,    0.66f, 0.2f,  0.33f,   0.0f,  0.66f, //  30 degrees
			 2.12f, -3.0f,  2.12f,    0.50f, 0.2f,  0.50f,   0.0f,  0.75f, //
			 1.50f, -3.0f,  2.59f,    0.33f, 0.2f,  0.66f,   0.0f,  0.83f, //  60 degrees
			 0.77f, -3.0f,  2.89f,    0.16f, 0.2f,  0.87f,   0.0f,  0.92f, //
			 0.00f, -3.0f,  3.00f,    0.00f, 0.2f,  1.00f,   0.0f,  1.00f, //  90 degrees
			-0.77f, -3.0f,  2.89f,   -0.16f, 0.2f,  0.87f,   0.0f,  0.92f, //
			-1.50f, -3.0f,  2.59f,   -0.33f, 0.2f,  0.66f,   0.0f,  0.83f, // 120 degrees
			-2.12f, -3.0f,  2.12f,   -0.50f, 0.2f,  0.50f,   0.0f,  0.75f, //
			-2.59f, -3.0f,  1.50f,   -0.66f, 0.2f,  0.33f,   0.0f,  0.66f, // 150 degrees
			-2.89f, -3.0f,  0.77f,   -0.83f, 0.2f,  0.16f,   0.0f,  0.58f, //
			-3.00f, -3.0f,  0.00f,   -1.00f, 0.2f,  0.00f,   0.0f,  0.50f, // 180 degrees
			-2.89f, -3.0f, -0.77f,   -0.83f, 0.2f, -0.16f,   0.0f,  0.58f, //
			-2.59f, -3.0f, -1.50f,   -0.66f, 0.2f, -0.33f,   0.0f,  0.66f, // 210 degrees
			-2.12f, -3.0f, -2.12f,   -0.50f, 0.2f, -0.50f,   0.0f,  0.75f, //
			-1.50f, -3.0f, -2.59f,   -0.33f, 0.2f, -0.66f,   0.0f,  0.83f, // 240 degrees
			-0.77f, -3.0f, -2.89f,   -0.16f, 0.2f, -0.83f,   0.0f,  0.92f, //
			 0.00f, -3.0f, -3.00f,    0.00f, 0.2f, -1.00f,   0.0f,  1.00f, // 270 degrees
			 0.77f, -3.0f, -2.89f,    0.16f, 0.2f, -0.83f,   0.0f,  0.92f, //
			 1.50f, -3.0f, -2.59f,    0.33f, 0.2f, -0.66f,   0.0f,  0.83f, // 300 degrees
			 2.12f, -3.0f, -2.12f,    0.50f, 0.2f, -0.50f,   0.0f,  0.75f, //
			 2.59f, -3.0f, -1.50f,    0.66f, 0.2f, -0.33f,   0.0f,  0.66f, // 330 degrees
			 2.89f, -3.0f, -0.77f,    0.83f, 0.2f, -0.16f,   0.0f,  0.58f, //

			 // Bottom of the Cup, Center Point
			 0.00f, -3.00f,  0.00f,   0.0f, -1.0f,  0.0f,   0.5f,  0.5f, //   Exterior
			 0.00f, -2.80f,  0.00f,   0.0f, -1.0f,  0.0f,   0.5f,  0.5f, //   Interior

			 // Interior Top of the Cup, Points around a Unit Circle (x2.85); 24 Vertices
			 2.85f,  3.0f,  0.00f,    0.00f, 0.0f,  0.00f,   0.5f,  0.50f, //   0 degrees
			 2.75f,  3.0f,  0.74f,    0.00f, 0.0f,  0.00f,   0.5f,  0.58f, //
			 2.46f,  3.0f,  1.42f,    0.00f, 0.0f,  0.00f,   0.5f,  0.66f, //  30 degrees
			 2.02f,  3.0f,  2.02f,    0.00f, 0.0f,  0.00f,   0.5f,  0.75f, //
			 1.42f,  3.0f,  2.46f,    0.00f, 0.0f,  0.00f,   0.5f,  0.83f, //  60 degrees
			 0.74f,  3.0f,  2.75f,    0.00f, 0.0f,  0.00f,   0.5f,  0.92f, //
			 0.00f,  3.0f,  2.85f,    0.00f, 0.0f,  0.00f,   0.5f,  1.00f, //  90 degrees
			-0.74f,  3.0f,  2.75f,    0.00f, 0.0f,  0.00f,   0.5f,  0.92f, //
			-1.42f,  3.0f,  2.46f,    0.00f, 0.0f,  0.00f,   0.5f,  0.83f, // 120 degrees
			-2.02f,  3.0f,  2.02f,    0.00f, 0.0f,  0.00f,   0.5f,  0.75f, //
			-2.46f,  3.0f,  1.42f,    0.00f, 0.0f,  0.00f,   0.5f,  0.66f, // 150 degrees
			-2.75f,  3.0f,  0.74f,    0.00f, 0.0f,  0.00f,   0.5f,  0.58f, //
			-2.85f,  3.0f,  0.00f,    0.00f, 0.0f,  0.00f,   0.5f,  0.50f, // 180 degrees
			-2.75f,  3.0f, -0.74f,    0.00f, 0.0f,  0.00f,   0.5f,  0.58f, //
			-2.46f,  3.0f, -1.42f,    0.00f, 0.0f,  0.00f,   0.5f,  0.66f, // 210 degrees
			-2.02f,  3.0f, -2.02f,    0.00f, 0.0f,  0.00f,   0.5f,  0.75f, //
			-1.42f,  3.0f, -2.46f,    0.00f, 0.0f,  0.00f,   0.5f,  0.83f, // 240 degrees
			-0.74f,  3.0f, -2.75f,    0.00f, 0.0f,  0.00f,   0.5f,  0.92f, //
			 0.00f,  3.0f, -2.85f,    0.00f, 0.0f,  0.00f,   0.5f,  1.00f, // 270 degrees
			 0.74f,  3.0f, -2.75f,    0.00f, 0.0f,  0.00f,   0.5f,  0.92f, //
			 1.42f,  3.0f, -2.46f,    0.00f, 0.0f,  0.00f,   0.5f,  0.83f, // 300 degrees
			 2.02f,  3.0f, -2.02f,    0.00f, 0.0f,  0.00f,   0.5f,  0.75f, //
			 2.46f,  3.0f, -1.42f,    0.00f, 0.0f,  0.00f,   0.5f,  0.66f, // 330 degrees
			 2.75f,  3.0f, -0.74f,    0.00f, 0.0f,  0.00f,   0.5f,  0.58f, //

			 // Interior Bottom of the Cup, Points around a Unit Circle (x2.85); 24 Vertices
			 2.85f, -2.80f,  0.00f,   0.00f,-1.0f,  0.00f,   0.0f,  0.50f, //   0 degrees
			 2.75f, -2.80f,  0.74f,   0.00f,-1.0f,  0.00f,   0.0f,  0.58f, //
			 2.46f, -2.80f,  1.42f,   0.00f,-1.0f,  0.00f,   0.0f,  0.66f, //  30 degrees
			 2.02f, -2.80f,  2.02f,   0.00f,-1.0f,  0.00f,   0.0f,  0.75f, //
			 1.42f, -2.80f,  2.46f,   0.00f,-1.0f,  0.00f,   0.0f,  0.83f, //  60 degrees
			 0.74f, -2.80f,  2.75f,   0.00f,-1.0f,  0.00f,   0.0f,  0.92f, //
			 0.00f, -2.80f,  2.85f,   0.00f,-1.0f,  0.00f,   0.0f,  1.00f, //  90 degrees
			-0.74f, -2.80f,  2.75f,   0.00f,-1.0f,  0.00f,   0.0f,  0.92f, //
			-1.42f, -2.80f,  2.46f,   0.00f,-1.0f,  0.00f,   0.0f,  0.83f, // 120 degrees
			-2.02f, -2.80f,  2.02f,   0.00f,-1.0f,  0.00f,   0.0f,  0.75f, //
			-2.46f, -2.80f,  1.42f,   0.00f,-1.0f,  0.00f,   0.0f,  0.66f, // 150 degrees
			-2.75f, -2.80f,  0.74f,   0.00f,-1.0f,  0.00f,   0.0f,  0.58f, //
			-2.85f, -2.80f,  0.00f,   0.00f,-1.0f,  0.00f,   0.0f,  0.50f, // 180 degrees
			-2.75f, -2.80f, -0.74f,   0.00f,-1.0f,  0.00f,   0.0f,  0.58f, //
			-2.46f, -2.80f, -1.42f,   0.00f,-1.0f,  0.00f,   0.0f,  0.66f, // 210 degrees
			-2.02f, -2.80f, -2.02f,   0.00f,-1.0f,  0.00f,   0.0f,  0.75f, //
			-1.42f, -2.80f, -2.46f,   0.00f,-1.0f,  0.00f,   0.0f,  0.83f, // 240 degrees
			-0.74f, -2.80f, -2.75f,   0.00f,-1.0f,  0.00f,   0.0f,  0.92f, //
			 0.00f, -2.80f, -2.85f,   0.00f,-1.0f,  0.00f,   0.0f,  1.00f, // 270 degrees
			 0.74f, -2.80f, -2.75f,   0.00f,-1.0f,  0.00f,   0.0f,  0.92f, //
			 1.42f, -2.80f, -2.46f,   0.00f,-1.0f,  0.00f,   0.0f,  0.83f, // 300 degrees
			 2.02f, -2.80f, -2.02f,   0.00f,-1.0f,  0.00f,   0.0f,  0.75f, //
			 2.46f, -2.80f, -1.42f,   0.00f,-1.0f,  0.00f,   0.0f,  0.66f, // 330 degrees
			 2.75f, -2.80f, -0.74f,   0.00f,-1.0f,  0.00f,   0.0f,  0.58f, //

			 // Handle Upper Z+
			 2.89f,  2.50f,  0.42f,   1.0f, 3.0f, 0.2f,   0.50f,  0.50f, //   1
			 3.70f,  2.45f,  0.42f,   1.2f, 2.8f, 0.2f,   0.45f,  0.55f, //   2
			 4.70f,  2.20f,  0.42f,   1.4f, 2.6f, 0.2f,   0.40f,  0.60f, //   3
			 4.85f,  2.00f,  0.42f,   1.6f, 2.4f, 0.2f,   0.35f,  0.65f, //   4
			 5.00f,  1.50f,  0.42f,   1.8f, 2.2f, 0.2f,   0.30f,  0.70f, //   5
			 5.10f,  1.00f,  0.42f,   1.9f, 2.0f, 0.2f,   0.25f,  0.75f, //   6
			 5.20f,  0.50f,  0.42f,   2.0f, 1.8f, 0.2f,   0.20f,  0.80f, //   7
			 5.20f,  0.00f,  0.42f,   1.9f, 1.6f, 0.2f,   0.15f,  0.85f, //   8
			 5.10f, -0.50f,  0.42f,   1.8f, 1.4f, 0.2f,   0.10f,  0.90f, //   9
			 4.95f, -1.00f,  0.42f,   1.6f, 1.2f, 0.2f,   0.05f,  0.95f, //   10
			 4.70f, -1.50f,  0.42f,   1.4f, 1.0f, 0.2f,   0.00f,  1.00f, //   11
			 4.30f, -2.00f,  0.42f,   1.2f, 0.8f, 0.2f,   0.05f,  0.95f, //   12
			 3.60f, -2.30f,  0.42f,   1.1f, 0.6f, 0.2f,   0.10f,  0.90f, //   13
			 2.89f, -2.50f,  0.42f,   1.0f, 0.4f, 0.2f,   0.15f,  0.85f, //   14

			 // Handle Upper Z-
			 2.89f,  2.50f, -0.42f,   1.0f, 3.0f, -0.2f,  0.00f,  0.50f, //   38
			 3.70f,  2.45f, -0.42f,   1.0f, 2.8f, -0.2f,  0.05f,  0.55f, //   2
			 4.70f,  2.20f, -0.42f,   1.0f, 2.6f, -0.2f,  0.10f,  0.60f, //   3
			 4.85f,  2.00f, -0.42f,   1.0f, 2.4f, -0.2f,  0.15f,  0.65f, //   4
			 5.00f,  1.50f, -0.42f,   1.0f, 2.2f, -0.2f,  0.20f,  0.70f, //   5
			 5.10f,  1.00f, -0.42f,   1.0f, 2.0f, -0.2f,  0.25f,  0.75f, //   6
			 5.20f,  0.50f, -0.42f,   1.0f, 1.8f, -0.2f,  0.30f,  0.80f, //   7
			 5.20f,  0.00f, -0.42f,   1.0f, 1.6f, -0.2f,  0.35f,  0.85f, //   8
			 5.10f, -0.50f, -0.42f,   1.0f, 1.4f, -0.2f,  0.40f,  0.90f, //   9
			 4.95f, -1.00f, -0.42f,   1.0f, 1.2f, -0.2f,  0.45f,  0.95f, //   10
			 4.70f, -1.50f, -0.42f,   1.0f, 1.0f, -0.2f,  0.50f,  1.00f, //   11
			 4.30f, -2.00f, -0.42f,   1.0f, 0.8f, -0.2f,  0.45f,  0.95f, //   12
			 3.60f, -2.30f, -0.42f,   1.0f, 0.6f, -0.2f,  0.40f,  0.90f, //   13
			 2.89f, -2.50f, -0.42f,   1.0f, 0.4f, -0.2f,  0.35f,  0.85f, //   14

			 // Handle Lower Z+
			 2.89f,  1.90f,  0.42f,  1.0f, 3.0f, 0.2f,   0.00f,  0.50f, //   52
			 3.80f,  1.85f,  0.42f,  1.0f, 2.8f, 0.2f,   0.05f,  0.55f, //   2
			 4.00f,  1.80f,  0.42f,  1.0f, 2.6f, 0.2f,   0.10f,  0.60f, //   3
			 4.30f,  1.75f,  0.42f,  1.0f, 2.4f, 0.2f,   0.15f,  0.65f, //   4
			 4.50f,  1.30f,  0.42f,  1.0f, 2.2f, 0.2f,   0.20f,  0.70f, //   5
			 4.60f,  1.00f,  0.42f,  1.0f, 2.0f, 0.2f,   0.25f,  0.75f, //   6
			 4.65f,  0.50f,  0.42f,  1.0f, 1.8f, 0.2f,   0.30f,  0.80f, //   7
			 4.65f,  0.00f,  0.42f,  1.0f, 1.6f, 0.2f,   0.35f,  0.85f, //   8
			 4.60f, -0.40f,  0.42f,  1.0f, 1.4f, 0.2f,   0.40f,  0.90f, //   9
			 4.50f, -0.80f,  0.42f,  1.0f, 1.2f, 0.2f,   0.45f,  0.95f, //   10
			 4.40f, -1.10f,  0.42f,  1.0f, 1.0f, 0.2f,   0.50f,  1.00f, //   11
			 4.15f, -1.30f,  0.42f,  1.0f, 0.8f, 0.2f,   0.45f,  0.95f, //   12
			 3.60f, -1.65f,  0.42f,  1.0f, 0.6f, 0.2f,   0.40f,  0.90f, //   13
			 2.89f, -1.80f,  0.42f,  1.0f, 0.4f, 0.2f,   0.35f,  0.85f, //   14

			 // Handle Lower Z-
			 2.89f,  1.90f, -0.42f,  1.0f, 3.0f, -0.2f,   0.50f,  0.50f, //   1
			 3.80f,  1.85f, -0.42f,  1.0f, 2.8f, -0.2f,   0.45f,  0.55f, //   2
			 4.00f,  1.80f, -0.42f,  1.0f, 2.6f, -0.2f,   0.40f,  0.60f, //   3
			 4.30f,  1.75f, -0.42f,  1.0f, 2.4f, -0.2f,   0.35f,  0.65f, //   4
			 4.50f,  1.30f, -0.42f,  1.0f, 2.2f, -0.2f,   0.30f,  0.70f, //   5
			 4.60f,  1.00f, -0.42f,  1.0f, 2.0f, -0.2f,   0.25f,  0.75f, //   6
			 4.65f,  0.50f, -0.42f,  1.0f, 1.8f, -0.2f,   0.20f,  0.80f, //   7
			 4.65f,  0.00f, -0.42f,  1.0f, 1.6f, -0.2f,   0.15f,  0.85f, //   8
			 4.60f, -0.40f, -0.42f,  1.0f, 1.4f, -0.2f,   0.10f,  0.90f, //   9
			 4.50f, -0.80f, -0.42f,  1.0f, 1.2f, -0.2f,   0.05f,  0.95f, //   10
			 4.40f, -1.10f, -0.42f,  1.0f, 1.0f, -0.2f,   0.00f,  1.00f, //   11
			 4.15f, -1.30f, -0.42f,  1.0f, 0.8f, -0.2f,   0.05f,  0.95f, //   12
			 3.60f, -1.65f, -0.42f,  1.0f, 0.6f, -0.2f,   0.10f,  0.90f, //   13
			 2.89f, -1.80f, -0.42f,  1.0f, 0.4f, -0.2f,   0.15f,  0.85f, //   14

			 // Table Top Upper
			 10.0f, -3.00f,  10.0f,  1.0f, 1.0f, -0.2f,   1.0f,  1.0f, //   1
			-10.0f, -3.00f,  10.0f,  1.0f, 1.0f, -0.2f,   0.5f,  1.0f, //   2
			-10.0f, -3.00f, -10.0f,  1.0f, 1.0f, -0.2f,   0.5f,  0.5f, //   3
			 10.0f, -3.00f, -10.0f,  1.0f, 1.0f, -0.2f,   1.0f,  0.5f, //   4

			 // Table Top Lower
			 10.0f, -4.00f,  10.0f,  1.0f,-1.0f, -0.2f,   0.5f,  0.5f, //   1
			-10.0f, -4.00f,  10.0f,  1.0f,-1.0f, -0.2f,   1.0f,  0.5f, //   2
			-10.0f, -4.00f, -10.0f,  1.0f,-1.0f, -0.2f,   1.0f,  1.0f, //   3
			 10.0f, -4.00f, -10.0f,  1.0f,-1.0f, -0.2f,   0.5f,  1.0f, //   4

			 // Ceiling
			 50.0f, 50.00f,  50.0f,   1.0f, 1.0f,  1.0f,   1.0f,  0.5f, //   1
			-50.0f, 50.00f,  50.0f,  -1.0f, 1.0f,  1.0f,   0.5f,  0.5f, //   2
			-50.0f, 50.00f, -50.0f,  -1.0f, 1.0f, -1.0f,   0.5f,  0.0f, //   3
			 50.0f, 50.00f, -50.0f,   1.0f, 1.0f, -1.0f,   1.0f,  0.0f, //   4

			 // Floor
			 50.0f, -30.00f,  50.0f,   1.0f, -1.0f,  1.0f,   0.5f,  0.5f, //   1
			-50.0f, -30.00f,  50.0f,  -1.0f, -1.0f,  1.0f,   0.0f,  0.5f, //   2
			-50.0f, -30.00f, -50.0f,  -1.0f, -1.0f, -1.0f,   0.0f,  0.0f, //   3
			 50.0f, -30.00f, -50.0f,   1.0f, -1.0f, -1.0f,   0.5f,  0.0f, //   4

			 // Floor Wall Texture
			 50.0f, -50.00f,  50.0f,   1.0f,  1.0f,  1.0f,   0.5f,  0.0f, //   1
			-50.0f, -50.00f,  50.0f,  -1.0f,  1.0f,  1.0f,   1.0f,  0.0f, //   2
			-50.0f, -50.00f, -50.0f,  -1.0f, -1.0f, -1.0f,   1.0f,  0.5f, //   3
			 50.0f, -50.00f, -50.0f,   1.0f, -1.0f, -1.0f,   0.5f,  0.5f, //   4

			 // Table Legs Top
			 9.0f, -4.00f,  9.0f,  1.0f, 0.0f, -0.2f,   0.5f,  1.0f, //   1
			 8.0f, -4.00f,  9.0f,  1.0f, 0.0f, -0.2f,   0.5f,  1.0f, //   1
			 8.0f, -4.00f,  8.0f,  1.0f, 0.0f, -0.2f,   0.5f,  1.0f, //   1
			 9.0f, -4.00f,  8.0f,  1.0f, 0.0f, -0.2f,   0.5f,  1.0f, //   1

			-9.0f, -4.00f,  9.0f,  1.0f, 0.0f, -0.2f,   0.5f,  1.0f, //   2
			-8.0f, -4.00f,  9.0f,  1.0f, 0.0f, -0.2f,   0.5f,  1.0f, //   2
			-8.0f, -4.00f,  8.0f,  1.0f, 0.0f, -0.2f,   0.5f,  1.0f, //   2
			-9.0f, -4.00f,  8.0f,  1.0f, 0.0f, -0.2f,   0.5f,  1.0f, //   2

			-9.0f, -4.00f, -9.0f,  1.0f, 0.0f, -0.2f,   0.5f,  1.0f, //   3
			-8.0f, -4.00f, -9.0f,  1.0f, 0.0f, -0.2f,   0.5f,  1.0f, //   3
			-8.0f, -4.00f, -8.0f,  1.0f, 0.0f, -0.2f,   0.5f,  1.0f, //   3
			-9.0f, -4.00f, -8.0f,  1.0f, 0.0f, -0.2f,   0.5f,  1.0f, //   3

			 9.0f, -4.00f, -9.0f,  1.0f, 0.0f, -0.2f,   0.5f,  1.0f, //   4
			 8.0f, -4.00f, -9.0f,  1.0f, 0.0f, -0.2f,   0.5f,  1.0f, //   4
			 8.0f, -4.00f, -8.0f,  1.0f, 0.0f, -0.2f,   0.5f,  1.0f, //   4
			 9.0f, -4.00f, -8.0f,  1.0f, 0.0f, -0.2f,   0.5f,  1.0f, //   4

			 // Table Legs Bottom
			 9.0f, -49.00f,  9.0f,  1.0f, 0.0f, -0.2f,   1.0f,  0.5f, //   1
			 8.0f, -49.00f,  9.0f,  1.0f, 0.0f, -0.2f,   1.0f,  0.5f, //   1
			 8.0f, -49.00f,  8.0f,  1.0f, 0.0f, -0.2f,   1.0f,  0.5f, //   1
			 9.0f, -49.00f,  8.0f,  1.0f, 0.0f, -0.2f,   1.0f,  0.5f, //   1

			-9.0f, -49.00f,  9.0f,  1.0f, 0.0f, -0.2f,   1.0f,  0.5f, //   2
			-8.0f, -49.00f,  9.0f,  1.0f, 0.0f, -0.2f,   1.0f,  0.5f, //   2
			-8.0f, -49.00f,  8.0f,  1.0f, 0.0f, -0.2f,   1.0f,  0.5f, //   2
			-9.0f, -49.00f,  8.0f,  1.0f, 0.0f, -0.2f,   1.0f,  0.5f, //   2

			-9.0f, -49.00f, -9.0f,  1.0f, 0.0f, -0.2f,   1.0f,  0.5f, //   3
			-8.0f, -49.00f, -9.0f,  1.0f, 0.0f, -0.2f,   1.0f,  0.5f, //   3
			-8.0f, -49.00f, -8.0f,  1.0f, 0.0f, -0.2f,   1.0f,  0.5f, //   3
			-9.0f, -49.00f, -8.0f,  1.0f, 0.0f, -0.2f,   1.0f,  0.5f, //   3

			 9.0f, -49.00f, -9.0f,  1.0f, 0.0f, -0.2f,   1.0f,  0.5f, //   4
			 8.0f, -49.00f, -9.0f,  1.0f, 0.0f, -0.2f,   1.0f,  0.5f, //   4
			 8.0f, -49.00f, -8.0f,  1.0f, 0.0f, -0.2f,   1.0f,  0.5f, //   4
			 9.0f, -49.00f, -8.0f,  1.0f, 0.0f, -0.2f,   1.0f,  0.5f, //   4
	};

	GLuint indices[] = {
			/* Reference
			 *   0 -  23 Top of Body; Exterior
			 *  24 -  47 Bottom of Body; Exterior
			 *  48		 Center Point of Bottom; Exterior
			 *  49		 Center Point of Bottom; Interior
			 *  50 -  73 Top of Body; Interior
			 *  74 -  97 Bottom of Body; Interior
			 *  */

			/* Indices used to draw Body Exterior */
			// Drawing triangles from two top vertices to bottom left; 24 triangles, 72 vertices
			0, 1, 24,			1, 2, 25,			2, 3, 26,			3, 4, 27,
			4, 5, 28,			5, 6, 29,			6, 7, 30,			7, 8, 31,
			8, 9, 32,			9, 10, 33,			10, 11, 34,			11, 12, 35,
			12, 13, 36,			13, 14, 37,			14, 15, 38,			15, 16, 39,
			16, 17, 40,			17, 18, 41,			18, 19, 42,			19, 20, 43,
			20, 21, 44,			21, 22, 45,			22, 23, 46,			23, 0, 47,

			// Drawing triangles from two bottom vertices to top right; 24 triangles, 72 vertices
			24, 25, 1,			25, 26, 2,			26, 27, 3,			27, 28, 4,
			28, 29, 5,			29, 30, 6,			30, 31, 7,			31, 32, 8,
			32, 33, 9,			33, 34, 10,			34, 35, 11,			35, 36, 12,
			36, 37, 13,			37, 38, 14,			38, 39, 15,			39, 40, 16,
			40, 41, 17,			41, 42, 18,			42, 43, 19,			43, 44, 20,
			44, 45, 21,			45, 46, 22,			46, 47, 23,			47, 24, 0,

			// Draw Exterior Cup Base; 24 triangles, 72 vertices
			24, 25, 48,			25, 26, 48,			26, 27, 48,			27, 28, 48,
			28, 29, 48,			29, 30, 48,			30, 31, 48,			31, 32, 48,
			32, 33, 48,			33, 34, 48,			34, 35, 48,			35, 36, 48,
			36, 37, 48,			37, 38, 48,			38, 39, 48,			39, 40, 48,
			40, 41, 48,			41, 42, 48,			42, 43, 48,			43, 44, 48,
			44, 45, 48,			45, 46, 48,			46, 47, 48,			47, 24, 48,

			/* Indices used to draw Body Interior */
			// Drawing triangles from two top vertices to bottom left; 24 triangles, 72 vertices
			50, 51, 74,			51, 52, 75,			52, 53, 76,			53, 54, 77,
			54, 55, 78,			55, 56, 79,			56, 57, 80,			57, 58, 81,
			58, 59, 82,			59, 60, 83,			60, 61, 84,			61, 62, 85,
			62, 63, 86,			63, 64, 87,			64, 65, 88,			65, 66, 89,
			66, 67, 90,			67, 68, 91,			68, 69, 92,			69, 70, 93,
			70, 71, 94,			71, 72, 95,			72, 73, 96,			73, 50, 97,

			// Drawing triangles from two bottom vertices to top right; 24 triangles, 72 vertices
			74, 75, 51,			75, 76, 52,			76, 77, 53,			77, 78, 54,
			78, 79, 55,			79, 80, 56,			80, 81, 57,			81, 82, 58,
			82, 83, 59,			83, 84, 60,			84, 85, 61,			85, 86, 62,
			86, 87, 63,			87, 88, 64,			88, 89, 65,			89, 90, 66,
			90, 91, 67,			91, 92, 68,			92, 93, 69,			93, 94, 70,
			94, 95, 71,			95, 96, 72,			96, 97, 73,			97, 74, 50,

			// Draw Interior Cup Base; 24 triangles, 72 vertices
			74, 75, 49,			75, 76, 49,			76, 77, 49,			77, 78, 49,
			78, 79, 49,			79, 80, 49,			80, 81, 49,			81, 82, 49,
			82, 83, 49,			83, 84, 49,			84, 85, 49,			85, 86, 49,
			86, 87, 49,			87, 88, 49,			88, 89, 49,			89, 90, 49,
			90, 91, 49,			91, 92, 49,			92, 93, 49,			93, 94, 49,
			94, 95, 49,			95, 96, 49,			96, 97, 49,			97, 74, 49,

			/* Indices used to connect top interior to top exterior; 48 triangles, 104 vertices*/
			0, 1, 50,			50, 51, 1,			1, 2, 51,			51, 52, 2,
			2, 3, 52,			52, 53, 3,			3, 4, 53,			53, 54, 4,
			4, 5, 54,			54, 55, 5,			5, 6, 55,			55, 56, 6,
			6, 7, 56,			56, 57, 7,			7, 8, 57,			57, 58, 8,
			8, 9, 58,			58, 59, 9,			9, 10, 59,			59, 60, 10,
			10, 11, 60,			60, 61, 11,			11, 12, 61,			61, 62, 12,
			12, 13, 62,			62, 63, 13,			13, 14, 63,			63, 64, 14,
			14, 15, 64,			64, 65, 15,			15, 16, 65,			65, 66, 16,
			16, 17, 66,			66, 67, 17,			17, 18, 67,			67, 68, 18,
			18, 19, 68,			68, 69, 19,			19, 20, 69,			69, 70, 20,
			20, 21, 70,			70, 71, 21,			21, 22, 71,			71, 72, 22,
			22, 23, 72,			72, 73, 23,			23, 0, 73,			73, 50, 0,

			/* Reference
			 *  98 - 111 Handle Upper Z+
			 * 112 - 125 Handle Upper Z-
			 * 126 - 139 Handle Lower Z+
			 * 140 - 153 Handle Lower Z-
			 *  */

			// Draw top and bottom sides of Handle; 52 triangles, 156 vertices
			98, 99, 112,		112, 113, 99,		126, 127, 140,		140, 141, 127,
			99, 100, 113,		113, 114, 100,		127, 128, 141,		141, 142, 128,
			100, 101, 114,		114, 115, 101,		128, 129, 142,		142, 143, 129,
			101, 102, 115,		115, 116, 102,		129, 130, 143,		143, 144, 130,
			102, 103, 116,		116, 117, 103,		130, 131, 144,		144, 145, 131,
			103, 104, 117,		117, 118, 104,		131, 132, 145,		145, 146, 132,
			104, 105, 118,		118, 119, 105,		132, 133, 146,		146, 147, 133,
			105, 106, 119,		119, 120, 106,		133, 134, 147,		147, 148, 134,
			106, 107, 120,		120, 121, 107,		134, 135, 148,		148, 149, 135,
			107, 108, 121,		121, 122, 108,		135, 136, 149,		149, 150, 136,
			108, 109, 122,		122, 123, 109,		136, 137, 150,		150, 151, 137,
			109, 110, 123,		123, 124, 110,		137, 138, 151,		151, 152, 138,
			110, 111, 124,		124, 125, 111,		138, 139, 152,		152, 153, 139,

			// Draw left and right sides of handle; 52 triangles, 156 vertices
			112, 113, 140,		140, 141, 113,		98, 99, 126,		126, 127, 99,
			113, 114, 141,		141, 142, 114,		99, 100, 127,		127, 128, 100,
			114, 115, 142,		142, 143, 115,		100, 101, 128,		128, 129, 101,
			115, 116, 143,		143, 144, 116,		101, 102, 129,		129, 130, 102,
			116, 117, 144,		144, 145, 117,		102, 103, 130,		130, 131, 103,
			117, 118, 145,		145, 146, 118,		103, 104, 131,		131, 132, 104,
			118, 119, 146,		146, 147, 119,		104, 105, 132,		132, 133, 105,
			119, 120, 147,		147, 148, 120,		105, 106, 133,		133, 134, 106,
			120, 121, 148,		148, 149, 121,		106, 107, 134,		134, 135, 107,
			121, 122, 149,		149, 150, 122,		107, 108, 135,		135, 136, 108,
			122, 123, 150,		150, 151, 123,		108, 109, 136,		136, 137, 109,
			123, 124, 151,		151, 152, 124,		109, 110, 137,		137, 138, 110,
			124, 125, 152,		152, 153, 125,		110, 111, 138,		138, 139, 111,

			/* Reference
			 * 154 - 157 Table Top Upper			174 - 177		182 - 185
			 * 158 - 161 Table Top Lower			178 - 181		186 - 189
			 *  */

			154, 155, 156,		158, 159, 160,
			156, 157, 154,		160, 161, 158,

			154, 155, 158,		158, 159, 155,
			155, 156, 159,		159, 160, 156,
			156, 157, 160,		160, 161, 157,
			157, 154, 161,		161, 158, 154,

			/* Reference
			 * 162 - 165 Ceiling
			 * 166 - 169 Floor
			 * 170 - 173 Floor - Wall Texture
			 *  */

			162, 163, 164,		166, 167, 168,
			164, 165, 162,		168, 169, 166,

			162, 163, 170,		163, 170, 171,
			163, 164, 171,		164, 171, 172,
			164, 165, 172,		165, 172, 173,
			165, 162, 173,		162, 173, 170,

			/* Reference
			 * 174 - 189 Table Legs Upper
			 * 190 - 205 Table Legs Lower
			 *  */
			174, 175, 190,		178, 179, 194,		182, 183, 198,		186, 187, 202,
			175, 176, 191,		179, 180, 195,		183, 184, 199,		187, 188, 203,
			176, 177, 192,		180, 181, 196, 		184, 185, 200,		188, 189, 204,
			177, 174, 193,		181, 178, 197,		185, 182, 201,		189, 186, 205,
			190, 191, 175,		194, 195, 179,		198, 199, 183,		202, 203, 187,
			191, 192, 176,		195, 196, 180,		199, 200, 184,		203, 204, 188,
			192, 193, 177,		196, 197, 181, 		200, 201, 185,		204, 205, 189,
			193, 190, 174,		197, 194, 178,		201, 198, 182,		205, 202, 186,

	};

	/* Create Buffers */
	glGenVertexArrays(1, &PyramidVAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	glBindVertexArray(PyramidVAO); 	// Activate VAO

	glBindBuffer(GL_ARRAY_BUFFER, VBO);	// Activate VBO
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW); // Sends vertex/color data to GPU

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);	// Activate EBO
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW); // Send data to GPU

	/* Instructs the GPU on how to handle the vertex buffer object data */
	glEnableVertexAttribArray(0); 	// Specifies initial position of the coordinates in the buffer
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)0);

	glEnableVertexAttribArray(1); 	// Specifies position 1 for normal values in the buffer
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(float)));

	glEnableVertexAttribArray(2); 	// Specifies position 2 texture coordinates
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(6 * sizeof(float)));

	glBindVertexArray(0); 		// Deactivate VAO
}

/* Implements UGenerateTexture Function */
void UGenerateTexture(){

	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);

	int width, height;

	unsigned char* image = SOIL_load_image("texture.jpg", &width, &height, 0, SOIL_LOAD_RGB);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
	glGenerateMipmap(GL_TEXTURE_2D);
	SOIL_free_image_data(image);
	glBindTexture(GL_TEXTURE_2D, 0);

}

/* Implements UKeyboard Function */
void UKeyboard(unsigned char key, GLint x, GLint y){
	// Detects the following keys presses
	switch(key){

	case 'p':
		currentKey = key;
		break;

	case 'r':
		currentKey = key;
		break;

	case 'w':
		currentKey = key;
		break;

	case 'a':
		currentKey = key;
		break;

	case 's':
		currentKey = key;
		break;

	case 'd':
		currentKey = key;
		break;

	case 'q':
		currentKey = key;
		break;

	case 'e':
		currentKey = key;
		break;

	case ' ':
		currentKey = key;
		break;

	case 'z':
		currentKey = key;
		break;
	}
}

/* Implements UKeyReleased Function */
void UKeyReleased(unsigned char key, GLint x, GLint y){

	currentKey = '0'; // Clears current key value when the key is released

}

/* Implements UMouseClick Function */
void UMouseClick(int button, int state, int x, int y){

	// Allows orbiting if left mouse button is pressed, zoom if right mouse button is pressed
	if((button == GLUT_LEFT_BUTTON) && (state == GLUT_DOWN)){
		orbit = true;
	}
	else if((button == GLUT_RIGHT_BUTTON) && (state == GLUT_DOWN)){
		zoom = true;
	}
	else{
		orbit = false;
		zoom = false;
	}

}

/* Implements UMousePressedMove Function */
void UMousePressedMove(int x, int y){

	// Immediately replaces center locked coordinates with new mouse coordinates
	if(mouseDetected){
		lastMouseX = x-300;
		lastMouseY = y-50;
		mouseDetected = false;
	}

	// Gets the direction the mouse was moved in x and y
	mouseXOffset = x - lastMouseX;
	mouseYOffset = lastMouseY - y;

	// Updates with new mouse coordinates
	lastMouseX = x;
	lastMouseY = y;

	// Applies sensitivity to the mouse direction
	mouseXOffset *= sensitivity;
	mouseYOffset *= sensitivity;

	/* Orbit Logic */
	if (orbit) {

		// Accumulates the yaw and pitch variables
		yaw += mouseXOffset;
		pitch += mouseYOffset;

		// Orbits around the center
		front.x = 10.0f * cos(yaw);
		front.y = 10.0f * sin(pitch);
		front.z = sin(yaw) * cos(pitch) * 10.0f;

	}

	/* Zoom Logic */
	else if (zoom) {
		if(mouseYOffset > 0){ // Zoom In
			cameraPosition += cameraSpeed * CameraForwardZ * sensitivity;
		}
		else{ // Zoom Out
			cameraPosition -= cameraSpeed * CameraForwardZ * sensitivity;
		}
	}


}





