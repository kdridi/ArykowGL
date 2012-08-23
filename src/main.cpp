#include <GL/glew.h>

#ifdef __APPLE__
#include <GLUT/glut.h>          /* Open GL Util    APPLE */
#else
#include <GL/glut.h>            /* Open GL Util    OpenGL*/
#endif

#include <iostream>
#include <boost/bind.hpp>
#include <boost/function.hpp>

static void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_DEPTH_TEST);
    
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-2.0, 2.0, -2.0, 2.0, -2.0, 500.0);
    
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(2, 2, 2, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
    glScalef(.005,.005,.005);
    glRotatef(20, 0, 1, 0);
    glRotatef(30, 0, 0, 1);
    glRotatef(5, 1, 0, 0);
    glTranslatef(-300, 0, 0);
    
    glColor3f(1,1,1);
    glutStrokeCharacter(GLUT_STROKE_ROMAN, 'H');
    glutStrokeCharacter(GLUT_STROKE_ROMAN, 'e');
    glutStrokeCharacter(GLUT_STROKE_ROMAN, 'l');
    glutStrokeCharacter(GLUT_STROKE_ROMAN, 'l');
    glutStrokeCharacter(GLUT_STROKE_ROMAN, 'o');
    
    glutStrokeCharacter(GLUT_STROKE_ROMAN, 'W');
    glutStrokeCharacter(GLUT_STROKE_ROMAN, 'o');
    glutStrokeCharacter(GLUT_STROKE_ROMAN, 'r');
    glutStrokeCharacter(GLUT_STROKE_ROMAN, 'l');
    glutStrokeCharacter(GLUT_STROKE_ROMAN, 'd');
    glutStrokeCharacter(GLUT_STROKE_ROMAN, '!');
    glutStrokeCharacter(GLUT_STROKE_ROMAN, '!');
    glutStrokeCharacter(GLUT_STROKE_ROMAN, '!');
    glutStrokeCharacter(GLUT_STROKE_ROMAN, '!');
    
    glutSwapBuffers();
}

static void timer(int value) {
    glutPostRedisplay();
    glutTimerFunc(1000.0f / 60.0f, timer, 0);
}

static void idle(void) {
}

static void keyboard(unsigned char key, int x, int y) {
    switch (key) {
        case 27:
            exit(0);
            break;
        default:
            break;
    }
}

int main(int argc, char *argv[]) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(300, 200);
    glutCreateWindow("Hello World!");  {
        GLenum err = glewInit();
        if (GLEW_OK != err) {
            fprintf(stderr, "Error initializing GLEW: %s\n", glewGetErrorString(err));
            return EXIT_FAILURE;
        }
        printf("GLEW Version            : %s\n", glewGetString(GLEW_VERSION));
    }
    {
        const GLubyte *renderer = glGetString(GL_RENDERER);
        const GLubyte *vendor = glGetString(GL_VENDOR);
        const GLubyte *version = glGetString(GL_VERSION);
        const GLubyte *glslVersion = glGetString(GL_SHADING_LANGUAGE_VERSION);
        GLint major, minor;
        glGetIntegerv(GL_MAJOR_VERSION, &major);
        glGetIntegerv(GL_MINOR_VERSION, &minor);
        printf("GLSL Version            : %s\n", glslVersion);
        printf("GL Vendor               : %s\n", vendor);
        printf("GL Renderer             : %s\n", renderer);
        printf("GL Version (string)     : %s\n", version);
        printf("GL Version (integer)    : %d.%d\n", major, minor);
    }
    {
        const GLubyte *extensions = glGetString(GL_EXTENSIONS);
        printf("GL Extensions           : %s\n", extensions);
    }

    glutDisplayFunc(display);
    glutIdleFunc(idle);
    glutKeyboardFunc(keyboard);
    glutTimerFunc(1000.0f / 60.0f, timer, 0);
    glutMainLoop();
} /* end func main */
