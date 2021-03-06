#include "synthizer/c_api.hpp"
#include "synthizer/context.hpp"
#include "synthizer/logging.hpp"
#include "synthizer/math.hpp"
#include "synthizer/sources.hpp"
#include "synthizer/spatialization_math.hpp"

#include <cmath>

namespace synthizer {

Source3D::Source3D(std::shared_ptr<Context> context): PannedSource(context) {
}

void Source3D::initInAudioThread() {
	PannedSource::initInAudioThread();
	this->setDistanceParams(context->getDistanceParams());
}

std::array<double, 3> Source3D::getPosition() {
	return this->position;
}

void Source3D::setPosition(std::array<double, 3> position) {
		this->position = position;
}

std::array<double, 6> Source3D::getOrientation() {
	return this->orientation;
}

void Source3D::setOrientation(std::array<double, 6> orientation) {
	Vec3d at = { orientation[0], orientation[1], orientation[2] };
	Vec3d up = { orientation[3], orientation[4], orientation[5] };
	throwIfParallel(at, up);
	this->orientation = orientation;
}

void Source3D::run() {
	auto ctx = this->getContext();
	auto listener_pos = ctx->getPosition();
	auto listener_orient = ctx->getOrientation();
	Vec3d listener_at = { listener_orient[0], listener_orient[1], listener_orient[2] };
	Vec3d listener_up = { listener_orient[3], listener_orient[4], listener_orient[5] };

	Vec3d pos = { this->position[0] - listener_pos[0], this->position[1] - listener_pos[1], this->position[2] - listener_pos[2] };
	Vec3d at = normalize(listener_at);
	Vec3d right = normalize(crossProduct(listener_at, listener_up));
	Vec3d up = crossProduct(right, at);

	/* Use the above to go to a coordinate system where positive y is forward, positive x is right, positive z is up. */
	double y = dotProduct(at, pos);
	double x = dotProduct(right, pos);
	double z = dotProduct(up, pos);

	/* Now get spherical coordinates. */
	double dist = magnitude(pos);
	if (dist == 0) {
		/* Source is at the center of the head. Arbitrarily decide on forward. */
		x = 0;
		y = 1;
		z = 0;
	} else {
		x /= dist;
		y /= dist;
		z /= dist;
	}
	/* Remember: this is clockwise of north and atan2 is -pi to pi. */
	double azimuth = std::atan2(x, y);
	double elevation = std::atan2(z, std::sqrt(x * x + y * y));

	azimuth = std::fmod(azimuth * 180 / PI + 360, 360.0);
	this->setAzimuth(clamp(azimuth, 0.0, 360.0));
	elevation = clamp(elevation * 180 / PI, -90.0, 90.0);
	this->setElevation(elevation);
	auto &dp = this->getDistanceParams();
	dp.distance = dist;
	this->setGain3D(mulFromDistanceParams(dp));
	assert(azimuth >= 0.0);
	PannedSource::run();
}

}

#define PROPERTY_CLASS Source3D
#define PROPERTY_BASE Source
#define PROPERTY_LIST SOURCE3D_PROPERTIES
#include "synthizer/property_impl.hpp"

using namespace synthizer;

SYZ_CAPI syz_ErrorCode syz_createSource3D(syz_Handle *out, syz_Handle context) {
	SYZ_PROLOGUE
	auto ctx = fromC<Context>(context);
	auto ret = ctx->createObject<Source3D>();
	std::shared_ptr<Source> src_ptr = ret;
	ctx->registerSource(src_ptr);
	*out = toC(ret);
	return 0;
	SYZ_EPILOGUE
}
