#pragma once

namespace maths {

class Camera2D final : public Camera {
	matrix view;
	matrix proj;
	matrix viewProj;
	float _zoomFactor = 1, minZoom = 0.01f, maxZoom = 100;
	float rotationRads = 0;
	bool recalculateView = true;
	bool recalculateProj = true;
	bool recalculateViewProj = true;
public:
	float3 position;
	float3 up;
	uint2 windowSize = {};
	inline constexpr float zoomFactor() { return 1 / _zoomFactor; }

	std::string toString() const {
		std::string s = "[position=" + position.toString() + "]";
		return std::move(s);
	}

	void init(uint2 windowSize) {
		this->windowSize = windowSize;
		this->position = float3{(float)windowSize.x / 2, (float)windowSize.y / 2, 1};
		this->up = float3{0, 1, 0};
	}
	auto moveTo(float2 pos) {
		position = {pos.x, pos.y, 1};
		recalculateView = true;
		return *this;
	}
	auto moveBy(float2 pos) {
		position += {pos.x, pos.y, 0};
		recalculateView = true;
		return *this;
	}
	// TODO - can we do zoom using Z?
	/// 0.5 = zoomed out (50%), 1 = (100%) no zoom, 2 = (200%) zoomed in
	auto setZoom(float z, float minZoom, float maxZoom) {
		_zoomFactor = 1 / z;
		this->minZoom = minZoom;
		this->maxZoom = maxZoom;
		recalculateProj = true;
		return *this;
	}
	auto zoomOut(float z) {
		if(_zoomFactor == maxZoom) return *this;
		_zoomFactor += z;
		if(_zoomFactor > maxZoom) {
			_zoomFactor = maxZoom;
		}
		recalculateProj = true;
		return *this;
	}
	auto zoomIn(float z) {
		if(_zoomFactor == minZoom) return *this;
		_zoomFactor -= z;
		if(_zoomFactor < minZoom) {
			_zoomFactor = minZoom;
		}
		recalculateProj = true;
		return *this;
	}
	const matrix& P() final override {
		if(recalculateProj) {
			float width = windowSize.x*_zoomFactor;
			float height = windowSize.y*_zoomFactor;

			proj = matrix::orthoRH(width, -height, 0.0f, 100.0f);

			recalculateProj = false;
			recalculateViewProj = true;
		}
		return proj;
	}
	const matrix& V() final override {
		if(recalculateView) {
			/// Z points out of the screen
			view = matrix::lookAtRH(position, position + float3{0, 0, -1}, up);

			recalculateView = false;
			recalculateViewProj = true;
		}
		return view;
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