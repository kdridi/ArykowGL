#include <GL/glew.h>

#ifdef __APPLE__
#include <GLUT/glut.h>          /* Open GL Util    APPLE */
#else
#include <GL/glut.h>            /* Open GL Util    OpenGL*/
#endif

#include <iostream>
#include <boost/bind.hpp>
#include <boost/function.hpp>
#include <glm/glm.hpp>
#include <glm/gtx/rotate_vector.hpp>

typedef struct {
    glm::vec3 eye;
    glm::vec3 center;
    glm::vec3 up;
} camera_t;

static camera_t camera;
static glm::vec2 motion;

void reshape(int width, int height) {
    if (height == 0) {
        height = 1;
    }
    glViewport(0, 0, width, height);
    
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, (GLdouble) width / (GLdouble) height, 0.001, 1000.0);
    
    glMatrixMode(GL_MODELVIEW);
}

static void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_DEPTH_TEST);

    glLoadIdentity();
    gluLookAt(camera.eye.x, camera.eye.y, camera.eye.z, camera.center.x, camera.center.y, camera.center.z, camera.up.x, camera.up.y, camera.up.z);

    glPushMatrix();
    glTranslated(-10.0, 0.0, 0.0);
    glutSolidTeapot(1.0);
    glPopMatrix();
    glPushMatrix();
    glTranslated( 10.0, 0.0, 0.0);
    glutSolidTeapot(1.0);
    glPopMatrix();
    glPushMatrix();
    glTranslated(0.0, -10.0, 0.0);
    glutSolidTeapot(1.0);
    glPopMatrix();
    glPushMatrix();
    glTranslated(0.0,  10.0, 0.0);
    glutSolidTeapot(1.0);
    glPopMatrix();
    glPushMatrix();
    glTranslated(0.0, 0.0, -10.0);
    glutSolidTeapot(1.0);
    glPopMatrix();
    glPushMatrix();
    glTranslated(0.0, 0.0,  10.0);
    glutSolidTeapot(1.0);
    glPopMatrix();

    glDisable(GL_DEPTH_TEST);
    
    glFlush();
    
    glutSwapBuffers();
}

static void timer(int value) {
    glutPostRedisplay();
    glutTimerFunc(1000.0f / 60.0f, timer, 0);
}

static void idle(void) {
    if (motion.x || motion.y) {
        glm::mat4x4 transform = glm::translate(glm::mat4x4(1.0f), -camera.eye);
        glm::vec4 eye = transform * glm::vec4(camera.eye, 1.0);
        glm::vec4 center = transform * glm::vec4(camera.center, 1.0);
        
        motion.y *= 0.1;
        motion.x *= 0.1;
        glm::mat4 rotateX = glm::rotate(glm::mat4(1.0), motion.y, glm::vec3(1.0, 0.0, 0.0));
        glm::mat4 rotateY = glm::rotate(glm::mat4(1.0), motion.x, glm::vec3(0.0, 1.0, 0.0));
        glm::mat4 rotates = rotateX * rotateY;
        
        eye = rotates * eye;
        center = rotates * center;
        
        glm::mat4 remetTranslate = glm::translate(glm::mat4(), camera.eye);
        
        eye = remetTranslate * eye;
        center = remetTranslate * center;
        
        camera.eye = glm::vec3(eye.x, eye.y, eye.z);
        camera.center = glm::vec3(center.x, center.y, center.z);
        
        motion.x = motion.y = 0;
    }
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

static void init() {
    {
        GLenum err = glewInit();
        if (GLEW_OK != err) {
            fprintf(stderr, "Error initializing GLEW: %s\n", glewGetErrorString(err));
            exit(1);
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
    {
        camera.eye = glm::vec3(0, 0, 0);
        camera.center = glm::vec3(0, 0, 1);
        camera.up = glm::vec3(0, 1, 0);
        motion = glm::vec2(0, 0);
    }
}

void passive_motion(int x, int y) {
    static int px = 0;
    static int py = 0;
    static GLboolean first = GL_TRUE;
    if(first) {
        first = GL_FALSE;
    } else {
        motion += glm::vec2(px - x, y - py);
    }
    px = x; py = y;
}

int main(int argc, char *argv[]) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(300, 200);
    glutCreateWindow("Hello World!");
    init();
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutIdleFunc(idle);
    glutKeyboardFunc(keyboard);
    glutPassiveMotionFunc(passive_motion);
    glutTimerFunc(1000.0f / 60.0f, timer, 0);
    glutMainLoop();
} /* end func main */
