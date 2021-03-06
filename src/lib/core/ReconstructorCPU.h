/* Copyright (C) 
 * 2016 - Tsing Gu
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
 * 
 */
#pragma once
#include "Reconstructor.h"
#include "Log.hpp"
#include <memory>
#include <core/PointCloud.hpp>
namespace SLS
{

// CPU reconstructor
class ReconstructorCPU: public Reconstructor
{
private:
    /*! Reconstruction buckets of cameras
     *
     * In the reconstruction, camera pixels are assigned to different projector pixels. 
     * Generally, one projector pixels contains more than one camera pixel. For each camera, we assign 
     * pixels to projector pixels, and call those projector pixels buckets.
     * ```
     * ProjPixels(Buckets)   Camera pixels
     * +------------------+  +---+---+---+
     * |       0          +->+   |   |   |
     * +------------------+  +-------+---+
     * |       1          +->+   |
     * +------------------+  +----
     * 
     * +------------------+  +---+---+
     * |       n          +->+   |   |
     * +------------------+  +---+---+
     *
     * ```
     * The camera pixels in the same bucket of two different cameras are considered correspondent pixels,
     * depth then can be extracted from those pixels.
     */
    std::vector<std::vector<std::vector<size_t>>> buckets_;//[camIdx][ProjPixelIdx][camPixelIdx]
    void initBuckets();
    void generateBuckets();
public:

    /*! Create a reconstructor with given projector size
    */
    ReconstructorCPU(const size_t projX, const size_t projY): 
        Reconstructor()
    {
            projector_ = new Projector(projX, projY);
    }
    ~ReconstructorCPU() override;

    //Interfaces
    //! Reconstruct point cloud.
    PointCloud reconstruct() override;

    /*! Add a camera to reconstructor\
     *
     * Accepts two camera now.
     */
    void addCamera(Camera *cam) override;
};
} // namespace SLS
