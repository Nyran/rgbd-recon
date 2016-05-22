#include "reconstruction.hpp"

#include "calibration_files.hpp"
#include "CalibVolumes.hpp"

#include <globjects/NamedString.h>
#include <globjects/base/File.h>

namespace kinect{

Reconstruction::Reconstruction(CalibrationFiles const& cfs, CalibVolumes const* cv, gloost::BoundingBox const&  bbox)
 :m_cv(cv)
 ,m_cf(&cfs)
 ,m_tex_width{cfs.getWidth()}
 ,m_tex_height{cfs.getHeight()}
 ,m_num_kinects{cfs.num()}
 ,m_min_length{cfs.minLength()}
 ,m_bbox{bbox}
{
   globjects::NamedString::create("/shading.glsl", new globjects::File("glsl/shading.glsl"));
}

void Reconstruction::reload() {

}

void  Reconstruction::resize(std::size_t width, std::size_t height) {
}

}