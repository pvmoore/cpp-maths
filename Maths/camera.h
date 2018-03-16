#pragma once

namespace maths {

class Camera {
public:
	virtual const matrix& V() = 0;
	virtual const matrix& P() = 0;
	virtual const matrix& VP() = 0;
};

}