#include <string.h>
#include <stdio.h>
#include <GLee.h>
#include <GL/glut.h>

#include <math/color.h>

#include <glutpp/free.h>
#include <glutpp/window.h>

//Size of shadow map
const int shadowMapSize = 512;//512;

glutpp::window::window(int setWidth, int setHeight,
		int setInitPositionX, int setInitPositionY,
		const char * title )
{
	width  = setWidth;               
	height = setHeight;

	initPositionX = setInitPositionX;
	initPositionY = setInitPositionY;

	glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE);
	glutInitWindowSize(width, height);
	glutInitWindowPosition(initPositionX, initPositionY);

	glutpp::__master.CallGlutCreateWindow( (char *)title, this );

	glViewport(0,0,width,height);
	// implement ortho projection in math::mat44

	//Check for necessary extensions
	if(!GLEE_ARB_depth_texture || !GLEE_ARB_shadow)
	{
		printf("I require ARB_depth_texture and ARB_shadow extensionsn\n");
		exit(0);//return false;
	}

	//Load identity modelview
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	//Shading states
	glShadeModel(GL_SMOOTH);
	//glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	//glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

	//Depth states
	glClearDepth(1.0f);
	glDepthFunc(GL_LEQUAL);
	glEnable(GL_DEPTH_TEST);

	glEnable(GL_CULL_FACE);

	//We use glScale when drawing the scene
	glEnable(GL_NORMALIZE);

	//Create the shadow map texture
	texture_shadow_map_.init(512,512);

	//Use the color as the ambient and diffuse material
	glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
	glEnable(GL_COLOR_MATERIAL);

	//White specular material color, shininess 16
	glMaterialfv(GL_FRONT, GL_SPECULAR, math::white);
	glMaterialf(GL_FRONT, GL_SHININESS, 16.0f);

	//Calculate & save matrices
	//camera_.pos = 
	//matrix(cam.pos, math::vec3(0.0f,0.0f,0.0f), math::vec3(0.0f,1.0f,0.0f));
	
	light_.camera_.eye_ = math::vec3(0,0,-10);
	light_.camera_.update_matrix();
}
glutpp::window::~window()
{
	glutDestroyWindow(windowID);
}
void glutpp::window::CallBackDisplayFunc(void)
{
	if( flags_ & SHADOWS )
	{
		//First pass - from light's point of view
		glClear(GL_COLOR_BUFFER_BIT);
		glClear(GL_DEPTH_BUFFER_BIT);
		
		glMatrixMode(GL_PROJECTION);
		glLoadMatrixf(light_.camera_.proj_);
		
		glMatrixMode(GL_MODELVIEW);
		glLoadMatrixf(light_.camera_.view_);
		
		//Use viewport the same size as the shadow map
		glViewport(0, 0, shadowMapSize, shadowMapSize);

		//Draw back faces into the shadow map
		glCullFace(GL_FRONT);

		//Disable color writes, and use flat shading for speed
		glShadeModel(GL_FLAT);
		glColorMask(0, 0, 0, 0);

		//Draw the scene
		//DrawScene(angle);
		Display();

		//Read the depth buffer into the shadow map texture
		texture_shadow_map_.bind();
		glCopyTexSubImage2D(
				GL_TEXTURE_2D,
				0, 0, 0, 0, 0,
				shadowMapSize, shadowMapSize);

		//restore states
		glCullFace(GL_BACK);
		glShadeModel(GL_SMOOTH);
		glColorMask(1, 1, 1, 1);
	}



	//2nd pass - Draw from camera's point of view
	glClear(GL_DEPTH_BUFFER_BIT);
	glClear(GL_COLOR_BUFFER_BIT);//me
	
	glMatrixMode(GL_PROJECTION);
	glLoadMatrixf(camera_.proj_);
	
	glMatrixMode(GL_MODELVIEW);
	glLoadMatrixf(camera_.view_);
	
	glViewport(0, 0, width, height);

	//Use dim light to represent shadowed areas
	glLightfv(GL_LIGHT1, GL_POSITION, math::vec4(light_.camera_.eye_));
	glLightfv(GL_LIGHT1, GL_AMBIENT, math::white*0.2f);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, math::white*0.2f);
	glLightfv(GL_LIGHT1, GL_SPECULAR, math::black);
	glEnable(GL_LIGHT1);
	glEnable(GL_LIGHTING);

	//DrawScene(angle);
	Display();




	//3rd pass
	//Draw with bright light
	glLightfv(GL_LIGHT1, GL_DIFFUSE, math::white);
	glLightfv(GL_LIGHT1, GL_SPECULAR, math::white);


	if( flags_ & SHADOWS )
	{
		//Calculate texture matrix for projection
		//This matrix takes us from eye space to the light's clip space
		//It is postmultiplied by the inverse of the current view matrix when specifying texgen
		static math::mat44 biasMatrix(0.5f, 0.0f, 0.0f, 0.0f,
				0.0f, 0.5f, 0.0f, 0.0f,
				0.0f, 0.0f, 0.5f, 0.0f,
				0.5f, 0.5f, 0.5f, 1.0f);	//bias from [-1, 1] to [0, 1]

		math::mat44 textureMatrix = biasMatrix * light_.camera_.proj_ * light_.camera_.view_;

		//Set up texture coordinate generation.
		glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_EYE_LINEAR);
		glTexGenfv(GL_S, GL_EYE_PLANE, textureMatrix.GetRow(0));
		glEnable(GL_TEXTURE_GEN_S);

		glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, GL_EYE_LINEAR);
		glTexGenfv(GL_T, GL_EYE_PLANE, textureMatrix.GetRow(1));
		glEnable(GL_TEXTURE_GEN_T);

		glTexGeni(GL_R, GL_TEXTURE_GEN_MODE, GL_EYE_LINEAR);
		glTexGenfv(GL_R, GL_EYE_PLANE, textureMatrix.GetRow(2));
		glEnable(GL_TEXTURE_GEN_R);

		glTexGeni(GL_Q, GL_TEXTURE_GEN_MODE, GL_EYE_LINEAR);
		glTexGenfv(GL_Q, GL_EYE_PLANE, textureMatrix.GetRow(3));
		glEnable(GL_TEXTURE_GEN_Q);

		//Bind & enable shadow map texture
		texture_shadow_map_.bind();
		glEnable(GL_TEXTURE_2D);
		
		//Enable shadow comparison
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_COMPARE_MODE_ARB, GL_COMPARE_R_TO_TEXTURE);
		
		//Shadow comparison should be true (ie not in shadow) if r<=texture
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_COMPARE_FUNC_ARB, GL_LEQUAL);

		//Shadow comparison should generate an INTENSITY result
		glTexParameteri(GL_TEXTURE_2D, GL_DEPTH_TEXTURE_MODE_ARB, GL_INTENSITY);

		//Set alpha test to discard false comparisons
		glAlphaFunc(GL_GEQUAL, 0.99f);
		glEnable(GL_ALPHA_TEST);
	}

	//DrawScene(angle);
	Display();

	//Disable textures and texgen
	glDisable(GL_TEXTURE_2D);

	glDisable(GL_TEXTURE_GEN_S);
	glDisable(GL_TEXTURE_GEN_T);
	glDisable(GL_TEXTURE_GEN_R);
	glDisable(GL_TEXTURE_GEN_Q);

	//Restore other states
	glDisable(GL_LIGHTING);
	glDisable(GL_ALPHA_TEST);

	if( flags_ & ORTHO)
	{
		//Set matrices for ortho
		glMatrixMode(GL_PROJECTION);
		glPushMatrix();
		glLoadIdentity();
		gluOrtho2D(-1.0f, 1.0f, -1.0f, 1.0f);

		glMatrixMode(GL_MODELVIEW);
		glPushMatrix();
		glLoadIdentity();


		DisplayOrtho();

		//Print text
		//glRasterPos2f(-1.0f, 0.9f);
		//for(unsigned int i=0; i<strlen(fpsString); ++i)
		//	glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, fpsString[i]);

		//reset matrices
		glMatrixMode(GL_PROJECTION);
		glPopMatrix();
		glMatrixMode(GL_MODELVIEW);
		glPopMatrix();
	}

	glFinish();
	glutSwapBuffers();
	glutPostRedisplay();

}
void glutpp::window::Reshape()
{
	glViewport(0,0,width,height);
	
	camera_.proj_.SetPerspective(45.0f, (float)width / (float)height, 1.0f, 100.0f);
	
	CallBackDisplayFunc();
}
void glutpp::window::CallBackReshapeFunc(int w, int h)
{
	width = w;
	height= h;

	Reshape();

	CallBackDisplayFunc();
}
void glutpp::window::CallBackIdleFunc(void)
{
	Idle();

	CallBackDisplayFunc();
}
void glutpp::window::StartSpinning()
{
	glutpp::__master.SetIdleToCurrentWindow();
	glutpp::__master.EnableIdleFunction();
}
void glutpp::window::CallBackKeyboardFunc(unsigned char key, int x, int y)
{
	printf("%s\n",__FUNCTION__);

	switch(key)
	{
		case 's':
			flags_ &= !SHADOWS;
			break;
		case 'o':
			flags_ &= !ORTHO;
			break;

	}


	//key; x; y;                //dummy function
}
void glutpp::window::CallBackMotionFunc(int x, int y)
{
	//x; y;                     //dummy function
}
void glutpp::window::CallBackMouseFunc(int button, int state, int x, int y)
{
	//button; state; x; y;      //dummy function
}
void glutpp::window::CallBackPassiveMotionFunc(int x, int y)
{
	//x; y;                     //dummy function
}
void glutpp::window::CallBackSpecialFunc(int key, int x, int y)
{
	//key; x; y;
}   
void glutpp::window::CallBackVisibilityFunc(int visible)
{
	//visible;                  //dummy function
}
void glutpp::window::SetWindowID(int newWindowID)
{
	windowID = newWindowID;
}
int glutpp::window::GetWindowID(void)
{
	return( windowID );
}

void glutpp::window::Display()
{}   
void glutpp::window::DisplayOrtho()
{}   
void glutpp::window::Idle()
{}   







