/*
 * precision_tracker.h
 *
 *  Created on: May 12, 2014
 *      Author: davheld
 */

#ifndef PRECISION_TRACKER_H_
#define PRECISION_TRACKER_H_

#include <pcl/point_types.h>
#include <pcl/point_cloud.h>

#include "scored_transform.h"
#include "motion_model.h"
#include "adh_tracker3d.h"

class PrecisionTracker {
public:
  PrecisionTracker();
  virtual ~PrecisionTracker();

  void track(
      const pcl::PointCloud<pcl::PointXYZRGB>::ConstPtr& current_points,
      const pcl::PointCloud<pcl::PointXYZRGB>::ConstPtr& previousModel,
      const double horizontal_distance,
      const MotionModel& motion_model,
      ScoredTransforms<ScoredTransformXYZ>* scored_transforms);

  static void computeCentroid(
      const pcl::PointCloud<pcl::PointXYZRGB>::ConstPtr& points,
      Eigen::Vector3f* centroid);

  static Eigen::Matrix4f estimateAlignmentCentroidDiff(
      const pcl::PointCloud<pcl::PointXYZRGB>::ConstPtr& interpolatedColoredPointsPtr,
      const pcl::PointCloud<pcl::PointXYZRGB>::ConstPtr& previousModelPtr);

private:
  void track(
      const pcl::PointCloud<pcl::PointXYZRGB>::ConstPtr& current_points,
      const double max_xy_stepSize,
      const double max_z_stepSize,
      std::pair <double, double> xRange,
      std::pair <double, double> yRange,
      std::pair <double, double> zRange,
      const pcl::PointCloud<pcl::PointXYZRGB>::ConstPtr& prev_points,
      const Eigen::Vector3f &current_points_centroid,
      const MotionModel& motion_model,
      const double down_sample_factor_prev,
      const double horizontal_distance,
      ScoredTransforms<ScoredTransformXYZ>* scored_transforms);

  ADHTracker3d adh_tracker3d_;
  boost::shared_ptr<AlignmentEvaluator> alignment_evaluator_;
};

#endif /* PRECISION_TRACKER_H_ */
