/// \file OrbitalImageCrop.h
///
/// Orbital Image Crop class
///
/// TODO: Write something here

#ifndef __MVP_ORBITALIMAGECROP_H__
#define __MVP_ORBITALIMAGECROP_H__

#include <mvp/OrbitalImageFileDescriptor.pb.h>

#include <vw/Image/ImageView.h>
#include <vw/FileIO/DiskImageView.h>
#include <vw/Camera/PinholeModel.h>

#include <boost/foreach.hpp>

#if MVP_ENABLE_OCTAVE_SUPPORT
#include <vw/Octave/Conversions.h>
#endif

namespace mvp {

class OrbitalImageCrop {
  vw::camera::PinholeModel m_camera;
  vw::ImageView<double> m_image;

  public:
    OrbitalImageCrop(OrbitalImageFileDescriptor const& image_file, vw::BBox2 const& lonlat_bbox) {
      // TODO: Create crops
      m_camera = vw::camera::PinholeModel(image_file.camera_path());
      m_image = vw::DiskImageView<double>(image_file.image_path());
    }

    vw::camera::PinholeModel camera() const {return m_camera;}
    vw::ImageView<double> image() const {return m_image;}
};

struct OrbitalImageCropCollection : public std::vector<OrbitalImageCrop> {
  OrbitalImageCropCollection(google::protobuf::RepeatedPtrField<OrbitalImageFileDescriptor> const& orbital_images, vw::BBox2 const& lonlat_bbox) {
    BOOST_FOREACH(OrbitalImageFileDescriptor const& o, orbital_images) {
      push_back(OrbitalImageCrop(o, lonlat_bbox));
    }
  }
};

#if MVP_ENABLE_OCTAVE_SUPPORT
class OrbitalImageCropOctave {
  ::Matrix m_camera;
  ::Matrix m_image;

  public:
    OrbitalImageCropOctave(OrbitalImageCrop const& oic) :
      m_camera(vw::octave::pinhole_to_octave(oic.camera())),
      m_image(vw::octave::imageview_to_octave(oic.image())) {}

    ::Matrix camera() const {return m_camera;}
    ::Matrix image() const {return m_image;}

    // octave_value_list struct
}
#endif

} // namespace mvp

#endif