

#include "ProxyMeshGridV2.h"



/// cpp includes
#include <string>
#include <iostream>
#include <vector>


namespace{
  struct vertex{
    float data[3];
  };
}

namespace mvt
{

/**
  \class ProxyMeshGridV2

  \brief Generates and renders a resH x resV mesh - normalized

  \author Stephan Beck
  \date   April 2011
  \remarks
*/

////////////////////////////////////////////////////////////////////////////////


/**
  \brief Class constructor
  \remarks ...
*/

ProxyMeshGridV2::ProxyMeshGridV2(unsigned int resH,
                             unsigned int resV):
  _resH(resH),
  _resV(resV),
  _displayListHandle(0),
  _displayListHandles(),
  _vboHandle(0),
  _numvertices(0)
{

}


////////////////////////////////////////////////////////////////////////////////


/**
   \brief Class destructor
*/

ProxyMeshGridV2::~ProxyMeshGridV2()
{
  if(_displayListHandle)
    glDeleteLists(_displayListHandle, 1);
  if(_vboHandle)
    glDeleteBuffersARB(1, &_vboHandle);

  for(unsigned i = 0; i < _displayListHandles.size(); ++i){
    glDeleteLists(_displayListHandles[i], 1);
  }

}


////////////////////////////////////////////////////////////////////////////////


/**
  \brief inits the ProxyMeshGridV2
*/

void
ProxyMeshGridV2::init()
{
  
  const float stepX = 1.0f/_resH;
  const float stepY = 1.0f/_resV;

#if 0
  std::vector<vertex> vertices;
  vertex v;
  v.data[2] = 0.0;
  int y = 0;
  while(y < (_resV - 1)){
	if(y % 2 == 0){
                int x = 0;
		for(; x < _resH; ++x){
		  
		  v.data[0] = (x+0.5) * stepX;
		  v.data[1] = (y + 0.5) * stepY;
		  vertices.push_back(v);
		  v.data[0] = (x+0.5) * stepX;
		  v.data[1] = (y + 1.5) * stepY;
		  vertices.push_back(v);
		}
		if(y < (_resV - 2)){
		  v.data[0] = (x+0.5) * stepX;
		  v.data[1] = (y + 1.5) * stepY;
		  vertices.push_back(v);
		  v.data[0] = (x+0.5) * stepX;
		  v.data[1] = (y + 1.5) * stepY;
		  vertices.push_back(v);
		}
	}
	else{
		int x = _resH - 1;
		for(; x >= 0; --x){

		  v.data[0] = (x+0.5) * stepX;
		  v.data[1] = (y + 0.5) * stepY;
		  vertices.push_back(v);
		  v.data[0] = (x+0.5) * stepX;
		  v.data[1] = (y + 1.5) * stepY;
		  vertices.push_back(v);
		}
		if(y < (_resV - 2)){
		  v.data[0] = (x+0.5) * stepX;
		  v.data[1] = (y + 1.5) * stepY;
		  vertices.push_back(v);
		  v.data[0] = (x+0.5) * stepX;
		  v.data[1] = (y + 1.5) * stepY;
		  vertices.push_back(v);
		}
	}
	++y;

  }
  glGenBuffers(1, &_vboHandle);
  glBindBuffer(GL_ARRAY_BUFFER, _vboHandle);
  glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(vertex) , vertices.front().data, GL_STATIC_DRAW);
  glBindBuffer(GL_ARRAY_BUFFER, 0);
  _numvertices = vertices.size();
  std::cerr << "ProxyMeshGridV2 init: " << _numvertices << std::endl;
  return;
#endif  

  _displayListHandle = glGenLists(1);
  glNewList(_displayListHandle, GL_COMPILE);

#if 0
  glBegin( GL_TRIANGLE_STRIP );
  int y = 0;
  while(y < (_resV - 1)){
	if(y % 2 == 0){
                int x = 0;
		for(; x < _resH; ++x){
		     glVertex2f( (x+0.5) * stepX, (y + 0.5) * stepY );
		     glVertex2f( (x+0.5) * stepX, (y + 1.5) * stepY );
		}
		if(y < (_resV - 2)){
		  glVertex2f( (x+0.5) * stepX, (y + 1.5) * stepY );
		  glVertex2f( (x+0.5) * stepX, (y + 1.5) * stepY );
		}
	}
	else{
		int x = _resH - 1;
		for(; x >= 0; --x){
		     glVertex2f( (x+0.5) * stepX, (y + 0.5) * stepY );
		     glVertex2f( (x+0.5) * stepX, (y + 1.5) * stepY );
		}
		if(y < (_resV - 2)){
		  glVertex2f( (x+0.5) * stepX, (y + 1.5) * stepY );
		  glVertex2f( (x+0.5) * stepX, (y + 1.5) * stepY );
		}
	}
	++y;

  }
  glEnd();
#endif


#if 1
  glBegin( GL_TRIANGLES );
  for(unsigned y = 0; y < _resV; ++y){
    for(unsigned x = 0; x < _resH; ++x){
      glVertex2f( (x+0.5) * stepX, (y + 0.5) * stepY );
      glVertex2f( (x+1.5) * stepX, (y + 0.5) * stepY );
      glVertex2f( (x+0.5) * stepX, (y + 1.5) * stepY );

      glVertex2f( (x+1.5) * stepX, (y + 0.5) * stepY );
      glVertex2f( (x+1.5) * stepX, (y + 1.5) * stepY );
      glVertex2f( (x+0.5) * stepX, (y + 1.5) * stepY );

    }
  }
  glEnd();
#endif

  glEndList();


  

}

////////////////////////////////////////////////////////////////////////////////


/**
  \brief inits the ProxyMeshGridV2
*/

void
ProxyMeshGridV2::inits(){
  unsigned res = 1;
  while( ((_resH/res)%2 == 0) &&  ((_resV/res)%2 == 0) ){
    
    int resH = _resH/res;
    int resV = _resV/res;
    res <<= 1;
    std::cerr << this << " ProxyMeshGridV2::inits() constructing " << resH << "x" << resV <<  std::endl;


    const float stepX = 1.0f/resH;
    const float stepY = 1.0f/resV;
    unsigned tmpid = glGenLists(1);
    _displayListHandles.push_back(tmpid);
    glNewList(tmpid, GL_COMPILE);
    glBegin( GL_TRIANGLE_STRIP );
    int y = 0;
    while(y < (resV - 1)){
      if(y % 2 == 0){
	int x = 0;
	for(; x < resH; ++x){
	  glVertex2f( (x+0.5) * stepX, (y + 0.5) * stepY );
	  glVertex2f( (x+0.5) * stepX, (y + 1.5) * stepY );
	}
	if(y < (resV - 2)){
	  glVertex2f( (x+0.5) * stepX, (y + 1.5) * stepY );
	  glVertex2f( (x+0.5) * stepX, (y + 1.5) * stepY );
	}
      }
      else{
	int x = resH - 1;
	for(; x >= 0; --x){
	  glVertex2f( (x+0.5) * stepX, (y + 0.5) * stepY );
	  glVertex2f( (x+0.5) * stepX, (y + 1.5) * stepY );
	}
	if(y < (resV - 2)){
	  glVertex2f( (x+0.5) * stepX, (y + 1.5) * stepY );
	  glVertex2f( (x+0.5) * stepX, (y + 1.5) * stepY );
	}
      }
      ++y;
    }
    glEnd();
    glEndList();
  }

}



////////////////////////////////////////////////////////////////////////////////


/**
   \brief draws the ProxyMeshGridV2
*/

void
ProxyMeshGridV2::draw(float lod)
{


#if 0 // does not work good until now
  if (0 == _displayListHandles.size())
  {
    inits();
  }
  const unsigned lods = _displayListHandles.size();
  unsigned num = std::min(lods - 1, (unsigned) std::floor(lods * ( (std::max(1.0f - lod, 0.0f)))));
  //  std::cerr << "ProxyMeshGridV2::draw: " << lods << " " << lod << " " << num << std::endl;

  glCallList(_displayListHandles[num]);
  return;
#endif


#if 1
  if (!_displayListHandle)
  {
    init();
  }
  glCallList(_displayListHandle);
  return;
#endif

#if 0
  if (!_vboHandle)
  {
    init();
  }
  else{
    std::cerr << "ProxyMeshGridV2 init: " <<_numvertices << std::endl;
    glBindBuffer(GL_ARRAY_BUFFER, _vboHandle);
    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(3, GL_FLOAT, 0, 0);
    glDrawArrays(GL_TRIANGLE_STRIP, 0, _numvertices);
    
    glDisableClientState(GL_VERTEX_ARRAY);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
  }
#endif
}


////////////////////////////////////////////////////////////////////////////////


/**
   \brief returns horizontal resolution of the grid
*/

unsigned int
ProxyMeshGridV2::getResH() const
{
  return _resH;
}


////////////////////////////////////////////////////////////////////////////////


/**
   \brief returns vertical resolution of the grid
*/

unsigned int
ProxyMeshGridV2::getResV() const
{
  return _resV;
}


////////////////////////////////////////////////////////////////////////////////





} // namespace mvt


