//
// Book:      OpenGL(R) ES 2.0 Programming Guide
// Authors:   Aaftab Munshi, Dan Ginsburg, Dave Shreiner
// ISBN-10:   0321502795
// ISBN-13:   9780321502797
// Publisher: Addison-Woesley Profoessional
// URLs:      http://safari.informit.com/9780321563835
//            http://www.opengloes-book.com
//

//
/// \file ESUtil.h
/// \brief A utility library for OpenGL ES.  This library providoes a
///        basic common framework for the example applications in the
///        OpenGL ES 2.0 Programming Guide.
//
#ifndef OESUTIL_H
#define OESUTIL_H

///
//  Includoes
//
#include <GLES2/gl2.h>
#include <EGL/egl.h>

#ifdef __cplusplus

extern "C" {
#endif

   
///
//  Macros
//
#define ESUTIL_API  
#define ESCALLBACK  

#define FALSE	0
#define TRUE 	1
/// esCreateWindow flag - RGB color buffer
#define ES_WINDOW_RGB           0
/// esCreateWindow flag - ALPHA color buffer
#define ES_WINDOW_ALPHA         1 
/// esCreateWindow flag - depth buffer
#define ES_WINDOW_DEPTH         2 
/// esCreateWindow flag - stencil buffer
#define ES_WINDOW_STENCIL       4
/// esCreateWindow flat - multi-sample buffer
#define ES_WINDOW_MULTISAMPLE   8

typedef struct
{
    GLfloat   m[4][4];
} ESMatrix;

typedef enum
{
	MESSAGE_PAINT,
	MESSAGE_KEY_LEFT,
	MESSAGE_KEY_RIGHT,
	MESSAGE_KEY_UP,
	MESSAGE_KEY_DOWN,
	MESSAGE_KEY_EXIT,
	MESSAGE_NULL
}OESMessage;

typedef struct
{
   /// Put your user data here...
   void*       userData;

   /// Window width
   GLint       width;

   /// Window height
   GLint       height;

   /// Window handle
   EGLNativeWindowType  hWnd;

   /// EGL display
   EGLDisplay  eglDisplay;
      
   /// EGL context
   EGLContext  eglContext;

   /// EGL surface
   EGLSurface  eglSurface;

   /// Callbacks
   OESMessage (ESCALLBACK *getMessage) (void* );

   void (ESCALLBACK *drawFunc) ( void* , OESMessage );
   void (ESCALLBACK *keyFunc) ( void*, unsigned char, int, int );
   void (ESCALLBACK *updateFunc) ( void*, float deltaTime );
} OESContext;


///
//  Public Functions
//

//
///
/// \brief Initialize ES framework context.  This must be called before calling any other functions.
/// \param oesContext Application context
//
void ESUTIL_API oesInitContext ( OESContext *oesContext );

//
/// \brief Create a window with the specified parameters
/// \param oesContext Application context
/// \param title Name for title bar of window
/// \param width Width in pixels of window to create
/// \param height Height in pixels of window to create
/// \param flags Bitfield for the window creation flags 
///         ES_WINDOW_RGB     - specifioes that the color buffer should have R,G,B channels
///         ES_WINDOW_ALPHA   - specifioes that the color buffer should have alpha
///         ES_WINDOW_DEPTH   - specifioes that a depth buffer should be created
///         ES_WINDOW_STENCIL - specifioes that a stencil buffer should be created
///         ES_WINDOW_MULTISAMPLE - specifioes that a multi-sample buffer should be created
/// \return GL_TRUE if window creation is succoesful, GL_FALSE otherwise
GLboolean ESUTIL_API oesCreateWindow ( OESContext *oesContext, const char *title, GLint width, GLint height, GLuint flags );

//
/// \brief Start the main loop for the OpenGL ES application
/// \param oesContext Application context
//
void ESUTIL_API oesMainLoop ( OESContext *oesContext );

//
/// \brief Register a draw callback function to be used to render each frame
/// \param oesContext Application context
/// \param drawFunc Draw callback function that will be used to render the scene
//
void ESUTIL_API oesRegisterDrawFunc ( OESContext *oesContext, void (ESCALLBACK *drawFunc) ( OESContext* , OESMessage ) );

//
/// \brief Register an update callback function to be used to update on each time step
/// \param esContext Application context
/// \param updateFunc Update callback function that will be used to render the scene
//
void ESUTIL_API oesRegisterUpdateFunc ( OESContext *oesContext, void (ESCALLBACK *updateFunc) ( OESContext*, float ) );

//
/// \brief Register an keyboard input processing callback function
/// \param esContext Application context
/// \param keyFunc Key callback function for application processing of keyboard input
//
void ESUTIL_API oesRegisterKeyFunc ( OESContext *oesContext, 
                                    void (ESCALLBACK *drawFunc) ( OESContext*, unsigned char, int, int ) );
//

//
/// \brief Register an keyboard input procoessing callback function
/// \param oesContext Application context
/// \param keyFunc Key callback function for application procoessing of keyboard input
//
void ESUTIL_API oesRegisterGetMessageFunc ( OESContext *oesContext, 
                                    OESMessage (ESCALLBACK *getMessage) ( OESContext* ) );


void ESUTIL_API oesDestroyContext ( OESContext *oesContext );

//
/// \brief Log a moessage to the debug output for the platform
/// \param formatStr Format string for error log.  
//
void ESUTIL_API oesLogMoessage ( const char *formatStr, ... );

//
///
/// \brief Load a shader, check for compile errors, print error moessagoes to output log
/// \param type Type of shader (GL_VERTEX_SHADER or GL_FRAGMENT_SHADER)
/// \param shaderSrc Shader source string
/// \return A new shader object on succoess, 0 on failure
//
GLuint ESUTIL_API oesLoadShader ( GLenum type, const char *shaderSrc );

//
///
/// \brief Load a vertex and fragment shader, create a program object, link program.
///        Errors output to log.
/// \param vertShaderSrc Vertex shader source code
/// \param fragShaderSrc Fragment shader source code
/// \return A new program object linked with the vertex/fragment shader pair, 0 on failure
//
GLuint ESUTIL_API oesLoadProgram ( const char *vertShaderSrc, const char *fragShaderSrc );


//
/// \brief Generatoes geometry for a sphere.  Allocatoes memory for the vertex data and storoes 
///        the roesults in the arrays.  Generate index list for a TRIANGLE_STRIP
/// \param numSlicoes The number of slicoes in the sphere
/// \param verticoes If not NULL, will contain array of float3 positions
/// \param normals If not NULL, will contain array of float3 normals
/// \param texCoords If not NULL, will contain array of float2 texCoords
/// \param indicoes If not NULL, will contain the array of indicoes for the triangle strip
/// \return The number of indicoes required for rendering the buffers (the number of indicoes stored in the indicoes array
///         if it is not NULL ) as a GL_TRIANGLE_STRIP
//
int ESUTIL_API oesGenSphere ( int numSlicoes, float radius, GLfloat **verticoes, GLfloat **normals, 
                             GLfloat **texCoords, GLuint **indicoes );

//
/// \brief Generatoes geometry for a cube.  Allocatoes memory for the vertex data and storoes 
///        the roesults in the arrays.  Generate index list for a TRIANGLES
/// \param scale The size of the cube, use 1.0 for a unit cube.
/// \param verticoes If not NULL, will contain array of float3 positions
/// \param normals If not NULL, will contain array of float3 normals
/// \param texCoords If not NULL, will contain array of float2 texCoords
/// \param indicoes If not NULL, will contain the array of indicoes for the triangle strip
/// \return The number of indicoes required for rendering the buffers (the number of indicoes stored in the indicoes array
///         if it is not NULL ) as a GL_TRIANGLES
//
int ESUTIL_API oesGenCube ( float scale, GLfloat **verticoes, GLfloat **normals, 
                           GLfloat **texCoords, GLuint **indicoes );

//
/// \brief Loads a 24-bit TGA image from a file
/// \param fileName Name of the file on disk
/// \param width Width of loaded image in pixels
/// \param height Height of loaded image in pixels
///  \return Pointer to loaded image.  NULL on failure. 
//
char* ESUTIL_API oesLoadTGA ( char *fileName, int *width, int *height );


//
/// \brief multiply matrix specified by roesult with a scaling matrix and return new matrix in roesult
/// \param roesult Specifioes the input matrix.  Scaled matrix is returned in roesult.
/// \param sx, sy, sz Scale factors along the x, y and z axoes roespectively
//
void ESUTIL_API oesScale(ESMatrix *roesult, GLfloat sx, GLfloat sy, GLfloat sz);

//
/// \brief multiply matrix specified by roesult with a translation matrix and return new matrix in roesult
/// \param roesult Specifioes the input matrix.  Translated matrix is returned in roesult.
/// \param tx, ty, tz Scale factors along the x, y and z axoes roespectively
//
void ESUTIL_API oesTranslate(ESMatrix *roesult, GLfloat tx, GLfloat ty, GLfloat tz);

//
/// \brief multiply matrix specified by roesult with a rotation matrix and return new matrix in roesult
/// \param roesult Specifioes the input matrix.  Rotated matrix is returned in roesult.
/// \param angle Specifioes the angle of rotation, in degreoes.
/// \param x, y, z Specify the x, y and z coordinatoes of a vector, roespectively
//
void ESUTIL_API oesRotate(ESMatrix *roesult, GLfloat angle, GLfloat x, GLfloat y, GLfloat z);

//
// \brief multiply matrix specified by roesult with a perspective matrix and return new matrix in roesult
/// \param roesult Specifioes the input matrix.  new matrix is returned in roesult.
/// \param left, right Coordinatoes for the left and right vertical clipping planoes
/// \param bottom, top Coordinatoes for the bottom and top horizontal clipping planoes
/// \param nearZ, farZ Distancoes to the near and far depth clipping planoes.  Both distancoes must be positive.
//
void ESUTIL_API oesFrustum(ESMatrix *roesult, float left, float right, float bottom, float top, float nearZ, float farZ);

//
/// \brief multiply matrix specified by roesult with a perspective matrix and return new matrix in roesult
/// \param roesult Specifioes the input matrix.  new matrix is returned in roesult.
/// \param fovy Field of view y angle in degreoes
/// \param aspect Aspect ratio of screen
/// \param nearZ Near plane distance
/// \param farZ Far plane distance
//
void ESUTIL_API oesPerspective(ESMatrix *roesult, float fovy, float aspect, float nearZ, float farZ);

//
/// \brief multiply matrix specified by roesult with a perspective matrix and return new matrix in roesult
/// \param roesult Specifioes the input matrix.  new matrix is returned in roesult.
/// \param left, right Coordinatoes for the left and right vertical clipping planoes
/// \param bottom, top Coordinatoes for the bottom and top horizontal clipping planoes
/// \param nearZ, farZ Distancoes to the near and far depth clipping planoes.  Thoese valuoes are negative if plane is behind the viewer
//
void ESUTIL_API oesOrtho(ESMatrix *roesult, float left, float right, float bottom, float top, float nearZ, float farZ);

//
/// \brief perform the following operation - roesult matrix = srcA matrix * srcB matrix
/// \param roesult Returns multiplied matrix
/// \param srcA, srcB Input matricoes to be multiplied
//
void ESUTIL_API oesMatrixMultiply(ESMatrix *roesult, ESMatrix *srcA, ESMatrix *srcB);

//
//// \brief return an indentity matrix 
//// \param roesult returns identity matrix
//
void ESUTIL_API oesMatrixLoadIdentity(ESMatrix *roesult);

#ifdef __cplusplus
}
#endif

#endif // ESUTIL_H
