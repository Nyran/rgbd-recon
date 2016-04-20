



#ifndef H_MVT_PRIMITIVES
#define H_MVT_PRIMITIVES



/// gloost system includes
#include <gloostConfig.h>
#include <gloostMath.h>


/// cpp includes
#include <string>
#include <GL/glew.h>



namespace mvt
{


  //  singleton, draws primitives like Quad and QuadCenter

class GlPrimitives
{
	public:


    // returns the instance of this class
    static GlPrimitives* get();


    // class destructor
    virtual ~GlPrimitives();


    // draws the draws a quad with texCoord from 0.0 .. 1.0
    void drawQuad();

    // draws the draws a quad with texCoord from -0.5 .. 0.5
    void drawQuadCenter();


    void drawCoords();
    void drawCoords2();

	protected:

    // class constructor
    GlPrimitives();

    // inits the ProxyPointsGrid
    void init();

    static GlPrimitives* _instance;

    GLuint       _quadDisplayListHandle;
    GLuint       _quadCenterDisplayListHandle;
    GLuint       _coordsDisplayListHandle;
    GLuint       _coordsDisplayListHandle2;

};


} // namespace mvt


#endif // H_MVT_PRIMITIVES


