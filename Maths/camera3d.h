#pragma once

namespace maths {

class Camera3D final : public Camera {
	matrix view;
	matrix proj;
	matrix viewProj;
	bool recalculateView = true;
	bool recalculateProj = true;
	bool recalculateViewProj = true;
	float focalLength = 0;
	float _fov = toRadians(60);
	float _near = 0.1f;
	float _far = 100.0f;
public:
	float3 position{0, 1, 0};
	float3 up{0, 1, 0};
	float3 forward{0, 0, 0};
	uint2 windowSize = {};

	inline constexpr float aspectRatio() const { return (float)windowSize.x / windowSize.y; }
	inline constexpr float fov() const { return _fov; }
	inline constexpr float3 focalPoint() const { return position + forward * focalLength; }

	std::string toString() const {
		std::string s =
			"[position=" + position.toString() +
			", up=" + up.toString() +
			", forward=" + forward.toString() +
			"]";
		return s;
	}

	auto& init(const uint2& windowSize, const float3& pos, const float3& up, const float3& focalPoint) {
		this->windowSize  = windowSize;
		this->position    = pos;
		this->up		  = up.normalised();
		this->forward     = (focalPoint-pos).normalised();
		this->focalLength = (focalPoint-pos).length();
        recalculateView = true;
        recalculateProj = true;
        recalculateViewProj = true;
        return *this;
	}
	auto& fovNearFar(float fovInRadians, float nr, float fr) {
		this->_fov = fovInRadians;
		this->_near = nr;
		this->_far = fr;
		recalculateProj = true;
		return *this;
	}
	auto& moveForward(float f) {
		auto dist = forward * f;
		position += dist;
		recalculateView = true;
		return *this;
	}
	auto& movePositionRelative(const float3& newpos) {
		position += newpos;
		recalculateView = true;
		return *this;
	}
    /// Rotate around the Y axis 
    auto& rotateAroundYAxis(float radians) {
        position = position.rotatedAroundY(radians);
        up       = up.rotatedAroundY(radians);
        forward  = forward.rotatedAroundY(radians);
        recalculateView = true;
        return *this;
    }
	/// move focal point up/down (around x plane)
	auto& pitch(float f) {
		auto right = forward.cross(up);
		auto dist  = up * f;
		forward  = (forward + dist).normalised();
		up = right.cross(forward);
		recalculateView = true;
		return *this;
	}
	/// move focal point left/right (around y plane)
	auto& yaw(float f) {
		auto right = forward.cross(up);
		auto dist = right * f;
		forward = (forward + dist).normalised();
		recalculateView = true;
		return *this;
	}
	/// tip (around z plane)
	auto& roll(float f) {
		auto right = forward.cross(up);
		auto dist = right * f;
		up = (up + dist).normalised();
		recalculateView = true;
		return *this;
	}
	const matrix& V() final override {
		if(recalculateView) {

			view = matrix::lookAtRH(position, focalPoint(), up);

			recalculateView = false;
			recalculateViewProj = true;
		}
		return view;
	}
	matrix invV() {
		return V().inversed();
	}
	const matrix& P() final override {
		if(recalculateProj) {

			proj = matrix::perspectiveFovRH(
				_fov,
				aspectRatio(),
				_near,
				_far
			);

			recalculateProj = false;
			recalculateViewProj = true;
		}
		return proj;
	}
	const matrix& VP() final override {
		if(recalculateView || recalculateProj || recalculateViewProj) {
			V();
			P();
			viewProj = proj * view;
			recalculateViewProj = false;
		}
		return viewProj;
	}
};

}